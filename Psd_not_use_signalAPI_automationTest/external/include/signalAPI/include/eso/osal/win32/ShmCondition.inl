/*
    Copyright e.solutions GmbH
    All rights reserved
    Authors:
        Matthias Gerstner
    $Id: $
*/
#ifndef OSAL_WIN32_SHMCONDITION_INL
#define OSAL_WIN32_SHMCONDITION_INL

namespace osal {
    
    inline bool ShmCondition::wait(osal::ShmMutex &p_lock)
    {
        return m_handle.wait(p_lock, NULL) != WAIT_SIGNALED;
    }

    inline int_fast8_t ShmCondition::waitTimeout(osal::ShmMutex &p_lock,
        const osal::AbsTimeT &end_time)
    {
        return m_handle.wait(p_lock, &end_time);
    }

    inline bool ShmCondition::signal()
    {
        return m_handle.signal(false);
    }

    inline bool ShmCondition::signalAll()
    {
        return m_handle.signal(true);
    }

    inline bool ShmCondition::destroy(void *shm_addr)
    {
        ShmConditionHandle::Data &data =
            *((ShmConditionHandle::Data*)shm_addr);

        data.event_name[0] = '\0';

        return false;
    }

} // end ns osal

#endif
