/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleInterfaceReplyS_hxx.tmpl
*/
#ifndef SERVMNGT_EXTENSIONS_SYSTEMEVENTS_REPLYS_CSTYLE_HXX
#define SERVMNGT_EXTENSIONS_SYSTEMEVENTS_REPLYS_CSTYLE_HXX
#include <comm/commidltypes.hxx>
#include <comm/Lifecycle.hxx>
#include <servmngt/extensions/cstyle/Definitions.hxx>
namespace servmngt
{
namespace extensions
{
namespace cstyle {

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
            
        ) = 0;

            /**
            
        inform the listener about a requested shutdown
        Each listener has to answer with shutdownRequestAck()
        
            shutdownCancelled Method ID: 1
            **/
        virtual bool shutdownCancelled (
            
        ) = 0;

            /**
            
        trigger a suspend request at the application
        
            suspendRequest Method ID: 6
            **/
        virtual bool suspendRequest (
            const servmngt::extensions::cstyle::SuspendRequest which_request
        ) = 0;


        virtual ~SystemEventsReplyS() {}
    protected:
        friend class SystemEventsProxyReply;
    };

} // namespace cstyle
}// namespace servmngt
}// namespace extensions


#endif// SERVMNGT_EXTENSIONS_SYSTEMEVENTS_REPLYS_CSTYLE_HXX
