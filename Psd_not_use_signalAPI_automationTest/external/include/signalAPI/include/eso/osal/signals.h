/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

/*****************************************************************************/
#ifndef OSAL_SIGNALS_H
#define OSAL_SIGNALS_H
/*****************************************************************************/
/*!
    \file
    \brief Global list of signal ids used across OSAL
*/
/*****************************************************************************/

#include <ipl_config.h>

#include <signal.h>

#if defined(IPL_OS_POSIX) /**************************************************/

//! \brief High prio timer goes ring! on a Posix system
#define IPL_TIMER_POSIX_SIGNAL_HIGHPRIO (SIGRTMIN+2)
//! \brief Default prio timer goes ring! on a Posix system
#define IPL_TIMER_POSIX_SIGNAL_DEFAULT (SIGRTMIN+3)

#elif defined(IPL_OS_WIN32) /************************************************/

// needed so they can be passed to a SignalCatcher
/*! \{
    \brief Dummy signal numbers for Windows
    
    These signals are not supported by Windows but are defined here so
    non-Windows signal catching code compiles with reduced functionality,
    but without errors.
    The two first signals even do work insofar as \c Ctrl-Brk and
    closing the Terminal Window are mapped to them by OSAL.
*/
#define SIGHUP     NSIG+1   //!< \brief Thrown on window close and logoff
// #define SIGINT         already defined by Windows
#define SIGQUIT    NSIG+3   //!< \brief Thrown on \c Ctrl-Brk
// #define SIGILL         already defined by Windows
#define SIGTRAP    NSIG+5   //!< \brief (dummy)
// #define SIGABRT    already defined by Windows
#define SIGIOT     NSIG+6   //!< \brief (dummy)
#define SIGBUS     NSIG+7   //!< \brief (dummy)
// #define SIGFPE         already defined by Windows
#define SIGKILL    NSIG+9   //!< \brief (dummy)
#define SIGUSR1    NSIG+10  //!< \brief (dummy)
// #define SIGSEGV        already defined by Windows
#define SIGUSR2    NSIG+12  //!< \brief (dummy)
#define SIGPIPE    NSIG+13  //!< \brief (dummy)
#define SIGALRM    NSIG+14  //!< \brief (dummy)
// #define SIGTERM        already defined by Windows
#define SIGSTKFLT  NSIG+16  //!< \brief (dummy)
#define SIGCHLD    NSIG+17  //!< \brief (dummy)
#define SIGCONT    NSIG+18  //!< \brief (dummy)
#define SIGSTOP    NSIG+19  //!< \brief (dummy)
#define SIGTSTP    NSIG+20  //!< \brief (dummy)
#define SIGTTIN    NSIG+21  //!< \brief (dummy)
#define SIGTTOU    NSIG+22  //!< \brief (dummy)
#define SIGURG     NSIG+23  //!< \brief (dummy)
#define SIGXCPU    NSIG+24  //!< \brief (dummy)
#define SIGXFSZ    NSIG+25  //!< \brief (dummy)
#define SIGVTALRM  NSIG+26  //!< \brief (dummy)
#define SIGPROF    NSIG+27  //!< \brief (dummy)
#define SIGWINCH   NSIG+28  //!< \brief (dummy)
#define SIGIO      NSIG+29  //!< \brief (dummy)
#define SIGPOLL    NSIG+29  //!< \brief (dummy)
#define SIGPWR     NSIG+30  //!< \brief (dummy)
#define SIGSYS     NSIG+31  //!< \brief (dummy)
/*! \} */

//! \brief High prio timer goes ring! on a Posix system
#define IPL_TIMER_POSIX_SIGNAL_HIGHPRIO 0  // dummy
//! \brief Default prio timer goes ring! on a Posix system
#define IPL_TIMER_POSIX_SIGNAL_DEFAULT 0  // dummy

#elif defined(IPL_OS_INTEGRITY) /********************************************/
//! \brief High prio timer goes ring! on a Posix system
#define IPL_TIMER_POSIX_SIGNAL_HIGHPRIO 0  // dummy
//! \brief Default prio timer goes ring! on a Posix system
#define IPL_TIMER_POSIX_SIGNAL_DEFAULT 0  // dummy

#else /**********************************************************************/
#error Unsupported OS
#endif

/*****************************************************************************/
#endif
