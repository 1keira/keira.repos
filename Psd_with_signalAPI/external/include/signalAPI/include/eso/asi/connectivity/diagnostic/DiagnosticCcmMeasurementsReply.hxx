/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceReply_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICCCMMEASUREMENTSREPLY_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICCCMMEASUREMENTSREPLY_HXX

#include <comm/commtypes.hxx>
#include <comm/commidltypes.hxx>
#include <comm/CallEvent.hxx>
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
    \brief  Declaration of the reply interface, which must be implemented by any user of this interface
    **/
    class DiagnosticCcmMeasurementsReply {

    public:
    // List of reply methods
            /**
            getSokFailedVerificationPduIds Method ID: 1
            **/
        virtual void getSokFailedVerificationPduIds(
            const CIPtr< CIUInt16Array >& ids,
            const asi::connectivity::diagnostic::ResultType result
        ) = 0;
            /**
            getSokFreshness Method ID: 3
            **/
        virtual void getSokFreshness(
            const CIPtr< CIPtrArray< asi::connectivity::diagnostic::SokFreshness > >& freshnessInfos,
            const asi::connectivity::diagnostic::ResultType result
        ) = 0;
            /**
            getSokMissingKeys Method ID: 5
            **/
        virtual void getSokMissingKeys(
            const CIPtr< CIUInt16Array >& keys,
            const asi::connectivity::diagnostic::ResultType result
        ) = 0;
            /**
            getSokTime Method ID: 7
            **/
        virtual void getSokTime(
            const CIPtr< asi::connectivity::diagnostic::SokTime >& timeInfo,
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
        getSokFailedVerificationPduIds_aU16_ResultTypeCallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<DiagnosticCcmMeasurementsReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 1;
            ce.assign(inst, mid);
        }

        void
        getSokFreshness_aSokFreshness_ResultTypeCallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<DiagnosticCcmMeasurementsReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 3;
            ce.assign(inst, mid);
        }

        void
        getSokMissingKeys_aU16_ResultTypeCallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<DiagnosticCcmMeasurementsReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 5;
            ce.assign(inst, mid);
        }

        void
        getSokTime_SokTime_ResultTypeCallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<DiagnosticCcmMeasurementsReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 7;
            ce.assign(inst, mid);
        }


        virtual ~DiagnosticCcmMeasurementsReply() {}
    };

}//namespace asi
}//namespace connectivity
}//namespace diagnostic

#endif// ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICCCMMEASUREMENTSREPLY_HXX
