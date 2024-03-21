/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleProxy_hxx.tmpl
*/
#ifndef ASI_VEHICLE_TEST_PROXY_CSTYLE_HXX
#define ASI_VEHICLE_TEST_PROXY_CSTYLE_HXX

#include <comm/ProxyStubFactory.hxx>
#include <comm/Proxy.hxx>
#include <comm/commidltypes.hxx>        // used for PROXY_EXPORT macro
#include <asi/vehicle/cstyle/StructKlemmenStatus01Struct.hxx>
#include <asi/vehicle/cstyle/Definitions.hxx>
#include <asi/vehicle/cstyle/TestC.hxx>
#include <asi/vehicle/cstyle/TestReply.hxx>
#include <asi/vehicle/cstyle/TestServiceReplyRegistration.hxx>

#include <string>

namespace asi
{
namespace vehicle
{

namespace cstyle
{
    /**
        \brief A proxy for services that implement the vehicle::Test interface.
    */
    class TestProxy  : public comm::Proxy
    {
    public:
        // ctor with listener pointer and no reply interface
        TestProxy(const comm::InstanceID& _id, comm::LifecycleListener* l=nullptr )
        : Proxy(comm::Proxy::IdentityArgs(_id, getIKey(), getIName())
                ,clientInitFactory
                ,comm::CStyle, l)
        {
        }

        // ctor with listener pointer and no reply interface
        // explicit so we don't magically construct proxies from integers
        explicit TestProxy(const uint32_t inst_cnt, comm::LifecycleListener* l=nullptr )
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_VEHICLE_TEST_REQUEST), inst_cnt),
                getIKey(), getIName())
                ,clientInitFactory
                ,comm::CStyle
                ,l)
        {
        }

        // ctor with listener reference and no reply interface
        TestProxy(const comm::InstanceID& id, comm::LifecycleListener& l )
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
                ,comm::CStyle, &l)
        {
        }

        // ctor with listener pointer and no reply interface
        TestProxy(const uint32_t inst_cnt, comm::LifecycleListener& l )
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_VEHICLE_TEST_REQUEST), inst_cnt)
                , getIKey(), getIName())
                ,clientInitFactory
                ,comm::CStyle
                ,&l)
        {
        }

        // constructors  with a user passed object factory to receive notifications
        // ctor with listener pointer and no reply interface
        // explicit so we don't magically construct proxies from integers
        explicit TestProxy(const uint32_t inst_cnt
                                        ,const comm::ActiveObjectFactoryPtr& aof
                                        ,comm::LifecycleListener* l=nullptr )
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_VEHICLE_TEST_REQUEST), inst_cnt),
                getIKey(), getIName())
                ,clientInitFactory
                ,aof
                ,comm::CStyle
                ,l)
        {
        }

        // ctor with listener pointer and no reply interface
        TestProxy(const uint32_t inst_cnt
                                ,const comm::ActiveObjectFactoryPtr& aof
                                ,comm::LifecycleListener& l )
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_VEHICLE_TEST_REQUEST), inst_cnt)
                , getIKey(), getIName())
                ,clientInitFactory
                ,aof
                ,comm::CStyle
                ,&l)
        {
        }

        // ctor with reply instance and listener pointers
        TestProxy(const comm::InstanceID& id, TestReply* r, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
                ,TestServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_VEHICLE_TEST_REPLY))
                    ,r
                    ,nullptr
                    )
                ,comm::CStyle
                ,l)
        {
        }

        // ctor with reply instance and listener pointers and ActiveObjectFactory
        TestProxy(const comm::InstanceID& id, TestReply* r, comm::ActiveObjectFactoryPtr aof, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
                ,TestServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_VEHICLE_TEST_REPLY))
                    ,r
                    ,nullptr
                    ,aof
                    )
                ,comm::CStyle
                ,l)
        {
        }

        // ctor with reply instance and listener pointers
        TestProxy(const uint32_t inst_cnt, TestReply* r, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_VEHICLE_TEST_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
                ,TestServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_VEHICLE_TEST_REPLY))
                    ,r
                    ,nullptr
                    )
                ,comm::CStyle
                ,l)
        {
        }

        // ctor with reply instance and listener pointers and ActiveObjectFactory
        TestProxy(const uint32_t inst_cnt, TestReply* r, comm::ActiveObjectFactoryPtr aof, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_VEHICLE_TEST_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
            ,TestServiceReplyRegistration(
                comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_VEHICLE_TEST_REPLY))
                ,r
                ,nullptr
                ,aof
                )
            ,comm::CStyle
            ,l)
        {
        }

        // ctor with reply instance reference and listener pointer
        TestProxy(const comm::InstanceID& id, TestReply& r, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
                ,TestServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_VEHICLE_TEST_REPLY))
                    ,&r
                    ,nullptr
                    )
            ,comm::CStyle
            ,l)
        {
        }

        // ctor with reply instance reference and listener pointer and ActiveObjectFactory
        TestProxy(const comm::InstanceID& id, TestReply& r, comm::ActiveObjectFactoryPtr aof, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
            ,TestServiceReplyRegistration(
                comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_VEHICLE_TEST_REPLY))
                ,&r
                ,nullptr
                ,aof
                )
            ,comm::CStyle
            ,l)
        {
        }

        // ctor with reply instance reference and listener pointer
        TestProxy(const uint32_t inst_cnt, TestReply& r, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_VEHICLE_TEST_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
            ,TestServiceReplyRegistration(
                comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_VEHICLE_TEST_REPLY))
                ,&r
                ,nullptr
                )
            ,comm::CStyle
            ,l)
        {
        }

        // ctor with reply instance reference and listener pointer and ActiveObjectFactory
        TestProxy(const uint32_t inst_cnt, TestReply& r, comm::ActiveObjectFactoryPtr aof, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_VEHICLE_TEST_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
            ,TestServiceReplyRegistration(
                comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_VEHICLE_TEST_REPLY))
                ,&r
                ,nullptr
                ,aof
                )
            ,comm::CStyle
            ,l)
        {
        }

        // ctor with reply instance and listener reference
        TestProxy(const comm::InstanceID& id, TestReply& r, comm::LifecycleListener& l)
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
                ,TestServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_VEHICLE_TEST_REPLY))
                    ,&r
                    ,nullptr
                    )
            ,comm::CStyle
            ,&l)
        {
        }

        // ctor with reply instance and listener reference and ActiveObjectFactory
        TestProxy(const comm::InstanceID& id, TestReply& r, comm::ActiveObjectFactoryPtr aof, comm::LifecycleListener& l)
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
                ,TestServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_VEHICLE_TEST_REPLY))
                    ,&r
                    ,nullptr
                    ,aof
                    )
            ,comm::CStyle
            ,&l)
        {
        }

        // ctor with reply instance and listener reference
        TestProxy(const uint32_t inst_cnt, TestReply& r, comm::LifecycleListener& l)
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_VEHICLE_TEST_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
                ,TestServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_VEHICLE_TEST_REPLY))
                    ,&r
                    ,nullptr
                    )
            ,comm::CStyle
            ,&l)
        {
        }

        // ctor with reply instance and listener reference and ActiveObjectFactory
        TestProxy(const uint32_t inst_cnt, TestReply& r, comm::ActiveObjectFactoryPtr aof, comm::LifecycleListener& l)
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_VEHICLE_TEST_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
                ,TestServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_VEHICLE_TEST_REPLY))
                    ,&r
                    ,nullptr
                    ,aof
                    )
            ,comm::CStyle
            ,&l)
        {
        }

        // default ctor
        TestProxy() {}
        // TestProxy is copy-assignable, default copy-ctor and assignment operator are fine
        // TestProxy is move-assignable when using C++11 or higher

        TestC& operator*() const
        {
            return *operator->();
        }

        TestC* operator->() const
        {
            return reinterpret_cast<TestC*>(getImpl());
        }

    private:

        static const comm::InterfaceKey& getIKey() {
            static comm::InterfaceKey ikey(0x00010000, 0x0000, 0x6000, 0x0000, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00);
            return ikey;
        }
        static const std::string& getIName() {
            static const std::string& iname{"asi.vehicle.Test"};
            return iname;
        }
        static const comm::InterfaceKey& getRIKey() {
            // semver is not different in request/reply direction
            return TestProxy::getIKey();
        }
        // proxy/stub factory init for the client side
        PROXY_EXPORT static const ProxyStubFactory* clientInitFactory();

    };

} // namespace cstyle
}//namespace asi
}//namespace vehicle
#endif// ASI_VEHICLE_TEST_PROXY_CSTYLE_HXX
