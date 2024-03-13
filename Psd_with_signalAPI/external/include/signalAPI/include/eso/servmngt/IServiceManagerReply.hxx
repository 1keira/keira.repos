/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceReply_hxx.tmpl
*/
#ifndef SERVMNGT_ISERVICEMANAGERREPLY_HXX
#define SERVMNGT_ISERVICEMANAGERREPLY_HXX

#include <comm/commtypes.hxx>
#include <comm/commidltypes.hxx>
#include <comm/CallEvent.hxx>
#include <servmngt/Definitions.hxx>

namespace servmngt
{

    /**
    \brief  Declaration of the reply interface, which must be implemented by any user of this interface
        Interface between Service Manager and Application
    **/
    class IServiceManagerReply {

    public:
    // List of reply methods
            /**
            initializeAppResult Method ID: 3
            **/
        virtual void initializeAppResult(
            const uint32_t app_id,
            const servmngt::LoaderResult result
        ) = 0;
            /**
            
        answer for state requests from run and stop
        
            reportAppState Method ID: 8
            **/
        virtual void reportAppState(
            const uint32_t app_id,
            const servmngt::AppState state
        ) = 0;
            /**
            reportSystemRunMode Method ID: 9
            **/
        virtual void reportSystemRunMode(
            const uint32_t app_id,
            const servmngt::SystemRunMode run_mode,
            const bool success
        ) = 0;
            /**
            reportAppRunMode Method ID: 7
            **/
        virtual void reportAppRunMode(
            const uint32_t app_id,
            const uint32_t run_mode
        ) = 0;
            /**
            persistenceFlushAck Method ID: 5
            **/
        virtual void persistenceFlushAck(
            const uint32_t app_id
        ) = 0;
            /**
            performUserCommand Method ID: 4
            **/
        virtual void performUserCommand(
            const uint32_t app_id,
            const uint32_t id,
            const CIPtr< CIString >& command
        ) = 0;
            /**
            suspendAck Method ID: 21
            **/
        virtual void suspendAck(
            const uint32_t app_id
        ) = 0;
            /**
            requestRestart Method ID: 12
            **/
        virtual void requestRestart(
            const uint32_t app_id
        ) = 0;
            /**
            responseAliveMsg Method ID: 14
            **/
        virtual void responseAliveMsg(
            const uint32_t app_id
        ) = 0;
            /**
             
        register at the SM watchdog system
        
            registerAppAtWD Method ID: 6
            **/
        virtual void registerAppAtWD(
            const uint32_t app_id,
            const uint32_t period_ms
        ) = 0;
            /**
             
        unregister from the SM watchdog system
        
            unregisterAppAtWD Method ID: 23
            **/
        virtual void unregisterAppAtWD(
            const uint32_t app_id
        ) = 0;
            /**
             
        set a new watchdog period
        
            setPeriodAtWD Method ID: 17
            **/
        virtual void setPeriodAtWD(
            const uint32_t app_id,
            const uint32_t period_ms
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
        initializeAppResultCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IServiceManagerReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 3;
            ce.assign(inst, mid);
        }

        void
        reportAppStateCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IServiceManagerReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 8;
            ce.assign(inst, mid);
        }

        void
        reportSystemRunModeCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IServiceManagerReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 9;
            ce.assign(inst, mid);
        }

        void
        reportAppRunModeCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IServiceManagerReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 7;
            ce.assign(inst, mid);
        }

        void
        persistenceFlushAckCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IServiceManagerReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 5;
            ce.assign(inst, mid);
        }

        void
        performUserCommandCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IServiceManagerReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 4;
            ce.assign(inst, mid);
        }

        void
        suspendAckCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IServiceManagerReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 21;
            ce.assign(inst, mid);
        }

        void
        requestRestartCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IServiceManagerReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 12;
            ce.assign(inst, mid);
        }

        void
        responseAliveMsgCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IServiceManagerReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 14;
            ce.assign(inst, mid);
        }

        void
        registerAppAtWDCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IServiceManagerReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 6;
            ce.assign(inst, mid);
        }

        void
        unregisterAppAtWDCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IServiceManagerReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 23;
            ce.assign(inst, mid);
        }

        void
        setPeriodAtWDCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<IServiceManagerReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 17;
            ce.assign(inst, mid);
        }


        virtual ~IServiceManagerReply() {}
    };

}//namespace servmngt

#endif// SERVMNGT_ISERVICEMANAGERREPLY_HXX
