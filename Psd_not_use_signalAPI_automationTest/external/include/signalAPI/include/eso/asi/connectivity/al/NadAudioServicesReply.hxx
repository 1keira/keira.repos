/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceReply_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_NADAUDIOSERVICESREPLY_HXX
#define ASI_CONNECTIVITY_AL_NADAUDIOSERVICESREPLY_HXX

#include <comm/commtypes.hxx>
#include <comm/commidltypes.hxx>
#include <comm/CallEvent.hxx>
#include <asi/connectivity/al/StructAudioScenario.hxx>
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
    class NadAudioServicesReply {

    public:
    // List of reply methods
            /**
            startPlaybackResponse Method ID: 13
            **/
        virtual void startPlaybackResponse(
            const asi::connectivity::al::ResultType result
        ) = 0;
            /**
            stopPlaybackResponse Method ID: 17
            **/
        virtual void stopPlaybackResponse(
            const asi::connectivity::al::ResultType result
        ) = 0;
            /**
            startRecordingResponse Method ID: 15
            **/
        virtual void startRecordingResponse(
            const asi::connectivity::al::ResultType result
        ) = 0;
            /**
            stopRecordingResponse Method ID: 19
            **/
        virtual void stopRecordingResponse(
            const asi::connectivity::al::ResultType result
        ) = 0;
            /**
            loadAudioConfigurationResponse Method ID: 1
            **/
        virtual void loadAudioConfigurationResponse(
            const asi::connectivity::al::ResultType result
        ) = 0;
            /**
            setAudioScenarioResponse Method ID: 3
            **/
        virtual void setAudioScenarioResponse(
            const asi::connectivity::al::ResultType result
        ) = 0;
            /**
            setSpeakerLevelResponse Method ID: 9
            **/
        virtual void setSpeakerLevelResponse(
            const asi::connectivity::al::ResultType result
        ) = 0;
            /**
            setMicLevelResponse Method ID: 5
            **/
        virtual void setMicLevelResponse(
            const asi::connectivity::al::ResultType result
        ) = 0;
            /**
            setMuteStateResponse Method ID: 7
            **/
        virtual void setMuteStateResponse(
            const asi::connectivity::al::ResultType result
        ) = 0;
            /**
            setWidebandResponse Method ID: 11
            **/
        virtual void setWidebandResponse(
            const asi::connectivity::al::ResultType result
        ) = 0;
            /**
            *
        * Indicates the current audio state.
        
            updateAudioState Method ID: 20
            **/
        virtual void updateAudioState(
            const asi::connectivity::al::AudioState state
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
        startPlaybackResponseCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NadAudioServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 13;
            ce.assign(inst, mid);
        }

        void
        stopPlaybackResponseCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NadAudioServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 17;
            ce.assign(inst, mid);
        }

        void
        startRecordingResponseCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NadAudioServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 15;
            ce.assign(inst, mid);
        }

        void
        stopRecordingResponseCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NadAudioServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 19;
            ce.assign(inst, mid);
        }

        void
        loadAudioConfigurationResponseCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NadAudioServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 1;
            ce.assign(inst, mid);
        }

        void
        setAudioScenarioResponseCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NadAudioServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 3;
            ce.assign(inst, mid);
        }

        void
        setSpeakerLevelResponseCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NadAudioServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 9;
            ce.assign(inst, mid);
        }

        void
        setMicLevelResponseCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NadAudioServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 5;
            ce.assign(inst, mid);
        }

        void
        setMuteStateResponseCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NadAudioServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 7;
            ce.assign(inst, mid);
        }

        void
        setWidebandResponseCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NadAudioServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 11;
            ce.assign(inst, mid);
        }

        void
        updateAudioStateCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NadAudioServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 20;
            ce.assign(inst, mid);
        }


        virtual ~NadAudioServicesReply() {}
    };

}//namespace asi
}//namespace connectivity
}//namespace al

#endif// ASI_CONNECTIVITY_AL_NADAUDIOSERVICESREPLY_HXX
