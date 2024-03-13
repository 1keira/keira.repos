/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_MUTEXGUARD_HXX
#define UTIL_MUTEXGUARD_HXX

#include <ipl_config.h>
#include <common/ScopeGuard.hxx>
#include <osal/Mutex.hxx>

namespace util
{

typedef bool(osal::Mutex::*mutex_func)(void) const;

/**
 * \brief
 *     This is a specialized ScopeGuard for mutexes that eases the
 *     handling for this special case that occurs rather often in the
 *     code

 *     Usage:
 *
 *     // here we have a brand new, unlocked mutex
 *     osal::Mutex my_mutex;
 *     {
 *         MutexGuard my_mutex_guard(my_mutex);
 *         // my_mutex is already locked now, nothing else to do
 *         // ...
 *         // do your work, the lock will be released at the end of
 *         // the current sope
 *     }
 *     // lock is released now
 * \see
 *     ipl::ScopeGuard
**/
class MutexGuard :
        public ipl::ScopeGuard< const osal::Mutex, mutex_func >
{
public:
    /**
     * \brief
     *     This constructor allows for easy usage of theScopeGuard
     *     functionality with osal::Mutex objects. The release
     *     function is automatically chosen to be the unlock
     *     function of the osal::Mutex. The osal::Mutex will also
     *     automatically be locked.
     *
     * \param
     *     p_mutex A reference to a osal::Mutex object that is to
     *     be locked and unlocked upon destruction of this
     *     MutexGuard object.
     **/
    MutexGuard( const osal::Mutex& p_mutex) IPL_NOEXCEPT :
        ipl::ScopeGuard< const osal::Mutex, mutex_func >(
            p_mutex,
            &osal::Mutex::unlock)
    {
        if( p_mutex.lock() )
        {
            return;
        }

        m_valid = true;
    }


};

/**
 * \brief
 *     The inversed logic of a MutexGuard

 *     Does the very same as a MutexGuard but it unlocks the mutex in
 *     the constructor and locks it in the destructor
 **/
class MutexGuardInverse :
        public ipl::ScopeGuard< const osal::Mutex, mutex_func >
{
public:
    MutexGuardInverse( const osal::Mutex& p_mutex) IPL_NOEXCEPT :
        ipl::ScopeGuard< const osal::Mutex, mutex_func >(
            p_mutex,
            &osal::Mutex::lock)
    {
        if( p_mutex.unlock() )
        {
            return;
        }

        m_valid = true;
    }
};

} // end namespace

#endif
