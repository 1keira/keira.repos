#ifndef OSAL_POSIX_SHMSPINLOCKDEFS_HXX
#define OSAL_POSIX_SHMSPINLOCKDEFS_HXX

/*
    Copyright e.solutions GmbH
    All rights reserved
    Authors:
        Matthias Gerstner
    $Id: $
*/

#include <osal/SpinLock.hxx>

namespace osal
{

//! OS handle to reference a shared memory spinlock
struct OSAL_EXPORT ShmSpinLockHandle
{
    struct Data
    {
//         pthread_spinlock_t spinlock;
//         bool valid;
    };

    Data *shm;
    bool m_auto_destroy;

    ShmSpinLockHandle() :
        shm(NULL),
        m_auto_destroy(false)
    { }

    ShmSpinLockHandle(volatile void *addr, const bool auto_destroy) :
        shm( (Data*)addr ),
        m_auto_destroy(auto_destroy)
    { }

    bool isValid() const
    {
        return 0;
//         return shm && shm->valid;
    }

    bool autoDestroy() const
    {
        return 0;
//         return m_auto_destroy;
    }

    void invalidate()
    {
//         shm = NULL;
    }
};

} // end ns osal

#endif
