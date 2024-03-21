/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceReplyS_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_HANDSFREESERVICES_REPLYS_HXX
#define ASI_CONNECTIVITY_AL_HANDSFREESERVICES_REPLYS_HXX
#include <ipl_config.h>
#include <comm/commidltypes.hxx>
#include <asi/connectivity/al/StructHfpDeviceInformation.hxx>
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
    class HandsfreeServicesReplyS
    {
    public:
        // List of reply methods
            /**
            *
         * BT address of device active on this instance
         * @param btAddress address of connected device or -1(=nothing connected)
         
            updActiveDevice Method ID: 11
            **/
        virtual bool updActiveDevice (
            const int64_t btAddress,
            const CIPtr< CIString >& friendlyName
        ) IPL_NOEXCEPT = 0;

            /**
            getHfpPhoneInformationResponse Method ID: 2
            **/
        virtual bool getHfpPhoneInformationResponse (
            const asi::connectivity::al::ResultType result,
            const CIPtr< asi::connectivity::al::HfpDeviceInformation >& info
        ) IPL_NOEXCEPT = 0;

            /**
            
         * @param level battery charging level (0..5)
         
            updBatteryLevel Method ID: 12
            **/
        virtual bool updBatteryLevel (
            const uint32_t level
        ) IPL_NOEXCEPT = 0;

            /**
            
         * @param strength signal strength (0..5)
         
            updNetworkSignalStrength Method ID: 18
            **/
        virtual bool updNetworkSignalStrength (
            const uint32_t strength
        ) IPL_NOEXCEPT = 0;

            /**
            updOperatorName Method ID: 19
            **/
        virtual bool updOperatorName (
            const CIPtr< CIString >& operator_name
        ) IPL_NOEXCEPT = 0;

            /**
            updRoamingIndicator Method ID: 20
            **/
        virtual bool updRoamingIndicator (
            const asi::connectivity::al::RoamingState roaming
        ) IPL_NOEXCEPT = 0;

            /**
            updNetworkServiceAvailibility Method ID: 17
            **/
        virtual bool updNetworkServiceAvailibility (
            const asi::connectivity::al::NetworkState availability
        ) IPL_NOEXCEPT = 0;

            /**
            
         * @param networkState network registration state
         * @param roamingState roaming indication
         * @param signalStrength between 0 and 5, 255 if unknown
         * @param batteryLevel between 0 and 5, 255 if unknown
         * @param operatorName network operator name subscribed to
         
            getPhoneStatusResponse Method ID: 4
            **/
        virtual bool getPhoneStatusResponse (
            const asi::connectivity::al::NetworkState networkState,
            const asi::connectivity::al::RoamingState roamingState,
            const uint32_t signalStrength,
            const uint32_t batteryLevel,
            const CIPtr< CIString >& operatorName
        ) IPL_NOEXCEPT = 0;

            /**
            
         * Update the HFP Subscriber Number
         
            updHfpSubscriberNumber Method ID: 14
            **/
        virtual bool updHfpSubscriberNumber (
            const CIPtr< CIString >& subscriber_number
        ) IPL_NOEXCEPT = 0;

            /**
            setHandsfreeModeResponse Method ID: 8
            **/
        virtual bool setHandsfreeModeResponse (
            const asi::connectivity::al::ResultType result
        ) IPL_NOEXCEPT = 0;

            /**
            updHandsfreeMode Method ID: 13
            **/
        virtual bool updHandsfreeMode (
            const asi::connectivity::al::HandsfreeMode mode
        ) IPL_NOEXCEPT = 0;

            /**
            
         * Informs if wideband speech is used for the current phone call or not.
         
            updWidebandSpeech Method ID: 22
            **/
        virtual bool updWidebandSpeech (
            const bool active
        ) IPL_NOEXCEPT = 0;

            /**
            
         * Phone may support inband ringing but temporarly deactivates that feature
         * @param enabled true if phone uses inband ringing or not
         
            updInbandRingingStatus Method ID: 15
            **/
        virtual bool updInbandRingingStatus (
            const bool enabled
        ) IPL_NOEXCEPT = 0;

            /**
            setAudioPolicyResponse Method ID: 6
            **/
        virtual bool setAudioPolicyResponse (
            const asi::connectivity::al::ResultType result
        ) IPL_NOEXCEPT = 0;

            /**
            setVoiceRecognitionResponse Method ID: 10
            **/
        virtual bool setVoiceRecognitionResponse (
            const asi::connectivity::al::ResultType result
        ) IPL_NOEXCEPT = 0;

            /**
            *
         * Update to inform about changed voice recognition state
         
            updVoiceRecognition Method ID: 21
            **/
        virtual bool updVoiceRecognition (
            const bool status
        ) IPL_NOEXCEPT = 0;

            /**
            updNetworkIndicators Method ID: 16
            **/
        virtual bool updNetworkIndicators (
            const asi::connectivity::al::NetworkState networkState,
            const asi::connectivity::al::RoamingState roamingState,
            const uint32_t signalStrength,
            const uint32_t batteryLevel
        ) IPL_NOEXCEPT = 0;

        virtual ~HandsfreeServicesReplyS() {}
    };

}// namespace asi
}// namespace connectivity
}// namespace al


#endif// ASI_CONNECTIVITY_AL_HANDSFREESERVICES_REPLYS_HXX
