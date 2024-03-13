/*
    Copyright esolutions GmbH
    All rights reserved
    Authors:
        Martin Stein
*/
#ifndef SERVMNGT_CORE_HXX_
#define SERVMNGT_CORE_HXX_


#include <ipl_config.h>
#include <util/config/Values.hxx>
#include <servmngt/IExtension.hxx>
#include <servmngt/Definitions.hxx>
#include <comm/SingleThreadedActiveObjectFactory.hxx>
#include <memory>

namespace servmngt {

#define SM_INTERNAL_WD_PERIOD 10000

/*!
    Service manager core system states.
*/
enum SystemState {
    SYSTEM_NOT_STARTED,     ///< The startup has not been triggered yet.
    SYSTEM_STARTUP_ACTIVE,     ///< The static startup has been started but is not completed yet.
    SYSTEM_UP_AND_RUNNING,     ///< The static startup has been started and is completed.
    SYSTEM_SHUTDOWN_ACTIVE,    ///< A shutdown is active.
    SYSTEM_SHUTDOWN_DONE    ///< A shutdown is done
};

/*!
    \brief    callback interface for Core::execConfigCommandBlock, which is called after the
            last command was performed
*/
class CmdBlockExecutionCB {
public:
    virtual void executeCommandResult(int16_t handle, bool successful) = 0;
    
    virtual ~CmdBlockExecutionCB() {}
};


/*!
    \brief 
        Pure virtual interface class to listen on restart requests for 
        applications or processes

        Implement this interface if you write a project specific service manager
        to get informed on restart requests in case of failure events of
        applications or processes
        
        It's called before the service-manager's internal restart handling
        is called. If a valid command-block for the restart is returned from
        this instance, it's performed and the internal restart handling is omitted
        
        Call Core::addRestartListener() to register the listener at the core.
    \note
        This interface cannot be implemented by an service management 
        application.
    \see
        Core::addRestartListener() Core::removeRestartListener()
*/
class ICoreRestartListener {
public:

    /*!
    \brief    possible actions to be requested from one of the listener calls 
    */
    enum Action {
        /*!
        request is not handled by the listener. All other listeners shall be asked
        */
        ACTION_UNHANDLED,
        //! ignore the restart request
        ACTION_IGNORE,
        //! perform the returned commands
        ACTION_COMMANDS,
        //! perform a system reset
        ACTION_RESET,
        //! action completely handled by the listener -> do nothing
        ACTION_HANDLED,
        //! kill the related process 
        ACTION_KILL,
    };

    /*!
    \brief    defines the reason for a restart request
    */
    enum RestartReason {
        //! from the service-manager because watchdog timeout
        RESTART_REQUESTED_BY_SM_WATCHDOG,
        //! from the service-manager because application or process reports AS_FAILED
        RESTART_REQUESTED_BY_SM_AS_FAILED,
        //! from the service-manager because process crashed
        RESTART_REQUESTED_BY_SM_CRASHED,
        //! from the application or process itself
        RESTART_REQUESTED_BY_SELF
    };
    
    class Decision {
        public:
            Decision()
                : m_action(ICoreRestartListener::ACTION_IGNORE)
                , m_action_string()
                , m_reset_param()
                {
                  toString();
                }
            Decision(ICoreRestartListener::Action a)
                : m_action(a)
                , m_action_string() 
                , m_reset_param()
                {
                  toString();
                }
             ICoreRestartListener::Action action() const { return m_action; }
             void setAction(ICoreRestartListener::Action action);
             void setAction(const ipl::string& action_string);
             const ipl::string& str() const { return m_action_string; }
             void setResetParam(const std::string& p) { m_reset_param = p; }
             const ipl::string resetParam() const { return m_reset_param; }

        private:
            //! set the m_action_string related to m_action;
            void toString();
            //! decision what to do 
            ICoreRestartListener::Action    m_action;
            //! string representation of action
            ipl::string                     m_action_string;
            //! optional parameter as string in case of action=ACTION_RESET
            ipl::string                     m_reset_param;
    };
    virtual ~ICoreRestartListener() {}


    /*!
    \brief    
        Signal that a process has to be restarted and request related actions. 
    \param[in]    name
        name of the process
    \param[in]    applications
        list of applications located on this process
    \param[out]    decision
        decision of what to do
    \param[out] default_app_id_index
        index into the list of given application. This application is used used for the commandblock execution as application id for all jobs on apps without name in the cmd
        If the value should not be used, a -1 must be given
    \return    
        a valid util::config::Array which contains the block if commands to be performed
        or an util::config::Value which is "undefined" (from util::config:Value::getUndefined())
    */
    virtual const util::config::Value& processRestartRequest (
            const ipl::string& name, 
            RestartReason reason, 
            ipl::vector<ipl::string>& applications, 
            Decision& decision, int32_t& default_app_id_index) = 0;
    
    /*!
    \brief    
        Signal that an application has to be restarted and request related actions. 
    \param[in]    app_name
        name of the application
    \param[in]    proc_name
        name of the process the application is running on
    \param[out]    decision
        decision of what to do
    \return    
        a valid util::config::Array which contains the block if commands to be performed
        or an util::config::Value which is "undefined" (from util::config:Value::getUndefined())
    */
    virtual const util::config::Value& applicationRestartRequest (
            const ipl::string& app_name, 
            RestartReason reason, 
            const ipl::string& proc_name, 
            Decision& decision) = 0;
};

/*!
    \brief 
        Pure virtual interface class to listen on service management core state changes like
        application states, process states, system states, etc.

        Implement this interface if you write a project specific service manager
        to get informed on important service management core state changes.
        Call Core::addStateListener() to register the listener at the core.
    \note
        This interface cannot be implemented by an service management 
        application.
    \see
        Core::addStateListener() Core::removeStateListener()
*/
class ICoreStateListener {
public:
    virtual ~ICoreStateListener() {}
    
    /*!
    \brief 
        Signals a system state change.

        Will be called immediately after the service management core has canged
        its system state.
    \note 
        The implementation of this method must not raise an error.
    \param 
        new_state The new system state.
    */
    virtual void systemStateChanged(SystemState new_state) = 0;

    /*!
    \brief 
        Signals an application state change.

        This method will be called immediately after the state of an application has 
        been changed in the service management core internal application descriptors 
        e.g. by a core job. This typically happens when an application reports a new
        state, but can e.g. also happen when a process died.
    \note 
        The implementation of this method must not raise an error.
    \param
        app_name The name of the application.
    \param 
        new_state The new application state.
    */
    virtual void appStateChanged(const ipl::string& app_name, AppState new_state) = 0;

    /*!
    \brief 
        Signals an application run mode change.

        This method will be called immediately after an application run mode has 
        been changed in the service management core internal application descriptors 
        e.g. by a core job. This happens when an application reports a new application
        run mode, or when it reports the state AS_INITIALIZED.
    \note 
        The implementation of this method must not raise an error.
    \param
        app_name The name of the application.
    \param 
        new_mode The new application run mode.
    */
    virtual void appRunModeChanged(const ipl::string& app_name, uint32_t new_mode) = 0;

    /*!
    \brief 
        Signals that an application has acknowledged a system run mode change.
    \note 
        The implementation of this method must not raise an error.
    \param
        app_name The name of the application.
    \param 
        new_mode The system run mode that was reported by the application.
    */
    virtual void sysRunModeChanged(const ipl::string& app_name, SystemRunMode new_mode) = 0;

    /*!
    \brief 
        Signals a process state change.

        This method will be called immediately after an process state has 
        been changed in the service management core internal process descriptors 
        e.g. by a core job.
    \note 
        The implementation of this method must not raise an error.
    \param
        proc_name The name of the process.
    \param 
        new_state The new state of the process.
    */
    virtual void procStateChanged(const ipl::string& proc_name, AppState new_state) = 0;
    
};

/*!
\brief    Listener Interface for user-defined-events
*/
class ICoreUserEventListener {
    public:
        virtual ~ICoreUserEventListener() {}
        /*!
        \brief    informs the registered listener that a user-evenet was injected
        */
        virtual void userEventInjected(int32_t event) = 0;
};

class ICoreSystemListener {
    public:
        virtual ~ICoreSystemListener() {}
        /*!
        \brief    Signals the request for a system reset 
        \param  status 
            additional information about the reason 
        \param parameter
            an additional parameter for the RESET
        \return    false in case of request can be performed, otherwise true
        */
        virtual bool requestSystemReset (const char* status, const char* parameter) = 0;
        
        /*!
        \brief    trigger the watchdog
        */
        virtual void watchdogAlive() = 0;
};


/*!
    \brief 
        Pure static interface class to the service management core.

        This class provides the interface to the generic service manager core.
        It is used by an project spicific service manager implementation. 
    \note
        This class cannot be used by an service management application.
*/
class Core {
public:

    static const int16_t EXEC_HANDLE_INVALID = -1;
    static const int16_t EXEC_HANDLE_NOTHING_TO_DO = 0;
    /*!
    \brief    defines for an execution the state of control
    */
    enum ExecutionState {
        //! nothing reqauested
        EXECUTION_NONE,
        //! execution shall be performed
        EXECUTION_ASKED,
        //! execution is triggered and ongoing
        EXECUTION_REQUESTED,
        //! exection is finished
        EXECUTION_FINISHED,
        //! execution run into timeout
        EXECUTION_TIMEOUT,
        //! execution can't be performed
        EXECUTION_DROPPED,
        //! execution was cancelled
        EXECUTION_CANCELLED
    };

    /*!
    \brief Command attributes.
    */
    enum CmdAttr {
        /*!
            The command shall be started immediately. Note that even when this attribute
            is used, the command will never be executed in the callers thread, but always 
            in the service manager main loop thread.
        */
        CA_START,

        /*!
            Don't start the command but put it into the queue of pending commands. 
        */
        CA_ENQUEUE,

        /*!
            Don't start the command but put it into the queue of pending commands. 
            Additionally mark the command as a blocking one, i.e. after it has been 
            started no further pending command will be started before this command 
            has been finished or the timeout expired.
        */
        CA_ENQUEUE_LOCK
    };
    
    /*!
    \brief    return the COMM ActiveObject singleton, which is used
            for all COMM-interface, used and provided within the
            service-manager core
    */
    static comm::ActiveObjectFactoryPtr getCOMMActiveObject() IPL_NOEXCEPT;

    /*!
    \brief    setup of the service management core system
            It must be called before any access to the service management
    \return    false on success, otherwise true
    \errorindicator
            return value
    \errors    none
    */
    static bool setup(const char* process_name = NULL) IPL_NOEXCEPT;

    /*!
    \brief    shutdown of the service management core system
            It must be called after any access to the service management
    \return    none
    */
    static void shutdown() IPL_NOEXCEPT;

    /*!
    \brief    add an extension (IExtension)
    \return    false on success, otherwise true
    \errorindicator
            return value
    \errors    none
    */
    static bool addExtension(IExtension& ext) IPL_NOEXCEPT;

    /*! add an IExtension::IJob to the job queue of the 
     * servicemanager. It will be performed by the SM
    */
    static void performExtensionJob(IExtension::IJob* job);

    /*! add an IExtension::IEvent and feed all active 
     * IExtension::IJob instances with this event
    */
    static void performExtensionEvent(std::shared_ptr<IExtension::IEvent>& event);


    using ExecCfgCall = std::function<int16_t(const util::config::Value& config, CmdBlockExecutionCB* cb)>;
    using ExtCmdFactory = std::function<IExtension::IJob*(std::string cmndName, const util::config::Value& config)>;
    using ExtCmdFactoryWithExecCfg = std::function<IExtension::IJob*(std::string cmndName, const util::config::Value &config, ExecCfgCall cb)>;
    /*!\brief register a new command to servicemgr core
     * 
     * @param cmndName   the name of the command
     * @param cmdFactory  factory function to create the IExtension::IJob object
     */
    static void registerExtensionCommand(std::string cmndName, ExtCmdFactory cmdFactory);
    static void registerExtensionCommand(std::string cmndName, ExtCmdFactoryWithExecCfg cmdFactory);


    /*!
    \brief    execute the service management system. It returns after shutdown of the
            service management
    \return    false on success, otherwise true
    \errorindicator
            return value
    \errors    none
    */
    static bool start(uint32_t wd_period = SM_INTERNAL_WD_PERIOD) IPL_NOEXCEPT;
    static bool start(uint32_t wd_period, bool ignore_static_startup) IPL_NOEXCEPT;

    /*!
    \brief    trigger the service management service execution to stop is work
            It will end up with the start() call will return
    \return    true in case of error: system is not in state SYSTEM_SHUTDOWN_DONE
            false in case of accepted
    \errors    none
    */
    static bool requestStop() IPL_NOEXCEPT;

    /*!
    \brief    
        Request to execute a command block from the configuration.


        Reads a complete command block from the configuration.
        All commands from the block are read from the configuration and
        put as job into the job-queue. 
        Each error within one command (syntax, execution failure) is only traced, but
        the execution is not stopped.

        Jobs need not to be executed directly. This depends on the attributes of the performed commands.
        
        The method returns after all jobs are created. 

        After the last job was executed completely the caller is informed via
        the given callback interface (param cb). If no callback instance is given the caller 
        isn't informed.
        The callback instance must be alive until it was called.

        If the command block count is zero there is nothing to do.
        In this case "nothing to do" is returned and the callback is NOT called.

        A failure is returned in case of
        - unrecoverable problems
        - ns::command_name not found
        In this case the callback is NOT called.

        It's not guaranteed that the callback is called AFTER the method returns. It may also
        happen, that the callback is called before the method returns.
        
    \param[in]    command_block
            is the config value which contains the array of commands
    \param[in]    cb
            is the callback instance. 
    \return handle of the execution (callback is called)
            EXEC_HANDLE_NOTHING_TO_DO on nothing to do  (callback is not called)
            EXEC_HANDLE_INVALID on error             (callback is not called, )
    */
    static int16_t execConfigCommandBlock (const util::config::Value& command_block, CmdBlockExecutionCB* cb = 0) IPL_NOEXCEPT;

    /*!
    \brief    
        like execConfigCommandBlock (const util::config::Value& command_block, CmdBlockExecutionCB* cb = 0) but
        a default process and application may be given.
        If app_name or proc_name is a known/defined application/process, it's used for all 
        commands in the command block, where the related name for the command is omitted.
    */
    static int16_t execConfigCommandBlock (const util::config::Value& command_block, 
                                            ipl::string& proc_name, ipl::string& app_name, 
                                            uint32_t default_app_run_mode,
                                            CmdBlockExecutionCB* cb = 0) IPL_NOEXCEPT;

    /*!
    \brief    request the core to cancel a running command-block-execution. All pending jobs 
            related to this command-block are removed from the job-queue. 
            In case of cancel_running_jobs=true all running jobs related to this command-block
            are cancelled.
            After all jobs are cancelled the callback given to the related  execConfigCommandBlock() call
            is called.
    \param[in] handle
            is the identifier to the command-block
    \param[in] cancel_running_jobs
            defines whether runnings jobs shall also be cancelled or not
    \return    false in case of cancellation is performed, true in case of "can't be cancelled"
    */
    static bool cancelConfigCommandBlock (int16_t handle, bool cancel_running_jobs) IPL_NOEXCEPT;

    /*!
    \brief return the last reported state of an application.

    \param[in] app_name The name of the application
    \param[out] state The last reported state of the application. Will be set to
        AS_UNDEFINED if app_name is not a valid name of an application. The return
        value will be true in this case. Note that AS_UNDEFINED can also be a
        valid state of an existing application (return value will be false in 
        that case).
    \return false on success, true if app_name is not a valid application name or
        the core has not been initialized yet. 
        state will will be set to AS_UNDEFINED then. 
    \errors    none
    */
    static bool getApplicationState(const ipl::string& app_name, AppState& state) IPL_NOEXCEPT;
    
    /*!
    \brief return the current state of persistence-flush request.

    \param[in] app_name The name of the application
    \param[out] state The current state of the application. 
    \return false on success, true if app_name is not a valid application name or
        the core has not been initialized yet. 
        state will not be changed in this case 
    \errors    none
    */
    static bool getApplicationPSFlushState (const ipl::string& app_name, ExecutionState& state) IPL_NOEXCEPT;
    
    /*!
    \brief return the current state of persistence-flush request.

    \param[in] app_name The name of the application
    \param[out] state The current state of the application. 
    \return false on success, true if app_name is not a valid application name or
        the core has not been initialized yet. 
        state will not be changed in this case 
    \errors    none
    */
    static bool getApplicationSuspend2RamState (const ipl::string& app_name, ExecutionState& state) IPL_NOEXCEPT;

    /*!
    \brief return the last reported state of a process.

    \param[in] proc_name The name of the process
    \param[out] state The last reported state of the process. Will be set to
        AS_UNDEFINED if proc_name is not a valid name of an process. The return
        value will be true in this case. Note that AS_UNDEFINED can also be a
        valid state of an existing process (return value will be false in 
        that case).
    \return false on success, true if app_name is not a valid application name or
        the core has not been initialized yet. 
        state will will be set to AS_UNDEFINED then. 
    \errors    none
    */
    static bool getProcessState(const ipl::string& proc_name, AppState& state) IPL_NOEXCEPT;
    
    /*!
    \brief return the last reported app run mode of an application.

    \param[in] app_name The name of the application
    \param[out] mode The last reported app run mode of the application. Will not
        be changed if app_name is not a valid name of an application. The return
        value will be true in this case.
    \return false on success, true if app_name is not a valid application name or
        the core has not been initialized yet. 
        mode will not be set then. 
    \errors    none
    */
    static bool getApplicationRunMode(const ipl::string& app_name, uint32_t& mode) IPL_NOEXCEPT;


    /*!
    \brief return the last requested app run mode of an application.

    \param[in] app_name The name of the application
    \param[out] mode The last requested app run mode of the application. Will not
        be changed if app_name is not a valid name of an application. The return
        value will be true in this case.
    \return false on success, true if app_name is not a valid application name or
        the core has not been initialized yet. 
        mode will not be set then. 
    \errors    none
    */
    static bool getRequestedApplicationRunMode(const ipl::string& app_name, uint32_t& mode) IPL_NOEXCEPT;
    
    /*!
    \brief return the last reported system run mode of an application.

    \param[in] app_name The name of the application
    \param[out] mode The last reported system run mode of the application. Will not
        be changed if app_name is not a valid name of an application. The return
        value will be true in this case.
    \return false on success, true if app_name is not a valid application name or
        the core has not been initialized yet. 
        mode will not be set then. 
    \errors    none
    */
    static bool getSystemRunMode(const ipl::string& app_name, SystemRunMode& mode) IPL_NOEXCEPT;


    /*!
    \brief return the last reported app run mode of an application.

    \param[in] app_name The name of the application
    \param[out] mode The last reported app run mode of the application. Will not
        be changed if app_name is not a valid name of an application. The return
        value will be true in this case.
    \return false on success, true if app_name is not a valid application name or
        the core has not been initialized yet. 
        mode will not be set then. 
    \errors none
    */
    static bool getPersistenceAccessMode(const ipl::string& app_name, PersistenceAccessMode& mode) IPL_NOEXCEPT;


    /*!
    \brief 
        Trigger the core to create an init application command.
    \note 
        The system run mode that will be used in the servmngt::IBundleLoaderS::initializeApp()
        call will be the active system run mode in the moment of calling initializeApp().

    \param[in] app_name The name of the application as used in the configuration.
    \param[in] app_run_mode The application run mode requested with the initializing request.
    \param[in] ps_mode The persistence acces mode used in the initializing request.
    \param[in] timeout The timeout that will be used by the command.
    \param[in] attr The command attribute. See documentation of servmngt::Core::CmdAttr.
    \return false on success, true if app_name is not a valid application name or the core
        has not been initialized yet. 
    \errors    none
    */
    static bool initApplication(const ipl::string& app_name, uint32_t app_run_mode, 
        PersistenceAccessMode ps_mode, uint32_t timeout, CmdAttr attr=CA_ENQUEUE) IPL_NOEXCEPT;


    /*!
    \brief 
        Trigger the core to create a run application command.
    \param[in] app_name The name of the application as used in the configuration.
    \param[in] timeout The timeout that will be used by the command.
    \param[in] attr The command attribute. See documentation of servmngt::Core::CmdAttr.
    \return false on success, true if app_name is not a valid application name or the core
        has not been initialized yet. 
    \errors    none
    */
    static bool runApplication(const ipl::string& app_name, uint32_t timeout, CmdAttr attr=CA_ENQUEUE) IPL_NOEXCEPT;
    
    /*!
    \brief 
        Trigger the core to create a kill process command.
    \param[in] process_name 
        The name of the application as used in the configuration.
    \param[in] timeout 
        The timeout that will be used by the command.
    \param[in] attr 
        The command attribute. See documentation of servmngt::Core::CmdAttr.
    \return false on success, true if process_name is not a valid process name or the core
        has not been initialized yet. 
    \errors    none
    */
    static bool killProcess (const ipl::string& process_name, uint32_t timeout, CmdAttr attr=CA_ENQUEUE) IPL_NOEXCEPT;


    /*!
    \brief 
        Trigger the core to create a stop application command.
    \param[in] app_name The name of the application as used in the configuration.
    \param[in] timeout The timeout that will be used by the command.
    \param[in] attr The command attribute. See documentation of servmngt::Core::CmdAttr.
    \return false on success, true if app_name is not a valid process name or the core
        has not been initialized yet. 
    \errors    none
    */
    static bool stopApplication(const ipl::string& app_name, uint32_t timeout, CmdAttr attr=CA_ENQUEUE) IPL_NOEXCEPT;


    /*!
    \brief 
        Trigger the core to create a set system run mode command.
    \param[in] mode The new system run mode.
    \param[in] timeout The timeout that will be used by the command.
    \param[in] attr The command attribute. See documentation of servmngt::Core::CmdAttr.
    \return false on success, true on error. 
    \errors    none
    */
    static bool setSystemRunmode(SystemRunMode mode, uint32_t timeout, CmdAttr attr=CA_ENQUEUE) IPL_NOEXCEPT;


    /*!
    \brief 
        Trigger the core to create a set application run mode command.
    \param[in] app_name The name of the application as used in the configuration.
    \param[in] mode The new application run mode.
    \param[in] timeout The timeout that will be used by the command.
    \param[in] attr The command attribute. See documentation of servmngt::Core::CmdAttr.
    \return false on success, true if app_name is not a valid process name or the core
        has not been initialized yet. 
    \errors    none
    */
    static bool setApplicationRunmode(const ipl::string& app_name, uint32_t mode, uint32_t timeout, CmdAttr attr=CA_ENQUEUE) IPL_NOEXCEPT;


    /*!
    \brief 
        Trigger the core to create a set application persistence access mode command.
    \param[in] app_name The name of the application as used in the configuration.
    \param[in] mode The new application persistence access mode.
    \param[in] attr The command attribute. See documentation of servmngt::Core::CmdAttr.
    \return false on success, true if app_name is not a valid process name or the core
        has not been initialized yet. 
    \errors    none
    \note There is no timeout parameter since changing the persistence access mode
        is never acknowledged by an application.
    */
    static bool setPersistenceAccessMode(const ipl::string& app_name, PersistenceAccessMode mode, CmdAttr attr=CA_ENQUEUE) IPL_NOEXCEPT;

    /*!
    \brief
        disable the persistence access mode for all applications by setting
        there ps_access_mode to PS_ACC_NONE. The
        current mode is stored

        for all running applications the persistence-access-mode is set to PS_ACC_NONE
        up from now all commands on applications containing a persistence-access-mode (init, setPSMode)
        the given mode from the command is overwritten by  PS_ACC_NONE

        In case of still disabled persistence access nothing is done
    \return
        true on error, false on success
    \errors
        CORE_NOT_INITIALIZED
    \note
        there is no feed-back whether setting the ps-mode to all running applications
        was successful or not.
     */
    static bool disablePersistenceAccess() IPL_NOEXCEPT;

    /*!
    \brief
        restore the ps_add_mode for all running applications to the mode before
        disablePersistenceAccess() was called.

        all actions done by disablePersistenceAccess() are reverted.
        In case of still enabled persistence access nothing is done
    \return
        true on error, false on success
    \errors
        CORE_NOT_INITIALIZED
    \note
        there is no feed-back whether setting the ps-mode to all running applications
        was successful or not
     */
    static bool restorePersistenceAccess() IPL_NOEXCEPT;

    /*!
    \brief
        set a new persistence-access-mode to all running applications
        and also for all actions in the future
    \return
        true on error, false on success
    \errors
        CORE_NOT_INITIALIZED
    \note
        there is no feed-back whether setting the ps-mode to all running applications
        was successful or not
     */
    static bool setSystemPersistenceAccessMode(servmngt::PersistenceAccessMode mode) IPL_NOEXCEPT;

    /*!
    \brief Register a state listener at the core.
    \see servmngt::ICoreStateListener.
    \see servmngt::Core::removeStateListener
    \param[in] listener A pointer to a ICoreStateListener interface implementation.
        Must not be NULL.
    \return false on success, true if the core has not been initialized yet. 
    \errors    none
    */
    static bool addStateListener(ICoreStateListener* listener) IPL_NOEXCEPT;

    /*!
    \brief Unregister a state listener at the core.
    \see servmngt::ICoreStateListener
    \see servmngt::Core::addStateListener
    \param[in] listener A pointer to a ICoreStateListener interface implementation.
        Must not be NULL.
    \return false on success, true if the core has not been initialized yet. If 
        the listener has not been registered before, this is ignored and false is 
        returned.
    \errors    none
    */
    static bool removeStateListener(ICoreStateListener* listener) IPL_NOEXCEPT;
    
    /*!
    \brief Register a restart listener at the core.
    \see servmngt::ICoreRestartListener.
    \see servmngt::Core::removeRestartListener
    \param[in] listener 
        A pointer to a ICoreRestartListener interface implementation.
        Must not be NULL.
    \return false on success, true if the core has not been initialized yet. 
    \errors    none
    */
    static bool addRestartListener(ICoreRestartListener* listener) IPL_NOEXCEPT;

    /*!
    \brief Unregister a restart listener at the core.
    \see servmngt::ICoreRestartListener
    \see servmngt::Core::addRestartListener
    \param[in] listener 
        A pointer to a ICoreRestartListener interface implementation.
        Must not be NULL.
    \return false on success, true if the core has not been initialized yet. If 
        the listener has not been registered before, this is ignored and false is 
        returned.
    \errors    none
    */
    static bool removeRestartListener(ICoreRestartListener* listener) IPL_NOEXCEPT;

    /*
    \brief    set the listener to system calls of the generic service-mananger
    \return
        true on error, false on success
    \errors
        CORE_NOT_INITIALIZED
    */
    static bool setSystemListener (ICoreSystemListener * listener) IPL_NOEXCEPT;
    
    /*
    \brief    unset the listener to system calls of the generic service-mananger
    \return
        true on error, false on success
    \errors
        CORE_NOT_INITIALIZED
    */
    static bool unsetSystemListener () IPL_NOEXCEPT;

    /*!
    \brief    retrieve the name of the process the given application is running on
    \param    [in] app_name
            is the name of the application, the parent process is requested for
    \param    [out] parent_name
            is the string, the parent name is stored
            In case of the application is unknown, param_name is set to ""
    \return    false in case known application of existing parent, true on error
    \return    
    */
    static bool getApplicationParent (const ipl::string& app_name, ipl::string& parent_name) IPL_NOEXCEPT;

    /*!
    \brief Request the actual core system-state (see definition of servmngt::SystemState).
    \note
        Don't mix up the core system state (startup or shutdown active, etc) 
        and the system run mode (used to signal application modes like software download,
        production mode, etc).
    */
    static SystemState getSystemState () IPL_NOEXCEPT;
    
    /*
    \brief    request the service-manager to perform a shutdown of all applications and 
            processes. The SM main-loop is NOT finished. This can be requested by stop()
            The start and completion of the shutdown is reported by the callback
            ICoreStateListener::systemStateChanged
    \param[in] fast
            defines, whether a fast-shutdown (without persistency saving) or
            a normal-shutdowm (with persistency saving) shall be performed
    \return    true in case of error: system is in state SYSTEM_SHUTDOWN_DONE or SYSTEM_SHUTDOWN_ACTIVE
            false in case of accepted
    */
    static bool requestShutdown (bool fast) IPL_NOEXCEPT;
    
    /*!
    \brief    inject an user-event. All registered listeners are informed about this
    \param[in] event
            is the injected event
    \return
        true on error, false on success
    \errors
        CORE_NOT_INITIALIZED
    */
    static bool injectUserEvent (int32_t event) IPL_NOEXCEPT;


    /*!
    \brief    add a listener 
    \param[in]    listener
            is the callback instance, which is called each time a user-event is injected
    */
    static bool addUserEventListener (ICoreUserEventListener* listener) IPL_NOEXCEPT;
    
    /*!
    \brief    remove a listener 
    \param[in]    listener
    */
    static bool removeUserEventListener (ICoreUserEventListener* listener) IPL_NOEXCEPT;
    
    /*!
    \brief    retrieve the label for the given application state
     */
    static const char* stateLabel(AppState state) IPL_NOEXCEPT;

    /*!
    \brief    retrieve the label for the given pesistence access mode
     */
    static const char* psAccessLabel(PersistenceAccessMode mode) IPL_NOEXCEPT;
    
    /*!
    \brief    mark at the EventLogger that an action is running

    This information is stored in the internal event logger
            In case of a system-reset, caused by a SM error itself, this 
            information is traced and stored in the IRC
    \param[in] actionID
         is an user-defined identifier for the action
         A value of 0 is not allowed
    */
    static void logActionStarted (uint32_t actionID) IPL_NOEXCEPT;
    
    /*!
    \brief    mark at the EventLogger that the last action (see logActionStarted) has
    finished
    */
    static void logActionFinished () IPL_NOEXCEPT;
    
    /*!
    \brief shall wd-handling be done or not
    */
    static bool watchdogDisabled() IPL_NOEXCEPT;

    /*!
     * Add the list of command line parameter
     * They are expected as
     *   --<key> <value> --<key> <value> .....
     * If a key is expected but the string does not start with -- 
     * the string is dropped, and still a key is expected
     *
     * Note: The call is not thread-safe
    */
    static void addCommandline(int argc, const char* argv[]);

    /*!
     * get a commandline parameter from the list given by addCommandLine
     * If the value exists, the string is copied into out and false is returned
     * True is returned in case of key does not exist
    */
    static bool getCommandLineParameter(const char* key, ipl::string& out);
    /*!
     * determine the restart parameter from the given restart configuration
     *
     * param[in] config is the restart configuration
     * param[in] state is the state of the process or application
     * param[out] decision
     *  describes the result
     *  
     *   Example for the configuration:
     *       "on_restart_failed" : "<action>"
     *
     *       "on_restart_failed" : {
     *           "*" : "<action>",
     *           "init" : "<action>"
     *           "run" : "<action>"
     *       }
     *   action has to one of: ["ignore", "kill_process", "reset"]
     *  - an optional string parameter for the restart-action = RESET
     *
     *   Example:
     *      "reset_param" : "<any-string>" 
     *
    */
    static void onRestartActions(const util::config::Value& config, AppState state, 
	                             ICoreRestartListener::Decision& decision);
private:
    Core();
    Core(const Core&) = delete;
    Core& operator=(const Core&) = delete;
    
};


}

#endif

