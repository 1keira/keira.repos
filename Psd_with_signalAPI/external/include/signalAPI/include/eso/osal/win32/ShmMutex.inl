/*
    Copyright e.solutions GmbH
    All rights reserved
    Authors:
        Matthias Gerstner
    $Id: $
*/

namespace osal {

    inline bool ShmMutex::destroy(void *shm_addr)
    {
        ShmMutexHandle::Data &data = *((ShmMutexHandle::Data*)shm_addr);

        data.mutex_name[0] = '\0';
        data.lock_count = 0;

        return false;
    }

    inline int_fast8_t ShmMutex::tryLock() const
    {
        return tryLockTimeout(0);
    }

} // end ns osal
