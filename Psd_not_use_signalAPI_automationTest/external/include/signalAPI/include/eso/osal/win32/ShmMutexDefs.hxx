#ifndef OSAL_WIN32_SHMMUTEXDEFS_HXX
#define OSAL_WIN32_SHMMUTEXDEFS_HXX

/*
    Copyright e.solutions GmbH
    All rights reserved
    Authors:
        Matthias Gerstner
    $Id: $
*/

#include <iplbase/win32.h>

namespace osal
{

//! OS handle to reference a shared memory mutex
struct OSAL_EXPORT ShmMutexHandle
{
    static const size_t MUTEX_NAME_LEN=19;

    struct Data
    {
        // for detection of recursive use of binary mutex
        size_t lock_count;
        wchar_t mutex_name[MUTEX_NAME_LEN];
    };

    Data *m_shm_data;
    bool m_auto_destroy;
    bool m_recursive;
    // handle associated with m_shm_data->mutex_name
    HANDLE m_mutex_handle;

    ShmMutexHandle() :
        m_shm_data( NULL ),
        m_auto_destroy( false ),
        m_recursive( false ),
        m_mutex_handle(INVALID_HANDLE_VALUE)
    { }

    ShmMutexHandle(void *addr,
        const bool auto_destroy,
        const bool recursive) :
        m_shm_data( (Data*)addr ),
        m_auto_destroy(auto_destroy),
        m_recursive(recursive),
        m_mutex_handle(INVALID_HANDLE_VALUE)
    { }

    bool isValid() const
    {
        return m_mutex_handle != INVALID_HANDLE_VALUE
            && m_shm_data;
    }

    bool autoDestroy() const
    {
        return m_auto_destroy;
    }

    bool recursive() const
    {
        return m_recursive;
    }

    // invalidate just this handle
    void invalidate()
    {
        m_mutex_handle = INVALID_HANDLE_VALUE;
        m_auto_destroy = false;
        m_shm_data = NULL;
    }
};

} // end ns osal

#endif
