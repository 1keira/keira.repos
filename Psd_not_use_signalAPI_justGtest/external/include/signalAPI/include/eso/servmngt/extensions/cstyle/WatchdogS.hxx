/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleInterfaceS_hxx.tmpl
*/
#ifndef SERVMNGT_EXTENSIONS_WATCHDOGS_CSTYLE_HXX
#define SERVMNGT_EXTENSIONS_WATCHDOGS_CSTYLE_HXX

#include <common/Macros.hxx>

#include <comm/commtypes.hxx>
#include <comm/commidltypes.hxx>
#include <comm/CallEvent.hxx>
#include <servmngt/extensions/cstyle/WatchdogServiceRegistration.hxx>
#include <servmngt/extensions/cstyle/Definitions.hxx>
#include <servmngt/extensions/cstyle/WatchdogProxyReply.hxx>
#include <servmngt/extensions/cstyle/WatchdogReplyS.hxx>

namespace servmngt
{
namespace extensions
{
namespace cstyle
{

    /**
    \brief  The extensions::cstyle::Watchdog interface on tthe service side.
    \details
            A service instance needs to implement this interface.
        Watchdog Interface of the servicemanager
      It can be used by any application which like to be watchdog supervised by the
      servicemanager

      An application can register itself at the servicemanager, and will then be
      supervised. 
      In case of a detected WD failure by the servicemanager, the SM
      can kill the process and, if configured in the servicemgr_restart.json, 
      restarted
    **/
    class WatchdogS
    {
    public:
        WatchdogS () {}
    // List of request methods
        /**
            
        register at the servicemanager watchdog. From now the process is
        supervised by the servicemanager
        \param [in] name
            is the name which identifies the application
        \param [in] pid
            is the OS process-id. The SM can use it for killing the process

        \param [in] period_ms
            is the watchdog period in milliseconds
        
            registerMe Method ID: 0
        **/
        virtual void registerMe(
            const ipl::string* name,
            const uint32_t pid,
            const uint32_t period_ms
            ,WatchdogProxyReply& reply
        ) = 0;
        /**
            unregisterMe Method ID: 3
        **/
        virtual void unregisterMe(
            const ipl::string* name
            ,WatchdogProxyReply& reply
        ) = 0;
        /**
            
            Acknowledge to requestAlive
        
            responseAlive Method ID: 2
        **/
        virtual void responseAlive(
            
            WatchdogProxyReply& reply
        ) = 0;

        /*!
        \brief Informs the service about a connected client
        \param count The number of connected clients
        \param reply A proxy that can be used to reply to the connected client. If the client did
        not register its reply interface, calling valid() or isAlive() on reply will return false.
        In this case calling any other methods of the proxy will yield in undefined behaviour.
        */
        virtual void clientConnected(uint32_t count
            ,WatchdogProxyReply& reply
        ) {}

        /*!
        \brief Informs the service that a client disconnected
        \param count the number of connected clients
        \param reply The proxy to the disconnected client. It is not alive any more, but can be used for comparison
        if it ever was valid.
        */
        virtual void clientDisconnected(uint32_t count
            ,WatchdogProxyReply& reply
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
                WatchdogServiceRegistration(comm::InstanceID (comm::InterfaceID(BINARY_UUID_SERVMNGT_EXTENSIONS_WATCHDOG_REQUEST), instance_no), static_cast<WatchdogS*>(this), l, factory );
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
                WatchdogServiceRegistration(comm::InstanceID (comm::InterfaceID(BINARY_UUID_SERVMNGT_EXTENSIONS_WATCHDOG_REQUEST), instance_no), static_cast<WatchdogS*>(this), l );
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
            m_registration = WatchdogServiceRegistration();
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
            m_registration = WatchdogServiceRegistration();
            return false;
        }

        virtual ~WatchdogS()
        {
            // unregister in case it wasn't done by the caller.
            unregisterSelf();
        }

        // call ids
        void
        registerMeCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<WatchdogS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 0;
            ce.assign(inst, mid);
        }
        void
        unregisterMeCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<WatchdogS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 3;
            ce.assign(inst, mid);
        }
        void
        responseAliveCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<WatchdogS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 2;
            ce.assign(inst, mid);
        }

    protected:
        WatchdogServiceRegistration m_registration;
    };

} // namespace cstyle
} //namespace servmngt
} //namespace extensions
#endif// SERVMNGT_EXTENSIONS_WATCHDOGS_CSTYLE_HXX
