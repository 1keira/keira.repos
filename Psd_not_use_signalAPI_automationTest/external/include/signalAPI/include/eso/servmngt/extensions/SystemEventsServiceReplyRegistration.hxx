/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template ServiceReplyRegistration_hxx.tmpl
*/
#ifndef SERVMNGT_EXTENSIONS_SYSTEMEVENTS_SERVICEREPLYREGISTRATION_HXX
#define SERVMNGT_EXTENSIONS_SYSTEMEVENTS_SERVICEREPLYREGISTRATION_HXX

#include <comm/commidltypes.hxx>        // used for PROXY_EXPORT macro
#include <comm/ServiceRegistration.hxx>

#include <string>

namespace servmngt
{
namespace extensions
{


    class SystemEventsReply;
    /**
        \brief The service registration instance for the extensions::SystemEventsReply interface.
    */
    class SystemEventsServiceReplyRegistration  : public comm::ServiceRegistration
    {
    public:
        /**
        \brief constructor with type and instance counter
        \param    _instID is the id, which identifies the interface realistion at the broker
        \param    svc is a pointer to the interface implementation object itself
        \param    l is a pointer to a listener for the lifecycle of the registration. This parameter is optinal. If
                it's not given, no listener is connected
        */
        SystemEventsServiceReplyRegistration (const ::comm::InstanceID& _instID, SystemEventsReply* svc, ::comm::LifecycleListener* l=nullptr)
        :ServiceRegistration(comm::IdentityArgs(_instID, getInterfaceKey(), getIName())
            ,svc
            ,comm::CIPtrStyle
            ,serviceInitFactory
            ,l)
        {
        }

        /**
        \brief constructor with type and instance number and ActiveObjectFactory
        \param    _instID is the id, which identifies the interface realistion at the broker
        \param    svc is a pointer to the interface implementation object itself
        \param    l is a pointer to a listener for the lifecycle of the registration.
        \param  p a factory for ActiveObjects. This allows to control the threads that call into the service.
        */
        SystemEventsServiceReplyRegistration (const ::comm::InstanceID& _instID, SystemEventsReply* svc, ::comm::LifecycleListener* l, const comm::ActiveObjectFactoryPtr& p)
        :ServiceRegistration(comm::IdentityArgs(_instID, getInterfaceKey(), getIName())
            ,svc
            ,comm::CIPtrStyle
            ,serviceInitFactory
            ,l
            ,p)
        {
        }

        static const comm::InterfaceKey& getInterfaceKey() {
            static comm::InterfaceKey ikey(0x00030000, 0x0001, 0x6000, 0x0000, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00);
            return ikey;
        }

        static const std::string& getIName() {
            static const std::string iname{"servmngt.extensions.SystemEventsReply"};
            return iname;
        }

        // proxy/stub factory init for the service side
        PROXY_EXPORT static const ProxyStubFactory* serviceInitFactory();

    };

}//namespace servmngt
}//namespace extensions
#endif// SERVMNGT_EXTENSIONS_SYSTEMEVENTS_SERVICEREPLYREGISTRATION_HXX
