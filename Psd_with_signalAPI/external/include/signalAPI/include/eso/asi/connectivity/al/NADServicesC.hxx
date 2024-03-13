/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceC_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_NADSERVICESC_HXX
#define ASI_CONNECTIVITY_AL_NADSERVICESC_HXX

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
    \brief The al::NADServices interface on the client side.
    \details
            A proxy implements this interface.
    **/
    class NADServicesC
    {
    public:
        // List of request methods
        /**
            *
         * Enables VoLTE (Mobile Originated voice call via VOIP) from the UE.
         * The voice call mode can be CS_ONLY, VOIP_ONLY, CS_PREFERRED or VOIP_PREFERRED.
         * if enable is set to true: VOIP_PREFERRED will be selected as voice call mode in NAD
         * if enable is set to false: CS_ONLY will be selected as voice call mode in NAD
         
            enableIMS Method ID: 4
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool enableIMS(
            const bool enable
        ) const IPL_NOEXCEPT = 0;

        /**
            *
        * Configures modem to use 5G or not.
        * Deprecated. to be removed.
        
            enable5G Method ID: 2
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool enable5G(
            const bool enable
        ) const IPL_NOEXCEPT = 0;

        /**
            *
        * Configures modem network selection parameters.
        
            setNetworkSelectConfiguration Method ID: 29
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool setNetworkSelectConfiguration(
            const bool enable2G,
            const bool enable3G,
            const bool enable4G,
            const bool enable4GCA,
            const bool enable5GNSA,
            const bool enable5GSA,
            const bool enable5GSACA,
            const bool enableFR2Bands
        ) const IPL_NOEXCEPT = 0;

        /**
            enterDormantMode Method ID: 8
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool enterDormantMode(
            
        ) const IPL_NOEXCEPT = 0;

        /**
            leaveDormantMode Method ID: 16
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool leaveDormantMode(
            
        ) const IPL_NOEXCEPT = 0;

        /**
            *
         * Switch on or off the airplane mode. The SIM card will be powered down like an unpluged SIM card.
         * @param on true to switch on the airplane mode, false to switch off the airplane mode.
         
            switchAirplaneMode Method ID: 33
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool switchAirplaneMode(
            const asi::connectivity::al::AirplaneMode airplaneMode
        ) const IPL_NOEXCEPT = 0;

        /**
            setSuspendMode Method ID: 31
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool setSuspendMode(
            const bool on
        ) const IPL_NOEXCEPT = 0;

        /**
            getEraGlonassStatus Method ID: 10
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool getEraGlonassStatus(
            
        ) const IPL_NOEXCEPT = 0;

        /**
            switchProfile Method ID: 35
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool switchProfile(
            const asi::connectivity::al::SimProfileId id
        ) const IPL_NOEXCEPT = 0;

        /**
            setAntennasScenario Method ID: 23
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool setAntennasScenario(
            const asi::connectivity::al::AntennasScenario scenario
        ) const IPL_NOEXCEPT = 0;

        /**
            setLTE4AntennaExistence Method ID: 43
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool setLTE4AntennaExistence(
            const bool exists
        ) const IPL_NOEXCEPT = 0;

        /**
            
        * Method used to forward the Verkaufsland from Adaptations to NAD
        
            setMarket Method ID: 27
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool setMarket(
            const CIPtr< CIString >& country
        ) const IPL_NOEXCEPT = 0;

        /**
            
         * Methods introduced for the recovery managemnent
         
            resetSim Method ID: 21
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool resetSim(
            
        ) const IPL_NOEXCEPT = 0;

        /**
            
         * Method used to trigger a Modem reset.
         * Response will report feedback of restart procedure:
         * RESULT_TYPE_OK, on success or RESULT_TYPE_ERROR, if procedure fails.
         * It is expected that a resetModem request will also lead to a
         * temporary NAD_OFF of NadInformationService::NadState attribute.
         
            resetModem Method ID: 19
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool resetModem(
            
        ) const IPL_NOEXCEPT = 0;

        /**
            getSIMFailureStatusRequest Method ID: 14
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool getSIMFailureStatusRequest(
            
        ) const IPL_NOEXCEPT = 0;

        /**
            getNWRejectionStatusRequest Method ID: 12
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool getNWRejectionStatusRequest(
            
        ) const IPL_NOEXCEPT = 0;

        /**
            
        * For VoiceProc to forward the OOC state transitions between CBOX_VTS_ACTIVE_CAN-OFF_SEARCHING
        * and CBOX_VTS_ACTIVE_CAN-OFF_SEARCHING_PAUSED to control the network searches on the modem
        
            allowNetworkSearching Method ID: 0
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool allowNetworkSearching(
            const bool allow
        ) const IPL_NOEXCEPT = 0;

        /**
            
        * For VoiceProc to forward the OOC request to turn jamming detection on based on the OOC state transition to
        * CBOX_POWER-SAVE_CAN-OFF_VTS ALARM CHECK
        
            enableJammingDetection Method ID: 6
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool enableJammingDetection(
            const bool enable
        ) const IPL_NOEXCEPT = 0;

        /**
            
        * For VoiceProc to forward actual battery state reported by OOC
        
            setBatteryState Method ID: 25
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool setBatteryState(
            const asi::connectivity::al::BatteryState state
        ) const IPL_NOEXCEPT = 0;

        NADServicesC()  {}
        virtual ~NADServicesC() {}
    protected:
        friend class NADServicesProxy;
    };

}//namespace asi
}//namespace connectivity
}//namespace al
#endif// ASI_CONNECTIVITY_AL_NADSERVICESC_HXX
