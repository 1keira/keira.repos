/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

/****************************************************************************/
#ifndef OSAL_IOMULTIPLEXER_HXX
#define OSAL_IOMULTIPLEXER_HXX
/****************************************************************************/

#include <osal/osal_dso.h>

#include <osal/Thread.hxx>
#include <common/Shared.hxx>
#include <threadsafe/Mutex.hxx>
#include <threadsafe/Condition.hxx>

#include <map>
#include <list>

#if defined USE_EPOLL
#    include "IoMultiplexerImpl-epoll.hxx"
#elif defined IPL_OS_POSIX || defined IPL_OS_INTEGRITY
#    include "IoMultiplexerImpl-poll.hxx"
#elif defined IPL_OS_WINPC
#    include "IoMultiplexerImpl-win32.hxx"
#else
#    error "error undefined IPL_OS_ variant"
#endif

/****************************************************************************/

namespace osal {

/****************************************************************************/

    /*!
        \brief "Socket poller"
        
        Monitor 0 or more Channels for I/O readiness and inform
        interested Clients.
        
        See base classes for more methods.
    */
    class OSAL_EXPORT IoMultiplexer {
        
    public:
        virtual ~IoMultiplexer() = default;

        class Standalone;
        
        using Channel=IoMultiplexerBase::Channel;
        using Client=IoMultiplexerImpl::Client;
        
        //! \brief Wait for events to happen on monitored channels,
        //! dispatch callbacks, wait more
        void run() IPL_NOEXCEPT { impl.run(); }
        //! \brief Make run() return, wait until the mainloop has ended
        void stop() IPL_NOEXCEPT { impl.stop(); }
        
        //! \brief Add another socket/handler
        //!
        //! The \p client will receive callbacks for events on \p channel
        //! for connection, fatal error and whatever is requested by
        //! \p for_read and \p for_write, additionally to whatever has
        //! already be requested.
        //! This is idempotent insofar as multiple calls to add() only
        //! set more flags but don't make the callbacks be called twice.
        //! \return false if the socket/handle can be added, true otherwise, e.g.
        //! if the isPollable for a socket is false. An error will be raised in
        //! this case
        virtual bool add(IoMultiplexerImpl::Channel &channel, Client &client,
                 bool for_read=true, bool for_write=false) IPL_NOEXCEPT {
            return impl.add(channel, client, for_read, for_write);
        }
        //! \brief Remove a socket
        //!
        //! On return it is guaranteed that no further callbacks happen
        //! for \p channel, including io_connected() and io_dead(),
        //! i.e. you can delete it safely.
        void remove(IoMultiplexerImpl::Channel &channel) IPL_NOEXCEPT {
            impl.remove(channel);
        }
        //! \brief Remove a handler
        //!
        //! On return it is guaranteed that no further callbacks happen
        //! on \p client, including io_connected() and io_dead(),
        //! i.e. you can delete it safely.
        void remove(const Client &client) IPL_NOEXCEPT {
            impl.remove(client);
        }
        
        static ipl::Shared<Standalone> DEFAULT;
        
    protected:
        IoMultiplexerImpl::Impl impl;
    };

/****************************************************************************/

    /*!
        \brief Self-contained IoMultiplexer that runs in its own thread
        
        This is mainly meant to be used with ipl::Shared.
    */
    class IoMultiplexer::Standalone: public IoMultiplexer {
        
    public:
        Standalone(): thread(main, this) {
            thread.start();
            impl.wait_until_running();
        }
        ~Standalone() override {
            stop();
            if (thread.join())
                ipl_error.ack();
        }

        Standalone(const Standalone&) = delete;
        Standalone& operator=(const Standalone&) = delete;
        
    protected:
        static void main(void *context);
        
        osal::Thread thread;
    };

/****************************************************************************/

}  // end of namespace osal

/****************************************************************************/
#endif
