/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceC_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_NADCALLHANDLINGSERVICESC_HXX
#define ASI_CONNECTIVITY_AL_NADCALLHANDLINGSERVICESC_HXX

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
    \brief The al::NadCallHandlingServices interface on the client side.
    \details
            A proxy implements this interface.
    **/
    class NadCallHandlingServicesC
    {
    public:
        // List of request methods
        /**
            acceptCall Method ID: 0
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool acceptCall(
            
        ) const IPL_NOEXCEPT = 0;

        /**
            dialNumber Method ID: 2
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool dialNumber(
            const CIPtr< CIString >& number
        ) const IPL_NOEXCEPT = 0;

        /**
            hangupCall Method ID: 4
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool hangupCall(
            const int32_t callID
        ) const IPL_NOEXCEPT = 0;

        /**
            sendDtmf Method ID: 6
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool sendDtmf(
            const int32_t value
        ) const IPL_NOEXCEPT = 0;

        NadCallHandlingServicesC()  {}
        virtual ~NadCallHandlingServicesC() {}
    protected:
        friend class NadCallHandlingServicesProxy;
    };

}//namespace asi
}//namespace connectivity
}//namespace al
#endif// ASI_CONNECTIVITY_AL_NADCALLHANDLINGSERVICESC_HXX
