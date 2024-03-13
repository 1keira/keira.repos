/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceReply_hxx.tmpl
*/
#ifndef SERVMNGT_EXTENSIONS_WATCHDOGREPLY_HXX
#define SERVMNGT_EXTENSIONS_WATCHDOGREPLY_HXX

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
        Watchdog Interface of the servicemanager
      It can be used by any application which like to be watchdog supervised by the
      servicemanager

      An application can register itself at the servicemanager, and will then be
      supervised. 
      In case of a detected WD failure by the servicemanager, the SM
      can kill the process and, if configured in the servicemgr_restart.json, 
      restarted
    **/
    class WatchdogReply {

    public:
    // List of reply methods
            /**
            
        the servicemanager requests that the registered application
        send the alive() call within the period time, which was 
        given at registerMe
        
            requestAlive Method ID: 1
            **/
        virtual void requestAlive(
            
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
        requestAliveCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<WatchdogReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 1;
            ce.assign(inst, mid);
        }


        virtual ~WatchdogReply() {}
    };

}//namespace servmngt
}//namespace extensions

#endif// SERVMNGT_EXTENSIONS_WATCHDOGREPLY_HXX
