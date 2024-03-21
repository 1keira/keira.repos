/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_POSIX_RWLOCKDEFS_HXX
#define OSAL_POSIX_RWLOCKDEFS_HXX

#ifndef OSAL_NEED_COMMON_RWLOCK_API

#include <string.h>
#include <pthread.h>

#include <osal/osal.hxx>

namespace osal
{

/*
 * We want to recycle the RWLock logic for the ShmRWLock that's why we
 * keep all relevant logic in this type as static functions
 */
struct OSAL_EXPORT RWLockOps
{
    static bool init(pthread_rwlock_t*,
        const bool process_shared);

    static bool destroy(pthread_rwlock_t*);

    static int_fast8_t lock(
        pthread_rwlock_t*,
        bool write_lock,
        const uint_fast32_t*);

    inline static bool unlock(pthread_rwlock_t*);

    static int_fast8_t handleLockError(const int error,
        const bool write_lock);

    static bool handleUnlockError(const int error);

    static bool isValid(const pthread_rwlock_t *l)
    {
        for( size_t i = 0; i < sizeof(pthread_rwlock_t); i++ ) // BRANCH_COVERAGE_UNREACHABLE
        {
            if( ((const uint8_t*)l)[i] != 0xFF )
                return true;
        }

        return false;
    }

    static void invalidate(pthread_rwlock_t *l)
    {
        ::memset(l, 0xFF, sizeof(pthread_rwlock_t));
    }
};


//! OS handle for rw_lock
struct RWLockHandle
{
    pthread_rwlock_t rwlock;

    bool isValid()
    {
        return RWLockOps::isValid(&rwlock);
    }

    void invalidate()
    {
        return RWLockOps::invalidate(&rwlock);
    }
};

} // end ns osal

#else
#    include <osal/common/RWLockDefs.hxx>
#endif // OSAL_NEED_COMMON_RWLOCK_API

#endif
