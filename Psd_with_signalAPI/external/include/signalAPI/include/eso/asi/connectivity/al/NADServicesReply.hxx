/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceReply_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_NADSERVICESREPLY_HXX
#define ASI_CONNECTIVITY_AL_NADSERVICESREPLY_HXX

#include <comm/commtypes.hxx>
#include <comm/commidltypes.hxx>
#include <comm/CallEvent.hxx>
#include <asi/connectivity/al/Definitions.hxx>

namespace asi
{
namespace connectivity
{
namespace al
{

    /**
    \brief  Declaration of the reply interface, which must be implemented by any user of this interface
    **/
    class NADServicesReply {

    public:
    // List of reply methods
            /**
            enableIMSResponse Method ID: 5
            **/
        virtual void enableIMSResponse(
            const asi::connectivity::al::ResultType result
        ) = 0;
            /**
            enable5GResponse Method ID: 3
            **/
        virtual void enable5GResponse(
            const asi::connectivity::al::ResultType result
        ) = 0;
            /**
            setNetworkSelectConfigurationResponse Method ID: 30
            **/
        virtual void setNetworkSelectConfigurationResponse(
            const asi::connectivity::al::ResultType result
        ) = 0;
            /**
            enterDormantModeResponse Method ID: 9
            **/
        virtual void enterDormantModeResponse(
            const asi::connectivity::al::ResultType result
        ) = 0;
            /**
            leaveDormantModeResponse Method ID: 17
            **/
        virtual void leaveDormantModeResponse(
            const asi::connectivity::al::ResultType result
        ) = 0;
            /**
            onSimRefreshed Method ID: 18
            **/
        virtual void onSimRefreshed(
            
        ) = 0;
            /**
            updNadError Method ID: 38
            **/
        virtual void updNadError(
            const asi::connectivity::al::NadError error,
            const uint32_t errorExt,
            const CIPtr< CIString >& errorReport
        ) = 0;
            /**
            *
         * NAD stored emergency numbers
         
            updEmergencyNumbers Method ID: 37
            **/
        virtual void updEmergencyNumbers(
            const CIPtr< CIStringArray >& numbers
        ) = 0;
            /**
            switchAirplaneModeResponse Method ID: 34
            **/
        virtual void switchAirplaneModeResponse(
            const asi::connectivity::al::ResultType result
        ) = 0;
            /**
            setSuspendModeResponse Method ID: 32
            **/
        virtual void setSuspendModeResponse(
            
        ) = 0;
            /**
            getEraGlonassStatusResponse Method ID: 11
            **/
        virtual void getEraGlonassStatusResponse(
            const asi::connectivity::al::EraGlonassStatus status
        ) = 0;
            /**
            switchProfileResponse Method ID: 36
            **/
        virtual void switchProfileResponse(
            const asi::connectivity::al::SimProfileId id,
            const asi::connectivity::al::ResultType result
        ) = 0;
            /**
            setAntennasScenario Method ID: 24
            **/
        virtual void setAntennasScenario(
            const asi::connectivity::al::ResultType result
        ) = 0;
            /**
            setLTE4AntennaExistenceResponse Method ID: 44
            **/
        virtual void setLTE4AntennaExistenceResponse(
            const asi::connectivity::al::ResultType result
        ) = 0;
            /**
            setMarketResponse Method ID: 28
            **/
        virtual void setMarketResponse(
            const asi::connectivity::al::ResultType result
        ) = 0;
            /**
            resetSimResponse Method ID: 22
            **/
        virtual void resetSimResponse(
            const asi::connectivity::al::ResultType result
        ) = 0;
            /**
            updateResetSim Method ID: 40
            **/
        virtual void updateResetSim(
            const bool isSuccessful
        ) = 0;
            /**
            resetModemResponse Method ID: 20
            **/
        virtual void resetModemResponse(
            const asi::connectivity::al::ResultType result
        ) = 0;
            /**
            getSIMFailureStatusResponse Method ID: 15
            **/
        virtual void getSIMFailureStatusResponse(
            const asi::connectivity::al::ResultType result
        ) = 0;
            /**
            updateSIMFailureStatus Method ID: 41
            **/
        virtual void updateSIMFailureStatus(
            const bool errorOccured,
            const asi::connectivity::al::SIMError simError
        ) = 0;
            /**
            getNWRejectionStatusResponse Method ID: 13
            **/
        virtual void getNWRejectionStatusResponse(
            const asi::connectivity::al::ResultType result
        ) = 0;
            /**
            updateNWRejectionStatus Method ID: 39
            **/
        virtual void updateNWRejectionStatus(
            const bool errorOccured,
            const bool isRjeceted,
            const int32_t rejectCause
        ) = 0;
            /**
            
        * For nadProc to inform VoiceProc about any timewindow in which it needs the system to stay awake
        * (due to modem actions that need to be executed or because the modem asks for it)
        
            updateWakeupReceived Method ID: 42
            **/
        virtual void updateWakeupReceived(
            
        ) = 0;
            /**
            allowNetworkSearchingResponse Method ID: 1
            **/
        virtual void allowNetworkSearchingResponse(
            const bool allow,
            const asi::connectivity::al::ResultType result
        ) = 0;
            /**
            enableJammingDetectionResponse Method ID: 7
            **/
        virtual void enableJammingDetectionResponse(
            const bool enable,
            const asi::connectivity::al::ResultType result
        ) = 0;
            /**
            setBatteryStateResponse Method ID: 26
            **/
        virtual void setBatteryStateResponse(
            const asi::connectivity::al::ResultType result
        ) = 0;

        /*!
        \brief Informs the service about a connected client
        \param count The number of connected clients
        */
        virtual void clientConnected(uint32_t count) {}

        /*!
        \brief Informs the service that a client disconnected
        \param count the number of connected clients
        */
        virtual void clientDisconnected(uint32_t count) {}

        // call ids
        void
        enableIMSResponseCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NADServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 5;
            ce.assign(inst, mid);
        }

        void
        enable5GResponseCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NADServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 3;
            ce.assign(inst, mid);
        }

        void
        setNetworkSelectConfigurationResponseCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NADServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 30;
            ce.assign(inst, mid);
        }

        void
        enterDormantModeResponseCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NADServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 9;
            ce.assign(inst, mid);
        }

        void
        leaveDormantModeResponseCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NADServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 17;
            ce.assign(inst, mid);
        }

        void
        onSimRefreshedCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NADServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 18;
            ce.assign(inst, mid);
        }

        void
        updNadErrorCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NADServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 38;
            ce.assign(inst, mid);
        }

        void
        updEmergencyNumbersCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NADServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 37;
            ce.assign(inst, mid);
        }

        void
        switchAirplaneModeResponseCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NADServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 34;
            ce.assign(inst, mid);
        }

        void
        setSuspendModeResponseCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NADServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 32;
            ce.assign(inst, mid);
        }

        void
        getEraGlonassStatusResponseCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NADServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 11;
            ce.assign(inst, mid);
        }

        void
        switchProfileResponseCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NADServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 36;
            ce.assign(inst, mid);
        }

        void
        setAntennasScenario_ResultTypeCallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<NADServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 24;
            ce.assign(inst, mid);
        }

        void
        setLTE4AntennaExistenceResponseCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NADServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 44;
            ce.assign(inst, mid);
        }

        void
        setMarketResponseCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NADServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 28;
            ce.assign(inst, mid);
        }

        void
        resetSimResponseCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NADServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 22;
            ce.assign(inst, mid);
        }

        void
        updateResetSimCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NADServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 40;
            ce.assign(inst, mid);
        }

        void
        resetModemResponseCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NADServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 20;
            ce.assign(inst, mid);
        }

        void
        getSIMFailureStatusResponseCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NADServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 15;
            ce.assign(inst, mid);
        }

        void
        updateSIMFailureStatusCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NADServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 41;
            ce.assign(inst, mid);
        }

        void
        getNWRejectionStatusResponseCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NADServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 13;
            ce.assign(inst, mid);
        }

        void
        updateNWRejectionStatusCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NADServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 39;
            ce.assign(inst, mid);
        }

        void
        updateWakeupReceivedCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NADServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 42;
            ce.assign(inst, mid);
        }

        void
        allowNetworkSearchingResponseCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NADServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 1;
            ce.assign(inst, mid);
        }

        void
        enableJammingDetectionResponseCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NADServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 7;
            ce.assign(inst, mid);
        }

        void
        setBatteryStateResponseCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NADServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 26;
            ce.assign(inst, mid);
        }


        virtual ~NADServicesReply() {}
    };

}//namespace asi
}//namespace connectivity
}//namespace al

#endif// ASI_CONNECTIVITY_AL_NADSERVICESREPLY_HXX
