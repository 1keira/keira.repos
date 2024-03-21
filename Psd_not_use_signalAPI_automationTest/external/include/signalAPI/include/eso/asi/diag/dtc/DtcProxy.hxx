/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Proxy_hxx.tmpl
*/
#ifndef ASI_DIAG_DTC_DTC_PROXY_HXX
#define ASI_DIAG_DTC_DTC_PROXY_HXX

#include <comm/ProxyStubFactory.hxx>
#include <comm/Proxy.hxx>
#include <comm/commidltypes.hxx>        // used for PROXY_EXPORT macro
#include <asi/diag/dtc/Definitions.hxx>
#include <asi/diag/dtc/DtcC.hxx>
#include <asi/diag/dtc/DtcReply.hxx>
#include <asi/diag/dtc/DtcServiceReplyRegistration.hxx>

#include <string>

namespace asi
{
namespace diag
{
namespace dtc
{

    /**
        \brief A proxy for services that implement the dtc::Dtc interface.
    */
    class DtcProxy  : public comm::Proxy
    {
    public:
        // ctor with listener pointer and no reply interface
        DtcProxy(const comm::InstanceID& _id, comm::LifecycleListener* l=nullptr )
        : Proxy(comm::Proxy::IdentityArgs(_id, getIKey(), getIName())
                ,clientInitFactory
                ,comm::CIPtrStyle, l)
        {
        }

        // ctor with listener pointer and no reply interface
        // explicit so we don't magically construct proxies from integers
        explicit DtcProxy(const uint32_t inst_cnt, comm::LifecycleListener* l=nullptr )
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_DIAG_DTC_DTC_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
                ,comm::CIPtrStyle
                ,l)
        {
        }

        // ctor with listener reference and no reply interface
        DtcProxy(const comm::InstanceID& id, comm::LifecycleListener& l )
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
                ,comm::CIPtrStyle, &l)
        {
        }

        // ctor with listener pointer and no reply interface
        DtcProxy(const uint32_t inst_cnt, comm::LifecycleListener& l )
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_DIAG_DTC_DTC_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
                ,comm::CIPtrStyle
                ,&l)
        {
        }

        // constructors  with a user passed object factory to receive notifications
        // ctor with listener pointer and no reply interface
        // explicit so we don't magically construct proxies from integers
        explicit DtcProxy(const uint32_t inst_cnt
                                        ,const comm::ActiveObjectFactoryPtr& aof
                                        ,comm::LifecycleListener* l=nullptr )
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_DIAG_DTC_DTC_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
                ,aof
                ,comm::CIPtrStyle
                ,l
                )
        {
        }

        // ctor with listener pointer and no reply interface
        DtcProxy(const uint32_t inst_cnt
                                ,const comm::ActiveObjectFactoryPtr& aof
                                ,comm::LifecycleListener& l )
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_DIAG_DTC_DTC_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
                ,aof
                ,comm::CIPtrStyle
                ,&l
                )
        {
        }
        // ctor with reply instance and listener pointers
        DtcProxy(const comm::InstanceID& id, DtcReply* r, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
                ,DtcServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_DIAG_DTC_DTC_REPLY))
                    ,r
                    ,nullptr
                    )
                ,comm::CIPtrStyle
                ,l
                )
        {
        }

        // ctor with reply instance and listener pointers and ActiveObjectFactory
        DtcProxy(const comm::InstanceID& id, DtcReply* r, comm::ActiveObjectFactoryPtr aof, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
                ,DtcServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_DIAG_DTC_DTC_REPLY))
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
        DtcProxy(const uint32_t inst_cnt, DtcReply* r, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_DIAG_DTC_DTC_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
                ,DtcServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_DIAG_DTC_DTC_REPLY))
                    ,r
                    ,nullptr
                    )
                ,comm::CIPtrStyle
                ,l
                )
        {
        }

        // ctor with reply instance and listener pointers and ActiveObjectFactory
        DtcProxy(const uint32_t inst_cnt, DtcReply* r, comm::ActiveObjectFactoryPtr aof, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_DIAG_DTC_DTC_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
            ,DtcServiceReplyRegistration(
                comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_DIAG_DTC_DTC_REPLY))
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
        DtcProxy(const comm::InstanceID& id, DtcReply& r, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
                ,DtcServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_DIAG_DTC_DTC_REPLY))
                    ,&r
                    ,nullptr
                    )
            ,comm::CIPtrStyle
            ,l
            )
        {
        }

        // ctor with reply instance reference and listener pointer and ActiveObjectFactory
        DtcProxy(const comm::InstanceID& id, DtcReply& r, comm::ActiveObjectFactoryPtr aof, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
            ,DtcServiceReplyRegistration(
                comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_DIAG_DTC_DTC_REPLY))
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
        DtcProxy(const uint32_t inst_cnt, DtcReply& r, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_DIAG_DTC_DTC_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
            ,DtcServiceReplyRegistration(
                comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_DIAG_DTC_DTC_REPLY))
                ,&r
                ,nullptr
                )
            ,comm::CIPtrStyle
            ,l
            )
        {
        }

        // ctor with reply instance reference and listener pointer and ActiveObjectFactory
        DtcProxy(const uint32_t inst_cnt, DtcReply& r, comm::ActiveObjectFactoryPtr aof, comm::LifecycleListener* l=nullptr)
        : Proxy(comm::Proxy::IdentityArgs(comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_DIAG_DTC_DTC_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
            ,DtcServiceReplyRegistration(
                comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_DIAG_DTC_DTC_REPLY))
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
        DtcProxy(const comm::InstanceID& id, DtcReply& r, comm::LifecycleListener& l)
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
                ,DtcServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_DIAG_DTC_DTC_REPLY))
                    ,&r
                    ,nullptr
                    )
            ,comm::CIPtrStyle
            ,&l
            )
        {
        }

        // ctor with reply instance and listener reference and ActiveObjectFactory
        DtcProxy(const comm::InstanceID& id, DtcReply& r, comm::ActiveObjectFactoryPtr aof, comm::LifecycleListener& l)
        : Proxy(comm::Proxy::IdentityArgs(id, getIKey(), getIName())
                ,clientInitFactory
                ,DtcServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_DIAG_DTC_DTC_REPLY))
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
        DtcProxy(const uint32_t inst_cnt, DtcReply& r, comm::LifecycleListener& l)
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_DIAG_DTC_DTC_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
                ,DtcServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_DIAG_DTC_DTC_REPLY))
                    ,&r
                    ,nullptr
                    )
            ,comm::CIPtrStyle
            ,&l
            )
        {
        }

        // ctor with reply instance and listener reference and ActiveObjectFactory
        DtcProxy(const uint32_t inst_cnt, DtcReply& r, comm::ActiveObjectFactoryPtr aof, comm::LifecycleListener& l)
        : Proxy(comm::Proxy::IdentityArgs(
                comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_DIAG_DTC_DTC_REQUEST), inst_cnt)
                ,getIKey(), getIName())
                ,clientInitFactory
                ,DtcServiceReplyRegistration(
                    comm::InstanceID(comm::InterfaceID(BINARY_UUID_ASI_DIAG_DTC_DTC_REPLY))
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
        DtcProxy() {}
        // DtcProxy is copy-assignable, default copy-ctor and assignment operator are fine
        // DtcProxy is move-assignable when using C++11 or higher

        DtcC& operator*() const
        {
            return *operator->();
        }

        DtcC* operator->() const
        {
            return reinterpret_cast<DtcC*>(getImpl());
        }

    private:
        static const comm::InterfaceKey& getIKey() {
            static comm::InterfaceKey ikey(0x00000005, 0x0000, 0x6000, 0x0000, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00);
            return ikey;
        }
        static const std::string& getIName() {
            static const std::string iname{"asi.diag.dtc.Dtc"};
            return iname;
        }
        static const comm::InterfaceKey& getRIKey() {
            // semver is not different in request/reply direction
            return DtcProxy::getIKey();
        }

        // proxy/stub factory init for the client side
        PROXY_EXPORT static const ProxyStubFactory* clientInitFactory();

    };

}//namespace asi
}//namespace diag
}//namespace dtc
#endif// ASI_DIAG_DTC_DTC_PROXY_HXX
