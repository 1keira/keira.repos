#ifndef SERVMNGT_IAPPLICATIONINIT_HXX
#define SERVMNGT_IAPPLICATIONINIT_HXX

/*
    Copyright esolutions GmbH
    All rights reserved
    Authors:
        Marco Staginski
        Martin Ruff
        Martin Stein
*/

#include <servmngt/Definitions.hxx>
#include <servmngt/servmngt_dso.h>

namespace servmngt{

/**
    \brief 
        Interface used by the service management (by the bundle loader component)
        to trigger initialization of an application.

        Internal applications need to implement this interface (except they derive
        from the servmngt::Application base class; see the note below). 

        If the 
        application is integrated into a bundle, a pointer to this interface 
        has to be used when registering the application at the bundle by calling 
        servmngt::Bundle::addApp().

        If the application is integrated into a single app proc, then a pointer to
        this interface is used when the main function of the process gives 
        control to the service management by calling servmngt::startApp().
    \note
        When you implement an application by use of the servmngt::Application
        base class, then you do not need to care about this interface. This 
        is done by the base class. You can call servmngt::Application::getInitIf()
        to retrieve a pointer to the IApplicationInit interface of the application.
*/
class SERVMNGT_EXPORT IApplicationInit
{
public:
    virtual ~IApplicationInit() { }

    /**
        \brief 
            Initialize the application.

            This method is called by the bundle loader when it received a 
            command from the service manager to initialize the application. When
            this method is called, the application shall start its initialization.

            Note that this method is called from within the COMM thread of the 
            bundle loader interface. The application shall not block for a long
            period of time. Typically the following actions are performed in this 
            function:
            - Store the app_id, run_mode, and ps_access_mode.
            - Connect a proxy to the service management COMM interface 
              servmngt::IServmngtAppProxy.
            - Register the own application COMM interface servmngt::IApplicationS.
              You need to use the app_id as instance identifier of this interface
              registration. Otherwise the service manager will not recognize your
              interface.
            - Connect a proxy to the watchdog COMM Interfage servmngt::IWatchdogProxy.
            - Register the application at the watchdog by calling registerApp() on 
              the watchdog proxy.
            - Start the application's threading and complete the initialization,
              if necessary, from the application's business logic main thread.

            Note that it is allowed, but not strictly 
            required to report the states servmngt::AS_INITIALIZING and 
            servmngt::AS_INITIALIZED from within this function. If you need to 
            complete the initialization from within the business logic main thread,
            because you need to perform some long running activities,
            then you must send servmngt::AS_INITIALIZED \b after everything is done. 
            It might make sense to report in this case also the state 
            servmngt::AS_INITIALIZING from within the business  logic
            thread (of course before you start the long running
            activities). The reason for this is that as soon as you have reported
            servmngt::AS_INITIALIZING, you might receive commands like 
            IApplicationS::setPersistenceAccess() via your application COMM interface
            and must be able to handle this calls, even if your threading is
            not started yet.

            Keep in mind that in every case the persistence access mode has to be 
            taken into account. If the application needs persistence read or even 
            read/write access before it can finalize its initialization, it needs 
            to wait for the appropriate access mode before reporting 
            servmngt::AS_INITIALIZED. But it is not possible to wait in this 
            function. This has also be handled in the application's main loop. 
            And you must send servmngt::AS_INITIALIZING before waiting on the 
            desired persistence access mode.
            Additionally the required persistence access mode for initialization 
            has to be documented in the application's system integration notes. 

        \note
            This method must not be overwritten by derived classes.

        \param app_id 
            The application identifier which is used by the service management. 
            There is no need for the application to know this value. However,
            it could be useful for analyzing service management error and warning 
            traces.

        \param system_run_mode
            The current system run mode (e.g. SYS_RM_DOWNLOAD). The system run mode
            is always the same for all applications. However, the actions that 
            must be performed by an application in this mode typically are application
            specific.

        \param app_run_mode
            The current run mode of the application. The application initialization
            should be optimized to reach this application specific run mode as 
            fast as possible.

        \param ps_access_mode
            The current persistence access mode of the application. 

        \errorindicator
            Via return code of true

        \errors
            The application can raise any error. However, the service management
            will only trace the reason and set the application state to AS_FAILED.
            It will not perform any error specific actions.

        \return true if there was an error and the application is not able to initialize
            itself. The service management will recognize the application to be in 
            the servmngt::AS_FAILED state then. If the initialization was successful,
            or if the initialization will be finalized later by another thread, 
            false has to be returned. 
    */
    virtual bool initialize(uint32_t app_id, SystemRunMode system_run_mode, uint32_t app_run_mode, PersistenceAccessMode ps_access_mode) = 0;
    
    virtual void deinitialize() = 0;
};

}

#endif

