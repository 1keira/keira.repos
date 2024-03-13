/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifdef OSAL_NEED_COMMON_RWLOCK_API

namespace osal
{

inline RWLock::RWLock()
{
    // nothing special to do, initialization is done by members of
    // m_handle
}

inline RWLock::~RWLock()
{
    // nothing special to do, cleanup is done by destructors of
    // members of m_handle
}
    
inline int_fast8_t RWLock::readLock(
    const uint_fast32_t p_timeout) const
{
    return m_handle.readLock( p_timeout ? &p_timeout : NULL );
}

inline int_fast8_t RWLock::writeLock(
    const uint_fast32_t p_timeout) const
{
    return m_handle.writeLock( p_timeout ? &p_timeout : NULL );
}

inline int_fast8_t RWLock::tryReadLock(void) const
{
    uint_fast32_t to = 0;
    return m_handle.readLock( &to );
}

inline int_fast8_t RWLock::tryWriteLock(void) const
{
    uint_fast32_t to = 0;
    return m_handle.writeLock( &to );
}

inline bool RWLock::unlock(void) const
{
    return m_handle.unlock();
}

} // end namespace

#endif
