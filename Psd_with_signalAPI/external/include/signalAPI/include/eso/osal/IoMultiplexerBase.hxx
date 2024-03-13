/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

/****************************************************************************/
#ifndef OSAL_IOMULTIPLEXERBASE_HXX
#define OSAL_IOMULTIPLEXERBASE_HXX
/****************************************************************************/

#include <osal/osal_dso.h>

#include <threadsafe/Mutex.hxx>
#include <threadsafe/Condition.hxx>
#include <common/Macros.hxx>
#include <common/error/Error.hxx>

#include <string>
#include <map>
#include <list>
#include <algorithm>
#include <functional>
#include <thread>


// this should be cleaned up together with the rest of Socket
#if defined IPL_OS_POSIX || defined IPL_OS_INTEGRITY
#    include "SocketDefs-posix.hxx"
#elif defined IPL_OS_WINPC
#    include "SocketDefs-win32.hxx"
#else
#    error "error undefined IPL_OS_ variant"
#endif

/****************************************************************************/

namespace osal {

/****************************************************************************/

    /*!
        \internal Common code for the various IoMultiplexerImpl
    */
    class OSAL_EXPORT IoMultiplexerBase {
        
    public:
        
        template <typename ConcreteImpl> class Impl;
        
        class Channel;
        class Client;
        
        virtual ~IoMultiplexerBase()=default;  /* keeping the compiler happy */
        
        void wait_until_running() IPL_NOEXCEPT;
        
        //! \brief Make run() return, wait until the mainloop has ended
        void stop() IPL_NOEXCEPT;

        static ipl::ErrorType error;
        
    protected:
        
        struct Subscription {
            Client *client{nullptr};
            bool for_read;
            bool for_write;
            // for_connect and for_dead implicitly true
            
            Subscription()=default;
            Subscription(Client *client, bool for_read, bool for_write):
                client(client), for_read(for_read), for_write(for_write) {}
        };
        
        //! \brief Wake up main loop
        virtual void update(threadsafe::Mutex::Guard & /* ensure mutex is held */)=0;
        
        threadsafe::Mutex mutex{true};  // recursive for registration pattern
        threadsafe::Condition condition{mutex};
        bool waiting{false};
        enum class Status { stopped, running, stopping } status{Status::stopped};
        //! \brief run() has seen any state changes, the requesting method can continue
        bool changes_seen{false};
        std::thread::id thread_id{};
    };

/****************************************************************************/

    template <typename ConcreteImpl>
    class IoMultiplexerBase::Impl: public IoMultiplexerBase {
            
    public:
        
#ifdef _MSC_VER  // we will need some actual version check in the future...
        // This is wrong. New & standards conforming clang does not like it.
        // All older compilers understand it, though, and our MSVC chokes
        // on the correct version.
        using Channel=typename ConcreteImpl::Channel;
#else
        // MSVC does not like this, but clang insists in it,
        // and it is actually correct.
        typedef class ConcreteImpl::Channel Channel;
#endif
        
        //! \brief Add another socket/handler
        //!
        //! The \p client will receive callbacks for events on \p channel
        //! for connection, fatal error and whatever is requested by
        //! \p for_read and \p for_write, additionally to whatever has
        //! already be requested.
        //! This is idempotent insofar as multiple calls to add() only
        //! set more flags but don't make the callbacks be called twice.
        //! Returns false if added successfully, true if adding failed
        virtual bool add(Channel &channel, Client &client,
                 bool for_read=true, bool for_write=false) IPL_NOEXCEPT;
        //! \brief Remove a socket
        //!
        //! On return it is guaranteed that no forther callbacks happen
        //! for \p channel, including io_connected() and io_dead(),
        //! i.e. you can delete it safely.
        virtual void remove(Channel &channel) IPL_NOEXCEPT;
        //! \brief Remove a handler
        //!
        //! On return it is guaranteed that no forther callbacks happen
        //! on \p client, including io_connected() and io_dead(),
        //! i.e. you can delete it safely.
        virtual void remove(const Client &client) IPL_NOEXCEPT;
        
    protected:
        //! \brief Remove a socket from certain events
        //!
        //! On return it is guaranteed that no further callbacks to \p client
        //! happen for the requested events for \p channel,
        //! but io_connected() and iuo_read() are still possible.
        void remove(threadsafe::Mutex::Guard & /* ensure mutex is held */,
                    Channel *channel, Client *client,
                    bool from_read, bool from_write);
        
        using Subscriptions=std::map</* no const */Channel *, std::list<Subscription>>;
        Subscriptions subscriptions;
        
        static void erase_if(Subscriptions &container,
            std::function<bool (const typename Subscriptions::value_type &value)> pred
        )
        {
            typename Subscriptions::const_iterator i=container.begin();
            while(i!=container.end()) {
                if(pred(*i))
                    i=container.erase(i);
                else
                   ++i;
            }
        }
    };

    template<typename ConcreteImpl>
    bool IoMultiplexerBase::Impl<ConcreteImpl>::add(Channel &channel,
                                                    Client &client,
                                                    bool for_read,
                                                    bool for_write) IPL_NOEXCEPT
    {
        if (!channel.isPollable())
        {
            ipl_raise(IoMultiplexerBase::error, 0);
            return true;
        }
        threadsafe::Mutex::Guard lock(mutex);
        auto &l=subscriptions[&channel];
        auto i=std::find_if(l.begin(), l.end(), [&client](const Subscription &s) {
            return s.client==&client;
        });
        if(i==l.end())
            l.emplace_back(&client, for_read, for_write);
        else {
            i->for_read|=for_read;
            i->for_write|=for_write;
        }
        changes_seen=false;
        update(lock);
        return false;
    }

    template<typename ConcreteImpl>
    void IoMultiplexerBase::Impl<ConcreteImpl>::remove(Channel &channel) IPL_NOEXCEPT
    {
        threadsafe::Mutex::Guard lock(mutex);

        subscriptions.erase(&channel);
        changes_seen=false;
        update(lock);
        while(thread_id != std::this_thread::get_id() &&
              status!=Status::stopped && !changes_seen)
            condition.wait();
    }

    template<typename ConcreteImpl>
    void IoMultiplexerBase::Impl<ConcreteImpl>::remove(const Client &client) IPL_NOEXCEPT
    {
        threadsafe::Mutex::Guard lock(mutex);
        
        for(auto &p: subscriptions)
        {
            (void)std::remove_if(p.second.begin(), p.second.end(),
                                 [&client](const Subscription &s) {
                return s.client==&client;
            });
        }
        erase_if(subscriptions,
                 [](const typename Subscriptions::value_type &p) {
            return p.second.empty();
        });
        
        changes_seen=false;
        update(lock);
        while(thread_id != std::this_thread::get_id() &&
              status!=Status::stopped && !changes_seen)
            condition.wait();
    }

    template<typename ConcreteImpl>
    void IoMultiplexerBase::Impl<ConcreteImpl>::remove(threadsafe::Mutex::Guard &,
                                                       Channel *channel,
                                                       Client *client,
                                                       bool from_read,
                                                       bool from_write)
    {
        auto i=subscriptions.find(channel);
        if(i!=subscriptions.end()) {
            for(auto &s : i->second)
                if(s.client==client) {
                    if(from_read)
                        s.for_read=false;
                    if(from_write)
                        s.for_write=false;
                }
            // subscription not removed because io_connected / io_dead
        }
    }
    
/****************************************************************************/

    //! \brief Interface for things to be monitored for I/O readiness (e.g. Sockets)
    class OSAL_EXPORT IoMultiplexerBase::Channel {
        
    public:
        
        enum class Status {
            ok,          //!< \brief Is connected and can be used
            connecting,  //!< \brief Is currently connecting
            error        //!< \brief Cannot currently be used
        };
        
        virtual ~Channel()=default;  // to keep the compiler happy
        
    protected:
        friend class IoMultiplexerImpl;
        
        //! \brief Try to nonblockingly finish any pending connect
        virtual Status finish_connect() IPL_NOEXCEPT=0;
        virtual Status status() const IPL_NOEXCEPT=0;
    };

/****************************************************************************/

    //! \brief Interface for monitoring I/O readiness
    class OSAL_EXPORT IoMultiplexerBase::Client {
    public:
        virtual ~Client()=default;

        //! \brief Gets called when \p channel has connected successfully
        //!
        //! If \p channel is an osal::TCPSocket this callback \e should
        //! call \c connected() on it to mimic the behaviour of
        //! synchronous \c connect().
        //! Or you ignore that very much unused feature altogether.
        //!
        //! \warning During this call the IoMultiplexer holds an internal
        //! mutex. Make sure your callback does not content for another one
        //! with code that calls into the IoMultiplexer.
        virtual void io_connected(const Channel *channel) IPL_NOEXCEPT;
        //! \brief Gets called when \p channel has an irrecoverable error
        //! including the peer has closed the connection
        //!
        //! Reading and writing might still be possible for some time.
        //!
        //! \warning During this call the IoMultiplexer holds an internal
        //! mutex. Make sure your callback does not content for another one
        //! with code that calls into the IoMultiplexer.
        virtual void io_dead(const Channel *channel, const std::string &error) IPL_NOEXCEPT;
        //! \brief Gets called when \p channel is readable,
        //! returns whether the client should stay subscribed for
        //! read on this channel
        //!
        //! \warning During this call the IoMultiplexer holds an internal
        //! mutex. Make sure your callback does not content for another one
        //! with code that calls into the IoMultiplexer.
        virtual bool io_read(const Channel *channel) IPL_NOEXCEPT;
        //! \brief Gets called when \p channel is writable,
        //! returns whether the client should stay subscribed for
        //! write on this channel
        //!
        //! \warning During this call the IoMultiplexer holds an internal
        //! mutex. Make sure your callback does not content for another one
        //! with code that calls into the IoMultiplexer.
        virtual bool io_write(const Channel *channel) IPL_NOEXCEPT;
    };

/****************************************************************************/

}  // end of namespace osal

/****************************************************************************/
#endif
