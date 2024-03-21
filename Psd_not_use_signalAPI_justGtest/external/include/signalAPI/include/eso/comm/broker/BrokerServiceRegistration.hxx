/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template ServiceRegistration_hxx.tmpl
*/
#ifndef COMM_BROKER_BROKER_SERVICEREGISTRATION_HXX
#define COMM_BROKER_BROKER_SERVICEREGISTRATION_HXX

#include <comm/commidltypes.hxx>        // used for PROXY_EXPORT macro
#include <comm/ServiceRegistration.hxx>

#include <string>

namespace comm
{
namespace broker
{

    class BrokerS;

    /**
        \brief The service registration instance for the broker::Broker interface.
    */
    class BrokerServiceRegistration  : public comm::ServiceRegistration
    {
    public:
        /**
        \brief constructor with type and instance counter
        \param    _instID is the id, which identifies the interface realistion at the broker
        \param    svc is a refenrence to the interface implementation object itself
        \param    l is a pointer to a listener for the lifecycle of the registration. This parameter is optinal. If
                it's not given, no listener is connected
        */
        BrokerServiceRegistration (const ::comm::InstanceID& _instID, BrokerS& svc, ::comm::LifecycleListener* l=nullptr)
        :ServiceRegistration(comm::IdentityArgs(_instID, getIKey(), getIName())
            ,&svc
            ,comm::CIPtrStyle
            ,serviceInitFactory
            ,l)
        {
        }

        /**
        \brief constructor with type and instance counter
        \param    _instID is the id, which identifies the interface realistion at the broker
        \param    svc is a reference to the interface implementation object itself
        \param    l is a pointer to a listener for the lifecycle of the registration.
        */
        BrokerServiceRegistration (const ::comm::InstanceID& _instID, BrokerS& svc, ::comm::LifecycleListener& l)
        :ServiceRegistration(comm::IdentityArgs(_instID, getIKey(), getIName())
            ,&svc
            ,comm::CIPtrStyle
            ,serviceInitFactory
            ,l)
        {
        }

        /**
        \brief constructor with type and instance counter
        \param    _instID is the id, which identifies the interface realistion at the broker
        \param    svc is a pointer to the interface implementation object itself
        \param    l is a pointer to a listener for the lifecycle of the registration. This parameter is optinal. If
                it's not given, no listener is connected
        */
        BrokerServiceRegistration (const ::comm::InstanceID& _instID, BrokerS* svc, ::comm::LifecycleListener* l=nullptr)
        :ServiceRegistration(comm::IdentityArgs(_instID, getIKey(), getIName())
            ,svc
            ,comm::CIPtrStyle
            ,serviceInitFactory
            ,l)
        {
        }

        /**
        \brief constructor with type and instance counter, lifecycle listener and ActiveObjectFactory
        \param    _instID is the id, which identifies the interface realistion at the broker
        \param    svc is a pointer to the interface implementation object itself
        \param    l is a pointer to a listener for the lifecycle of the registration.
        \param  p a factory for ActiveObjects. This allows to control the threads that call into the service.
        */
        BrokerServiceRegistration (const ::comm::InstanceID& _instID, BrokerS* svc, ::comm::LifecycleListener* l, const comm::ActiveObjectFactoryPtr& p)
        :ServiceRegistration(comm::IdentityArgs(_instID, getIKey(), getIName())
            ,svc
            ,comm::CIPtrStyle
            ,serviceInitFactory
            ,l
            ,p)
        {
        }

        /**
        \brief constructor with type and instance counter and ActiveObjectFactory
        \param    _instID is the id, which identifies the interface realistion at the broker
        \param    svc is a pointer to the interface implementation object itself
        \param  p a factory for ActiveObjects. This allows to control the threads that call into the service.
        */
        BrokerServiceRegistration (const ::comm::InstanceID& _instID, BrokerS* svc, const comm::ActiveObjectFactoryPtr& p)
        :ServiceRegistration(comm::IdentityArgs(_instID, getIKey(), getIName())
            ,svc
            ,comm::CIPtrStyle
            ,serviceInitFactory
            ,nullptr
            ,p)
        {
        }

        /**
        \brief constructor with type and instance counter
        \param    _instID is the id, which identifies the interface realistion at the broker
        \param    svc is a pointer to the interface implementation object itself
        \param    l is a pointer to a listener for the lifecycle of the registration.
        */
        BrokerServiceRegistration (const ::comm::InstanceID& _instID, BrokerS* svc,  ::comm::LifecycleListener& l)
        :ServiceRegistration(comm::IdentityArgs(_instID, getIKey(), getIName())
            ,svc
            ,comm::CIPtrStyle
            ,serviceInitFactory
            ,l)
        {
        }

        // default ctor
        BrokerServiceRegistration() {}

        static const char* getInterfaceName() { return getIName().c_str(); }

    private:
        static const comm::InterfaceKey& getIKey() {
            static comm::InterfaceKey ikey(0x00040000, 0x0001, 0x6000, 0x0000, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00);
            return ikey;
        }

        static const std::string& getIName() {
            static const std::string iname{"comm.broker.Broker"};
            return iname;
        }

        // proxy/stub factory init for the service side
        PROXY_EXPORT static const ProxyStubFactory* serviceInitFactory();

    };

}//namespace comm
}//namespace broker
#endif// COMM_BROKER_BROKER_SERVICEREGISTRATION_HXX
