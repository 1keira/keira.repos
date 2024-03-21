/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

// common implementation of RWLOCK API, if needed
#ifdef OSAL_NEED_COMMON_RWLOCK_API

namespace osal
{
    
inline bool ShmRWLock::destroy(void *shm_addr)
{
    bool ret = false;

    Data *rw_shm_data = (Data*)shm_addr;

    ret |= ShmMutex::destroy( & rw_shm_data->lock );
    ret |= ShmCondition::destroy( & rw_shm_data->readers_cond );
    ret |= ShmCondition::destroy( & rw_shm_data->writers_cond );

    return ret;
}

inline int_fast8_t ShmRWLock::readLock(
    const uint_fast32_t p_timeout) const
{
    return m_handle.readLock( p_timeout ? &p_timeout : NULL );
}

inline int_fast8_t ShmRWLock::writeLock(
    const uint_fast32_t p_timeout) const
{
    return m_handle.writeLock( p_timeout ? &p_timeout : NULL );
}

inline int_fast8_t ShmRWLock::tryReadLock(void) const
{
    uint_fast32_t to = 0;
    return m_handle.readLock( &to );
}

inline int_fast8_t ShmRWLock::tryWriteLock(void) const
{
    uint_fast32_t to = 0;
    return m_handle.writeLock( &to );
}

inline bool ShmRWLock::unlock(void) const
{
    return m_handle.unlock();
}

} // end namespace

#endif
