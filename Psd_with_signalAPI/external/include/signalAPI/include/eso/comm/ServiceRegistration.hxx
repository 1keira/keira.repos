/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef COMM_SERVICE_REGISTRATION_HXX
#define COMM_SERVICE_REGISTRATION_HXX

#include <ipl_config.h>

#include <memory>

#include <util/serializer/SerializerTag.hxx>
#include <comm/comm_dso.h>
#include <comm/util.hxx>
#include <comm/commtypes.hxx>
#include <comm/Identity.hxx>
#include <comm/Lifecycle.hxx>
#include <comm/IActiveObjectFactory.hxx>
#include <comm/ProxyStubFactory.hxx>

// unit test support
class MockAgent;

namespace comm {

    class DefaultActiveObjectFactory;
    class ConnectionHandler;
    class AgentImpl;
    class Broker1Connector;
    class Model;
    class Core;
    class UnregisterServiceJob;
    class ServiceInfo;
    class ServiceRegistration;
    class ServiceLifecycleEvent;
    struct ServiceState;
    class CallEventImpl;
    class Proxy;

    /** callback for 'service released' */
    typedef void (*ServiceReleasedFct)(void* ctx, const comm::ServiceRegistration& service_reg);

    /*!
    \brief    base class for service registrations.

    - contains methods for registering and unregistering an realised interface at the broker
    - offers methods for lifecycle supervision

    */
    class COMM_EXPORT ServiceRegistration : public Lifecycle {
        public:
            typedef comm::IdentityArgs IdentityArgs;
            typedef std::shared_ptr<ServiceState> StatePtr;

        protected:
            /**
             \brief constructor with type and instance counter
            \param    iargs contains the identity related properies. Most notably the instance id, which identifies a specific instance of a service
            \param    svc is a pointer to the interface implementation object itself
            \param    l is a pointer to a listener for the lifecycle of the registration. This parameter is optinal. If
                    it's not given, no listener is connected
            */
            ServiceRegistration (const IdentityArgs& iargs, void* svc
                                ,const InterfaceStyle style
                                ,FactoryGetterFct factory_getter
                                ,LifecycleListener* l=nullptr
                                ,ActiveObjectFactoryPtr p=nullptr);
            /**
             \brief constructor with type and instance counter
            \param    iargs contains the identity related properies. Most notably the instance id, which identifies a specific instance of a service
            \param    svc is a pointer to the interface implementation object itself
            \param    l is a pointer to a listener for the lifecycle of the registration.
            */
            ServiceRegistration (const IdentityArgs& iargs, void* svc
                                ,const InterfaceStyle style
                                ,FactoryGetterFct factory_getter
                                ,LifecycleListener& l);

        public:
            /*! empty registration. Such a registration can never be used */
            ServiceRegistration ();
            /*! copy ctor */
            ServiceRegistration( const ServiceRegistration& other );
            /*! from state */
            explicit ServiceRegistration( const ServiceRegistration::StatePtr& s );
            /*! assignment */
            ServiceRegistration& operator=( const ServiceRegistration& other);

            /*! Destructor. It's unregisters the interface implicitely */
            ~ServiceRegistration () override;

            /*!
            \brief    Unregisters a service.

            The service instance is removed from the system. Everyone who is
                    connected to it is informed that the service isn't available
                    any more. No more calls are dispatched to the service implementation.
                    It is possible though that a call is being dispatched while this call is
                    executed. Therefore it is not safe to delete the service implementation and/or
                    lifecycle listener passed in the constructor after this call returns.
                    \see unregisterAndNotify.
            */
            void unregisterService () const;

            /**
            \brief    Unregisters a service.

            The service instance is removed from the set of available services.
                All proxies that are connected to this service go dead.
                No more calls are dispatched to this service.
                The passed function will be called after
                <ul>
                <li>The comm agent released all references to objects passed in the constructor
                (e.g. LifecycleListener, service implementation).</li>
                <li>No call is currently active in the service implementation.</li>
                <li>No LifecycleListener callback is currently active.</li>
                </ul>
                It is safe to delete LifecycleListener and service implementation objects
                that were passed to the constructor in the callback.
                The callback will only be called if false is returned.
                The callback is called from the thread associated with this service.
            \param    callback notification callback.
            \param    context a pointer that is returned in the notification callback.
            \return
                false on success, meaning the service is being unregistered.
                true in case of errors:
                <ul>
                <li>the service registration is not valid
                <li>an unregisterService() or unregisterAndNotify had already been called.
                <li>the callback is NULL.
                </ul>
            \errors
                COMM_ERROR when the service had already been unregistered, this
                ServiceRegistration is not valid or the callback is NULL.
                \see valid()
            **/

            bool unregisterAndNotify(ServiceReleasedFct callback, void* context);

            /*!
            \brief    register the service at the broker.

            The service instance becomes visible to clients. Clients that track this instance are informed
                    that it is now available (their lifecycle state goes to ALIVE).
                    Messages can now be delivered to the service.

                    If this instance had already been registered nothing is done.

                    If another registeration with the same instanceID is already registered, the registration
                    is not performed.
            \return
                    true on error, false otherwise
            \errors comm::Error with ID OBJECT_IS_DEAD
            \errorindicator via return code
            */
            bool registerService();


            /**
            \brief    check whether the registration is ALIVE or not.

            A registration is alive, when register() was called

            \return    true -> ALIVE
            \return    false -> NOT ALIVE
            \exception    nothrow
            **/
            bool isAlive() const override;

            /**
            \brief    check whether the registration is DEAD or not.

            A registration is dead, when unregister() was called

            \return    true -> DEAD
            \return    false -> NOT DEAD
            \exception    nothrow
            **/
            bool isDead() const override;

            /**
            \brief    wait until the registration's state changes to DEAD

            The call is suspened by waiting on a condition. It wakes up, the state has changed
            \exception    nothrow
            **/
            void waitUntilDead() override;

            /**
            \brief    wait until the registration's state changes to ALIVE

            The call is suspened by waiting on a condition. Teh call returns either if the state changed to ALIVE
                or if it cahged to DEAD. In case the state is DEAD, true is returned.
            \return
                true on error, false otherwise
            \errors
                comm::Error
            **/
            bool waitUntilAlive() override;

            /**
            \brief    Pins the serialization this Service can use.

            \return true if the tag has an invalid value.
            **/
            bool setSerializerTag(util::serializer::SerializerTag tag) IPL_NOEXCEPT;

            const void* getService() const;

            bool valid() const;

            const InstanceID& getInstanceID() const;

            bool operator==(const Lifecycle* other) const;
            bool operator!=(const Lifecycle* other) const {
                return ! operator==(other);
            }

            const InterfaceKey& getInterfaceKey() const;
            const char* getInterfaceName() const;

            /*!
            \brief Marks service as discoverable or undiscoverable

            Services marked as not discoverable will not be puplished to broker. Other
            processes will not be able to discover them.

            The default for all services is to be discoverable.
            */
            void setDiscoverable(bool discoverable);

            bool isDiscoverable() const;
        private:
            StatePtr                            m_state;
            const StatePtr& state() const { return m_state; }

            InstanceID& getInstanceID(bool);
            ActiveObjectFactoryPtr& getActiveObjectFactory() const;
            bool notifyListener(const ServiceEvent& e) const;

            friend class ConnectionHandler;
            friend class AgentImpl;
            friend class DefaultActiveObjectFactory;
            friend class Model;
            friend class Core;
            friend class ServiceInfo;
            friend class UnregisterServiceJob;
            friend class ServiceLifecycleEvent;
            friend class ::MockAgent;
            friend class CallEventImpl;
            friend class Proxy;
            friend class GenericServiceBase;
            friend class Broker1Connector;
    };
}

#endif // COMM_SERVICE_REGISTRATION_HXX
// vim: ts=4 sw=4:


