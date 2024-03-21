/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceReplyS_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_NADAUDIOSERVICES_REPLYS_HXX
#define ASI_CONNECTIVITY_AL_NADAUDIOSERVICES_REPLYS_HXX
#include <ipl_config.h>
#include <comm/commidltypes.hxx>
#include <asi/connectivity/al/StructAudioScenario.hxx>
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
    class NadAudioServicesReplyS
    {
    public:
        // List of reply methods
            /**
            startPlaybackResponse Method ID: 13
            **/
        virtual bool startPlaybackResponse (
            const asi::connectivity::al::ResultType result
        ) IPL_NOEXCEPT = 0;

            /**
            stopPlaybackResponse Method ID: 17
            **/
        virtual bool stopPlaybackResponse (
            const asi::connectivity::al::ResultType result
        ) IPL_NOEXCEPT = 0;

            /**
            startRecordingResponse Method ID: 15
            **/
        virtual bool startRecordingResponse (
            const asi::connectivity::al::ResultType result
        ) IPL_NOEXCEPT = 0;

            /**
            stopRecordingResponse Method ID: 19
            **/
        virtual bool stopRecordingResponse (
            const asi::connectivity::al::ResultType result
        ) IPL_NOEXCEPT = 0;

            /**
            loadAudioConfigurationResponse Method ID: 1
            **/
        virtual bool loadAudioConfigurationResponse (
            const asi::connectivity::al::ResultType result
        ) IPL_NOEXCEPT = 0;

            /**
            setAudioScenarioResponse Method ID: 3
            **/
        virtual bool setAudioScenarioResponse (
            const asi::connectivity::al::ResultType result
        ) IPL_NOEXCEPT = 0;

            /**
            setSpeakerLevelResponse Method ID: 9
            **/
        virtual bool setSpeakerLevelResponse (
            const asi::connectivity::al::ResultType result
        ) IPL_NOEXCEPT = 0;

            /**
            setMicLevelResponse Method ID: 5
            **/
        virtual bool setMicLevelResponse (
            const asi::connectivity::al::ResultType result
        ) IPL_NOEXCEPT = 0;

            /**
            setMuteStateResponse Method ID: 7
            **/
        virtual bool setMuteStateResponse (
            const asi::connectivity::al::ResultType result
        ) IPL_NOEXCEPT = 0;

            /**
            setWidebandResponse Method ID: 11
            **/
        virtual bool setWidebandResponse (
            const asi::connectivity::al::ResultType result
        ) IPL_NOEXCEPT = 0;

            /**
            *
        * Indicates the current audio state.
        
            updateAudioState Method ID: 20
            **/
        virtual bool updateAudioState (
            const asi::connectivity::al::AudioState state
        ) IPL_NOEXCEPT = 0;

        virtual ~NadAudioServicesReplyS() {}
    };

}// namespace asi
}// namespace connectivity
}// namespace al


#endif// ASI_CONNECTIVITY_AL_NADAUDIOSERVICES_REPLYS_HXX
