/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceReplyS_hxx.tmpl
*/
#ifndef SERVMNGT_EXTENSIONS_SERVICEMANAGEREVENTS_REPLYS_HXX
#define SERVMNGT_EXTENSIONS_SERVICEMANAGEREVENTS_REPLYS_HXX
#include <ipl_config.h>
#include <comm/commidltypes.hxx>
#include <servmngt/extensions/StructWatchdogMissedEvent.hxx>
#include <servmngt/extensions/Definitions.hxx>
namespace servmngt
{
namespace extensions
{

    /**
    \brief  Interface declaration, which is implemented by the proxy, and used/called by any user of this interface
    Interface where a client like the IDS sensor can subscribe to certain SM events. 
     *  For now only watchdog miss from an application is reported
    **/
    class ServiceManagerEventsReplyS
    {
    public:
        // List of reply methods
            /**
             notify the client about the watchdog miss 
            notifyWatchdogMissed Method ID: 0
            **/
        virtual bool notifyWatchdogMissed (
            const CIPtr< servmngt::extensions::WatchdogMissedEvent >& event
        ) IPL_NOEXCEPT = 0;

        virtual ~ServiceManagerEventsReplyS() {}
    };

}// namespace servmngt
}// namespace extensions


#endif// SERVMNGT_EXTENSIONS_SERVICEMANAGEREVENTS_REPLYS_HXX
