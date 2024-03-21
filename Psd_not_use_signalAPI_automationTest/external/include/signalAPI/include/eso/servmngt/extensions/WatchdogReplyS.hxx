/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceReplyS_hxx.tmpl
*/
#ifndef SERVMNGT_EXTENSIONS_WATCHDOG_REPLYS_HXX
#define SERVMNGT_EXTENSIONS_WATCHDOG_REPLYS_HXX
#include <ipl_config.h>
#include <comm/commidltypes.hxx>
#include <servmngt/extensions/Definitions.hxx>
namespace servmngt
{
namespace extensions
{

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
            
        ) IPL_NOEXCEPT = 0;

        virtual ~WatchdogReplyS() {}
    };

}// namespace servmngt
}// namespace extensions


#endif// SERVMNGT_EXTENSIONS_WATCHDOG_REPLYS_HXX
