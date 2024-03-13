/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template ProxyReply_hxx.tmpl
*/
#ifndef PERSISTENCE_IPERSISTENCEA_PROXYREPLY_HXX
#define PERSISTENCE_IPERSISTENCEA_PROXYREPLY_HXX


#include <comm/Proxy.hxx>
#include <comm/CoreApi.hxx>
#include <comm/commidltypes.hxx>        // used for PROXY_EXPORT macro
#include <persistence/Definitions.hxx>
#include <persistence/IPersistenceAReplyS.hxx>

#include <string>

namespace persistence
{

    class IPersistenceAProxyReply  : public comm::Proxy {
    public:
        // ctor with listener pointer and no reply interface
        IPersistenceAProxyReply(const comm::InstanceID& _id, comm::LifecycleListener* l=nullptr )
        : Proxy(comm::Proxy::IdentityArgs(_id, getRIKey(), getIName(), false /* not discoverable */)
                ,clientInitFactory
                , comm::CIPtrStyle, l)
        {
        }

        // ctor with listener pointer and no reply interface
        IPersistenceAProxyReply(const uint32_t inst_cnt, comm::LifecycleListener* l=nullptr )
        : Proxy(comm::Proxy::IdentityArgs(
            comm::InstanceID (comm::InterfaceID(BINARY_UUID_PERSISTENCE_IPERSISTENCEA_REPLY), inst_cnt)
            ,getRIKey(), getIName(), false /* not discoverable */)
            ,clientInitFactory
            ,comm::CIPtrStyle
            ,l)
        {
        }

        // ctor with listener reference and no reply interface
        IPersistenceAProxyReply(const comm::InstanceID& id, comm::LifecycleListener& l )
        : Proxy(comm::Proxy::IdentityArgs(id, getRIKey(), getIName(), false /* not discoverable */)
            ,clientInitFactory
            , comm::CIPtrStyle, &l)
        {
        }

        // ctor with listener reference and no reply interface
        IPersistenceAProxyReply( const uint32_t inst_cnt, comm::LifecycleListener& l )
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_PERSISTENCE_IPERSISTENCEA_REPLY), inst_cnt)
                ,getRIKey(), getIName(), false /* not discoverable */)
                ,clientInitFactory
                ,comm::CIPtrStyle
                ,&l)
        {
        }

        IPersistenceAReplyS& operator*() const
        {
            return *operator->();
        }

        IPersistenceAReplyS* operator->() const
        {
            return reinterpret_cast<IPersistenceAReplyS*>(getImpl());
        }

        // default ctor
        IPersistenceAProxyReply() {}
        // IPersistenceAProxyReply is copy-assignable, default copy-ctor and assignment operator are fine
        // IPersistenceAProxyReply is move-assignable when using C++11 or higher

    private:
        static const comm::InterfaceKey& getRIKey() {
            static comm::InterfaceKey rikey(0x00010004, 0x0000, 0x6000, 0x0000, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00);
            return rikey;
        }

        static const std::string& getIName() {
            static const std::string iname{"persistence.IPersistenceA"};
            return iname;
        }

        // proxy/stub factory init for the client side
        PROXY_EXPORT static const ProxyStubFactory* clientInitFactory();

    };

}// namespace persistence

#endif// PERSISTENCE_IPERSISTENCEA_PROXYREPLY_HXX
