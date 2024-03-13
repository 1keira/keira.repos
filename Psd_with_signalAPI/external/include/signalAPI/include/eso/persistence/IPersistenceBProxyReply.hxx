/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template ProxyReply_hxx.tmpl
*/
#ifndef PERSISTENCE_IPERSISTENCEB_PROXYREPLY_HXX
#define PERSISTENCE_IPERSISTENCEB_PROXYREPLY_HXX


#include <comm/Proxy.hxx>
#include <comm/CoreApi.hxx>
#include <comm/commidltypes.hxx>        // used for PROXY_EXPORT macro
#include <persistence/Definitions.hxx>
#include <persistence/IPersistenceBReplyS.hxx>

#include <string>

namespace persistence
{

    class IPersistenceBProxyReply  : public comm::Proxy {
    public:
        // ctor with listener pointer and no reply interface
        IPersistenceBProxyReply(const comm::InstanceID& _id, comm::LifecycleListener* l=nullptr )
        : Proxy(comm::Proxy::IdentityArgs(_id, getRIKey(), getIName(), false /* not discoverable */)
                ,clientInitFactory
                , comm::CIPtrStyle, l)
        {
        }

        // ctor with listener pointer and no reply interface
        IPersistenceBProxyReply(const uint32_t inst_cnt, comm::LifecycleListener* l=nullptr )
        : Proxy(comm::Proxy::IdentityArgs(
            comm::InstanceID (comm::InterfaceID(BINARY_UUID_PERSISTENCE_IPERSISTENCEB_REPLY), inst_cnt)
            ,getRIKey(), getIName(), false /* not discoverable */)
            ,clientInitFactory
            ,comm::CIPtrStyle
            ,l)
        {
        }

        // ctor with listener reference and no reply interface
        IPersistenceBProxyReply(const comm::InstanceID& id, comm::LifecycleListener& l )
        : Proxy(comm::Proxy::IdentityArgs(id, getRIKey(), getIName(), false /* not discoverable */)
            ,clientInitFactory
            , comm::CIPtrStyle, &l)
        {
        }

        // ctor with listener reference and no reply interface
        IPersistenceBProxyReply( const uint32_t inst_cnt, comm::LifecycleListener& l )
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_PERSISTENCE_IPERSISTENCEB_REPLY), inst_cnt)
                ,getRIKey(), getIName(), false /* not discoverable */)
                ,clientInitFactory
                ,comm::CIPtrStyle
                ,&l)
        {
        }

        IPersistenceBReplyS& operator*() const
        {
            return *operator->();
        }

        IPersistenceBReplyS* operator->() const
        {
            return reinterpret_cast<IPersistenceBReplyS*>(getImpl());
        }

        // default ctor
        IPersistenceBProxyReply() {}
        // IPersistenceBProxyReply is copy-assignable, default copy-ctor and assignment operator are fine
        // IPersistenceBProxyReply is move-assignable when using C++11 or higher

    private:
        static const comm::InterfaceKey& getRIKey() {
            static comm::InterfaceKey rikey(0x00010004, 0x0000, 0x6000, 0x0000, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00);
            return rikey;
        }

        static const std::string& getIName() {
            static const std::string iname{"persistence.IPersistenceB"};
            return iname;
        }

        // proxy/stub factory init for the client side
        PROXY_EXPORT static const ProxyStubFactory* clientInitFactory();

    };

}// namespace persistence

#endif// PERSISTENCE_IPERSISTENCEB_PROXYREPLY_HXX
