#ifndef OSAL_POSIX_SHMMUTEXDEFS_HXX
#define OSAL_POSIX_SHMMUTEXDEFS_HXX

/*
    Copyright e.solutions GmbH
    All rights reserved
    Authors:
        Matthias Gerstner
    $Id: $
*/

#include <osal/Mutex.hxx>

namespace osal
{

//! OS handle to reference a shared memory mutex
struct OSAL_EXPORT ShmMutexHandle
{
//     typedef pthread_mutex_t Data;
    typedef int Data;
//     pthread_mutex_t *shm_mutex;
//     bool m_auto_destroy;

    ShmMutexHandle()/* :
        shm_mutex(NULL),
        m_auto_destroy(false)*/
    { }

    ShmMutexHandle(void *addr, const bool auto_destroy)/* :
        shm_mutex( (pthread_mutex_t*)addr ),
        m_auto_destroy(auto_destroy)*/
    { }

    bool isValid() const
    {
        return 0;
//         return shm_mutex && MutexOps::isValid(shm_mutex);
    }

    bool autoDestroy() const
    {
        return 0;
//         return m_auto_destroy;
    }

    void invalidate()
    {
//         shm_mutex = NULL;
    }
};

} // end ns osal

#endif
