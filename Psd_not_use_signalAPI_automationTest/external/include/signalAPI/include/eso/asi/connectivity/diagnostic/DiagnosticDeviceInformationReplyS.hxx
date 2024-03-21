/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceReplyS_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDEVICEINFORMATION_REPLYS_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDEVICEINFORMATION_REPLYS_HXX
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
    \brief  Interface declaration, which is implemented by the proxy, and used/called by any user of this interface
    **/
    class DiagnosticDeviceInformationReplyS
    {
    public:
        // List of reply methods
            /**
            \brief
            reply for the attribute OverallSoftwareVersion
            updateOverallSoftwareVersion Method ID: 11
            **/
        virtual bool updateOverallSoftwareVersion (
            const CIPtr< CIString >& OverallSoftwareVersion,
            const bool isValid
        ) IPL_NOEXCEPT = 0;

            /**
            \brief
            reply for the attribute CompanionSoftwareVersion
            updateCompanionSoftwareVersion Method ID: 7
            **/
        virtual bool updateCompanionSoftwareVersion (
            const CIPtr< CIString >& CompanionSoftwareVersion,
            const bool isValid
        ) IPL_NOEXCEPT = 0;

            /**
            \brief
            reply for the attribute HardwareVersion
            updateHardwareVersion Method ID: 10
            **/
        virtual bool updateHardwareVersion (
            const CIPtr< CIString >& HardwareVersion,
            const bool isValid
        ) IPL_NOEXCEPT = 0;

            /**
            \brief
            reply for the attribute SerialNumber
            updateSerialNumber Method ID: 12
            **/
        virtual bool updateSerialNumber (
            const CIPtr< CIString >& SerialNumber,
            const bool isValid
        ) IPL_NOEXCEPT = 0;

            /**
            \brief
            reply for the attribute SparePartNumber
            updateSparePartNumber Method ID: 13
            **/
        virtual bool updateSparePartNumber (
            const CIPtr< CIString >& SparePartNumber,
            const bool isValid
        ) IPL_NOEXCEPT = 0;

            /**
            \brief
            reply for the attribute HardwarePartNumber
            updateHardwarePartNumber Method ID: 8
            **/
        virtual bool updateHardwarePartNumber (
            const CIPtr< CIString >& HardwarePartNumber,
            const bool isValid
        ) IPL_NOEXCEPT = 0;

            /**
            \brief
            reply for the attribute HardwareVariant
            updateHardwareVariant Method ID: 9
            **/
        virtual bool updateHardwareVariant (
            const uint16_t HardwareVariant,
            const bool isValid
        ) IPL_NOEXCEPT = 0;

            /**
            \brief
            reply for the attribute AssemblyInformation
            updateAssemblyInformation Method ID: 6
            **/
        virtual bool updateAssemblyInformation (
            const uint32_t AssemblyInformation,
            const bool isValid
        ) IPL_NOEXCEPT = 0;

        virtual ~DiagnosticDeviceInformationReplyS() {}
    };

}// namespace asi
}// namespace connectivity
}// namespace diagnostic


#endif// ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDEVICEINFORMATION_REPLYS_HXX
