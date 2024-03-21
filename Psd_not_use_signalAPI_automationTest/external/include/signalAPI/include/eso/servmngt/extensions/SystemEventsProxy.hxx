/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Proxy_hxx.tmpl
*/
#ifndef SERVMNGT_EXTENSIONS_SYSTEMEVENTS_PROXY_HXX
#define SERVMNGT_EXTENSIONS_SYSTEMEVENTS_PROXY_HXX

#include <comm/ProxyStubFactory.hxx>
#include <comm/Proxy.hxx>
#include <comm/commidltypes.hxx>        // used for PROXY_EXPORT macro
#include <servmngt/extensions/Definitions.hxx>
#include <servmngt/extensions/SystemEventsC.hxx>
#include <servmngt/extensions/SystemEventsReply.hxx>
#include <servmngt/extensions/SystemEventsServiceReplyRegistration.hxx>

#include <string>

namespace servmngt
{
namespace extensions
{

    /**
        \brief A proxy for services that implement the extensions::SystemEvents interface.
    */
    class SystemEventsProxy  : public comm::Proxy
    {
    public:
        // ctor with listener pointer and no reply interface
        SystemEventsProxy(const comm::InstanceID& _id, comm::LifecycleListener* l=nullptr )
        : Proxy(comm::Proxy::IdentityArgs(_id, getIKey(), getIName())
                ,clientInitFactory
                ,comm::CIPtrStyle, l)
        {
        }

        // ctor with listener pointer and no reply interface
        // explicit so we don't magically construct proxies from integers
        explicit SystemEventsProxy(const uint32_t inst_cnt, comm::LifecycleListener* l=nullptr )
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_SERVMNGT_EXTENSIONS_SYSTEMEVENTS_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
                ,comm::CIPtrStyle
                ,l)
        {
        }

        // ctor with listener reference and no reply interface
        SystemEventsProxy(const comm::InstanceID& id, comm::LifecycleListener& l )
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
                ,comm::CIPtrStyle, &l)
        {
        }

        // ctor with listener pointer and no reply interface
        SystemEventsProxy(const uint32_t inst_cnt, comm::LifecycleListener& l )
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_SERVMNGT_EXTENSIONS_SYSTEMEVENTS_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
                ,comm::CIPtrStyle
                ,&l)
        {
        }

        // constructors  with a user passed object factory to receive notifications
        // ctor with listener pointer and no reply interface
        // explicit so we don't magically construct proxies from integers
        explicit SystemEventsProxy(const uint32_t inst_cnt
                                        ,const comm::ActiveObjectFactoryPtr& aof
                                        ,comm::LifecycleListener* l=nullptr )
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_SERVMNGT_EXTENSIONS_SYSTEMEVENTS_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
                ,aof
                ,comm::CIPtrStyle
                ,l
                )
        {
        }

        // ctor with listener pointer and no reply interface
        SystemEventsProxy(const uint32_t inst_cnt
                                ,const comm::ActiveObjectFactoryPtr& aof
                                ,comm::LifecycleListener& l )
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_SERVMNGT_EXTENSIONS_SYSTEMEVENTS_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
                ,aof
                ,comm::CIPtrStyle
                ,&l
                )
        {
        }
        // ctor with reply instance and listener pointers
        SystemEventsProxy(const comm::InstanceID& id, SystemEventsReply* r, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
                ,SystemEventsServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_SERVMNGT_EXTENSIONS_SYSTEMEVENTS_REPLY))
                    ,r
                    ,nullptr
                    )
                ,comm::CIPtrStyle
                ,l
                )
        {
        }

        // ctor with reply instance and listener pointers and ActiveObjectFactory
        SystemEventsProxy(const comm::InstanceID& id, SystemEventsReply* r, comm::ActiveObjectFactoryPtr aof, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
                ,SystemEventsServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_SERVMNGT_EXTENSIONS_SYSTEMEVENTS_REPLY))
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
        SystemEventsProxy(const uint32_t inst_cnt, SystemEventsReply* r, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_SERVMNGT_EXTENSIONS_SYSTEMEVENTS_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
                ,SystemEventsServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_SERVMNGT_EXTENSIONS_SYSTEMEVENTS_REPLY))
                    ,r
                    ,nullptr
                    )
                ,comm::CIPtrStyle
                ,l
                )
        {
        }

        // ctor with reply instance and listener pointers and ActiveObjectFactory
        SystemEventsProxy(const uint32_t inst_cnt, SystemEventsReply* r, comm::ActiveObjectFactoryPtr aof, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_SERVMNGT_EXTENSIONS_SYSTEMEVENTS_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
            ,SystemEventsServiceReplyRegistration(
                comm::InstanceID(comm::InterfaceID(BINARY_UUID_SERVMNGT_EXTENSIONS_SYSTEMEVENTS_REPLY))
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
        SystemEventsProxy(const comm::InstanceID& id, SystemEventsReply& r, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
                ,SystemEventsServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_SERVMNGT_EXTENSIONS_SYSTEMEVENTS_REPLY))
                    ,&r
                    ,nullptr
                    )
            ,comm::CIPtrStyle
            ,l
            )
        {
        }

        // ctor with reply instance reference and listener pointer and ActiveObjectFactory
        SystemEventsProxy(const comm::InstanceID& id, SystemEventsReply& r, comm::ActiveObjectFactoryPtr aof, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
            ,SystemEventsServiceReplyRegistration(
                comm::InstanceID(comm::InterfaceID(BINARY_UUID_SERVMNGT_EXTENSIONS_SYSTEMEVENTS_REPLY))
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
        SystemEventsProxy(const uint32_t inst_cnt, SystemEventsReply& r, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_SERVMNGT_EXTENSIONS_SYSTEMEVENTS_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
            ,SystemEventsServiceReplyRegistration(
                comm::InstanceID(comm::InterfaceID(BINARY_UUID_SERVMNGT_EXTENSIONS_SYSTEMEVENTS_REPLY))
                ,&r
                ,nullptr
                )
            ,comm::CIPtrStyle
            ,l
            )
        {
        }

        // ctor with reply instance reference and listener pointer and ActiveObjectFactory
        SystemEventsProxy(const uint32_t inst_cnt, SystemEventsReply& r, comm::ActiveObjectFactoryPtr aof, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(comm::InstanceID (comm::InterfaceID(BINARY_UUID_SERVMNGT_EXTENSIONS_SYSTEMEVENTS_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
            ,SystemEventsServiceReplyRegistration(
                comm::InstanceID(comm::InterfaceID(BINARY_UUID_SERVMNGT_EXTENSIONS_SYSTEMEVENTS_REPLY))
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
        SystemEventsProxy(const comm::InstanceID& id, SystemEventsReply& r, comm::LifecycleListener& l)
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
                ,SystemEventsServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_SERVMNGT_EXTENSIONS_SYSTEMEVENTS_REPLY))
                    ,&r
                    ,nullptr
                    )
            ,comm::CIPtrStyle
            ,&l
            )
        {
        }

        // ctor with reply instance and listener reference and ActiveObjectFactory
        SystemEventsProxy(const comm::InstanceID& id, SystemEventsReply& r, comm::ActiveObjectFactoryPtr aof, comm::LifecycleListener& l)
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
                ,SystemEventsServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_SERVMNGT_EXTENSIONS_SYSTEMEVENTS_REPLY))
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
        SystemEventsProxy(const uint32_t inst_cnt, SystemEventsReply& r, comm::LifecycleListener& l)
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_SERVMNGT_EXTENSIONS_SYSTEMEVENTS_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
                ,SystemEventsServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_SERVMNGT_EXTENSIONS_SYSTEMEVENTS_REPLY))
                    ,&r
                    ,nullptr
                    )
            ,comm::CIPtrStyle
            ,&l
            )
        {
        }

        // ctor with reply instance and listener reference and ActiveObjectFactory
        SystemEventsProxy(const uint32_t inst_cnt, SystemEventsReply& r, comm::ActiveObjectFactoryPtr aof, comm::LifecycleListener& l)
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_SERVMNGT_EXTENSIONS_SYSTEMEVENTS_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
                ,SystemEventsServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_SERVMNGT_EXTENSIONS_SYSTEMEVENTS_REPLY))
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
        SystemEventsProxy() {}
        // SystemEventsProxy is copy-assignable, default copy-ctor and assignment operator are fine
        // SystemEventsProxy is move-assignable when using C++11 or higher

        SystemEventsC& operator*() const
        {
            return *operator->();
        }

        SystemEventsC* operator->() const
        {
            return reinterpret_cast<SystemEventsC*>(getImpl());
        }

    private:
        static const comm::InterfaceKey& getIKey() {
            static comm::InterfaceKey ikey(0x00030000, 0x0001, 0x6000, 0x0000, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00);
            return ikey;
        }
        static const std::string& getIName() {
            static const std::string iname{"servmngt.extensions.SystemEvents"};
            return iname;
        }
        static const comm::InterfaceKey& getRIKey() {
            // semver is not different in request/reply direction
            return SystemEventsProxy::getIKey();
        }

        // proxy/stub factory init for the client side
        PROXY_EXPORT static const ProxyStubFactory* clientInitFactory();

    };

}//namespace servmngt
}//namespace extensions
#endif// SERVMNGT_EXTENSIONS_SYSTEMEVENTS_PROXY_HXX
