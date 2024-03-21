/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleProxy_hxx.tmpl
*/
#ifndef SERVMNGT_EXTENSIONS_SERVICEMANAGEREVENTS_PROXY_CSTYLE_HXX
#define SERVMNGT_EXTENSIONS_SERVICEMANAGEREVENTS_PROXY_CSTYLE_HXX

#include <comm/ProxyStubFactory.hxx>
#include <comm/Proxy.hxx>
#include <comm/commidltypes.hxx>        // used for PROXY_EXPORT macro
#include <servmngt/extensions/cstyle/StructWatchdogMissedEvent.hxx>
#include <servmngt/extensions/cstyle/Definitions.hxx>
#include <servmngt/extensions/cstyle/ServiceManagerEventsC.hxx>
#include <servmngt/extensions/cstyle/ServiceManagerEventsReply.hxx>
#include <servmngt/extensions/cstyle/ServiceManagerEventsServiceReplyRegistration.hxx>

#include <string>

namespace servmngt
{
namespace extensions
{

namespace cstyle
{
    /**
        \brief A proxy for services that implement the extensions::ServiceManagerEvents interface.
    */
    class ServiceManagerEventsProxy  : public comm::Proxy
    {
    public:
        // ctor with listener pointer and no reply interface
        ServiceManagerEventsProxy(const comm::InstanceID& _id, comm::LifecycleListener* l=nullptr )
        : Proxy(comm::Proxy::IdentityArgs(_id, getIKey(), getIName())
                ,clientInitFactory
                ,comm::CStyle, l)
        {
        }

        // ctor with listener pointer and no reply interface
        // explicit so we don't magically construct proxies from integers
        explicit ServiceManagerEventsProxy(const uint32_t inst_cnt, comm::LifecycleListener* l=nullptr )
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_SERVMNGT_EXTENSIONS_SERVICEMANAGEREVENTS_REQUEST), inst_cnt),
                getIKey(), getIName())
                ,clientInitFactory
                ,comm::CStyle
                ,l)
        {
        }

        // ctor with listener reference and no reply interface
        ServiceManagerEventsProxy(const comm::InstanceID& id, comm::LifecycleListener& l )
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
                ,comm::CStyle, &l)
        {
        }

        // ctor with listener pointer and no reply interface
        ServiceManagerEventsProxy(const uint32_t inst_cnt, comm::LifecycleListener& l )
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_SERVMNGT_EXTENSIONS_SERVICEMANAGEREVENTS_REQUEST), inst_cnt)
                , getIKey(), getIName())
                ,clientInitFactory
                ,comm::CStyle
                ,&l)
        {
        }

        // constructors  with a user passed object factory to receive notifications
        // ctor with listener pointer and no reply interface
        // explicit so we don't magically construct proxies from integers
        explicit ServiceManagerEventsProxy(const uint32_t inst_cnt
                                        ,const comm::ActiveObjectFactoryPtr& aof
                                        ,comm::LifecycleListener* l=nullptr )
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_SERVMNGT_EXTENSIONS_SERVICEMANAGEREVENTS_REQUEST), inst_cnt),
                getIKey(), getIName())
                ,clientInitFactory
                ,aof
                ,comm::CStyle
                ,l)
        {
        }

        // ctor with listener pointer and no reply interface
        ServiceManagerEventsProxy(const uint32_t inst_cnt
                                ,const comm::ActiveObjectFactoryPtr& aof
                                ,comm::LifecycleListener& l )
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_SERVMNGT_EXTENSIONS_SERVICEMANAGEREVENTS_REQUEST), inst_cnt)
                , getIKey(), getIName())
                ,clientInitFactory
                ,aof
                ,comm::CStyle
                ,&l)
        {
        }

        // ctor with reply instance and listener pointers
        ServiceManagerEventsProxy(const comm::InstanceID& id, ServiceManagerEventsReply* r, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
                ,ServiceManagerEventsServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_SERVMNGT_EXTENSIONS_SERVICEMANAGEREVENTS_REPLY))
                    ,r
                    ,nullptr
                    )
                ,comm::CStyle
                ,l)
        {
        }

        // ctor with reply instance and listener pointers and ActiveObjectFactory
        ServiceManagerEventsProxy(const comm::InstanceID& id, ServiceManagerEventsReply* r, comm::ActiveObjectFactoryPtr aof, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
                ,ServiceManagerEventsServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_SERVMNGT_EXTENSIONS_SERVICEMANAGEREVENTS_REPLY))
                    ,r
                    ,nullptr
                    ,aof
                    )
                ,comm::CStyle
                ,l)
        {
        }

        // ctor with reply instance and listener pointers
        ServiceManagerEventsProxy(const uint32_t inst_cnt, ServiceManagerEventsReply* r, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_SERVMNGT_EXTENSIONS_SERVICEMANAGEREVENTS_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
                ,ServiceManagerEventsServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_SERVMNGT_EXTENSIONS_SERVICEMANAGEREVENTS_REPLY))
                    ,r
                    ,nullptr
                    )
                ,comm::CStyle
                ,l)
        {
        }

        // ctor with reply instance and listener pointers and ActiveObjectFactory
        ServiceManagerEventsProxy(const uint32_t inst_cnt, ServiceManagerEventsReply* r, comm::ActiveObjectFactoryPtr aof, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_SERVMNGT_EXTENSIONS_SERVICEMANAGEREVENTS_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
            ,ServiceManagerEventsServiceReplyRegistration(
                comm::InstanceID(comm::InterfaceID(BINARY_UUID_SERVMNGT_EXTENSIONS_SERVICEMANAGEREVENTS_REPLY))
                ,r
                ,nullptr
                ,aof
                )
            ,comm::CStyle
            ,l)
        {
        }

        // ctor with reply instance reference and listener pointer
        ServiceManagerEventsProxy(const comm::InstanceID& id, ServiceManagerEventsReply& r, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
                ,ServiceManagerEventsServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_SERVMNGT_EXTENSIONS_SERVICEMANAGEREVENTS_REPLY))
                    ,&r
                    ,nullptr
                    )
            ,comm::CStyle
            ,l)
        {
        }

        // ctor with reply instance reference and listener pointer and ActiveObjectFactory
        ServiceManagerEventsProxy(const comm::InstanceID& id, ServiceManagerEventsReply& r, comm::ActiveObjectFactoryPtr aof, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
            ,ServiceManagerEventsServiceReplyRegistration(
                comm::InstanceID(comm::InterfaceID(BINARY_UUID_SERVMNGT_EXTENSIONS_SERVICEMANAGEREVENTS_REPLY))
                ,&r
                ,nullptr
                ,aof
                )
            ,comm::CStyle
            ,l)
        {
        }

        // ctor with reply instance reference and listener pointer
        ServiceManagerEventsProxy(const uint32_t inst_cnt, ServiceManagerEventsReply& r, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_SERVMNGT_EXTENSIONS_SERVICEMANAGEREVENTS_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
            ,ServiceManagerEventsServiceReplyRegistration(
                comm::InstanceID(comm::InterfaceID(BINARY_UUID_SERVMNGT_EXTENSIONS_SERVICEMANAGEREVENTS_REPLY))
                ,&r
                ,nullptr
                )
            ,comm::CStyle
            ,l)
        {
        }

        // ctor with reply instance reference and listener pointer and ActiveObjectFactory
        ServiceManagerEventsProxy(const uint32_t inst_cnt, ServiceManagerEventsReply& r, comm::ActiveObjectFactoryPtr aof, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(comm::InstanceID (comm::InterfaceID(BINARY_UUID_SERVMNGT_EXTENSIONS_SERVICEMANAGEREVENTS_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
            ,ServiceManagerEventsServiceReplyRegistration(
                comm::InstanceID(comm::InterfaceID(BINARY_UUID_SERVMNGT_EXTENSIONS_SERVICEMANAGEREVENTS_REPLY))
                ,&r
                ,nullptr
                ,aof
                )
            ,comm::CStyle
            ,l)
        {
        }

        // ctor with reply instance and listener reference
        ServiceManagerEventsProxy(const comm::InstanceID& id, ServiceManagerEventsReply& r, comm::LifecycleListener& l)
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
                ,ServiceManagerEventsServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_SERVMNGT_EXTENSIONS_SERVICEMANAGEREVENTS_REPLY))
                    ,&r
                    ,nullptr
                    )
            ,comm::CStyle
            ,&l)
        {
        }

        // ctor with reply instance and listener reference and ActiveObjectFactory
        ServiceManagerEventsProxy(const comm::InstanceID& id, ServiceManagerEventsReply& r, comm::ActiveObjectFactoryPtr aof, comm::LifecycleListener& l)
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
                ,ServiceManagerEventsServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_SERVMNGT_EXTENSIONS_SERVICEMANAGEREVENTS_REPLY))
                    ,&r
                    ,nullptr
                    ,aof
                    )
            ,comm::CStyle
            ,&l)
        {
        }

        // ctor with reply instance and listener reference
        ServiceManagerEventsProxy(const uint32_t inst_cnt, ServiceManagerEventsReply& r, comm::LifecycleListener& l)
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_SERVMNGT_EXTENSIONS_SERVICEMANAGEREVENTS_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
                ,ServiceManagerEventsServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_SERVMNGT_EXTENSIONS_SERVICEMANAGEREVENTS_REPLY))
                    ,&r
                    ,nullptr
                    )
            ,comm::CStyle
            ,&l)
        {
        }

        // ctor with reply instance and listener reference and ActiveObjectFactory
        ServiceManagerEventsProxy(const uint32_t inst_cnt, ServiceManagerEventsReply& r, comm::ActiveObjectFactoryPtr aof, comm::LifecycleListener& l)
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_SERVMNGT_EXTENSIONS_SERVICEMANAGEREVENTS_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
                ,ServiceManagerEventsServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_SERVMNGT_EXTENSIONS_SERVICEMANAGEREVENTS_REPLY))
                    ,&r
                    ,nullptr
                    ,aof
                    )
            ,comm::CStyle
            ,&l)
        {
        }

        // default ctor
        ServiceManagerEventsProxy() {}
        // ServiceManagerEventsProxy is copy-assignable, default copy-ctor and assignment operator are fine
        // ServiceManagerEventsProxy is move-assignable when using C++11 or higher

        ServiceManagerEventsC& operator*() const
        {
            return *operator->();
        }

        ServiceManagerEventsC* operator->() const
        {
            return reinterpret_cast<ServiceManagerEventsC*>(getImpl());
        }

    private:

        static const comm::InterfaceKey& getIKey() {
            static comm::InterfaceKey ikey(0x00030000, 0x0001, 0x6000, 0x0000, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00);
            return ikey;
        }
        static const std::string& getIName() {
            static const std::string& iname{"servmngt.extensions.ServiceManagerEvents"};
            return iname;
        }
        static const comm::InterfaceKey& getRIKey() {
            // semver is not different in request/reply direction
            return ServiceManagerEventsProxy::getIKey();
        }
        // proxy/stub factory init for the client side
        PROXY_EXPORT static const ProxyStubFactory* clientInitFactory();

    };

} // namespace cstyle
}//namespace servmngt
}//namespace extensions
#endif// SERVMNGT_EXTENSIONS_SERVICEMANAGEREVENTS_PROXY_CSTYLE_HXX
