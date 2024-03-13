/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceReply_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_NADCALLHANDLINGSERVICESREPLY_HXX
#define ASI_CONNECTIVITY_AL_NADCALLHANDLINGSERVICESREPLY_HXX

#include <comm/commtypes.hxx>
#include <comm/commidltypes.hxx>
#include <comm/CallEvent.hxx>
#include <asi/connectivity/al/StructCallStatus.hxx>
#include <asi/connectivity/al/Definitions.hxx>

namespace asi
{
namespace connectivity
{
namespace al
{

    /**
    \brief  Declaration of the reply interface, which must be implemented by any user of this interface
    **/
    class NadCallHandlingServicesReply {

    public:
    // List of reply methods
            /**
            acceptCallResponse Method ID: 1
            **/
        virtual void acceptCallResponse(
            const asi::connectivity::al::ResultType result
        ) = 0;
            /**
            dialNumberResponse Method ID: 3
            **/
        virtual void dialNumberResponse(
            const asi::connectivity::al::ResultType result
        ) = 0;
            /**
            hangupCallResponse Method ID: 5
            **/
        virtual void hangupCallResponse(
            const asi::connectivity::al::ResultType result
        ) = 0;
            /**
            updCallStatus Method ID: 8
            **/
        virtual void updCallStatus(
            const CIPtr< CIPtrArray< asi::connectivity::al::CallStatus > >& states
        ) = 0;
            /**
            *
        *@param callId The ID of the call, which got disconnected.
        *@param ccCause The cause value for call control according to ETSI TS 124 008.
        *@param endStatus The call end status as reported by the Huawei M2M SDK.
        
            updCallDisconnected Method ID: 7
            **/
        virtual void updCallDisconnected(
            const int32_t callId,
            const int32_t ccCause,
            const int32_t endStatus
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
        acceptCallResponseCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NadCallHandlingServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 1;
            ce.assign(inst, mid);
        }

        void
        dialNumberResponseCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NadCallHandlingServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 3;
            ce.assign(inst, mid);
        }

        void
        hangupCallResponseCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NadCallHandlingServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 5;
            ce.assign(inst, mid);
        }

        void
        updCallStatusCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NadCallHandlingServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 8;
            ce.assign(inst, mid);
        }

        void
        updCallDisconnectedCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NadCallHandlingServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 7;
            ce.assign(inst, mid);
        }


        virtual ~NadCallHandlingServicesReply() {}
    };

}//namespace asi
}//namespace connectivity
}//namespace al

#endif// ASI_CONNECTIVITY_AL_NADCALLHANDLINGSERVICESREPLY_HXX
