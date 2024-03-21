/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Proxy_hxx.tmpl
*/
#ifndef SERVMNGT_ISERVICEMANAGER_PROXY_HXX
#define SERVMNGT_ISERVICEMANAGER_PROXY_HXX

#include <comm/ProxyStubFactory.hxx>
#include <comm/Proxy.hxx>
#include <comm/commidltypes.hxx>        // used for PROXY_EXPORT macro
#include <servmngt/Definitions.hxx>
#include <servmngt/IServiceManagerC.hxx>
#include <servmngt/IServiceManagerReply.hxx>
#include <servmngt/IServiceManagerServiceReplyRegistration.hxx>

#include <string>

namespace servmngt
{

    /**
        \brief A proxy for services that implement the servmngt::IServiceManager interface.
    */
    class IServiceManagerProxy  : public comm::Proxy
    {
    public:
        // ctor with listener pointer and no reply interface
        IServiceManagerProxy(const comm::InstanceID& _id, comm::LifecycleListener* l=nullptr )
        : Proxy(comm::Proxy::IdentityArgs(_id, getIKey(), getIName())
                ,clientInitFactory
                ,comm::CIPtrStyle, l)
        {
        }

        // ctor with listener pointer and no reply interface
        // explicit so we don't magically construct proxies from integers
        explicit IServiceManagerProxy(const uint32_t inst_cnt, comm::LifecycleListener* l=nullptr )
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_SERVMNGT_ISERVICEMANAGER_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
                ,comm::CIPtrStyle
                ,l)
        {
        }

        // ctor with listener reference and no reply interface
        IServiceManagerProxy(const comm::InstanceID& id, comm::LifecycleListener& l )
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
                ,comm::CIPtrStyle, &l)
        {
        }

        // ctor with listener pointer and no reply interface
        IServiceManagerProxy(const uint32_t inst_cnt, comm::LifecycleListener& l )
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_SERVMNGT_ISERVICEMANAGER_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
                ,comm::CIPtrStyle
                ,&l)
        {
        }

        // constructors  with a user passed object factory to receive notifications
        // ctor with listener pointer and no reply interface
        // explicit so we don't magically construct proxies from integers
        explicit IServiceManagerProxy(const uint32_t inst_cnt
                                        ,const comm::ActiveObjectFactoryPtr& aof
                                        ,comm::LifecycleListener* l=nullptr )
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_SERVMNGT_ISERVICEMANAGER_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
                ,aof
                ,comm::CIPtrStyle
                ,l
                )
        {
        }

        // ctor with listener pointer and no reply interface
        IServiceManagerProxy(const uint32_t inst_cnt
                                ,const comm::ActiveObjectFactoryPtr& aof
                                ,comm::LifecycleListener& l )
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_SERVMNGT_ISERVICEMANAGER_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
                ,aof
                ,comm::CIPtrStyle
                ,&l
                )
        {
        }
        // ctor with reply instance and listener pointers
        IServiceManagerProxy(const comm::InstanceID& id, IServiceManagerReply* r, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
                ,IServiceManagerServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_SERVMNGT_ISERVICEMANAGER_REPLY))
                    ,r
                    ,nullptr
                    )
                ,comm::CIPtrStyle
                ,l
                )
        {
        }

        // ctor with reply instance and listener pointers and ActiveObjectFactory
        IServiceManagerProxy(const comm::InstanceID& id, IServiceManagerReply* r, comm::ActiveObjectFactoryPtr aof, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
                ,IServiceManagerServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_SERVMNGT_ISERVICEMANAGER_REPLY))
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
        IServiceManagerProxy(const uint32_t inst_cnt, IServiceManagerReply* r, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_SERVMNGT_ISERVICEMANAGER_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
                ,IServiceManagerServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_SERVMNGT_ISERVICEMANAGER_REPLY))
                    ,r
                    ,nullptr
                    )
                ,comm::CIPtrStyle
                ,l
                )
        {
        }

        // ctor with reply instance and listener pointers and ActiveObjectFactory
        IServiceManagerProxy(const uint32_t inst_cnt, IServiceManagerReply* r, comm::ActiveObjectFactoryPtr aof, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_SERVMNGT_ISERVICEMANAGER_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
            ,IServiceManagerServiceReplyRegistration(
                comm::InstanceID(comm::InterfaceID(BINARY_UUID_SERVMNGT_ISERVICEMANAGER_REPLY))
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
        IServiceManagerProxy(const comm::InstanceID& id, IServiceManagerReply& r, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
                ,IServiceManagerServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_SERVMNGT_ISERVICEMANAGER_REPLY))
                    ,&r
                    ,nullptr
                    )
            ,comm::CIPtrStyle
            ,l
            )
        {
        }

        // ctor with reply instance reference and listener pointer and ActiveObjectFactory
        IServiceManagerProxy(const comm::InstanceID& id, IServiceManagerReply& r, comm::ActiveObjectFactoryPtr aof, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
            ,IServiceManagerServiceReplyRegistration(
                comm::InstanceID(comm::InterfaceID(BINARY_UUID_SERVMNGT_ISERVICEMANAGER_REPLY))
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
        IServiceManagerProxy(const uint32_t inst_cnt, IServiceManagerReply& r, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_SERVMNGT_ISERVICEMANAGER_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
            ,IServiceManagerServiceReplyRegistration(
                comm::InstanceID(comm::InterfaceID(BINARY_UUID_SERVMNGT_ISERVICEMANAGER_REPLY))
                ,&r
                ,nullptr
                )
            ,comm::CIPtrStyle
            ,l
            )
        {
        }

        // ctor with reply instance reference and listener pointer and ActiveObjectFactory
        IServiceManagerProxy(const uint32_t inst_cnt, IServiceManagerReply& r, comm::ActiveObjectFactoryPtr aof, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(comm::InstanceID (comm::InterfaceID(BINARY_UUID_SERVMNGT_ISERVICEMANAGER_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
            ,IServiceManagerServiceReplyRegistration(
                comm::InstanceID(comm::InterfaceID(BINARY_UUID_SERVMNGT_ISERVICEMANAGER_REPLY))
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
        IServiceManagerProxy(const comm::InstanceID& id, IServiceManagerReply& r, comm::LifecycleListener& l)
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
                ,IServiceManagerServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_SERVMNGT_ISERVICEMANAGER_REPLY))
                    ,&r
                    ,nullptr
                    )
            ,comm::CIPtrStyle
            ,&l
            )
        {
        }

        // ctor with reply instance and listener reference and ActiveObjectFactory
        IServiceManagerProxy(const comm::InstanceID& id, IServiceManagerReply& r, comm::ActiveObjectFactoryPtr aof, comm::LifecycleListener& l)
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
                ,IServiceManagerServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_SERVMNGT_ISERVICEMANAGER_REPLY))
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
        IServiceManagerProxy(const uint32_t inst_cnt, IServiceManagerReply& r, comm::LifecycleListener& l)
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_SERVMNGT_ISERVICEMANAGER_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
                ,IServiceManagerServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_SERVMNGT_ISERVICEMANAGER_REPLY))
                    ,&r
                    ,nullptr
                    )
            ,comm::CIPtrStyle
            ,&l
            )
        {
        }

        // ctor with reply instance and listener reference and ActiveObjectFactory
        IServiceManagerProxy(const uint32_t inst_cnt, IServiceManagerReply& r, comm::ActiveObjectFactoryPtr aof, comm::LifecycleListener& l)
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_SERVMNGT_ISERVICEMANAGER_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
                ,IServiceManagerServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_SERVMNGT_ISERVICEMANAGER_REPLY))
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
        IServiceManagerProxy() {}
        // IServiceManagerProxy is copy-assignable, default copy-ctor and assignment operator are fine
        // IServiceManagerProxy is move-assignable when using C++11 or higher

        IServiceManagerC& operator*() const
        {
            return *operator->();
        }

        IServiceManagerC* operator->() const
        {
            return reinterpret_cast<IServiceManagerC*>(getImpl());
        }

    private:
        static const comm::InterfaceKey& getIKey() {
            static comm::InterfaceKey ikey(0x00030003, 0x0000, 0x6000, 0x0000, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00);
            return ikey;
        }
        static const std::string& getIName() {
            static const std::string iname{"servmngt.IServiceManager"};
            return iname;
        }
        static const comm::InterfaceKey& getRIKey() {
            // semver is not different in request/reply direction
            return IServiceManagerProxy::getIKey();
        }

        // proxy/stub factory init for the client side
        PROXY_EXPORT static const ProxyStubFactory* clientInitFactory();

    };

}//namespace servmngt
#endif// SERVMNGT_ISERVICEMANAGER_PROXY_HXX
