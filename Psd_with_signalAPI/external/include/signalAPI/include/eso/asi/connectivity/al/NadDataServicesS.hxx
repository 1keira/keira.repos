/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceS_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_NADDATASERVICESS_HXX
#define ASI_CONNECTIVITY_AL_NADDATASERVICESS_HXX

#include <common/Macros.hxx>

#include <comm/commtypes.hxx>
#include <comm/commidltypes.hxx>
#include <comm/CallEvent.hxx>
#include <asi/connectivity/al/NadDataServicesServiceRegistration.hxx>
#include <asi/connectivity/al/StructDataConnectionInfo.hxx>
#include <asi/connectivity/al/StructSimDataConfig.hxx>

#include <asi/connectivity/al/Definitions.hxx>

#include <asi/connectivity/al/NadDataServicesProxyReply.hxx>
#include <asi/connectivity/al/NadDataServicesReplyS.hxx>

namespace asi
{
namespace connectivity
{
namespace al
{

    /**
    \brief  The al::NadDataServices interface on tthe service side.
    \details
            A service instance needs to implement this interface.
    **/
    class NadDataServicesS
    {
    public:
        NadDataServicesS () {}
    // List of request methods
        /**
            *
         * Request a data connection.
         * @param dataConnectionId the identifier of the data connection the action is performed for.
         * @param active "true" if a data connection must be is active, else "false".
         * @param ecmId the identifier of the ecm driver that should be used for the data connection
         *       (currently can be 0 –ecm0 or 1 –ecm1 ).
         *
         
            requestDataConnection Method ID: 2
        **/
        virtual void requestDataConnection(
            const int32_t dataConnectionId,
            const int32_t ecmId,
            const bool active
            ,NadDataServicesProxyReply& reply
        ) = 0;
        /**
            *
         * Confirm DataConnection.
         * @param dataConnectionId the identifier of the data connection the action is performed for.
         * @param ecmId the identifier of the ecm driver that should be used for the data connection
         *
         * @brief this is called after routing has been set up or dataCall/routing has been started externally
         * @note please treat a disconnection of the ASI in the same way as DataConnectionState::DISCONNECTED
	 
            updateConfirmDataConnection Method ID: 8
        **/
        virtual void updateConfirmDataConnection(
            const int32_t dataConnectionId,
            const int32_t ecmId,
            const asi::connectivity::al::DataConnectionState state
            ,NadDataServicesProxyReply& reply
        ) = 0;
        /**
            bipRouteResponse Method ID: 1
        **/
        virtual void bipRouteResponse(
            const asi::connectivity::al::BipRouteResult result
            ,NadDataServicesProxyReply& reply
        ) = 0;
        /**
            *
         * Set a configuration parameter e.g. APN, login or password for data connections.
         * @param request reqId  request identifier
         * @param request config  configuration, could be for multi apns
         * @param reply reqId  request identifier received by the request
         * @param reply result  the cme error code that was obtained as response for the set at command, -1 if timeout or nad is switched off or 0, in case of success.
         
            setConfiguration Method ID: 6
        **/
        virtual void setConfiguration(
            const int32_t reqId,
            const CIPtr< asi::connectivity::al::SimDataConfig >& config
            ,NadDataServicesProxyReply& reply
        ) = 0;
        /**
            *
         * Ask NAD to deattach and re-attach to Packet Domain service.
         * @param reply result holds the outcome of the request to de-attach/re-attach.
         
            requestPSReattach Method ID: 4
        **/
        virtual void requestPSReattach(
            
            NadDataServicesProxyReply& reply
        ) = 0;

        /*!
        \brief Informs the service about a connected client
        \param count The number of connected clients
        \param reply A proxy that can be used to reply to the connected client. If the client did
        not register its reply interface, calling valid() or isAlive() on reply will return false.
        In this case calling any other methods of the proxy will yield in undefined behaviour.
        */
        virtual void clientConnected(uint32_t count
            ,NadDataServicesProxyReply& reply
        ) {}

        /*!
        \brief Informs the service that a client disconnected
        \param count the number of connected clients
        \param reply The proxy to the disconnected client. It is not alive any more, but can be used for comparison
        if it ever was valid.
        */
        virtual void clientDisconnected(uint32_t count
            ,NadDataServicesProxyReply& reply
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
                NadDataServicesServiceRegistration(comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_AL_NADDATASERVICES_REQUEST), instance_no), static_cast<NadDataServicesS*>(this), l, factory );
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
                NadDataServicesServiceRegistration(comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_AL_NADDATASERVICES_REQUEST), instance_no), static_cast<NadDataServicesS*>(this), l );
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
            m_registration = NadDataServicesServiceRegistration();
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
            NadDataServicesServiceRegistration tmp{m_registration};
            // let go of the reference the member holds
            m_registration = NadDataServicesServiceRegistration();
            // call unregisterAndNotify
            return tmp.unregisterAndNotify(callback, ctx);
        }

        virtual ~NadDataServicesS()
        {
            // unregister in case it wasn't done by the caller.
            unregisterSelf();
        }

        // call ids
        void
        requestDataConnectionCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NadDataServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 2;
            ce.assign(inst, mid);
        }
        void
        updateConfirmDataConnectionCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NadDataServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 8;
            ce.assign(inst, mid);
        }
        void
        bipRouteResponseCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NadDataServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 1;
            ce.assign(inst, mid);
        }
        void
        setConfigurationCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NadDataServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 6;
            ce.assign(inst, mid);
        }
        void
        requestPSReattachCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NadDataServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 4;
            ce.assign(inst, mid);
        }

    protected:
        NadDataServicesServiceRegistration m_registration;
    };

} //namespace asi
} //namespace connectivity
} //namespace al
#endif// ASI_CONNECTIVITY_AL_NADDATASERVICESS_HXX
