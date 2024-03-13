/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceReplyS_hxx.tmpl
*/
#ifndef SERVMNGT_EXTENSIONS_SYSTEMEVENTS_REPLYS_HXX
#define SERVMNGT_EXTENSIONS_SYSTEMEVENTS_REPLYS_HXX
#include <ipl_config.h>
#include <comm/commidltypes.hxx>
#include <servmngt/extensions/Definitions.hxx>
namespace servmngt
{
namespace extensions
{

    /**
    \brief  Interface declaration, which is implemented by the proxy, and used/called by any user of this interface
    **/
    class SystemEventsReplyS
    {
    public:
        // List of reply methods
            /**
            
        inform the listener about a requested shutdown
        Each listener has to answer with shutdownRequestAck()
        
            shutdownRequested Method ID: 3
            **/
        virtual bool shutdownRequested (
            
        ) IPL_NOEXCEPT = 0;

            /**
            
        inform the listener about a requested shutdown
        Each listener has to answer with shutdownRequestAck()
        
            shutdownCancelled Method ID: 1
            **/
        virtual bool shutdownCancelled (
            
        ) IPL_NOEXCEPT = 0;

            /**
            
        trigger a suspend request at the application
        
            suspendRequest Method ID: 6
            **/
        virtual bool suspendRequest (
            const servmngt::extensions::SuspendRequest which_request
        ) IPL_NOEXCEPT = 0;

        virtual ~SystemEventsReplyS() {}
    };

}// namespace servmngt
}// namespace extensions


#endif// SERVMNGT_EXTENSIONS_SYSTEMEVENTS_REPLYS_HXX
