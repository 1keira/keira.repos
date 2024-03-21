/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Proxy_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICVTTMEASUREMENTS_PROXY_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICVTTMEASUREMENTS_PROXY_HXX

#include <comm/ProxyStubFactory.hxx>
#include <comm/Proxy.hxx>
#include <comm/commidltypes.hxx>        // used for PROXY_EXPORT macro
#include <asi/connectivity/diagnostic/StructVttStatus.hxx>
#include <asi/connectivity/diagnostic/Definitions.hxx>
#include <asi/connectivity/diagnostic/DiagnosticVttMeasurementsC.hxx>
#include <asi/connectivity/diagnostic/DiagnosticVttMeasurementsReply.hxx>
#include <asi/connectivity/diagnostic/DiagnosticVttMeasurementsServiceReplyRegistration.hxx>

#include <string>

namespace asi
{
namespace connectivity
{
namespace diagnostic
{

    /**
        \brief A proxy for services that implement the diagnostic::DiagnosticVttMeasurements interface.
    */
    class DiagnosticVttMeasurementsProxy  : public comm::Proxy
    {
    public:
        // ctor with listener pointer and no reply interface
        DiagnosticVttMeasurementsProxy(const comm::InstanceID& _id, comm::LifecycleListener* l=nullptr )
        : Proxy(comm::Proxy::IdentityArgs(_id, getIKey(), getIName())
                ,clientInitFactory
                ,comm::CIPtrStyle, l)
        {
        }

        // ctor with listener pointer and no reply interface
        // explicit so we don't magically construct proxies from integers
        explicit DiagnosticVttMeasurementsProxy(const uint32_t inst_cnt, comm::LifecycleListener* l=nullptr )
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICVTTMEASUREMENTS_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
                ,comm::CIPtrStyle
                ,l)
        {
        }

        // ctor with listener reference and no reply interface
        DiagnosticVttMeasurementsProxy(const comm::InstanceID& id, comm::LifecycleListener& l )
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
                ,comm::CIPtrStyle, &l)
        {
        }

        // ctor with listener pointer and no reply interface
        DiagnosticVttMeasurementsProxy(const uint32_t inst_cnt, comm::LifecycleListener& l )
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICVTTMEASUREMENTS_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
                ,comm::CIPtrStyle
                ,&l)
        {
        }

        // constructors  with a user passed object factory to receive notifications
        // ctor with listener pointer and no reply interface
        // explicit so we don't magically construct proxies from integers
        explicit DiagnosticVttMeasurementsProxy(const uint32_t inst_cnt
                                        ,const comm::ActiveObjectFactoryPtr& aof
                                        ,comm::LifecycleListener* l=nullptr )
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICVTTMEASUREMENTS_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
                ,aof
                ,comm::CIPtrStyle
                ,l
                )
        {
        }

        // ctor with listener pointer and no reply interface
        DiagnosticVttMeasurementsProxy(const uint32_t inst_cnt
                                ,const comm::ActiveObjectFactoryPtr& aof
                                ,comm::LifecycleListener& l )
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICVTTMEASUREMENTS_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
                ,aof
                ,comm::CIPtrStyle
                ,&l
                )
        {
        }
        // ctor with reply instance and listener pointers
        DiagnosticVttMeasurementsProxy(const comm::InstanceID& id, DiagnosticVttMeasurementsReply* r, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
                ,DiagnosticVttMeasurementsServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICVTTMEASUREMENTS_REPLY))
                    ,r
                    ,nullptr
                    )
                ,comm::CIPtrStyle
                ,l
                )
        {
        }

        // ctor with reply instance and listener pointers and ActiveObjectFactory
        DiagnosticVttMeasurementsProxy(const comm::InstanceID& id, DiagnosticVttMeasurementsReply* r, comm::ActiveObjectFactoryPtr aof, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
                ,DiagnosticVttMeasurementsServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICVTTMEASUREMENTS_REPLY))
                    ,r
                    ,nullptr
                    ,aof
                    )
                ,comm::CIPtrStyle
                ,l
                )
        {
        }

        // ctor with reply instance and listener pointers
        DiagnosticVttMeasurementsProxy(const uint32_t inst_cnt, DiagnosticVttMeasurementsReply* r, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICVTTMEASUREMENTS_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
                ,DiagnosticVttMeasurementsServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICVTTMEASUREMENTS_REPLY))
                    ,r
                    ,nullptr
                    )
                ,comm::CIPtrStyle
                ,l
                )
        {
        }

        // ctor with reply instance and listener pointers and ActiveObjectFactory
        DiagnosticVttMeasurementsProxy(const uint32_t inst_cnt, DiagnosticVttMeasurementsReply* r, comm::ActiveObjectFactoryPtr aof, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICVTTMEASUREMENTS_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
            ,DiagnosticVttMeasurementsServiceReplyRegistration(
                comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICVTTMEASUREMENTS_REPLY))
                ,r
                ,nullptr
                ,aof
                )
            ,comm::CIPtrStyle
            ,l
            )
        {
        }

        // ctor with reply instance reference and listener pointer
        DiagnosticVttMeasurementsProxy(const comm::InstanceID& id, DiagnosticVttMeasurementsReply& r, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
                ,DiagnosticVttMeasurementsServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICVTTMEASUREMENTS_REPLY))
                    ,&r
                    ,nullptr
                    )
            ,comm::CIPtrStyle
            ,l
            )
        {
        }

        // ctor with reply instance reference and listener pointer and ActiveObjectFactory
        DiagnosticVttMeasurementsProxy(const comm::InstanceID& id, DiagnosticVttMeasurementsReply& r, comm::ActiveObjectFactoryPtr aof, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
            ,DiagnosticVttMeasurementsServiceReplyRegistration(
                comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICVTTMEASUREMENTS_REPLY))
                ,&r
                ,nullptr
                ,aof
                )
            ,comm::CIPtrStyle
            ,l
            )
        {
        }

        // ctor with reply instance reference and listener pointer
        DiagnosticVttMeasurementsProxy(const uint32_t inst_cnt, DiagnosticVttMeasurementsReply& r, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICVTTMEASUREMENTS_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
            ,DiagnosticVttMeasurementsServiceReplyRegistration(
                comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICVTTMEASUREMENTS_REPLY))
                ,&r
                ,nullptr
                )
            ,comm::CIPtrStyle
            ,l
            )
        {
        }

        // ctor with reply instance reference and listener pointer and ActiveObjectFactory
        DiagnosticVttMeasurementsProxy(const uint32_t inst_cnt, DiagnosticVttMeasurementsReply& r, comm::ActiveObjectFactoryPtr aof, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICVTTMEASUREMENTS_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
            ,DiagnosticVttMeasurementsServiceReplyRegistration(
                comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICVTTMEASUREMENTS_REPLY))
                ,&r
                ,nullptr
                ,aof
                )
            ,comm::CIPtrStyle
            ,l
            )
        {
        }

        // ctor with reply instance and listener reference
        DiagnosticVttMeasurementsProxy(const comm::InstanceID& id, DiagnosticVttMeasurementsReply& r, comm::LifecycleListener& l)
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
                ,DiagnosticVttMeasurementsServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICVTTMEASUREMENTS_REPLY))
                    ,&r
                    ,nullptr
                    )
            ,comm::CIPtrStyle
            ,&l
            )
        {
        }

        // ctor with reply instance and listener reference and ActiveObjectFactory
        DiagnosticVttMeasurementsProxy(const comm::InstanceID& id, DiagnosticVttMeasurementsReply& r, comm::ActiveObjectFactoryPtr aof, comm::LifecycleListener& l)
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
                ,DiagnosticVttMeasurementsServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICVTTMEASUREMENTS_REPLY))
                    ,&r
                    ,nullptr
                    ,aof
                    )
            ,comm::CIPtrStyle
            ,&l
            )
        {
        }

        // ctor with reply instance and listener reference
        DiagnosticVttMeasurementsProxy(const uint32_t inst_cnt, DiagnosticVttMeasurementsReply& r, comm::LifecycleListener& l)
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICVTTMEASUREMENTS_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
                ,DiagnosticVttMeasurementsServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICVTTMEASUREMENTS_REPLY))
                    ,&r
                    ,nullptr
                    )
            ,comm::CIPtrStyle
            ,&l
            )
        {
        }

        // ctor with reply instance and listener reference and ActiveObjectFactory
        DiagnosticVttMeasurementsProxy(const uint32_t inst_cnt, DiagnosticVttMeasurementsReply& r, comm::ActiveObjectFactoryPtr aof, comm::LifecycleListener& l)
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICVTTMEASUREMENTS_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
                ,DiagnosticVttMeasurementsServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICVTTMEASUREMENTS_REPLY))
                    ,&r
                    ,nullptr
                    ,aof
                    )
            ,comm::CIPtrStyle
            ,&l
            )
        {
        }
        // default ctor
        DiagnosticVttMeasurementsProxy() {}
        // DiagnosticVttMeasurementsProxy is copy-assignable, default copy-ctor and assignment operator are fine
        // DiagnosticVttMeasurementsProxy is move-assignable when using C++11 or higher

        DiagnosticVttMeasurementsC& operator*() const
        {
            return *operator->();
        }

        DiagnosticVttMeasurementsC* operator->() const
        {
            return reinterpret_cast<DiagnosticVttMeasurementsC*>(getImpl());
        }

    private:
        static const comm::InterfaceKey& getIKey() {
            static comm::InterfaceKey ikey(0x00020008, 0x0000, 0x6000, 0x0000, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00);
            return ikey;
        }
        static const std::string& getIName() {
            static const std::string iname{"asi.connectivity.diagnostic.DiagnosticVttMeasurements"};
            return iname;
        }
        static const comm::InterfaceKey& getRIKey() {
            // semver is not different in request/reply direction
            return DiagnosticVttMeasurementsProxy::getIKey();
        }

        // proxy/stub factory init for the client side
        PROXY_EXPORT static const ProxyStubFactory* clientInitFactory();

    };

}//namespace asi
}//namespace connectivity
}//namespace diagnostic
#endif// ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICVTTMEASUREMENTS_PROXY_HXX
