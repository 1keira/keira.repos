/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_COMMON_SHMRWLOCKDEFS_HXX
#define OSAL_COMMON_SHMRWLOCKDEFS_HXX

/*
 *    For the common OSAL impl. of RWLock we simply rely on osal Mutex
 *    and Condition primitives.
 *
 *    This way the RWLock can easily be implemented, providing all
 *    features.
 */

#include <osal/osal_dso.h>
#include <osal/RWLock.hxx>
#include <osal/ShmCondition.hxx>
#include <osal/ShmMutex.hxx>

namespace osal
{

//! OS handle to reference a shared memory mutex
struct OSAL_EXPORT ShmRWLockHandle :
    public RWLockBase<osal::ShmMutex, osal::ShmCondition>
{
    struct Data
    {
        ShmMutex::Data lock;
        ShmCondition::Data readers_cond;
        ShmCondition::Data writers_cond;
        RWLockBase<osal::ShmMutex, osal::ShmCondition>::State state;
    };

    Data *m_shm_data;
    bool m_auto_destroy;

    ShmRWLockHandle() :
        RWLockBase<osal::ShmMutex, osal::ShmCondition>(NULL),
        m_shm_data(NULL),
        m_auto_destroy( false )
    { }

    void setup(void *addr,
        const bool auto_destroy)
    {
        m_state = &((Data*)addr)->state;
        m_shm_data = (Data*)addr;
        m_auto_destroy = auto_destroy;
    }

    bool autoDestroy() const
    {
        return m_auto_destroy;
    }

    // invalidate just this handle
    void invalidate()
    {
        m_shm_data = NULL;
        m_lock.close();
        m_readers.close();
        m_writers.close();
        m_state = NULL;
    }
};

} // end ns

#endif // OCSHMRWLOCKDEFS
