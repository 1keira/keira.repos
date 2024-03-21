/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_RWLOCKGUARD_HXX
#define UTIL_RWLOCKGUARD_HXX

#include <ipl_config.h>
#include <common/ScopeGuard.hxx>
#include <osal/RWLock.hxx>

namespace util
{

typedef bool(osal::RWLock::*rwlock_release)(void) const;

/**
    \brief
        This is a specialized ScopeGuard for RWLocks that eases the handling for this
        special case that occurs rather often in the code.
**/
class RWLockGuard :
        public ipl::ScopeGuard< const osal::RWLock, rwlock_release>
{
public:
    /**
     *    \brief
     *        This constructor allows for easy usage of theScopeGuard
     *        functionality with osal::RWLock objects. The release function
     *        is automatically chosen to be the unlock function of the
     *        osal::RWLock. The osal::Mutex will also automatically be locked.
     *
     *    \param
     *        p_mutex A reference to a osal::RWLock object that is to be locked
     *        and unlocked upon destruction of this RWLockGuard object.
     **/
    RWLockGuard( const osal::RWLock& p_mutex, bool p_lock_for_write) IPL_NOEXCEPT :
                ipl::ScopeGuard< const osal::RWLock, rwlock_release >
                    (p_mutex, & osal::RWLock::unlock)
    {
        if (p_lock_for_write && p_mutex.writeLock() )
        {
            return;
        }
        else if( !p_lock_for_write && p_mutex.readLock())
        {
            return;
        }

        m_valid = true;
    }
private:
};

} // end namespace

#endif
