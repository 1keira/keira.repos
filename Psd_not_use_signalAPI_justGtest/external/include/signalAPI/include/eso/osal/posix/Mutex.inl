/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

namespace osal {

    inline Mutex::Mutex(const MutexType p_mutex_type, const bool p_prio_inherit) :
        m_handle()
    {
        MutexOps::init(&m_handle.mutex,
            p_mutex_type == RECURSIVE,
            p_prio_inherit,
            false);
    }

    inline Mutex::~Mutex()
    {
        if( m_handle.isValid() && MutexOps::destroy( &m_handle.mutex ) )
        {
            IPL_WARN("Error destroying mutex");
            ipl_error.ack();
        }
    }

    inline bool Mutex::lock() const
    {
        return MutexOps::lock(&m_handle.mutex);
    }

    inline bool Mutex::unlock() const
    {
        return MutexOps::unlock(&m_handle.mutex);
    }

    inline int_fast8_t Mutex::tryLock() const
    {
        return MutexOps::tryLock(&m_handle.mutex);
    }

    inline int_fast8_t Mutex::tryLockTimeout(
        const osal::TimeT &p_timeout_ms) const
    {
        return MutexOps::tryLockTimeout(&m_handle.mutex, p_timeout_ms);
    }

} // end ns osal
