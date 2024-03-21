/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleInterfaceReplyS_hxx.tmpl
*/
#ifndef SERVMNGT_EXTENSIONS_WATCHDOG_REPLYS_CSTYLE_HXX
#define SERVMNGT_EXTENSIONS_WATCHDOG_REPLYS_CSTYLE_HXX
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
    Watchdog Interface of the servicemanager
      It can be used by any application which like to be watchdog supervised by the
      servicemanager

      An application can register itself at the servicemanager, and will then be
      supervised. 
      In case of a detected WD failure by the servicemanager, the SM
      can kill the process and, if configured in the servicemgr_restart.json, 
      restarted
    **/
    class WatchdogReplyS
    {
    public:
        // List of reply methods
            /**
            
        the servicemanager requests that the registered application
        send the alive() call within the period time, which was 
        given at registerMe
        
            requestAlive Method ID: 1
            **/
        virtual bool requestAlive (
            
        ) = 0;


        virtual ~WatchdogReplyS() {}
    protected:
        friend class WatchdogProxyReply;
    };

} // namespace cstyle
}// namespace servmngt
}// namespace extensions


#endif// SERVMNGT_EXTENSIONS_WATCHDOG_REPLYS_CSTYLE_HXX
