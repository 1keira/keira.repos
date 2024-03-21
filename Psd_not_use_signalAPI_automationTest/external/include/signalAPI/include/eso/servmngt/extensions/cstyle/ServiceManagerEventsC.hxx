/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleInterfaceC_hxx.tmpl
*/
#ifndef SERVMNGT_EXTENSIONS_SERVICEMANAGEREVENTSC_CSTYLE_HXX
#define SERVMNGT_EXTENSIONS_SERVICEMANAGEREVENTSC_CSTYLE_HXX

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
    \brief The extensions::cstyle::ServiceManagerEvents interface on the client side.
    \detail
            A proxy implements this interface.
        Interface where a client like the IDS sensor can subscribe to certain SM events. 
     *  For now only watchdog miss from an application is reported
    **/
    class ServiceManagerEventsC
    {
    public:
        // List of request methods
        /**
            
        register as an application interested in IDS events from the servicemgr
        \param [in] name
            is the name which identifies the application
        \param [in] event
            an array of events which an application may be interested in

        
            registerMe Method ID: 1
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool registerMe(
            const ipl::string* name,
            const ipl::vector< servmngt::extensions::cstyle::ServiceManagerEventType >* types
        ) const = 0;

        /**
             remove registration 
            unregisterMe Method ID: 2
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool unregisterMe(
            
        ) const = 0;

        ServiceManagerEventsC()  {}
        virtual ~ServiceManagerEventsC() {}
    protected:
        friend class ServiceManagerEventsProxy;
    };

} // cstyle
}//namespace servmngt
}//namespace extensions
#endif// SERVMNGT_EXTENSIONS_SERVICEMANAGEREVENTSC_CSTYLE_HXX
