/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceS_hxx.tmpl
*/
#ifndef SERVMNGT_ISERVICEMANAGERS_HXX
#define SERVMNGT_ISERVICEMANAGERS_HXX

#include <common/Macros.hxx>

#include <comm/commtypes.hxx>
#include <comm/commidltypes.hxx>
#include <comm/CallEvent.hxx>
#include <servmngt/IServiceManagerServiceRegistration.hxx>

#include <servmngt/Definitions.hxx>

#include <servmngt/IServiceManagerProxyReply.hxx>
#include <servmngt/IServiceManagerReplyS.hxx>

namespace servmngt
{

    /**
    \brief  The servmngt::IServiceManager interface on tthe service side.
    \details
            A service instance needs to implement this interface.
        Interface between Service Manager and Application
    **/
    class IServiceManagerS
    {
    public:
        IServiceManagerS () {}
    // List of request methods
        /**
            initializeApp Method ID: 2
        **/
        virtual void initializeApp(
            const uint32_t app_id,
            const uint32_t bundle_id,
            const servmngt::SystemRunMode system_run_mode,
            const uint32_t app_run_mode,
            const servmngt::PersistenceAccessMode ps_access_mode
            ,IServiceManagerProxyReply& reply
        ) = 0;
        /**
            run Method ID: 15
        **/
        virtual void run(
            
            IServiceManagerProxyReply& reply
        ) = 0;
        /**
            stop Method ID: 20
        **/
        virtual void stop(
            
            IServiceManagerProxyReply& reply
        ) = 0;
        /**
            setSystemRunMode Method ID: 19
        **/
        virtual void setSystemRunMode(
            const servmngt::SystemRunMode run_mode
            ,IServiceManagerProxyReply& reply
        ) = 0;
        /**
            
        request to stop the process 
        
            exitProcess Method ID: 1
        **/
        virtual void exitProcess(
            
            IServiceManagerProxyReply& reply
        ) = 0;
        /**
            setAppRunMode Method ID: 16
        **/
        virtual void setAppRunMode(
            const uint32_t run_mode
            ,IServiceManagerProxyReply& reply
        ) = 0;
        /**
            setPersistenceAccess Method ID: 18
        **/
        virtual void setPersistenceAccess(
            const servmngt::PersistenceAccessMode ps_access
            ,IServiceManagerProxyReply& reply
        ) = 0;
        /**
            requestPersistenceFlush Method ID: 11
        **/
        virtual void requestPersistenceFlush(
            const servmngt::PersistenceAccessMode ps_access_after_flush
            ,IServiceManagerProxyReply& reply
        ) = 0;
        /**
            systemEventOccured Method ID: 22
        **/
        virtual void systemEventOccured(
            const servmngt::SystemEvent event
            ,IServiceManagerProxyReply& reply
        ) = 0;
        /**
            userCommandDone Method ID: 24
        **/
        virtual void userCommandDone(
            const uint32_t id,
            const servmngt::UserCommandResult result
            ,IServiceManagerProxyReply& reply
        ) = 0;
        /**
            requestSuspend Method ID: 13
        **/
        virtual void requestSuspend(
            const servmngt::SuspendRequest request,
            const bool acknowledgeExpected
            ,IServiceManagerProxyReply& reply
        ) = 0;
        /**
            
            a project defined event has happended and is distributed
            to the application. The possible values and there meaning
            is project defined and has to be described on project level

            This command has not to be acknowledged by the user application
        
            customEventOccured Method ID: 0
        **/
        virtual void customEventOccured(
            const uint32_t event
            ,IServiceManagerProxyReply& reply
        ) = 0;
        /**
            requestAliveMsg Method ID: 10
        **/
        virtual void requestAliveMsg(
            
            IServiceManagerProxyReply& reply
        ) = 0;

        /*!
        \brief Informs the service about a connected client
        \param count The number of connected clients
        \param reply A proxy that can be used to reply to the connected client. If the client did
        not register its reply interface, calling valid() or isAlive() on reply will return false.
        In this case calling any other methods of the proxy will yield in undefined behaviour.
        */
        virtual void clientConnected(uint32_t count
            ,IServiceManagerProxyReply& reply
        ) {}

        /*!
        \brief Informs the service that a client disconnected
        \param count the number of connected clients
        \param reply The proxy to the disconnected client. It is not alive any more, but can be used for comparison
        if it ever was valid.
        */
        virtual void clientDisconnected(uint32_t count
            ,IServiceManagerProxyReply& reply
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
                IServiceManagerServiceRegistration(comm::InstanceID (comm::InterfaceID(BINARY_UUID_SERVMNGT_ISERVICEMANAGER_REQUEST), instance_no), static_cast<IServiceManagerS*>(this), l, factory );
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
                IServiceManagerServiceRegistration(comm::InstanceID (comm::InterfaceID(BINARY_UUID_SERVMNGT_ISERVICEMANAGER_REQUEST), instance_no), static_cast<IServiceManagerS*>(this), l );
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
            m_registration = IServiceManagerServiceRegistration();
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
            IServiceManagerServiceRegistration tmp{m_registration};
            // let go of the reference the member holds
            m_registration = IServiceManagerServiceRegistration();
            // call unregisterAndNotify
            return tmp.unregisterAndNotify(callback, ctx);
        }

        virtual ~IServiceManagerS()
        {
            // unregister in case it wasn't done by the caller.
            unregisterSelf();
        }

        // call ids
        void
        initializeAppCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IServiceManagerS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 2;
            ce.assign(inst, mid);
        }
        void
        runCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IServiceManagerS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 15;
            ce.assign(inst, mid);
        }
        void
        stopCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IServiceManagerS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 20;
            ce.assign(inst, mid);
        }
        void
        setSystemRunModeCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IServiceManagerS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 19;
            ce.assign(inst, mid);
        }
        void
        exitProcessCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IServiceManagerS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 1;
            ce.assign(inst, mid);
        }
        void
        setAppRunModeCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IServiceManagerS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 16;
            ce.assign(inst, mid);
        }
        void
        setPersistenceAccessCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IServiceManagerS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 18;
            ce.assign(inst, mid);
        }
        void
        requestPersistenceFlushCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IServiceManagerS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 11;
            ce.assign(inst, mid);
        }
        void
        systemEventOccuredCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IServiceManagerS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 22;
            ce.assign(inst, mid);
        }
        void
        userCommandDoneCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IServiceManagerS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 24;
            ce.assign(inst, mid);
        }
        void
        requestSuspendCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IServiceManagerS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 13;
            ce.assign(inst, mid);
        }
        void
        customEventOccuredCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IServiceManagerS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 0;
            ce.assign(inst, mid);
        }
        void
        requestAliveMsgCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IServiceManagerS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 10;
            ce.assign(inst, mid);
        }

    protected:
        IServiceManagerServiceRegistration m_registration;
    };

} //namespace servmngt
#endif// SERVMNGT_ISERVICEMANAGERS_HXX
