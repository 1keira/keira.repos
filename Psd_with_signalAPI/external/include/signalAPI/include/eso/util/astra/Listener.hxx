/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/
/****************************************************************************/
#ifndef UTIL_ASTRA_LISTENER_HXX
#define UTIL_ASTRA_LISTENER_HXX
/****************************************************************************/

#include <util/util_dso.h>
#include <osal/Message.hxx>
#include <iplbase/exceptions.hxx>

#include <threadsafe/Mutex.hxx>
#include <memory>
#include <map>

/****************************************************************************/

namespace util {
    namespace astra {

/****************************************************************************/

        class Transport;

/****************************************************************************/

        /*!
            \brief New-style asynchronous interface for "receiving"
            incoming Transport connections
        */
        class UTIL_EXPORT Listener {
            
        public:
            
            class RawCallbacks;
            class Client;
            class Connect;
            
            virtual ~Listener() IPL_NOEXCEPT=default;
            
            /*!
                If not, expect all other calls to fail.
            */
            virtual bool isValid() const IPL_NOEXCEPT=0;
            
            /*!
                \brief Retry a failed call to \c client->accepted()
            */
            virtual void retry_accepted() IPL_NOEXCEPT=0;

            /*!
                \brief Avoid calling directly, use Listener::Connect instead
                
                A Listener is created without a Client, i.e. it is very much
                inoperable initially. This is necessary because the client
                needs to know the ultimate receiver of the callbacks while
                a factory cannot know it.
                
                Some initialization must possibly be deferred until
                set_client() and finalization must be done before
                set_client(nullptr) actually removes the client.
                This is done by set_client() calling enable() / disable()
                internally, and concrete Listener implementations can
                override the empty default implementations as needed.
            */
            void set_client(RawCallbacks *client) IPL_NOEXCEPT;
            
        protected:
            //! Called internally by set_client(). Override as needed.
            virtual void enable() IPL_NOEXCEPT;
            //! Called internally by set_client(nullptr). Override as needed.
            virtual void disable() IPL_NOEXCEPT;

            threadsafe::Mutex mutex{true};  // recursive for registration pattern
            RawCallbacks *client{nullptr};
        };

/****************************************************************************/

        /*!
            \brief Callback interface for Listener
        */
        class UTIL_EXPORT Listener::RawCallbacks {
            
        public:
            virtual ~RawCallbacks() IPL_NOEXCEPT=default;
            
            //! \brief A \p transport has been accepted on the \p listener
            //!
            //! Return \c false and take ownership of \p transport if you can
            //! or return \c true and don't touch \p transport if not.
            //! In that case you must call \c listener->retry_accepted() later.
            virtual bool accepted(Listener *listener,
                                  Transport *transport) IPL_NOEXCEPT=0;
            virtual bool error(Listener *listener, const std::string &error) IPL_NOEXCEPT=0;
        };

/****************************************************************************/

        class UTIL_EXPORT Listener::Client:
            public RawCallbacks, public osal::Message::Pusher {
            
        public:
            explicit Client(osal::Message::Sink &queue) IPL_NOEXCEPT:
                queue(queue) {}
            
            virtual void listener_accepted(Listener *listener,
                                           Transport *transport) IPL_NOEXCEPT=0;
            virtual void listener_error(Listener *listener,
                                        const std::string &error) IPL_NOEXCEPT=0;

            // RawCallbacks
            bool accepted(Listener *listener,
                          Transport *transport) IPL_NOEXCEPT override;
            bool error(Listener *listener,
                       const std::string &error) IPL_NOEXCEPT override;
                            
            // Pusher
            void retry_push() IPL_NOEXCEPT override;
            
        protected:
            osal::Message::Sink &queue;
            threadsafe::Mutex mutex;
            typedef std::set<Listener *> Waiting;
            Waiting waiting;
        };

/****************************************************************************/

        /*!
            \brief Guard to register some Client(s) with a
            Listener \em and \em unregister \em them \em again
            
            Prefer this over manually calling Listener::set_client()
            wherever feasible.
            And don't try to be clever and have your Client inherit from this,
            as it is nontrivial to get right. You have been warned.

            For more rationale see Transport::Connect.
        */
        class UTIL_EXPORT Listener::Connect {
            
        public:
            Connect(Listener &listener, RawCallbacks &client) IPL_NOEXCEPT:
                listener(&listener) {
                this->listener->set_client(&client);
            }

            Connect(Connect &&other) IPL_NOEXCEPT: listener(other.listener) {
                other.listener=nullptr;
            }

            ~Connect() IPL_NOEXCEPT {
                if(listener)
                    listener->set_client(nullptr);
            }
            
        protected:
            Listener *listener;
        };
        
/****************************************************************************/

    }  // end of namespace astra
}  // end of namespace util

/****************************************************************************/
#endif
