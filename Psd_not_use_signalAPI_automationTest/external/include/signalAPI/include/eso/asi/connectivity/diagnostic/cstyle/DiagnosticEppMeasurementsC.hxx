/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleInterfaceC_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICEPPMEASUREMENTSC_CSTYLE_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICEPPMEASUREMENTSC_CSTYLE_HXX

#include <comm/commidltypes.hxx>
#include <comm/Lifecycle.hxx>
#include <asi/connectivity/diagnostic/cstyle/Definitions.hxx>

namespace asi
{
namespace connectivity
{
namespace diagnostic
{
namespace cstyle {

    /**
    \brief The diagnostic::cstyle::DiagnosticEppMeasurements interface on the client side.
    \detail
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
        ) const = 0;

        DiagnosticEppMeasurementsC()  {}
        virtual ~DiagnosticEppMeasurementsC() {}
    protected:
        friend class DiagnosticEppMeasurementsProxy;
    };

} // cstyle
}//namespace asi
}//namespace connectivity
}//namespace diagnostic
#endif// ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICEPPMEASUREMENTSC_CSTYLE_HXX
