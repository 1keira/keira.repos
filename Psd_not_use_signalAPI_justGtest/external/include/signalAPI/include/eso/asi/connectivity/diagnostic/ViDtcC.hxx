/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceC_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_VIDTCC_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_VIDTCC_HXX

#include <ipl_config.h>
#include <comm/commidltypes.hxx>
#include <asi/connectivity/diagnostic/StructDtc.hxx>
#include <asi/connectivity/diagnostic/Definitions.hxx>

namespace asi
{
namespace connectivity
{
namespace diagnostic
{

    /**
    \brief The diagnostic::ViDtc interface on the client side.
    \details
            A proxy implements this interface.
    **/
    class ViDtcC
    {
    public:
        // List of request methods
        /**
            setDtc Method ID: 4
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool setDtc(
            const CIPtr< asi::connectivity::diagnostic::Dtc >& dtc
        ) const IPL_NOEXCEPT = 0;

        /**
            getDtcs Method ID: 0
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool getDtcs(
            const CIPtr< CIUInt32Array >& codes
        ) const IPL_NOEXCEPT = 0;

        /**
            subscribeIds Method ID: 5
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool subscribeIds(
            const CIPtr< CIUInt32Array >& codes
        ) const IPL_NOEXCEPT = 0;

        /**
            unsubscribeIds Method ID: 6
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool unsubscribeIds(
            const CIPtr< CIUInt32Array >& codes
        ) const IPL_NOEXCEPT = 0;

        ViDtcC()  {}
        virtual ~ViDtcC() {}
    protected:
        friend class ViDtcProxy;
    };

}//namespace asi
}//namespace connectivity
}//namespace diagnostic
#endif// ASI_CONNECTIVITY_DIAGNOSTIC_VIDTCC_HXX
