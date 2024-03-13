/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_POSIX_SHMRWLOCKDEFS_HXX
#define OSAL_POSIX_SHMRWLOCKDEFS_HXX

#include <osal/RWLock.hxx>

namespace osal
{

//! OS handle to reference a shared memory rw lock
struct OSAL_EXPORT ShmRWLockHandle
{
    typedef pthread_rwlock_t Data;
    pthread_rwlock_t *shm_rwlock;
    bool m_auto_destroy;

    ShmRWLockHandle() :
        shm_rwlock(NULL),
        m_auto_destroy(false)
    { }

    ShmRWLockHandle(void *addr, const bool auto_destroy) :
        shm_rwlock( (pthread_rwlock_t*)addr ),
        m_auto_destroy(auto_destroy)
    { }

    bool isValid() const
    {
        return shm_rwlock && RWLockOps::isValid(shm_rwlock);
    }

    bool autoDestroy() const
    {
        return m_auto_destroy;
    }

    void invalidate()
    {
        shm_rwlock = NULL;
    }
};

} // end ns osal

#endif
