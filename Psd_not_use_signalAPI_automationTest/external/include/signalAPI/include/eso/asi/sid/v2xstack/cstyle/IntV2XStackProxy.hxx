/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleProxy_hxx.tmpl
*/
#ifndef ASI_SID_V2XSTACK_INTV2XSTACK_PROXY_CSTYLE_HXX
#define ASI_SID_V2XSTACK_INTV2XSTACK_PROXY_CSTYLE_HXX

#include <comm/ProxyStubFactory.hxx>
#include <comm/Proxy.hxx>
#include <comm/commidltypes.hxx>        // used for PROXY_EXPORT macro
#include <asi/sid/v2xstack/cstyle/StructBlinkmodi02Struct.hxx>
#include <asi/sid/v2xstack/cstyle/StructEBKV03AuthStruct.hxx>
#include <asi/sid/v2xstack/cstyle/StructESC50Struct.hxx>
#include <asi/sid/v2xstack/cstyle/StructESC51AuthStruct.hxx>
#include <asi/sid/v2xstack/cstyle/StructESP21Struct.hxx>
#include <asi/sid/v2xstack/cstyle/StructESP24Struct.hxx>
#include <asi/sid/v2xstack/cstyle/StructGetriebe11Struct.hxx>
#include <asi/sid/v2xstack/cstyle/StructKlemmenStatus01Struct.hxx>
#include <asi/sid/v2xstack/cstyle/StructLWI01Struct.hxx>
#include <asi/sid/v2xstack/cstyle/StructLichtAnf01Struct.hxx>
#include <asi/sid/v2xstack/cstyle/StructLichtvorne01Struct.hxx>
#include <asi/sid/v2xstack/cstyle/StructMotor14Struct.hxx>
#include <asi/sid/v2xstack/cstyle/StructPersonalisierung01Struct.hxx>
#include <asi/sid/v2xstack/cstyle/StructVMM02AuthStruct.hxx>
#include <asi/sid/v2xstack/cstyle/Definitions.hxx>
#include <asi/sid/v2xstack/cstyle/IntV2XStackC.hxx>
#include <asi/sid/v2xstack/cstyle/IntV2XStackReply.hxx>
#include <asi/sid/v2xstack/cstyle/IntV2XStackServiceReplyRegistration.hxx>

#include <string>

namespace asi
{
namespace sid
{
namespace v2xstack
{

namespace cstyle
{
    /**
        \brief A proxy for services that implement the v2xstack::IntV2XStack interface.
    */
    class IntV2XStackProxy  : public comm::Proxy
    {
    public:
        // ctor with listener pointer and no reply interface
        IntV2XStackProxy(const comm::InstanceID& _id, comm::LifecycleListener* l=nullptr )
        : Proxy(comm::Proxy::IdentityArgs(_id, getIKey(), getIName())
                ,clientInitFactory
                ,comm::CStyle, l)
        {
        }

        // ctor with listener pointer and no reply interface
        // explicit so we don't magically construct proxies from integers
        explicit IntV2XStackProxy(const uint32_t inst_cnt, comm::LifecycleListener* l=nullptr )
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_SID_V2XSTACK_INTV2XSTACK_REQUEST), inst_cnt),
                getIKey(), getIName())
                ,clientInitFactory
                ,comm::CStyle
                ,l)
        {
        }

        // ctor with listener reference and no reply interface
        IntV2XStackProxy(const comm::InstanceID& id, comm::LifecycleListener& l )
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
                ,comm::CStyle, &l)
        {
        }

        // ctor with listener pointer and no reply interface
        IntV2XStackProxy(const uint32_t inst_cnt, comm::LifecycleListener& l )
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_SID_V2XSTACK_INTV2XSTACK_REQUEST), inst_cnt)
                , getIKey(), getIName())
                ,clientInitFactory
                ,comm::CStyle
                ,&l)
        {
        }

        // constructors  with a user passed object factory to receive notifications
        // ctor with listener pointer and no reply interface
        // explicit so we don't magically construct proxies from integers
        explicit IntV2XStackProxy(const uint32_t inst_cnt
                                        ,const comm::ActiveObjectFactoryPtr& aof
                                        ,comm::LifecycleListener* l=nullptr )
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_SID_V2XSTACK_INTV2XSTACK_REQUEST), inst_cnt),
                getIKey(), getIName())
                ,clientInitFactory
                ,aof
                ,comm::CStyle
                ,l)
        {
        }

        // ctor with listener pointer and no reply interface
        IntV2XStackProxy(const uint32_t inst_cnt
                                ,const comm::ActiveObjectFactoryPtr& aof
                                ,comm::LifecycleListener& l )
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_SID_V2XSTACK_INTV2XSTACK_REQUEST), inst_cnt)
                , getIKey(), getIName())
                ,clientInitFactory
                ,aof
                ,comm::CStyle
                ,&l)
        {
        }

        // ctor with reply instance and listener pointers
        IntV2XStackProxy(const comm::InstanceID& id, IntV2XStackReply* r, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
                ,IntV2XStackServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_SID_V2XSTACK_INTV2XSTACK_REPLY))
                    ,r
                    ,nullptr
                    )
                ,comm::CStyle
                ,l)
        {
        }

        // ctor with reply instance and listener pointers and ActiveObjectFactory
        IntV2XStackProxy(const comm::InstanceID& id, IntV2XStackReply* r, comm::ActiveObjectFactoryPtr aof, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
                ,IntV2XStackServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_SID_V2XSTACK_INTV2XSTACK_REPLY))
                    ,r
                    ,nullptr
                    ,aof
                    )
                ,comm::CStyle
                ,l)
        {
        }

        // ctor with reply instance and listener pointers
        IntV2XStackProxy(const uint32_t inst_cnt, IntV2XStackReply* r, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_SID_V2XSTACK_INTV2XSTACK_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
                ,IntV2XStackServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_SID_V2XSTACK_INTV2XSTACK_REPLY))
                    ,r
                    ,nullptr
                    )
                ,comm::CStyle
                ,l)
        {
        }

        // ctor with reply instance and listener pointers and ActiveObjectFactory
        IntV2XStackProxy(const uint32_t inst_cnt, IntV2XStackReply* r, comm::ActiveObjectFactoryPtr aof, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_SID_V2XSTACK_INTV2XSTACK_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
            ,IntV2XStackServiceReplyRegistration(
                comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_SID_V2XSTACK_INTV2XSTACK_REPLY))
                ,r
                ,nullptr
                ,aof
                )
            ,comm::CStyle
            ,l)
        {
        }

        // ctor with reply instance reference and listener pointer
        IntV2XStackProxy(const comm::InstanceID& id, IntV2XStackReply& r, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
                ,IntV2XStackServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_SID_V2XSTACK_INTV2XSTACK_REPLY))
                    ,&r
                    ,nullptr
                    )
            ,comm::CStyle
            ,l)
        {
        }

        // ctor with reply instance reference and listener pointer and ActiveObjectFactory
        IntV2XStackProxy(const comm::InstanceID& id, IntV2XStackReply& r, comm::ActiveObjectFactoryPtr aof, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
            ,IntV2XStackServiceReplyRegistration(
                comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_SID_V2XSTACK_INTV2XSTACK_REPLY))
                ,&r
                ,nullptr
                ,aof
                )
            ,comm::CStyle
            ,l)
        {
        }

        // ctor with reply instance reference and listener pointer
        IntV2XStackProxy(const uint32_t inst_cnt, IntV2XStackReply& r, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_SID_V2XSTACK_INTV2XSTACK_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
            ,IntV2XStackServiceReplyRegistration(
                comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_SID_V2XSTACK_INTV2XSTACK_REPLY))
                ,&r
                ,nullptr
                )
            ,comm::CStyle
            ,l)
        {
        }

        // ctor with reply instance reference and listener pointer and ActiveObjectFactory
        IntV2XStackProxy(const uint32_t inst_cnt, IntV2XStackReply& r, comm::ActiveObjectFactoryPtr aof, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_SID_V2XSTACK_INTV2XSTACK_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
            ,IntV2XStackServiceReplyRegistration(
                comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_SID_V2XSTACK_INTV2XSTACK_REPLY))
                ,&r
                ,nullptr
                ,aof
                )
            ,comm::CStyle
            ,l)
        {
        }

        // ctor with reply instance and listener reference
        IntV2XStackProxy(const comm::InstanceID& id, IntV2XStackReply& r, comm::LifecycleListener& l)
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
                ,IntV2XStackServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_SID_V2XSTACK_INTV2XSTACK_REPLY))
                    ,&r
                    ,nullptr
                    )
            ,comm::CStyle
            ,&l)
        {
        }

        // ctor with reply instance and listener reference and ActiveObjectFactory
        IntV2XStackProxy(const comm::InstanceID& id, IntV2XStackReply& r, comm::ActiveObjectFactoryPtr aof, comm::LifecycleListener& l)
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
                ,IntV2XStackServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_SID_V2XSTACK_INTV2XSTACK_REPLY))
                    ,&r
                    ,nullptr
                    ,aof
                    )
            ,comm::CStyle
            ,&l)
        {
        }

        // ctor with reply instance and listener reference
        IntV2XStackProxy(const uint32_t inst_cnt, IntV2XStackReply& r, comm::LifecycleListener& l)
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_SID_V2XSTACK_INTV2XSTACK_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
                ,IntV2XStackServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_SID_V2XSTACK_INTV2XSTACK_REPLY))
                    ,&r
                    ,nullptr
                    )
            ,comm::CStyle
            ,&l)
        {
        }

        // ctor with reply instance and listener reference and ActiveObjectFactory
        IntV2XStackProxy(const uint32_t inst_cnt, IntV2XStackReply& r, comm::ActiveObjectFactoryPtr aof, comm::LifecycleListener& l)
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_SID_V2XSTACK_INTV2XSTACK_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
                ,IntV2XStackServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_SID_V2XSTACK_INTV2XSTACK_REPLY))
                    ,&r
                    ,nullptr
                    ,aof
                    )
            ,comm::CStyle
            ,&l)
        {
        }

        // default ctor
        IntV2XStackProxy() {}
        // IntV2XStackProxy is copy-assignable, default copy-ctor and assignment operator are fine
        // IntV2XStackProxy is move-assignable when using C++11 or higher

        IntV2XStackC& operator*() const
        {
            return *operator->();
        }

        IntV2XStackC* operator->() const
        {
            return reinterpret_cast<IntV2XStackC*>(getImpl());
        }

    private:

        static const comm::InterfaceKey& getIKey() {
            static comm::InterfaceKey ikey(0x00010000, 0x0000, 0x6000, 0x0000, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00);
            return ikey;
        }
        static const std::string& getIName() {
            static const std::string& iname{"asi.sid.v2xstack.IntV2XStack"};
            return iname;
        }
        static const comm::InterfaceKey& getRIKey() {
            // semver is not different in request/reply direction
            return IntV2XStackProxy::getIKey();
        }
        // proxy/stub factory init for the client side
        PROXY_EXPORT static const ProxyStubFactory* clientInitFactory();

    };

} // namespace cstyle
}//namespace asi
}//namespace sid
}//namespace v2xstack
#endif// ASI_SID_V2XSTACK_INTV2XSTACK_PROXY_CSTYLE_HXX
