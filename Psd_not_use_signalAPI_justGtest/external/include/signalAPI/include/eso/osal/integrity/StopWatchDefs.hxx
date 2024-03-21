#ifndef OSAL_INTEGRITY_STOPWATCHDEFS_HXX
#define OSAL_INTEGRITY_STOPWATCHDEFS_HXX

// #include <time.h>
#include <INTEGRITY.h>

namespace osal
{

//! OS handle for time queries
typedef struct
{
     //! start time of the StopWatch
     ::Time start_time;
     //! accumulated time of subsequent start()/stop() calls
     ::Time elapsed_time;
     //! the clock to use for this watch
     clockid_t clock;
} StopWatchHandle;

} // end ns osal

#endif // inc. guard
