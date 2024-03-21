/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceC_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_CALLHANDLINGSERVICESC_HXX
#define ASI_CONNECTIVITY_AL_CALLHANDLINGSERVICESC_HXX

#include <ipl_config.h>
#include <comm/commidltypes.hxx>
#include <asi/connectivity/al/StructCallStatus.hxx>
#include <asi/connectivity/al/Definitions.hxx>

namespace asi
{
namespace connectivity
{
namespace al
{

    /**
    \brief The al::CallHandlingServices interface on the client side.
    \details
            A proxy implements this interface.
    **/
    class CallHandlingServicesC
    {
    public:
        // List of request methods
        /**
            sendDtmf Method ID: 18
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool sendDtmf(
            const int32_t tone
        ) const IPL_NOEXCEPT = 0;

        /**
            acceptCall Method ID: 2
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool acceptCall(
            const asi::connectivity::al::DeviceType device
        ) const IPL_NOEXCEPT = 0;

        /**
            acceptAndHoldCall Method ID: 0
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool acceptAndHoldCall(
            const asi::connectivity::al::DeviceType device,
            const int32_t callId
        ) const IPL_NOEXCEPT = 0;

        /**
            switchCalls Method ID: 22
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool switchCalls(
            const asi::connectivity::al::DeviceType device
        ) const IPL_NOEXCEPT = 0;

        /**
            dialNumber Method ID: 6
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool dialNumber(
            const asi::connectivity::al::DeviceType device,
            const CIPtr< CIString >& number,
            const bool isEmergencyNumber
        ) const IPL_NOEXCEPT = 0;

        /**
            hangupCall Method ID: 10
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool hangupCall(
            const asi::connectivity::al::DeviceType device,
            const int32_t callID
        ) const IPL_NOEXCEPT = 0;

        /**
            joinCalls Method ID: 14
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool joinCalls(
            const asi::connectivity::al::DeviceType device
        ) const IPL_NOEXCEPT = 0;

        /**
            splitCall Method ID: 20
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool splitCall(
            const asi::connectivity::al::DeviceType device,
            const int32_t callID
        ) const IPL_NOEXCEPT = 0;

        /**
            holdActiveCalls Method ID: 12
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool holdActiveCalls(
            const asi::connectivity::al::DeviceType device
        ) const IPL_NOEXCEPT = 0;

        /**
            resumeHeldCalls Method ID: 16
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool resumeHeldCalls(
            const asi::connectivity::al::DeviceType device
        ) const IPL_NOEXCEPT = 0;

        /**
            *
         * Execute a USSD (unstructured supplementary service code). The response may take up to
         * 30s.
         * @param serviceCode the service code to execute
         
            executeUSSD Method ID: 8
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool executeUSSD(
            const CIPtr< CIString >& serviceCode
        ) const IPL_NOEXCEPT = 0;

        /**
            *
         * Cancel any ongoing USSD session
         
            cancelUSSD Method ID: 4
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool cancelUSSD(
            
        ) const IPL_NOEXCEPT = 0;

        CallHandlingServicesC()  {}
        virtual ~CallHandlingServicesC() {}
    protected:
        friend class CallHandlingServicesProxy;
    };

}//namespace asi
}//namespace connectivity
}//namespace al
#endif// ASI_CONNECTIVITY_AL_CALLHANDLINGSERVICESC_HXX
