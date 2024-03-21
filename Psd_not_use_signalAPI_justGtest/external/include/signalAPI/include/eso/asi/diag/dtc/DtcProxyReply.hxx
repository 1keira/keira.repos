/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template ProxyReply_hxx.tmpl
*/
#ifndef ASI_DIAG_DTC_DTC_PROXYREPLY_HXX
#define ASI_DIAG_DTC_DTC_PROXYREPLY_HXX


#include <comm/Proxy.hxx>
#include <comm/CoreApi.hxx>
#include <comm/commidltypes.hxx>        // used for PROXY_EXPORT macro
#include <asi/diag/dtc/Definitions.hxx>
#include <asi/diag/dtc/DtcReplyS.hxx>

#include <string>

namespace asi
{
namespace diag
{
namespace dtc
{

    class DtcProxyReply  : public comm::Proxy {
    public:
        // ctor with listener pointer and no reply interface
        DtcProxyReply(const comm::InstanceID& _id, comm::LifecycleListener* l=nullptr )
        : Proxy(comm::Proxy::IdentityArgs(_id, getRIKey(), getIName(), false /* not discoverable */)
                ,clientInitFactory
                , comm::CIPtrStyle, l)
        {
        }

        // ctor with listener pointer and no reply interface
        DtcProxyReply(const uint32_t inst_cnt, comm::LifecycleListener* l=nullptr )
        : Proxy(comm::Proxy::IdentityArgs(
            comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_DIAG_DTC_DTC_REPLY), inst_cnt)
            ,getRIKey(), getIName(), false /* not discoverable */)
            ,clientInitFactory
            ,comm::CIPtrStyle
            ,l)
        {
        }

        // ctor with listener reference and no reply interface
        DtcProxyReply(const comm::InstanceID& id, comm::LifecycleListener& l )
        : Proxy(comm::Proxy::IdentityArgs(id, getRIKey(), getIName(), false /* not discoverable */)
            ,clientInitFactory
            , comm::CIPtrStyle, &l)
        {
        }

        // ctor with listener reference and no reply interface
        DtcProxyReply( const uint32_t inst_cnt, comm::LifecycleListener& l )
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_DIAG_DTC_DTC_REPLY), inst_cnt)
                ,getRIKey(), getIName(), false /* not discoverable */)
                ,clientInitFactory
                ,comm::CIPtrStyle
                ,&l)
        {
        }

        DtcReplyS& operator*() const
        {
            return *operator->();
        }

        DtcReplyS* operator->() const
        {
            return reinterpret_cast<DtcReplyS*>(getImpl());
        }

        // default ctor
        DtcProxyReply() {}
        // DtcProxyReply is copy-assignable, default copy-ctor and assignment operator are fine
        // DtcProxyReply is move-assignable when using C++11 or higher

    private:
        static const comm::InterfaceKey& getRIKey() {
            static comm::InterfaceKey rikey(0x00000005, 0x0000, 0x6000, 0x0000, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00);
            return rikey;
        }

        static const std::string& getIName() {
            static const std::string iname{"asi.diag.dtc.Dtc"};
            return iname;
        }

        // proxy/stub factory init for the client side
        PROXY_EXPORT static const ProxyStubFactory* clientInitFactory();

    };

}// namespace asi
}// namespace diag
}// namespace dtc

#endif// ASI_DIAG_DTC_DTC_PROXYREPLY_HXX
