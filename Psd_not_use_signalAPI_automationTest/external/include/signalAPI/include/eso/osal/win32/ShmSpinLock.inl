/*
    Copyright e.solutions GmbH
    All rights reserved
    Authors:
        Matthias Gerstner
    $Id: $
*/

namespace osal
{

    inline bool ShmSpinLock::attach(volatile void *shm_addr,
        const bool initialize,
        const bool auto_destroy)
    {
        if( this->isValid() && this->close() )
        {
            IPL_WARN("error closing shm spinlock");
        }

        return m_handle.setup(shm_addr, initialize, auto_destroy);
    }

    inline bool ShmSpinLock::close()
    {
        return m_handle.mutex.close();
    }

    inline bool ShmSpinLock::destroy(volatile void *shm_addr)
    {
        return ShmMutex::destroy((void*)shm_addr);
    }

    inline bool ShmSpinLock::lock() const
    {
        return m_handle.mutex.lock();
    }

    inline bool ShmSpinLock::unlock() const
    {
        return m_handle.mutex.unlock();
    }

    inline int_fast8_t ShmSpinLock::tryLock() const
    {
        return m_handle.mutex.tryLock();
    }

} // end ns osal
