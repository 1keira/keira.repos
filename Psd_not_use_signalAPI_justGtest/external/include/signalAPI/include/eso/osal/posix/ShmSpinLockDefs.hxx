/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_POSIX_SHMSPINLOCKDEFS_HXX
#define OSAL_POSIX_SHMSPINLOCKDEFS_HXX

#include <osal/SpinLock.hxx>

namespace osal
{

//! OS handle to reference a shared memory spinlock
struct OSAL_EXPORT ShmSpinLockHandle
{
    struct Data
    {
        pthread_spinlock_t spinlock;
        bool valid;
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
        return shm && shm->valid;
    }

    bool autoDestroy() const
    {
        return m_auto_destroy;
    }

    void invalidate()
    {
        shm = NULL;
    }
};

} // end ns osal

#endif
