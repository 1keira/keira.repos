/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceC_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICCCMMEASUREMENTSC_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICCCMMEASUREMENTSC_HXX

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
    \brief The diagnostic::DiagnosticCcmMeasurements interface on the client side.
    \details
            A proxy implements this interface.
    **/
    class DiagnosticCcmMeasurementsC
    {
    public:
        // List of request methods
        /**
            getSokFailedVerificationPduIds Method ID: 0
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool getSokFailedVerificationPduIds(
            
        ) const IPL_NOEXCEPT = 0;

        /**
            getSokFreshness Method ID: 2
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool getSokFreshness(
            
        ) const IPL_NOEXCEPT = 0;

        /**
            getSokMissingKeys Method ID: 4
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool getSokMissingKeys(
            
        ) const IPL_NOEXCEPT = 0;

        /**
            getSokTime Method ID: 6
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool getSokTime(
            
        ) const IPL_NOEXCEPT = 0;

        DiagnosticCcmMeasurementsC()  {}
        virtual ~DiagnosticCcmMeasurementsC() {}
    protected:
        friend class DiagnosticCcmMeasurementsProxy;
    };

}//namespace asi
}//namespace connectivity
}//namespace diagnostic
#endif// ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICCCMMEASUREMENTSC_HXX
