/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template ProxyReply_hxx.tmpl
*/
#ifndef SERVMNGT_EXTENSIONS_SERVICEMANAGEREVENTS_PROXYREPLY_HXX
#define SERVMNGT_EXTENSIONS_SERVICEMANAGEREVENTS_PROXYREPLY_HXX


#include <comm/Proxy.hxx>
#include <comm/CoreApi.hxx>
#include <comm/commidltypes.hxx>        // used for PROXY_EXPORT macro
#include <servmngt/extensions/Definitions.hxx>
#include <servmngt/extensions/ServiceManagerEventsReplyS.hxx>

#include <string>

namespace servmngt
{
namespace extensions
{

    class ServiceManagerEventsProxyReply  : public comm::Proxy {
    public:
        // ctor with listener pointer and no reply interface
        ServiceManagerEventsProxyReply(const comm::InstanceID& _id, comm::LifecycleListener* l=nullptr )
        : Proxy(comm::Proxy::IdentityArgs(_id, getRIKey(), getIName(), false /* not discoverable */)
                ,clientInitFactory
                , comm::CIPtrStyle, l)
        {
        }

        // ctor with listener pointer and no reply interface
        ServiceManagerEventsProxyReply(const uint32_t inst_cnt, comm::LifecycleListener* l=nullptr )
        : Proxy(comm::Proxy::IdentityArgs(
            comm::InstanceID (comm::InterfaceID(BINARY_UUID_SERVMNGT_EXTENSIONS_SERVICEMANAGEREVENTS_REPLY), inst_cnt)
            ,getRIKey(), getIName(), false /* not discoverable */)
            ,clientInitFactory
            ,comm::CIPtrStyle
            ,l)
        {
        }

        // ctor with listener reference and no reply interface
        ServiceManagerEventsProxyReply(const comm::InstanceID& id, comm::LifecycleListener& l )
        : Proxy(comm::Proxy::IdentityArgs(id, getRIKey(), getIName(), false /* not discoverable */)
            ,clientInitFactory
            , comm::CIPtrStyle, &l)
        {
        }

        // ctor with listener reference and no reply interface
        ServiceManagerEventsProxyReply( const uint32_t inst_cnt, comm::LifecycleListener& l )
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_SERVMNGT_EXTENSIONS_SERVICEMANAGEREVENTS_REPLY), inst_cnt)
                ,getRIKey(), getIName(), false /* not discoverable */)
                ,clientInitFactory
                ,comm::CIPtrStyle
                ,&l)
        {
        }

        ServiceManagerEventsReplyS& operator*() const
        {
            return *operator->();
        }

        ServiceManagerEventsReplyS* operator->() const
        {
            return reinterpret_cast<ServiceManagerEventsReplyS*>(getImpl());
        }

        // default ctor
        ServiceManagerEventsProxyReply() {}
        // ServiceManagerEventsProxyReply is copy-assignable, default copy-ctor and assignment operator are fine
        // ServiceManagerEventsProxyReply is move-assignable when using C++11 or higher

    private:
        static const comm::InterfaceKey& getRIKey() {
            static comm::InterfaceKey rikey(0x00030000, 0x0001, 0x6000, 0x0000, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00);
            return rikey;
        }

        static const std::string& getIName() {
            static const std::string iname{"servmngt.extensions.ServiceManagerEvents"};
            return iname;
        }

        // proxy/stub factory init for the client side
        PROXY_EXPORT static const ProxyStubFactory* clientInitFactory();

    };

}// namespace servmngt
}// namespace extensions

#endif// SERVMNGT_EXTENSIONS_SERVICEMANAGEREVENTS_PROXYREPLY_HXX
