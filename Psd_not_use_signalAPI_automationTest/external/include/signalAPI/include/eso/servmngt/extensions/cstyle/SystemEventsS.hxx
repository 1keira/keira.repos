/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleInterfaceS_hxx.tmpl
*/
#ifndef SERVMNGT_EXTENSIONS_SYSTEMEVENTSS_CSTYLE_HXX
#define SERVMNGT_EXTENSIONS_SYSTEMEVENTSS_CSTYLE_HXX

#include <common/Macros.hxx>

#include <comm/commtypes.hxx>
#include <comm/commidltypes.hxx>
#include <comm/CallEvent.hxx>
#include <servmngt/extensions/cstyle/SystemEventsServiceRegistration.hxx>
#include <servmngt/extensions/cstyle/Definitions.hxx>
#include <servmngt/extensions/cstyle/SystemEventsProxyReply.hxx>
#include <servmngt/extensions/cstyle/SystemEventsReplyS.hxx>

namespace servmngt
{
namespace extensions
{
namespace cstyle
{

    /**
    \brief  The extensions::cstyle::SystemEvents interface on tthe service side.
    \details
            A service instance needs to implement this interface.
    **/
    class SystemEventsS
    {
    public:
        SystemEventsS () {}
    // List of request methods
        /**
            
        register as servicemanager system event listener. From now the process is
        informed by the servicemanager about system events
        \param [in] name
            is the name which identifies the application

        
            registerMe Method ID: 0
        **/
        virtual void registerMe(
            const ipl::string* name
            ,SystemEventsProxyReply& reply
        ) = 0;
        /**
             remove registration 
            unregisterMe Method ID: 7
        **/
        virtual void unregisterMe(
            
            SystemEventsProxyReply& reply
        ) = 0;
        /**
            
        acknowleded a shutdownRequest()
        
            shutdownRequestedAck Method ID: 4
        **/
        virtual void shutdownRequestedAck(
            
            SystemEventsProxyReply& reply
        ) = 0;
        /**
            
        acknowleded a shutdownRequest()
        
            shutdownCancelledAck Method ID: 2
        **/
        virtual void shutdownCancelledAck(
            
            SystemEventsProxyReply& reply
        ) = 0;
        /**
            
        acknowleded a suspendRequest
        
            suspendAck Method ID: 5
        **/
        virtual void suspendAck(
            
            SystemEventsProxyReply& reply
        ) = 0;

        /*!
        \brief Informs the service about a connected client
        \param count The number of connected clients
        \param reply A proxy that can be used to reply to the connected client. If the client did
        not register its reply interface, calling valid() or isAlive() on reply will return false.
        In this case calling any other methods of the proxy will yield in undefined behaviour.
        */
        virtual void clientConnected(uint32_t count
            ,SystemEventsProxyReply& reply
        ) {}

        /*!
        \brief Informs the service that a client disconnected
        \param count the number of connected clients
        \param reply The proxy to the disconnected client. It is not alive any more, but can be used for comparison
        if it ever was valid.
        */
        virtual void clientDisconnected(uint32_t count
            ,SystemEventsProxyReply& reply
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
                SystemEventsServiceRegistration(comm::InstanceID (comm::InterfaceID(BINARY_UUID_SERVMNGT_EXTENSIONS_SYSTEMEVENTS_REQUEST), instance_no), static_cast<SystemEventsS*>(this), l, factory );
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
                SystemEventsServiceRegistration(comm::InstanceID (comm::InterfaceID(BINARY_UUID_SERVMNGT_EXTENSIONS_SYSTEMEVENTS_REQUEST), instance_no), static_cast<SystemEventsS*>(this), l );
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
            m_registration = SystemEventsServiceRegistration();
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
        bool unregisterSelf(comm::ServiceReleasedFct callback, void* ctx)
        {
            if ( m_registration.unregisterAndNotify(callback, ctx) ) {
                return true;
            }
            // let go of the reference
            m_registration = SystemEventsServiceRegistration();
            return false;
        }

        virtual ~SystemEventsS()
        {
            // unregister in case it wasn't done by the caller.
            unregisterSelf();
        }

        // call ids
        void
        registerMeCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<SystemEventsS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 0;
            ce.assign(inst, mid);
        }
        void
        unregisterMeCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<SystemEventsS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 7;
            ce.assign(inst, mid);
        }
        void
        shutdownRequestedAckCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<SystemEventsS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 4;
            ce.assign(inst, mid);
        }
        void
        shutdownCancelledAckCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<SystemEventsS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 2;
            ce.assign(inst, mid);
        }
        void
        suspendAckCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<SystemEventsS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 5;
            ce.assign(inst, mid);
        }

    protected:
        SystemEventsServiceRegistration m_registration;
    };

} // namespace cstyle
} //namespace servmngt
} //namespace extensions
#endif// SERVMNGT_EXTENSIONS_SYSTEMEVENTSS_CSTYLE_HXX
