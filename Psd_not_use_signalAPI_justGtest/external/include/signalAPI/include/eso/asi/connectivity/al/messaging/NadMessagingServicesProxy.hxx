/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Proxy_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_MESSAGING_NADMESSAGINGSERVICES_PROXY_HXX
#define ASI_CONNECTIVITY_AL_MESSAGING_NADMESSAGINGSERVICES_PROXY_HXX

#include <comm/ProxyStubFactory.hxx>
#include <comm/Proxy.hxx>
#include <comm/commidltypes.hxx>        // used for PROXY_EXPORT macro
#include <asi/connectivity/al/messaging/StructSimInfo.hxx>
#include <asi/connectivity/al/messaging/Definitions.hxx>
#include <asi/connectivity/al/messaging/NadMessagingServicesC.hxx>
#include <asi/connectivity/al/messaging/NadMessagingServicesReply.hxx>
#include <asi/connectivity/al/messaging/NadMessagingServicesServiceReplyRegistration.hxx>

#include <string>

namespace asi
{
namespace connectivity
{
namespace al
{
namespace messaging
{

    /**
        \brief A proxy for services that implement the messaging::NadMessagingServices interface.
    */
    class NadMessagingServicesProxy  : public comm::Proxy
    {
    public:
        // ctor with listener pointer and no reply interface
        NadMessagingServicesProxy(const comm::InstanceID& _id, comm::LifecycleListener* l=nullptr )
        : Proxy(comm::Proxy::IdentityArgs(_id, getIKey(), getIName())
                ,clientInitFactory
                ,comm::CIPtrStyle, l)
        {
        }

        // ctor with listener pointer and no reply interface
        // explicit so we don't magically construct proxies from integers
        explicit NadMessagingServicesProxy(const uint32_t inst_cnt, comm::LifecycleListener* l=nullptr )
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_AL_MESSAGING_NADMESSAGINGSERVICES_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
                ,comm::CIPtrStyle
                ,l)
        {
        }

        // ctor with listener reference and no reply interface
        NadMessagingServicesProxy(const comm::InstanceID& id, comm::LifecycleListener& l )
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
                ,comm::CIPtrStyle, &l)
        {
        }

        // ctor with listener pointer and no reply interface
        NadMessagingServicesProxy(const uint32_t inst_cnt, comm::LifecycleListener& l )
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_AL_MESSAGING_NADMESSAGINGSERVICES_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
                ,comm::CIPtrStyle
                ,&l)
        {
        }

        // constructors  with a user passed object factory to receive notifications
        // ctor with listener pointer and no reply interface
        // explicit so we don't magically construct proxies from integers
        explicit NadMessagingServicesProxy(const uint32_t inst_cnt
                                        ,const comm::ActiveObjectFactoryPtr& aof
                                        ,comm::LifecycleListener* l=nullptr )
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_AL_MESSAGING_NADMESSAGINGSERVICES_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
                ,aof
                ,comm::CIPtrStyle
                ,l
                )
        {
        }

        // ctor with listener pointer and no reply interface
        NadMessagingServicesProxy(const uint32_t inst_cnt
                                ,const comm::ActiveObjectFactoryPtr& aof
                                ,comm::LifecycleListener& l )
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_AL_MESSAGING_NADMESSAGINGSERVICES_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
                ,aof
                ,comm::CIPtrStyle
                ,&l
                )
        {
        }
        // ctor with reply instance and listener pointers
        NadMessagingServicesProxy(const comm::InstanceID& id, NadMessagingServicesReply* r, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
                ,NadMessagingServicesServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_AL_MESSAGING_NADMESSAGINGSERVICES_REPLY))
                    ,r
                    ,nullptr
                    )
                ,comm::CIPtrStyle
                ,l
                )
        {
        }

        // ctor with reply instance and listener pointers and ActiveObjectFactory
        NadMessagingServicesProxy(const comm::InstanceID& id, NadMessagingServicesReply* r, comm::ActiveObjectFactoryPtr aof, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
                ,NadMessagingServicesServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_AL_MESSAGING_NADMESSAGINGSERVICES_REPLY))
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
        NadMessagingServicesProxy(const uint32_t inst_cnt, NadMessagingServicesReply* r, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_AL_MESSAGING_NADMESSAGINGSERVICES_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
                ,NadMessagingServicesServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_AL_MESSAGING_NADMESSAGINGSERVICES_REPLY))
                    ,r
                    ,nullptr
                    )
                ,comm::CIPtrStyle
                ,l
                )
        {
        }

        // ctor with reply instance and listener pointers and ActiveObjectFactory
        NadMessagingServicesProxy(const uint32_t inst_cnt, NadMessagingServicesReply* r, comm::ActiveObjectFactoryPtr aof, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_AL_MESSAGING_NADMESSAGINGSERVICES_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
            ,NadMessagingServicesServiceReplyRegistration(
                comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_AL_MESSAGING_NADMESSAGINGSERVICES_REPLY))
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
        NadMessagingServicesProxy(const comm::InstanceID& id, NadMessagingServicesReply& r, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
                ,NadMessagingServicesServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_AL_MESSAGING_NADMESSAGINGSERVICES_REPLY))
                    ,&r
                    ,nullptr
                    )
            ,comm::CIPtrStyle
            ,l
            )
        {
        }

        // ctor with reply instance reference and listener pointer and ActiveObjectFactory
        NadMessagingServicesProxy(const comm::InstanceID& id, NadMessagingServicesReply& r, comm::ActiveObjectFactoryPtr aof, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
            ,NadMessagingServicesServiceReplyRegistration(
                comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_AL_MESSAGING_NADMESSAGINGSERVICES_REPLY))
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
        NadMessagingServicesProxy(const uint32_t inst_cnt, NadMessagingServicesReply& r, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_AL_MESSAGING_NADMESSAGINGSERVICES_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
            ,NadMessagingServicesServiceReplyRegistration(
                comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_AL_MESSAGING_NADMESSAGINGSERVICES_REPLY))
                ,&r
                ,nullptr
                )
            ,comm::CIPtrStyle
            ,l
            )
        {
        }

        // ctor with reply instance reference and listener pointer and ActiveObjectFactory
        NadMessagingServicesProxy(const uint32_t inst_cnt, NadMessagingServicesReply& r, comm::ActiveObjectFactoryPtr aof, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_AL_MESSAGING_NADMESSAGINGSERVICES_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
            ,NadMessagingServicesServiceReplyRegistration(
                comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_AL_MESSAGING_NADMESSAGINGSERVICES_REPLY))
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
        NadMessagingServicesProxy(const comm::InstanceID& id, NadMessagingServicesReply& r, comm::LifecycleListener& l)
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
                ,NadMessagingServicesServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_AL_MESSAGING_NADMESSAGINGSERVICES_REPLY))
                    ,&r
                    ,nullptr
                    )
            ,comm::CIPtrStyle
            ,&l
            )
        {
        }

        // ctor with reply instance and listener reference and ActiveObjectFactory
        NadMessagingServicesProxy(const comm::InstanceID& id, NadMessagingServicesReply& r, comm::ActiveObjectFactoryPtr aof, comm::LifecycleListener& l)
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
                ,NadMessagingServicesServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_AL_MESSAGING_NADMESSAGINGSERVICES_REPLY))
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
        NadMessagingServicesProxy(const uint32_t inst_cnt, NadMessagingServicesReply& r, comm::LifecycleListener& l)
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_AL_MESSAGING_NADMESSAGINGSERVICES_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
                ,NadMessagingServicesServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_AL_MESSAGING_NADMESSAGINGSERVICES_REPLY))
                    ,&r
                    ,nullptr
                    )
            ,comm::CIPtrStyle
            ,&l
            )
        {
        }

        // ctor with reply instance and listener reference and ActiveObjectFactory
        NadMessagingServicesProxy(const uint32_t inst_cnt, NadMessagingServicesReply& r, comm::ActiveObjectFactoryPtr aof, comm::LifecycleListener& l)
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_AL_MESSAGING_NADMESSAGINGSERVICES_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
                ,NadMessagingServicesServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_AL_MESSAGING_NADMESSAGINGSERVICES_REPLY))
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
        NadMessagingServicesProxy() {}
        // NadMessagingServicesProxy is copy-assignable, default copy-ctor and assignment operator are fine
        // NadMessagingServicesProxy is move-assignable when using C++11 or higher

        NadMessagingServicesC& operator*() const
        {
            return *operator->();
        }

        NadMessagingServicesC* operator->() const
        {
            return reinterpret_cast<NadMessagingServicesC*>(getImpl());
        }

    private:
        static const comm::InterfaceKey& getIKey() {
            static comm::InterfaceKey ikey(0x00020000, 0x0001, 0x6000, 0x0000, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00);
            return ikey;
        }
        static const std::string& getIName() {
            static const std::string iname{"asi.connectivity.al.messaging.NadMessagingServices"};
            return iname;
        }
        static const comm::InterfaceKey& getRIKey() {
            // semver is not different in request/reply direction
            return NadMessagingServicesProxy::getIKey();
        }

        // proxy/stub factory init for the client side
        PROXY_EXPORT static const ProxyStubFactory* clientInitFactory();

    };

}//namespace asi
}//namespace connectivity
}//namespace al
}//namespace messaging
#endif// ASI_CONNECTIVITY_AL_MESSAGING_NADMESSAGINGSERVICES_PROXY_HXX
