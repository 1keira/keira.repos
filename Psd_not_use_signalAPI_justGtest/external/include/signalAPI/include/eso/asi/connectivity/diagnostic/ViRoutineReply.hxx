/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceReply_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_VIROUTINEREPLY_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_VIROUTINEREPLY_HXX

#include <comm/commtypes.hxx>
#include <comm/commidltypes.hxx>
#include <comm/CallEvent.hxx>
#include <asi/connectivity/diagnostic/StructRoutineRequest.hxx>
#include <asi/connectivity/diagnostic/StructRoutineResponse.hxx>
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
    class ViRoutineReply {

    public:
    // List of reply methods
            /**
            routineRequest Method ID: 0
            **/
        virtual void routineRequest(
            const CIPtr< asi::connectivity::diagnostic::RoutineRequest >& request
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
        routineRequestCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<ViRoutineReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 0;
            ce.assign(inst, mid);
        }


        virtual ~ViRoutineReply() {}
    };

}//namespace asi
}//namespace connectivity
}//namespace diagnostic

#endif// ASI_CONNECTIVITY_DIAGNOSTIC_VIROUTINEREPLY_HXX
