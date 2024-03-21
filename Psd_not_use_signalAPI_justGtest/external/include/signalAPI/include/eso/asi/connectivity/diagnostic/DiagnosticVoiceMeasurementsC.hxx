/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceC_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICVOICEMEASUREMENTSC_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICVOICEMEASUREMENTSC_HXX

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
    \brief The diagnostic::DiagnosticVoiceMeasurements interface on the client side.
    \details
            A proxy implements this interface.
    **/
    class DiagnosticVoiceMeasurementsC
    {
    public:
        // List of request methods
        /**
            getAerialSwitchStatus Method ID: 0
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool getAerialSwitchStatus(
            
        ) const IPL_NOEXCEPT = 0;

        /**
            getECallActivationState Method ID: 2
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool getECallActivationState(
            
        ) const IPL_NOEXCEPT = 0;

        /**
            getECallCallState Method ID: 4
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool getECallCallState(
            
        ) const IPL_NOEXCEPT = 0;

        /**
            getEcallOperationStatus Method ID: 14
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool getEcallOperationStatus(
            
        ) const IPL_NOEXCEPT = 0;

        /**
            getRecentCallList Method ID: 16
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool getRecentCallList(
            
        ) const IPL_NOEXCEPT = 0;

        /**
            getECallSetOfData Method ID: 12
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool getECallSetOfData(
            
        ) const IPL_NOEXCEPT = 0;

        /**
            getECallEraProfileActivationStatus Method ID: 8
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool getECallEraProfileActivationStatus(
            
        ) const IPL_NOEXCEPT = 0;

        /**
            getECallEraProfileAvailabilityStatus Method ID: 10
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool getECallEraProfileAvailabilityStatus(
            
        ) const IPL_NOEXCEPT = 0;

        /**
            getECallEraIccid Method ID: 6
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool getECallEraIccid(
            
        ) const IPL_NOEXCEPT = 0;

        DiagnosticVoiceMeasurementsC()  {}
        virtual ~DiagnosticVoiceMeasurementsC() {}
    protected:
        friend class DiagnosticVoiceMeasurementsProxy;
    };

}//namespace asi
}//namespace connectivity
}//namespace diagnostic
#endif// ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICVOICEMEASUREMENTSC_HXX
