/*
    Copyright e.solutions GmbH
    All rights reserved
    Authors:
        Matthias Gerstner
    $Id: $
*/

namespace osal {

    inline bool ShmMutex::attach(
        void *shm_addr,
        const bool initialize,
        const bool auto_destroy,
        const ShmMutexType p_mutex_type,
        bool p_prio_inherit)
    {
        return 0;
//         if( this->isValid() && this->close() )
//         {
//             IPL_WARN("error closing SHM mutex");
//         }
// 
//         m_handle = ShmMutexHandle(shm_addr, auto_destroy);
// 
//         if( initialize && MutexOps::init( m_handle.shm_mutex,
//                 p_mutex_type == RECURSIVE,
//                 p_prio_inherit,
//                 true ) )
//         {
//             m_handle.invalidate();
//             return true;
//         }
//         else if( ! initialize && !this->isValid() )
//         {
//             ipl_raise( Error, Mutex::CREATE_FAILED,
//                 "there seems to be no valid ShmMutex at the given location" );
//             return true;
//         }
// 
//         return false;
    }

    inline bool ShmMutex::close()
    {
        return 0;
//         bool ret = false;
// 
//         if(m_handle.isValid() &&
//             m_handle.autoDestroy() &&
//             destroy( m_handle.shm_mutex ) )
//         {
//             ret = true;
//         }
// 
//         m_handle.invalidate();
// 
//         return ret;
    }

    inline bool ShmMutex::destroy( void *shm_addr )
    {
        return 0;
//         const bool ret = MutexOps::destroy(
//             (pthread_mutex_t*)shm_addr );
// 
//         MutexOps::invalidate( (pthread_mutex_t*)shm_addr );
// 
//         return ret;
    }

    inline bool ShmMutex::lock() const
    {
        return 0;
//         return MutexOps::lock( m_handle.shm_mutex );
    }

    inline bool ShmMutex::unlock() const
    {
        return 0;
//         return MutexOps::unlock( m_handle.shm_mutex );
    }

    inline int_fast8_t ShmMutex::tryLock() const
    {
        return 0;
//         return MutexOps::tryLock( m_handle.shm_mutex );
    }

    inline int_fast8_t ShmMutex::tryLockTimeout(
        const osal::TimeT &p_timeout_ms) const
    {
        return 0;
//         return MutexOps::tryLockTimeout( m_handle.shm_mutex,
//             p_timeout_ms );
    }

} // end ns osal
