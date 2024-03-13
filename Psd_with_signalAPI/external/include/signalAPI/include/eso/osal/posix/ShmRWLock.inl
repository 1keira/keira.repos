/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

namespace osal {
    
    inline bool ShmRWLock::attach(
        void *shm_addr,
        const bool initialize,
        const bool auto_destroy)
    {
        if( this->isValid() && this->close() ) // BRANCH_COVERAGE_UNTESTABLE
        {
            IPL_WARN("error closing SHM rwlock");
        }

        m_handle = ShmRWLockHandle(shm_addr, auto_destroy);

        if( initialize && RWLockOps::init( m_handle.shm_rwlock, true ) ) // BRANCH_COVERAGE_UNTESTABLE
        {
            m_handle.invalidate();
            return true;
        }
        else if( ! initialize && !this->isValid() )
        {
            ipl_raise( Error, RWLock::CREATE_FAILED,
                "there seems to be no valid ShmRWLock at the given location" );
            return true;
        }

        return false;
    }

    inline bool ShmRWLock::close()
    {
        if( ! this->isValid() )
            return false;

        bool ret = false;

        if( m_handle.autoDestroy() && destroy( m_handle.shm_rwlock) ) // BRANCH_COVERAGE_UNTESTABLE
        {
            ret = true;
        }

        m_handle.invalidate();

        return ret;
    }

    inline bool ShmRWLock::destroy(void *shm_addr)
    {
        const bool ret = RWLockOps::destroy(
            (pthread_rwlock_t*)shm_addr );

        RWLockOps::invalidate( (pthread_rwlock_t*)shm_addr );

        return ret;
    }

    inline int_fast8_t ShmRWLock::readLock(
        const uint_fast32_t p_timeout_ms) const
    {
        return RWLockOps::lock(
            m_handle.shm_rwlock,
            false,
            p_timeout_ms? &p_timeout_ms : NULL);
    }

    inline int_fast8_t ShmRWLock::writeLock(
        const uint_fast32_t p_timeout_ms) const
    {
        return RWLockOps::lock(
            m_handle.shm_rwlock,
            true,
            p_timeout_ms? &p_timeout_ms : NULL);
    }

    inline int_fast8_t ShmRWLock::tryReadLock(void) const
    {
        const uint_fast32_t timeout(0);

        return RWLockOps::lock(
            m_handle.shm_rwlock,
            false,
            &timeout);
    }

    inline int_fast8_t ShmRWLock::tryWriteLock(void) const
    {
        const uint_fast32_t timeout(0);

        return RWLockOps::lock(
            m_handle.shm_rwlock,
            true,
            &timeout);
    }

    inline bool ShmRWLock::unlock() const
    {
        return RWLockOps::unlock(m_handle.shm_rwlock);
    }

} // end ns osal
