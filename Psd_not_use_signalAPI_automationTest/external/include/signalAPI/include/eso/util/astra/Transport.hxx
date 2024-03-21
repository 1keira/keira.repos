/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/
/****************************************************************************/
#ifndef UTIL_ASTRA_TRANSPORT_HXX
#define UTIL_ASTRA_TRANSPORT_HXX
/****************************************************************************/

#include <util/util_dso.h>
#include <util/astra/astra.hxx>
#include <util/transport/PeerInfo.hxx>
#include <osal/Message.hxx>
#include <common/buffers.hxx>
#include <common/error/Error.hxx>
#include <iplbase/exceptions.hxx>

#include <threadsafe/Mutex.hxx>
#include <set>
#include <memory>

/****************************************************************************/

namespace util {
    namespace astra {

/****************************************************************************/

        /*!
            \brief New-style asynchronous interface for bidirectional
            communication of chunks of bytes
            
            \see \ref util_astra_page
        */
        class UTIL_EXPORT Transport: public ipl::Buf::Allocator {
            
        public:
            
            class RawCallbacks;
            class Client;
            class Connect;
            class Hold;
            
            //! \brief You \e should use this for buffers to be sent on this
            //! Transport
            //!
            //! By default this calls ipl::Buf::DEFAULT_ALLOCATOR.malloc(),
            //! but some implementations will provide something optimized.
            ipl::Buf malloc(size_t bytes) const IPL_NOEXCEPT override;
            
            /*!
                If not, expect all other calls to fail.
            */
            virtual bool isValid() const IPL_NOEXCEPT=0;
            
            /*!
                \brief Try to send \p data over this Transport
                
                On success this takes ownership of \p data and returns \c false,
                i.e. you must not touch or free \p data afterwards.
                
                On failure ownership is left with the caller, \c true is returned
                and ipl_error is set accordingly.
                On a retryable error (e.g. Transport congestion) the \p client
                from set_client() is guaranteed to get its try_again()
                callback called exactly once and then should call send() again
                with the same \p data (which may fail again and lead to more
                retries) -- provided it is still interested in sending, of course.
                On a non-retryable error the client should free \c data and
                delete the Transport.
                
                \p data \e should have been allocated via this instance's
                alloc() method to allow for zero copy optimizations, but
                any ipl::Buf will work.
            */
            virtual bool send(const ipl::Buf &data) IPL_NOEXCEPT=0;
            
            /*!
                \brief Retry a failed call to \c client->received()
                or client->error()
            */
            virtual void retry() IPL_NOEXCEPT=0;

            /*!
                \brief Avoid calling directly, use Client::Connect instead
                
                A Transport is created without a Client, i.e. it is very much
                inoperable initially. This is necessary because the client
                needs to know the ultimate receiver of the callbacks while
                a factory like e.g. a Listener cannot know it.
                
                Some initialization must possibly be deferred until
                set_client() and finalization must be done before
                set_client(nullptr) actually removes the client.
                This is done by set_client() calling enable() / disable()
                internally, and concrete Transport implementations can
                override the empty default implementations as needed.
            */
            void set_client(RawCallbacks *client) IPL_NOEXCEPT;
            
            static ipl::ErrorType error;
            //! \brief "Failed for now, you can retry later"
            static ipl::ErrorType retryable_error;
            //! \brief "You try something invalid, the Transport remains in service"
            static ipl::ErrorType invalid_use_error;
            //! \brief "Transport permanently out of service"
            static ipl::ErrorType final_error;
            
        protected:
            
            //! Called internally by set_client(). Override as needed.
            //!
            //! Note that this can be called multiple times and therefore must
            //! be idempotent
            virtual void enable() IPL_NOEXCEPT;
            //! Called internally by set_client(nullptr). Override as needed.
            virtual void disable() IPL_NOEXCEPT;
            
            threadsafe::Mutex mutex{true};  // recursive for registration pattern
            RawCallbacks *client{nullptr};
            bool retry_needed{false};
        };

/****************************************************************************/

        /*!
            \brief Callback interface for Transport
            
            Basic principle is that the callbacks (except retry_send()) can
            fail, in which case they return \c true and get called again
            when you call \c retry() on the transport later.
            
            The exception is retry_send() which does the opposite ––
            it tells the client that it should retry a send() call that failed
            earlier.
        */
        class UTIL_EXPORT Transport::RawCallbacks {
            
        public:
            virtual ~RawCallbacks() IPL_NOEXCEPT=default;
            
            //! \brief The last send() on \p transport can be retried now
            virtual void retry_send(Transport *transport) IPL_NOEXCEPT=0;
            
            //! \brief A message \p data has been received on \p transport
            //!
            //! Return \c false and take ownership of \p data if you can
            //! or return \c true and don't touch \p data if not.
            //! In that case you must call \c transport->retry() later
            //! to trigger another call.
            virtual bool received(Transport *transport,
                                  const ipl::Buf &data) IPL_NOEXCEPT=0;
            //! \brief Some (non-retrieable) \p error happened on \p transport
            //!
            //! Return \c false if you can process (or ignore) the error
            //! or return \c true if not.
            //! In that case you must call \c transport->retry() later
            //! to trigger another call.
            virtual bool error(Transport *transport,
                               const std::string &error) IPL_NOEXCEPT=0;
            //! \brief Peer identity information has been received on \p transport
            //!
            //! This can be called any number of times, including zero,
            //! and deliver several different or identical peerinfos.
            //!
            //! Return \c false if you can process (or ignore) \p peerinfo
            //! or return \c true if not.
            //! In that case you must call \c transport->retry() later
            //! to trigger another call.
            virtual bool peerinfo(Transport *transport,
                                  const std::shared_ptr<transport::PeerInfo> &peerinfo
                                 ) IPL_NOEXCEPT;
        };

/****************************************************************************/

        /*!
            \brief Asynchronous callback handler for sending to and 
            receiving from a Transport,
            ready to use with osal::Message dispatching
        */
        class UTIL_EXPORT Transport::Client:
            public RawCallbacks, public osal::Message::Pusher {
            
        public:
            explicit Client(osal::Message::Sink &queue) IPL_NOEXCEPT:
                queue(queue) {}
            
            //! \brief We have received \p data from \p transport
            virtual void transport_received(Transport *transport,
                                            const ipl::Buf &data) IPL_NOEXCEPT=0;
            //! \brief Some (non-retrieable) \p error happened on \p transport
            virtual void transport_error(Transport *transport,
                                         const std::string &error) IPL_NOEXCEPT=0;
            //! \brief The last send() on \p transport can be retried now
            virtual void transport_retry(Transport *transport) IPL_NOEXCEPT=0;
            //! \brief We have received \p peerinfo on \p transport
            virtual void transport_peerinfo(
                Transport *transport,
                const std::shared_ptr<transport::PeerInfo> &peerinfo
            ) IPL_NOEXCEPT;
           
            // RawCallbacks
            bool received(Transport *transport,
                          const ipl::Buf &data) IPL_NOEXCEPT override;
            bool error(Transport *transport,
                       const std::string &error) IPL_NOEXCEPT override;
            bool peerinfo(Transport *transport,
                          const std::shared_ptr<transport::PeerInfo> &peerinfo
                         ) IPL_NOEXCEPT override;
            void retry_send(Transport *transport) IPL_NOEXCEPT override;
                            
            // Pusher
            void retry_push() IPL_NOEXCEPT override;
            
        protected:
            osal::Message::Sink &queue;
            threadsafe::Mutex mutex;
            typedef std::set<Transport *> Waiting;
            Waiting waiting_receive;
            Waiting waiting_send;
        };
        
/****************************************************************************/

        /*!
            \brief Guard to register some Client(s) with a
            Transport \em and \em unregister \em them \em again
            
            Prefer this over manually calling Transport::set_client()
            wherever feasible.
            And don't try to be clever and have your Client inherit from this,
            as it is nontrivial to get right. You have been warned.
            
            The reason why this exists at all is to fulfill these goals
            simultaneously and as hassle-free as possible:
            - Have the Transport know its callback object
            - Allow the callback object to know its Transport if needed,
              so we cannot simply pass one in the other's constructor
            - Avoid segfaults from forgetting to deregister a Client before
              it is destroyed
            - Avoid more segfaults from auto-registering in some base class
              constructor while the derived class's constructor has not yet
              initialized the actual logic
        */
        class UTIL_EXPORT Transport::Connect {
            
        public:
            Connect(Transport *transport, RawCallbacks *client) IPL_NOEXCEPT:
                transport(transport) {
                // defensive coding -- caller might not be able to check this
                // until later, so avoid segfault for now
                if(transport)
                    transport->set_client(client);
            }
            
            Connect(Transport &transport, RawCallbacks &client) IPL_NOEXCEPT:
                Connect(&transport, &client) {}
                
            Connect(Connect &&other) IPL_NOEXCEPT: transport(other.transport) {
                other.transport=nullptr;
            }
            
            ~Connect() IPL_NOEXCEPT {
                if(transport)
                    transport->set_client(nullptr);
            }
            
        protected:
            Transport *transport;
        };
        
/****************************************************************************/

        /*!
            \brief Convenient wrapper for dealing with failed sends
            
            Wraps around the sending functionality of a Transport but doesn't
            fail retryably. Instead it holds the buffer-to-be-sent internally
            and retries on retry_send().
            
            You must not try to send another buffer while one is still being
            held.
        */
        class UTIL_EXPORT Transport::Hold {
                
        public:
            explicit Hold(Transport &transport) IPL_NOEXCEPT:
                transport(transport) {}
            Hold(Hold &&)=default;

            ~Hold() IPL_NOEXCEPT { if(buf) buf.free(); }
            
            //! \brief \c true if a buffer is pending
            explicit operator bool () const IPL_NOEXCEPT { return buf; }
            
            //! Contrary to Transport::send() this always takes ownership of
            //! \p data. This relieves the user from the burden of conditionally
            //! holding on to a buffer that failed to send.
            //!
            //! If you call this while another buffer is already pending
            //! (as indicated by operator bool ()), \c true is returned,
            //! error is raised and \p data is deleted.
            //!
            //! On a retryable error the buffer gets stored for a later retry
            //! and the error gets swallowed,
            //! any other error automatically deletes it.
            //!
            //! Non-retryable errors from Transport::send() get passed along.
            bool send(const ipl::Buf &data) IPL_NOEXCEPT {
                if(buf) {
                    ipl_raise(error, 0);
                    data.free();
                    return true;
                }
                buf=data;
                if(retry_send()) {
                    if(ipl_error.isA(retryable_error)) {  // BRANCH_COVERAGE_UNTESTABLE
                        ipl_error.ack();
                        return false;
                    }
                    buf.free();
                    buf={};//ipl::Buf();
                    return true;
                }
                return false;
            }
            
            //! If data from some failed send is stored, the send is retried.
            //! If that fails (non-retryably), the error is passed on and
            //! the buffer is deleted.
            //!
            //! Call this from your Client's retry_send.
            bool retry_send() IPL_NOEXCEPT {
                if(!buf)
                    return false;  // nothing to do is success
                auto b=buf;
                buf={};  // cope with not-so-asynchronous Transports
                if(transport.send(b)) {
                    if(ipl_error.isA(retryable_error)) {  // BRANCH_COVERAGE_UNTESTABLE
                        IPL_ASSERT(!buf);
                        ipl_error.ack();
                        buf=b;
                        return false;
                    }
                    b.free();
                    return true;
                }
                return false;
            }
            
            //! If data from some earlier failed send is stored, delete it.
            void free() IPL_NOEXCEPT {
                if(buf) {
                    buf.free();
                    buf={};
                }
            }
            
            Transport &transport;  //!< \brief Use for buffer allocation
            static ipl::ErrorType error;
            
        protected:
            ipl::Buf buf;
        };
            
/****************************************************************************/

    }  // end of namespace astra
}  // end of namespace util

/****************************************************************************/
#endif
