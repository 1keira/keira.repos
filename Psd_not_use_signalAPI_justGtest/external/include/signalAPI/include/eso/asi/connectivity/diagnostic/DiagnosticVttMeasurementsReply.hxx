/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceReply_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICVTTMEASUREMENTSREPLY_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICVTTMEASUREMENTSREPLY_HXX

#include <comm/commtypes.hxx>
#include <comm/commidltypes.hxx>
#include <comm/CallEvent.hxx>
#include <asi/connectivity/diagnostic/StructVttStatus.hxx>
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
    class DiagnosticVttMeasurementsReply {

    public:
    // List of reply methods
            /**
            getSmsPdus Method ID: 1
            **/
        virtual void getSmsPdus(
            const CIPtr< CIStringArray >& pdus
        ) = 0;
            /**
            getVttStatus Method ID: 3
            **/
        virtual void getVttStatus(
            const CIPtr< asi::connectivity::diagnostic::VttStatus >& vttStatus
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
        getSmsPdus_aSCallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<DiagnosticVttMeasurementsReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 1;
            ce.assign(inst, mid);
        }

        void
        getVttStatus_VttStatusCallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<DiagnosticVttMeasurementsReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 3;
            ce.assign(inst, mid);
        }


        virtual ~DiagnosticVttMeasurementsReply() {}
    };

}//namespace asi
}//namespace connectivity
}//namespace diagnostic

#endif// ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICVTTMEASUREMENTSREPLY_HXX
