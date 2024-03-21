/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleProxyReply_hxx.tmpl
*/
#ifndef SERVMNGT_EXTENSIONS_SYSTEMEVENTS_PROXYREPLY_CSTYLE_HXX
#define SERVMNGT_EXTENSIONS_SYSTEMEVENTS_PROXYREPLY_CSTYLE_HXX


#include <comm/Proxy.hxx>
#include <comm/CoreApi.hxx>
#include <comm/commidltypes.hxx>        // used for PROXY_EXPORT macro
#include <servmngt/extensions/cstyle/Definitions.hxx>
#include <servmngt/extensions/cstyle/SystemEventsReplyS.hxx>

#include <string>

namespace servmngt
{
namespace extensions
{

namespace cstyle {

    class SystemEventsProxyReply  : public comm::Proxy {
    public:
        // ctor with listener pointer and no reply interface
        SystemEventsProxyReply(const comm::InstanceID& _id, comm::LifecycleListener* l=nullptr )
        : Proxy(comm::Proxy::IdentityArgs(_id, getRIKey(), getIName(), false /* not discoverable */)
        ,clientInitFactory
        , comm::CStyle, l)
        {
        }

        // ctor with listener pointer and no reply interface
        SystemEventsProxyReply(const uint32_t inst_cnt, comm::LifecycleListener* l=nullptr )
        : Proxy(comm::Proxy::IdentityArgs(
            comm::InstanceID (comm::InterfaceID(BINARY_UUID_SERVMNGT_EXTENSIONS_SYSTEMEVENTS_REPLY), inst_cnt)
            ,getRIKey(), getIName(), false /* not discoverable */)
            ,clientInitFactory
            ,comm::CStyle
            ,l)
        {
        }

        // ctor with listener reference and no reply interface
        SystemEventsProxyReply(const comm::InstanceID& id, comm::LifecycleListener& l )
        : Proxy(comm::Proxy::IdentityArgs(id, getRIKey(), getIName(), false /* not discoverable */)
        ,clientInitFactory
        , comm::CStyle, &l)
        {
        }

        // ctor with listener reference and no reply interface
        SystemEventsProxyReply( const uint32_t inst_cnt, comm::LifecycleListener& l )
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_SERVMNGT_EXTENSIONS_SYSTEMEVENTS_REPLY), inst_cnt)
                ,getRIKey(), getIName(), false /* not discoverable */)
                ,clientInitFactory
                ,comm::CStyle
                ,&l)
        {
        }

        SystemEventsReplyS& operator*() const
        {
            return *operator->();
        }

        SystemEventsReplyS* operator->() const
        {
            return reinterpret_cast<SystemEventsReplyS*>(getImpl());
        }

        // default ctor
        SystemEventsProxyReply() {}
        // SystemEventsProxyReply is copy-assignable, default copy-ctor and assignment operator are fine
        // SystemEventsProxyReply is move-assignable when using C++11 or higher

    private:
        static const comm::InterfaceKey& getRIKey() {
            static comm::InterfaceKey rikey(0x00030000, 0x0001, 0x6000, 0x0000, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00);
            return rikey;
        }

        static const std::string& getIName() {
            static const std::string iname{"servmngt.extensions.SystemEvents"};
            return iname;
        }

        // proxy/stub factory init for the client side
        PROXY_EXPORT static const ProxyStubFactory* clientInitFactory();


    };

} // namespace cstyle
}// namespace servmngt
}// namespace extensions

#endif// SERVMNGT_EXTENSIONS_SYSTEMEVENTS_PROXYREPLY_CSTYLE_HXX
