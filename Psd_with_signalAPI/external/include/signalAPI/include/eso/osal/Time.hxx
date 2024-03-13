/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_TIME_HXX
#define OSAL_TIME_HXX

#include <ipl_config.h>

#include <osal/osal.hxx>
#include <osal/osal_dso.h>

#ifdef USE_THREADSAFE_IN_OSAL

#include <iplbase/time.hxx>

#else

//#if defined (IPL_OS_ANDROID) || defined (IPL_OS_LINUX) || defined (IPL_OS_QNX)
#ifdef IPL_OS_POSIX
#    include "posix/TimeDefs.hxx"
#elif defined (IPL_OS_WINPC)
#    include "win32/TimeDefs.hxx"
#else
#    error "error undefined IPL_OS_ variant"
#endif

#endif

namespace osal
{

#ifdef IPL_OS_WINPC
extern bool OSAL_EXPORT g_osal_win32_hwcounter;
extern LONGLONG OSAL_EXPORT g_osal_win32_hwcounter_reffreq;
#endif

/**
 * \brief
 *    Special type for absolute time specification

 *    To achieve higher type safety in comparison to relative time
 *    specifications this type is used.
 *
 *    You can get a valid instance of this object from
 *    osal::Time::getTime(const osal::TimeT&)
 **/
struct AbsTimeT
{
    TimeT t;

    bool isValid() const
    { return m_valid; }

    AbsTimeT() : t(), m_valid(false) { }

protected:
    // only osal::Time is allowed to create valid absolute times
    friend class Time;

    bool m_valid;
};

/**
 * \brief
 *    Collection of static functions for getting primitive time values
 *    from the OS

 *     Different kinds of time retrieval are offered that provide
 *     different kinds of efficieny, comparability and reference time
 *     points.
 * \note
 *    Note theres a difference between functions based on different
 *    clocks.
 *
 *    The real-time clock can change if the system time is changed and
 *    also the clock speed can change (e.g.  NTP operation). The
 *    monotonic clock, however, won't suddenly change in an
 *    unpredictable manner.
 *
 *    It is still possible that the underlying clock source of
 *    monotonic clocks are subject to variations in clock speed,
 *    however. The latter is typically done by NTP programs that use
 *    for example adjtime() on POSIX systems to let the clock run
 *    faster or slower.
**/
class OSAL_EXPORT Time
{
public: // types
    //! specific Time error IDs
    enum TimeErrors
    {
        NO_CLOCK_SOURCE = 0,
        SLEEP_FAILED,
        GET_TIME_FAILED,
        GET_UPTIME_FAILED,
        GET_TIMESTAMP_FAILED
    };

    //! Time specific error type
    static ipl::ErrorType Error;
public: // functions
    /**
     * \brief
     *    Puts the time in milliseconds since some unspecified
     *    starting point into \c t

     *    This time value is only valid on the current OS and in
     *    the current process.  Comparison beyond these borders
     *    are undefined.
     *
     *    This function can be used for efficient time
     *    measurements inside a process.  If you need comparable
     *    time across process limits then use getTimestamp()
     *    instead.
     *
     *    The clock on which this function is based is monotonic
     *    on POSIX systems i.e.  it won't jump backwards and it
     *    hopefully also won't change in speed.
     * \param[out] t
     *    variable where the according time value is written to.
     * \return
     *    true on error, false on success
     * \errors
     *    SysError with ID
     *
     *    - NOT_IMPLEMENTED if the system doesn't supply an
     *    according timing facility.
     *
     *    Time::Error with ID
     *
     *    - GET_TIME_FAILED on severe internal errors
     * \errorindicator
     *    via return code
     **/
    static bool getTime(TimeT &t);

    /**
     * \brief
     *     Does the same as getTime(TimeT) but returns an AbsTimeT

     *     If provided adds \c add_time to the obtained absolute
     *     time.
     * \errorindicator
     *     via isValid() member of the returned object
     * \errors
     *     \see getTime(TimeT&)

     *     Only osal::Time is allowed to create AbsTimeT objects.
     *     This is to emphasize that only times retrieved from
     *     Time::getTime() are suitable for absolute times.
     **/
    static AbsTimeT getTime(const osal::TimeT &add_time = 0)
    {
#ifdef USE_THREADSAFE_IN_OSAL
            AbsTimeT ret;
            ret.m_valid=true;
            ret.t=(TimeT)iplbase::TimePoint(add_time, 1000).ms();
            return ret;
#else
        AbsTimeT ret;
        ret.m_valid = (Time::getTime(ret.t) != true);
        ret.t += add_time;
        return ret;
#endif
    }

    /**
     * \brief
     *    Returns the uptime of the system in milliseconds

     *    The uptime is the time since the hardware, operating
     *    system or process has been started. The actual base for
     *    this is platform-dependent. Thus it cannot be compared
     *    against measurements of other processes or systems.
     *
     *    The clock on which this function is based is monotonic
     *    i.e. is doesn't jump and always runs at the same speed,
     *    hopefully.
     * \warning
     *    On some OS the uptime may overflow after a certain
     *    amount of time and begin at zero again. (currently the
     *    case on WIN32 when no high-performance counters are
     *    available).
     * \return
     *    true on error, false on success
     * \param[out] t
     *    Here the time in milliseconds since the start of the
     *    hardware, OS or process is written to.
     * \errors
     *    Time::Error with ID
     *
     *    - GET_UPTIME_FAILED on severe internal errors
     * \errorindicator
     *    via return code
     **/
    static bool getUptime(TimeT &t);

    /**
     * \brief
     *    Returns the time when osal was initialized

     *    Just like getUptime() the value returned from this
     *    function is platform-dependent. Probably the only
     *    useful purpose for this timestamp is if you want to
     *    measure start-up times of processes, which requires
     *    creation of an Osal object very soon after entering
     *    main().
     * \warning
     *    Don't call this before creating an Osal object! There is
     *    no error-checking for this case at the moment.
     * \return
     *    The time in milliseconds when osal was initialized,
     *    relative to hardware or OS startup.
     **/
    static TimeT const & getInitTime();

    /**
     * \brief
     *    Returns the time in milliseconds since the beginning of the UNIX epoch
     *    (1.1.1970 00:00 UTC)

     *    This function is present to get a defined timestamp
     *    using the beginning of the UNIX epoch as basis. This
     *    allows to compare timestamps across processes and OSs.
     *
     *    The clock on which this function is based is not
     *    monotonic i.e. it can jump and it change in speed.
     * \param[out] t
     *    Here the time in milliseconds since the beginning of the
     *    UNIX epoch will be put.
     * \return
     *    true on error, false on success
     * \warning
     *    On WinCE lower than 5.0 the highest resolution that can
     *    be provided here is "seconds". This is due to OS
     *    insufficiencies.
     * \errorindicator
     *    via return code
     * \errors
     *    SysError with IDs:
     *
     *    - NOT_IMPLEMENTED if the system doesn't supply an
     *    according timing facility.
     *
     *    Time::Error with IDs:
     *
     *    - GET_TIMESTAMP_FAILED on severe internal errors
     **/
    static bool getTimestamp(TimeT &t);

    /**
     * \brief
     *    Returns the time in nanoseconds since the beginning of the UNIX epoch
     *    (1.1.1970 00:00 UTC)

     *    This function is present to get a defined timestamp
     *    using the beginning of the UNIX epoch as basis. This
     *    allows to compare timestamps across processes and OSs.
     *
     *    The clock on which this function is based is not
     *    monotonic i.e. it can jump and it change in speed.
     * \param[out] t
     *    Here the time in nanoseconds since the beginning of the
     *    UNIX epoch will be put.
     * \return
     *    true on error, false on success
     * \warning
     *    On WinCE lower than 5.0 the highest resolution that can
     *    be provided here is "seconds". This is due to OS
     *    insufficiencies.
     * \errorindicator
     *    via return code
     * \errors
     *    SysError with IDs:
     *
     *    - NOT_IMPLEMENTED if the system doesn't supply an
     *    according timing facility.
     *
     *    Time::Error with IDs:
     *
     *    - GET_TIMESTAMP_FAILED on severe internal errors
     **/
    static bool getTimestampNS(TimeT &t);


    /**
     * \brief
     *    Make the caller sleep for at least the given number of
     *    milliseconds

     *    The sleep duration may be longer than actually requested
     *    due to the resolution of the respective hardware timer
     *    or due to scheduling behaviour.
     *
     *    If \c p_sleep_ms is negative or zero then no sleep will
     *    be performed.
     * \param[in]
     *    p_sleep_ms The number of milliseconds to suspend
     *    execution
     * \return
     *    true if an error occured, false otherwise
     * \errors
     *    Time::Error with ID
     *
     *    - SLEEP_FAILED on severe, internal errors
     * \errorindicator
     *    via return code
     **/
    static bool sleep(const TimeT p_sleep_ms);
private: // functions
    //! This object should not be instantiated.
    Time();
    //! We dont want this object to be instantiated.
    ~Time();

    /**
     * \brief
     *     Initialise our timer backend (check hw-features)
     * \note
     *     This will only be called by the osal::Osal init object
     * \return
     *     true on error, false on success
     * \errorindicator
     *     via return code
     * \errors
     *     Time::Error with ID
     *
     *     - NO_CLOCK_SOURCE if it wasn't possible to determine a
     *     suitable clock source
     **/
    static bool init();

    //! to allow the init object to call init()
    friend class osal::Osal;
}; // end class Time

} // end namespace

#endif // OSAL_TIME_HXX
