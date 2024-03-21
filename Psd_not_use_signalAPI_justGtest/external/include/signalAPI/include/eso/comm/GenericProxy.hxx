/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/


#ifndef COMM_GENERIC_PROXY_HXX
#define COMM_GENERIC_PROXY_HXX

#include <comm/comm_dso.h>
#include <comm/Proxy.hxx>
#include <comm/IGenericServiceC.hxx>

namespace comm {

    class IGenericService;
    /**
      \brief A proxy for an IGenericService instance
      */
    class COMM_EXPORT GenericProxy  : public comm::Proxy {
        public:
            GenericProxy() = default;
            ~GenericProxy() override = default;
            // GenericProxy is copy-assignable, default copy-ctor and assignment operator are fine


            // ctor without reply service
            explicit GenericProxy(const comm::InstanceID& iid, const comm::InterfaceKey& ikey
                    ,const char* name
                    ,comm::LifecycleListener* l=nullptr);

            // ctor without reply service, with ActiveObjectFactory
            explicit GenericProxy(const comm::InstanceID& iid, const comm::InterfaceKey& ikey
                    ,const char* name
                    ,comm::ActiveObjectFactoryPtr aof
                    ,comm::LifecycleListener* l=nullptr);


            // ctor with reply service
            explicit GenericProxy(const comm::InstanceID& iid, const comm::InterfaceKey& ikey
                    ,const char* name
                    ,const comm::InstanceID& reply_iid, const comm::InterfaceKey& repy_ikey
                    ,const char* reply_name
                    ,IGenericService* reply_svc
                    ,comm::LifecycleListener* l=nullptr);

            // ctor with reply service, with ActiveObjectFactory
            explicit GenericProxy(const comm::InstanceID& iid, const comm::InterfaceKey& ikey
                    ,const char* name
                    ,const comm::InstanceID& reply_iid, const comm::InterfaceKey& repy_ikey
                    ,const char* reply_name
                    ,IGenericService* reply_svc
                    ,comm::ActiveObjectFactoryPtr aof
                    ,comm::LifecycleListener* l=nullptr);

            IGenericServiceC& operator*() const
            {
                return *operator->();
            }

            IGenericServiceC* operator->() const
            {
                return reinterpret_cast<IGenericServiceC*>(getImpl());
            }

        protected:
            // reply proxy
            GenericProxy(const comm::InstanceID& iid, const char* name);
    };

}
#endif // COMM_GENERIC_PROXY_HXX
