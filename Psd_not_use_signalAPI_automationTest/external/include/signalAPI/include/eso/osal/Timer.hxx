/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_TIMER_HXX
#define OSAL_TIMER_HXX

#include <ipl_config.h>

#include <common/stdint.h>
#include <common/error/ErrorType.hxx>
#include <common/NonCopyable.hxx>

#include <osal/osal_dso.h>

#include <osal/Alarm.hxx>
#include <osal/signals.h>

namespace osal
{

/**
 * \brief \b DEPRECATED, do not use. Use osal::Alarm instead.
 *
 *    This is outdated technology. It used to have its own implementation
 *    but now it is merely a shim around osal::Alarm.
 *    Use that instead.
 *
 *
 *    A timer: an object to handle periodic or non-periodic events
 *    delayed by a given amount of time.

 *    This is a timer. It allows you to specify a callback to be
 *    called either once or periodically.
 *
 *    The moment in time when the callback is to be invoked is given
 *    in milliseconds and always interpreted relative to the moment
 *    when the timer is started.
 *
 *    The callback is invoked from a thread context different than the
 *    one that started or created the timer. Thus one needs to take
 *    appriopriate measures to guard shared data against concurrent
 *    access in the callbacks implementation.
 *
 *     The implementation of a timer might utilize timer functionality
 *     provided by the OS API. Several if not all timers are likely to
 *     share a common thread which receives notification from the OS on
 *     timer expiration. Since callbacks are called from that thread
 *     context, it is important to keep the runtime of the callback
 *     minimal as to not delay the invocation of callbacks due next.
 * \note
 *    The timer object is not copy-assignable. If you need
 *    copy-assignable semantics, use pointers to timers.
 *
 *    The achievable accuracy of the time period depends on a
 *    multitude of factors like the underlying OS timer
 *    implementation, load, timer resolution etc. so no hard
 *    guarantees can be made in this regard.
 **/

class OSAL_EXPORT Timer :
    public ipl::NonCopyable
{
public: // types

    //! specific error IDs
    enum TimerErrors
    {
        CREATE_FAILED = 0,
        START_FAILED,
        STOP_FAILED,
        SNOOZE_FAILED
    };


    //! specific error type
    static ipl::ErrorType Error;

    /**
     * \brief
     *     The callback declaration.

     *    The prototype of the timer callback. It has a pointer to
     *    the timer instance as the only argument.
     * \param[in]
     *    which A pointer to the associated timer instance.
     **/
    typedef void (*TimerCallback)(Timer* const which);

public: // functions
    /**
     * \brief
     *    Creates a new Timer instance.

     *    The timer properties will be defined at every call to
     *    start()
     *
     *    The timer object is bound to a single timer tick
     *    callback function for its lifetime. So choose wisely,
     *    please.
     * \param[in]
     *    cb The C callback function that is called upon timer
     *    ticks
     * \param[in]
     *    is_high_prio Enables prioritization for this timer.
     *    Availabitliy of this feature is platform dependent.
     * \errorindicator
     *    via isValid()
     * \errors
     *    ipl::CommonError with IDs:
     *
     *    - INVALID_USAGE if cb is NULL (only in debug mode)
     *
     *    osal::SystemError with IDs:
     *
     *    - SYSTEM_RESSOURCES_EXHAUSTED if no more ressources are
     *    available to create another timer
     *
     *    Timer::Error with IDs:
     *
     *    - CREATE_FAILED on system specific, other error
     *    conditions
     **/
    Timer(TimerCallback cb, const bool is_high_prio = false);

    /**
     * \brief
     *    The destructor. Cleans up the timer on underlying level.

     *    If the timer was not stopped previously then it is
     *    stopped by the destructor. If a callback for the timer
     *    is still active then the destructor will delay until the
     *    callback is finished before returning execution.
     **/
    virtual ~Timer();

    //! \brief
    //! returns true if construction of the Timer object was
    //! successful, false otherwise
    bool isValid() const { return m_cb!=NULL; }

    /**
     * \brief
     *    Starts or retriggers the timer.

     *    The parameter interval_ms defines after what time period
     *    the timer will tick. If the parameter periodic is true
     *    then the timer will tick again and again until somebody
     *    calls stop() on it or the object is destroyed.
     *
     *    Calling start on an already started timer is allowed. It
     *    will restart the timer with the new parameters. On race
     *    conditions a pending callback from the old timer values
     *    might still occur.
     *
     *    To restart the timer without changing parameters or
     *    invoking its callback function call snooze().
     * \param[in]
     *    interval_ms The time in milliseconds relative to the
     *    start of the timer when the callback will be invoked.
     *    Must not be zero.
     * \param[in]
     *    periodic A flag indicating periodic or non-periodic
     *    execution. If true the timer is periodic.
     * \sa
     *    stop()
     * \return
     *    true on error, false on success
     * \errorindicator
     *    via return code
     * \errors
     *    ipl::CommonError with IDs:
     *
     *    - INVALID_USAGE if interval_ms is zero
     *    - INT_OUT_OF_RANGE in case the specified interval is too
     *    big/small etc.
     *
     *    Timer::Error with IDs:
     *
     *    - START_FAILED on system specific, other error conditions
     **/
    bool start(const uint32_t interval_ms, const bool periodic);

    /**
     * \brief
     *    Stops the timer independent of its properties. If the
     *    timer is already stopped then nothing happens.

     *    It is possible that the callback is invoked once more,
     *    depending on the exact timing of the stop() invocation,
     *    the timers interval_ms parameter and scheduling. This is
     *    an inherent race condition due to timers being
     *    asynchronous and can not be avoided.
     *
     *    On some OS it is guaranteed that after stop() no more
     *    callback are coming in. This also means that stop() may
     *    delay on these OS until a currently active timer
     *    callback returns.
     * \return
     *    true on error, false on success
     * \errorindicator
     *    via return code
     * \errors
     *    Timer::Error with IDs:
     *
     *    - STOP_FAILED on system specific errors (usually serious
     *    integrity error)
     **/
    bool stop();

    /**
     * \brief
     *    Causes the timer to be restarted with its current
     *    parameters.

     *    A race condition may occur that causes a callback still
     *    to be coming in regardless of snooze() being called. Be
     *    prepared.
     * \return
     *    true on error, false on success
     * \errorindicator
     *    via return code
     * \errors
     *    ipl::CommonError with IDs:
     *
     *    - INVALID_USAGE if the timer is not running currently.
     *    Only in debug mode.
     *
     *    Timer::Error with IDs:
     *
     *    - SNOOZE_FAILED if the operation failed for system
     *    specific reasons
     **/
    bool snooze();

    /**
     * \brief
     *    Returns the interval currently set for the timer.
     * \note
     *    If the timer is not running any more then either the
     *    last set value or zero is returned.
    **/
    uint32_t getInterval() const;

    /**
     * \brief
     *    Returns wheter a currently running timer is periodic.
     * \note
     *    If the timer is not running any more then either the
     *    last set value or false is returned.
     **/
    bool isPeriodic() const;

private: // data

    class HighPrioTimer: public Alarm::Timer {
    public:
        HighPrioTimer(): Timer(IPL_TIMER_POSIX_SIGNAL_HIGHPRIO, "HighPrioTimer") {}
    };

    //! The callback
    TimerCallback m_cb;

    uint32_t m_interval;
    bool m_periodic;

    Alarm alarm;

    static ipl::Shared<Alarm::DefaultTimer> &timer_low_prio;
    static ipl::Shared<HighPrioTimer> timer_high_prio;

    static void procedure(void *context);
};

} // end namespace

#endif // OSAL_TIMER_HXX
