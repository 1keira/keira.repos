/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_TIMERGROUP_HXX
#define UTIL_TIMERGROUP_HXX

#include <ipl_config.h>

#include <util/util_dso.h>

#include <iplbase/exceptions.hxx>

#include <common/types/map.hxx>
#include <common/types/queue.hxx>

#include <osal/Timer.hxx>
#include <osal/Mutex.hxx>
#include <osal/AtomicCounter.hxx>
#include <util/ThreadPool.hxx>
#include <util/Thread.hxx>

#include <common/NonCopyable.hxx>

namespace util
{

// fwd. declaration to speed up header parsing
class ThreadPool;

//! \brief
//!    an identifier that is used for identifying individual timers in
//!    the timer group
typedef uint_fast32_t TimerID;

/**
 * \brief
 *    base class for arbitrary C++ callbacks used by the
 *    util::TimerGroup
 * \see
 *    TimerCallback
 * \see
 *    TimerGroup
 **/
class TimerCallbackBase
{
public:
    //! virtual destructor to get impl. destructor called always
    virtual ~TimerCallbackBase() IPL_NOEXCEPT { return; };

    /**
     * \brief
     *    pure virtual operator() for making it possible to call
     *    arbitrary class member functions by deriving from
     *    TimerCallbackBase and implementing the operator
     *    accordingly.
     * \param[in]
     *    which The TimerID of the timer that has triggered
     **/
    virtual void operator()(const TimerID which) IPL_NOEXCEPT = 0;
};



/**
 * \brief
 *    c++ timer callback class implementation

 *    Implements the operator() for arbitrary classes and their member
 *    functions. This is done by using a template argument for the
 *    class type.
 **/
template<class CLASS>
class TimerCallback :
    public TimerCallbackBase
{
public:
    //! type definition of the callback signature
    typedef void (CLASS::*timercb)(const TimerID which);

    /**
     * \brief
     *    The constructor for an arbitrary timer callback object
     * \param[in]
     *    class_pointer A pointer to the class instance where the
     *    callback should be called at
     * \param[in]
     *    callback_member The member function to call at the
     *    object instance
     **/
    TimerCallback(CLASS* class_pointer, timercb callback_member) IPL_NOEXCEPT
    {
        m_class = class_pointer;
        m_method = callback_member;
    }

    //! virtual destructor to satisfy gcc and C++ gurus
    virtual ~TimerCallback() IPL_NOEXCEPT { return; };

    //! implementation of operator() that calls the actual callback
    virtual void operator()(const TimerID which) IPL_NOEXCEPT
    {
        IPLBASE_ABORT_ON_EXCEPTION(
            (m_class->*m_method)(which);
        )
    }
private:
    //! class instance pointer
    CLASS* m_class;
    //! callback member function at m_class
    timercb m_method;
};



/**
 * \brief
 *    Advanced timer functionality on top of osal::Timer

 *
 *    \b WARNING! This does not do what you probably think!
 *    Consider using osal::Alarm and possibly osal::Dispatcher instead!
 *
 *    The osal::Timer aims only to provide a thin abstraction of OS
 *    timer services. This util class now adds comfort features to
 *    timer handling.
 *
 *    The features provided - or to be provided in the future - are:
 *
 *    - C++ callbacks instead of plain C callbacks (i.e. callbacks to
 *    arbitrary C++ class member functions)
 *
 *    - If a high amount of timers is needed then this class can
 *    quickly collect timer ticks by queuing apropriate information
 *    inside class data structures. This queued ticks are then
 *    processed by a configurable sized ThreadPool to actually
 *    dispatch the ticks to the class user. This helps keeping the
 *    osal::Timer functionality reactive while still maintaining the
 *    tick order and not loosing any ticks.
 *
 *    - Alternatively to the standard callback on timer tick
 *    additional actions may be implemented like: Sending a message on
 *    a MessageQueue or triggering an event/condition variable.
 *
 *    - If only few timers are available by the OS then additional
 *    software timers may be setup on top of available OS/hardware
 *    timers to save ressources.
 *    -> this requirement has been dropped. This is now performed on
 *    OSAL level already.  this has the following reasons: if some OS
 *    provide many timers on OSAL level and some don't then we already
 *    have a portability problem. Thus we want always to have many
 *    timers on OSAL level. This eliminates the need for further
 *    multiplexing on UTIL level.
 *
 *    Of course we could also have chosen the other way around: Think
 *    of having only few timers available on OSAL level and encourage
 *    the user to use UTIL layer with multiplexing. But encouraging
 *    the user is a hard thing and then you have your portability
 *    problems again. Also some users might only access the OSAL layer
 *    and suffer from few timers being available.
 * \note
 *    Alternative timer actions are not currently implemented
 *
 *    Also software timers on top of OS timers are currently not
 *    implemented
 * \warning
 *    Timer ticks are asynchronous events. Thus race conditions are
 *    inherent. E.g.  stopping a running timer might or might not
 *    prevent an outstanding timer tick. The same counts for snoozing
 *    a timer and alike. Thus the application must always be aware of
 *    such race condition ticks.
 **/
class UTIL_EXPORT TimerGroup :
    // should not be copied
    public ipl::NonCopyable,
    // for util::ThreadPool instrumentalization
    public IRunnable
{
public:

    /**
     * \brief
     *    Enum to differentiate between different timer tick
     *    actions
     * \note
     *    These may be implemented by providing different addTimer
     *    member functions for each
     **/
    enum TickAction
    {
        //! perform a C++ callback
        TICK_CALLBACK,
        //! send a message on a message queue
        SEND_MESSAGE,
        //! trigger a signal on an event object
        SIGNAL
    };

    //! used to indicate an invalid timer ID
    static const TimerID INVALID_TIMER_ID = UINT32_MAX;
    //! default name pattern for thread names
    static const char* THREAD_NAME;
public:
    /**
     * \brief
     *    Create a new timer group, optionally instrumenting a
     *    thread pool.

     *    If the thread pool options is used then a number of
     *    threads will be present to which timer callbacks are
     *    forwarded for actual processing. This lowers the
     *    processing time for the actual osal::Timer callback and
     *    keeps the timer subsystem reactive.
     *
     *    At the same time the order of triggered timers will be
     *    obtained and timer callbacks will be delivered
     *    asynchronously to the actual callback interface provided
     *    by the user of the TimerGroup.
     *
     *    If the thread pool option is disabled then the
     *    TimerGroup callbacks will run in the context of the
     *    timer and might influence the reactivity of the timer
     *    subsystem by introducing delays.
     * \param[in]
     *    thread_amount The amount of threads to be used in the
     *    thread pool
     * \param[in]
     *    max_queue_size The maximum number of timer callbacks to
     *    enqueue
     * \errorindicator
     *    via isValid()
     * \errors
     *    The errors described at ThreadPool() are valid here, too
     **/
    TimerGroup(const uint8_t thread_amount,
        const uint16_t max_queue_size = UINT16_MAX
        ) IPL_NOEXCEPT;

    /**
     * \brief
     *    Create a new timer group, optionally instrumenting a
     *    thread pool.

     *    If the thread pool options is used then a number of
     *    threads will be present to which timer callbacks are
     *    forwarded for actual processing. This lowers the
     *    processing time for the actual osal::Timer callback and
     *    keeps the timer subsystem reactive.
     *
     *    At the same time the order of triggered timers will be
     *    obtained and timer callbacks will be delivered
     *    asynchronously to the actual callback interface provided
     *    by the user of the TimerGroup.
     *
     *    If the thread pool option is disabled then the
     *    TimerGroup callbacks will run in the context of the
     *    timer and might influence the reactivity of the timer
     *    subsystem by introducing delays.
     * \param[in]
     *    thread_amount The amount of threads to be used in the
     *    thread pool
     * \param[in]
     *    thread_name The name pattern for the timer group's threads.
     * \param[in]
     *    max_queue_size The maximum number of timer callbacks to
     *    enqueue
     * \errorindicator
     *    via isValid()
     * \errors
     *    The errors described at ThreadPool() are valid here, too
     **/
    TimerGroup(const uint8_t thread_amount,
        const char* thread_name,
        const uint16_t max_queue_size = UINT16_MAX
        ) IPL_NOEXCEPT;

    /**
     * \brief
     *    Destructor for the TimerGroup. Shuts down any threads
     *    associated with the group. Dispatching of any timer
     *    ticks is ceased.

     *    Before destruction all active timers must have been
     *    removed from the group.  Otherwise a negative assertion
     *    will be raised in debug mode.
     **/
    virtual ~TimerGroup() IPL_NOEXCEPT;

    /**
     * \brief
     *    Add a new timer to the group

     *    A new osal::Timer will be setup matching the provided
     *    parameters. The timer will henceforth be permanently
     *    known to the timer group. It will not be started,
     *    though. Control of timer runtime is performed via the
     *    stopTimer and startTimer methods.
     *
     *    Eventually the timer has to be removed via removeTimer
     *    before the timer group is destroyed.
     *
     *    Identification of the timer at the group is only done
     *    via the returned TimerID. To check wheter a certain
     *    timer is known to the group you can use the isTimerValid
     *    function.
     * \param[in]
     *    interval The interval in milliseconds after which the
     *    timer is triggered.  May not be zero.
     * \param[in]
     *    periodic Wheter the timer should be triggered
     *    periodically or only once
     * \param[in]
     *    callback The C++ callback that should be called upon
     *    timer tick. Note that this callback has to be valid for
     *    the lifetime of the timer. Doom is ahead otherwise.
     * \param[in]
     *    high_prio if set to true, then ignore max_queue_size
     *    construction time parameter for this timer. i.e. this
     *    timer is prioritized in respect to other timers
     * \return
     *    A unique identifier for the new timer
     * \errorindicator
     *    if INVALID_TIMER_ID is returned then an error occured
     * \errors
     *    ipl::CommonError with IDs:
     *
     *    - OUT_OF_MEMORY if associated data structures could not
     *    be allocated
     *
     *    The errors defined at osal::Timer() can also occur.
     **/
    TimerID addTimer(const uint_fast32_t interval, const bool periodic,
        TimerCallbackBase &callback,
        const bool high_prio = false) IPL_NOEXCEPT;

    /**
     * \brief
     *    Remove any previously via addTimer registered timers
     *    from the timer group

     *    Stops any active timers and remove them from the timer
     *    group. None of the timers can be used furthermore
     * \errors
     *    none
     **/
    void removeAllTimers() IPL_NOEXCEPT;

    /**
     * \brief
     *    Remove a timer that has previously been added via
     *    addTimer.

     *    If the timer is currently running then it will be
     *    stopped before it is removed.
     * \param[in]
     *    which The identifier of the timer to remove from the
     *    group.
     * \return
     *    true on error, false otherwise
     * \errorindicator
     *    via return code
     * \errors
     *    ipl::CommonError with IDs:
     *
     *    - PAR_OUT_OF_RANGE if the given timer ID is not known to
     *    the timer group.
     **/
    bool removeTimer(const TimerID which) IPL_NOEXCEPT;

    /**
     * \brief
     *    Modify parameters of a timer that has already been added
     *    via addTimer.

     *    If the timer is currently running then modifyTimer does
     *    not cause the timer to stop or to apply the new values.
     *    This has to be achieved by calling stopTimer() and
     *    startTimer() accordingly.
     * \param[in]
     *    which The identifier of the timer which parameters
     *    should be modified
     * \param[in]
     *    interval The new interval in milliseconds that the timer
     *    shall have. May not be zero.
     * \param[in]
     *    periodic Wheter the timer should be periodic or oneshot.
     * \return
     *    true on error, false otherwise
     * \errorindicator
     *    via return code
     * \errors
     *    ipl::CommonError with IDs:
     *
     *    - PAR_OUT_OF_RANGE if the given timer ID is not known to
     *    the timer group.
     **/
    bool modifyTimer(const TimerID which, const uint_fast32_t interval,
        const bool periodic) IPL_NOEXCEPT;

    /**
     * \brief
     *    Stop the given timer.
     * \note
     *    If the timer is not currently running the nothing
     *    happens.
     * \param[in]
     *    which The identifier of the timer that should be stopped
     * \return
     *    true on error, false otherwise
     * \errorindicator
     *    via return code
     * \errors
     *    ipl::CommonError with IDs:
     *
     *    - PAR_OUT_OF_RANGE if the given timer ID is not known to
     *    the timer group.
     *
     *    additionally the errors stated at osal::Timer::stop()
     *    can occur.
     **/
    bool stopTimer(const TimerID which) IPL_NOEXCEPT;

    /**
     * \brief
     *    Start the given timer.

     *    Start the given timer using the parameters given at
     *    addTimer or modifyTimer
     * \note
     *    If the timer is already running then the behaviour is
     *    similar to snooze()
     * \param[in]
     *    which The identifier of the timer to start.
     * \return
     *    true on error, false otherwise
     * \errorindicator
     *    via return code
     * \errors
     *    ipl::CommonError with IDs:
     *
     *    - PAR_OUT_OF_RANGE if the given timer ID is not known to
     *    the timer group.
     *
     *    additionally the errors stated at osal::Timer::start()
     *    can occur.
     **/
    bool startTimer(const TimerID which) IPL_NOEXCEPT;

    /**
     * \brief
     *    Snooze the given timer.

     *    To snooze the timer means to restart it from the
     *    beginning using the same parameters.
     *
     *    If the timer is not currently running then nothing
     *    happens.
     * \param[in]
     *    which The identifier of the timer to snooze.
     * \return
     *    true on error, false otherwise
     * \errorindicator
     *    via return code
     * \errors
     *    ipl::CommonError with IDs:
     *
     *    - PAR_OUT_OF_RANGE if the given timer ID is not known to
     *    the timer group.
     *
     *    additionally the errors stated at osal::Timer::snooze()
     *    can occur.
     **/
    bool snoozeTimer(const TimerID which) IPL_NOEXCEPT;

    /**
     * \brief
     *    Return wheter the given TimerID corresponds to a known
     *    timer of the timer group.
     * \param[in]
     *    which The identifier to check for validity
     * \return
     *    true if the given TimerID is valid, false otherwise.
     **/
    bool isTimerValid(const TimerID which) const IPL_NOEXCEPT;

    /**
     * \brief
     *    Returns the set interval for the given TimerID.
     * \param[in]
     *    which The identifier to get the interval for
     * \note
     *     If currently a timer is already running then it is
     *     possible that it is using different parameters than
     *     returned here, because it has not been restarted since a
     *     call to modifyTimer(). To determine parameters of an
     *     already running timer use getTimerObj().
     * \return
     *    zero on error, otherwise on success
     * \errorindicator
     *    via return code
     * \errors
     *    ipl::CommonError with IDs:
     *
     *    - PAR_OUT_OF_RANGE if the given timer ID is not known to
     *    the timer group.
     **/
    uint32_t getTimerInterval(const TimerID which) const IPL_NOEXCEPT;

    /**
     * \brief
     *    Returns wheter the given TimerID is set to periodic
     * \param[in]
     *    which The identifier to check periodicness for
     * \note
     *     If currently a timer is already running then it is
     *     possible that it is using different parameters than
     *     returned here, because it has not been restarted since a
     *     call to modifyTimer(). To determine parameters of an
     *     already running timer use getTimerObj().
     * \return
     *    zero if timer is non-periodic, > 0 if timer is periodic,
     *    < 0 on error
     * \errorindicator
     *    via return code of < 0
     * \errors
     *    ipl::CommonError with IDs:
     *
     *    - PAR_OUT_OF_RANGE if the given timer ID is not known to
     *    the timer group.
     **/
    int_fast8_t isTimerPeriodic(const TimerID which) const IPL_NOEXCEPT;

    /**
     * \brief
     *     Returns the osal::Timer object associated with \c which

     *     The returned object can be used to query its currenty
     *     settings for example.
     * \return
     *     The ptr. to the associated osal::Timer object or NULL on
     *     error
     * \warning
     *     Don't access the returned ptr. after \c which has been
     *     removed via removeTimer().
     **/
    const osal::Timer* getTimerObj(const TimerID which) const IPL_NOEXCEPT;

    //! \brief
    //! Returns whether the TimerGroup has been constructed
    //! successfully
    bool isValid() const IPL_NOEXCEPT
    { return m_thread_pool.isValid(); }
private:
    //! a struct to gather timer information
    struct TimerInfo
    {
        osal::Timer *os_timer;
        TimerCallbackBase &callback;
        uint_fast32_t interval;
        bool periodic;
    };

    // tick callback from osal::Timer
    static void TimerTick( osal::Timer* const );

    // little helper function that checks for validity of TimerID
    // and returns the iterator to it, if valid
    ipl::map<TimerID, TimerInfo>::iterator findTimer(const TimerID);
    ipl::map<TimerID, TimerInfo>::const_iterator
        findTimer(const TimerID) const;

    // IRunnable interface implementation for ThreadPool
    void threadLoop(const util::Thread* const);

    /////////////
    // MEMBERS //
    /////////////

    //! this mutex protects access to the m_tick_queue
    osal::Mutex m_tick_queue_lock;

    //! this mutex protects access to the m_rt_tick_queue
    osal::Mutex m_rt_tick_queue_lock;

    //! this mutex protects access to the m_timers map
    mutable osal::Mutex m_timer_info_lock;

    //! the next timer ID to use upon a call to addTimer
    TimerID m_next_timer_id;

    //! \brief
    //! thread pool that is instrumentalized if the option is chosen
    //! at construction time
    util::ThreadPool m_thread_pool;

    //! \brief
    //! this queue contains all TimerIDs that have ticks
    //! outstanding, in order of arrival for normal priority timers
    ipl::queue<TimerID> m_tick_queue;

    //! like m_tick_queue but for high priority timers
    ipl::queue<TimerID> m_rt_tick_queue;

    //! the collection of all known timers, mapped from TimerID to
    //TimerInfo
    ipl::map<TimerID, TimerInfo> m_timers;

    //! the maximum number of timer callbacks to enqueue
    uint16_t m_max_queue_size;

    //! counter for unnamed thread pool instances(used in thread name generation)
    static osal::AtomicCounter m_inst_counter;

    static ipl::string getDefaultName();
}; // end class

} // end namespace

#endif
