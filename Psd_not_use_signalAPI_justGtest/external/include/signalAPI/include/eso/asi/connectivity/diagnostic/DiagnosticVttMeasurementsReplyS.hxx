/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceReplyS_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICVTTMEASUREMENTS_REPLYS_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICVTTMEASUREMENTS_REPLYS_HXX
#include <ipl_config.h>
#include <comm/commidltypes.hxx>
#include <asi/connectivity/diagnostic/StructVttStatus.hxx>
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
    class DiagnosticVttMeasurementsReplyS
    {
    public:
        // List of reply methods
            /**
            getSmsPdus Method ID: 1
            **/
        virtual bool getSmsPdus (
            const CIPtr< CIStringArray >& pdus
        ) IPL_NOEXCEPT = 0;

            /**
            getVttStatus Method ID: 3
            **/
        virtual bool getVttStatus (
            const CIPtr< asi::connectivity::diagnostic::VttStatus >& vttStatus
        ) IPL_NOEXCEPT = 0;

        virtual ~DiagnosticVttMeasurementsReplyS() {}
    };

}// namespace asi
}// namespace connectivity
}// namespace diagnostic


#endif// ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICVTTMEASUREMENTS_REPLYS_HXX
