/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceReply_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICCODINGREPLY_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICCODINGREPLY_HXX

#include <comm/commtypes.hxx>
#include <comm/commidltypes.hxx>
#include <comm/CallEvent.hxx>
#include <asi/connectivity/diagnostic/StructAdaptationValues.hxx>
#include <asi/connectivity/diagnostic/StructCodingValues.hxx>
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
    class DiagnosticCodingReply {

    public:
    // List of reply methods
            /**
            \brief
            reply for the attribute AdaptationValues
            updateAdaptationValues Method ID: 11
            **/
        virtual void updateAdaptationValues(
            const CIPtr< asi::connectivity::diagnostic::AdaptationValues >& AdaptationValues,
            const bool isValid
        ) = 0;
            /**
            \brief
            reply for the attribute CodingValues
            \details
            *
         * Delivers coding values received from IOC (either on startup or when
         * a value has been changed)
         *
         * @param CodingValues - Contains values of all coding parameters
         
            updateCodingValues Method ID: 9
            **/
        virtual void updateCodingValues(
            const CIPtr< asi::connectivity::diagnostic::CodingValues >& CodingValues,
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
        updateAdaptationValuesCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<DiagnosticCodingReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 11;
            ce.assign(inst, mid);
        }

        void
        updateCodingValuesCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<DiagnosticCodingReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 9;
            ce.assign(inst, mid);
        }


        virtual ~DiagnosticCodingReply() {}
    };

}//namespace asi
}//namespace connectivity
}//namespace diagnostic

#endif// ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICCODINGREPLY_HXX
