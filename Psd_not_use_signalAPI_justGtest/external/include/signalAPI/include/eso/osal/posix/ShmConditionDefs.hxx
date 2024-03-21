/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_POSIX_SHMCONDITIONDEFS_HXX
#define OSAL_POSIX_SHMCONDITIONDEFS_HXX

#include <osal/Condition.hxx>

namespace osal
{

//! OS handle to reference a shared memory condition
struct OSAL_EXPORT ShmConditionHandle
{
    typedef pthread_cond_t Data;
    pthread_cond_t *shm_cond;
    bool m_auto_destroy;

    ShmConditionHandle() :
        shm_cond(NULL),
        m_auto_destroy(false)
    { }

    ShmConditionHandle(void *addr, const bool auto_destroy) :
        shm_cond( (pthread_cond_t*)addr ),
        m_auto_destroy(auto_destroy)
    { }

    bool isValid() const
    {
        return shm_cond && ConditionOps::isValid(shm_cond);
    }

    bool autoDestroy() const
    {
        return m_auto_destroy;
    }

    void invalidate()
    {
        shm_cond = NULL;
    }
};

} // end ns osal

#endif
