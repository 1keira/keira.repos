/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceReplyS_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICCCMMEASUREMENTS_REPLYS_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICCCMMEASUREMENTS_REPLYS_HXX
#include <ipl_config.h>
#include <comm/commidltypes.hxx>
#include <asi/connectivity/diagnostic/StructSokFreshness.hxx>
#include <asi/connectivity/diagnostic/StructSokTime.hxx>
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
    class DiagnosticCcmMeasurementsReplyS
    {
    public:
        // List of reply methods
            /**
            getSokFailedVerificationPduIds Method ID: 1
            **/
        virtual bool getSokFailedVerificationPduIds (
            const CIPtr< CIUInt16Array >& ids,
            const asi::connectivity::diagnostic::ResultType result
        ) IPL_NOEXCEPT = 0;

            /**
            getSokFreshness Method ID: 3
            **/
        virtual bool getSokFreshness (
            const CIPtr< CIPtrArray< asi::connectivity::diagnostic::SokFreshness > >& freshnessInfos,
            const asi::connectivity::diagnostic::ResultType result
        ) IPL_NOEXCEPT = 0;

            /**
            getSokMissingKeys Method ID: 5
            **/
        virtual bool getSokMissingKeys (
            const CIPtr< CIUInt16Array >& keys,
            const asi::connectivity::diagnostic::ResultType result
        ) IPL_NOEXCEPT = 0;

            /**
            getSokTime Method ID: 7
            **/
        virtual bool getSokTime (
            const CIPtr< asi::connectivity::diagnostic::SokTime >& timeInfo,
            const asi::connectivity::diagnostic::ResultType result
        ) IPL_NOEXCEPT = 0;

        virtual ~DiagnosticCcmMeasurementsReplyS() {}
    };

}// namespace asi
}// namespace connectivity
}// namespace diagnostic


#endif// ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICCCMMEASUREMENTS_REPLYS_HXX
