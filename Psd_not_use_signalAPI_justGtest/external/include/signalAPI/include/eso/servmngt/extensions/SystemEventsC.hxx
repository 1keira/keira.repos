/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceC_hxx.tmpl
*/
#ifndef SERVMNGT_EXTENSIONS_SYSTEMEVENTSC_HXX
#define SERVMNGT_EXTENSIONS_SYSTEMEVENTSC_HXX

#include <ipl_config.h>
#include <comm/commidltypes.hxx>
#include <servmngt/extensions/Definitions.hxx>

namespace servmngt
{
namespace extensions
{

    /**
    \brief The extensions::SystemEvents interface on the client side.
    \details
            A proxy implements this interface.
    **/
    class SystemEventsC
    {
    public:
        // List of request methods
        /**
            
        register as servicemanager system event listener. From now the process is
        informed by the servicemanager about system events
        \param [in] name
            is the name which identifies the application

        
            registerMe Method ID: 0
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool registerMe(
            const CIPtr< CIString >& name
        ) const IPL_NOEXCEPT = 0;

        /**
             remove registration 
            unregisterMe Method ID: 7
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool unregisterMe(
            
        ) const IPL_NOEXCEPT = 0;

        /**
            
        acknowleded a shutdownRequest()
        
            shutdownRequestedAck Method ID: 4
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool shutdownRequestedAck(
            
        ) const IPL_NOEXCEPT = 0;

        /**
            
        acknowleded a shutdownRequest()
        
            shutdownCancelledAck Method ID: 2
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool shutdownCancelledAck(
            
        ) const IPL_NOEXCEPT = 0;

        /**
            
        acknowleded a suspendRequest
        
            suspendAck Method ID: 5
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool suspendAck(
            
        ) const IPL_NOEXCEPT = 0;

        SystemEventsC()  {}
        virtual ~SystemEventsC() {}
    protected:
        friend class SystemEventsProxy;
    };

}//namespace servmngt
}//namespace extensions
#endif// SERVMNGT_EXTENSIONS_SYSTEMEVENTSC_HXX
