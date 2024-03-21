#ifndef OSAL_WIN32_SHMCONDITIONDEFS_HXX
#define OSAL_WIN32_SHMCONDITIONDEFS_HXX

/*
    Copyright e.solutions GmbH
    All rights reserved
    Authors:
        Matthias Gerstner
    $Id: $
*/

// to prevent annoying warnings on WIN32
#include <iplcompiler.h>

#include <iplbase/win32.h>
#include "ConditionBase.hxx"
#include <osal/ShmMutex.hxx>

namespace osal
{

#ifndef OSAL_EXPORT_CONTEXT
extern template class ConditionBase<osal::ShmMutex>;
#endif

//! OS handle to reference a shared memory mutex
struct OSAL_EXPORT ShmConditionHandle :
    public ConditionBase<osal::ShmMutex>
{
    static const size_t EVENT_NAME_LEN = 19;

    struct Data
    {
        wchar_t event_name[EVENT_NAME_LEN];
        osal::ShmMutex::Data mutex;
        ConditionBase::State state;
    };

    Data *m_shm_data;
    bool m_auto_destroy;

    ShmConditionHandle() :
        ConditionBase<osal::ShmMutex>(NULL),
        m_shm_data(NULL),
        m_auto_destroy(false)
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

    bool isValid() const
    {
        return ConditionBase<osal::ShmMutex>::isValid()
            && m_shm_data;
    }

    // invalidate just this handle
    void invalidate()
    {
        m_auto_destroy = false;
        m_shm_data = NULL;
        m_event.close();
        m_counter_lock.close();
        m_state = NULL;
    }
};

} // end ns osal

#endif
