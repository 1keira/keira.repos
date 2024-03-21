/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_POSIX_SPINLOCKDEFS_HXX
#define OSAL_POSIX_SPINLOCKDEFS_HXX

#include <pthread.h>
#include <string.h>

#include <common/streams/iostream.hxx>

namespace osal
{

/*
 * we want to recycle the spinlock logic for ShmSpinLock on POSIX
 *
 * that is why we have all relevant logic as static functions in
 * SpinLockOps
 */

struct OSAL_EXPORT SpinLockOps
{
    inline static bool init(pthread_spinlock_t*,
        const bool process_shared);

    inline static bool destroy(pthread_spinlock_t*);

    inline static bool lock(pthread_spinlock_t *);

    inline static bool unlock(pthread_spinlock_t *);

    inline static int_fast8_t tryLock(pthread_spinlock_t *);

    static bool handleLockError(const int error);
    static int_fast8_t handleTryLockError(const int error);
    static bool handleUnlockError(const int error);
};

//! OS handle to reference a posix spinlock
struct OSAL_EXPORT SpinLockHandle
{
    pthread_spinlock_t spin;
    bool valid;

    SpinLockHandle() :
        valid(false)
    { }

    bool isValid() const
    {
        return valid;
    }

    void invalidate()
    {
        valid = false;
    }
};

} // end ns osal

#endif
