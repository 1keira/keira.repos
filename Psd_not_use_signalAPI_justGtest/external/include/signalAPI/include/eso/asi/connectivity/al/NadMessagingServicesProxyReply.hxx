/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template ProxyReply_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_NADMESSAGINGSERVICES_PROXYREPLY_HXX
#define ASI_CONNECTIVITY_AL_NADMESSAGINGSERVICES_PROXYREPLY_HXX


#include <comm/Proxy.hxx>
#include <comm/CoreApi.hxx>
#include <comm/commidltypes.hxx>        // used for PROXY_EXPORT macro
#include <asi/connectivity/al/Definitions.hxx>
#include <asi/connectivity/al/NadMessagingServicesReplyS.hxx>

#include <string>

namespace asi
{
namespace connectivity
{
namespace al
{

    class NadMessagingServicesProxyReply  : public comm::Proxy {
    public:
        // ctor with listener pointer and no reply interface
        NadMessagingServicesProxyReply(const comm::InstanceID& _id, comm::LifecycleListener* l=nullptr )
        : Proxy(comm::Proxy::IdentityArgs(_id, getRIKey(), getIName(), false /* not discoverable */)
                ,clientInitFactory
                , comm::CIPtrStyle, l)
        {
        }

        // ctor with listener pointer and no reply interface
        NadMessagingServicesProxyReply(const uint32_t inst_cnt, comm::LifecycleListener* l=nullptr )
        : Proxy(comm::Proxy::IdentityArgs(
            comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_AL_NADMESSAGINGSERVICES_REPLY), inst_cnt)
            ,getRIKey(), getIName(), false /* not discoverable */)
            ,clientInitFactory
            ,comm::CIPtrStyle
            ,l)
        {
        }

        // ctor with listener reference and no reply interface
        NadMessagingServicesProxyReply(const comm::InstanceID& id, comm::LifecycleListener& l )
        : Proxy(comm::Proxy::IdentityArgs(id, getRIKey(), getIName(), false /* not discoverable */)
            ,clientInitFactory
            , comm::CIPtrStyle, &l)
        {
        }

        // ctor with listener reference and no reply interface
        NadMessagingServicesProxyReply( const uint32_t inst_cnt, comm::LifecycleListener& l )
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_AL_NADMESSAGINGSERVICES_REPLY), inst_cnt)
                ,getRIKey(), getIName(), false /* not discoverable */)
                ,clientInitFactory
                ,comm::CIPtrStyle
                ,&l)
        {
        }

        NadMessagingServicesReplyS& operator*() const
        {
            return *operator->();
        }

        NadMessagingServicesReplyS* operator->() const
        {
            return reinterpret_cast<NadMessagingServicesReplyS*>(getImpl());
        }

        // default ctor
        NadMessagingServicesProxyReply() {}
        // NadMessagingServicesProxyReply is copy-assignable, default copy-ctor and assignment operator are fine
        // NadMessagingServicesProxyReply is move-assignable when using C++11 or higher

    private:
        static const comm::InterfaceKey& getRIKey() {
            static comm::InterfaceKey rikey(0x00010000, 0x0001, 0x6000, 0x0000, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00);
            return rikey;
        }

        static const std::string& getIName() {
            static const std::string iname{"asi.connectivity.al.NadMessagingServices"};
            return iname;
        }

        // proxy/stub factory init for the client side
        PROXY_EXPORT static const ProxyStubFactory* clientInitFactory();

    };

}// namespace asi
}// namespace connectivity
}// namespace al

#endif// ASI_CONNECTIVITY_AL_NADMESSAGINGSERVICES_PROXYREPLY_HXX
