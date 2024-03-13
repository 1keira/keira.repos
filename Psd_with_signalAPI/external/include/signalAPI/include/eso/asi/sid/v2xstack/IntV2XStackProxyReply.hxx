/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template ProxyReply_hxx.tmpl
*/
#ifndef ASI_SID_V2XSTACK_INTV2XSTACK_PROXYREPLY_HXX
#define ASI_SID_V2XSTACK_INTV2XSTACK_PROXYREPLY_HXX


#include <comm/Proxy.hxx>
#include <comm/CoreApi.hxx>
#include <comm/commidltypes.hxx>        // used for PROXY_EXPORT macro
#include <asi/sid/v2xstack/Definitions.hxx>
#include <asi/sid/v2xstack/IntV2XStackReplyS.hxx>

#include <string>

namespace asi
{
namespace sid
{
namespace v2xstack
{

    class IntV2XStackProxyReply  : public comm::Proxy {
    public:
        // ctor with listener pointer and no reply interface
        IntV2XStackProxyReply(const comm::InstanceID& _id, comm::LifecycleListener* l=nullptr )
        : Proxy(comm::Proxy::IdentityArgs(_id, getRIKey(), getIName(), false /* not discoverable */)
                ,clientInitFactory
                , comm::CIPtrStyle, l)
        {
        }

        // ctor with listener pointer and no reply interface
        IntV2XStackProxyReply(const uint32_t inst_cnt, comm::LifecycleListener* l=nullptr )
        : Proxy(comm::Proxy::IdentityArgs(
            comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_SID_V2XSTACK_INTV2XSTACK_REPLY), inst_cnt)
            ,getRIKey(), getIName(), false /* not discoverable */)
            ,clientInitFactory
            ,comm::CIPtrStyle
            ,l)
        {
        }

        // ctor with listener reference and no reply interface
        IntV2XStackProxyReply(const comm::InstanceID& id, comm::LifecycleListener& l )
        : Proxy(comm::Proxy::IdentityArgs(id, getRIKey(), getIName(), false /* not discoverable */)
            ,clientInitFactory
            , comm::CIPtrStyle, &l)
        {
        }

        // ctor with listener reference and no reply interface
        IntV2XStackProxyReply( const uint32_t inst_cnt, comm::LifecycleListener& l )
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_SID_V2XSTACK_INTV2XSTACK_REPLY), inst_cnt)
                ,getRIKey(), getIName(), false /* not discoverable */)
                ,clientInitFactory
                ,comm::CIPtrStyle
                ,&l)
        {
        }

        IntV2XStackReplyS& operator*() const
        {
            return *operator->();
        }

        IntV2XStackReplyS* operator->() const
        {
            return reinterpret_cast<IntV2XStackReplyS*>(getImpl());
        }

        // default ctor
        IntV2XStackProxyReply() {}
        // IntV2XStackProxyReply is copy-assignable, default copy-ctor and assignment operator are fine
        // IntV2XStackProxyReply is move-assignable when using C++11 or higher

    private:
        static const comm::InterfaceKey& getRIKey() {
            static comm::InterfaceKey rikey(0x00010000, 0x0000, 0x6000, 0x0000, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00);
            return rikey;
        }

        static const std::string& getIName() {
            static const std::string iname{"asi.sid.v2xstack.IntV2XStack"};
            return iname;
        }

        // proxy/stub factory init for the client side
        PROXY_EXPORT static const ProxyStubFactory* clientInitFactory();

    };

}// namespace asi
}// namespace sid
}// namespace v2xstack

#endif// ASI_SID_V2XSTACK_INTV2XSTACK_PROXYREPLY_HXX
