/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceReply_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_HANDSFREESERVICESREPLY_HXX
#define ASI_CONNECTIVITY_AL_HANDSFREESERVICESREPLY_HXX

#include <comm/commtypes.hxx>
#include <comm/commidltypes.hxx>
#include <comm/CallEvent.hxx>
#include <asi/connectivity/al/StructHfpDeviceInformation.hxx>
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
    class HandsfreeServicesReply {

    public:
    // List of reply methods
            /**
            *
         * BT address of device active on this instance
         * @param btAddress address of connected device or -1(=nothing connected)
         
            updActiveDevice Method ID: 11
            **/
        virtual void updActiveDevice(
            const int64_t btAddress,
            const CIPtr< CIString >& friendlyName
        ) = 0;
            /**
            getHfpPhoneInformationResponse Method ID: 2
            **/
        virtual void getHfpPhoneInformationResponse(
            const asi::connectivity::al::ResultType result,
            const CIPtr< asi::connectivity::al::HfpDeviceInformation >& info
        ) = 0;
            /**
            
         * @param level battery charging level (0..5)
         
            updBatteryLevel Method ID: 12
            **/
        virtual void updBatteryLevel(
            const uint32_t level
        ) = 0;
            /**
            
         * @param strength signal strength (0..5)
         
            updNetworkSignalStrength Method ID: 18
            **/
        virtual void updNetworkSignalStrength(
            const uint32_t strength
        ) = 0;
            /**
            updOperatorName Method ID: 19
            **/
        virtual void updOperatorName(
            const CIPtr< CIString >& operator_name
        ) = 0;
            /**
            updRoamingIndicator Method ID: 20
            **/
        virtual void updRoamingIndicator(
            const asi::connectivity::al::RoamingState roaming
        ) = 0;
            /**
            updNetworkServiceAvailibility Method ID: 17
            **/
        virtual void updNetworkServiceAvailibility(
            const asi::connectivity::al::NetworkState availability
        ) = 0;
            /**
            
         * @param networkState network registration state
         * @param roamingState roaming indication
         * @param signalStrength between 0 and 5, 255 if unknown
         * @param batteryLevel between 0 and 5, 255 if unknown
         * @param operatorName network operator name subscribed to
         
            getPhoneStatusResponse Method ID: 4
            **/
        virtual void getPhoneStatusResponse(
            const asi::connectivity::al::NetworkState networkState,
            const asi::connectivity::al::RoamingState roamingState,
            const uint32_t signalStrength,
            const uint32_t batteryLevel,
            const CIPtr< CIString >& operatorName
        ) = 0;
            /**
            
         * Update the HFP Subscriber Number
         
            updHfpSubscriberNumber Method ID: 14
            **/
        virtual void updHfpSubscriberNumber(
            const CIPtr< CIString >& subscriber_number
        ) = 0;
            /**
            setHandsfreeModeResponse Method ID: 8
            **/
        virtual void setHandsfreeModeResponse(
            const asi::connectivity::al::ResultType result
        ) = 0;
            /**
            updHandsfreeMode Method ID: 13
            **/
        virtual void updHandsfreeMode(
            const asi::connectivity::al::HandsfreeMode mode
        ) = 0;
            /**
            
         * Informs if wideband speech is used for the current phone call or not.
         
            updWidebandSpeech Method ID: 22
            **/
        virtual void updWidebandSpeech(
            const bool active
        ) = 0;
            /**
            
         * Phone may support inband ringing but temporarly deactivates that feature
         * @param enabled true if phone uses inband ringing or not
         
            updInbandRingingStatus Method ID: 15
            **/
        virtual void updInbandRingingStatus(
            const bool enabled
        ) = 0;
            /**
            setAudioPolicyResponse Method ID: 6
            **/
        virtual void setAudioPolicyResponse(
            const asi::connectivity::al::ResultType result
        ) = 0;
            /**
            setVoiceRecognitionResponse Method ID: 10
            **/
        virtual void setVoiceRecognitionResponse(
            const asi::connectivity::al::ResultType result
        ) = 0;
            /**
            *
         * Update to inform about changed voice recognition state
         
            updVoiceRecognition Method ID: 21
            **/
        virtual void updVoiceRecognition(
            const bool status
        ) = 0;
            /**
            updNetworkIndicators Method ID: 16
            **/
        virtual void updNetworkIndicators(
            const asi::connectivity::al::NetworkState networkState,
            const asi::connectivity::al::RoamingState roamingState,
            const uint32_t signalStrength,
            const uint32_t batteryLevel
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
        updActiveDeviceCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<HandsfreeServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 11;
            ce.assign(inst, mid);
        }

        void
        getHfpPhoneInformationResponseCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<HandsfreeServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 2;
            ce.assign(inst, mid);
        }

        void
        updBatteryLevelCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<HandsfreeServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 12;
            ce.assign(inst, mid);
        }

        void
        updNetworkSignalStrengthCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<HandsfreeServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 18;
            ce.assign(inst, mid);
        }

        void
        updOperatorNameCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<HandsfreeServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 19;
            ce.assign(inst, mid);
        }

        void
        updRoamingIndicatorCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<HandsfreeServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 20;
            ce.assign(inst, mid);
        }

        void
        updNetworkServiceAvailibilityCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<HandsfreeServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 17;
            ce.assign(inst, mid);
        }

        void
        getPhoneStatusResponseCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<HandsfreeServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 4;
            ce.assign(inst, mid);
        }

        void
        updHfpSubscriberNumberCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<HandsfreeServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 14;
            ce.assign(inst, mid);
        }

        void
        setHandsfreeModeResponseCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<HandsfreeServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 8;
            ce.assign(inst, mid);
        }

        void
        updHandsfreeModeCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<HandsfreeServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 13;
            ce.assign(inst, mid);
        }

        void
        updWidebandSpeechCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<HandsfreeServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 22;
            ce.assign(inst, mid);
        }

        void
        updInbandRingingStatusCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<HandsfreeServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 15;
            ce.assign(inst, mid);
        }

        void
        setAudioPolicyResponseCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<HandsfreeServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 6;
            ce.assign(inst, mid);
        }

        void
        setVoiceRecognitionResponseCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<HandsfreeServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 10;
            ce.assign(inst, mid);
        }

        void
        updVoiceRecognitionCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<HandsfreeServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 21;
            ce.assign(inst, mid);
        }

        void
        updNetworkIndicatorsCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<HandsfreeServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 16;
            ce.assign(inst, mid);
        }


        virtual ~HandsfreeServicesReply() {}
    };

}//namespace asi
}//namespace connectivity
}//namespace al

#endif// ASI_CONNECTIVITY_AL_HANDSFREESERVICESREPLY_HXX
