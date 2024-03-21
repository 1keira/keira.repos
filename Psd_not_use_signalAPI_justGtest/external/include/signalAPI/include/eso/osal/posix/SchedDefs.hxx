/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_POSIX_SCHEDDEFS_HXX
#define OSAL_POSIX_SCHEDDEFS_HXX

#include <ipl_config.h>
#include <osal/osal_dso.h>

#include <sched.h>
#include <limits.h>

// scheduling related definitions for osla/posix
namespace osal
{

//! A type that can represent arbitrary scheduling priorities on POSIX
typedef int Priority;

//! OS specific default priority
const Priority g_default_prio =
#ifdef IPL_OS_QNX
    10;
#elif defined(IPL_OS_LINUX)
    0;  // static priority of all threads running with NORMAL/OTHER policy,
        // also good as the default nice value if interpreted as such.
#else
    0;
#    error "Please set a default thread priority for threads"
        " for your platform"
#endif

// a constant denoting an invalid priority
const Priority INVALID_PRIORITY = INT_MIN;
    
//! \brief
//! This types differentiates between higher priorities are higher
//! values and lower priorities are lower values    
enum PriorityOrder
{
    //! higher values are higher priorities
    INCREASING,
    //! lower vaules are higher priorities
    DECREASING
};

//! scheduling priorities increase with higher values on POSIX
const PriorityOrder g_prio_order = INCREASING;

} // end namespace

#endif // OSAL_POSIX_SCHEDDEFS_HXX
