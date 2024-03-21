/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_POSIX_STOPWATCHDEFS_HXX
#define OSAL_POSIX_STOPWATCHDEFS_HXX

#include <time.h>

namespace osal
{

//! OS handle for time queries
typedef struct
{
    //! start time of the StopWatch
    struct timespec start_time;
    //! accumulated time of subsequent start()/stop() calls
    struct timespec elapsed_time;
    //! the clock to use for this watch
    clockid_t clock;
} StopWatchHandle;

} // end ns osal

#endif // inc. guard
