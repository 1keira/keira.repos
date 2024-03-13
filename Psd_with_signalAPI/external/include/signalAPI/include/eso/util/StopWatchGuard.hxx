/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_STOPWATCHGUARD_HXX
#define UTIL_STOPWATCHGUARD_HXX

#include <ipl_config.h>

#include <common/ScopeGuard.hxx>
#include <osal/StopWatch.hxx>

namespace util
{

/**
 * \brief
 *     This is a specialized guard for the osal::StopWatch that eases
 *     the handling of the StopWatch under certain circumstances

 *     The StopWatchGuard helps you measuring the time span needed for
 *     processing a certain code block.
 *
 *     Usage:
 *
 *     // here we have a new stopwatch
 *     osal::StopWatch my_watch;
 *     {
 *         StopWatchGuard my_watch_guard(my_watch);
 *         // the StopWatch is started now, nothing else to do
 *         // ...
 *         // do your work, the stop watch will be stopped at the end of the block.
 *     }
 *     // lock is released now
**/
template <class WATCH = osal::StopWatch>
class StopWatchGuard
{
public:
    /**
     * \brief
     *    The stopwatch will automatically be started and the
     *    release function is the stop function such that the
     *    lifetime of the StopWatchGuard is measured
     * \param[in,out]
     *    p_watch A reference to an osal::StopWatch object that is
     *    to be started at construction time and stopped again
     *    upon destruction of this StopWatchGuard object.
     **/
    StopWatchGuard( WATCH &p_watch) IPL_NOEXCEPT :
        m_watch(p_watch)
    {
        p_watch.start();
    }

    ~StopWatchGuard() IPL_NOEXCEPT
    {
        m_watch.stop();
    }
private:
    WATCH &m_watch;
};

typedef StopWatchGuard<osal::RealtimeStopWatch> RealtimeStopWatchGuard;
typedef StopWatchGuard<osal::ProcessTimeStopWatch> ProcessTimeStopWatchGuard;
typedef StopWatchGuard<osal::ThreadTimeStopWatch> ThreadTimeStopWatchGuard;

} // end namespace

#endif
