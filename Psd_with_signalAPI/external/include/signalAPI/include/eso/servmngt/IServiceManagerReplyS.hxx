/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceReplyS_hxx.tmpl
*/
#ifndef SERVMNGT_ISERVICEMANAGER_REPLYS_HXX
#define SERVMNGT_ISERVICEMANAGER_REPLYS_HXX
#include <ipl_config.h>
#include <comm/commidltypes.hxx>
#include <servmngt/Definitions.hxx>
namespace servmngt
{

    /**
    \brief  Interface declaration, which is implemented by the proxy, and used/called by any user of this interface
    Interface between Service Manager and Application
    **/
    class IServiceManagerReplyS
    {
    public:
        // List of reply methods
            /**
            initializeAppResult Method ID: 3
            **/
        virtual bool initializeAppResult (
            const uint32_t app_id,
            const servmngt::LoaderResult result
        ) IPL_NOEXCEPT = 0;

            /**
            
        answer for state requests from run and stop
        
            reportAppState Method ID: 8
            **/
        virtual bool reportAppState (
            const uint32_t app_id,
            const servmngt::AppState state
        ) IPL_NOEXCEPT = 0;

            /**
            reportSystemRunMode Method ID: 9
            **/
        virtual bool reportSystemRunMode (
            const uint32_t app_id,
            const servmngt::SystemRunMode run_mode,
            const bool success
        ) IPL_NOEXCEPT = 0;

            /**
            reportAppRunMode Method ID: 7
            **/
        virtual bool reportAppRunMode (
            const uint32_t app_id,
            const uint32_t run_mode
        ) IPL_NOEXCEPT = 0;

            /**
            persistenceFlushAck Method ID: 5
            **/
        virtual bool persistenceFlushAck (
            const uint32_t app_id
        ) IPL_NOEXCEPT = 0;

            /**
            performUserCommand Method ID: 4
            **/
        virtual bool performUserCommand (
            const uint32_t app_id,
            const uint32_t id,
            const CIPtr< CIString >& command
        ) IPL_NOEXCEPT = 0;

            /**
            suspendAck Method ID: 21
            **/
        virtual bool suspendAck (
            const uint32_t app_id
        ) IPL_NOEXCEPT = 0;

            /**
            requestRestart Method ID: 12
            **/
        virtual bool requestRestart (
            const uint32_t app_id
        ) IPL_NOEXCEPT = 0;

            /**
            responseAliveMsg Method ID: 14
            **/
        virtual bool responseAliveMsg (
            const uint32_t app_id
        ) IPL_NOEXCEPT = 0;

            /**
             
        register at the SM watchdog system
        
            registerAppAtWD Method ID: 6
            **/
        virtual bool registerAppAtWD (
            const uint32_t app_id,
            const uint32_t period_ms
        ) IPL_NOEXCEPT = 0;

            /**
             
        unregister from the SM watchdog system
        
            unregisterAppAtWD Method ID: 23
            **/
        virtual bool unregisterAppAtWD (
            const uint32_t app_id
        ) IPL_NOEXCEPT = 0;

            /**
             
        set a new watchdog period
        
            setPeriodAtWD Method ID: 17
            **/
        virtual bool setPeriodAtWD (
            const uint32_t app_id,
            const uint32_t period_ms
        ) IPL_NOEXCEPT = 0;

        virtual ~IServiceManagerReplyS() {}
    };

}// namespace servmngt


#endif// SERVMNGT_ISERVICEMANAGER_REPLYS_HXX
