/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceC_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_NADAUDIOSERVICESC_HXX
#define ASI_CONNECTIVITY_AL_NADAUDIOSERVICESC_HXX

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
    \brief The al::NadAudioServices interface on the client side.
    \details
            A proxy implements this interface.
    **/
    class NadAudioServicesC
    {
    public:
        // List of request methods
        /**
            *
         * Playback
         * @param audioFile, the file, which should be played back.
         
            startPlayback Method ID: 12
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool startPlayback(
            const CIPtr< CIString >& audioFile
        ) const IPL_NOEXCEPT = 0;

        /**
            stopPlayback Method ID: 16
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool stopPlayback(
            
        ) const IPL_NOEXCEPT = 0;

        /**
            *
         * Records
         * @param recordingFile, the file, which stores the recording.
         
            startRecording Method ID: 14
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool startRecording(
            const CIPtr< CIString >& recordingFile
        ) const IPL_NOEXCEPT = 0;

        /**
            stopRecording Method ID: 18
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool stopRecording(
            
        ) const IPL_NOEXCEPT = 0;

        /**
            loadAudioConfiguration Method ID: 0
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool loadAudioConfiguration(
            const CIPtr< CIString >& file
        ) const IPL_NOEXCEPT = 0;

        /**
            setAudioScenario Method ID: 2
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool setAudioScenario(
            const CIPtr< asi::connectivity::al::AudioScenario >& scenario
        ) const IPL_NOEXCEPT = 0;

        /**
            setSpeakerLevel Method ID: 8
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool setSpeakerLevel(
            const int32_t level
        ) const IPL_NOEXCEPT = 0;

        /**
            setMicLevel Method ID: 4
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool setMicLevel(
            const int32_t level
        ) const IPL_NOEXCEPT = 0;

        /**
            *
        * Mute or unmute the microphone and speakers.
        
            setMuteState Method ID: 6
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool setMuteState(
            const bool mute
        ) const IPL_NOEXCEPT = 0;

        /**
            *
        * Enable or disable the wideband capability for voice calls.
        * @param onoff if true wideband is enabled, if false wideband is disabled.
        
            setWideband Method ID: 10
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool setWideband(
            const bool onoff
        ) const IPL_NOEXCEPT = 0;

        NadAudioServicesC()  {}
        virtual ~NadAudioServicesC() {}
    protected:
        friend class NadAudioServicesProxy;
    };

}//namespace asi
}//namespace connectivity
}//namespace al
#endif// ASI_CONNECTIVITY_AL_NADAUDIOSERVICESC_HXX
