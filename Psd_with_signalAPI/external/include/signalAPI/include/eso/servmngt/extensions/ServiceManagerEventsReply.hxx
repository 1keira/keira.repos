/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceReply_hxx.tmpl
*/
#ifndef SERVMNGT_EXTENSIONS_SERVICEMANAGEREVENTSREPLY_HXX
#define SERVMNGT_EXTENSIONS_SERVICEMANAGEREVENTSREPLY_HXX

#include <comm/commtypes.hxx>
#include <comm/commidltypes.hxx>
#include <comm/CallEvent.hxx>
#include <servmngt/extensions/StructWatchdogMissedEvent.hxx>
#include <servmngt/extensions/Definitions.hxx>

namespace servmngt
{
namespace extensions
{

    /**
    \brief  Declaration of the reply interface, which must be implemented by any user of this interface
        Interface where a client like the IDS sensor can subscribe to certain SM events. 
     *  For now only watchdog miss from an application is reported
    **/
    class ServiceManagerEventsReply {

    public:
    // List of reply methods
            /**
             notify the client about the watchdog miss 
            notifyWatchdogMissed Method ID: 0
            **/
        virtual void notifyWatchdogMissed(
            const CIPtr< servmngt::extensions::WatchdogMissedEvent >& event
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
        notifyWatchdogMissedCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<ServiceManagerEventsReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 0;
            ce.assign(inst, mid);
        }


        virtual ~ServiceManagerEventsReply() {}
    };

}//namespace servmngt
}//namespace extensions

#endif// SERVMNGT_EXTENSIONS_SERVICEMANAGEREVENTSREPLY_HXX
