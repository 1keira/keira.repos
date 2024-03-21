/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_PROCESSTNG_HXX
#define OSAL_PROCESSTNG_HXX

#include <ipl_config.h>

#include <common/Macros.hxx>

#include <common/types/vector.hxx>
#include <common/types/utility.hxx>
#include <common/types/string.hxx>
#include <common/NonCopyable.hxx>

#ifndef USE_SPAWN_API_IN_POSIX_PROCESSTNG
    #include <common/error/Error.hxx>
#endif


#ifdef IPL_OS_POSIX
#    include "posix/ProcessTNGDefs.hxx"
#    include "posix/SchedDefs.hxx"
#elif defined (IPL_OS_WINPC)
#    include "win32/ProcessTNGDefs.hxx"
#    include "win32/SchedDefs.hxx"
#elif defined (IPL_OS_INTEGRITY)
#    include "integrity/ProcessTNGDefs.hxx"
#    include "integrity/SchedDefs.hxx"
#else
#    error "error undefined IPL_OS_ variant"
#endif

#include <osal/osal_dso.h>
#include <osal/osal.hxx>
#include <osal/Mutex.hxx>
#include <osal/Condition.hxx>
#include <osal/Pipe.hxx>
#include <osal/Thread.hxx>

#include <string.h>

namespace osal {

    class UnicodeString;

    /*!
        \brief A child processes

        The simplest use case is the following:

        Creating a child process that runs in parallel. It inherits stdin,
        stdout and stderr from the parent. It inherits the environment
        from the parent. No asynchronous notification of child process exit.
        The return code is collected at some later time by the client
        synchronously.

        Advanced operations are possible: Asynchronous notification via
        callback upon child process exit, redirecting child's stdin, stdout and
        stderr, setting a custom environment for the child.

        \note Win32 doesn't support suspension of processes in a feasible way.
        Only individual threads from a process can be suspended. Also sending
        cooperative termination signals like SIGTERM on POSIX aren't available
        on system API level on Win32.

    */
    class OSAL_EXPORT ProcessTNG: public ipl::NonCopyable {

    public:

        //! specific error IDs
        enum ProcessErrors
        {
            START_FAILED = 0,
            CREATE_FAILED,
            KILL_FAILED,
            // WAIT_FAILED is already set on win32
            WAIT_FAIL,
            NOT_FOUND
        };

        static ipl::ErrorType Error;
        //! \brief Platform dependent executable naming postfix
        static const char *const ExecutableSuffix;
        typedef osal::Priority Priority;
        //! \brief Environment variables in the form of Name-value-pairs
        //! (avoid '='!)
        typedef ipl::vector<ipl::pair<ipl::string, ipl::string> > Vars;

        //! \brief Merged process exit data
        class ExitState {

        public:
            ExitState() :
                m_has_exited(false),
                m_was_killed(false),
                m_exit_code(-1),
                m_obj(NULL) { }

            /*!
                \brief Process exit state for unsuccesful child exit
                (e.g. wait() failed within timeout constraints)
            */
            ExitState(osal::ProcessTNG *obj) :
                m_has_exited(false),
                m_was_killed(false),
                m_exit_code(-1),
                m_obj(obj) { }

            /*!
                \brief Process exit state for successful child exit

                \param[in] obj The associated object
                \param[in] was_killed Whether the process was killed as opposed
                to normal exit
                \param[in] exit_code The exit code of the process (only valid
                if \a !was_killed)
            */
            ExitState(osal::ProcessTNG *obj, const bool was_killed,
                    const ProcessExitCode exit_code):
                m_has_exited(true), m_was_killed(was_killed),
                m_exit_code(exit_code), m_obj(obj) {}

            //! \brief Whether the child process actually exited
            bool hasExited() const { return m_has_exited; }

            //! \brief Whether the child process was killed by us
            //!
            //! Only valid if hasExited() returns true.
            //! This condition is asserted.
            //!
            //! Whether a child killed by another process is reported as killed
            //! or not is system dependent.
            bool wasKilled() const {
                IPL_ASSERT( m_has_exited );
                return m_was_killed;
            }

            /*!
                \brief The child's exit code

                Only valid if hasExited() returns true.
                This condition is asserted.

                In case the child process could not be started, because
                libraries or something similar were missing, or if the child
                abnormally terminated (being killed, aborted etc.) then the exit
                codes returned differ greatly between platforms, and worse
                aren't event documented/standardized on some (namely Win32).
            */
            ProcessExitCode getExitCode() const {
                IPL_ASSERT(!m_was_killed);
                return m_exit_code;
            }

            //! \brief The associated object
            osal::ProcessTNG *getObj() const { return m_obj; }

            //! \brief No particular meaning, only needed for ordering containers
            bool operator<(const ExitState &other) const { return m_obj<other.m_obj; }

        private:
            bool m_has_exited;
            bool m_was_killed;
            ProcessExitCode m_exit_code;
            osal::ProcessTNG *m_obj;
        };

        /*!
            \brief Callback interface for child process state change
        */
        class IProcessEvent {

        public:
            virtual ~IProcessEvent() {}

            /*!
                \brief The child process has exited. Duh.

                \a exit_state.hasExited() will always return true. You may
                delete the object associated with \a exit_state from within the
                callback.

                \warning This callback runs in the context of an internal OSAL
                thread. Thus the callback code should not block, else other
                functionality is stalled.
            */
            virtual void processExited(ExitState &exit_state) = 0;
        };

        /*!
            Use setExecutable(), setArgs() and the other methods as necessary
            to set up what to run and start() or startSync() to actually run it.

            If you pass a Callback object \a cb, the process' termination will
            reported to it. If you don't, process termination can be checked for
            with wait().

            \errorindicator via isValid()

            \errors ipl::CommonError with IDs:
            - INVALID_PATH if exec_path is not a valid absolute path or if it
              is a valid path but the pointer to file is not executable.
              These checks are only done in debug mode.
            \{
        */
        inline ProcessTNG(IProcessEvent *const cb=NULL);
        inline ProcessTNG(const osal::UnicodeString &ucs, IProcessEvent *const cb=NULL);
        inline ProcessTNG(const ipl::string &exec_path, IProcessEvent *const cb=NULL);
        /*! \} */

        /*!
            No child process must be active any more. You are responsible
            yourself to ensure this, e.g. via wait(). This condition is asserted.
        */
        virtual ~ProcessTNG();

        //! \brief Has construction beed successful?
        bool isValid() const { return !m_has_error; }

        /*!
            \brief Set executable path, check for validity

            This function will check for existence of \c exec_path
            on the filesystem and also that \c exec_path is an
            executable file (if this is possible on the underlying
            OS).

            \return \c true on error, \c false on success

            \errors osal::FileAccessError with ID BAD_PATH if \c exec_path is
            not existing and executable

            \{
        */
        bool setExecutable(const ipl::string &exec_path);
        bool setExecutable(const osal::UnicodeString &ucs);
        /*! \} */

        /*!
            By convention the child's \c argv[0] is the path to its executable.
            This one is supplied regardless of the arguments set here.
        */
        inline void setArgs(const ipl::vector<ipl::string> &args);

        /*!
            \brief Set the environment to be used in the call

            \a vars contains name-value-pairs which shouldn't contain any '='.
            If no or an empty environment is set, the child inherits caller's
            environment instead.
        */
        inline void setEnv(const Vars &vars);

        /*!
            If \a discard is \c true, the child's \c stdout won't show up
            on the caller's \c stdout or whatever you set with setStdout().

        */
        void discardStdout(const bool discard=true) { m_discard_stdout = discard; };

        /*!
            If \a discard is \c true, the child's \c stderr won't show up
            on the caller's \c stderr or whatever you set with setStderr().

        */
        void discardStderr(const bool discard=true) { m_discard_stderr = discard; };

        /*!
            If \a discard is \c true, the child's \c stdout and \c stderr won't
            show up on the caller's \c stdout and \c stderr or whatever you set
            with setStdout() and setStderr().

        */
        void discardOutput(const bool discard=true) {
            discardStdout(discard);
            discardStderr(discard);
        }

        /*!
            The child's \c stdin shall read from the file \a from.
            If \a from is empty, the parent's \c stdin is inherited instead.

        */
        inline void setStdin(const ipl::string &from);
        /*!
            The child's \c stdin shall read from \a pipe.

        */
        inline void setStdin(osal::Pipe &pipe);

        /*!
            The child's \c stdout shall be written to the file \a to.
            If \a to is empty, the parent's \c stdout is inherited instead.

            setStdout() and setStderr() are allowed to use the same file path.

        */
        inline void setStdout(const ipl::string &to, const bool append=false);
        /*!
            The child's \c stdout shall be written to \a pipe.

        */
        inline void setStdout(osal::Pipe &pipe);

        /*!
            The child's \c stderr shall be written to the file \a to.
            If \a to is empty, the parent's \c stderr is inherited instead.

            setStdout() and setStderr() are allowed to use the same file path.

        */
        inline void setStderr(const ipl::string &to, const bool append=false);
        /*!
            The child's \c stderr shall be written to \a pipe.

        */
        inline void setStderr(osal::Pipe &pipe);

        /*!
            Both the child's \c stdout and \c stderr shall be written to the
            file \a to. If \a to is empty, the parent's \c stdout and \c stderr
            are inherited instead.

        */
        void setOutput(const ipl::string &to, const bool append=false) {
            setStdout(to, append);
            setStderr(to, append);
        }
        /*!
            Both the child's \c stdout and \c stderr shall be written to \a pipe.

        */
        void setOutput(osal::Pipe &pipe)
        {
            setStdout(pipe);
            setStderr(pipe);
        }

        /*!
            \brief Set whether the child should have its own process group

            The child's children will by default share the child's process group.
            This allows terminating them all in one go by killing the group,
            which the kill() method will do automatically.
        */
        inline void createNewProcessGroup(const bool val) { m_create_new_pg = val; }
        //! \brief Whether the child should be created in its own process group
        inline bool createNewProcessGroup() const { return m_create_new_pg; }

        /*!
            \brief Sets the child's priority

            With this call the child always inherits the scheduling policy of the thread calling start().
            <br>See setSchedAttrs(const osal::sched::Attr&, ) for a way
            to set scheduling policy and its parameters.

            If \a inherit_priority is \c true the child also inherits the priority
            of the thread calling start().
            <br>If \a inherit_priority is \c false
            the child is started with priority \a prio.
            <br>If start() can't set the priority (e.g. due to lacking permissions) it
            will fall back to inheriting the callers' priority.

            \return \c true on error, \c false on success

            \errorindicator via return code

            \note
            On Linux - if the thread that calls start() has the osal::sched::OSAL_SCHED_POLICY_NORMAL
            policy this call will change the nice value of the main thread of the child process.
        */
        bool setPriority(const bool inherit_priority, const Priority prio = 0);


        /*!
           \brief
              Sets the scheduling attributes of the child.

            Start() may fail due to invalid parameters set here.

           \param
              attr The scheduling policy and parameter for the child process.
           \return
              true on error, false on success
           \errorindicator
              via return code
           \errors
              Thread::Error with IDs

              - SETPRIORITY_FAILED if an operation regarding getting/setting
              the priority failed.

        */
        bool setSchedAttrs(const osal::sched::Attr& attr);

        /*!
            \brief Set which CPU(s) the child may run on

            Each bit in \a mask corresponds to a CPU. If it is \c false,
            the corresponding CPU is not used by this process (if the system
            supports this). When the \a mask is all-\c false, the behaviour is
            system dependent.

            Missing bits (\a mask too short) are treated as \c false, except
            when the mask's size is 0 all CPUs are \e allowed. Extra bits are
            ignored.
        */
        void setCPUAffinity(const ipl::vector<bool> &mask) { m_cpu_affinity=mask; }

        /*!
            Start in the background the (not yet running) child process as
            parameterized by all the set* methods and return its process
            identifier.

            Failure to start may result in INVALID_PROCESS_ID being returned or
            in the child exiting immediatly with any result code it deems
            appropriate. Calling this method while there is already a child
            process running is an error.

            If you have specified a callback at construction time then child
            process exit, both normal and due to errors, will be reported to it.
            If you haven't, the child process exit can be waited/polled for
            synchronously via wait().


            \errorindicator via INVALID_PROCESS_ID return

            \errors ipl::CommonError with IDs:
            - INVALID_USAGE if there is already a child process
              existing for this object.

            SysError with IDs:
            - SYSTEM_RESSOURCES_EXHAUSTED if kernel memory is
              exhausted (but a retry is possible) or if a system limit
              of maximum child processes has been hit
            - OUT_OF_MEMORY if kernel/userspace memory is exhausted

            ProcessTNG::Error with IDs:
            - START_FAILED on other system specific errors
        */
        ProcessId start();

        /*!
            \brief start() and wait()
        */
        bool startSync(ExitState &state) {
            if(start()!=INVALID_PROCESS_ID)
                return wait(state);
            return true;
        }

        /*!
            \brief Terminate the child/its whole process group if running

            On systems that support this (i.e. not Windows), if \a only_request
            is \c true the child is signalled via means it can catch, react upon
            and possibly ignore. By default the child is killed hard. In any
            case this method will \e not wait for the child to actually
            terminate.

            On POSIX \c SIGTERM and \c SIGKILL are used.

            There is an inherent race condition when killing child
            processes after checking for exit status (no matter the method),
            since it could have exited just before or
            while a call to kill() is performed.

            \see ExitState::wasKilled()

            \return \c true on error, \c false on success

            \errorindicator via return code

            \errors ProcessTNG::Error with error id:
            - KILL_FAILED on system specific errors
            - attached with a SysError with ID PERMISSION_DENIED if
              you're not allowed to kill the process
        */
        bool kill(const bool only_request=false);


        /*!
            \brief Send a kill signal to the child/its whole process group if running

            On systems that do not support this (i.e. Windows),
            a hard kill command is always sent to the child.

            On POSIX any signal can be used.

            There is an inherent race condition when killing child
            processes after checking for exit status (no matter the method),
            since it could have exited just before or
            while a call to kill() is performed.

            \see ExitState::wasKilled()

            \return \c true on error, \c false on success

            \errorindicator via return code

            \errors ProcessTNG::Error with error id:
            - KILL_FAILED on system specific errors
            - attached with a SysError with ID PERMISSION_DENIED if
              you're not allowed to send a signal to the process
        */
        bool kill( int signal );

        /*!
            \brief Terminate any process or process group by ID

            Do not use for your own child processes, use kill() instead.

            On systems that support this (i.e. not Windows), if \a only_request
            is \c true the child is signalled via means it can catch, react upon
            and possibly ignore. By default the child is killed hard. In any
            case this method will \e not wait for the child to actually
            terminate.

            On POSIX \c SIGTERM and \c SIGKILL are used.

            \return \c true on error, \c false on success

            \errorindicator via return code

            \errors ProcessTNG::Error with error id:
            - KILL_FAILED on system specific errors
            - attached with a SysError with ID PERMISSION_DENIED if
              you're not allowed to kill the process
            - ID NOT_FOUND if the given process could not be found
        */
        static bool killProcess(const ProcessId &pid, const bool only_request=false);

        /*!
            \brief Send a kill signal to any process or process group by ID

            Do not use for your own child processes, use kill() instead.

            On systems that do not support this (i.e. Windows),
            a hard kill command is always sent to the child.

            On POSIX any signal can be used.

            \return \c true on error, \c false on success

            \errorindicator via return code

            \errors ProcessTNG::Error with error id:
            - KILL_FAILED on system specific errors
            - attached with a SysError with ID PERMISSION_DENIED if
              you're not allowed to kill the process
            - ID NOT_FOUND if the given process could not be found
        */
        static bool killProcess(const ProcessId &pid, int signal);

        /*!
            \brief Return 0 if \a id corresponds to an existing process,
            <0 on error, >0 otherwise

            \errors SysError with error id:
            - PERMISSION_DENIED if the current process is not allowed to check
              the existance of the target process
            - UNKNOWN_ERROR on any other error
        */
        static int_fast8_t existsProcess(const osal::ProcessId &id);

        /*!
            Wait for the child to exit (if not exited already) or, if
            \a use_timeout is set, for \a timeout milliseconds at max,
            fill the \a state.

            On error but not on timeout, \c true is returned. You can
            distinguish exit and timeout by state.hasExited().

            This method works only once per child exiting, i.e. after you have
            collected a return code etc. once, the data is freed. Subsequent
            calls will raise ipl::CommonError(INVALID_USAGE).

            \errorindicator via return code

            \errors ipl::CommonError with IDs:
            - INVALID_USAGE if no child process is currently running or waiting
              to be joined

            ProcessTNG::Error with IDs:
            - WAIT_FAILED on system specific errors during the operation
        */
        bool wait(ExitState &state, const bool use_timeout=false,
                  const osal::TimeT timeout=0);

        /*!
            \brief The process ID of the running child or INVALID_PROCESS_ID
        */
        inline ProcessId getProcessId() const;

        /*!
            \brief Search OS for a process name and return all process IDs found

            If \a exact_match is \c false, only the basenames of running
            processes are considered.
        */
        static void getProcessId(const ipl::string &name,
                                 ipl::vector<ProcessId> &pids,
                                 bool exact_match=false);

        /*!
            \brief The process ID of \e this process
        */
        static ProcessId getOwnProcessId();

        /*!
            \brief The process name of \e this process according to the OS

            This string is platform-dependent. Usually you'll get the path to
            the executable in the filesystem. If there is no name, the empty
            string is returned.
        */
        static ipl::string getOwnProcessName();

        /*!
            \brief Turn a process name into something platform dependent

            This is really just a fancy name for appending ".exe" on Windows.
        */
        static ipl::string makeExecutableName(const ipl::string &name) { return name+ExecutableSuffix; }

        /*!
            \brief How many distinct priorities are there?

            \see osal::Thread::getNumPriorities()
        */
        static size_t getNumPriorities() { return (size_t)(getMaxPriority() - getMinPriority()); }

        /*!
            \brief The default priority for priority-enabled processes

            \see osal::Thread::getDefaultPriority()
        */
        static size_t getDefaultPriority() { return g_default_prio; }

        /*!
            \brief Are higher priorities bigger or smaller numbers?

            \see osal::Thread::getPriorityOrder()
        */
        static PriorityOrder getPriorityOrder() { return g_prio_order; }

        /*!
            \brief Smallest number usable as priority

            \see osal::Thread::getMinPriority()
        */
        static Priority getMinPriority() { return osal::Thread::getMinPriority(); }

        /*!
            \brief Biggest number usable as priority

            \see osal::Thread::getMaxPriority()
        */
        static Priority getMaxPriority() { return osal::Thread::getMaxPriority(); }

        static const ProcessId INVALID_PROCESS_ID;

    private:
        //! \brief Helper transforming a vector with args. and env.
        //! into C-POSIX-API compliant form
        class VectorTransformer;

        //! common construction code
        void init();

        //! called from osal::Osal
        static bool init(const bool lazy);

        //! called from osal::Osal
        static void exit();

        //! actually does the PD child starting part
        bool startChild();

        static void processExited(ProcessTNG *obj, const bool was_killed,
                                  const ProcessExitCode exit_code);

#ifdef USE_SPAWN_API_IN_POSIX_PROCESSTNG
        /* nothing needed */
#else  // =use fork
        static void actually_start_child(void *context);

        void store_error(bool have_error, const char *file=NULL, int line=0,
                         const ipl::ErrorType *type=NULL, ipl::ErrorInt id=-1) {
            error=have_error;
            error_file=file;
            error_line=line;
            error_type=type;
            error_id=id;
        }

        bool raise_if_error() {
            if(error)
                ipl::ErrorOutput(error_file, error_line, true)(*error_type, error_id);
            return error;
        }

        bool error;
        const char *error_file;
        int error_line;
        const ipl::ErrorType *error_type;
        ipl::ErrorInt error_id;
#endif

        bool m_has_error;

        //! \brief
        //! For asynchronous execution this holds the system's child
        //! process ID
        ProcessHandle m_handle;

        //! \brief
        //! Callback interface of the client, if registered (NULL
        //! otherwise)
        IProcessEvent *const m_cb;

        //! Whether to discard stdout of subprocess
        bool m_discard_stdout;

        //! Whether to discard stderr of subprocess
        bool m_discard_stderr;

        //! Whether to append stdout to m_stdout_redir, if set
        bool m_append_stdout;

        //! Whether to append stderr to m_stderr_redir, if set
        bool m_append_stderr;

        //! Whether to create a new process group for the child
        bool m_create_new_pg;

        //! \brief
        //! lock for accessing m_handle during racy situations like
        //! between kill() and processExited()
        osal::Mutex m_handle_lock;

        //! \brief
        //! For for synchronous wait for exit of process in wait(). This
        //! is bound to m_handle_lock.
        osal::Condition m_exit_cond;

        //! \brief
        //! Last process exit code (used for wait()), protected by
        //! m_handle_lock
        ExitState m_last_state;

        //! Priority value to be applied to newly started child
        Priority m_priority;

        //! scheduling policy and paraneter to be applied to newly started child
        osal::sched::Attr m_sched_attr;

        //! \brief
        //! The currently set processor affinity for newly started
        //! childs
        ipl::vector<bool> m_cpu_affinity;

        friend class Osal;
        friend struct ProcessImpl;
        friend void childContext(const ProcessTNG&);
    };

    class ProcessTNG::VectorTransformer {

    public:
        VectorTransformer(const ipl::string &exec_path,
                          const ipl::vector< ipl::string > &args,
                          const ipl::vector< ipl::pair< ipl::string, ipl::string > > &env):
            m_native_args(NULL), m_native_env(NULL), m_exec_path(exec_path),
            m_args(args), m_env(env) {}

        ~VectorTransformer() {
            delete[] m_native_args;
            for(size_t i=0; i<m_env.size(); i++)
                free(m_native_env[i]);
            delete[] m_native_env;
        }
        VectorTransformer(const VectorTransformer&) = delete;
        VectorTransformer& operator=(const VectorTransformer&) = delete;

        char **getArgs() {
            if( ! m_native_args ) {
                // we need plus one argument as the list of
                // arguments (also the list of environment
                // variables) needs to be terminated by a NULL
                // pointer.
                //
                // we need plus one argument for the argv[0] of
                // the new program, by convention.
                m_native_args = NULL;
                IPL_NEW(m_native_args, new(ipl::nothrow) char *[m_args.size()+2],
                        "native arguments vector");
                // first parameter needs to be the path to the
                // executable by convention we can use flat copy
                // here as the member variable stays valid for
                // the needed duration. Same goes for m_args.
                m_native_args[0]=const_cast<char *>(m_exec_path.c_str());
                for(size_t i=0; i<m_args.size(); i++)
                    m_native_args[i+1]=const_cast<char *>(m_args[i].c_str());
                // acc. to man page it needs to be a (char*)
                // NULL pointer
                m_native_args[m_args.size()+1]=NULL;
            }
            return m_native_args;
        }

        char **getEnv() {
            if(!m_native_env) {
                IPL_NEW(m_native_env, new(ipl::nothrow) char *[m_env.size()+1],
                        "native arguments vector");
                for(size_t i=0; i<m_env.size(); i++) {
                    ipl::string env_entry=m_env[i].first;
                    env_entry.append("=");
                    env_entry.append(m_env[i].second);
                    // don't take temporary string in here!
                    m_native_env[i]=::strdup(env_entry.c_str());
                }
                // acc. to man page it needs to be a (char*)
                // NULL pointer
                m_native_env[m_env.size()]=NULL;
            }
            return m_native_env;
        }

    private:
        char **m_native_args;
        char **m_native_env;

        const ipl::string &m_exec_path;
        const ipl::vector<ipl::string> &m_args;
        const ipl::vector<ipl::pair<ipl::string, ipl::string> > &m_env;
    };

}  // end of namespace osal

#ifdef IPL_OS_POSIX
#    include "posix/ProcessTNG.inl"
#elif defined (IPL_OS_WINPC)
#    include "win32/ProcessTNG.inl"
#elif defined (IPL_OS_INTEGRITY)
#    include "integrity/ProcessTNG.inl"
#else
#    error "error undefined IPL_OS_ variant"
#endif

#endif
