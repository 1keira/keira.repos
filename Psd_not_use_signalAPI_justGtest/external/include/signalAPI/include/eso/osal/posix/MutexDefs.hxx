/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_POSIX_MUTEXDEFS_HXX
#define OSAL_POSIX_MUTEXDEFS_HXX

#include <pthread.h>
#include <string.h>

#include <osal/osal.hxx>

namespace osal
{

/*
 * we want to recycle the mutex logic for ShmMutex on POSIX
 *
 * that is why we have all relevant logic as static functions in
 * MutexOps
 */

struct OSAL_EXPORT MutexOps
{
    static bool init(pthread_mutex_t*,
        const bool recursive,
        const bool prio_inherit,
        const bool process_shared);

    static bool destroy(pthread_mutex_t*);

    static bool lock(pthread_mutex_t *mutex)
    {
        int res;

        if( (res = pthread_mutex_lock(mutex)) ) // BRANCH_COVERAGE_UNTESTABLE
        {
            return handleLockError(res);
        }

        return false;
    }

    static bool unlock(pthread_mutex_t *mutex)
    {
        int res;

        if ( ( res = pthread_mutex_unlock(mutex) ) ) // BRANCH_COVERAGE_UNTESTABLE
        {
            return handleUnlockError(res);
        }

        return false;
    }

    static int_fast8_t tryLock(pthread_mutex_t *mutex)
    {
        int res;

        if( ( res = pthread_mutex_trylock(mutex) ) ) // BRANCH_COVERAGE_UNTESTABLE
        {
            return handleTryLockError(res);
        }

        // TRY_LOCK_SUCCESS
        return 0;
    }

    static int_fast8_t tryLockTimeout(pthread_mutex_t*,
        const osal::TimeT&);

    static bool handleLockError(const int error);
    static int_fast8_t handleTryLockError(const int error);
    static bool handleUnlockError(const int error);

    static bool isValid(const pthread_mutex_t *m)
    {
        if (!m)
        {
            return false;
        }

        for( size_t i = 0; i < sizeof(pthread_mutex_t); i++ ) // BRANCH_COVERAGE_UNREACHABLE
        {
            if( ((const uint8_t*)m)[i] != 0xEB )
                return true;
        }

        return false;
    }

    static void invalidate(pthread_mutex_t *m)
    {
        /*
         *    we have some complexity here dealing with
         *    validity. we set the whole handle to FF, to
         *    mark invalidity.
         *
         *    This is to save a separate validity flag for
         *    memory saving reasons.
         *
         *    Beware that using zero for invalidity is not a
         *    good idea as a validly initialized mutex may be
         *    all zero.
         */
        ::memset(m, 0xEB, sizeof(pthread_mutex_t));
    }
};

//! OS handle to reference a posix mutex
struct OSAL_EXPORT MutexHandle
{
    pthread_mutex_t mutex;

    bool isValid() const
    {
        return MutexOps::isValid(&mutex);
    }

    void invalidate()
    {
        return MutexOps::invalidate(&mutex);
    }
};

} // end ns

#endif // include guard
