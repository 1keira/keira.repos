#ifndef SERVMNGT_APPLICATION_HXX
#define SERVMNGT_APPLICATION_HXX

/*
    Copyright esolutions GmbH
    All rights reserved
    Authors:
		Martin Stein
*/

#include <ipl_config.h>

#include <servmngt/servmngt_dso.h>
#include <servmngt/Definitions.hxx>
#include <servmngt/IApplicationInit.hxx>

namespace servmngt{

class App2ServMngt;

/**
    \brief Base class for applications that can be managed by the service management.

    The easiest way to create an internal application (i.e. an application that 
    cooperates with the service management and is monitored by the watchdog) 
    is to derive from this class. 
    The class encapsulates completely the COMM communication set up and tear down
    and provides handy methods to interact with the service management and the 
    watchdog. 

    Note that the Application class does not make any assumptions on the thread
    model or event system of the real application. The Application base class 
    implements a passive object with no main loop thread or something similar.
    However, it is recommended that a real world application comes with a main 
    loop thread, because it should not perform long running 
    tasks in the abstract methods of Application. The recommended design is to 
    start the application business logic main loop in initApplication(). 
    In all other abstract methods of Application you can then 
    send corresponding signals to your main loop and perform the input handling
    in the main loop. Also feeding the watchdog should be done there.

    Each application \b must support the application state model as shown in the
    chapter "Application state model" of the framework user guide. That means
    each application must apply the states servmngt::AS_STOPPED, 
    servmngt::AS_INITIALIZING, servmngt::AS_INITIALIZED, servmngt::AS_RUNNING,
    servmngt::AS_STOPPING, servmngt::AS_STOPPED, and servmngt::AS_FAILED. Read
    the framework user guide for a detailed description of these states. 

    Note that an application is not allowed to switch its state without trigger
    from the service management. Only the following transitions can be performed
    by the application without external trigger:
    - from servmngt::AS_INITIALIZING to servmngt::AS_INITIALIZED
    - from servmngt::AS_STOPPING to servmngt::AS_STOPPED
    - from any state to servmngt::AS_FAILED

    The application must report its state (by calling setAppState()) to the 
    service manager every time the state changes, even if the state transition 
    was triggered by the service manager.    

    Each application must support changes of the system-run-mode. It requested
    by the service-manager by the call of systemRunModeChanged(...). The
    result of changing the system-run-mode has to be reported to the
    service-manager using the method reportSystemRunMode()

    Each application must support changes of the application-run-mode. The
    meaning of the values of the application-run-mode, which is an uint32_t value
    is defined by the application implementation itself.
    It requested from the service-manager by the call of appRunModeChanged(...). The
    result of changing the application-run-mode has to be reported to the
    service-manager using the method reportAppRunMode(). The application
    has to report it's "real" app-run-mode, which may differ from the requested mode value.
    This behaviour is given to the application design. The service-mananger does no
    comparison check between the requested and the reported application run mode

    An application object is instantiated during bundle initialization 
    (see Bundle::initBundle()) which is performed after the bundle loader has 
    successfully loaded the bundle shared library into a process. When multiple 
    applications are grouped in one bundle, all application instances are created
    during bundle initialization, even if only one application shall be started.
    
    Therefore, and in order to speed up the system startup, it is important that 
    the constructor code of derived classes obeys the following rules:
    - Don't allocate significant system resources.
    - Don't create and start threads.
    - Don't register COMM service interfaces or request COMM proxies.
    - Don't cause significant CPU load or delays.
    - Don't access persistent storage.
    - Don't block.

    All these activities are typically performed in the initApplication() 
    method (persistent storage access might be a special topic).
    
    If the application is integrated into a single application process,
    the creation of the application instance is typically done in the main() 
    function of the single app proc, which is implemented by the application
    developer. See the documentation of the function servmngt::startApp() for
    details.
    
    See the service management samples for a detailed description on how to 
    create an application by use of this class.

    \see Bundle::initBundle()
    \see servmngt::startApp()
**/
class SERVMNGT_EXPORT Application
{
public:
    /**
        \brief The default constructor sets all class attributes to default values. 

        Neither the own COMM application interface is registered yet, nor the 
        service management and watchdog proxies are yet connected. The application
        is still passive (no threads are created) and is simply waiting on
        a trigger for being initialized. The application state is set to 
        servmngt::AS_STOPPED. 

        The application is not yet registered at the watchdog, 
        so you do not have to be afraid of watchdog timeouts for now.
        It will be automatically registered at the watchdog when the service 
        management triggers the initialization of your application. 
        If you do not want that your application is registered with the default 
        timeout period at the watchdog, then you have to call setWatchdogPeriod() 
        with the required timeout in the constructor of the 
        derived application class. However, you can change the timeout period at
        any time, also during initialization.

        Note that a derived application class is very restricted with respect to 
        allowed actions in the constructor. See the detailed class documentation of
        the Application class. E.g. it is not allowed to create threads in the 
        constructor.

    **/
    Application() IPL_NOEXCEPT;

    /**
        \brief Disconnects all proxies and unregisters and destroys the own COMM
            application interface.

        The application should be in the state AS_STOPPED when its class is destroyed.
        If it is not in that state a trace error message is created.
    **/
    virtual ~Application() IPL_NOEXCEPT;

    /**
        \brief Getter for the application state.

        The application code can call this method to retrieve the current 
        application state. There is no need to store the state in an additional
        variable.
        
        \return The current application state.
    **/
    AppState getAppState() IPL_NOEXCEPT { return m_app_state; }

    /**
        \brief An application calls this method to change its state and to report the 
            new state to the service management.

        Note that no consistency check is done here. So if you report an invalid
        state or a not allowed state to the service management (e.g. you report 
        AS_RUNNING after service management requested AS_INITIALIZING), this is 
        not suppressed here.
        
        \param state The new application state.
    **/
    void setAppState(AppState state) IPL_NOEXCEPT;

    /**
        \brief 
            Getter for the application's system run mode.

            The application code can call this method to retrieve the current 
            system run mode. There is no need to store the run mode in an additional
            variable.

        \return The current run mode.
    **/
    SystemRunMode getSystemRunMode() IPL_NOEXCEPT { return m_system_run_mode; }

    /**
        \brief 
            Getter for the application's app-run-mode, as requested from the
            service-manager

            The application code can call this method to retrieve the current 
            requested application run mode. There is no need to store the run mode in an additional
            variable.

        \return The current run mode.
    **/
    uint32_t getRequestedAppRunMode() IPL_NOEXCEPT { return m_app_requested_run_mode; }
    
    /**
        \brief 
            Getter for the application's app-run-mode, which was reported to
            the service-manager

            The application code can call this method to retrieve the current 
            application run mode as reported last time to the service-manager.
            There is no need to store the run mode in an additional
            variable.

        \return The current run mode.
    **/
    uint32_t getReportedAppRunMode() IPL_NOEXCEPT { return m_app_reported_run_mode; }
    
    /**
        \brief Getter for the application's persistence access mode.
        
        The application code can call this method to retrieve the current persistence
        access mode. There is no need to store the access mode in an additional
        variable.
        
        \return The current persistence access mode.
    **/
    PersistenceAccessMode getPersistAccMode() IPL_NOEXCEPT { return m_ps_acc_mode; }

    /**
        \brief Getter for the application's ID.

        The ID is generated by the service management. The application must not
        make any assumptions about the value of the ID, i.e. there is 
        no predefined assignment of IDs like "the navigation app has ID x". 
        Actually the ID is defined by the framework configuration and may change
        when the configuration is changed.

        The service management posts the ID to the application when it is 
        initializing the application. Therefore, when you call this method in the 
        constructor of the derived application class, it will return zero, which
        is an invalid application ID. 

        \return Zero if the application has not been initialized yet. Any other 
            value is a valid application ID.
    **/
    uint32_t getAppID() IPL_NOEXCEPT { return m_app_id; }

    /**
        \brief Getter for the watchdog period.

        The value of the period is initially set to a system default value.
        Use setWatchdogPeriod() to change this value. 
        
        \return The currently used watchdog period in milliseconds 
            for this application.
    **/
    uint32_t getWatchdogPeriod() IPL_NOEXCEPT { return m_watchdog_period; }

    /**
        \brief An application calls this method to change its watchdog period.

        If the application has already been initialized, this method communicates
        with the watchdog to announce the new period for this application. But
        it is also valid to call this method before initialization in the derived 
        application class' constructor. Actually, this is necessary if you want to 
        make the Application class to use the new period already when it 
        registers your derived application at the watchdog (see initApplication()).

        \param period The new watchdog period in milliseconds for this 
            application. It must be in the range of servmngt::WD_MIN_PERIOD to 
            servmngt::WD_MAX_PERIOD. If this value is out of this range it is 
            corrected and the new value is returned.
        \return The new watchdog timeout of the application in milliseconds. If
            the requested one was out of the allowed range, the return value
            might differ from the period parameter.
    **/
    uint32_t setWatchdogPeriod(uint32_t period) IPL_NOEXCEPT;

    /**
        \brief    An application calls this method to send an alive message to the 
                watchdog.
    **/
    void sendWatchdogAliveMsg() IPL_NOEXCEPT;
    
    /**
    \brief
        acknowledged a requestPersistenceFlush() request
    **/
    void persistenceFlushAck() IPL_NOEXCEPT;

    /**
    \brief
        acknowledged a requestSuspend() request
    **/
    bool requestSuspendAck() IPL_NOEXCEPT;
    
    /**
    \brief    
        report the current system-run-mode to the service-manager
        It's the acknowledge to the systemRunModeChanged(...) request from the
        service-manager. 
    \param[in] run_mode
        is the reported run_mode
    \param[in] success
        defines, whether the requested was accepted and performed successfully or not
    \return    true on error, false on success. 
    \errorindicator
        via return value
    \errors
        none
    **/
    bool reportSystemRunMode (SystemRunMode run_mode, bool success) IPL_NOEXCEPT;
    
    /**
    \brief    
        report the current application-run-mode to the service-manager
        It's the acknowledge to the appRunModeChanged(...) request from the
        service-manager. 
    \param[in] run_mode
        is the reported run_mode
    \return    true on error, false on success. 
    \errorindicator
        via return value
    \errors
        none
    **/
    bool reportAppRunMode (uint32_t run_mode) IPL_NOEXCEPT;
    
    /**
        \brief Get the IApplicationInit interface.

        The returned pointer is e.g. needed as parameter in a call to 
        servmngt::startApp().

        \return A pointer to the IApplicationInit interface, which is
            used by the implementation of the Application class.
    **/
    Application* getInitIf() IPL_NOEXCEPT;
    
    /**
    \brief    
        the applications sends a request to the servicemanager to be restarted
        The SM triggers the configured restart scenario as in case of a
        failure of the application (state=AS_FAILED, process crashed, ....)
        but the restart-counter is not incremented
    \return    true on error, false on success. 
    \errorindicator
        via return value
    \errors
        none
    **/
    bool requestRestart() IPL_NOEXCEPT;
    
    /**
    \brief    
        the applications sends a request to the servicemanager to perform
        a user-command. 
        
        The SM searches in the configuration file servicemgr_usercommands.json for
        an entry on root level with the name of the given command
        
        If it's an array of commands, the related jobs are started and performed
        If all the jobs are done, userCommandDone() is called 
        
        The SM looks within the servicemgr_usercommands.json file for an entry
        TODO
    \param[in] id
        value which is send back via the response (userCommandDone). It gives the application
        the possibilit to distinguish between different requests
    \param[in] command
        command to be performed
    \return    true on error, false on success. 
    \errorindicator
        via return value
    \errors
        none
    **/
    bool performUserCommand(const uint32_t id, const char* command) IPL_NOEXCEPT;


    /*!
     * \brief retrieve the instance-ID used by the SM to 
     * register interfaces
     *
     * The service manager registers a number of COMM services
     * by default they are on instance-ID = 1, but in multi SM 
     * scenarios each SM uses an own unique instance ID. This can be
     * retrieved via this call. This is mainly useful for the
     * external interfaces as the external WD or the system event
     * interface
    */
    uint32_t getServicesInstanceID() const IPL_NOEXCEPT;

protected:

    /**
        \brief Will be called when the application needs to initialize itself.

        Derived classes need to implement this method. It will be called
        by the service management (to be precise: by the bundle loader) when the
        application shall be initialized. Note that this method is called from 
        within the COMM thread of the bundle loader interface. Therefore 
        the application must not block for a long period of time. 
        Typically in this method the required
        system resources are allocated, the application's threading is created,
        and the main loop is started.

        When this method is called the Application base class has already 
        performed the following initialization: 

        - The application COMM interface (servmngt::IApplicationS) has already 
          been created and registered successfully. However, you do not need
          to access this interface directly.
        - The proxies to the service management (servmngt::IServmngtAppProxy) 
          and the watchdog (servmngt::IWatchdogProxy) have been connected 
          successfully. However, you do not need to access the proxies directly.
        - The application has been registered at the watchdog. If you want to 
          make this watchdog registration with another period than the default 
          one, you must call setWatchdogPeriod() in the constructor of your 
          derived application class.

        The application should call setAppState(servmngt::AS_INITIALIZING) as 
        early as possible. However, the service management will not send to you any 
        persistence access mode or run mode messages before you called 
        setAppState(servmngt::AS_INITIALIZING). So you should first initialize 
        the application so far that it is ready to handle runModeChanged() and 
        persistenceAccessModeChanged() calls, then call 
        setAppState(servmngt::AS_INITIALIZING), then do further initializing 
        (in particular the long running part), and finally call 
        setAppState(servmngt::AS_INITIALIZED). 

        The application
        must always be able to correctly handle a stopApplication() call at any
        time. Note that the stopApplication() call might occur in parallel from
        another thread while initApplication() is still executed!

        If the initialization failed and it is not possible to execute the application,
        then you have to call setAppState(servmngt::AS_FAILED) and return false.
        
        Note that in a real world application the initialization could take 
        a significant amount of time. In that case it is better to finalize 
        initialization in the main loop thread of the application. 
        In that case the application starts the main loop and returns true in 
        the initApplication() method. But then it <b>must not</b> call 
        setAppState(servmngt::AS_INITIALIZED) here.
        You must not report servmngt::AS_INITIALIZED before 
        initialization is really finalized, i.e. you are able to handle
        service requests.

        The recommended design is to start the application's business logic main 
        thread here and do all other initialization when entering this thread.
        You should then report servmngt::AS_INITIALIZING immediately when 
        entering the business logic thread, do all other long running initialization,
        and finally report servmngt::AS_INITIALIZED.

        Note that it is mandatory to report every application's state change. 
        The service manager will start a timer after it triggered your 
        initialization. If the application does not report 
        servmngt::AS_INITIALIZED in time, the service manager will produce a trace
        warning and will increase the timeout counter of your application. The 
        service management timeout is part of the system configuration.

        Keep in mind that in every case you have to take the persistence access 
        mode into account. When the application needs persistence read or even 
        read/write access before it can finalize its initialization, it needs 
        to wait for the appropriate access mode. But it is not possible to wait 
        in initApplication(). This has to be handled in your application's 
        main loop thread. Additionally the required persistence access mode for 
        initialization has to be documented in the application's system 
        integration notes.

        Keep also in mind that the application is already registered at the 
        watchdog. This means that the watchdog will periodically call the 
        application's watchdogAliveRequest() method, which has to be served. Note
        that watchdogAliveRequest() will be called from within another thread
        context than initApplication().

        \param system_run_mode This tells the application which system run mode shall
            be reached. The requested behaviour is application specific. See the section 
            "Definitions" in the framework user guide.
        \param app_run_mode This tells the application which application run mode shall
            be reached. The run mode is application specific. See the section 
            "Definitions" in the framework user guide.
        \param ps_access_mode The current persistence access mode of the application.
        \return true if the initialization failed, false if initialization was 
            successful or if initialization will be finalized by another thread.
    **/
    virtual bool initApplication(SystemRunMode system_run_mode, uint32_t app_run_mode, PersistenceAccessMode ps_access_mode) = 0;

    /**
        \brief Will be called when the service management triggers the transition
            from servmngt::AS_INITIALIZED to servmngt::AS_RUNNING.

        Derived classes need to implement this method. It will be called by the 
        service management after the application has reported servmngt::AS_INITIALIZED
        and the service management wants the application to switch to 
        servmngt::AS_RUNNING. As soon as the application has entered the run state
        it needs to call setAppState(servmngt::AS_RUNNING); this is not done by
        the base class.

        Derived classes may implement some additional "enter run state actions"
        here. But, as for all abstract methods of the Application class,
        it may not block for a long period of time. The recommended design is to
        send a signal to the business logic main loop thread and perform additional
        actions there.
    **/
    virtual void runApplication() = 0;

    /**
        \brief Will be called when the application needs to enter the state
            servmngt::AS_STOPPING.
        
        Derived classes need to implement this method. It will be called when
        the service management has triggered the application to stop. The application
        needs to enter the servmngt::AS_STOPPING state immediately and to call 
        setAppState(servmngt::AS_STOPPING). It then starts to tear down the 
        application business logic, to free all its resources, and to stop its 
        threading. As last activity the application reports the state 
        servmngt::AS_STOPPED by calling setAppState().
        After this call the application is not allowed to perform any additional
        activities. It should be in the same passive state as after being 
        constructed.

        Note that the application must consider the persistence access mode also 
        during shutdown. Even if no persistence write access is allowed the application
        must shut down without needless delay or sleep. There are system states
        that allow the loss of persistent data for the sake of fast shutdown 
        time (urgent shutdown).

        Also note that at this point the application does not have any possibility 
        to request a delay of the application's shutdown, or even reject the 
        shutdown. This kind of system shutdown delay is negotiated in normal run 
        state between the applications and the power management and is out of the 
        scope of service management. When this method has been called, this is 
        the point of no return for the application. The service management will 
        start a timer (the value is configurable) and will kill the application 
        if it does not report AS_STOPPED in time.
    **/
    virtual void stopApplication() = 0;

    /**
        \brief 
        Will be called when the service management has changed the system run mode of the application.

        The application must acknowledge the request by reportSystemRunMode(...) 
        
        \param run_mode The new run mode.
    **/
    virtual void systemRunModeChanged(SystemRunMode run_mode) = 0;
    
    /**
        \brief 
        Will be called when the service management has changed the application run mode of the application.

        The application must acknowledge the request by reportAppRunMode(...) 
        
        \param run_mode The new run mode.
    **/
    virtual void appRunModeChanged(uint32_t run_mode) = 0;
    
    /**
        \brief Will be called when the service management has changed the
            persistence access mode of the application.
        
        The application does not need to acknowledge the new persistence 
        access mode.
        
        \param ps_access The new persistence access mode.
    **/
    virtual void persistenceAccessModeChanged(PersistenceAccessMode ps_access) = 0;

    /**
        \brief Will be called when a request from the watchdog for an alive
        message has been received.
        
        The watchdog will continuously send this request to the application with 
        a period that can be controlled by the application with setWatchdogPeriod().
        The application must call sendWatchdogAliveMsg() to serve this request, 
        but only after the application has verified that it is running correctly.
        The reply needs to be received by the watchdog within one period.

        Note that the watchdog may use a period which slightly 
        differs from the value set by the application via setWatchdogPeriod().
        Actually, the watchdog may use a slightly longer period, but it will 
        never use a shorter one. Therefore you should not use the 
        watchdogAliveRequest() calls as "clock ticks" in your application
        code.
    **/
    virtual void watchdogAliveRequest() = 0;
    
    /**
    \brief    Will be called to inform an application to flush all it's persistency data to
            a persitency system. 
            
            Normaly, values which shall be stored in a persistency system, are not stored
            automatically any time they are changed but stored in a shadow-location in the memory
            (e.g this may cost time, flash-storages must not be written to often, ...), 
            but only if a reason to store occures, like system-shutdown.
            
            The service-manager knows about such a reason and can inform all applications via this
            call. 
            
            After all values from this application send completely to the persistency-system 
            the application has to answer this call via  persistenceFlushAck()
            
            In addition the paramater ps_access_after_flush tells a new persistence access-mode
            which is valid AFTER flushing all values.
            
            NOTE: The current value of the persistence-access-mode, set at the application before,
            has to be ignored. The flush command has to be performed anyhow
    \param[in] ps_access_after_flush
            is the new persistence access mode which shall be set after the flush
    **/
    virtual void requestPersistenceFlush () = 0;
    
    /**
    \brief
        Informs the application about the occurance of an event within the system

        The application may react on this event, depending on its interest on these events
        It can be overwritten by an application, but it need not

        The application does not need to acknowledge the request
    \param[in] event
        the event which has occured
    */
    virtual void systemEventOccured (const SystemEvent event);

    /*
    \brief
        a project defined event has happended and is distributed
        to the application. The possible values and there meaning
        is project defined and described on project level

        This command has not to be acknowledged by the user application
    */
    virtual void customEventOccured (const uint32_t event);
    
    /**
    \brief
        response to requestUserCommand()
        
        It's called when the request is completely done
        
        It may be overwritten by the application
    */
    virtual void userCommandDone (const uint32_t id, const servmngt::UserCommandResult result);

    /**
    \brief
        informs the application about a suspend request. 
        
        It may be overwritten by the application

    \param[in] request
        is the kind of request

    \param[in] acknowledgeExpected
        defines whether the application has to acknowledge the request
        via requestSuspendAck() after the related actions are performed
    */
    virtual void requestSuspend(servmngt::SuspendRequest request, bool acknowledgeExpected);

private:
    AppState        m_app_state;
    SystemRunMode   m_system_run_mode;
    uint32_t        m_app_requested_run_mode;
    uint32_t        m_app_reported_run_mode;
    PersistenceAccessMode m_ps_acc_mode;
    uint32_t        m_app_id;
    uint32_t        m_watchdog_period;
    App2ServMngt*   m_app2sm;
    friend App2ServMngt;
};

}


#endif
