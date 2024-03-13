/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef COMM_ERROHANDLER_HXX
#define COMM_ERROHANDLER_HXX

#include <cstddef>
#include <memory>
#include <functional>
#include <ipl_config.h>
#include <comm/comm_dso.h>
#include <comm/commtypes.hxx>
#include <util/transport/Readable.hxx>

namespace comm {

    class ErrorHandler;
    using ErrorHandlerPtr = std::shared_ptr<ErrorHandler>;

    class ErrorHandlerImpl;
    class CallErrorContextImpl;

    class CallErrorEvent;
    namespace protocol {
        struct CallError;
    }

    /**
     * \brief
     *  A class for handling errors that occured during method execution in a service.
     *
     *  Some errors during method execution can make it impossible to execute a method call
     *  in a service (e.g. errors during deserialization of the calls arguments).
     *  Those errors are reported back to the calling client.
     *
     *  Due to the asynchronous design of comm method calls these errors are also
     *  reported asynchronoulsy with respect to the method call that triggered
     *  the error.
     *
     *  The ErrorHandler can be used to process those errors.
     *  The registered callback is called for every instance of such an error.
     *
     *  There is always an ErrorHandler instance available in a comm agent.
     *  \see ErrorHandler::getDefaultErrorHandler()
     *
     *  ErrorHandler instances can also be created and associated with Proxies.
     *  \see comm::Proxy::setErrorHandler()
     *
     *  An ErrorHandler associated with a comm::Proxy will only handle errors triggered by
     *  calls from the Proxy.
     *  The same ErrorHandler can be associated with several Proxies.
     *
     *  The default behaviour of an ErrorHandler is to trace a message on level error with
     *  some details of the failed call.
     *
     *  Registering a callbacks allows to taylor the reaction to errors.
     *
     **/
    class COMM_EXPORT ErrorHandler {

        public:
            ErrorHandler() IPL_NOEXCEPT;
            ~ErrorHandler() IPL_NOEXCEPT;

            ErrorHandler(const ErrorHandler&) = delete;
            ErrorHandler(ErrorHandler&&) = delete;
            ErrorHandler& operator=(const ErrorHandler&) = delete;
            ErrorHandler& operator=(ErrorHandler&&) = delete;


            /**
             * \brief
             *  A class for retrieving context information about a comm call error.
             *
             *  CallErrorContext is not copy- or move- constructible, but all its elements are.
             */
            class COMM_EXPORT CallErrorContext {
                public:
                    enum class ErrorCode  {
                        DESERIALIZATION_FAILED      // payload could not be deserialized
                        ,METHOD_NOT_AVAILABLE       // method id does not exist in the service
                        ,UNKNOWN_ERROR              // any other error
                    };

                    explicit CallErrorContext(const CallErrorContextImpl& impl) IPL_NOEXCEPT;
                    ~CallErrorContext() IPL_NOEXCEPT;

                    CallErrorContext(const CallErrorContext&) = delete;
                    CallErrorContext(CallErrorContext&&) = delete;
                    CallErrorContext& operator=(const CallErrorContext&) = delete;
                    CallErrorContext& operator=(CallErrorContext&&) = delete;

                    /** Retrieves the ID of the proxy that was used in the call that caused the error. */
                    ProxyID getProxyID() const IPL_NOEXCEPT;
                    /** Retrieves the ID of the stub that received the call that caused the error. */
                    StubID getStubID() const IPL_NOEXCEPT;
                    /** Retrieves the ID of the method called that caused the error. */
                    MethodID getMethodID() const IPL_NOEXCEPT;
                    /** Retrieves the sequence number of the call that caused the error. */
                    uint32_t getSeq() const IPL_NOEXCEPT;
                    /** Retrieves the time stamp of the call that caused the error. */
                    uint64_t getTimeStamp() const IPL_NOEXCEPT;
                    /** Retrieves the ID of the service that received the call that caused the error. */
                    const InstanceID& getInstanceID() const IPL_NOEXCEPT;
                    using Readable = util::transport::Readable;
                    /** Retrieves the serialized payload sent in the call that caused the error. */
                    const Readable& getPayload() const IPL_NOEXCEPT;
                    /** Retrieves the the error code */
                    ErrorCode getErrorCode() const IPL_NOEXCEPT;
                private:
                    // CallErrorContext is passed in call by const reference,
                    // cannot be copied. Raw pointer is fine.
                    const CallErrorContextImpl* m_impl{nullptr};

            };

            /** The callback function used to handle call errors.
             *
             *  It can be registered with registerCallErrorCallback().
             *
             *  The passed \a ctx can be used to retrieve details about the call that caused the error.
             *  \see CallErrorContext.
             *
             *  The callback will be executed from the thread associated with the comm::ActiveObject
             *  of the Proxy that caused the error (its ProxyID is returned in CallErrorContext::getProxyID()).
             *
             *  If the Proxy has no associated ActiveObject (e.g. a Proxy for a service without replies) the
             *  callback will be executed from the comm::Agent's notifier thread.
             *
             *  The callback is called without taking any locks. This means if several proxies with
             *  different ActiveObjects share an ErrorHandler instance, the same callback may be
             *  called from different threads concurrently.
             *
             *  \return If true is returned the handler will emit its default error trace, if
             *  false is returned, it will not.
             *
             *  An example of registering an ErrorHandler at a proxy:
             *  \code
             *     comm::SomeProxy m_proxy(...);
             *     ...
             *     comm::ErrorHandlerPtr eh = comm::ErrorHandler::create();
             *     eh->registerCallErrorCallback(
             *              // error handler callback
             *              [](const comm::ErrorHandler::CallErrorContext& ctx) -> bool {
             *                  IPL_TRACE_USE_CHANNEL(TEST_CHANNEL); // some channel
             *                  IPL_TRACE_ERR_CV("Call Error: from proxy %d to stub %d, method %u (seq %u), service %s"
             *                          , (int)ctx.getProxyID()
             *                          , (int)ctx.getStubID()
             *                          , (unsigned)ctx.getMethodID()
             *                          , (unsigned)ctx.getSeq()
             *                          , ctx.getInstanceID().str().c_str()
             *                          );
             *                  return false; // let's not have the default trace
             *              }
             *      );
             *      m_proxy.setErrorHandler(eh);
             *  \endcode
             *
             *  The global ErrorHandler could be used instead with:
             *  \code
             *  comm::ErrorHandler::getDefaultErrorHandler()->registerCallErrorCallback(
             *              [](const comm::ErrorHandler::CallErrorContext& ctx) -> bool {
             *                  // callback implementation
             *                  return false;
             *              }
             *        );
             *  \endcode
             */
            using CallErrorCallback = std::function<bool(const comm::ErrorHandler::CallErrorContext& ctx
                                                        )>;

            /** Registers a callback to handle call errors.
             *  Repeatedly registering a callback replaces a previously registered callback.
             *  Registering a nullptr callback unregsiters a previously registered callback.
             */
            void registerCallErrorCallback( const comm::ErrorHandler::CallErrorCallback& f ) IPL_NOEXCEPT ;

            /** Returns the per-agent ErrorHandler.
             * May return an empty ErrorHandlerPtr if called before the comm::AgentStarter
             * constructor or after its destructor.
             */
            static ErrorHandlerPtr getDefaultErrorHandler() IPL_NOEXCEPT ;

            /** Creates a new ErrorHandler.
             */
            static ErrorHandlerPtr create() IPL_NOEXCEPT;
        private:

            void handleCallError(const protocol::CallError& error);

            using ErrorHandlerImplPtr = std::unique_ptr<ErrorHandlerImpl>;
            ErrorHandlerImplPtr   m_impl;

            friend class CallErrorEvent;

    };

}
#endif // COMM_ERROHANDLER_HXX
// vim: ts=4 sw=4:

