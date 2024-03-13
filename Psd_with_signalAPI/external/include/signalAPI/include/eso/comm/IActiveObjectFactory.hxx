#ifndef COMM_IACTIVE_OBJ_FACTORY_HXX
#define COMM_IACTIVE_OBJ_FACTORY_HXX
/**
    Copyright e.solutions GmbH
    All rights reserved
    Authors:
        Stefan Bittner
 **/

// project-specific header files
#include <comm/comm_dso.h>
#include <comm/commtypes.hxx>
#include <util/SharedPtr.hxx>

namespace comm {
    class ActiveObject;
    typedef util::SharedPtr<ActiveObject> ActiveObjectPtr;
    class ServiceRegistration;
    class AOFactories;

    /**
        \brief An interface of an ActiveObject factory. 

        An implementation of this interface will create new instances of ActiveObjects using some
        implementation specific policy. 
        An implementation must also keep all created instances internally for later retrieval.
    */
    class COMM_EXPORT IActiveObjectFactory {
        public:
            IActiveObjectFactory() {}
            virtual ~IActiveObjectFactory() {}

            /**
                \brief Returns an ActiveObject instance for a comm service instance id.

                    Returns an ActiveObject instance for a given InstanceID.
                    Implementations may choose any policy to map InstanceID to an ActiveObject instance. 
                    This call has create or get semantics. 
                    If the policy dictates to create an ActiveObject instance for the given InstanceID and 
                    that instance had not yet been created, it will be created and returned, otherwise an
                    earlier created instance mapped to the given InstanceID will be returned.
                    An ActiveObject created with this method will have a thread running with default priority.
            
                \return Shared Pointer to the requested ActiveObject. May return an non valid shared pointer
                        (valid() on the shared pointer returns false) if we run out of memory.
                    
            */
            virtual ActiveObjectPtr getActiveObject(const comm::InstanceID&) = 0;

            /**
                \brief Returns an ActiveObject instance for a comm service instance id.

                    Returns an ActiveObject instance for a comm service instance id. This call never
                    creates a new ActiveObject instance. If there is no ActiveObject for the given
                    InstanceID, a non valid shared pointer (valid() on the shared pointer returns false)
                    is returned.
                    An ActiveObject created with this method will have a thread running with default priority.

                return Shared Pointer to the requested ActiveObject. If there is no ActiveObject for the given
                    InstanceID, a non valid shared pointer (valid() on the shared pointer returns false)
                    is returned.
            */
            virtual ActiveObjectPtr hasActiveObject(const comm::InstanceID&) = 0;

            /**
                \brief Returns an ActiveObject instance for a comm service registration.

                    Returns an ActiveObject instance for a given InstanceID.
                    Implementations may choose any policy to map InstanceID to an ActiveObject instance. 
                    This call has create or get semantics. 
                    If the policy dictates to create an ActiveObject instance for the given InstanceID and 
                    that instance had not yet been created, it will be created and returned, otherwise an
                    earlier created instance mapped to the given InstanceID will be returned.
                    An ActiveObject created with this method will have a thread running with a priority that is 
                    set by framework configuration.
            
                \return Shared Pointer to the requested ActiveObject. May return an non valid shared pointer
                        (valid() on the shared pointer returns false) if we run out of memory.
                    
            */
            virtual ActiveObjectPtr getActiveObject(const comm::ServiceRegistration&) = 0;

        private:            
            // not copy-assignable
            IActiveObjectFactory(const IActiveObjectFactory&);
            IActiveObjectFactory& operator=(const IActiveObjectFactory&);

            /** Stops all pooled Active Objects */
            virtual void stop() = 0;

            friend class AOFactories;
    };

    typedef util::SharedPtr<IActiveObjectFactory> ActiveObjectFactoryPtr;

} // namespace comm

#endif // COMM_IACTIVE_OBJ_FACTORY_HXX

