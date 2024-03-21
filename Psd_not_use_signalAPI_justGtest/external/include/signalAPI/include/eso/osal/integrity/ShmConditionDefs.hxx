#ifndef OSAL_POSIX_SHMCONDITIONDEFS_HXX
#define OSAL_POSIX_SHMCONDITIONDEFS_HXX

/*
    Copyright e.solutions GmbH
    All rights reserved
    Authors:
        Matthias Gerstner
    $Id: $
*/

// #include <osal/Condition.hxx>

namespace osal
{

//! OS handle to reference a shared memory condition
struct OSAL_EXPORT ShmConditionHandle
{
//     typedef pthread_cond_t Data;
    typedef int Data;
//     pthread_cond_t *shm_cond;
//     bool m_auto_destroy;

    ShmConditionHandle()/*: shm_cond(NULL), m_auto_destroy(false)*/ {}

    ShmConditionHandle(void *addr, const bool auto_destroy)/*:
        shm_cond( (pthread_cond_t*)addr ),
        m_auto_destroy(auto_destroy)*/
    {}

    bool isValid() const
    {
        return 0;
//         return shm_cond && ConditionOps::isValid(shm_cond);
    }

    bool autoDestroy() const
    {
        return 0;
//         return m_auto_destroy;
    }

    void invalidate()
    {
//         shm_cond = NULL;
    }
};

} // end ns osal

#endif
