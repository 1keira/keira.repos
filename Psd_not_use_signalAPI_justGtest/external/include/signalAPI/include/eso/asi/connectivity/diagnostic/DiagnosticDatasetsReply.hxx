/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceReply_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDATASETSREPLY_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDATASETSREPLY_HXX

#include <comm/commtypes.hxx>
#include <comm/commidltypes.hxx>
#include <comm/CallEvent.hxx>
#include <asi/connectivity/diagnostic/StructDatasetParameter.hxx>
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
    class DiagnosticDatasetsReply {

    public:
    // List of reply methods
            /**
            \brief
            reply for the attribute DatasetParameters
            updateDatasetParameters Method ID: 7
            **/
        virtual void updateDatasetParameters(
            const CIPtr< CIPtrArray< asi::connectivity::diagnostic::DatasetParameter > >& DatasetParameters,
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
        updateDatasetParametersCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<DiagnosticDatasetsReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 7;
            ce.assign(inst, mid);
        }


        virtual ~DiagnosticDatasetsReply() {}
    };

}//namespace asi
}//namespace connectivity
}//namespace diagnostic

#endif// ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICDATASETSREPLY_HXX
