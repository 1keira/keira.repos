/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/


#ifndef COMM_GENERIC_SERVICEREGISTRATION_HXX
#define COMM_GENERIC_SERVICEREGISTRATION_HXX

#include <common/types/string.hxx>
#include <comm/ServiceRegistration.hxx>

namespace comm {

    class IGenericService;


    /**
        \brief The service registration instance for an IGenericService implementation
    */
    class GenericServiceRegistration  : public comm::ServiceRegistration {
        public:
            /**
              \brief constructor with instance id, interface key, name and lifecycle listener
              \param    iid is the instance id, which identifies the service identity
              \param    ikey ist the interface key
              \param    name is the interface name, the contents are it not copied, name must remain valid
              for as long as this object lives.
              \param    svc is the IGenericService implementation
              \param    l is a pointer to a listener for the lifecycle of the registration. This parameter is optional, may be 0
              */
            GenericServiceRegistration (const comm::InstanceID& iid
                                        ,const comm::InterfaceKey& ikey
                                        ,const char* name
                                        ,IGenericService* svc
                                        ,comm::LifecycleListener* l=nullptr);

            /**
              \brief constructor with instance id, interface key, name and ActiveobjectFactory and lifecycle listener
              \param    iid the instance id, which identifies the service identity
              \param    ikey the interface key
              \param    name is the interface name, the contents are it not copied, name must remain valid
              for as long as this object lives.
              \param    svc the IGenericService implementation
              \param    aof an ActiveObjectFactory
              \param    l is a pointer to a listener for the lifecycle of the registration. This parameter is optional, may be 0
              */
            GenericServiceRegistration (const comm::InstanceID& iid
                                        ,const comm::InterfaceKey& ikey
                                        ,const char* name
                                        ,IGenericService* svc
                                        ,const ActiveObjectFactoryPtr aof
                                        ,comm::LifecycleListener* l=nullptr);

            // default ctor
            GenericServiceRegistration();

            ~GenericServiceRegistration() override;
    };

}
#endif // COMM_GENERIC_SERVICEREGISTRATION_HXX

