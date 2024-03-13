/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_POSIX_TIMEDEFS_HXX
#define OSAL_POSIX_TIMEDEFS_HXX

#include <time.h>

namespace osal
{

/**
 * \brief
 *     sets an absolute timestamp into \c spec

 *     The current time from \c clock will be retrieve and the time found in
 *     \c t (in milliseconds) will be added to it.
 * \return
 *     \c true on error, \c false otherwise. errno is kept no error is
 *     raised.
 **/
inline bool setTimespec(
    clockid_t clock, struct timespec *spec, const osal::TimeT &t)
{
    if (clock_gettime (clock, spec))
    {
        return true;
    }

    // ms div 1000 is the number of seconds to wait
    spec->tv_sec += t / 1000;
    // the left ms times 10^6 is the number of ns wanted
    spec->tv_nsec += (t % 1000) * 1000 * 1000;

    if (spec->tv_nsec >= 1000 * 1000 * 1000)
    {
        spec->tv_sec++;
        spec->tv_nsec -= 1000 * 1000 * 1000;
    }

    return false;
}

} // end ns osal

#endif // inc. guard
