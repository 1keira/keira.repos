/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceReply_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICVOICEMEASUREMENTSREPLY_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICVOICEMEASUREMENTSREPLY_HXX

#include <comm/commtypes.hxx>
#include <comm/commidltypes.hxx>
#include <comm/CallEvent.hxx>
#include <asi/connectivity/diagnostic/StructEcallOperationStatus.hxx>
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
    class DiagnosticVoiceMeasurementsReply {

    public:
    // List of reply methods
            /**
            getAerialSwitchStatus Method ID: 1
            **/
        virtual void getAerialSwitchStatus(
            const asi::connectivity::diagnostic::AerialSwitchStatus status,
            const asi::connectivity::diagnostic::ResultType result
        ) = 0;
            /**
            getECallActivationState Method ID: 3
            **/
        virtual void getECallActivationState(
            const bool isActivated,
            const asi::connectivity::diagnostic::ResultType result
        ) = 0;
            /**
            getECallCallState Method ID: 5
            **/
        virtual void getECallCallState(
            const uint8_t isActivated,
            const asi::connectivity::diagnostic::ResultType result
        ) = 0;
            /**
            getEcallOperationStatus Method ID: 15
            **/
        virtual void getEcallOperationStatus(
            const CIPtr< asi::connectivity::diagnostic::EcallOperationStatus >& status,
            const asi::connectivity::diagnostic::ResultType result
        ) = 0;
            /**
            getRecentCallList Method ID: 17
            **/
        virtual void getRecentCallList(
            const CIPtr< CIStringArray >& callList,
            const asi::connectivity::diagnostic::ResultType result
        ) = 0;
            /**
            getECallSetOfData Method ID: 13
            **/
        virtual void getECallSetOfData(
            const CIPtr< CIString >& set,
            const asi::connectivity::diagnostic::ResultType result
        ) = 0;
            /**
            getECallEraProfileActivationStatus Method ID: 9
            **/
        virtual void getECallEraProfileActivationStatus(
            const bool isActivated,
            const asi::connectivity::diagnostic::ResultType result
        ) = 0;
            /**
            getECallEraProfileAvailabilityStatus Method ID: 11
            **/
        virtual void getECallEraProfileAvailabilityStatus(
            const bool isAvailable,
            const asi::connectivity::diagnostic::ResultType result
        ) = 0;
            /**
            getECallEraIccid Method ID: 7
            **/
        virtual void getECallEraIccid(
            const CIPtr< CIString >& iccid,
            const asi::connectivity::diagnostic::ResultType result
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
        getAerialSwitchStatus_AerialSwitchStatus_ResultTypeCallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<DiagnosticVoiceMeasurementsReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 1;
            ce.assign(inst, mid);
        }

        void
        getECallActivationState_B_ResultTypeCallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<DiagnosticVoiceMeasurementsReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 3;
            ce.assign(inst, mid);
        }

        void
        getECallCallState_U8_ResultTypeCallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<DiagnosticVoiceMeasurementsReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 5;
            ce.assign(inst, mid);
        }

        void
        getEcallOperationStatus_EcallOperationStatus_ResultTypeCallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<DiagnosticVoiceMeasurementsReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 15;
            ce.assign(inst, mid);
        }

        void
        getRecentCallList_aS_ResultTypeCallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<DiagnosticVoiceMeasurementsReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 17;
            ce.assign(inst, mid);
        }

        void
        getECallSetOfData_S_ResultTypeCallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<DiagnosticVoiceMeasurementsReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 13;
            ce.assign(inst, mid);
        }

        void
        getECallEraProfileActivationStatus_B_ResultTypeCallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<DiagnosticVoiceMeasurementsReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 9;
            ce.assign(inst, mid);
        }

        void
        getECallEraProfileAvailabilityStatus_B_ResultTypeCallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<DiagnosticVoiceMeasurementsReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 11;
            ce.assign(inst, mid);
        }

        void
        getECallEraIccid_S_ResultTypeCallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<DiagnosticVoiceMeasurementsReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 7;
            ce.assign(inst, mid);
        }


        virtual ~DiagnosticVoiceMeasurementsReply() {}
    };

}//namespace asi
}//namespace connectivity
}//namespace diagnostic

#endif// ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICVOICEMEASUREMENTSREPLY_HXX
