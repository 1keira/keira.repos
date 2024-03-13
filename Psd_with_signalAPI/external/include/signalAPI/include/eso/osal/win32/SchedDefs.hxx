#ifndef OSAL_WIN32_SCHEDDEFS_HXX
#define OSAL_WIN32_SCHEDDEFS_HXX

/*
    Copyright esolutions GmbH
    All rights reserved
    Authors:
        Peter Dusel
        Marcel Brueckner
        Matthias Gerstner
        Stefan Bittner
*/

#include <ipl_config.h>

namespace osal
{
//! A type that can represent arbitrary scheduling priorities on WIN32
typedef int Priority;

//! implementation specific default priority for PC / CE
const Priority g_default_prio =
#ifdef IPL_OS_WINPC
    // this maps to NORMAL priority
    0;
#else
    // on WinCE this is the replacement for NORMAL
    251;
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
const PriorityOrder g_prio_order = 
#ifdef IPL_OS_WINPC
    INCREASING;
#else
    // on WinCE everything is upside down. Fits it. Maybe they shook
    // it too hard such that all the functionality dropped out of
    // it. And what was left was all messed up.
    DECREASING;
#endif

} // end namespace

#endif // OSAL_WIN32_SCHEDDEFS_HXX
