#ifndef OSAL_INTEGRITY_SCHEDDEFS_HXX
#define OSAL_INTEGRITY_SCHEDDEFS_HXX

/*
    Copyright esolutions GmbH
    All rights reserved
    Authors:
        Peter Dusel
        Marcel Brueckner
        Matthias Gerstner
        Stefan Bittner
		Jörg Kupietz
*/

// #include <ipl_config.h>
// #include <osal/osal_dso.h>
// 
// #include <sched.h>
#include <limits.h>

namespace osal
{

//! A type that can represent arbitrary scheduling priorities on POSIX
typedef int Priority;

//! implementation specific default priority for OSAL_INTEGRITY_SCHEDULER
const Priority g_default_prio =  128;

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

#endif
