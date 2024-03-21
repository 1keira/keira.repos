/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_THREAD_HXX
#define UTIL_THREAD_HXX

#include <ipl_config.h>

#include <util/util_dso.h>
#include <common/Macros.hxx>
#include <osal/Thread.hxx>

#include <osal/Mutex.hxx>
#include <osal/SysError.hxx>
#include <util/MutexGuard.hxx>
#include <util/IRunnable.hxx>
#include <util/PlainThread.hxx>

namespace util
{

class Thread;

// our typical runnable taking a pointer to util::Thread as parameter
typedef IRunnableT<const util::Thread* const> IRunnable;

/**
 *  \brief
 *     Thread specialization that implements a cooperative threading
 *     scheme
 *
 *      This thread type introduces cooperative threading by means a
 *      thread working loop that is managed via request states set at
 *      the Thread object.
 *
 *      The additional thread state handling allows to cooperatively
 *      request from the associated thread to enter a PAUSE state or to
 *      request the thread to return from it's entry function such that
 *      it can be joined.
 *
 *      The thread entry point IRunnable is parametrized to get passed a
 *      pointer to its associated util::Thread object. This allows the
 *      thread to access the associate request state handling in any
 *      case. The pointer can also be used to distuingish different
 *      threads that use the entry point.
 *
 *     This thread type is also used in more complex facilities like
 *     util::ThreadPool to perform its tasks.
**/
class UTIL_EXPORT Thread :
    public util::PlainThread<const util::Thread* const>
{
public: // types
    /**
     * \brief
     *    This enum defines certain requests that can be issued
     *    for the associated thread.
     *
     *    As threads cannot be forcibly killed in a clean way the
     *    custom thread logic needs to ensure that the thread does
     *    react correctly to certain requests from other threads
     *    in the system. To prevent individual state handling in
     *    every thread, application or module this class provides
     *    a common way of handling typical requests i.e. causing a
     *    thread to pause its operation until it is waked up later
     *    on and stopping thread execution completely by returning
     *    from the thread entry function.
     *
     *    Every thread started by this class should thus be
     *    implemented similar to this:
     *
     *    void threadLoop(const util::Thread* const obj)
     *    {
     *        while( obj->getRequestedState() != STOP_REQUESTED )
     *        {
     *            // this, of course is optional
     *            if( obj->getRequestedState() == PAUSE_REQUESTED )
     *            {
     *                // this returns whenever an external thread
     *                // changes the state to NORMAL_OPERATION again
     *                m_thread_ctrl.enterPause();
     *
     *                continue;
     *            }
     *
     *            // do your job
     *        }
     *
     *         // upon STOP_REQUESTED we return
     *        return;
     *    }
     **/
    enum RequestState
    {
        NORMAL_OPERATION,
        PAUSE_REQUESTED,
        STOP_REQUESTED
    };

public: // member functions
    /**
     * \brief
     *    Creates a util::Thread object which represents the thread.
     *
     *    Constructs a thread that will run the threadLoop()
     *    function of the given \p runnable.
     *    <br>The thread is unnamed. The OS might still associate a name with the thread.
     *    <br>The thread is joinable.
     *    <br>The thread runs with the default scheduling attributes for the given platform.
     *
     * \param[in]
     *    runnable The IRunnable instance that is to be used
     *    as entry point for the new thread.
     * \errorindicator
     *    via isValid()
     * \errors
     *    see osal::Thread()
     **/
    Thread( IRunnable* const runnable) IPL_NOEXCEPT;

    /**
     * \brief
     *    Creates a util::Thread object which represents the thread.
     *
     *    Constructs a thread that will run the threadLoop()
     *    function of the given \p runnable.
     *    <br>The thread is named.
     *    <br>The thread is joinable.
     *    <br>The thread runs with the default scheduling attributes for the given platform.
     *
     * \param[in]
     *    runnable The IRunnable instance that is to be used
     *    as entry point for the new thread.
     * \param[in]
     *    name An friendly name for the thread.
     *    NULL is a valid value. The argument is copied and may be destroyed after
     *    the constructor returns.
     * \errorindicator
     *    via isValid()
     * \errors
     *    see osal::Thread()
     **/
    Thread( IRunnable* const runnable, const char* const name) IPL_NOEXCEPT;

    /**
     * \brief
     *    Creates a util::Thread object which represents the thread.
     *
     *    Constructs a thread that will run the threadLoop()
     *    function of the given \p runnable.
     *    <br>The thread is named.
     *    <br>The thread is joinable.
     *    <br>The thread runs with the passed priority if \p set_priority is true.
     *    The scheduling policy is inherited from the calling thread.
     *
     * \param[in]
     *    runnable The IRunnable instance that is to be used
     *     as entry point for the new thread.
     * \param[in]
     *    name An friendly name for the thread.
     *    NULL is a valid value. The argument is copied and may be destroyed after
     *    the constructor returns.
     * \param[in]
     *    set_priority If set to \c true then an paraemeter \p priority
     *    will be used.
     * \param[in]
     *    priority The priority for the new thread. Only used if
     *    \p set_priority is \c true. See osal::Thread(osal::ThreadFct, void*, const bool, const uint32_t, const bool)
     *    for details.
     * \errorindicator
     *    via isValid()
     * \errors
     *    see osal::Thread()
     **/
    Thread( IRunnable* const runnable, const char* const name
            ,const bool set_priority, const osal::Priority priority = 0 ) IPL_NOEXCEPT;

    /**
     * \brief
     *    Creates a util::Thread object which represents the thread.
     *
     *    Constructs a thread that will run the threadLoop()
     *    function of the given \p runnable.
     *    <br>The thread is named.
     *    <br>The thread is joinable.
     *    <br>The thread runs with the passed priority if \p set_priority is true.
     *    The scheduling policy is inherited from the calling thread.
     *
     * \param[in]
     *    runnable The IRunnable instance that is to be used
     *    as entry point for the new thread.
     * \param[in]
     *    name An friendly name for the thread.
     *    NULL is a valid value. The argument is copied and may be destroyed after
     *    the constructor returns.
     * \param[in]
     *    sched_attr The scheduling attributes for the new thread. See
     *    osal::Thread(ThreadFct, void*, const char* const, const osal::sched::Attr&, const bool)
     *    for details.
     * \errorindicator
     *    via isValid()
     * \errors
     *    see osal::Thread()
     **/
    Thread( IRunnable* const runnable, const char* const name
            ,const osal::sched::Attr& sched_attr) IPL_NOEXCEPT;

    /**
     * \brief
     *    Destroy the Thread object. In principle the same rules
     *    as to osal::~Thread() apply here.
     **/
    virtual ~Thread() IPL_NOEXCEPT { };

    /**
     * \brief
     *    return the state the thread is currently requested to be in
     * \note
     *    The initial requested state is NORMAL_OPERATION
     * \return
     *    the state the thread is currently requested to be in
     **/
    RequestState getRequestedState() const IPL_NOEXCEPT
    {
        util::MutexGuard g(m_req_lock);
        IPL_ASSERT( static_cast<bool>(g) == true );
        return m_requested_state;
    }

    //! \brief
    //! shorthand to check whether NORMAL_OPERATION is currently
    //! requested
    bool normalOperation() const IPL_NOEXCEPT
    {
        return getRequestedState() == NORMAL_OPERATION;
    }

    //! \brief
    //! shorthand to check whether STOP is currently requested
    bool stopRequested() const IPL_NOEXCEPT
    {
        return getRequestedState() == STOP_REQUESTED;
    }

    //! \brief
    //! shorthand to check whether PAUSE is currently requested
    bool pauseRequested() const IPL_NOEXCEPT
    {
        return getRequestedState() == PAUSE_REQUESTED;
    }

    /**
     * \brief
     *    request a new state for the associated thread
     *
     *    If the new requested state is NORMAL_OPERATION or
     *    STOP_REQUESTED then the thread will be woken up if in
     *    thread state SUSPENDED. A change of the requested thread
     *    state may make a parallel, pending call to
     *    waitUntilPaused() return.
     * \param[in]
     *    p_new_state The new state the thread is requested to be
     *    in
     * \pre
     *    The thread must be started before a state change is
     *    requested. Otherwise an error is raised and true
     *    returned.
     * \warning
     *    When you're using the cooperative API from util::Thread
     *    then you shouldn't in parallel access the raw wakeup()
     *    function of osal::Thread.
     * \return
     *    true on error, false on success
     * \errorindicator
     *    via return code
     * \errors
     *    ipl::CommonError with IDs:
     *
     *    - INVALID_USAGE if the Thread is still in state CREATED
     **/
    bool requestStateChange(const RequestState p_new_state) IPL_NOEXCEPT;

    //! calls requestStatechange with STOP_REQUESTED
    bool requestStop() IPL_NOEXCEPT
    {
        return this->requestStateChange(STOP_REQUESTED);
    }

    //! calls requestStatechange with PAUSE_REQUESTED
    bool requestPause() IPL_NOEXCEPT
    {
        return this->requestStateChange(PAUSE_REQUESTED);
    }

    /**
     * \brief
     *    Wait until a request for the thread to pause has been
     *    fulfilled or timeout occurs, if specified
     *
     *    If the current requested state is PAUSE_REQUESTED and
     *    the current thread state is RUNNING then the function
     *    call will block until either the requested state has
     *    changed or until the thread state has changed.
     *
     *    This function must not be called by the thread
     *    associated with this object as the result would be an
     *    infinite blocking call.
     *
     *    Note that when you call this function that the logic of
     *    the associated thread cannot be guaranteed to actually
     *    call enterPause() when requested. This is subject to the
     *    actual implementation of the IRunnable implementation.
     *    If this requirement is not fulfilled by the
     *    implementation then this call might block forever when
     *    no timeout has been specified.
     * \param[in] p_timeout_ms
     *    The maximum time to wait for thread to be paused. If set
     *    to zero then no timeout is applied.
     * \return
     *    > 0 if the thread has reached the SUSPENDED state, zero
     *    if timeout was triggered, < 0 if an error occured
     * \errorindicator
     *    via return code
     * \errors
     *    ipl::CommonError with IDs:
     *
     *    - INVALID_USAGE if the Thread that is associated with
     *    this object tried waiting for itself.
     **/
    int_fast8_t waitUntilPaused(const osal::TimeT p_timeout_ms = 0) IPL_NOEXCEPT;

    /**
     * \brief
     *    Wait until a request for the thread to stop has been
     *    fulfilled or timeout occurs, if specified
     *
     *    A call to this function is only valid if the requested
     *    state is STOP_REQUESTED. If the requested state changes
     *    while a call to this function is blocking then an
     *    error will be raised and the call returns.
     *
     *    A timeout may be specified to wait only a certain amount
     *    of time for the thread to stop. If the call returns a
     *    value greater zero the thread's state will be DEAD and
     *    it will have been joined by the calling thread.
     *
     *    Note that if the implementation of the IRunnable
     *    interface doesn't ensure the thread to accommodate the
     *    request then this call will block infinitely in case no
     *    timeout is specified.
     *
     *    Only a thread different than the thread associated with
     *    this object may call this function as otherwise the wait
     *    would be senseless and will block infinitely.
     * \pre
     *    The requested state has to be STOP_REQUESTED and must
     *    not change during the wait call.
     * \post
     *    If the return value is greater zero then the thread is
     *    in state DEAD and was joined by the calling thread as if
     *    osal::Thread::join() has been called.
     * \param[in] p_timeout_ms
     *    The maximum time to wait for the thread to stop. If zero
     *    then no timeout is applied.
     * \return
     *    > 0 if the thread has accommodated the stop request in
     *    time and has successfully been joined, zero if the
     *    timeout was triggered, < 0 if an error occured
     * \errorindicator
     *    via return code
     * \errors
     *    ipl::CommonError with IDs:
     *
     *    - INVALID_USAGE if the Thread that is associated with
     *    this object tried waiting for itself. This error is also
     *    raised if the requested state for this thread object
     *    isn't STOP_REQUESTED upon entry / exit of the function
     *    call.
     *
     *    The errors described at osal::Thread::join() may also
     *    occur.
     **/
    int_fast8_t waitUntilStopped(const osal::TimeT p_timeout_ms = 0) IPL_NOEXCEPT;

    /**
     * \brief
     *    Allows the associated thread to enter a paused state
     *
     *    Depending on the passed parameter the thread can
     *    actively enter a pause state.
     *
     *    If p_only_if_requested is \c true the thread will only
     *    enter the pause state if the current requested state is
     *    already PAUSE_REQUESTED. If this is condition is not
     *    met then the call will immediatly return without effect
     *    in this case.
     *
     *    If p_only_if_requested is \c false then the
     *    PAUSE_REQUESTED state will actively be set even if the
     *    current requested state is NORMAL_OPERATION.
     *
     *    Only a call to this function will cause
     *    waitUntilPaused() to return if another thread is
     *    blocking on it. A direct call to osal::Thread::suspend()
     *    will *not* do this. Also a direct call to suspend()
     *    might wake up even if the requested state is still
     *    PAUSE_REQUESTED.
     *
     *    This function may only be called by the thread
     *    associated with this Thread object i.e.
     *    osal::Thread::getCallerThread() ==
     *    osal::Thread::getThreadId() must evaluate to true.
     * \param[in]
     *    p_only_if_requested If \c true then the pause state will
     *    only be entered if the current request state is
     *    PAUSE_REQUESTED. Otherwise the pause state will also be
     *    entered when the current request state is
     *    NORMAL_OPERATION and the new requested state will be
     *    PAUSE_REQUESTED. This does not happen if the current
     *    requested state is STOP_REQUESTED, though to prevent
     *    override of stop requests.
     * \return
     *    true on error, false on success
     * \errorindicator
     *    via return code
     * \errors
     *    ipl::CommonError with IDs:
     *
     *    - INVALID_USAGE if the caller is not the Thread that is
     *    associated with this object.
     **/
    bool enterPause(const bool p_only_if_requested = true) IPL_NOEXCEPT;

    //! true if the object constructed okay, false otherwise
    bool isValid() const IPL_NOEXCEPT
    {
        return osal::Thread::isValid();
    }

protected:

    /**
     * \brief
     *     Small wrapper to add additional logic to the thread
     **/
    class UTIL_EXPORT RunnableWrapper :
        public IRunnable
    {
    public: // member functions
        //! additional wrapper to handle request states
        virtual void threadLoop(const Thread* const);
    };

    // let the wrapper access our stuff
    friend class RunnableWrapper;

private: // members

    //! current state the thread is requested to be in
    util::Thread::RequestState m_requested_state;

    //! \brief
    //!    current state the thread is in
    //!
    //!    (this is needed to indicate to waitUntilPaused when the
    //!    thread really intents to go to pause - the SUSPENDED
    //!    state of the base class is too late for us and causes RC)
    util::Thread::RequestState m_current_state;

    //! lock for safely changing the requested state
    osal::Mutex m_req_lock;

    //! condition that is signalled upon thread entering pause
    osal::Condition m_pause_event;

    //! \brief
    //! condition that is signalled upon thread leaving the
    //! IRunnable::threadLoop function.
    osal::Condition m_stop_event;

    //! the clients runnable interface for the thread
    IRunnable* const m_thread_if;

    //! \brief
    //! performs the indirection to m_thread_if without the need to
    //! make IRunnable a direct base of util::Thread
    RunnableWrapper m_wrapper;
}; // end class

} // end namespace

#endif
