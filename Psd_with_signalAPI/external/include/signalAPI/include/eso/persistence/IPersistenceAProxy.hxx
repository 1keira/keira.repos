/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Proxy_hxx.tmpl
*/
#ifndef PERSISTENCE_IPERSISTENCEA_PROXY_HXX
#define PERSISTENCE_IPERSISTENCEA_PROXY_HXX

#include <comm/ProxyStubFactory.hxx>
#include <comm/Proxy.hxx>
#include <comm/commidltypes.hxx>        // used for PROXY_EXPORT macro
#include <persistence/StructPartitionHandle.hxx>
#include <persistence/Definitions.hxx>
#include <persistence/IPersistenceAC.hxx>
#include <persistence/IPersistenceAReply.hxx>
#include <persistence/IPersistenceAServiceReplyRegistration.hxx>

#include <string>

namespace persistence
{

    /**
        \brief A proxy for services that implement the persistence::IPersistenceA interface.
    */
    class IPersistenceAProxy  : public comm::Proxy
    {
    public:
        // ctor with listener pointer and no reply interface
        IPersistenceAProxy(const comm::InstanceID& _id, comm::LifecycleListener* l=nullptr )
        : Proxy(comm::Proxy::IdentityArgs(_id, getIKey(), getIName())
                ,clientInitFactory
                ,comm::CIPtrStyle, l)
        {
        }

        // ctor with listener pointer and no reply interface
        // explicit so we don't magically construct proxies from integers
        explicit IPersistenceAProxy(const uint32_t inst_cnt, comm::LifecycleListener* l=nullptr )
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_PERSISTENCE_IPERSISTENCEA_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
                ,comm::CIPtrStyle
                ,l)
        {
        }

        // ctor with listener reference and no reply interface
        IPersistenceAProxy(const comm::InstanceID& id, comm::LifecycleListener& l )
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
                ,comm::CIPtrStyle, &l)
        {
        }

        // ctor with listener pointer and no reply interface
        IPersistenceAProxy(const uint32_t inst_cnt, comm::LifecycleListener& l )
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_PERSISTENCE_IPERSISTENCEA_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
                ,comm::CIPtrStyle
                ,&l)
        {
        }

        // constructors  with a user passed object factory to receive notifications
        // ctor with listener pointer and no reply interface
        // explicit so we don't magically construct proxies from integers
        explicit IPersistenceAProxy(const uint32_t inst_cnt
                                        ,const comm::ActiveObjectFactoryPtr& aof
                                        ,comm::LifecycleListener* l=nullptr )
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_PERSISTENCE_IPERSISTENCEA_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
                ,aof
                ,comm::CIPtrStyle
                ,l
                )
        {
        }

        // ctor with listener pointer and no reply interface
        IPersistenceAProxy(const uint32_t inst_cnt
                                ,const comm::ActiveObjectFactoryPtr& aof
                                ,comm::LifecycleListener& l )
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_PERSISTENCE_IPERSISTENCEA_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
                ,aof
                ,comm::CIPtrStyle
                ,&l
                )
        {
        }
        // ctor with reply instance and listener pointers
        IPersistenceAProxy(const comm::InstanceID& id, IPersistenceAReply* r, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
                ,IPersistenceAServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_PERSISTENCE_IPERSISTENCEA_REPLY))
                    ,r
                    ,nullptr
                    )
                ,comm::CIPtrStyle
                ,l
                )
        {
        }

        // ctor with reply instance and listener pointers and ActiveObjectFactory
        IPersistenceAProxy(const comm::InstanceID& id, IPersistenceAReply* r, comm::ActiveObjectFactoryPtr aof, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
                ,IPersistenceAServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_PERSISTENCE_IPERSISTENCEA_REPLY))
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
        IPersistenceAProxy(const uint32_t inst_cnt, IPersistenceAReply* r, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_PERSISTENCE_IPERSISTENCEA_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
                ,IPersistenceAServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_PERSISTENCE_IPERSISTENCEA_REPLY))
                    ,r
                    ,nullptr
                    )
                ,comm::CIPtrStyle
                ,l
                )
        {
        }

        // ctor with reply instance and listener pointers and ActiveObjectFactory
        IPersistenceAProxy(const uint32_t inst_cnt, IPersistenceAReply* r, comm::ActiveObjectFactoryPtr aof, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_PERSISTENCE_IPERSISTENCEA_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
            ,IPersistenceAServiceReplyRegistration(
                comm::InstanceID(comm::InterfaceID(BINARY_UUID_PERSISTENCE_IPERSISTENCEA_REPLY))
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
        IPersistenceAProxy(const comm::InstanceID& id, IPersistenceAReply& r, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
                ,IPersistenceAServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_PERSISTENCE_IPERSISTENCEA_REPLY))
                    ,&r
                    ,nullptr
                    )
            ,comm::CIPtrStyle
            ,l
            )
        {
        }

        // ctor with reply instance reference and listener pointer and ActiveObjectFactory
        IPersistenceAProxy(const comm::InstanceID& id, IPersistenceAReply& r, comm::ActiveObjectFactoryPtr aof, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
            ,IPersistenceAServiceReplyRegistration(
                comm::InstanceID(comm::InterfaceID(BINARY_UUID_PERSISTENCE_IPERSISTENCEA_REPLY))
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
        IPersistenceAProxy(const uint32_t inst_cnt, IPersistenceAReply& r, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_PERSISTENCE_IPERSISTENCEA_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
            ,IPersistenceAServiceReplyRegistration(
                comm::InstanceID(comm::InterfaceID(BINARY_UUID_PERSISTENCE_IPERSISTENCEA_REPLY))
                ,&r
                ,nullptr
                )
            ,comm::CIPtrStyle
            ,l
            )
        {
        }

        // ctor with reply instance reference and listener pointer and ActiveObjectFactory
        IPersistenceAProxy(const uint32_t inst_cnt, IPersistenceAReply& r, comm::ActiveObjectFactoryPtr aof, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(comm::InstanceID (comm::InterfaceID(BINARY_UUID_PERSISTENCE_IPERSISTENCEA_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
            ,IPersistenceAServiceReplyRegistration(
                comm::InstanceID(comm::InterfaceID(BINARY_UUID_PERSISTENCE_IPERSISTENCEA_REPLY))
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
        IPersistenceAProxy(const comm::InstanceID& id, IPersistenceAReply& r, comm::LifecycleListener& l)
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
                ,IPersistenceAServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_PERSISTENCE_IPERSISTENCEA_REPLY))
                    ,&r
                    ,nullptr
                    )
            ,comm::CIPtrStyle
            ,&l
            )
        {
        }

        // ctor with reply instance and listener reference and ActiveObjectFactory
        IPersistenceAProxy(const comm::InstanceID& id, IPersistenceAReply& r, comm::ActiveObjectFactoryPtr aof, comm::LifecycleListener& l)
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
                ,IPersistenceAServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_PERSISTENCE_IPERSISTENCEA_REPLY))
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
        IPersistenceAProxy(const uint32_t inst_cnt, IPersistenceAReply& r, comm::LifecycleListener& l)
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_PERSISTENCE_IPERSISTENCEA_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
                ,IPersistenceAServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_PERSISTENCE_IPERSISTENCEA_REPLY))
                    ,&r
                    ,nullptr
                    )
            ,comm::CIPtrStyle
            ,&l
            )
        {
        }

        // ctor with reply instance and listener reference and ActiveObjectFactory
        IPersistenceAProxy(const uint32_t inst_cnt, IPersistenceAReply& r, comm::ActiveObjectFactoryPtr aof, comm::LifecycleListener& l)
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_PERSISTENCE_IPERSISTENCEA_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
                ,IPersistenceAServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_PERSISTENCE_IPERSISTENCEA_REPLY))
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
        IPersistenceAProxy() {}
        // IPersistenceAProxy is copy-assignable, default copy-ctor and assignment operator are fine
        // IPersistenceAProxy is move-assignable when using C++11 or higher

        IPersistenceAC& operator*() const
        {
            return *operator->();
        }

        IPersistenceAC* operator->() const
        {
            return reinterpret_cast<IPersistenceAC*>(getImpl());
        }

    private:
        static const comm::InterfaceKey& getIKey() {
            static comm::InterfaceKey ikey(0x00010004, 0x0000, 0x6000, 0x0000, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00);
            return ikey;
        }
        static const std::string& getIName() {
            static const std::string iname{"persistence.IPersistenceA"};
            return iname;
        }
        static const comm::InterfaceKey& getRIKey() {
            // semver is not different in request/reply direction
            return IPersistenceAProxy::getIKey();
        }

        // proxy/stub factory init for the client side
        PROXY_EXPORT static const ProxyStubFactory* clientInitFactory();

    };

}//namespace persistence
#endif// PERSISTENCE_IPERSISTENCEA_PROXY_HXX
