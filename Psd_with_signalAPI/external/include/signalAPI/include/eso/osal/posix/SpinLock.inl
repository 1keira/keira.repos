/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#include <errno.h>
#include <osal/SysError.hxx>

namespace osal {

    inline bool SpinLockOps::init(pthread_spinlock_t *spin, const bool process_shared)
    {
        int res;

        if( (res = ::pthread_spin_init( spin,
            process_shared ? PTHREAD_PROCESS_SHARED :
                PTHREAD_PROCESS_PRIVATE )) )
        {
            errno = res;

            switch(res)
            {
            case EAGAIN:
                osal_raise( SysError, SYSTEM_RESSOURCES_EXHAUSTED );
                osal_reraise( SpinLock::Error, SpinLock::CREATE_FAILED );
                break;
            case ENOMEM:
                osal_raise( SysError, OUT_OF_MEMORY );
                osal_reraise( SpinLock::Error, SpinLock::CREATE_FAILED );
                break;
            // the spin is already in use somewhere
            case EBUSY:
            default:
                osal_try_reraise( SpinLock::Error, SpinLock::CREATE_FAILED );
            }

            return true;
        }

        return false;
    }

    inline bool SpinLockOps::destroy(pthread_spinlock_t *spin)
    {
        int res;

        if( (res = ::pthread_spin_destroy( spin ) ))
        {
            errno = res;

            switch(res)
            {
            case EBUSY:
                osal_raise( SpinLock::Error,
                    SpinLock::INCONSISTENCY );
                break;
            case EINVAL:
            default:
                osal_raise( SysError, INTEGRITY_ERROR );
                break;
            }

            return true;
        }

        return false;
    }

    inline bool SpinLockOps::lock(pthread_spinlock_t *spin)
    {
        int res;

        if( (res = pthread_spin_lock(spin)) )
        {
            return handleLockError(res);
        }

        return false;
    }

    inline bool SpinLockOps::unlock(pthread_spinlock_t *spin)
    {
        int res;

        if ( ( res = pthread_spin_unlock(spin) ) )
        {
            return handleUnlockError(res);
        }

        return false;
    }

    inline int_fast8_t SpinLockOps::tryLock(pthread_spinlock_t *spin)
    {
        int res;

        if( ( res = pthread_spin_trylock(spin)) )
        {
            return handleTryLockError(res);
        }

        return SpinLock::TRY_LOCK_SUCCESS;
    }

    inline SpinLock::SpinLock()
    {
        if( ! SpinLockOps::init( &m_handle.spin, false ) )
        {
            m_handle.valid = true;
        }
    }

    inline SpinLock::~SpinLock()
    {
        if( SpinLockOps::destroy( &m_handle.spin ) )
        {
            IPL_WARN("error destroying spin lock!");
            ipl_error.ack();
        }

        m_handle.valid = false;
    }

    inline bool SpinLock::lock() const
    {
        return SpinLockOps::lock( &m_handle.spin );
    }

    inline bool SpinLock::unlock() const
    {
        return SpinLockOps::unlock( &m_handle.spin );
    }

    inline int_fast8_t SpinLock::tryLock() const
    {
        return SpinLockOps::tryLock( &m_handle.spin );
    }

} // end ns osal
