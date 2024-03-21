/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Proxy_hxx.tmpl
*/
#ifndef PERSISTENCE_IPERSISTENCEB_PROXY_HXX
#define PERSISTENCE_IPERSISTENCEB_PROXY_HXX

#include <comm/ProxyStubFactory.hxx>
#include <comm/Proxy.hxx>
#include <comm/commidltypes.hxx>        // used for PROXY_EXPORT macro
#include <persistence/StructPartitionHandle.hxx>
#include <persistence/Definitions.hxx>
#include <persistence/IPersistenceBC.hxx>
#include <persistence/IPersistenceBReply.hxx>
#include <persistence/IPersistenceBServiceReplyRegistration.hxx>

#include <string>

namespace persistence
{

    /**
        \brief A proxy for services that implement the persistence::IPersistenceB interface.
    */
    class IPersistenceBProxy  : public comm::Proxy
    {
    public:
        // ctor with listener pointer and no reply interface
        IPersistenceBProxy(const comm::InstanceID& _id, comm::LifecycleListener* l=nullptr )
        : Proxy(comm::Proxy::IdentityArgs(_id, getIKey(), getIName())
                ,clientInitFactory
                ,comm::CIPtrStyle, l)
        {
        }

        // ctor with listener pointer and no reply interface
        // explicit so we don't magically construct proxies from integers
        explicit IPersistenceBProxy(const uint32_t inst_cnt, comm::LifecycleListener* l=nullptr )
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_PERSISTENCE_IPERSISTENCEB_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
                ,comm::CIPtrStyle
                ,l)
        {
        }

        // ctor with listener reference and no reply interface
        IPersistenceBProxy(const comm::InstanceID& id, comm::LifecycleListener& l )
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
                ,comm::CIPtrStyle, &l)
        {
        }

        // ctor with listener pointer and no reply interface
        IPersistenceBProxy(const uint32_t inst_cnt, comm::LifecycleListener& l )
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_PERSISTENCE_IPERSISTENCEB_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
                ,comm::CIPtrStyle
                ,&l)
        {
        }

        // constructors  with a user passed object factory to receive notifications
        // ctor with listener pointer and no reply interface
        // explicit so we don't magically construct proxies from integers
        explicit IPersistenceBProxy(const uint32_t inst_cnt
                                        ,const comm::ActiveObjectFactoryPtr& aof
                                        ,comm::LifecycleListener* l=nullptr )
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_PERSISTENCE_IPERSISTENCEB_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
                ,aof
                ,comm::CIPtrStyle
                ,l
                )
        {
        }

        // ctor with listener pointer and no reply interface
        IPersistenceBProxy(const uint32_t inst_cnt
                                ,const comm::ActiveObjectFactoryPtr& aof
                                ,comm::LifecycleListener& l )
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_PERSISTENCE_IPERSISTENCEB_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
                ,aof
                ,comm::CIPtrStyle
                ,&l
                )
        {
        }
        // ctor with reply instance and listener pointers
        IPersistenceBProxy(const comm::InstanceID& id, IPersistenceBReply* r, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
                ,IPersistenceBServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_PERSISTENCE_IPERSISTENCEB_REPLY))
                    ,r
                    ,nullptr
                    )
                ,comm::CIPtrStyle
                ,l
                )
        {
        }

        // ctor with reply instance and listener pointers and ActiveObjectFactory
        IPersistenceBProxy(const comm::InstanceID& id, IPersistenceBReply* r, comm::ActiveObjectFactoryPtr aof, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
                ,IPersistenceBServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_PERSISTENCE_IPERSISTENCEB_REPLY))
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
        IPersistenceBProxy(const uint32_t inst_cnt, IPersistenceBReply* r, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_PERSISTENCE_IPERSISTENCEB_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
                ,IPersistenceBServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_PERSISTENCE_IPERSISTENCEB_REPLY))
                    ,r
                    ,nullptr
                    )
                ,comm::CIPtrStyle
                ,l
                )
        {
        }

        // ctor with reply instance and listener pointers and ActiveObjectFactory
        IPersistenceBProxy(const uint32_t inst_cnt, IPersistenceBReply* r, comm::ActiveObjectFactoryPtr aof, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_PERSISTENCE_IPERSISTENCEB_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
            ,IPersistenceBServiceReplyRegistration(
                comm::InstanceID(comm::InterfaceID(BINARY_UUID_PERSISTENCE_IPERSISTENCEB_REPLY))
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
        IPersistenceBProxy(const comm::InstanceID& id, IPersistenceBReply& r, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
                ,IPersistenceBServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_PERSISTENCE_IPERSISTENCEB_REPLY))
                    ,&r
                    ,nullptr
                    )
            ,comm::CIPtrStyle
            ,l
            )
        {
        }

        // ctor with reply instance reference and listener pointer and ActiveObjectFactory
        IPersistenceBProxy(const comm::InstanceID& id, IPersistenceBReply& r, comm::ActiveObjectFactoryPtr aof, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
            ,IPersistenceBServiceReplyRegistration(
                comm::InstanceID(comm::InterfaceID(BINARY_UUID_PERSISTENCE_IPERSISTENCEB_REPLY))
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
        IPersistenceBProxy(const uint32_t inst_cnt, IPersistenceBReply& r, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_PERSISTENCE_IPERSISTENCEB_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
            ,IPersistenceBServiceReplyRegistration(
                comm::InstanceID(comm::InterfaceID(BINARY_UUID_PERSISTENCE_IPERSISTENCEB_REPLY))
                ,&r
                ,nullptr
                )
            ,comm::CIPtrStyle
            ,l
            )
        {
        }

        // ctor with reply instance reference and listener pointer and ActiveObjectFactory
        IPersistenceBProxy(const uint32_t inst_cnt, IPersistenceBReply& r, comm::ActiveObjectFactoryPtr aof, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(comm::InstanceID (comm::InterfaceID(BINARY_UUID_PERSISTENCE_IPERSISTENCEB_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
            ,IPersistenceBServiceReplyRegistration(
                comm::InstanceID(comm::InterfaceID(BINARY_UUID_PERSISTENCE_IPERSISTENCEB_REPLY))
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
        IPersistenceBProxy(const comm::InstanceID& id, IPersistenceBReply& r, comm::LifecycleListener& l)
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
                ,IPersistenceBServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_PERSISTENCE_IPERSISTENCEB_REPLY))
                    ,&r
                    ,nullptr
                    )
            ,comm::CIPtrStyle
            ,&l
            )
        {
        }

        // ctor with reply instance and listener reference and ActiveObjectFactory
        IPersistenceBProxy(const comm::InstanceID& id, IPersistenceBReply& r, comm::ActiveObjectFactoryPtr aof, comm::LifecycleListener& l)
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
                ,IPersistenceBServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_PERSISTENCE_IPERSISTENCEB_REPLY))
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
        IPersistenceBProxy(const uint32_t inst_cnt, IPersistenceBReply& r, comm::LifecycleListener& l)
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_PERSISTENCE_IPERSISTENCEB_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
                ,IPersistenceBServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_PERSISTENCE_IPERSISTENCEB_REPLY))
                    ,&r
                    ,nullptr
                    )
            ,comm::CIPtrStyle
            ,&l
            )
        {
        }

        // ctor with reply instance and listener reference and ActiveObjectFactory
        IPersistenceBProxy(const uint32_t inst_cnt, IPersistenceBReply& r, comm::ActiveObjectFactoryPtr aof, comm::LifecycleListener& l)
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_PERSISTENCE_IPERSISTENCEB_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
                ,IPersistenceBServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_PERSISTENCE_IPERSISTENCEB_REPLY))
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
        IPersistenceBProxy() {}
        // IPersistenceBProxy is copy-assignable, default copy-ctor and assignment operator are fine
        // IPersistenceBProxy is move-assignable when using C++11 or higher

        IPersistenceBC& operator*() const
        {
            return *operator->();
        }

        IPersistenceBC* operator->() const
        {
            return reinterpret_cast<IPersistenceBC*>(getImpl());
        }

    private:
        static const comm::InterfaceKey& getIKey() {
            static comm::InterfaceKey ikey(0x00010004, 0x0000, 0x6000, 0x0000, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00);
            return ikey;
        }
        static const std::string& getIName() {
            static const std::string iname{"persistence.IPersistenceB"};
            return iname;
        }
        static const comm::InterfaceKey& getRIKey() {
            // semver is not different in request/reply direction
            return IPersistenceBProxy::getIKey();
        }

        // proxy/stub factory init for the client side
        PROXY_EXPORT static const ProxyStubFactory* clientInitFactory();

    };

}//namespace persistence
#endif// PERSISTENCE_IPERSISTENCEB_PROXY_HXX
