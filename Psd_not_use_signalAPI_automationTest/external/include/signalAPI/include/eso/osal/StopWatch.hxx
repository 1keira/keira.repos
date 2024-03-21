/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_STOPWATCH_HXX
#define OSAL_STOPWATCH_HXX

#include <ipl_config.h>

#ifdef IPL_OS_POSIX
#    include "posix/StopWatchDefs.hxx"
#    include "posix/ProcessTNGDefs.hxx"
#elif defined IPL_OS_WINPC
#    include "win32/StopWatchDefs.hxx"
#    include "win32/ProcessTNGDefs.hxx"
#elif defined IPL_OS_INTEGRITY
#    include "integrity/StopWatchDefs.hxx"
#    include "integrity/ProcessTNGDefs.hxx"
#else
#    error "error undefined IPL_OS_ variant"
#endif

#include <osal/osal.hxx>
#include <osal/osal_dso.h>

namespace osal
{

/**
 * \brief
 *    This class allows to measure varouss types of time periods in an
 *    efficient manner.

 *    For getting information about time that passed between two
 *    certain points in time this class can be used. It internally
 *    stores an OS dependent, efficient data type that is
 *    high-resolution and doesn't need to be transformed into abstract
 *    time values during measurement.
 *
 *    When measurement has been finished then an abstract time value
 *    can be retrieved.
 *
 *    This is just a base class that provides basic API. It can't be
 *    instantiated on its own. Specializations for specific types for
 *    time are provided along with this header.
 **/
class OSAL_EXPORT StopWatchBase
{
public:
    /**
     * \brief
     *    enum used for choosing different time units at
     *    getElapsedTime
     * \note
     *    This is mainly present to allow more fine-grained
     *    resolution than milliseconds. Finer resolution than
     *    MICROSECONDS is not expected to be needed.
     **/
    enum TimeUnit
    {
        MILLISECONDS,
        MICROSECONDS
    };
public:
    /**
     * \brief
     *    Start measurement of time. Causes the start time of the
     *    StopWatch to be overwritten.
     * \note
     *    Multiple subsequent calls to start are without effect.
     * \errorindicator
     *    via hasError()
     * \errors
     *    osal::Time::Error with IDs:
     *
     *    - GET_TIME_FAILED if access the system time was not
     *    possible
     **/
    void start();

    /**
     * \brief
     *    Stop measurement of time. Causes the time that elapsed
     *    since the last call to start() to be added
     * \note
     *    Multiple subsequent calls to stop are without effect.
     * \errorindicator
     *    via hasError()
     * \errors
     *    osal::Time::Error with IDs:
     *
     *    - GET_TIME_FAILED if access the system time was not
     *    possible
     **/
    void stop();

    /**
     * \brief
     *    Set the elapsed time recorded so far in the StopWatch
     *    object to zero
     * \note
     *    This doesn't affect the running state of the object.
     *    I.e. if start() was previously called then the watch is
     *    still running after reset().
     **/
    void reset();

    /**
     * \brief
     *    Returns wheter the watch is currently running
     **/
    bool isWatchRunning() const
    {
        return m_watch_running;
    }

    /**
     * \brief
     *    Get the accumulated time that elapsed between subsequent
     *    start and stop calls. Not counting the elapsed time of
     *    the possibly still running stopwatch.

     *    This function also covers overflow handling if needed as
     *    well as any time unit conversions.
     * \param[in]
     *    p_unit The time unit in which the stopped time should be
     *    retrieved
     * \return
     *    The elapsed time between all calls to start() and stop()
     *    since construction of the object or since the reset()
     *    function has been called last.
     **/
    TimeT getStoppedTime(
        const TimeUnit p_unit = MILLISECONDS) const;

    /**
     * \brief
     *    Get the accumulated time of subsequent start and stop
     *    calls _plus_ the current stopwatch time, if the
     *    stopwatch is currently running.
     * \param[in]
     *    p_unit The time unit in which the elapsed time should be
     *    retrieved
     * \return
     *    getStoppedTime(p_unit) + peekRuntime(p_unit)
     **/
    TimeT getElapsedTime(
        const TimeUnit p_unit = MILLISECONDS) const;

    /**
     * \brief
     *    Get the time that currently elapsed since the last call
     *    to start(). This does not cause the accumulated stopped
     *    time to be increased.

     *    If the stopwatch is not currently running then zero will
     *    be returned
     * \param[in]
     *    p_unit The time unit in which the runtime should be
     *    retrieved
     * \return
     *    The elapsed time since the last call to start() or zero
     *    if the stopwatch is not currently running
     * \errorindicator
     *    via hasError()
     * \errors
     *    osal::Time::Error with IDs:
     *
     *    - GET_TIME_FAILED if access the system time was not possible
     **/
    TimeT peekRuntime(
        const TimeUnit p_unit = MILLISECONDS) const;

    //! returns true if the last operation failed, false otherwise
    bool hasError() const
    { return m_has_error; }
protected:
    /**
     * \brief
     *    Construct a new StopWatch object
     * \errorindicator
     *    via hasError()
     **/
    StopWatchBase();

    void resetError() const
    { m_has_error = false; }

    void setError() const
    { m_has_error = true; }

    //! OS-dependent handle for stop watch impl.
    StopWatchHandle m_handle;
private:
    //! \brief
    //! whether the stopwatch is currently running i.e. start has
    //! been called
    bool m_watch_running;

    //! whether the last operation failed
    mutable bool m_has_error;
};

/**
 * \brief
 *    StopWatch that measures elapsed realtime
 **/
class OSAL_EXPORT RealtimeStopWatch :
    public StopWatchBase
{
public:
    /*
     * \param[in] start
     *    If set to true then the watch will immediatly be
     *    started. This behaves like start() has been called after
     *    construction.
     */
    RealtimeStopWatch(const bool start = false);
};

//! \brief
//!    backward compatibility for old osal::StopWatch
//!
//!    earlier there was only one stopwatch type that was operating on
//!    real-time
typedef RealtimeStopWatch StopWatch;

/**
 * \brief
 *    StopWatch that measures consumed processor time for a process
 * \note
 *    This kind of timer is not available on WinCE.  Any attempt to
 *    create an instance of this timer will raise an error of the Type
 *    Time::Error and the ID Time::NO_CLOCK_SOURCE. The resulting
 *    object will not be usable.
 **/
class OSAL_EXPORT ProcessTimeStopWatch :
    public StopWatchBase
{
public:
	/** StopWatch for the own process. */
    ProcessTimeStopWatch(const bool start = false);

	/** StopWatch for the process, whose process id is passed.
	 * If the process doesn't exist, or the clock for the process can't be accessed an error
	 * is raised and hasError() returns true
	 */
    ProcessTimeStopWatch(osal::ProcessId pid, const bool auto_start);
};

/**
 * \brief
 *    StopWatch that measures consumed processor time for the current
 *    thread
 **/
class OSAL_EXPORT ThreadTimeStopWatch :
    public StopWatchBase
{
public:
    ThreadTimeStopWatch(const bool start = false);
};

} // end namespace

#endif
