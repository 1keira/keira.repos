/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleInterfaceReply_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDTCSREPLY_CSTYLE_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDTCSREPLY_CSTYLE_HXX

#include <comm/commtypes.hxx>
#include <comm/commidltypes.hxx>
#include <comm/CallEvent.hxx>
#include <asi/connectivity/diagnostic/cstyle/StructDtc.hxx>
#include <asi/connectivity/diagnostic/cstyle/Definitions.hxx>

namespace asi
{
namespace connectivity
{
namespace diagnostic
{
namespace cstyle
{

    /**
    \brief  Declaration of the reply interface, which must be implemented by any user of this interface
    **/
    class DiagnosticDtcsReply {

    public:
    // List of reply methods
            /**
            \brief
            reply for the attribute Dtcs
            updateDtcs Method ID: 8
            **/
        virtual void updateDtcs(
            const ipl::vector< asi::connectivity::diagnostic::cstyle::Dtc >* Dtcs,
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
        updateDtcsCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<DiagnosticDtcsReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 8;
            ce.assign(inst, mid);
        }


        virtual ~DiagnosticDtcsReply() {}
    };

} // namespace cstyle
}//namespace asi
}//namespace connectivity
}//namespace diagnostic

#endif// ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDTCSREPLY_CSTYLE_HXX
