/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceReplyS_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICVOICEMEASUREMENTS_REPLYS_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICVOICEMEASUREMENTS_REPLYS_HXX
#include <ipl_config.h>
#include <comm/commidltypes.hxx>
#include <asi/connectivity/diagnostic/StructEcallOperationStatus.hxx>
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
    class DiagnosticVoiceMeasurementsReplyS
    {
    public:
        // List of reply methods
            /**
            getAerialSwitchStatus Method ID: 1
            **/
        virtual bool getAerialSwitchStatus (
            const asi::connectivity::diagnostic::AerialSwitchStatus status,
            const asi::connectivity::diagnostic::ResultType result
        ) IPL_NOEXCEPT = 0;

            /**
            getECallActivationState Method ID: 3
            **/
        virtual bool getECallActivationState (
            const bool isActivated,
            const asi::connectivity::diagnostic::ResultType result
        ) IPL_NOEXCEPT = 0;

            /**
            getECallCallState Method ID: 5
            **/
        virtual bool getECallCallState (
            const uint8_t isActivated,
            const asi::connectivity::diagnostic::ResultType result
        ) IPL_NOEXCEPT = 0;

            /**
            getEcallOperationStatus Method ID: 15
            **/
        virtual bool getEcallOperationStatus (
            const CIPtr< asi::connectivity::diagnostic::EcallOperationStatus >& status,
            const asi::connectivity::diagnostic::ResultType result
        ) IPL_NOEXCEPT = 0;

            /**
            getRecentCallList Method ID: 17
            **/
        virtual bool getRecentCallList (
            const CIPtr< CIStringArray >& callList,
            const asi::connectivity::diagnostic::ResultType result
        ) IPL_NOEXCEPT = 0;

            /**
            getECallSetOfData Method ID: 13
            **/
        virtual bool getECallSetOfData (
            const CIPtr< CIString >& set,
            const asi::connectivity::diagnostic::ResultType result
        ) IPL_NOEXCEPT = 0;

            /**
            getECallEraProfileActivationStatus Method ID: 9
            **/
        virtual bool getECallEraProfileActivationStatus (
            const bool isActivated,
            const asi::connectivity::diagnostic::ResultType result
        ) IPL_NOEXCEPT = 0;

            /**
            getECallEraProfileAvailabilityStatus Method ID: 11
            **/
        virtual bool getECallEraProfileAvailabilityStatus (
            const bool isAvailable,
            const asi::connectivity::diagnostic::ResultType result
        ) IPL_NOEXCEPT = 0;

            /**
            getECallEraIccid Method ID: 7
            **/
        virtual bool getECallEraIccid (
            const CIPtr< CIString >& iccid,
            const asi::connectivity::diagnostic::ResultType result
        ) IPL_NOEXCEPT = 0;

        virtual ~DiagnosticVoiceMeasurementsReplyS() {}
    };

}// namespace asi
}// namespace connectivity
}// namespace diagnostic


#endif// ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICVOICEMEASUREMENTS_REPLYS_HXX
