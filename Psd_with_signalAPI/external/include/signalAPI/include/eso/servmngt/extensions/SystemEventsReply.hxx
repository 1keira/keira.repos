/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceReply_hxx.tmpl
*/
#ifndef SERVMNGT_EXTENSIONS_SYSTEMEVENTSREPLY_HXX
#define SERVMNGT_EXTENSIONS_SYSTEMEVENTSREPLY_HXX

#include <comm/commtypes.hxx>
#include <comm/commidltypes.hxx>
#include <comm/CallEvent.hxx>
#include <servmngt/extensions/Definitions.hxx>

namespace servmngt
{
namespace extensions
{

    /**
    \brief  Declaration of the reply interface, which must be implemented by any user of this interface
    **/
    class SystemEventsReply {

    public:
    // List of reply methods
            /**
            
        inform the listener about a requested shutdown
        Each listener has to answer with shutdownRequestAck()
        
            shutdownRequested Method ID: 3
            **/
        virtual void shutdownRequested(
            
        ) = 0;
            /**
            
        inform the listener about a requested shutdown
        Each listener has to answer with shutdownRequestAck()
        
            shutdownCancelled Method ID: 1
            **/
        virtual void shutdownCancelled(
            
        ) = 0;
            /**
            
        trigger a suspend request at the application
        
            suspendRequest Method ID: 6
            **/
        virtual void suspendRequest(
            const servmngt::extensions::SuspendRequest which_request
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
        shutdownRequestedCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<SystemEventsReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 3;
            ce.assign(inst, mid);
        }

        void
        shutdownCancelledCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<SystemEventsReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 1;
            ce.assign(inst, mid);
        }

        void
        suspendRequestCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<SystemEventsReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 6;
            ce.assign(inst, mid);
        }


        virtual ~SystemEventsReply() {}
    };

}//namespace servmngt
}//namespace extensions

#endif// SERVMNGT_EXTENSIONS_SYSTEMEVENTSREPLY_HXX
