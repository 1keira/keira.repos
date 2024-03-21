/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceS_hxx.tmpl
*/
#ifndef COMM_BROKER_BROKERS_HXX
#define COMM_BROKER_BROKERS_HXX

#include <common/Macros.hxx>

#include <comm/commtypes.hxx>
#include <comm/commidltypes.hxx>
#include <comm/CallEvent.hxx>
#include <comm/broker/BrokerServiceRegistration.hxx>
#include <comm/broker/StructInstanceID.hxx>

#include <comm/broker/Definitions.hxx>


namespace comm
{
namespace broker
{

    /**
    \brief  The broker::Broker interface on tthe service side.
    \details
            A service instance needs to implement this interface.
    **/
    class BrokerS
    {
    public:
        BrokerS () {}
    // List of request methods
        /**
            
            \brief announces an agent to the broker
            \param agent_interface_id the InstanceID id of the calling agent's Agent Inteface.
                   The handle in the interface_id IS the agent_id.
        
            announce Method ID: 0
        **/
        virtual void announce(
            const CIPtr< comm::broker::InstanceID >& agent_interface_id
        ) = 0;
        /**
            
            \brief Registers a service
            \param svc_id the instance id of the service
            \param home_agent_id the agent id of the agent where the service is located
        
            registerService Method ID: 2
        **/
        virtual void registerService(
            const CIPtr< comm::broker::InstanceID >& svc_id,
            const uint16_t home_agent_id
        ) = 0;
        /**
            
            \brief Unregisters a service
            \param svc_id the instance id of the service
            \param home_agent_id the agent id of the agent where the service is located
        
            unregisterService Method ID: 3
        **/
        virtual void unregisterService(
            const CIPtr< comm::broker::InstanceID >& svc_id,
            const uint16_t home_agent_id
        ) = 0;
        /**
            
            \brief Looks up a service
            \param svc_id the instance id of the service
            \param caller_id the agent id of the calling agent
        
            lookupService Method ID: 1
        **/
        virtual void lookupService(
            const CIPtr< comm::broker::InstanceID >& svc_id,
            const uint16_t caller_id
        ) = 0;

        /*!
        \brief Informs the service about a connected client
        \param count The number of connected clients
        */
        virtual void clientConnected(uint32_t count
            ,const comm::CallContext& ctx
        ) {}

        /*!
        \brief Informs the service that a client disconnected
        \param count the number of connected clients
        */
        virtual void clientDisconnected(uint32_t count
            ,const comm::CallContext& ctx
        ) {}

        /*!
        \brief  Registers this service instance.
        \param  instance_no is the instance number for the service.
        \param  p a user provided ActiveObject factory. This gives control over the threads that call the service.
        \return false on success, true on error
        \errorindicator
                return code
        \errors
                any possible error generated from COMM
        */
        bool registerSelf(uint32_t instance_no, const comm::ActiveObjectFactoryPtr& factory, comm::LifecycleListener* l=nullptr)
        {
            if (m_registration.isAlive()) {
                ipl_raise(comm::Error, comm::error::SELF_ALREADY_REGISTERED
                            ,((ipl::string)m_registration.getInstanceID()).c_str());
                return true;
            }

            m_registration =
                BrokerServiceRegistration(comm::InstanceID (comm::InterfaceID(BINARY_UUID_COMM_BROKER_BROKER_REQUEST), instance_no), static_cast<BrokerS*>(this), l, factory );
            if (!m_registration.valid()) {
                comm::error::fatal( "can't create ServiceRegistration, OOM ", COMM_HERE);
                return true;
            }
            return m_registration.registerService();
        }

        /*!
        \brief  Registers this service instance.
        \param  instance_no is the instance number for the service interface.
        \param  l is the lifecycle listern instance
        \return false on success, true on error
        \errorindicator
                return code
        \errors
                any possible error generated from COMM
        */
        bool registerSelf(uint32_t instance_no, comm::LifecycleListener* l=nullptr)
        {
            if (m_registration.isAlive()) {
                ipl_raise(comm::Error, comm::error::SELF_ALREADY_REGISTERED
                            ,((ipl::string)m_registration.getInstanceID()).c_str());
                return true;
            }

            m_registration =
                BrokerServiceRegistration(comm::InstanceID (comm::InterfaceID(BINARY_UUID_COMM_BROKER_BROKER_REQUEST), instance_no), static_cast<BrokerS*>(this), l );
            if (!m_registration.valid()) {
                comm::error::fatal( "can't create ServiceRegistration, OOM ", COMM_HERE);
                return true;
            }
            return m_registration.registerService();
        }

        /*!
        \brief  Registers this service instance.
        \param  instance_no is the instance number for the service interface
        \param  l is the lifecycle listern instance
        \return false on success, true on error
        \errorindicator
                return code
        \errors
                any possible error generated from COMM
        */
        bool registerSelf(uint32_t instance_no, comm::LifecycleListener& l)
        {
            return registerSelf (instance_no, &l);
        }

        /*!
        \brief  Unregisters this service instance.
        \return false on success, true on error
        \errorindicator
                return code
        \errors
                none
        */
        bool unregisterSelf()
        {
            if (!m_registration.isAlive()) {
                // not registered -> nothing to do.
                return false;
            }
            m_registration.unregisterService();
            // must not be alive after unregistration
            IPL_ASSERT(!m_registration.isAlive());
            // let go of the reference
            m_registration = BrokerServiceRegistration();
            return false;
        }

        /*!
        \brief  Unregisters this service instance and calls a callback.
        \return false if the service is being unregistered, true on error
                The callback is called only if false is returned.
                Errors are:
                <ul>
                <li>the service registration is not valid
                <li>an unregisterSelf() or ServiceRegistration::unregisterService() or
                    or ServiceRegistration::unregisterAndNotify had already been called.
                <li>the callback is NULL.
                </ul>
        \errorindicator
                return code
        \errors
                \see comm::ServiceRegistration::unregisterAndNotify
        */
        bool unregisterSelf(comm::ServiceReleasedFct callback, void* ctx) // NOSONAR - must not be changed because of API compatibility
        {
            // to not race with the callback. we can't touch m_registration after
            // calling unregisterAndNotify
            // make a temporary copy
            BrokerServiceRegistration tmp{m_registration};
            // let go of the reference the member holds
            m_registration = BrokerServiceRegistration();
            // call unregisterAndNotify
            return tmp.unregisterAndNotify(callback, ctx);
        }

        virtual ~BrokerS()
        {
            // unregister in case it wasn't done by the caller.
            unregisterSelf();
        }

        // call ids
        void
        announceCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<BrokerS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 0;
            ce.assign(inst, mid);
        }
        void
        registerServiceCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<BrokerS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 2;
            ce.assign(inst, mid);
        }
        void
        unregisterServiceCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<BrokerS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 3;
            ce.assign(inst, mid);
        }
        void
        lookupServiceCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<BrokerS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 1;
            ce.assign(inst, mid);
        }

    protected:
        BrokerServiceRegistration m_registration;
    };

} //namespace comm
} //namespace broker
#endif// COMM_BROKER_BROKERS_HXX
