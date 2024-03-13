/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceC_hxx.tmpl
*/
#ifndef SERVMNGT_ISERVICEMANAGERC_HXX
#define SERVMNGT_ISERVICEMANAGERC_HXX

#include <ipl_config.h>
#include <comm/commidltypes.hxx>
#include <servmngt/Definitions.hxx>

namespace servmngt
{

    /**
    \brief The servmngt::IServiceManager interface on the client side.
    \details
            A proxy implements this interface.
        Interface between Service Manager and Application
    **/
    class IServiceManagerC
    {
    public:
        // List of request methods
        /**
            initializeApp Method ID: 2
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool initializeApp(
            const uint32_t app_id,
            const uint32_t bundle_id,
            const servmngt::SystemRunMode system_run_mode,
            const uint32_t app_run_mode,
            const servmngt::PersistenceAccessMode ps_access_mode
        ) const IPL_NOEXCEPT = 0;

        /**
            run Method ID: 15
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool run(
            
        ) const IPL_NOEXCEPT = 0;

        /**
            stop Method ID: 20
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool stop(
            
        ) const IPL_NOEXCEPT = 0;

        /**
            setSystemRunMode Method ID: 19
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool setSystemRunMode(
            const servmngt::SystemRunMode run_mode
        ) const IPL_NOEXCEPT = 0;

        /**
            
        request to stop the process 
        
            exitProcess Method ID: 1
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool exitProcess(
            
        ) const IPL_NOEXCEPT = 0;

        /**
            setAppRunMode Method ID: 16
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool setAppRunMode(
            const uint32_t run_mode
        ) const IPL_NOEXCEPT = 0;

        /**
            setPersistenceAccess Method ID: 18
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool setPersistenceAccess(
            const servmngt::PersistenceAccessMode ps_access
        ) const IPL_NOEXCEPT = 0;

        /**
            requestPersistenceFlush Method ID: 11
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool requestPersistenceFlush(
            const servmngt::PersistenceAccessMode ps_access_after_flush
        ) const IPL_NOEXCEPT = 0;

        /**
            systemEventOccured Method ID: 22
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool systemEventOccured(
            const servmngt::SystemEvent event
        ) const IPL_NOEXCEPT = 0;

        /**
            userCommandDone Method ID: 24
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool userCommandDone(
            const uint32_t id,
            const servmngt::UserCommandResult result
        ) const IPL_NOEXCEPT = 0;

        /**
            requestSuspend Method ID: 13
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool requestSuspend(
            const servmngt::SuspendRequest request,
            const bool acknowledgeExpected
        ) const IPL_NOEXCEPT = 0;

        /**
            
            a project defined event has happended and is distributed
            to the application. The possible values and there meaning
            is project defined and has to be described on project level

            This command has not to be acknowledged by the user application
        
            customEventOccured Method ID: 0
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool customEventOccured(
            const uint32_t event
        ) const IPL_NOEXCEPT = 0;

        /**
            requestAliveMsg Method ID: 10
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool requestAliveMsg(
            
        ) const IPL_NOEXCEPT = 0;

        IServiceManagerC()  {}
        virtual ~IServiceManagerC() {}
    protected:
        friend class IServiceManagerProxy;
    };

}//namespace servmngt
#endif// SERVMNGT_ISERVICEMANAGERC_HXX
