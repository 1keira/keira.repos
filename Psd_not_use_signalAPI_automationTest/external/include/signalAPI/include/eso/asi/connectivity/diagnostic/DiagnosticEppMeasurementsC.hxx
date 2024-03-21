/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceC_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICEPPMEASUREMENTSC_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICEPPMEASUREMENTSC_HXX

#include <ipl_config.h>
#include <comm/commidltypes.hxx>
#include <asi/connectivity/diagnostic/Definitions.hxx>

namespace asi
{
namespace connectivity
{
namespace diagnostic
{

    /**
    \brief The diagnostic::DiagnosticEppMeasurements interface on the client side.
    \details
            A proxy implements this interface.
    **/
    class DiagnosticEppMeasurementsC
    {
    public:
        // List of request methods
        /**
            reportRollenmodusStatus Method ID: 0
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool reportRollenmodusStatus(
            const uint8_t status
        ) const IPL_NOEXCEPT = 0;

        DiagnosticEppMeasurementsC()  {}
        virtual ~DiagnosticEppMeasurementsC() {}
    protected:
        friend class DiagnosticEppMeasurementsProxy;
    };

}//namespace asi
}//namespace connectivity
}//namespace diagnostic
#endif// ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICEPPMEASUREMENTSC_HXX
