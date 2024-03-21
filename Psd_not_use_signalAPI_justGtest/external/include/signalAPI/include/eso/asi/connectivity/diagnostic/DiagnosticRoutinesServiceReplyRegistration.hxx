/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template ServiceReplyRegistration_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICROUTINES_SERVICEREPLYREGISTRATION_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICROUTINES_SERVICEREPLYREGISTRATION_HXX

#include <comm/commidltypes.hxx>        // used for PROXY_EXPORT macro
#include <comm/ServiceRegistration.hxx>

#include <string>

namespace asi
{
namespace connectivity
{
namespace diagnostic
{


    class DiagnosticRoutinesReply;
    /**
        \brief The service registration instance for the diagnostic::DiagnosticRoutinesReply interface.
    */
    class DiagnosticRoutinesServiceReplyRegistration  : public comm::ServiceRegistration
    {
    public:
        /**
        \brief constructor with type and instance counter
        \param    _instID is the id, which identifies the interface realistion at the broker
        \param    svc is a pointer to the interface implementation object itself
        \param    l is a pointer to a listener for the lifecycle of the registration. This parameter is optinal. If
                it's not given, no listener is connected
        */
        DiagnosticRoutinesServiceReplyRegistration (const ::comm::InstanceID& _instID, DiagnosticRoutinesReply* svc, ::comm::LifecycleListener* l=nullptr)
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
        DiagnosticRoutinesServiceReplyRegistration (const ::comm::InstanceID& _instID, DiagnosticRoutinesReply* svc, ::comm::LifecycleListener* l, const comm::ActiveObjectFactoryPtr& p)
        :ServiceRegistration(comm::IdentityArgs(_instID, getInterfaceKey(), getIName())
            ,svc
            ,comm::CIPtrStyle
            ,serviceInitFactory
            ,l
            ,p)
        {
        }

        static const comm::InterfaceKey& getInterfaceKey() {
            static comm::InterfaceKey ikey(0x00020008, 0x0000, 0x6000, 0x0000, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00);
            return ikey;
        }

        static const std::string& getIName() {
            static const std::string iname{"asi.connectivity.diagnostic.DiagnosticRoutinesReply"};
            return iname;
        }

        // proxy/stub factory init for the service side
        PROXY_EXPORT static const ProxyStubFactory* serviceInitFactory();

    };

}//namespace asi
}//namespace connectivity
}//namespace diagnostic
#endif// ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICROUTINES_SERVICEREPLYREGISTRATION_HXX
