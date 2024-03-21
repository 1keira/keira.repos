/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleInterfaceReplyS_hxx.tmpl
*/
#ifndef SERVMNGT_EXTENSIONS_SERVICEMANAGEREVENTS_REPLYS_CSTYLE_HXX
#define SERVMNGT_EXTENSIONS_SERVICEMANAGEREVENTS_REPLYS_CSTYLE_HXX
#include <comm/commidltypes.hxx>
#include <comm/Lifecycle.hxx>
#include <servmngt/extensions/cstyle/StructWatchdogMissedEvent.hxx>
#include <servmngt/extensions/cstyle/Definitions.hxx>
namespace servmngt
{
namespace extensions
{
namespace cstyle {

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
            const servmngt::extensions::cstyle::WatchdogMissedEvent* event
        ) = 0;


        virtual ~ServiceManagerEventsReplyS() {}
    protected:
        friend class ServiceManagerEventsProxyReply;
    };

} // namespace cstyle
}// namespace servmngt
}// namespace extensions


#endif// SERVMNGT_EXTENSIONS_SERVICEMANAGEREVENTS_REPLYS_CSTYLE_HXX
