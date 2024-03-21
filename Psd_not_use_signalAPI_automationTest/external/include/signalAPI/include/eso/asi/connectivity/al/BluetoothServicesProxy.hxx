/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Proxy_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_BLUETOOTHSERVICES_PROXY_HXX
#define ASI_CONNECTIVITY_AL_BLUETOOTHSERVICES_PROXY_HXX

#include <comm/ProxyStubFactory.hxx>
#include <comm/Proxy.hxx>
#include <comm/commidltypes.hxx>        // used for PROXY_EXPORT macro
#include <asi/connectivity/al/StructBluetoothDevice.hxx>
#include <asi/connectivity/al/StructBtDeviceRecord.hxx>
#include <asi/connectivity/al/StructServiceVersions.hxx>
#include <asi/connectivity/al/StructSimplePairingInformation.hxx>
#include <asi/connectivity/al/Definitions.hxx>
#include <asi/connectivity/al/BluetoothServicesC.hxx>
#include <asi/connectivity/al/BluetoothServicesReply.hxx>
#include <asi/connectivity/al/BluetoothServicesServiceReplyRegistration.hxx>

#include <string>

namespace asi
{
namespace connectivity
{
namespace al
{

    /**
        \brief A proxy for services that implement the al::BluetoothServices interface.
    */
    class BluetoothServicesProxy  : public comm::Proxy
    {
    public:
        // ctor with listener pointer and no reply interface
        BluetoothServicesProxy(const comm::InstanceID& _id, comm::LifecycleListener* l=nullptr )
        : Proxy(comm::Proxy::IdentityArgs(_id, getIKey(), getIName())
                ,clientInitFactory
                ,comm::CIPtrStyle, l)
        {
        }

        // ctor with listener pointer and no reply interface
        // explicit so we don't magically construct proxies from integers
        explicit BluetoothServicesProxy(const uint32_t inst_cnt, comm::LifecycleListener* l=nullptr )
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_AL_BLUETOOTHSERVICES_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
                ,comm::CIPtrStyle
                ,l)
        {
        }

        // ctor with listener reference and no reply interface
        BluetoothServicesProxy(const comm::InstanceID& id, comm::LifecycleListener& l )
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
                ,comm::CIPtrStyle, &l)
        {
        }

        // ctor with listener pointer and no reply interface
        BluetoothServicesProxy(const uint32_t inst_cnt, comm::LifecycleListener& l )
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_AL_BLUETOOTHSERVICES_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
                ,comm::CIPtrStyle
                ,&l)
        {
        }

        // constructors  with a user passed object factory to receive notifications
        // ctor with listener pointer and no reply interface
        // explicit so we don't magically construct proxies from integers
        explicit BluetoothServicesProxy(const uint32_t inst_cnt
                                        ,const comm::ActiveObjectFactoryPtr& aof
                                        ,comm::LifecycleListener* l=nullptr )
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_AL_BLUETOOTHSERVICES_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
                ,aof
                ,comm::CIPtrStyle
                ,l
                )
        {
        }

        // ctor with listener pointer and no reply interface
        BluetoothServicesProxy(const uint32_t inst_cnt
                                ,const comm::ActiveObjectFactoryPtr& aof
                                ,comm::LifecycleListener& l )
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_AL_BLUETOOTHSERVICES_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
                ,aof
                ,comm::CIPtrStyle
                ,&l
                )
        {
        }
        // ctor with reply instance and listener pointers
        BluetoothServicesProxy(const comm::InstanceID& id, BluetoothServicesReply* r, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
                ,BluetoothServicesServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_AL_BLUETOOTHSERVICES_REPLY))
                    ,r
                    ,nullptr
                    )
                ,comm::CIPtrStyle
                ,l
                )
        {
        }

        // ctor with reply instance and listener pointers and ActiveObjectFactory
        BluetoothServicesProxy(const comm::InstanceID& id, BluetoothServicesReply* r, comm::ActiveObjectFactoryPtr aof, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
                ,BluetoothServicesServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_AL_BLUETOOTHSERVICES_REPLY))
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
        BluetoothServicesProxy(const uint32_t inst_cnt, BluetoothServicesReply* r, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_AL_BLUETOOTHSERVICES_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
                ,BluetoothServicesServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_AL_BLUETOOTHSERVICES_REPLY))
                    ,r
                    ,nullptr
                    )
                ,comm::CIPtrStyle
                ,l
                )
        {
        }

        // ctor with reply instance and listener pointers and ActiveObjectFactory
        BluetoothServicesProxy(const uint32_t inst_cnt, BluetoothServicesReply* r, comm::ActiveObjectFactoryPtr aof, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_AL_BLUETOOTHSERVICES_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
            ,BluetoothServicesServiceReplyRegistration(
                comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_AL_BLUETOOTHSERVICES_REPLY))
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
        BluetoothServicesProxy(const comm::InstanceID& id, BluetoothServicesReply& r, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
                ,BluetoothServicesServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_AL_BLUETOOTHSERVICES_REPLY))
                    ,&r
                    ,nullptr
                    )
            ,comm::CIPtrStyle
            ,l
            )
        {
        }

        // ctor with reply instance reference and listener pointer and ActiveObjectFactory
        BluetoothServicesProxy(const comm::InstanceID& id, BluetoothServicesReply& r, comm::ActiveObjectFactoryPtr aof, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
            ,BluetoothServicesServiceReplyRegistration(
                comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_AL_BLUETOOTHSERVICES_REPLY))
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
        BluetoothServicesProxy(const uint32_t inst_cnt, BluetoothServicesReply& r, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_AL_BLUETOOTHSERVICES_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
            ,BluetoothServicesServiceReplyRegistration(
                comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_AL_BLUETOOTHSERVICES_REPLY))
                ,&r
                ,nullptr
                )
            ,comm::CIPtrStyle
            ,l
            )
        {
        }

        // ctor with reply instance reference and listener pointer and ActiveObjectFactory
        BluetoothServicesProxy(const uint32_t inst_cnt, BluetoothServicesReply& r, comm::ActiveObjectFactoryPtr aof, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_AL_BLUETOOTHSERVICES_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
            ,BluetoothServicesServiceReplyRegistration(
                comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_AL_BLUETOOTHSERVICES_REPLY))
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
        BluetoothServicesProxy(const comm::InstanceID& id, BluetoothServicesReply& r, comm::LifecycleListener& l)
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
                ,BluetoothServicesServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_AL_BLUETOOTHSERVICES_REPLY))
                    ,&r
                    ,nullptr
                    )
            ,comm::CIPtrStyle
            ,&l
            )
        {
        }

        // ctor with reply instance and listener reference and ActiveObjectFactory
        BluetoothServicesProxy(const comm::InstanceID& id, BluetoothServicesReply& r, comm::ActiveObjectFactoryPtr aof, comm::LifecycleListener& l)
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
                ,BluetoothServicesServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_AL_BLUETOOTHSERVICES_REPLY))
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
        BluetoothServicesProxy(const uint32_t inst_cnt, BluetoothServicesReply& r, comm::LifecycleListener& l)
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_AL_BLUETOOTHSERVICES_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
                ,BluetoothServicesServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_AL_BLUETOOTHSERVICES_REPLY))
                    ,&r
                    ,nullptr
                    )
            ,comm::CIPtrStyle
            ,&l
            )
        {
        }

        // ctor with reply instance and listener reference and ActiveObjectFactory
        BluetoothServicesProxy(const uint32_t inst_cnt, BluetoothServicesReply& r, comm::ActiveObjectFactoryPtr aof, comm::LifecycleListener& l)
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_AL_BLUETOOTHSERVICES_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
                ,BluetoothServicesServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_AL_BLUETOOTHSERVICES_REPLY))
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
        BluetoothServicesProxy() {}
        // BluetoothServicesProxy is copy-assignable, default copy-ctor and assignment operator are fine
        // BluetoothServicesProxy is move-assignable when using C++11 or higher

        BluetoothServicesC& operator*() const
        {
            return *operator->();
        }

        BluetoothServicesC* operator->() const
        {
            return reinterpret_cast<BluetoothServicesC*>(getImpl());
        }

    private:
        static const comm::InterfaceKey& getIKey() {
            static comm::InterfaceKey ikey(0x00010000, 0x0001, 0x6000, 0x0000, 0x00, 0x01, 0x00, 0x05, 0x00, 0x00);
            return ikey;
        }
        static const std::string& getIName() {
            static const std::string iname{"asi.connectivity.al.BluetoothServices"};
            return iname;
        }
        static const comm::InterfaceKey& getRIKey() {
            // semver is not different in request/reply direction
            return BluetoothServicesProxy::getIKey();
        }

        // proxy/stub factory init for the client side
        PROXY_EXPORT static const ProxyStubFactory* clientInitFactory();

    };

}//namespace asi
}//namespace connectivity
}//namespace al
#endif// ASI_CONNECTIVITY_AL_BLUETOOTHSERVICES_PROXY_HXX
