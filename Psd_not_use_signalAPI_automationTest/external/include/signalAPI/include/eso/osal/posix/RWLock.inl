/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

namespace osal {

    inline RWLock::RWLock()
    {
        RWLockOps::init(&m_handle.rwlock,
            false);
    }

    inline RWLock::~RWLock()
    {
        if( RWLockOps::destroy(&m_handle.rwlock) ) // BRANCH_COVERAGE_UNTESTABLE
        {
            IPL_WARN("Error destroying RWLock!");
            ipl_error.ack();
        }
    }

    inline bool RWLockOps::unlock(pthread_rwlock_t *l)
    {
        int ret;

        if ((ret = pthread_rwlock_unlock(l))) // BRANCH_COVERAGE_UNTESTABLE
        {
            return handleUnlockError(ret);
        }

        return false;
    }

    inline int_fast8_t RWLock::readLock(const uint_fast32_t p_timeout_ms) const
    {
        return RWLockOps::lock(&m_handle.rwlock, false,
                                p_timeout_ms ? &p_timeout_ms : NULL );
    }

    inline int_fast8_t RWLock::writeLock(const uint_fast32_t p_timeout_ms) const
    {
        return RWLockOps::lock(&m_handle.rwlock, true,
                            p_timeout_ms? &p_timeout_ms : NULL);
    }

    inline int_fast8_t RWLock::tryReadLock(void) const
    {
        const uint_fast32_t timeout(0);

        return RWLockOps::lock(&m_handle.rwlock, false,
                            &timeout);
    }

    inline int_fast8_t RWLock::tryWriteLock(void) const
    {
        const uint_fast32_t timeout(0);

        return RWLockOps::lock(&m_handle.rwlock, true,
                            &timeout);
    }

    inline bool RWLock::unlock(void) const
    {
        return RWLockOps::unlock(&m_handle.rwlock);
    }

} // end ns osal
