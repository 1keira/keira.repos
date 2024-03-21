/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceReplyS_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_VIDTC_REPLYS_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_VIDTC_REPLYS_HXX
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
    \brief  Interface declaration, which is implemented by the proxy, and used/called by any user of this interface
    **/
    class ViDtcReplyS
    {
    public:
        // List of reply methods
            /**
            setDtc Method ID: 3
            **/
        virtual bool setDtc (
            const asi::connectivity::diagnostic::ViError error
        ) IPL_NOEXCEPT = 0;

            /**
            onDtcs Method ID: 2
            **/
        virtual bool onDtcs (
            const CIPtr< CIPtrArray< asi::connectivity::diagnostic::Dtc > >& dtcs
        ) IPL_NOEXCEPT = 0;

            /**
            getDtcs Method ID: 1
            **/
        virtual bool getDtcs (
            const CIPtr< CIPtrArray< asi::connectivity::diagnostic::Dtc > >& dtcs,
            const asi::connectivity::diagnostic::ViError error
        ) IPL_NOEXCEPT = 0;

        virtual ~ViDtcReplyS() {}
    };

}// namespace asi
}// namespace connectivity
}// namespace diagnostic


#endif// ASI_CONNECTIVITY_DIAGNOSTIC_VIDTC_REPLYS_HXX
