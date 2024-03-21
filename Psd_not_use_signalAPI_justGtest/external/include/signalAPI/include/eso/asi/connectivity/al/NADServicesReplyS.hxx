/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceReplyS_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_NADSERVICES_REPLYS_HXX
#define ASI_CONNECTIVITY_AL_NADSERVICES_REPLYS_HXX
#include <ipl_config.h>
#include <comm/commidltypes.hxx>
#include <asi/connectivity/al/Definitions.hxx>
namespace asi
{
namespace connectivity
{
namespace al
{

    /**
    \brief  Interface declaration, which is implemented by the proxy, and used/called by any user of this interface
    **/
    class NADServicesReplyS
    {
    public:
        // List of reply methods
            /**
            enableIMSResponse Method ID: 5
            **/
        virtual bool enableIMSResponse (
            const asi::connectivity::al::ResultType result
        ) IPL_NOEXCEPT = 0;

            /**
            enable5GResponse Method ID: 3
            **/
        virtual bool enable5GResponse (
            const asi::connectivity::al::ResultType result
        ) IPL_NOEXCEPT = 0;

            /**
            setNetworkSelectConfigurationResponse Method ID: 30
            **/
        virtual bool setNetworkSelectConfigurationResponse (
            const asi::connectivity::al::ResultType result
        ) IPL_NOEXCEPT = 0;

            /**
            enterDormantModeResponse Method ID: 9
            **/
        virtual bool enterDormantModeResponse (
            const asi::connectivity::al::ResultType result
        ) IPL_NOEXCEPT = 0;

            /**
            leaveDormantModeResponse Method ID: 17
            **/
        virtual bool leaveDormantModeResponse (
            const asi::connectivity::al::ResultType result
        ) IPL_NOEXCEPT = 0;

            /**
            onSimRefreshed Method ID: 18
            **/
        virtual bool onSimRefreshed (
            
        ) IPL_NOEXCEPT = 0;

            /**
            updNadError Method ID: 38
            **/
        virtual bool updNadError (
            const asi::connectivity::al::NadError error,
            const uint32_t errorExt,
            const CIPtr< CIString >& errorReport
        ) IPL_NOEXCEPT = 0;

            /**
            *
         * NAD stored emergency numbers
         
            updEmergencyNumbers Method ID: 37
            **/
        virtual bool updEmergencyNumbers (
            const CIPtr< CIStringArray >& numbers
        ) IPL_NOEXCEPT = 0;

            /**
            switchAirplaneModeResponse Method ID: 34
            **/
        virtual bool switchAirplaneModeResponse (
            const asi::connectivity::al::ResultType result
        ) IPL_NOEXCEPT = 0;

            /**
            setSuspendModeResponse Method ID: 32
            **/
        virtual bool setSuspendModeResponse (
            
        ) IPL_NOEXCEPT = 0;

            /**
            getEraGlonassStatusResponse Method ID: 11
            **/
        virtual bool getEraGlonassStatusResponse (
            const asi::connectivity::al::EraGlonassStatus status
        ) IPL_NOEXCEPT = 0;

            /**
            switchProfileResponse Method ID: 36
            **/
        virtual bool switchProfileResponse (
            const asi::connectivity::al::SimProfileId id,
            const asi::connectivity::al::ResultType result
        ) IPL_NOEXCEPT = 0;

            /**
            setAntennasScenario Method ID: 24
            **/
        virtual bool setAntennasScenario (
            const asi::connectivity::al::ResultType result
        ) IPL_NOEXCEPT = 0;

            /**
            setLTE4AntennaExistenceResponse Method ID: 44
            **/
        virtual bool setLTE4AntennaExistenceResponse (
            const asi::connectivity::al::ResultType result
        ) IPL_NOEXCEPT = 0;

            /**
            setMarketResponse Method ID: 28
            **/
        virtual bool setMarketResponse (
            const asi::connectivity::al::ResultType result
        ) IPL_NOEXCEPT = 0;

            /**
            resetSimResponse Method ID: 22
            **/
        virtual bool resetSimResponse (
            const asi::connectivity::al::ResultType result
        ) IPL_NOEXCEPT = 0;

            /**
            updateResetSim Method ID: 40
            **/
        virtual bool updateResetSim (
            const bool isSuccessful
        ) IPL_NOEXCEPT = 0;

            /**
            resetModemResponse Method ID: 20
            **/
        virtual bool resetModemResponse (
            const asi::connectivity::al::ResultType result
        ) IPL_NOEXCEPT = 0;

            /**
            getSIMFailureStatusResponse Method ID: 15
            **/
        virtual bool getSIMFailureStatusResponse (
            const asi::connectivity::al::ResultType result
        ) IPL_NOEXCEPT = 0;

            /**
            updateSIMFailureStatus Method ID: 41
            **/
        virtual bool updateSIMFailureStatus (
            const bool errorOccured,
            const asi::connectivity::al::SIMError simError
        ) IPL_NOEXCEPT = 0;

            /**
            getNWRejectionStatusResponse Method ID: 13
            **/
        virtual bool getNWRejectionStatusResponse (
            const asi::connectivity::al::ResultType result
        ) IPL_NOEXCEPT = 0;

            /**
            updateNWRejectionStatus Method ID: 39
            **/
        virtual bool updateNWRejectionStatus (
            const bool errorOccured,
            const bool isRjeceted,
            const int32_t rejectCause
        ) IPL_NOEXCEPT = 0;

            /**
            
        * For nadProc to inform VoiceProc about any timewindow in which it needs the system to stay awake
        * (due to modem actions that need to be executed or because the modem asks for it)
        
            updateWakeupReceived Method ID: 42
            **/
        virtual bool updateWakeupReceived (
            
        ) IPL_NOEXCEPT = 0;

            /**
            allowNetworkSearchingResponse Method ID: 1
            **/
        virtual bool allowNetworkSearchingResponse (
            const bool allow,
            const asi::connectivity::al::ResultType result
        ) IPL_NOEXCEPT = 0;

            /**
            enableJammingDetectionResponse Method ID: 7
            **/
        virtual bool enableJammingDetectionResponse (
            const bool enable,
            const asi::connectivity::al::ResultType result
        ) IPL_NOEXCEPT = 0;

            /**
            setBatteryStateResponse Method ID: 26
            **/
        virtual bool setBatteryStateResponse (
            const asi::connectivity::al::ResultType result
        ) IPL_NOEXCEPT = 0;

        virtual ~NADServicesReplyS() {}
    };

}// namespace asi
}// namespace connectivity
}// namespace al


#endif// ASI_CONNECTIVITY_AL_NADSERVICES_REPLYS_HXX
