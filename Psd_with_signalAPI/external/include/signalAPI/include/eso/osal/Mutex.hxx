/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_MUTEX_HXX
#define OSAL_MUTEX_HXX

#include <ipl_config.h>

#include <common/stdint.h>
#include <common/error/Error.hxx>
#include <common/NonCopyable.hxx>
#include <osal/osal_dso.h>

#ifdef USE_THREADSAFE_IN_OSAL
#include <threadsafe/Mutex.hxx>
#endif

#if defined IPL_OS_POSIX
#    include "posix/MutexDefs.hxx"
#elif defined IPL_OS_WINPC
#    include "win32/MutexDefs.hxx"
#elif defined IPL_OS_INTEGRITY
/* we need no steenking defs */
#else
#    error "error undefined IPL_OS_ variant"
#endif

#include <osal/osal.hxx>
#include <osal/SysError.hxx>

namespace osal
{

/**
 * \brief
 *    An Inter-Thread Mutex Object

 *    A mutex is a synchronization mechanism between threads in the
 *    same process. Some also like to call it a critical section. It
 *    is usually utilized to protect certain operations from parallel
 *    access between several threads.
 *
 *    A mutex is the usual choice for synchronization within the same
 *    process. It is fast as long as there is not contention. System
 *    calls are only performed in the contention case. The contention
 *    case is thereby efficiently handled by the kernel as opposed to
 *    osal::SpinLock that performs a busy wait in the contention case.
 * \note
 *    On some systems that support it there will be debugging support
 *    from the native mutex API (only for BINARY mutex type). This
 *    means that deadlocks or invalid mutex accesses (like unlocking
 *    too often) won't result in actual deadlocks but will issue an
 *    error. This class utilizes this facilities as far as possible
 *    and enables the debugging features for debug builds. Debugging
 *    support will be enabled when the IPL_DEBUG preprocessor variable
 *    is defined.
**/
class OSAL_EXPORT Mutex :
    public ipl::NonCopyable
{
public: // types

     //! \brief Used to select the type of mutex
    enum MutexType
    {
        //! \brief
        //!    A binary mutex can only be locked once. Any
        //!    additional attempt to lock will block unless
        //!    unlock is called by the original locker.
        //!
        //!    An attempt to lock the mutex twice by the same
        //!    thread results in undefined behaviour when using
        //!    BINARY mutex types.
        //! \note
        //!    On some systems the BINARY mutex type supports
        //!    additional debug semantics that are enabled if
        //!    IPL_DEBUG is defined.
        BINARY,
        //! \brief
        //!    a recursive mutex may be locked more than once
        //!    but only by the same thread. If another
        //!    thread tries to lock the mutex it will be blocked.
        RECURSIVE
    };

    //! \brief
    //! because osal::Condition needs access to the internal Mutex
    //! handle
    friend class Condition;

    //! specific mutex error IDs
    enum MutexErrors
    {
        CREATE_FAILED = 0,
        LOCK_FAILED,
        UNLOCK_FAILED,
        //! \brief
        //! deadlock occured or invalid lock/unlock sequence
        //! detected
        INCONSISTENCY
    };

    //! Mutex specific error type
    static ipl::ErrorType Error;

    //! return value from tryLock, tryLockTimeout() on success
    static const int_fast8_t TRY_LOCK_SUCCESS = 0;
    //! return value from tryLock, tryLockTimeout() on error
    static const int_fast8_t TRY_LOCK_ERROR = -1;
    //! brief
    //! return value from tryLock, tryLockTimeout() on failure to
    //! acquire the lock
    static const int_fast8_t TRY_LOCK_NOLUCK = 1;
public:

    /**
     * \brief
     *    The only constructor for a Mutex.

     *    The default mutex type is BINARY. It is safer than
     *    allowing recursive mutexes by default as recursive
     *    mutexes support the lazy programmer and may result in
     *    code that isn't cleanly structured to reflect the logic
     *    of the participating threads.
     *
     *    On some systems the RECURSIVE type is the native default
     *    type. So take note of this changed behaviour. If you
     *    choose a recursive mutex please think about, if you
     *    really need it.
     *
     *    If \c p_prio_inherit is set to \c true then priority
     *    inheritance is enabled for this mutex. This means if
     *    realtime priorities are in effect for any thread that
     *    tries to acquire the lock then the priority inheritance
     *    protocol will be used. This causes a lower priority
     *    thread that currently owns the mutex to get the priority
     *    of a higher priority thread if the latter thread tries
     *    to lock the mutex. This feature should only be used with
     *    care! It decreases portability which is the case with
     *    all realtime related features. Also this feature is
     *    currently only available for POSIX compatible OS that
     *    implement the realtime extension appropriately. On
     *    WinCE Mutexes are *always* implementing priority
     *    inheritance instead.
     * \errors
     *    SysError with IDs
     *
     *    - OUT_OF_MEMORY
     *    - SYSTEM_RESSOURCES_EXHAUSTED (not memory, retry
     *    possible)
     *
     *    Mutex::Error with IDs
     *
     *    - CREATE_FAILED on other errors
     * \errorindicator
     *    via isValid()
     * \note
     *    If the constructor passes without error then all
     *    ressources regarding the Mutex have been allocated and
     *    the object is fully usable.
     *
     *    If an error occurs no ressources should be left
     *    allocated in any circumstance.
    **/
    inline Mutex(const MutexType p_mutex_type = BINARY,
        const bool p_prio_inherit = false);

    /**
     * \brief
     *    Cleans up associated ressources.

     *    May abort in case deallocation of associated ressources
     *    fails.
     * \note
     *     This is kept non-virtual to avoid increase of object
     *     size. It is improbable that anybody will inherit from
     *     Mutex.
    **/
    inline /*virtual*/ ~Mutex();

    /**
     * \brief
     *    lock the mutex

     *    This method blocks until the calling thread can aquire
     *    the mutex. After it successfulreturns the caller owns
     *    the mutex and may safely modify any data structures
     *    protected by it.
     *    If the MutexType is RECURSIVE then the lock call will
     *    succeed also if the calling thread already owns the
     *    mutex.
     * \post
     *    The mutex is owned by the calling thread (or the lock
     *    count is incremented for the calling thread in case of a
     *    RECURSIVE mutex type).
     * \return
     *    true if an error occured during the operation and thus
     *    the mutex couldn't be obtained. false on success.
     * \errors
     *    Mutex::Error with IDs
     *
     *    - INCONSISTENCY: a lock/unlock sequence has been
     *    detected that would have caused the call to block
     *    indefinitely. This is debugging support not available in
     *    production code. If this happens you should go back to
     *    the drawing board :).
     *    - LOCK_FAILED on other errors which can be: Maximum lock
     *    count for a recursive mutex has been reached.
     * \errorindicator
     *    via return code
     * \note
     *    In case of an error the mutex state should not have
     *    changed. But usually the logic behind the mutex is
     *    already messed up. Best you can do is getting a new one
     *    or fixing your program...
    **/
    inline bool lock() const;

    /**
     * \brief
     *    unlock the mutex

     *    A call to this method releases the hold of the mutex if
     *    it was previously obtained by calling lock().
     * \note
     *    Unlocking a mutex that was previously obtained by a
     *    different thread or unlocking a mutex more often than it
     *    was locked by the same thread will result in undefined
     *    behaviour (deadlocks, mostly).
     * \pre
     *    The mutex was locked at least one time by the calling
     *    thread.
     * \post
     *    On success the mutex is no longer owned by the calling
     *    thread (or the lock count is decreased for the calling
     *    thread in case of a RECURSIVE mutex type).
     * \return
     *    true if an error occured while trying to unlock the
     *    mutex, false otherwise
     * \errors
     *    Mutex::Error with IDs
     *
     *    - INCONSISTENCY if the mutex is invalid or not owned by
     *    the calling thread (occurs in debug mode only)
     *    - UNLOCK_FAILED if some other error occured
     * \errorindicator
     *    via return code
     * \note
     *    In case of an error the mutex state should not have
     *    changed. But usually the logic behind the mutex is
     *    already messed up. Best you can do is getting a new one
     *    or fixing your program...
    **/
    inline bool unlock() const;

    /**
     * \brief
     *    try to aquire a lock on the mutex

     *    the tryLock function acts basicly similar to the lock().
     *    The only difference is that if the mutex cannot be
     *    currently obtained by the calling thread (because it is
     *    already owned by the thread or by another thread) the
     *    call will not block but return with a return value of
     *    false.
     * \return
     *    zero/TRY_LOCK_SUCCESS on successful aquisition of the
     *    lock, > 0 / TRY_LOCK_NOLUCK if the mutex couldn't be
     *    acquired, < 0 / TRY_LOCK_NOLUCK if an error occured.
     * \post
     *    The same as with lock() if TRY_LOCK_SUCCESS or
     *    TRY_LOCK_ERROR is returned.
     *    If TRY_LOCK_NOLUCK is returned then the mutex was not
     *    obtained (or the lock count wasn't increased in case of
     *    a RECURSIVE mutex type) and nothing else will have
     *    happened.
     * \see
     *    lock()
     * \errors
     *    The same errors described at lock() are valid here, too.
     * \errorindicator
     *    On error < 0 / TRY_LOCK_ERROR is returned.
    **/
    inline int_fast8_t tryLock() const;

    /**
     * \brief
     *    try to aquire a lock for the given number of miliseconds

     *    behaviour is just like tryLock() with the difference
     *    that it will attempt to obtain the mutex for the given
     *    number of milliseconds. If the mutex can be obtained
     *    before the timeout occurs then the call returns and the
     *    mutex is acquired. If the timeout elapses without the
     *    mutex becoming available then the call returns and the
     *    mutex is not obtained.
     *
     *    The clock used for implementing the timeout is monotonic
     *    only on QNX starting from veresion 6.5.0 and on WIN32.
     *    On POSIX in general the clock used for this function is
     *    based on the realtime clock and thus can jump.
     * \warning
     *    on some platforms (i.e. POSIX compatible ones) this maps
     *    to a real API call that ensures efficient implementation
     *    and that the mutex will be acquired as soon as it
     *    becomes available. On other platforms (i.e. WIN32) this
     *    function tries to obtain the mutex immediatly and if it
     *    isn't available then it tries acquiring the mutex again
     *    after (and only after) the given number of miliseconds.
     *    Thus behaviour may differ between platforms in this
     *    respect.
     * \param
     *    p_timeout_ms The timeout in milliseconds before trying
     *    to acquire the mutex is given up.
     * \return
     *    zero / TRY_LOCK_SUCCESS if the mutex could be acquired,
     *    > 0 / TRY_LOCK_NOLUCK if the timeout elapsed without the
     *    mutex being acquired, < 0 / TRY_LOCK_ERROR if an error
     *    occured.
     * \see
     *    tryLock()
     * \errors
     *    The errors described at lock() are valid here, too plus
     *    the following ID:
     *
     *    - LOCK_FAILED now also if an error regarding the time
     *    clock source occured.
     * \errorindicator
     *    On error < 0 / TRY_LOCK_ERROR is returned.
     **/
    inline int_fast8_t tryLockTimeout(
        const osal::TimeT &p_timeout_ms) const;

    //! Returns true if construction succeeded, false otherwise
    bool isValid() const
#ifdef USE_THREADSAFE_IN_OSAL
    { return true; }
#else
    { return m_handle.isValid(); }
#endif

private: // members
#ifdef USE_THREADSAFE_IN_OSAL
    mutable /* some idiot has declared (un)lock as const */ threadsafe::Mutex mutex;
#else
    //! The os mutex handle
    mutable MutexHandle m_handle;
#endif
}; // class Mutex

} // end namespace

#ifdef USE_THREADSAFE_IN_OSAL

inline osal::Mutex::Mutex(const MutexType p_mutex_type, const bool p_prio_inherit):
    mutex(p_mutex_type==RECURSIVE)
{
    /* NOP */
}

inline osal::Mutex::~Mutex()
{
    /* NOP */
}

inline bool osal::Mutex::lock() const
{
    const char *result=mutex.lock();
    if(result) { // BRANCH_COVERAGE_UNTESTABLE
        if(result==threadsafe::Mutex::ERROR_INCONSISTENCY) // BRANCH_COVERAGE_UNTESTABLE
            osal_raise(Mutex::Error, Mutex::INCONSISTENCY);
        else
            osal_raise(Mutex::Error, Mutex::LOCK_FAILED);
        return true;
    }
    return false;
}

inline bool osal::Mutex::unlock() const
{
    const char *result=mutex.unlock();
    if(result) { // BRANCH_COVERAGE_UNTESTABLE
        if(result==threadsafe::Mutex::ERROR_INCONSISTENCY) // BRANCH_COVERAGE_UNTESTABLE
            osal_raise(Mutex::Error, Mutex::INCONSISTENCY);
        else
            osal_raise(Mutex::Error, Mutex::UNLOCK_FAILED);
        return true;
    }
    return false;
}

inline int_fast8_t osal::Mutex::tryLock() const
{
    const char *result=mutex.try_lock();
    if(result) {
        if(result==threadsafe::Mutex::NO_LUCK) // BRANCH_COVERAGE_UNTESTABLE
            return Mutex::TRY_LOCK_NOLUCK;
        else if(result==threadsafe::Mutex::ERROR_INCONSISTENCY) // BRANCH_COVERAGE_UNTESTABLE
            osal_raise(Mutex::Error, Mutex::INCONSISTENCY);
        else
            osal_raise(Mutex::Error, Mutex::LOCK_FAILED);
        return Mutex::TRY_LOCK_ERROR;
    }
    return Mutex::TRY_LOCK_SUCCESS;
}

inline int_fast8_t osal::Mutex::tryLockTimeout(const osal::TimeT &p_timeout_ms) const
{
    const char *result=mutex.try_lock(iplbase::Duration(p_timeout_ms, 1000));
    if(result) {
        if(result==threadsafe::Mutex::NO_LUCK) // BRANCH_COVERAGE_UNTESTABLE
            return Mutex::TRY_LOCK_NOLUCK;
        else if(result==threadsafe::Mutex::ERROR_INCONSISTENCY) // BRANCH_COVERAGE_UNTESTABLE
            osal_raise(Mutex::Error, Mutex::INCONSISTENCY);
        else
            osal_raise(Mutex::Error, Mutex::LOCK_FAILED);
        return Mutex::TRY_LOCK_ERROR;
    }
    return Mutex::TRY_LOCK_SUCCESS;
}

#else

#ifdef IPL_OS_POSIX
#    include "posix/Mutex.inl"
#elif defined (IPL_OS_WINPC)
#    include "win32/Mutex.inl"
#else
#    error "error undefined IPL_OS_ variant"
#endif

#endif

//! a macro that locks a mutex and on error aborts the program
#define IPL_MUTEX_LOCK_OR_ABORT(M) do if( (M).lock() ) \
    { IPL_ABORT("error locking"); } while(false)

//! a macro that unlocks a mutex and on error aborts the program
#define IPL_MUTEX_UNLOCK_OR_ABORT(M) do if( (M).unlock() )\
    { IPL_ABORT("error unlocking"); } while(false)

#endif /* OSAL_MUTEX_HXX */
