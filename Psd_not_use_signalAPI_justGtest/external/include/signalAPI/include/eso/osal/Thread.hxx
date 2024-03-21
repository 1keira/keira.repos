/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_THREAD_HXX
#define OSAL_THREAD_HXX

#include <common/streams/ostream.hxx>

#include <common/NonCopyable.hxx>
#include <common/Macros.hxx>
#include <common/types/vector.hxx>

//#if defined (IPL_OS_ANDROID) || defined (IPL_OS_LINUX) || defined (IPL_OS_QNX)
#ifdef IPL_OS_POSIX
#    include "posix/ThreadDefs.hxx"
#    include "posix/SchedDefs.hxx"
#elif defined (IPL_OS_WINPC)
#    include "win32/ThreadDefs.hxx"
#    include "win32/SchedDefs.hxx"
#elif defined (IPL_OS_INTEGRITY)
#    include "integrity/ThreadDefs.hxx"
#    include "integrity/SchedDefs.hxx"
#else
#    error "error undefined IPL_OS_ variant"
#endif

#include <osal/osal.hxx>
#include <osal/osal_dso.h>
#include <osal/Condition.hxx>
#include <osal/Mutex.hxx>
#include <osal/TLS.hxx>
#include <osal/sched.hxx>

namespace osal
{

/**
 * \brief
 *     Platform-independent Thread Abstraction

 *     A thread is a separate thread of execution within a process.
 *     Unlike between processes all threads within one process share a
 *     common address space. This makes communication between threads
 *     much easier and more efficient then communication between
 *     processes. On the other hand more intense synchronisation has to
 *     be performed to avoid race conditions between threads.
 *
 *     Usually a large number of threads can be created within a single
 *     process. The so called main thread is the original thread that
 *     starts its execution in the main function of a process. All
 *     other threads have to be actively created and start their
 *     execution in a user defined function.
 *
 *     Synchronisation objects typically used together with threads are
 *     mutexes and conditions. See osal::Mutex and osal::Condition
 *     classes regarding this.
 * \note
 *    This thread implementation aims only to provide quite a thin
 *    layer to abstract the underlying thread API of the OS. A more
 *    advanced class providing additional thread logic and state
 *    handling is provided in form of a separate util::Thread class
 *    based on this Thread class.
**/
class OSAL_EXPORT Thread :
    // threads should not be copied
    public ipl::NonCopyable
{
public: // types
    /**
     *\brief
     *    This type denotes all possible states a thread can be
     *    in.

     *    These are the states of the thread that are relevant for
     *    safely starting, running and stopping a thread.
     **/
    enum ThreadState
    {
        //! \brief
        //! the thread has been created by the constructor but
        //! not yet started
        CREATED,
        //! \brief
        //! the thread was created in joinable mode, is active
        //! and running in the users code
        RUNNING,
        //! \brief
        //! the thread is currently suspended as he called the
        //! suspend() member function
        SUSPENDED,
        //! \brief
        //! the thread has exited users code, not active any
        //! longer and in a joinable state
        EXITED,
        //! \brief
        //! the thread has been joined and is now officially
        //! dead
        DEAD
    };

    /**
     * \brief
     *    Possible reasons for thread exit.

     *    This enum is passed as a parameter to registered exit
     *    handlers of the Thread class.
     **/
    enum ExitReason
    {
        //! \brief
        //! the thread returned voluntarily from its threadLoop
        //! entry point.
        THREAD_RETURNED,
        //! the thread has been forcibly terminated
        THREAD_TERMINATED
    };

    //! specific thread error IDs
    enum ThreadErrors
    {
        CREATE_FAILED = 0,
        START_FAILED,
        SETPRIORITY_FAILED,
        YIELD_FAILED,
        JOIN_FAILED,
        TERMINATE_FAILED,
        SUSPEND_FAILED,
        WAKEUP_FAILED,
        REGISTER_EXIT_HANDLER_FAILED,
        SETGETAFFINITY_FAILED
    };

    //! Thread specific error type
    static ipl::ErrorType Error;

    // fwd. decl.
    class ThreadId;

    //! A type to duistingish interpretation of Priorities
    typedef osal::PriorityOrder PriorityOrder;

    // signature of a thread exit function
    typedef void (*ThreadExitFunc)(const ThreadId&, const ExitReason);

public: // inner classes

    /**
     * \brief
     *    A little helper class for storing and comparing
     *    ThreadIDs

     *    ThreadIDs should never be plainly compared but only via
     *    the according OS functions.
     **/
    class OSAL_EXPORT ThreadId
    {
        // only the Thread may change and access the primitive
        // value
        friend class Thread;
        // output operator for sanely printing thread IDs
        friend OSAL_EXPORT ipl::ostream&
            operator<<(ipl::ostream&, const ThreadId&);
    public:
        /**
         * \brief
         *     The only constructor creates an invalid thread ID
         **/
        ThreadId();

        /**
         * \brief
         *    Compare two ThreadId objects for equality. If
         *    true is returned then the ThreadIds refer to the
         *    same logical thread.
         * \param
         *    p_other The object to compare this object to.
         * \return
         *    true if both object refer to the same thread,
         *    false otherwise
         **/
        bool operator==(const ThreadId &p_other) const;

        /**
         * \brief
         *    opposite of operator==
         **/
        bool operator!=(const ThreadId &p_other) const
        {
            return !operator==(p_other);
        }

        /**
         * \brief
         *    operator "less" to make it possible to keep
         *    ThreadId objects in std containers.
         **/
        bool operator<(const ThreadId &p_other) const;

        /**
         * \brief
         *     Returns the raw integer value of the thread
         *     identifier
         **/
        OSThreadId rawId() const
        {
            return m_id;
        }
    public:
        /**
         * \brief
         *     this static object can be used for checking
         *     wheter a ThreadId is invalid or to assign an
         *     invalid value to a ThreadId object.
         **/
        static const ThreadId INVALID_THREAD_ID;
    private:
        //! \brief The primitive ThreadID of the system
        OSThreadId m_id;
    }; // end class ThreadId

    /**
     * \brief
     *    A type that is able to represent scheduling priorities
     *
     *     Generally the type is considered to be signed and
     *     integral. I.e. an int. It is also considered that
     *     priorities can be changed in steps of one. Details about
     *     can be found setPriority().
     **/
    typedef osal::Priority Priority;

    /**
     * \brief
     *    A type for the thread function.
     *
     *     A function of this is invoked in the newly created thread.
     *     It takes one parameter. The argument is passed via the thread constructor.
     **/
    typedef void (*ThreadFct)(void*);

public: // member functions
    /**
     * \brief
     *    Creates an osal::Thread object which represents the thread.
     *
     *    The new thread will execute the passed thread function with the passed argument.
     *    <br>The thread is not running after the constructor, see start().
     *    <br>The thread is unnamed and joinable. The os may associate some name with the thread.
     * \param[in]
     *    f The function that will be invoked after start() is called.
     * \param[in]
     *    arg the argument passed to the thread funtion \p f.
     **/
    Thread( ThreadFct f, void* arg);

    /**
     * \brief
     *    Creates an osal::Thread object which represents the thread.
     *
     *    The new thread will execute the passed thread function with the passed argument.
     *    <br>The thread is not running after the constructor, see start().
     *    <br>The thread is named.
     *    <br>The thread is joinable.
     * \param[in]
     *    f The function that will be invoked after start() is called.
     * \param[in]
     *    arg the argument passed to the thread funtion \p f.
     * \param[in]
     *    name An optional friendly name for the new thread.
     *    <br>The OS may abbreviate the name in some way or not use the passed
     *    name at all.
     *    <br>NULL is a valid value. The argument is copied and may be destroyed after
     *    the constructor returns.
     **/
    Thread( ThreadFct f, void* p_argument, const char* const name);

    /**
     * \brief
     *    Creates an osal::Thread object which represents the thread.
     *
     *    The new thread will execute the passed thread function with the passed argument.
     *    <br>The thread is not running after the constructor, see start().
     *    <br>The thread is named.
     *    <br>The thread's joinable state depends on the detached parameter.
     *    <br>A priority can be passed.
     *    <br>
     *    The OS may have a concept of scheduling policy which can not be passed via this
     *    constructor - see the constructor that takes policy and associated scheduling parameters.
     *    <br>
     *    If the priority can not be set due to inadequate permissions the thread will fall back to
     *    inheriting scheduling attributes from the calling thread.
     * \param[in]
     *    f The function that will be invoked after start() is called.
     * \param[in]
     *    arg the argument passed to the thread funtion \p f.
     * \param[in]
     *    name An optional friendly name for the new thread.
     *    The OS may abbreviate the name in some way or not use the passed
     *    name at all.
     *    NULL is a valid value. The argument is copied and may be destroyed after
     *    the constructor returns.
     * \param[in]
     *    set_priority If set to true then the argument \p priority will be used.
     * \param[in]
     *    priority If \p set_priority is set to true this value will be used.
     *    The interpretation depends on the scheduling policy of the calling thread.
     *    <br>
     *    On QNX the priority will be used as the static priority of the POSIX
     *    RR or FIFO policies.
     *    <br>
     *    On Linux kernels the value will be used as the static priority of the RR and FIFO policies,
     *    for the OTHER (CFS/default scheduler) policy it will be interpreted as the nice value.
     *    <br>
     *    On Windows the value will be used as the thread priority.
     *    <br>
     *    On Integrity it will be used as the priority.
     * \param[in]
     *    stacksize The size of the stack that is available to
     *    the new thread, in bytes. The default is zero which
     *    means that the system default stack size applies.
     * \param[in]
     *    detached If set to \c true then the thread will be
     *    created in detached mode.
     *    <br>This means that no join operation can be performed on the resulting thread to
     *    collect the thread exit state.
     *    <br>The default is to be not detached (joinable).
     *    <br>For detached threads the lifecycle model applied by
     *    osal::Thread is different. The states EXITED and DEAD
     *    will never be reached. The last known state will be
     *    RUNNING.
     * \post
     *    The thread object will be in state CREATED.
     * \errorindicator
     *    via isValid()
     * \errors
     *    Thread::Error with reason CREATE_FAILED attached with
     *    an:
     *
     *    * ipl::CommonError with IDs:
     *    - INT_OUT_OF_RANGE if stacksize is too low or too high
     *
     *    * osal::SysError with IDs:
     *    - OUT_OF_MEMORY if not enough memory to allocate
     *    associated ressources
     *    - PERMISSION_DENIED if the requested scheduling
     *    parameters are not allowed for the caller
     *    - SYSTEM_RESSOURCES_EXHAUSTED if ressources other then
     *    memory are lacking to create the thread (thus a retry is
     *    possible) Thread::Error with IDs:
     *    - CREATE_FAILED on other, unclassified errors during
     *    creation
     **/

    Thread(
        ThreadFct f,
        void* arg,
        const char* const name,
        const bool set_priority,
        const Priority priority = 0,
        const uint32_t stacksize = 0,
        const bool detached = false);

    /**
     * \brief
     *    Creates an osal::Thread object which represents the thread.
     *
     *    The new thread will execute the passed thread function with the passed argument.
     *    <br>The thread is not running after the constructor, see start().
     *    <br>The thread is named.
     *    <br>Scheduling attributes are passed in \p sched_policy and \p sched_param.
     *    <br>The thread's joinable state depends on the detached parameter.
     * \param[in]
     *    f The function that will be invoked after start() is called.
     * \param[in]
     *    arg the argument passed to the thread funtion \p f.
     * \param[in]
     *    name An optional friendly name for the new thread.
     *    The OS may abbreviate the name in some way or not use the passed
     *    name at all.
     *    NULL is a valid value. The argument is copied and may be destroyed after
     *    the constructor returns.
     * \param[in]
     *    sched_attr The scheduling attributes for the new thread. See osal::sched::Attr for details.
     * \param[in]
     *    detached If set to \c true then the thread will be
     *    created in detached mode.
     *    <br>This means that no join operation can be performed on the resulting thread to
     *    collect the thread exit state.
     *    <br>The default is to be not detached (joinable).
     *    <br>For detached threads the lifecycle model applied by
     *    osal::Thread is different. The states EXITED and DEAD
     *    will never be reached. The last known state will be
     *    RUNNING.
     * \post
     *    The thread object will be in state CREATED.
     * \errorindicator
     *    via isValid()
     * \errors
     *    Thread::Error with reason CREATE_FAILED attached with
     *    an:
     *
     *    * ipl::CommonError with IDs:
     *    - INT_OUT_OF_RANGE if stacksize is too low or too high
     *
     *    * osal::SysError with IDs:
     *    - OUT_OF_MEMORY if not enough memory to allocate
     *    associated ressources
     *    - PERMISSION_DENIED if the requested scheduling
     *    parameters are not allowed for the caller
     *    - SYSTEM_RESSOURCES_EXHAUSTED if ressources other then
     *    memory are lacking to create the thread (thus a retry is
     *    possible) Thread::Error with IDs:
     *    - CREATE_FAILED on other, unclassified errors during
     *    creation
     * \note
     * In POSIX the nice value is a process property. On Linux the nice value is applied per thread though.
     * <br>The priority class on Windows is a process property thus setting it for a thread will still
     * affect the whole process.
     **/
    Thread(
        ThreadFct f, void* arg, const char* const name,
        const sched::Attr& sched_attr,
        const bool detached = false
        );

    /**
     * \brief
     *     Cleanup associated thread ressources
     *
     *    The destructor will make sure that the thread is in a
     *    sane state. If the thread is in state CREATED and thus
     *    has never been started then it will be shut down by the
     *    Thread class without it ever entering the user supplied
     *    thread entry function.
     *    <br>
     *    If the thread is in state EXITED i.e. not yet joined
     *    then it will be joined by the destructor. If the thread
     *    is in state RUNNING or SUSPENDED, however, then a
     *    negative assertion will be issued. An exception to this
     *    is made for detached threads which can never reach the
     *    EXITED or DEAD state.
     *    <br>
     *    If the thread is already in DEAD state then nothing will
     *    be done except cleaning up the member variables.
     **/
    virtual ~Thread();

    /**
     * \brief
     *    Return the state the thread is currently in
     * \return
     *    The currently active thread state.
     * \note
     *    The thread state retrieved here is only a snapshot and
     *    it may change any time.
     **/
    ThreadState getThreadState() const
    {
        // I make no new error handling here for now. Would mess
        // up the API completely.
        ThreadState ret;
        bool error = false;
        error |= m_state_lock.lock();
        ret = m_thread_state;
        error |= m_state_lock.unlock();

        IPL_ASSERT( ! error );

        return ret;
    }

    /**
     * \brief
     *    Starts the thread.
     *
     *    After construction only the call to this member function
     *    will make the thread actually calling the provided entry
     *    function.
     *    <br>
     *    Note that the actual entry of the thread in the entry
     *    function heavily depends on scheduling. It may very well
     *    be that start() has returned long before the thread is
     *    running. Also it might be possible that the entry
     *    function has already been left again by the thread upon
     *    return of start() and thus the thread state changed to
     *    EXITED.
     * \note
     *    Starting a thread a second time is not supported. You
     *    need to create a new Thread object for this purpose.
     * \pre
     *    The thread object needs to be in state CREATED
     * \post
     *    The thread object is in state RUNNING (may immediatly
     *    change again - dependent on thread logic e.g. if the
     *    thread goes to sleep soon by calling suspend())
     * \return
     *    true on error, false on success
     * \errorindicator
     *    via return code
     * \errors
     *    ipl::CommonErrror with IDs:
     *
     *    - INVALID_USAGE if start is called more than once or in
     *    an invalid state
     *
     *    Thread::Error with IDs:
     *
     *    - START_FAILED if a related operation failed
     **/
    bool start();

    /**
     * \brief
     *    Force termination of a running thread
     *
     *    This function causes a thread in state RUNNING or
     *    SUSPENDED to be terminated ungracefully. This is only to
     *    be done in emergency cases e.g. when the thread isn't
     *    reacting any more to userspace level stop requests.
     *
     *    If a thread is terminated then several system objects
     *    like mutexes, conditions and many more will be in an
     *    undefined state. Thus terminating a thread is a last
     *    measure action. After a thread termination the process
     *    should be restarted or shutdown soon.
     * \warning
     *    Don't use this function. Except you have a very good
     *    reason.
     *
     *    For example, if the terminated thread was inside a
     *    standard library call involving any static or global
     *    variables then other threads using those calls may run
     *    into Nirvana.
     * \pre
     *    The thread object must be in state RUNNING.
     * \post
     *    After this function returns the thread state will be
     *    DEAD.
     * \return
     *    true on error, false on success
     * \errorindicator
     *    via return code
     * \errors
     *    ipl::CommonError with IDs:
     *
     *    - INVALID_USAGE if the thread state was not RUNNING.
     *
     *    Thread::Error with IDs:
     *
     *    - TERMINATE_FAILED if an operation regarding termination
     *    failed.
     **/
    bool terminate();

    /**
     * \brief
     *    Return the friendly name of the thread that was
     *    specified at construction time.
     * \warning
     *    If no name was specified then this function will return
     *    NULL.
     * \return
     *    The friendly name of the thread, if present. NULL
     *    otherwise.
     **/
    const char* getFriendlyName() const
    { return m_friendly_name; }

    /**
     * \brief
     *    Wait for the thread to exit and cleanup any system
     *    ressources associated with it
     *
     *    If the thread is in state RUNNING then join blocks until
     *    the thread reaches state EXITED. When the thread reached
     *    the EXITED state then all ressources associated with the
     *    thread will be cleaned up and join will return.
     *    <br>After join returns the state of the thread is DEAD.
     *
     *    If the thread is in state CREATED or DEAD when join is
     *    called then an error will be raised.
     *
     *    If the thread is in state SUSPENDED when join is called
     *    then wakeup() will be called before the join operation
     *    is performed.
     * \pre
     *    Thread is in state RUNNING, SUSPENDED or EXITED.
     * \post
     *    Thread is in state DEAD.
     * \return
     *    true on error, false otherwise
     * \errorindicator
     *    via return code
     * \errors
     *    ipl::CommonError with IDs:
     *
     *    - INVALID_USAGE if the Thread is in an invalid state or
     *    if the calling thread is also the thread to be joined
     *    (join on self). This error is also raised in cause the
     *    Thread was created in "detached" mode. A detached thread
     *    cannot be joined any more even if you would like to.
     *
     *    Thread::Error with IDs:
     *
     *    - JOIN_FAILED on other errors
     **/
    bool join();

    /**
     * \brief
     *     Does the same as join with added timeout handling.
     *
     *     This variant of join can be used to poll for the
     *     possibility to join or to put an upper limit
     *     on the join operation.
     *
     *     \c p_max_wait_ms determines the maximum number of
     *     milliseconds to wait for the thread to enter a joinable
     *     state. If \c p_max_wait_ms is zero then it is immediatly
     *     checked whether the thread can be joined and if not so,
     *     the call returns with timeout indication without
     *     entering a blocking state at all.
     * \note
     *     On QNX with qnx version >= 6.5.0 this function's
     *     timeout is based on CLOCK_MONOTONIC and therefore not
     *     affected by realtime clock changes. On all other
     *     configurations the timeout is based on CLOCK_REALTIME
     *     and thus affected by realtime clock changes.
     * \return
     *     - zero on successful join with the thread
     *     - > 0 if joining was not possible within the given time
     *     constraint
     *     - < 0 if an error as described at join() occured.
     **/
    int joinTimeout(const osal::TimeT &p_max_wait_ms);

    /**
     * \brief
     *    Return the thread ID of the thread associated with this
     *    object
     * \return
     *    ThreadId object containing the ThreadId associated with
     *    this Thread object.
     * \errors
     *    none
     **/
    ThreadId getThreadId() const;


    /**
     * \brief
     *    Returns the priority of the thread represented by this osal::Thread instance.
     *
     * For the osal::sched::OSAL_SCHED_POLICY_NORMAL on Linux policy this returns the thread's nice value
     * and not the static priority 0.
     **/
    Priority getPriority() const;

    /**
     * \brief
     *    Returns the scheduling attributes of the thread represented by this osal::Thread instance.
     *
     *    If the OS has no concept of scheduling policy, \p attr.policy is set to \a osal::sched::OSAL_SCHED_NOOP.
     *    <br>If the policy has no paramters, attr.param is not changed.
     *    If an error occurs, true is returned and policy set to osal::sched::OSAL_SCHED_NOOP.
     * \param[out]
     *    attr scheduling attributes of the thread.
     * \errors
     *    Thread::Error with IDs
     *
     *    - SETPRIORITY_FAILED if an operation regarding getting/setting
     *    the priority failed.
     **/
    bool getSchedAttrs(osal::sched::Attr& attr) const;

    /**
     * \brief
     *    Returns the scheduling attributes of the calling thread.
     *
     *    If the OS has no concept of scheduling policy, \p attr.policy is set to \a osal::sched::OSAL_SCHED_NOOP.
     *    <br>If the policy has no paramters, attr.param is not changed.
     *    If an error occurs, true is returned and policy set to osal::sched::OSAL_SCHED_NOOP.
     * \param[out]
     *    attr scheduling attributes of the thread.
     * \errors
     *    Thread::Error with IDs
     *
     *    - SETPRIORITY_FAILED if an operation regarding getting/setting
     *    the priority failed.
     **/
    static bool getCallerSchedAttrs(osal::sched::Attr& attr);

    /**
     * \brief
     *    Changes the priority of the running thread.
     *
     *    A call to this function is only valid if the state of
     *    the thread object is CREATED, RUNNING or SUSPENDED. In
     *    other states there will be no effect.
     *    <br>
     *    On Linux - if the thread has the osal::sched::OSAL_SCHED_POLICY_NORMAL policy -
     *    this call will change the nice value of the thread.
     * \param
     *    p_priority The new priority value.
     * \return
     *    true on error, false on success
     * \errorindicator
     *    via return code
     * \errors
     *    Thread::Error with IDs
     *
     *    - SETPRIORITY_FAILED if an operation regarding getting/setting
     *    the priority failed.
     **/
    bool setPriority(const Priority p_priority);

    /**
     * \brief
     *    Changes the scheduling attributes of the thread represented by this osal::Thread instance.
     *
     *    A call to this function is only valid if the state of
     *    the thread object is CREATED, RUNNING or SUSPENDED. In
     *    other states there will be no effect.
     * \param
     *    attr The scheduling policy and attributes.
     * \return
     *    true on error, false on success
     * \errorindicator
     *    via return code
     * \errors
     *    Thread::Error with IDs
     *
     *    - SETPRIORITY_FAILED if an operation regarding getting/setting
     *    the priority failed.
     *
     * \note
     *    Setting a nice value on Linux will only affect this thread, not the whole process.
     *    <br>Setting a priority class (via policy) on Windows will affect the whole process, not
     *    only one thread.
     *    <br>These 'limitations' are due to system behavior:
     *    <br>the nice value is a thread attribute on Linux (while in POSIX
     *    it is defined as a per process attribute),
     *    <br>the priority class is a process attribute on Windows.
     **/
    bool setSchedAttrs(const osal::sched::Attr& attr);

    /**
      \brief Sets the CPU affinity mask.

      Each element in \a mask corresponds to a CPU. If it is \c false,
      the corresponding CPU is not used by this thread (if the system
      supports this). When the \a mask is all-\c false with a size greater than 0,
      the call does nothing.
      Setting the cpu affinity mask may trigger a thread migration.

      If there are fewer elements in \a mask than there are CPUs all missing elements
      are treated as \c false except when the size of \a mask is 0 then all CPUs are \e allowed.

      If there are more elements in \a mask than there are CPUs the extra elements are
      ignored.

      If you are building for a posix system that doesn't support pthread_setaffinity_np, either
      make sure that the thread started running, or check afterwards via getCPUAffinity(),
      otherwise this call may fail silently.

      If the call fails, true is returned and an error is raised, false is returned on success.
      **/
    bool setCPUAffinity(const ipl::vector<bool> &mask);

    /**
      \brief Returns the CPU affinity mask.

      Each element in \a mask corresponds to a CPU. If it is \c false,
      the corresponding CPU is not used by this thread, if it is \c true may be used by this
      thread.

      \{
    **/
    bool getCPUAffinity(ipl::vector<bool> &mask);
    static bool getCallerCPUAffinity(ipl::vector<bool> &mask);
    /*! \} */

    /**
     * \brief
     *    Suspend the execution of the calling thread for the
     *    given number of milliseconds or until another thread
     *    calls wakeup().
     *
     *    This call is _only_ valid for the thread that is
     *    associated with this Thread object. If a different
     *    thread is calling this method then an error will be
     *    raised.
     *    <br>
     *    If you just want to plainly sleep for a certain amount
     *    of time without the possibility of interruption then
     *    please use osal::Time::sleep().
     * \param[in]
     *    p_duration_ms If greater than zero then the calling
     *    thread will be suspended at max for the given number of
     *    milliseconds or shorter if another thread calls wakeup()
     *    on this object. If this equals zero then the calling
     *    thread will be suspended infinitely until some other
     *    thread calls wakeup().
     * \return
     *    true on error, false on success
     * \errorindicator
     *    via return code
     * \errors
     *    ipl::CommonError with IDs:
     *
     *    - INVALID_USAGE if the calling thread is not the thread
     *    associated with this object
     *
     *    Thread::Error with IDs:
     *
     *    - SUSPEND_FAILED if an operation regarding suspend
     *    failed
     **/
    bool suspend(const osal::TimeT p_duration_ms);

    /**
     * \brief
     *    Wakeup the thread if it is currently is SUSPENDED state.
     *    If not then this call has no effect.
     *
     *    A call to this method may wake up a thread that call
     *    suspend() before the sleep duration passed or if a
     *    thread called suspend() with zero as an argument.
     * \return
     *    true on error, false on success
     * \errorindicator
     *    via return code
     * \errors
     *    Thread::Error with IDs:
     *
     *    - WAKEUP_FAILED if an operation regarding wakeup failed
     **/
    bool wakeup();

    //! whether the object was successfully constructed
    bool isValid() const
    { return m_valid; }
public: // static functions

    /**
     * \brief
     *    Yield execution of the calling thread.
     *
     *    A call to this function will yield execution of the
     *    calling thread and give other threads or processes in
     *    the system the opportunity to run. Usually the calling
     *    thread will be reenlisted in the scheduler in the back
     *    of the queue of processes to run.
     *    <br>
     *    It may happen, if the calling thread has the highest
     *    priority in the system that it will gain execution
     *    immediatly again.
     * \return
     *    true on error, false on success
     * \errorindicator
     *    via return code
     * \errors
     *    Thread::Error with ID YIELD_FAILED if the operation
     *    couldn't be performed.
     **/
    static bool yield();


    /**
     * \brief
     *     Returns the minimum priority value for the scheduling policy of the caller's thread.
     * \note
     *     Lower priority values need not to be lower scheduling
     *     priorities. It might also be that lower values mean
     *     higher priorities. Check getPriorityOrder() to determine
     *     this.
     * \errors
     *    none
     **/
    static Priority getMinPriority();

    /**
     * \brief
     *     Returns the maximum priority value for the scheduling policy of the caller's thread.
     * \note
     *     Higher priority values need not to be higher scheduling
     *     priorities. It might also be that higher values mean
     *     lower priorities. Check getPriorityOrder() to determine
     *     this.
     * \errors
     *    none
     **/
    static Priority getMaxPriority();

    /**
     * \brief
     *     Returns the default priority.
     *
     *     The default priority for threads is an OSAL compile-time
     *     constant which is OS and target specific.
     *     It is the priority most threads should use.
     **/
    static Priority getDefaultPriority()
    {
        return g_default_prio;
    }

    /**
     * \brief
     *     Returns the priority of the calling thread.
     **/
    inline static Priority getCallerPriority();

    /**
     * \brief
     *     Returns the number of different thread priorities
     *     available for use at setPriority().
     *
     *     This information is calculated using getMinPriority()
     *     and getMaxPriority(). It is only a convenience function.
     **/
    static size_t getNumPriorities()
    {
        return (size_t)(getMaxPriority() - getMinPriority());
    }

    /**
     * \brief
     *     Returns the priority order for the current system
     *
     *     The priority order determines whether higher priority
     *     values represent higher scheduling priorities or vice
     *     versa.
     *
     *     On WinCE the priority order is DECREASING. On all
     *     other OSs it is INCREASING.
     **/
    static PriorityOrder getPriorityOrder()
    {
        return g_prio_order;
    }

    /**
     * \brief
     *    Returns the thread ID of the main thread.
     *
     *    The main thread is always present. Its ID will be set
     *    from the osal::Osal init object.
     * \note
     *    As hinted above this function actually returns the ThreadId of the thread that
     *    invoked the osal::Osal constructor, not necessarily the ThreadId of the main
     *    thread.
     * \errors
     *    none
     **/
    static ThreadId getMainThreadId()
    { return s_main_thread_id; }

    /**
     * \brief
     *    Return the thread ID of the calling thread
     * \return
     *    ThreadId object containing the ThreadId that belongs to
     *    the caller of this function.
     * \errors
     *    none
     **/
    static ThreadId getCallerThreadId();

    /**
     * \brief
     *    Return the scheduling attributes in effect at Osal construction.
     *
     * \return
     *    The scheduling attributes.
     * \errors
     *    none
     **/
    static sched::Attr getMainSchedAttrs();

    /**
     * \brief
     *    Register a callback function to be called at thread exit
     *    time of the calling thread.
     * \param[in]
     *    p_exit_cb The pointer to the callback function to be
     *    called at exit time of the thread. The provided
     *    parameters will contain the ThreadId of the thread that
     *    exited and the reason for thread exit.
     *
     *    If the exit reason is THREAD_RETURNED then the callback
     *    will be done still in the context of the returning
     *    thread. If the reason is THREAD_TERMINATED then the
     *    callback will be done in the context of some other
     *    thread.
     * \warning
     *    This functionality is only available for threads that
     *    have been created via this class.
     * \note
     *    This functionality can be used for e.g. cleaning up
     *    per-thread allocated heap memory under certain
     *    circumstances.
     *
     *    This only allows to set an exit handler for the calling
     *    thread not for a different thread.
     *
     *    Beware that when this callback is performed the thread
     *    might still be present from an OS point of view.
     *
     *    If you register an exit handler for the main thread then
     *    it will be called as soon as OSAL is deinitialized. The main
     *    thread is thus considered to be the thread that initialized
     *    OSAL by convention.
     * \return
     *    true on error, false on success
     * \errorindicator
     *    via return code
     * \errors
     *    ipl::CommonError with IDs:
     *
     *    - INVALID_USAGE if a thread called this function that
     *    wasn't started via this class.
     *
     *    SystemError with IDs:
     *
     *    - SYSTEM_RESSOURCES_EXHAUSTED if no more exit handlers
     *    can be registered for the calling thread.
     **/
    static bool registerExitHandler( ThreadExitFunc p_exit_cb );
protected: // functions
private: // functions
    //! called internally to prepare a joing system call
    bool prepareJoin();

    //! called internally to mark a thread joined
    bool markJoined();

    /**
     * \brief
     *    This is an internal thread wrapping function.
     *
     *    This is the OS dependent entry point for the thread that
     *    will be levered to the corresponding user supplied,
     *    abstract entry function with the correct argument. This
     *    function has to be static as no member functions can be
     *    called by a thread directly.
     *    <br>
     *    For now the signature of this function is luckily the
     *    same on all platforms.
     *    <br>
     *    This wrapper also has the duty to exit the thread
     *    correctly after the user supplied function ends and to
     *    reflect the state change accordingly.
     * \param[in]
     *    p_osalthread This argument will contain a ptr. to the
     *    Thread object instance that created the thread. This
     *    allows the new thread to access its related member
     *    variables.
     * \return
     *    A data item can be returned that can be accessed from
     *    other threads after thread termination. This is not used
     *    currently.
     **/
    static void* threadWrapper(void* p_osalthread);

    /**
     * \brief
     *    this function is called from the osal::Osal init object
     *    thread.
     * \return
     *    true on error, false on success
     * \errorindicator
     *    via return code
     * \errors
     *    Thread::Error with IDs:
     *
     *    - SETPRIORITY_FAILED if getting/setting thread priority
     *    information failed.
     **/
    static bool init();

    /**
     * \brief
     *    This method is called by osal_exit to make the exit
     *    handlers for the main thread being executed
     **/
    static void mainThreadExiting();

    /**
     * \brief
     *    Calls all exit handlers with the given reason and thread ID
     * \errors
     *    none
     **/
    void callExitHandlers(const ThreadId &p_who, const ExitReason p_why);

    bool initialize(void* arg, const char* const name, uint32_t stacksize
                    ,const sched::Attr& sched_att);

public: // constants
    //! maximum number of exit handlers that may be registered.
    static const uint_fast16_t MAX_EXIT_HANDLERS = 4;

protected: // members
    //! a condition that allows the thread to wait for something interesting
    osal::Condition m_wakeup;

    //! accompanying lock for m_wakeup
    osal::Mutex m_state_lock;

#ifdef IPL_OS_INTEGRITY
    //! a condition that allows the thread to wait for exiting
    osal::Condition m_exited;
#endif

private: // members
    //! whether construction succeeded
    bool m_valid;

    //! the OS specific handle for the thread
    ThreadHandle m_thread_handle;

    //! the friendly name of the thread (can be NULL!)
    char *m_friendly_name;

    //! the user entry function for the thread
    void (*m_thread_fct)(void*);

    //! the user supplied thread argument
    void* m_thread_argument;

    //! the state the thread is currently in
    ThreadState m_thread_state;

    //! the currently set priority for the thread
    Priority m_priority;

    //! whether the thread was constructed in detached mode
    const bool m_detached_mode;

    //! \brief
    //! if m_detached_mode is \c true then this indicated the child
    //! thread has detached
    bool m_thread_detached;

    //! \brief
    //! the osal::Osal init object will set the ID of the main
    //! thread here
    static ThreadId s_main_thread_id;

    //! an array of MAX_EXIT_HANDLERS callback functions that can be
    //! registered as exit handlers
    void* m_exit_handlers[MAX_EXIT_HANDLERS];

    //! same as above but for the main thread that doesn't own a
    //! Thread object itself
    static void* s_main_exit_handlers[MAX_EXIT_HANDLERS];
    static osal::Mutex s_state_lock;

    // friendships
    friend class Osal;
}; // end class

/**
 * \brief
 *    global output operator for thread IDs
 **/
OSAL_EXPORT ipl::ostream& operator<<(ipl::ostream &p_stream,
    const Thread::ThreadId &p_thread_id);

} // end namespace

//#if defined (IPL_OS_ANDROID) || defined (IPL_OS_LINUX) || defined (IPL_OS_QNX)
#ifdef IPL_OS_POSIX
#    include "posix/Thread.inl"
#elif defined (IPL_OS_WINPC)
#    include "win32/Thread.inl"
#elif defined (IPL_OS_INTEGRITY)
#    include "integrity/Thread.inl"
#else
#    error "error undefined IPL_OS_ variant"
#endif

#endif // OSAL_THREAD_HXX
