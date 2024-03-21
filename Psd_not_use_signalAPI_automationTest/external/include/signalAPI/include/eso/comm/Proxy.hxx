/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/


#ifndef COMM_PROXY_HXX
#define COMM_PROXY_HXX

#include <memory>

#include <comm/comm_dso.h>
#include <comm/commtypes.hxx>
#include <comm/Identity.hxx>
#include <comm/Error.hxx>
#include <comm/Lifecycle.hxx>
#include <osal/SystemLogger.hxx>
#include <comm/ServiceRegistration.hxx>
#include <util/serializer/SerializerTag.hxx>
#include <comm/ErrorHandler.hxx>
#include <comm/ServiceVersion.hxx>

// support mock core implementation in unit tests
class MockAgent;

namespace comm {

    struct ProxyState;
    class ConnectProxyJob;
    class DisconnectProxyJob;
    class Core;
    class Model;
    class ServiceInfo;
    class ProxyCompletionEvent;
    class ProxyLifecycleEvent;
    class StatusTrace;
    class AgentImpl;
    class CallEventImpl;
    class Proxy;
    class ErrorHandler;
    namespace protocol {
        class V7MessageSender;
    }

    COMM_EXPORT bool raiseUnborn();
    COMM_EXPORT bool raiseDead();

    typedef void (*ProxyReleasedFct)(void* ctx, const comm::Proxy& proxy);

/*!
    \brief Base class for all comm proxies.

        Proxies represent comm services in a client's context.
        This proxy-class is a wrapper for a concrete proxy, which does the marshalling if necessary.

        The proxy must be created first and then connected. After the proxy was connected
        and its service is available the service can be accessed using the proxy.
        If the service disappears the proxy becomes unusable.

        Proxies support tracking of a service lifecycle.

        A proxy has a state during its lifecycle:
            UNBORN  when it is created but not connected to the a service instance
            ALIVE   when it is connected to a service instance
            DEAD    when the service instance has been unregistered or is unacessible for other reasons
                    e.g. loss of connection to the process running the service.

        A proxy which is DEAD can never be reused again. A new proxy must be created.

        \note Proxies are not thread safe. Access to shared proxies from different threads must be
        synchronized within the client.

        \note Proxies support tracking of the lifecycle of a service instance. The invovation of
        LifecycleListener methods reflect the lifecycle of a proxy-service session. It can be closed
        for instance if the proxy disconnects, if the service unregisters or if the connection
        to the process hosting the service is lost.
        After a disconnect() returns no more LifecycleListener callbacks are called for a proxy.
        It is still possible though that a LifecycleListener callback is already in process
        when disconnect() is called if the session was terminated from the other side.

 **/
    class COMM_EXPORT Proxy : public Lifecycle  {
        public:
            /*! default ctor */
            Proxy() IPL_NOEXCEPT;
            /*! copy ctor */
            Proxy( const Proxy& other ) IPL_NOEXCEPT;
            /*! copy assignment */
            Proxy& operator=( const Proxy& other) IPL_NOEXCEPT;
            ~Proxy();
            /*! equality */
            bool operator==(const Proxy& other) const IPL_NOEXCEPT;
            bool operator!=(const Proxy& other) const IPL_NOEXCEPT {
                return !operator==(other);
            }

#if __cplusplus>=201103L // C++11, we need to keep this for our old swig for the time being
                         // all C++ compilers in HCP3 must be at least C++14
#if !defined(__clang__) || (__clang_major__ < 9)
            // any compiler not clang 9 or higher
            /*! move ctor */
            Proxy(Proxy&&) IPL_NOEXCEPT = default;
            /*! move assignment */
            Proxy& operator=(Proxy&& other) IPL_NOEXCEPT = default;
#else
            // clang 9 and up: those two can't be noexcept (the default calculated move
            // ctor and move assignment aren't. Trying to use noexcept for these gives this error
            // "error: exception specification of explicitly defaulted move constructor does not
            // match the calculated one" in arm clang 9 [Android Q toolchain])
            // TODO: unterstand the details
            /*! move ctor */
            Proxy(Proxy&&) = default;
            /*! move assignment */
            Proxy& operator=(Proxy&& other) = default;
#endif // clang
#endif // cplusplus

            typedef comm::IdentityArgs IdentityArgs;
            typedef util::serializer::SerializerTag SerializerTag;
            typedef util::UInt32Tag UInt32Tag;

        protected:
            /**
            \brief  constructor without reply-interface

            used to create a proxy to an interface without reply-interface defintion. This
                    method only creates the proxy, but does not perform the connect()
            \param  iargs instance ID, interface key, interface name
            \param  l is an instance to a listener which reports connection states to the interface.
                    this parameter is optional
            \errorindicator
                    none
            **/
            Proxy(const IdentityArgs& iargs
                     ,FactoryGetterFct factory_getter
                     ,const InterfaceStyle interfaceStyle
                     ,LifecycleListener* l=nullptr);
            Proxy(const IdentityArgs& iargs
                   , FactoryGetterFct factory_getter
                   ,const comm::ActiveObjectFactoryPtr& aof
                   ,const InterfaceStyle interfaceStyle
                   ,LifecycleListener* l=nullptr
                );


            /**
            \brief  constructor with reply-interface

            used to create a proxy to an interface with reply-interface defintion. This
                    method only creates the proxy, but does not perform the connect()
            \param  iargs instance ID, interface key, interface name
            \param  l is an instance to a listener which reports connection states to the interface.
                    this parameter is optional
            \errorindicator
                    none
            **/
            Proxy(const IdentityArgs& iargs
                 , FactoryGetterFct factory_getter
                 ,const ServiceRegistration& replyReg
                 ,const InterfaceStyle interfaceStyle
                 ,LifecycleListener* l=nullptr );

        public:

            /**
            \brief  request the proxy to connect to its service instance

                If the service instance is already registered the connection is established.
                Otherwise the broker is requested to inform this instance, when
                the service instance appears.

                if the proxy is already connected or has died, nothing is done.

                If the agent can not fullfill the request, true is returned and an error raised, false otherwise.

                Calling connect() will also trigger the reception of lifecycle events if a LifecycleListener
                for this instance exists and subsequently the invocation of dead() and alive() callbacks.
            \return
                false on success, true on error
                Missing service is not reason for an error but success(false) is returned.
            \errors
                comm:Error with ID NO_FACTORY_FOR_INTERFACE, ID_POOL_EXHAUSTED, OBJECT_IS_DEAD
            \errorindicator
                via return value
            */
            bool connect() IPL_NOEXCEPT;

            /**
            \brief  request the proxy to connect to its service instance using the serializer passed in \a serializer_tag

                This starts establishing a session with the service.

                If connect had been called before this call has no effect.

                In case of an error true is returned. Otherwise the proxy will eventually
                go alive if its service is registered.

                Calling connect() will trigger the reception of lifecycle events if a LifecycleListener
                for this instance exists and subsequently the invocation of dead() and alive() callbacks.
            \param serializer_tag tag of the serializer to be used in the session. If this serializer
                is not available, connect will return true. Session establishment can fail if
                the serializer passed her is available in this proces, but not in the process hosting
                the service. In that case connect will return false, but the proxy will eventually go dead.

            \return
                false on success, true on error
                Missing service is not reason for an error but success(false) is returned.
            \errors
                comm:Error with ID NO_FACTORY_FOR_INTERFACE, ID_POOL_EXHAUSTED, OBJECT_IS_DEAD
            \errorindicator
                via return value
            */
            bool connect(SerializerTag serializer_tag) IPL_NOEXCEPT;

            /**
            \brief  Disconnects the proxy from its service.

                The proxy closes the session with its service and is invalidated.
                It can't be reused afterwards.
                No further LifecycleListener callbacks for this proxy are called.
                Calling disconnect() does not cause the invocation of the dead() callback of a
                LifecycleListener for this proxy.
                This call is processed asynchronously and may return before all of the related
                actions are processed.
                Thus it is not safe to delete objects that are passed to the proxy
                in its constructor (e.g. LifecycleListener and reply service).
                Because of the above it is possible that calls to a reply service passed
                to this proxy will be dispatched after disconnect() had been called.
            \errors
                none
            **/
            void disconnect() IPL_NOEXCEPT;

            /**
            \brief  Disconnects the proxy from its service.

                This closes the proxy - service session.
                The passed callback function will be called after
                <ul>
                <li>The comm agent released all references to objects passed in the constructor
                (e.g. LifecycleListener, reply service).</li>
                <li>No call is currently active in the reply service (if there is one).</li>
                <li>No LifecycleListener callback is currently active.</li>
                </ul>
                It is safe to delete LifecycleListener and reply service objects that were passed
                to the constructor in the passed function.
                The callback will only be called if false is returned.
                The callback is called from the same thread that would call LifecycleListener's
                dead() and alive().
            \param    callback notification callback function.
            \param  context a pointer that is returned in the notification callback.
            \return
                false on success, meaning the proxy is being disconnected.
                true in case of errors:
                <ul>
                <li>the proxy is not valid
                <li>a disconnect() or disconnectAndNotify had already been called
                <li>the callback parameter is NULL
                </ul>
            \errors
                PROXY_IS_INVALID when called on a proxy that is not valid.
                \see valid()
                COMM_ERROR when the proxy had already been disconnected or the
                callback is NULL
            **/
            bool disconnectAndNotify(ProxyReleasedFct callback, void* context) IPL_NOEXCEPT;

            /**
            \brief  check whether the proxy is alive or not.

                A proxy is alive, when it successfully connected to its service.

            \return true -> ALIVE
            \return false -> NOT ALIVE
            **/
            bool isAlive() const override;

            /**
            \brief  check whether the proxy is DEAD or not.

                A proxy is dead after it disconnected from its service, the service unregistered
                or disappeared (e.g. due to connection loss) or if connecting to the service failed.

            \return true -> DEAD
            \return false -> NOT DEAD
            \errorindicator
                    none
            **/
            bool isDead() const override;

            /**
            \brief  wait until the proxy's state changes to DEAD

                The call is suspened by waiting on a condition. It wakes up, when the broker
                tells, that the related interface has disappeared and the proxy is in state DEAD
            \return
                true on error, false otherwise
            \errorindicator
                via return code.
            **/
            void waitUntilDead() override;

            /**
            \brief  wait until the proxy's state changes to ALIVE

                The call is suspened by waiting on a condition. It wakes up when either the service instance associated with this
                proxy is ready to receive calls or an error occurred and the proxy transitioned to state DEAD.
            \return true on error, false otherwise
            \errors comm:Error with ID OBJECT_ISDEAD.
            \errorindicator
                via return code.
            */
            bool waitUntilAlive() override;

            /**
            \brief  request the instance ID the proxy is related to

                It returns a reference to the instance ID, which was given to the constructor
            \return reference to the instanceID
            \errorindicator
                    none
            **/
            const InstanceID& getInstanceID() const IPL_NOEXCEPT;

            /**
            \brief compare identity with Lifecycle*, use in alive/dead callbacks
            **/
            bool operator==(const Lifecycle* other) const IPL_NOEXCEPT;

            bool operator!=(const Lifecycle* other) const IPL_NOEXCEPT {
                return ! operator==(other);
            }

            const InterfaceKey&    getInterfaceKey() const IPL_NOEXCEPT;


            const ServiceRegistration& getReplySvcRegistration() const IPL_NOEXCEPT;

            const ProxyID getPID() const IPL_NOEXCEPT;
            const StubID getSID() const IPL_NOEXCEPT;

            bool hasReplyService() const IPL_NOEXCEPT {
                return valid()
                    && getReplySvcRegistration().valid()
                    && !getReplySvcRegistration().getInstanceID().isInvalid()
                    && getReplySvcRegistration().getService()
                    ;
            }

            /* Returns the agent id of the process this proxies' service runs in */
            AgentID getServiceLocation() const IPL_NOEXCEPT;
            /* Returns the name of the process this proxies' service runs in */
            ipl::string getServiceProcessName() const IPL_NOEXCEPT;
            /* Returns the epoch of the process this proxies' service runs in */
            AgentEpoch getPeerEpoch() const IPL_NOEXCEPT;

            bool valid() const IPL_NOEXCEPT;

            typedef std::shared_ptr<ProxyState> StatePtr;
            explicit Proxy(const StatePtr& s);

            // Returns the serializer (tag) used in the proxy-service session.
            // The return value reflects the serializer used in the session only
            // after the proxy went alive
            UInt32Tag getSerializerTag() const IPL_NOEXCEPT;

            /*! Internal. Retrieve serializer tag from proxy state */
            static UInt32Tag getSerializerTag(const ProxyState* state) IPL_NOEXCEPT;

            /** Sets the ErrorHandler for this proxy instance.
             *
             * Setting a new ErrorHandler replaces a previously set one.
             *
             * Passing an empty ErrorHandlerPtr removes the ErrorHandler from this proxy.
             *
             * Calling setErrorHandler on a non-valid proxy is silently ignored. \see
             * comm::Proxy::valid()
             */
            void setErrorHandler(const comm::ErrorHandlerPtr& eh);

            /** Retrieves the ErrorHandler from this proxy instance.
             *
             *  May return an empty ErrorHandlerPtr (e.g. if no ErrorHandler was set previously or
             *  if the proxy is not valid). \see comm::Proxy::valid()
             */
            const comm::ErrorHandlerPtr& getErrorHandler() const;

            /** Retrieves the ServiceVersion of the service.
             *
             *  The service's version is only available after the proxy went alive.
             *  The value in status indicates if the information is available.
             */
            struct Version {
                ServiceVersion          version;
                ServiceVersionStatus    status{ServiceVersionStatus::StatusNotAlive};
                bool isValid() const { return status == ServiceVersionStatus::StatusOK; }
            };
            Version getServiceVersion() const;

        protected:
            /**
            \brief  request the underlying proxy-instance
            \return the proxy instance
            \errorindicator
                    none
            **/
            void* getImpl() const IPL_NOEXCEPT;

        private:
            StatePtr                            m_state;

            const StatePtr&     state() const { return m_state; }
            StatePtr&           state(bool) { return m_state; }

            Lifecycle::State getState() const;

            ServiceRegistration& getReplySvcRegistration(bool dummy);

            bool notifyListener(const ServiceEvent& e) const;

            friend class ::MockAgent;
            friend class ConnectProxyJob;
            friend class ConnectProxyJobPhase1;
            friend class ConnectProxyJobPhase2;
            friend class ConnectProxyJobPhase3;
            friend class DisconnectProxyJob;
            friend class Core;
            friend class Model;
            friend class ServiceInfo;
            friend class ProxyCompletionEvent;
            friend class ProxyLifecycleEvent;
            friend class Broker;
            friend class ServiceNodeInfo;
            friend class StatusTrace;
            friend class AgentImpl;
            friend class CallEventImpl;
            friend class protocol::V7MessageSender;
            friend class StubBase;
    };

}
#endif // COMM_PROXY_HXX
// vim: ts=4 sw=4:
