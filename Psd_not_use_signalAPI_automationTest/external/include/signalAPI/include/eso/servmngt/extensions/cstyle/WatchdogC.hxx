/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleInterfaceC_hxx.tmpl
*/
#ifndef SERVMNGT_EXTENSIONS_WATCHDOGC_CSTYLE_HXX
#define SERVMNGT_EXTENSIONS_WATCHDOGC_CSTYLE_HXX

#include <comm/commidltypes.hxx>
#include <comm/Lifecycle.hxx>
#include <servmngt/extensions/cstyle/Definitions.hxx>

namespace servmngt
{
namespace extensions
{
namespace cstyle {

    /**
    \brief The extensions::cstyle::Watchdog interface on the client side.
    \detail
            A proxy implements this interface.
        Watchdog Interface of the servicemanager
      It can be used by any application which like to be watchdog supervised by the
      servicemanager

      An application can register itself at the servicemanager, and will then be
      supervised. 
      In case of a detected WD failure by the servicemanager, the SM
      can kill the process and, if configured in the servicemgr_restart.json, 
      restarted
    **/
    class WatchdogC
    {
    public:
        // List of request methods
        /**
            
        register at the servicemanager watchdog. From now the process is
        supervised by the servicemanager
        \param [in] name
            is the name which identifies the application
        \param [in] pid
            is the OS process-id. The SM can use it for killing the process

        \param [in] period_ms
            is the watchdog period in milliseconds
        
            registerMe Method ID: 0
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool registerMe(
            const ipl::string* name,
            const uint32_t pid,
            const uint32_t period_ms
        ) const = 0;

        /**
            unregisterMe Method ID: 3
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool unregisterMe(
            const ipl::string* name
        ) const = 0;

        /**
            
            Acknowledge to requestAlive
        
            responseAlive Method ID: 2
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool responseAlive(
            
        ) const = 0;

        WatchdogC()  {}
        virtual ~WatchdogC() {}
    protected:
        friend class WatchdogProxy;
    };

} // cstyle
}//namespace servmngt
}//namespace extensions
#endif// SERVMNGT_EXTENSIONS_WATCHDOGC_CSTYLE_HXX
