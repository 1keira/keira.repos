/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

/*****************************************************************************/
#ifndef THREADSAFE_MUTEX_HXX
#define THREADSAFE_MUTEX_HXX
/*****************************************************************************/

#include <ipl_config.h>

// #include "threadsafe_dso.h"

#if defined(IPL_OS_POSIX)
#include "MutexImpl-posix.hxx"
#elif defined(IPL_OS_WIN32)
#include "MutexImpl-win32.hxx"
#elif defined(IPL_OS_INTEGRITY)
#include "MutexImpl-integrity.hxx"
#else
#error Unsupported OS
#endif

#include "MutexBase.hxx"

#include <iplbase/time.hxx>
#include <iplbase/abort.hxx>

/*****************************************************************************/

namespace threadsafe {

/*****************************************************************************/

    /*!
        \brief Mutual exclusion between threads aka. a Critical Section

        When you lock() the Mutex, you own it until you unlock() it again.
        The Mutex can only be locked while unowned,
        plus (in the case of a recursive Mutex) when already owned by the
        locking thread.
        Locking an already owned Mutex blocks until it becomes unowned again.
        Trying to lock it fails.

        All the methods return NULL on success or a string describing
        the failure.
        You can compare the pointer you get against the
        \ref ipl_MutexBase_error_constants "error constants" to assess
        the problem
        or just output the string to the user.

        \link2req{satisfies,req~FW_THREADSAFE_MUTEX~1}
    */

    class /* THREADSAFE_EXPORT nope, inline-only */ Mutex: public MutexBase {
    public:

        class Guard;

        Mutex(bool recursive=false) IPL_NOEXCEPT: impl(recursive) {}

        const char *lock() IPL_NOEXCEPT     { return impl.lock();     }
        const char *unlock() IPL_NOEXCEPT   { return impl.unlock();   }
        const char *try_lock() IPL_NOEXCEPT { return impl.try_lock(); }
        const char *try_lock(const iplbase::Duration &timeout) IPL_NOEXCEPT {
            return impl.try_lock(timeout);
        }

    protected:
        MutexImpl impl;
        friend class Condition;  // may access impl
    };

/*****************************************************************************/

    /*!
        \brief <a href="http://en.wikipedia.org/wiki/Resource_Acquisition_Is_Initialization">RAII</a>
        wrapper for Mutex

        \code
        threadsafe::Mutex::Guard lock(mutex);
        if(frobnicate()==ERROR)
            return WAAH;
        return ALLRIGHT;
        \endcode
        is better than
        \code
        mutex.lock();
        if(frobnicate()==ERROR) {
            // Oh, I forgot to mutex.unlock()
            return WAAH;
        }
        mutex.unlock();
        return ALLRIGHT;
        \endcode
    */
    class /* THREADSAFE_EXPORT inline-only */ Mutex::Guard {

    public:
        Guard(Mutex &mutex) IPL_NOEXCEPT: mutex(&mutex) {
            if(mutex.lock()) // BRANCH_COVERAGE_UNTESTABLE
                iplbase::abort(__FILE__, __LINE__, __FUNCTION__,
                               "Mutex::lock() failed");
        }

        //! For special cases where \a mutex can be NULL – use Guard(Mutex &) otherwise!
        Guard(Mutex *mutex) IPL_NOEXCEPT: mutex(mutex) {
            if(mutex)
                if(mutex->lock()) // BRANCH_COVERAGE_UNTESTABLE
                    iplbase::abort(__FILE__, __LINE__, __FUNCTION__,
                                   "Mutex::lock() failed");
        }

        ~Guard() IPL_NOEXCEPT {
            if(mutex)
                if(mutex->unlock()) // BRANCH_COVERAGE_UNTESTABLE
                    iplbase::abort(__FILE__, __LINE__, __FUNCTION__,
                                   "Mutex::unlock() failed");
        }

        Mutex *mutex;  //! public to allow direct access by those who know what they do
    };

/*****************************************************************************/

}  // end of namespace threadsafe

/*****************************************************************************/
#endif
