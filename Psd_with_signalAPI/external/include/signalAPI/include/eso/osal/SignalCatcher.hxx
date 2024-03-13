/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

/****************************************************************************/
#ifndef OSAL_SIGNALCATCHER_HXX
#define OSAL_SIGNALCATCHER_HXX
/****************************************************************************/

#include <ipl_config.h>

#if defined(IPL_OS_POSIX)
#include "SignalCatcherImpl-posix.hxx"
#elif defined(IPL_OS_WIN32)
#include "SignalCatcherImpl-win32.hxx"
#elif defined(IPL_OS_INTEGRITY)
#include "SignalCatcherImpl-integrity.hxx"
#else
#error Unsupported OS
#endif

#include <common/Shared.hxx>
#include <osal/osal_dso.h>
#include <osal/SignalQueue.hxx>
#include <osal/SignalDispatcher.hxx>

/****************************************************************************/

namespace osal {

/****************************************************************************/

    /*!
        \brief Set up a callback to be invoked on a (Posix) signal

        The callback is not invoked directly from the signal handler,
        so you \e need \e not obey arcane rules about async-safe functions.
        Instead either a special signal dispatching thread
        (which is started on demand) calls your stuff
        or you provide your own queue and the callback is called from
        however you handle this queue.

        You cannot catch a signal that has already a signal handler installed.
        Consequently only one SignalCatcher can exist for any signal number
        at any given time.

        If you destroy a SignalCatcher that has signals queued up but not
        called the callback yet, those signals simply get dropped.

        \note Signal handling is severely crippled under Windows,
        as no signal can be caught reliably
        and only SIGABRT, SIGFPE and SIGSEGV are generated at all.
        Therefore under Windows only Ctrl-C, Ctrl-Brk, window close et al.
        are supported and mapped to SIGTERM, SIGBRK, SIGHUP, respectively.
    */
    class OSAL_EXPORT SignalCatcher: public SignalCatcherImpl {

    public:
        //! \brief Catch \a signal and make it call \a callback(\a context)
        SignalCatcher(int signal,
                      SignalQueue::Callback callback, void *context=NULL);
        //! \brief Catch \a signal and make it put a call to
        //! \a callback(\a context) into \a queue
        SignalCatcher(int signal, SignalQueue &queue,
                      SignalQueue::Callback callback=NULL, void *context=NULL);
    };

/****************************************************************************/

}  // end of namespace osal

/****************************************************************************/
#endif
