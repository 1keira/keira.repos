/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleProxyReply_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICVOICEMEASUREMENTS_PROXYREPLY_CSTYLE_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICVOICEMEASUREMENTS_PROXYREPLY_CSTYLE_HXX


#include <comm/Proxy.hxx>
#include <comm/CoreApi.hxx>
#include <comm/commidltypes.hxx>        // used for PROXY_EXPORT macro
#include <asi/connectivity/diagnostic/cstyle/Definitions.hxx>
#include <asi/connectivity/diagnostic/cstyle/DiagnosticVoiceMeasurementsReplyS.hxx>

#include <string>

namespace asi
{
namespace connectivity
{
namespace diagnostic
{

namespace cstyle {

    class DiagnosticVoiceMeasurementsProxyReply  : public comm::Proxy {
    public:
        // ctor with listener pointer and no reply interface
        DiagnosticVoiceMeasurementsProxyReply(const comm::InstanceID& _id, comm::LifecycleListener* l=nullptr )
        : Proxy(comm::Proxy::IdentityArgs(_id, getRIKey(), getIName(), false /* not discoverable */)
        ,clientInitFactory
        , comm::CStyle, l)
        {
        }

        // ctor with listener pointer and no reply interface
        DiagnosticVoiceMeasurementsProxyReply(const uint32_t inst_cnt, comm::LifecycleListener* l=nullptr )
        : Proxy(comm::Proxy::IdentityArgs(
            comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICVOICEMEASUREMENTS_REPLY), inst_cnt)
            ,getRIKey(), getIName(), false /* not discoverable */)
            ,clientInitFactory
            ,comm::CStyle
            ,l)
        {
        }

        // ctor with listener reference and no reply interface
        DiagnosticVoiceMeasurementsProxyReply(const comm::InstanceID& id, comm::LifecycleListener& l )
        : Proxy(comm::Proxy::IdentityArgs(id, getRIKey(), getIName(), false /* not discoverable */)
        ,clientInitFactory
        , comm::CStyle, &l)
        {
        }

        // ctor with listener reference and no reply interface
        DiagnosticVoiceMeasurementsProxyReply( const uint32_t inst_cnt, comm::LifecycleListener& l )
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICVOICEMEASUREMENTS_REPLY), inst_cnt)
                ,getRIKey(), getIName(), false /* not discoverable */)
                ,clientInitFactory
                ,comm::CStyle
                ,&l)
        {
        }

        DiagnosticVoiceMeasurementsReplyS& operator*() const
        {
            return *operator->();
        }

        DiagnosticVoiceMeasurementsReplyS* operator->() const
        {
            return reinterpret_cast<DiagnosticVoiceMeasurementsReplyS*>(getImpl());
        }

        // default ctor
        DiagnosticVoiceMeasurementsProxyReply() {}
        // DiagnosticVoiceMeasurementsProxyReply is copy-assignable, default copy-ctor and assignment operator are fine
        // DiagnosticVoiceMeasurementsProxyReply is move-assignable when using C++11 or higher

    private:
        static const comm::InterfaceKey& getRIKey() {
            static comm::InterfaceKey rikey(0x00020008, 0x0000, 0x6000, 0x0000, 0x00, 0x01, 0x00, 0x02, 0x00, 0x00);
            return rikey;
        }

        static const std::string& getIName() {
            static const std::string iname{"asi.connectivity.diagnostic.DiagnosticVoiceMeasurements"};
            return iname;
        }

        // proxy/stub factory init for the client side
        PROXY_EXPORT static const ProxyStubFactory* clientInitFactory();


    };

} // namespace cstyle
}// namespace asi
}// namespace connectivity
}// namespace diagnostic

#endif// ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICVOICEMEASUREMENTS_PROXYREPLY_CSTYLE_HXX
