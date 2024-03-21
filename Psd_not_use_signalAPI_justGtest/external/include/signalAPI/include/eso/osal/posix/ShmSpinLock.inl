/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

namespace osal
{

    inline bool ShmSpinLock::close()
    {
        bool ret = false;

        if( m_handle.autoDestroy() )
        {
            if( destroy( &(m_handle.shm)->spinlock ) )
            {
                ret = true;
            }

            (m_handle.shm)->valid = false;
        }

        m_handle.invalidate();

        return ret;
    }

    inline bool ShmSpinLock::attach(
        volatile void *shm_addr,
        const bool initialize,
        const bool auto_destroy)
    {
        if( this->isValid() && this->close() )
        {
            IPL_WARN("error closing SHM mutex");
        }

        m_handle = ShmSpinLockHandle(shm_addr, auto_destroy);

        if( initialize && SpinLockOps::init(
                &(m_handle.shm)->spinlock,
                true ) )
        {
            m_handle.invalidate();
        }
        else if( initialize )
        {
            (m_handle.shm)->valid = true;
        }
        else if( ! initialize && ! this->isValid() )
        {
            ipl_raise( Error,
                SpinLock::CREATE_FAILED,
                "there seems to be no valid ShmSpinLock at the "
                "given location" );
        }

        return (m_handle.shm)->valid;
    }

    inline bool ShmSpinLock::destroy( volatile void *shm_addr )
    {
        return SpinLockOps::destroy( (pthread_spinlock_t*)shm_addr );
    }

    inline bool ShmSpinLock::lock() const
    {
        return SpinLockOps::lock( &(m_handle.shm)->spinlock );
    }

    inline bool ShmSpinLock::unlock() const
    {
        return SpinLockOps::unlock( &(m_handle.shm)->spinlock );
    }

    inline int_fast8_t ShmSpinLock::tryLock() const
    {
        return SpinLockOps::tryLock( &(m_handle.shm)->spinlock );
    }

} // end ns osal
