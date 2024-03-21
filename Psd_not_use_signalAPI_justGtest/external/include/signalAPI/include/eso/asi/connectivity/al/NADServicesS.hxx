/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceS_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_NADSERVICESS_HXX
#define ASI_CONNECTIVITY_AL_NADSERVICESS_HXX

#include <common/Macros.hxx>

#include <comm/commtypes.hxx>
#include <comm/commidltypes.hxx>
#include <comm/CallEvent.hxx>
#include <asi/connectivity/al/NADServicesServiceRegistration.hxx>

#include <asi/connectivity/al/Definitions.hxx>

#include <asi/connectivity/al/NADServicesProxyReply.hxx>
#include <asi/connectivity/al/NADServicesReplyS.hxx>

namespace asi
{
namespace connectivity
{
namespace al
{

    /**
    \brief  The al::NADServices interface on tthe service side.
    \details
            A service instance needs to implement this interface.
    **/
    class NADServicesS
    {
    public:
        NADServicesS () {}
    // List of request methods
        /**
            *
         * Enables VoLTE (Mobile Originated voice call via VOIP) from the UE.
         * The voice call mode can be CS_ONLY, VOIP_ONLY, CS_PREFERRED or VOIP_PREFERRED.
         * if enable is set to true: VOIP_PREFERRED will be selected as voice call mode in NAD
         * if enable is set to false: CS_ONLY will be selected as voice call mode in NAD
         
            enableIMS Method ID: 4
        **/
        virtual void enableIMS(
            const bool enable
            ,NADServicesProxyReply& reply
        ) = 0;
        /**
            *
        * Configures modem to use 5G or not.
        * Deprecated. to be removed.
        
            enable5G Method ID: 2
        **/
        virtual void enable5G(
            const bool enable
            ,NADServicesProxyReply& reply
        ) = 0;
        /**
            *
        * Configures modem network selection parameters.
        
            setNetworkSelectConfiguration Method ID: 29
        **/
        virtual void setNetworkSelectConfiguration(
            const bool enable2G,
            const bool enable3G,
            const bool enable4G,
            const bool enable4GCA,
            const bool enable5GNSA,
            const bool enable5GSA,
            const bool enable5GSACA,
            const bool enableFR2Bands
            ,NADServicesProxyReply& reply
        ) = 0;
        /**
            enterDormantMode Method ID: 8
        **/
        virtual void enterDormantMode(
            
            NADServicesProxyReply& reply
        ) = 0;
        /**
            leaveDormantMode Method ID: 16
        **/
        virtual void leaveDormantMode(
            
            NADServicesProxyReply& reply
        ) = 0;
        /**
            *
         * Switch on or off the airplane mode. The SIM card will be powered down like an unpluged SIM card.
         * @param on true to switch on the airplane mode, false to switch off the airplane mode.
         
            switchAirplaneMode Method ID: 33
        **/
        virtual void switchAirplaneMode(
            const asi::connectivity::al::AirplaneMode airplaneMode
            ,NADServicesProxyReply& reply
        ) = 0;
        /**
            setSuspendMode Method ID: 31
        **/
        virtual void setSuspendMode(
            const bool on
            ,NADServicesProxyReply& reply
        ) = 0;
        /**
            getEraGlonassStatus Method ID: 10
        **/
        virtual void getEraGlonassStatus(
            
            NADServicesProxyReply& reply
        ) = 0;
        /**
            switchProfile Method ID: 35
        **/
        virtual void switchProfile(
            const asi::connectivity::al::SimProfileId id
            ,NADServicesProxyReply& reply
        ) = 0;
        /**
            setAntennasScenario Method ID: 23
        **/
        virtual void setAntennasScenario(
            const asi::connectivity::al::AntennasScenario scenario
            ,NADServicesProxyReply& reply
        ) = 0;
        /**
            setLTE4AntennaExistence Method ID: 43
        **/
        virtual void setLTE4AntennaExistence(
            const bool exists
            ,NADServicesProxyReply& reply
        ) = 0;
        /**
            
        * Method used to forward the Verkaufsland from Adaptations to NAD
        
            setMarket Method ID: 27
        **/
        virtual void setMarket(
            const CIPtr< CIString >& country
            ,NADServicesProxyReply& reply
        ) = 0;
        /**
            
         * Methods introduced for the recovery managemnent
         
            resetSim Method ID: 21
        **/
        virtual void resetSim(
            
            NADServicesProxyReply& reply
        ) = 0;
        /**
            
         * Method used to trigger a Modem reset.
         * Response will report feedback of restart procedure:
         * RESULT_TYPE_OK, on success or RESULT_TYPE_ERROR, if procedure fails.
         * It is expected that a resetModem request will also lead to a
         * temporary NAD_OFF of NadInformationService::NadState attribute.
         
            resetModem Method ID: 19
        **/
        virtual void resetModem(
            
            NADServicesProxyReply& reply
        ) = 0;
        /**
            getSIMFailureStatusRequest Method ID: 14
        **/
        virtual void getSIMFailureStatusRequest(
            
            NADServicesProxyReply& reply
        ) = 0;
        /**
            getNWRejectionStatusRequest Method ID: 12
        **/
        virtual void getNWRejectionStatusRequest(
            
            NADServicesProxyReply& reply
        ) = 0;
        /**
            
        * For VoiceProc to forward the OOC state transitions between CBOX_VTS_ACTIVE_CAN-OFF_SEARCHING
        * and CBOX_VTS_ACTIVE_CAN-OFF_SEARCHING_PAUSED to control the network searches on the modem
        
            allowNetworkSearching Method ID: 0
        **/
        virtual void allowNetworkSearching(
            const bool allow
            ,NADServicesProxyReply& reply
        ) = 0;
        /**
            
        * For VoiceProc to forward the OOC request to turn jamming detection on based on the OOC state transition to
        * CBOX_POWER-SAVE_CAN-OFF_VTS ALARM CHECK
        
            enableJammingDetection Method ID: 6
        **/
        virtual void enableJammingDetection(
            const bool enable
            ,NADServicesProxyReply& reply
        ) = 0;
        /**
            
        * For VoiceProc to forward actual battery state reported by OOC
        
            setBatteryState Method ID: 25
        **/
        virtual void setBatteryState(
            const asi::connectivity::al::BatteryState state
            ,NADServicesProxyReply& reply
        ) = 0;

        /*!
        \brief Informs the service about a connected client
        \param count The number of connected clients
        \param reply A proxy that can be used to reply to the connected client. If the client did
        not register its reply interface, calling valid() or isAlive() on reply will return false.
        In this case calling any other methods of the proxy will yield in undefined behaviour.
        */
        virtual void clientConnected(uint32_t count
            ,NADServicesProxyReply& reply
        ) {}

        /*!
        \brief Informs the service that a client disconnected
        \param count the number of connected clients
        \param reply The proxy to the disconnected client. It is not alive any more, but can be used for comparison
        if it ever was valid.
        */
        virtual void clientDisconnected(uint32_t count
            ,NADServicesProxyReply& reply
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
                NADServicesServiceRegistration(comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_AL_NADSERVICES_REQUEST), instance_no), static_cast<NADServicesS*>(this), l, factory );
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
                NADServicesServiceRegistration(comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_AL_NADSERVICES_REQUEST), instance_no), static_cast<NADServicesS*>(this), l );
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
            m_registration = NADServicesServiceRegistration();
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
            NADServicesServiceRegistration tmp{m_registration};
            // let go of the reference the member holds
            m_registration = NADServicesServiceRegistration();
            // call unregisterAndNotify
            return tmp.unregisterAndNotify(callback, ctx);
        }

        virtual ~NADServicesS()
        {
            // unregister in case it wasn't done by the caller.
            unregisterSelf();
        }

        // call ids
        void
        enableIMSCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NADServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 4;
            ce.assign(inst, mid);
        }
        void
        enable5GCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NADServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 2;
            ce.assign(inst, mid);
        }
        void
        setNetworkSelectConfigurationCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NADServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 29;
            ce.assign(inst, mid);
        }
        void
        enterDormantModeCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NADServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 8;
            ce.assign(inst, mid);
        }
        void
        leaveDormantModeCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NADServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 16;
            ce.assign(inst, mid);
        }
        void
        switchAirplaneModeCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NADServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 33;
            ce.assign(inst, mid);
        }
        void
        setSuspendModeCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NADServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 31;
            ce.assign(inst, mid);
        }
        void
        getEraGlonassStatusCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NADServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 10;
            ce.assign(inst, mid);
        }
        void
        switchProfileCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NADServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 35;
            ce.assign(inst, mid);
        }
        void
        setAntennasScenario_AntennasScenarioCallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<NADServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 23;
            ce.assign(inst, mid);
        }
        void
        setLTE4AntennaExistenceCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NADServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 43;
            ce.assign(inst, mid);
        }
        void
        setMarketCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NADServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 27;
            ce.assign(inst, mid);
        }
        void
        resetSimCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NADServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 21;
            ce.assign(inst, mid);
        }
        void
        resetModemCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NADServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 19;
            ce.assign(inst, mid);
        }
        void
        getSIMFailureStatusRequestCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NADServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 14;
            ce.assign(inst, mid);
        }
        void
        getNWRejectionStatusRequestCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NADServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 12;
            ce.assign(inst, mid);
        }
        void
        allowNetworkSearchingCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NADServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 0;
            ce.assign(inst, mid);
        }
        void
        enableJammingDetectionCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NADServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 6;
            ce.assign(inst, mid);
        }
        void
        setBatteryStateCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NADServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 25;
            ce.assign(inst, mid);
        }

    protected:
        NADServicesServiceRegistration m_registration;
    };

} //namespace asi
} //namespace connectivity
} //namespace al
#endif// ASI_CONNECTIVITY_AL_NADSERVICESS_HXX
