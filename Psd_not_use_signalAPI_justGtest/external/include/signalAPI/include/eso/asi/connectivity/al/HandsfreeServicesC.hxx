/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceC_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_HANDSFREESERVICESC_HXX
#define ASI_CONNECTIVITY_AL_HANDSFREESERVICESC_HXX

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
    \brief The al::HandsfreeServices interface on the client side.
    \details
            A proxy implements this interface.
    **/
    class HandsfreeServicesC
    {
    public:
        // List of request methods
        /**
            
         * Indicates if service client is ready of receiving updates (updCallStatus, updNetworkType, ...)
         
            enableUpdates Method ID: 0
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool enableUpdates(
            const bool enable
        ) const IPL_NOEXCEPT = 0;

        /**
            getHfpPhoneInformation Method ID: 1
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool getHfpPhoneInformation(
            
        ) const IPL_NOEXCEPT = 0;

        /**
            
         * Request to retrieve a complete new set of phone indicators
         
            getPhoneStatus Method ID: 3
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool getPhoneStatus(
            
        ) const IPL_NOEXCEPT = 0;

        /**
            setHandsfreeMode Method ID: 7
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool setHandsfreeMode(
            const asi::connectivity::al::HandsfreeMode mode
        ) const IPL_NOEXCEPT = 0;

        /**
            
         * Configure default behavior to handle incoming audio connections
         * @param policy either automatic accept or reject
         
            setAudioPolicy Method ID: 5
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool setAudioPolicy(
            const asi::connectivity::al::HfpAudioPolicy policy,
            const bool allow_wideband
        ) const IPL_NOEXCEPT = 0;

        /**
            *
         * Request to enable/disable voice recogniton via BVRA
         
            setVoiceRecognition Method ID: 9
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool setVoiceRecognition(
            const bool onoff
        ) const IPL_NOEXCEPT = 0;

        HandsfreeServicesC()  {}
        virtual ~HandsfreeServicesC() {}
    protected:
        friend class HandsfreeServicesProxy;
    };

}//namespace asi
}//namespace connectivity
}//namespace al
#endif// ASI_CONNECTIVITY_AL_HANDSFREESERVICESC_HXX
