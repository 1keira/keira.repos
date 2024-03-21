/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleProxy_hxx.tmpl
*/
#ifndef ASI_SID_LHWAPP_INTLHWAPP_PROXY_CSTYLE_HXX
#define ASI_SID_LHWAPP_INTLHWAPP_PROXY_CSTYLE_HXX

#include <comm/ProxyStubFactory.hxx>
#include <comm/Proxy.hxx>
#include <comm/commidltypes.hxx>        // used for PROXY_EXPORT macro
#include <asi/sid/lhwapp/cstyle/StructAirbag01Struct.hxx>
#include <asi/sid/lhwapp/cstyle/StructBlinkmodi02Struct.hxx>
#include <asi/sid/lhwapp/cstyle/StructDaempfer01Struct.hxx>
#include <asi/sid/lhwapp/cstyle/StructESC50Struct.hxx>
#include <asi/sid/lhwapp/cstyle/StructESP21Struct.hxx>
#include <asi/sid/lhwapp/cstyle/StructESP24Struct.hxx>
#include <asi/sid/lhwapp/cstyle/StructESP30Struct.hxx>
#include <asi/sid/lhwapp/cstyle/StructHVK01Struct.hxx>
#include <asi/sid/lhwapp/cstyle/StructMotor18Struct.hxx>
#include <asi/sid/lhwapp/cstyle/StructMotor41Struct.hxx>
#include <asi/sid/lhwapp/cstyle/StructPOSGNSSDR01Struct.hxx>
#include <asi/sid/lhwapp/cstyle/StructPSD04Struct.hxx>
#include <asi/sid/lhwapp/cstyle/StructPSD05Struct.hxx>
#include <asi/sid/lhwapp/cstyle/StructPSD06Struct.hxx>
#include <asi/sid/lhwapp/cstyle/StructRKA01Struct.hxx>
#include <asi/sid/lhwapp/cstyle/Definitions.hxx>
#include <asi/sid/lhwapp/cstyle/IntLHWAppC.hxx>
#include <asi/sid/lhwapp/cstyle/IntLHWAppReply.hxx>
#include <asi/sid/lhwapp/cstyle/IntLHWAppServiceReplyRegistration.hxx>

#include <string>

namespace asi
{
namespace sid
{
namespace lhwapp
{

namespace cstyle
{
    /**
        \brief A proxy for services that implement the lhwapp::IntLHWApp interface.
    */
    class IntLHWAppProxy  : public comm::Proxy
    {
    public:
        // ctor with listener pointer and no reply interface
        IntLHWAppProxy(const comm::InstanceID& _id, comm::LifecycleListener* l=nullptr )
        : Proxy(comm::Proxy::IdentityArgs(_id, getIKey(), getIName())
                ,clientInitFactory
                ,comm::CStyle, l)
        {
        }

        // ctor with listener pointer and no reply interface
        // explicit so we don't magically construct proxies from integers
        explicit IntLHWAppProxy(const uint32_t inst_cnt, comm::LifecycleListener* l=nullptr )
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_SID_LHWAPP_INTLHWAPP_REQUEST), inst_cnt),
                getIKey(), getIName())
                ,clientInitFactory
                ,comm::CStyle
                ,l)
        {
        }

        // ctor with listener reference and no reply interface
        IntLHWAppProxy(const comm::InstanceID& id, comm::LifecycleListener& l )
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
                ,comm::CStyle, &l)
        {
        }

        // ctor with listener pointer and no reply interface
        IntLHWAppProxy(const uint32_t inst_cnt, comm::LifecycleListener& l )
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_SID_LHWAPP_INTLHWAPP_REQUEST), inst_cnt)
                , getIKey(), getIName())
                ,clientInitFactory
                ,comm::CStyle
                ,&l)
        {
        }

        // constructors  with a user passed object factory to receive notifications
        // ctor with listener pointer and no reply interface
        // explicit so we don't magically construct proxies from integers
        explicit IntLHWAppProxy(const uint32_t inst_cnt
                                        ,const comm::ActiveObjectFactoryPtr& aof
                                        ,comm::LifecycleListener* l=nullptr )
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_SID_LHWAPP_INTLHWAPP_REQUEST), inst_cnt),
                getIKey(), getIName())
                ,clientInitFactory
                ,aof
                ,comm::CStyle
                ,l)
        {
        }

        // ctor with listener pointer and no reply interface
        IntLHWAppProxy(const uint32_t inst_cnt
                                ,const comm::ActiveObjectFactoryPtr& aof
                                ,comm::LifecycleListener& l )
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_SID_LHWAPP_INTLHWAPP_REQUEST), inst_cnt)
                , getIKey(), getIName())
                ,clientInitFactory
                ,aof
                ,comm::CStyle
                ,&l)
        {
        }

        // ctor with reply instance and listener pointers
        IntLHWAppProxy(const comm::InstanceID& id, IntLHWAppReply* r, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
                ,IntLHWAppServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_SID_LHWAPP_INTLHWAPP_REPLY))
                    ,r
                    ,nullptr
                    )
                ,comm::CStyle
                ,l)
        {
        }

        // ctor with reply instance and listener pointers and ActiveObjectFactory
        IntLHWAppProxy(const comm::InstanceID& id, IntLHWAppReply* r, comm::ActiveObjectFactoryPtr aof, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
                ,IntLHWAppServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_SID_LHWAPP_INTLHWAPP_REPLY))
                    ,r
                    ,nullptr
                    ,aof
                    )
                ,comm::CStyle
                ,l)
        {
        }

        // ctor with reply instance and listener pointers
        IntLHWAppProxy(const uint32_t inst_cnt, IntLHWAppReply* r, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_SID_LHWAPP_INTLHWAPP_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
                ,IntLHWAppServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_SID_LHWAPP_INTLHWAPP_REPLY))
                    ,r
                    ,nullptr
                    )
                ,comm::CStyle
                ,l)
        {
        }

        // ctor with reply instance and listener pointers and ActiveObjectFactory
        IntLHWAppProxy(const uint32_t inst_cnt, IntLHWAppReply* r, comm::ActiveObjectFactoryPtr aof, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_SID_LHWAPP_INTLHWAPP_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
            ,IntLHWAppServiceReplyRegistration(
                comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_SID_LHWAPP_INTLHWAPP_REPLY))
                ,r
                ,nullptr
                ,aof
                )
            ,comm::CStyle
            ,l)
        {
        }

        // ctor with reply instance reference and listener pointer
        IntLHWAppProxy(const comm::InstanceID& id, IntLHWAppReply& r, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
                ,IntLHWAppServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_SID_LHWAPP_INTLHWAPP_REPLY))
                    ,&r
                    ,nullptr
                    )
            ,comm::CStyle
            ,l)
        {
        }

        // ctor with reply instance reference and listener pointer and ActiveObjectFactory
        IntLHWAppProxy(const comm::InstanceID& id, IntLHWAppReply& r, comm::ActiveObjectFactoryPtr aof, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
            ,IntLHWAppServiceReplyRegistration(
                comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_SID_LHWAPP_INTLHWAPP_REPLY))
                ,&r
                ,nullptr
                ,aof
                )
            ,comm::CStyle
            ,l)
        {
        }

        // ctor with reply instance reference and listener pointer
        IntLHWAppProxy(const uint32_t inst_cnt, IntLHWAppReply& r, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_SID_LHWAPP_INTLHWAPP_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
            ,IntLHWAppServiceReplyRegistration(
                comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_SID_LHWAPP_INTLHWAPP_REPLY))
                ,&r
                ,nullptr
                )
            ,comm::CStyle
            ,l)
        {
        }

        // ctor with reply instance reference and listener pointer and ActiveObjectFactory
        IntLHWAppProxy(const uint32_t inst_cnt, IntLHWAppReply& r, comm::ActiveObjectFactoryPtr aof, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_SID_LHWAPP_INTLHWAPP_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
            ,IntLHWAppServiceReplyRegistration(
                comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_SID_LHWAPP_INTLHWAPP_REPLY))
                ,&r
                ,nullptr
                ,aof
                )
            ,comm::CStyle
            ,l)
        {
        }

        // ctor with reply instance and listener reference
        IntLHWAppProxy(const comm::InstanceID& id, IntLHWAppReply& r, comm::LifecycleListener& l)
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
                ,IntLHWAppServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_SID_LHWAPP_INTLHWAPP_REPLY))
                    ,&r
                    ,nullptr
                    )
            ,comm::CStyle
            ,&l)
        {
        }

        // ctor with reply instance and listener reference and ActiveObjectFactory
        IntLHWAppProxy(const comm::InstanceID& id, IntLHWAppReply& r, comm::ActiveObjectFactoryPtr aof, comm::LifecycleListener& l)
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
                ,IntLHWAppServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_SID_LHWAPP_INTLHWAPP_REPLY))
                    ,&r
                    ,nullptr
                    ,aof
                    )
            ,comm::CStyle
            ,&l)
        {
        }

        // ctor with reply instance and listener reference
        IntLHWAppProxy(const uint32_t inst_cnt, IntLHWAppReply& r, comm::LifecycleListener& l)
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_SID_LHWAPP_INTLHWAPP_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
                ,IntLHWAppServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_SID_LHWAPP_INTLHWAPP_REPLY))
                    ,&r
                    ,nullptr
                    )
            ,comm::CStyle
            ,&l)
        {
        }

        // ctor with reply instance and listener reference and ActiveObjectFactory
        IntLHWAppProxy(const uint32_t inst_cnt, IntLHWAppReply& r, comm::ActiveObjectFactoryPtr aof, comm::LifecycleListener& l)
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_SID_LHWAPP_INTLHWAPP_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
                ,IntLHWAppServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_SID_LHWAPP_INTLHWAPP_REPLY))
                    ,&r
                    ,nullptr
                    ,aof
                    )
            ,comm::CStyle
            ,&l)
        {
        }

        // default ctor
        IntLHWAppProxy() {}
        // IntLHWAppProxy is copy-assignable, default copy-ctor and assignment operator are fine
        // IntLHWAppProxy is move-assignable when using C++11 or higher

        IntLHWAppC& operator*() const
        {
            return *operator->();
        }

        IntLHWAppC* operator->() const
        {
            return reinterpret_cast<IntLHWAppC*>(getImpl());
        }

    private:

        static const comm::InterfaceKey& getIKey() {
            static comm::InterfaceKey ikey(0x00010000, 0x0000, 0x6000, 0x0000, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00);
            return ikey;
        }
        static const std::string& getIName() {
            static const std::string& iname{"asi.sid.lhwapp.IntLHWApp"};
            return iname;
        }
        static const comm::InterfaceKey& getRIKey() {
            // semver is not different in request/reply direction
            return IntLHWAppProxy::getIKey();
        }
        // proxy/stub factory init for the client side
        PROXY_EXPORT static const ProxyStubFactory* clientInitFactory();

    };

} // namespace cstyle
}//namespace asi
}//namespace sid
}//namespace lhwapp
#endif// ASI_SID_LHWAPP_INTLHWAPP_PROXY_CSTYLE_HXX
