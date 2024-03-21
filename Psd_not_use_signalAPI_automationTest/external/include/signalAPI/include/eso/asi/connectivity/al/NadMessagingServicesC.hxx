/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceC_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_NADMESSAGINGSERVICESC_HXX
#define ASI_CONNECTIVITY_AL_NADMESSAGINGSERVICESC_HXX

#include <ipl_config.h>
#include <comm/commidltypes.hxx>
#include <asi/connectivity/al/StructTimestamp.hxx>
#include <asi/connectivity/al/Definitions.hxx>

namespace asi
{
namespace connectivity
{
namespace al
{

    /**
    \brief The al::NadMessagingServices interface on the client side.
    \details
            A proxy implements this interface.
    **/
    class NadMessagingServicesC
    {
    public:
        // List of request methods
        /**
            sendMessage Method ID: 2
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool sendMessage(
            const CIPtr< CIString >& pdu
        ) const IPL_NOEXCEPT = 0;

        NadMessagingServicesC()  {}
        virtual ~NadMessagingServicesC() {}
    protected:
        friend class NadMessagingServicesProxy;
    };

}//namespace asi
}//namespace connectivity
}//namespace al
#endif// ASI_CONNECTIVITY_AL_NADMESSAGINGSERVICESC_HXX
