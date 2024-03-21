/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_SPINLOCK_HXX
#define OSAL_SPINLOCK_HXX

#include <ipl_config.h>

#include <common/error/Error.hxx>
#include <common/NonCopyable.hxx>

#include <osal/osal_dso.h>

#if defined IPL_OS_ANDROID
#include "android/SpinLockDefs.hxx"
#elif defined IPL_OS_LINUX || defined IPL_OS_QNX
#include "posix/SpinLockDefs.hxx"
#elif defined IPL_OS_WINPC
#include "win32/SpinLockDefs.hxx"
#elif defined IPL_OS_INTEGRITY
#include "integrity/SpinLockDefs.hxx"
#else
#error "error undefined IPL_OS_ variant"
#endif
#include <osal/osal.hxx>

namespace osal
{

/**
 * \brief
 *    An Inter-Thread Spin Lock Object

 *     A spin lock is a very lightweight utility for synchronizing
 *     access to data between different threads in the same process.
 *
 *     The area of use is, however, much more restricted than that of
 *     an osal::Mutex. A spin lock is, in case of contention for the
 *     lock, not causing the calling thread to go to sleep. Instead if
 *     the lock is already taken the contending thread is doing a busy
 *     wait for the lock.
 *
 *     This causes the lock to be very efficient in case the time locks
 *     are held is very short. Think of something like securing access
 *     to modifying an integer variable, for example. In case the time
 *     the lock is taken is longer or unpredictable (especially if
 *     system calls are involved while holding the lock) then it will
 *     hit performance pretty bad.
 *
 *    Also you have to consider the potential effect on realtime
 *    scheduling. If a thread of high priority is contending for a
 *    spin lock that is currently taken by a thread of low priority
 *    then priority inversion, if not an infinite loop may occur. The
 *    details of this heavily depend on how spin locks are implemented
 *    in OSAL and the operating system respectively.
 *
 *    Spin locks are always binary i.e. the same thread may not lock
 *    it more than once.
 *
 *    Note that while the intention of this facility is not to block
 *    in the event of contention that there is no *gurantee* that
 *    there won't be a blocking call into kernel mode anyway. POSIX
 *    for example doesn't require that, it's only suggesting it. On
 *    Win32 the spin lock can be configured to enter a blocking state
 *    if after a number of spins the lock couldn't be acquired.
 *
 *    On QNX according to documentation a SpinLock is effectively the
 *    same as an osal::Mutex. On Linux there seems to be actually be a
 *    special spin lock involved. On Win32 the SpinLock is a special
 *    variant of an osal::Mutex. It is configured to try and spin for
 *    a configured number of times before giving up and entering
 *    kernel mode for efficient waiting. The number of spin attempts
 *    is a compile time configuration constant of OSAL.
**/
class OSAL_EXPORT SpinLock :
    public ipl::NonCopyable
{
public: // types
    //! return value from tryLock, tryLockTimeout() on success
    static const int_fast8_t TRY_LOCK_SUCCESS = 0;
    //! return value from tryLock, tryLockTimeout() on error
    static const int_fast8_t TRY_LOCK_ERROR = -1;
    //! brief
    //! return value from tryLock, tryLockTimeout() on failure to
    //! acquire the lock
    static const int_fast8_t TRY_LOCK_NOLUCK = 1;

    //! specific mutex error IDs
    enum SpinLockErrors
    {
        CREATE_FAILED = 0,
        LOCK_FAILED,
        UNLOCK_FAILED,
        //! \brief
        //! deadlock occured or invalid lock/unlock sequence
        //! detected
        INCONSISTENCY
    };

    //! SpinLock specific error type
    static ipl::ErrorType Error;
public:

    /**
     * \brief
     *    The only constructor for a SpinLock.

     *     Due to the light-weightiness of spin locks there are no
     *     special options for its construction.
     * \errors
     *    SysError with IDs
     *
     *    - OUT_OF_MEMORY
     *    - SYSTEM_RESSOURCES_EXHAUSTED (not memory, retry
     *    possible)
     *
     *    SpinLock::Error with IDs
     *
     *    - CREATE_FAILED on other errors
     * \errorindicator
     *    via isValid()
     * \note
     *    If the constructor passes without error then all
     *    ressources regarding the spin lock have been allocated
     *    and the object is fully usable.
     *
     *    If an error occurs no ressources should be left
     *    allocated in any circumstance.
    **/
    inline SpinLock();

    /**
     * \brief
     *    Cleans up associated ressources.

     *    May abort in case deallocation of associated ressources
     *    fails.
    **/
    inline virtual ~SpinLock();

    /**
     * \brief
     *    lock the spin lock

     *    This method blocks until the calling thread can aquire
     *    the spinlock. After it successful returns, the caller
     *    owns the spin lock and may safely modify any data
     *    structures protected by it.
     * \post
     *    The spin lock is owned by the calling thread
     * \return
     *    true if an error occured during the operation and thus
     *    the spin lock couldn't be obtained. false on success.
     * \errors
     *    SpinLock::Error with IDs
     *
     *    - INCONSISTENCY: a lock/unlock sequence has been
     *    detected that would have caused the call to block
     *    indefinitely. This is debugging support not available in
     *    production code. If this happens you should go back to
     *    the drawing board :).
     *    - LOCK_FAILED on other errors
     * \errorindicator
     *    via return code
     * \note
     *    In case of an error the lock state should not have
     *    changed. But usually the logic behind the spin lock is
     *    already messed up. Best you can do is getting a new one
     *    or fixing your program...
    **/
    inline bool lock() const;

    /**
     * \brief
     *    Unlock the Spin Lock

     *    A call to this method releases the hold of the spin lock
     *    if it was previously obtained by calling lock().
     * \note
     *    Unlocking a spin lock that was previously obtained by a
     *    different thread or unlocking a spin lock more often
     *    than it was locked by the same thread will result in
     *    undefined behaviour (deadlocks, mostly).
     * \pre
     *    The spin lock was locked by the calling thread.
     * \post
     *    On success the spin lock is no longer owned by the calling
     *    thread
     * \return
     *    true if an error occured while trying to unlock the
     *    spin lock, false otherwise
     * \errors
     *    SpinLock::Error with IDs
     *
     *    - INCONSISTENCY if the spin lock is invalid or not owned
     *    by the calling thread
     *    - UNLOCK_FAILED if some other error occured
     * \errorindicator
     *    via return code
     * \note
     *    In case of an error the lock state should not have
     *    changed. But usually the logic behind the lock is
     *    already messed up. Best you can do is getting a new one
     *    or fixing your program...
    **/
    inline bool unlock() const;

    /**
     * \brief
     *    Try to Aquire a Lock on the Spin Lock

     *    The tryLock function acts basicly similar to the lock()
     *    function. The only difference is that if the spin lock
     *    cannot be currently obtained by the calling thread
     *    (because it is already owned by the thread or by another
     *    thread) the call will not block but return with a return
     *    value of TRY_LOCK_NOLUCK.
     * \return
     *    TRY_LOCK_SUCCESS on successful aquisition of the lock,
     *    TRY_LOCK_NOLUCK if the spin lock couldn't be acquired,
     *    TRY_LOCK_ERROR if an error occured.
     * \post
     *    The same as with lock() if TRY_LOCK_SUCCESS or
     *    TRY_LOCK_ERROR is returned. If TRY_LOCK_NOLUCK is
     *    returned then the spin lock was not obtained and nothing
     *    else will have happened.
     * \see
     *    lock()
     * \errors
     *    The same errors described at lock() are valid here, too.
     * \errorindicator
     *    On error TRY_LOCK_ERROR is returned.
    **/
    inline int_fast8_t tryLock() const;

    //! Returns true if construction succeeded, false otherwise
    bool isValid() const
    { return m_handle.isValid(); }
private: // members
    //! The os spin lock handle
    mutable SpinLockHandle m_handle;
}; // class

} // end namespace

#if defined IPL_OS_ANDROID
#include "android/SpinLock.inl"
#elif defined IPL_OS_LINUX || defined IPL_OS_QNX
#include "posix/SpinLock.inl"
#elif defined IPL_OS_WINPC
#include "win32/SpinLock.inl"
#elif defined IPL_OS_INTEGRITY
#include "integrity/SpinLock.inl"
#else
#error "error undefined IPL_OS_ variant"
#endif

//! a macro that locks a spin lock and on error aborts the program
#define IPL_SPINLOCK_LOCK_OR_ABORT(M) do if( M.lock() ) \
    { IPL_ABORT("error spin-locking"); } while(false)

//! a macro that unlocks a spin lock and on error aborts the program
#define IPL_SPINLOCK_UNLOCK_OR_ABORT(M) do if( M.unlock() )\
    { IPL_ABORT("error spin-unlocking"); } while(false)

#endif /* OSAL_SPINLOCK_HXX */
