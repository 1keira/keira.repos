/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Proxy_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_OOC_POWERMANAGEMENTSERVICE_PROXY_HXX
#define ASI_CONNECTIVITY_OOC_POWERMANAGEMENTSERVICE_PROXY_HXX

#include <comm/ProxyStubFactory.hxx>
#include <comm/Proxy.hxx>
#include <comm/commidltypes.hxx>        // used for PROXY_EXPORT macro
#include <asi/connectivity/ooc/Definitions.hxx>
#include <asi/connectivity/ooc/PowerManagementServiceC.hxx>
#include <asi/connectivity/ooc/PowerManagementServiceReply.hxx>
#include <asi/connectivity/ooc/PowerManagementServiceServiceReplyRegistration.hxx>

#include <string>

namespace asi
{
namespace connectivity
{
namespace ooc
{

    /**
        \brief A proxy for services that implement the ooc::PowerManagementService interface.
    */
    class PowerManagementServiceProxy  : public comm::Proxy
    {
    public:
        // ctor with listener pointer and no reply interface
        PowerManagementServiceProxy(const comm::InstanceID& _id, comm::LifecycleListener* l=nullptr )
        : Proxy(comm::Proxy::IdentityArgs(_id, getIKey(), getIName())
                ,clientInitFactory
                ,comm::CIPtrStyle, l)
        {
        }

        // ctor with listener pointer and no reply interface
        // explicit so we don't magically construct proxies from integers
        explicit PowerManagementServiceProxy(const uint32_t inst_cnt, comm::LifecycleListener* l=nullptr )
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_OOC_POWERMANAGEMENTSERVICE_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
                ,comm::CIPtrStyle
                ,l)
        {
        }

        // ctor with listener reference and no reply interface
        PowerManagementServiceProxy(const comm::InstanceID& id, comm::LifecycleListener& l )
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
                ,comm::CIPtrStyle, &l)
        {
        }

        // ctor with listener pointer and no reply interface
        PowerManagementServiceProxy(const uint32_t inst_cnt, comm::LifecycleListener& l )
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_OOC_POWERMANAGEMENTSERVICE_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
                ,comm::CIPtrStyle
                ,&l)
        {
        }

        // constructors  with a user passed object factory to receive notifications
        // ctor with listener pointer and no reply interface
        // explicit so we don't magically construct proxies from integers
        explicit PowerManagementServiceProxy(const uint32_t inst_cnt
                                        ,const comm::ActiveObjectFactoryPtr& aof
                                        ,comm::LifecycleListener* l=nullptr )
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_OOC_POWERMANAGEMENTSERVICE_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
                ,aof
                ,comm::CIPtrStyle
                ,l
                )
        {
        }

        // ctor with listener pointer and no reply interface
        PowerManagementServiceProxy(const uint32_t inst_cnt
                                ,const comm::ActiveObjectFactoryPtr& aof
                                ,comm::LifecycleListener& l )
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_OOC_POWERMANAGEMENTSERVICE_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
                ,aof
                ,comm::CIPtrStyle
                ,&l
                )
        {
        }
        // ctor with reply instance and listener pointers
        PowerManagementServiceProxy(const comm::InstanceID& id, PowerManagementServiceReply* r, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
                ,PowerManagementServiceServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_OOC_POWERMANAGEMENTSERVICE_REPLY))
                    ,r
                    ,nullptr
                    )
                ,comm::CIPtrStyle
                ,l
                )
        {
        }

        // ctor with reply instance and listener pointers and ActiveObjectFactory
        PowerManagementServiceProxy(const comm::InstanceID& id, PowerManagementServiceReply* r, comm::ActiveObjectFactoryPtr aof, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
                ,PowerManagementServiceServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_OOC_POWERMANAGEMENTSERVICE_REPLY))
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
        PowerManagementServiceProxy(const uint32_t inst_cnt, PowerManagementServiceReply* r, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_OOC_POWERMANAGEMENTSERVICE_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
                ,PowerManagementServiceServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_OOC_POWERMANAGEMENTSERVICE_REPLY))
                    ,r
                    ,nullptr
                    )
                ,comm::CIPtrStyle
                ,l
                )
        {
        }

        // ctor with reply instance and listener pointers and ActiveObjectFactory
        PowerManagementServiceProxy(const uint32_t inst_cnt, PowerManagementServiceReply* r, comm::ActiveObjectFactoryPtr aof, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_OOC_POWERMANAGEMENTSERVICE_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
            ,PowerManagementServiceServiceReplyRegistration(
                comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_OOC_POWERMANAGEMENTSERVICE_REPLY))
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
        PowerManagementServiceProxy(const comm::InstanceID& id, PowerManagementServiceReply& r, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
                ,PowerManagementServiceServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_OOC_POWERMANAGEMENTSERVICE_REPLY))
                    ,&r
                    ,nullptr
                    )
            ,comm::CIPtrStyle
            ,l
            )
        {
        }

        // ctor with reply instance reference and listener pointer and ActiveObjectFactory
        PowerManagementServiceProxy(const comm::InstanceID& id, PowerManagementServiceReply& r, comm::ActiveObjectFactoryPtr aof, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
            ,PowerManagementServiceServiceReplyRegistration(
                comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_OOC_POWERMANAGEMENTSERVICE_REPLY))
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
        PowerManagementServiceProxy(const uint32_t inst_cnt, PowerManagementServiceReply& r, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_OOC_POWERMANAGEMENTSERVICE_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
            ,PowerManagementServiceServiceReplyRegistration(
                comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_OOC_POWERMANAGEMENTSERVICE_REPLY))
                ,&r
                ,nullptr
                )
            ,comm::CIPtrStyle
            ,l
            )
        {
        }

        // ctor with reply instance reference and listener pointer and ActiveObjectFactory
        PowerManagementServiceProxy(const uint32_t inst_cnt, PowerManagementServiceReply& r, comm::ActiveObjectFactoryPtr aof, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_OOC_POWERMANAGEMENTSERVICE_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
            ,PowerManagementServiceServiceReplyRegistration(
                comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_OOC_POWERMANAGEMENTSERVICE_REPLY))
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
        PowerManagementServiceProxy(const comm::InstanceID& id, PowerManagementServiceReply& r, comm::LifecycleListener& l)
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
                ,PowerManagementServiceServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_OOC_POWERMANAGEMENTSERVICE_REPLY))
                    ,&r
                    ,nullptr
                    )
            ,comm::CIPtrStyle
            ,&l
            )
        {
        }

        // ctor with reply instance and listener reference and ActiveObjectFactory
        PowerManagementServiceProxy(const comm::InstanceID& id, PowerManagementServiceReply& r, comm::ActiveObjectFactoryPtr aof, comm::LifecycleListener& l)
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
                ,PowerManagementServiceServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_OOC_POWERMANAGEMENTSERVICE_REPLY))
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
        PowerManagementServiceProxy(const uint32_t inst_cnt, PowerManagementServiceReply& r, comm::LifecycleListener& l)
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_OOC_POWERMANAGEMENTSERVICE_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
                ,PowerManagementServiceServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_OOC_POWERMANAGEMENTSERVICE_REPLY))
                    ,&r
                    ,nullptr
                    )
            ,comm::CIPtrStyle
            ,&l
            )
        {
        }

        // ctor with reply instance and listener reference and ActiveObjectFactory
        PowerManagementServiceProxy(const uint32_t inst_cnt, PowerManagementServiceReply& r, comm::ActiveObjectFactoryPtr aof, comm::LifecycleListener& l)
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_OOC_POWERMANAGEMENTSERVICE_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
                ,PowerManagementServiceServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_OOC_POWERMANAGEMENTSERVICE_REPLY))
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
        PowerManagementServiceProxy() {}
        // PowerManagementServiceProxy is copy-assignable, default copy-ctor and assignment operator are fine
        // PowerManagementServiceProxy is move-assignable when using C++11 or higher

        PowerManagementServiceC& operator*() const
        {
            return *operator->();
        }

        PowerManagementServiceC* operator->() const
        {
            return reinterpret_cast<PowerManagementServiceC*>(getImpl());
        }

    private:
        static const comm::InterfaceKey& getIKey() {
            static comm::InterfaceKey ikey(0x00010000, 0x0001, 0x6000, 0x0000, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01);
            return ikey;
        }
        static const std::string& getIName() {
            static const std::string iname{"asi.connectivity.ooc.PowerManagementService"};
            return iname;
        }
        static const comm::InterfaceKey& getRIKey() {
            // semver is not different in request/reply direction
            return PowerManagementServiceProxy::getIKey();
        }

        // proxy/stub factory init for the client side
        PROXY_EXPORT static const ProxyStubFactory* clientInitFactory();

    };

}//namespace asi
}//namespace connectivity
}//namespace ooc
#endif// ASI_CONNECTIVITY_OOC_POWERMANAGEMENTSERVICE_PROXY_HXX
