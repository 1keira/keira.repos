/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleProxy_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDATASETS_PROXY_CSTYLE_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDATASETS_PROXY_CSTYLE_HXX

#include <comm/ProxyStubFactory.hxx>
#include <comm/Proxy.hxx>
#include <comm/commidltypes.hxx>        // used for PROXY_EXPORT macro
#include <asi/connectivity/diagnostic/cstyle/StructDatasetParameter.hxx>
#include <asi/connectivity/diagnostic/cstyle/Definitions.hxx>
#include <asi/connectivity/diagnostic/cstyle/DiagnosticDatasetsC.hxx>
#include <asi/connectivity/diagnostic/cstyle/DiagnosticDatasetsReply.hxx>
#include <asi/connectivity/diagnostic/cstyle/DiagnosticDatasetsServiceReplyRegistration.hxx>

#include <string>

namespace asi
{
namespace connectivity
{
namespace diagnostic
{

namespace cstyle
{
    /**
        \brief A proxy for services that implement the diagnostic::DiagnosticDatasets interface.
    */
    class DiagnosticDatasetsProxy  : public comm::Proxy
    {
    public:
        // ctor with listener pointer and no reply interface
        DiagnosticDatasetsProxy(const comm::InstanceID& _id, comm::LifecycleListener* l=nullptr )
        : Proxy(comm::Proxy::IdentityArgs(_id, getIKey(), getIName())
                ,clientInitFactory
                ,comm::CStyle, l)
        {
        }

        // ctor with listener pointer and no reply interface
        // explicit so we don't magically construct proxies from integers
        explicit DiagnosticDatasetsProxy(const uint32_t inst_cnt, comm::LifecycleListener* l=nullptr )
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDATASETS_REQUEST), inst_cnt),
                getIKey(), getIName())
                ,clientInitFactory
                ,comm::CStyle
                ,l)
        {
        }

        // ctor with listener reference and no reply interface
        DiagnosticDatasetsProxy(const comm::InstanceID& id, comm::LifecycleListener& l )
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
                ,comm::CStyle, &l)
        {
        }

        // ctor with listener pointer and no reply interface
        DiagnosticDatasetsProxy(const uint32_t inst_cnt, comm::LifecycleListener& l )
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDATASETS_REQUEST), inst_cnt)
                , getIKey(), getIName())
                ,clientInitFactory
                ,comm::CStyle
                ,&l)
        {
        }

        // constructors  with a user passed object factory to receive notifications
        // ctor with listener pointer and no reply interface
        // explicit so we don't magically construct proxies from integers
        explicit DiagnosticDatasetsProxy(const uint32_t inst_cnt
                                        ,const comm::ActiveObjectFactoryPtr& aof
                                        ,comm::LifecycleListener* l=nullptr )
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDATASETS_REQUEST), inst_cnt),
                getIKey(), getIName())
                ,clientInitFactory
                ,aof
                ,comm::CStyle
                ,l)
        {
        }

        // ctor with listener pointer and no reply interface
        DiagnosticDatasetsProxy(const uint32_t inst_cnt
                                ,const comm::ActiveObjectFactoryPtr& aof
                                ,comm::LifecycleListener& l )
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDATASETS_REQUEST), inst_cnt)
                , getIKey(), getIName())
                ,clientInitFactory
                ,aof
                ,comm::CStyle
                ,&l)
        {
        }

        // ctor with reply instance and listener pointers
        DiagnosticDatasetsProxy(const comm::InstanceID& id, DiagnosticDatasetsReply* r, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
                ,DiagnosticDatasetsServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDATASETS_REPLY))
                    ,r
                    ,nullptr
                    )
                ,comm::CStyle
                ,l)
        {
        }

        // ctor with reply instance and listener pointers and ActiveObjectFactory
        DiagnosticDatasetsProxy(const comm::InstanceID& id, DiagnosticDatasetsReply* r, comm::ActiveObjectFactoryPtr aof, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
                ,DiagnosticDatasetsServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDATASETS_REPLY))
                    ,r
                    ,nullptr
                    ,aof
                    )
                ,comm::CStyle
                ,l)
        {
        }

        // ctor with reply instance and listener pointers
        DiagnosticDatasetsProxy(const uint32_t inst_cnt, DiagnosticDatasetsReply* r, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDATASETS_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
                ,DiagnosticDatasetsServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDATASETS_REPLY))
                    ,r
                    ,nullptr
                    )
                ,comm::CStyle
                ,l)
        {
        }

        // ctor with reply instance and listener pointers and ActiveObjectFactory
        DiagnosticDatasetsProxy(const uint32_t inst_cnt, DiagnosticDatasetsReply* r, comm::ActiveObjectFactoryPtr aof, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDATASETS_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
            ,DiagnosticDatasetsServiceReplyRegistration(
                comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDATASETS_REPLY))
                ,r
                ,nullptr
                ,aof
                )
            ,comm::CStyle
            ,l)
        {
        }

        // ctor with reply instance reference and listener pointer
        DiagnosticDatasetsProxy(const comm::InstanceID& id, DiagnosticDatasetsReply& r, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
                ,DiagnosticDatasetsServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDATASETS_REPLY))
                    ,&r
                    ,nullptr
                    )
            ,comm::CStyle
            ,l)
        {
        }

        // ctor with reply instance reference and listener pointer and ActiveObjectFactory
        DiagnosticDatasetsProxy(const comm::InstanceID& id, DiagnosticDatasetsReply& r, comm::ActiveObjectFactoryPtr aof, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
            ,DiagnosticDatasetsServiceReplyRegistration(
                comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDATASETS_REPLY))
                ,&r
                ,nullptr
                ,aof
                )
            ,comm::CStyle
            ,l)
        {
        }

        // ctor with reply instance reference and listener pointer
        DiagnosticDatasetsProxy(const uint32_t inst_cnt, DiagnosticDatasetsReply& r, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDATASETS_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
            ,DiagnosticDatasetsServiceReplyRegistration(
                comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDATASETS_REPLY))
                ,&r
                ,nullptr
                )
            ,comm::CStyle
            ,l)
        {
        }

        // ctor with reply instance reference and listener pointer and ActiveObjectFactory
        DiagnosticDatasetsProxy(const uint32_t inst_cnt, DiagnosticDatasetsReply& r, comm::ActiveObjectFactoryPtr aof, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDATASETS_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
            ,DiagnosticDatasetsServiceReplyRegistration(
                comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDATASETS_REPLY))
                ,&r
                ,nullptr
                ,aof
                )
            ,comm::CStyle
            ,l)
        {
        }

        // ctor with reply instance and listener reference
        DiagnosticDatasetsProxy(const comm::InstanceID& id, DiagnosticDatasetsReply& r, comm::LifecycleListener& l)
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
                ,DiagnosticDatasetsServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDATASETS_REPLY))
                    ,&r
                    ,nullptr
                    )
            ,comm::CStyle
            ,&l)
        {
        }

        // ctor with reply instance and listener reference and ActiveObjectFactory
        DiagnosticDatasetsProxy(const comm::InstanceID& id, DiagnosticDatasetsReply& r, comm::ActiveObjectFactoryPtr aof, comm::LifecycleListener& l)
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
                ,DiagnosticDatasetsServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDATASETS_REPLY))
                    ,&r
                    ,nullptr
                    ,aof
                    )
            ,comm::CStyle
            ,&l)
        {
        }

        // ctor with reply instance and listener reference
        DiagnosticDatasetsProxy(const uint32_t inst_cnt, DiagnosticDatasetsReply& r, comm::LifecycleListener& l)
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDATASETS_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
                ,DiagnosticDatasetsServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDATASETS_REPLY))
                    ,&r
                    ,nullptr
                    )
            ,comm::CStyle
            ,&l)
        {
        }

        // ctor with reply instance and listener reference and ActiveObjectFactory
        DiagnosticDatasetsProxy(const uint32_t inst_cnt, DiagnosticDatasetsReply& r, comm::ActiveObjectFactoryPtr aof, comm::LifecycleListener& l)
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDATASETS_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
                ,DiagnosticDatasetsServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDATASETS_REPLY))
                    ,&r
                    ,nullptr
                    ,aof
                    )
            ,comm::CStyle
            ,&l)
        {
        }

        // default ctor
        DiagnosticDatasetsProxy() {}
        // DiagnosticDatasetsProxy is copy-assignable, default copy-ctor and assignment operator are fine
        // DiagnosticDatasetsProxy is move-assignable when using C++11 or higher

        DiagnosticDatasetsC& operator*() const
        {
            return *operator->();
        }

        DiagnosticDatasetsC* operator->() const
        {
            return reinterpret_cast<DiagnosticDatasetsC*>(getImpl());
        }

    private:

        static const comm::InterfaceKey& getIKey() {
            static comm::InterfaceKey ikey(0x00020008, 0x0000, 0x6000, 0x0000, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00);
            return ikey;
        }
        static const std::string& getIName() {
            static const std::string& iname{"asi.connectivity.diagnostic.DiagnosticDatasets"};
            return iname;
        }
        static const comm::InterfaceKey& getRIKey() {
            // semver is not different in request/reply direction
            return DiagnosticDatasetsProxy::getIKey();
        }
        // proxy/stub factory init for the client side
        PROXY_EXPORT static const ProxyStubFactory* clientInitFactory();

    };

} // namespace cstyle
}//namespace asi
}//namespace connectivity
}//namespace diagnostic
#endif// ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDATASETS_PROXY_CSTYLE_HXX
