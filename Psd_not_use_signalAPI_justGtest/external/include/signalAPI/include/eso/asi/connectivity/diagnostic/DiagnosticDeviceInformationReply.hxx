/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceReply_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDEVICEINFORMATIONREPLY_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDEVICEINFORMATIONREPLY_HXX

#include <comm/commtypes.hxx>
#include <comm/commidltypes.hxx>
#include <comm/CallEvent.hxx>
#include <asi/connectivity/diagnostic/Definitions.hxx>

namespace asi
{
namespace connectivity
{
namespace diagnostic
{

    /**
    \brief  Declaration of the reply interface, which must be implemented by any user of this interface
    **/
    class DiagnosticDeviceInformationReply {

    public:
    // List of reply methods
            /**
            \brief
            reply for the attribute OverallSoftwareVersion
            updateOverallSoftwareVersion Method ID: 11
            **/
        virtual void updateOverallSoftwareVersion(
            const CIPtr< CIString >& OverallSoftwareVersion,
            const bool isValid
        ) = 0;
            /**
            \brief
            reply for the attribute CompanionSoftwareVersion
            updateCompanionSoftwareVersion Method ID: 7
            **/
        virtual void updateCompanionSoftwareVersion(
            const CIPtr< CIString >& CompanionSoftwareVersion,
            const bool isValid
        ) = 0;
            /**
            \brief
            reply for the attribute HardwareVersion
            updateHardwareVersion Method ID: 10
            **/
        virtual void updateHardwareVersion(
            const CIPtr< CIString >& HardwareVersion,
            const bool isValid
        ) = 0;
            /**
            \brief
            reply for the attribute SerialNumber
            updateSerialNumber Method ID: 12
            **/
        virtual void updateSerialNumber(
            const CIPtr< CIString >& SerialNumber,
            const bool isValid
        ) = 0;
            /**
            \brief
            reply for the attribute SparePartNumber
            updateSparePartNumber Method ID: 13
            **/
        virtual void updateSparePartNumber(
            const CIPtr< CIString >& SparePartNumber,
            const bool isValid
        ) = 0;
            /**
            \brief
            reply for the attribute HardwarePartNumber
            updateHardwarePartNumber Method ID: 8
            **/
        virtual void updateHardwarePartNumber(
            const CIPtr< CIString >& HardwarePartNumber,
            const bool isValid
        ) = 0;
            /**
            \brief
            reply for the attribute HardwareVariant
            updateHardwareVariant Method ID: 9
            **/
        virtual void updateHardwareVariant(
            const uint16_t HardwareVariant,
            const bool isValid
        ) = 0;
            /**
            \brief
            reply for the attribute AssemblyInformation
            updateAssemblyInformation Method ID: 6
            **/
        virtual void updateAssemblyInformation(
            const uint32_t AssemblyInformation,
            const bool isValid
        ) = 0;

        /*!
        \brief Informs the service about a connected client
        \param count The number of connected clients
        */
        virtual void clientConnected(uint32_t count) {}

        /*!
        \brief Informs the service that a client disconnected
        \param count the number of connected clients
        */
        virtual void clientDisconnected(uint32_t count) {}

        // call ids
        void
        updateOverallSoftwareVersionCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<DiagnosticDeviceInformationReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 11;
            ce.assign(inst, mid);
        }

        void
        updateCompanionSoftwareVersionCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<DiagnosticDeviceInformationReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 7;
            ce.assign(inst, mid);
        }

        void
        updateHardwareVersionCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<DiagnosticDeviceInformationReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 10;
            ce.assign(inst, mid);
        }

        void
        updateSerialNumberCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<DiagnosticDeviceInformationReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 12;
            ce.assign(inst, mid);
        }

        void
        updateSparePartNumberCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<DiagnosticDeviceInformationReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 13;
            ce.assign(inst, mid);
        }

        void
        updateHardwarePartNumberCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<DiagnosticDeviceInformationReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 8;
            ce.assign(inst, mid);
        }

        void
        updateHardwareVariantCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<DiagnosticDeviceInformationReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 9;
            ce.assign(inst, mid);
        }

        void
        updateAssemblyInformationCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<DiagnosticDeviceInformationReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 6;
            ce.assign(inst, mid);
        }


        virtual ~DiagnosticDeviceInformationReply() {}
    };

}//namespace asi
}//namespace connectivity
}//namespace diagnostic

#endif// ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDEVICEINFORMATIONREPLY_HXX
