/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/
#ifndef COMM_GENERICSERVICEBASE_HXX
#define COMM_GENERICSERVICEBASE_HXX

#include <vector>
#include <comm/IGenericService.hxx>
#include <comm/GenericServiceRegistration.hxx>
#include <comm/Proxy.hxx>
#include <comm/ServiceVersion.hxx>
#include <util/serializer/SerializerTag.hxx>

namespace comm {

    /**
      \brief A base class for IGenericService implementations that can register and unregister itself.
     **/
    class COMM_EXPORT GenericServiceBase : public comm::IGenericService {
        public:

            GenericServiceBase (const comm::InstanceID iid, const InterfaceKey& ikey, const char* name
                    ,LifecycleListener* l=nullptr);
            GenericServiceBase (const comm::InstanceID iid, const InterfaceKey& ikey, const char* name
                    ,const ActiveObjectFactoryPtr& aof
                    ,LifecycleListener* l=nullptr);
            GenericServiceBase (const comm::InstanceID iid, const comm::ServiceVersion& semver, const char* name
                    ,LifecycleListener* l=nullptr);
            GenericServiceBase (const comm::InstanceID iid, const comm::ServiceVersion& semver, const char* name
                    ,const ActiveObjectFactoryPtr& aof
                    ,LifecycleListener* l=nullptr);
            GenericServiceBase() = delete;
            GenericServiceBase(const GenericServiceBase&) = delete;
            GenericServiceBase(GenericServiceBase&&) = delete;
            GenericServiceBase& operator=(const GenericServiceBase&)=delete;
            GenericServiceBase& operator=(GenericServiceBase&&)=delete;
            ~GenericServiceBase() override;

            /*!
              \brief Registers the service.
              \errorindicator
              return code
              \errors
              any possible error generated from COMM
              */
            bool registerSelf();

            /*!
              \brief Registers the service that will only use the passed serializer.
              \errorindicator
              return code
              \errors
              any possible error generated from COMM
              */

            bool registerSelf( util::serializer::SerializerTag tag );

            /*!
              \brief Unregisters the service.
              \return false on success, true on error
              \errorindicator
              return code
              \errors
              none
              */
            bool unregisterSelf();

            /*!
              \brief  Unregisters this service instance and calls a callback.
              \return false if the service is being unregistered, true on error
              The callback is called only if false is returned.
              Errors are:
              <ul>
                <li>the service registration is not valid
                <li>any call that unregisters the service had already been called.
                <li>the callback is NULL.
              </ul>
            \errorindicator
                    return code
            \errors
                    \see comm::ServiceRegistration::unregisterAndNotify
            */
            // Note: we'll stick with the same callback API as in comm::ServiceRegistration::unregisterAndNotify for consistency
            // even though c++11 would allow better
            bool unregisterSelf(comm::ServiceReleasedFct callback, void* ctx); // NOSONAR - must not be changed because of API compatibility

        protected:
            GenericServiceRegistration m_registration;
            InstanceID m_iid;
            InterfaceKey m_ikey;
            ipl::string m_name;
            LifecycleListener* m_listener;
            ActiveObjectFactoryPtr m_aof;
    };
}
#endif // COMM_GENERICSERVICEBASE_HXX

