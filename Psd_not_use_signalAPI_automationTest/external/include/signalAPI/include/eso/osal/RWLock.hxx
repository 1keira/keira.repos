/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_RWLOCK_HXX
#define OSAL_RWLOCK_HXX

#include <ipl_config.h>

#if defined IPL_OS_ANDROID
// The Android pthread_rwlock API is broken:
// a pthread_rwlock_tryrdlock after a successfull pthread_rwlock_wrlock (from the same thread)
// succeeds.
// That violates the spec:
// "The calling thread acquires the read lock if a writer does not
// hold the lock and there are no writers blocked on the lock."
#define OSAL_NEED_COMMON_RWLOCK_API
#include "common/RWLockDefs.hxx"
#elif defined IPL_OS_LINUX || defined IPL_OS_QNX
#include "posix/RWLockDefs.hxx"
#elif defined IPL_OS_WINPC
#define OSAL_NEED_COMMON_RWLOCK_API
#include "common/RWLockDefs.hxx"
#elif defined IPL_OS_INTEGRITY
//#define OSAL_NEED_COMMON_RWLOCK_API
#include "common/RWLockDefs.hxx"
#else
#error "error undefined IPL_OS_ variant"
#endif

// RWLock needs to be non-copyable
#include <common/NonCopyable.hxx>
#include <osal/osal.hxx>
#include <osal/osal_dso.h>

#include <osal/SysError.hxx>

namespace osal
{

/**
 * \brief
 *    Specialized lock that differentiates between readers and writers

 *    This lock acts similar to an osal::Mutex. However it allows more
 *    efficient operation in case there are a high amount of threads
 *    that only need to do read-only access to some shared data.
 *
 *    This higher efficency comes at the cost of a more complicated
 *    interface for the lock.
 *
 *    The RWLock allows multiple readers to obtain access to the lock
 *    in parallel. For writing only a single writer and no readers may
 *    be present.
 *
 *    The writers usually have priority above the readers (exact
 *    behaviour depends on the OS scheduling and real-time settings,
 *    e.g. thread priorities). This means if at least one writer is
 *    waiting to obtain the lock then further attempts to get the lock
 *    for reading will be blocked and it will be waited until any
 *    present readers return their lock such that the writer gets the
 *    oppurtunity to modify the data.
 **/
class OSAL_EXPORT RWLock  :
    public ipl::NonCopyable
{
public: // types

    //! specific error IDs
    enum RWLockErrors
    {
        CREATE_FAILED = 0,
        DEADLOCK_DETECTED,
        MAXLOCK_REACHED,
        READ_LOCK_FAILED,
        WRITE_LOCK_FAILED,
        UNLOCK_FAILED
    };

    //! specific error type
    static ipl::ErrorType Error;

    //! return value from readLock(), writeLock() on success
    static const int_fast8_t LOCK_SUCCESS = 0;
    //! return value from readLock(), writeLock() on error
    static const int_fast8_t LOCK_ERROR = -1;
    //! \brief
    //! return value from readLock(), writeLock() on failure to
    //! acquire the lock
    static const int_fast8_t LOCK_NOLUCK = 1;

public: // functions
    /**
     * \brief
     *    Initialization of read-write lock
     * \errorindicator
     *    via isValid()
     * \errors
     *    osal::SysError with IDs:
     *
     *    - SYSTEM_RESSOURCES_EXHAUSTED if ressources other than
     *    memory are lacking
     *    - OUT_OF_MEMORY if memory is lacking
     *
     *    RWLock::Error with IDs:
     *
     *    - CREATE_FAILED on other system specific errors
     **/
    inline RWLock();

    /**
     * \brief
     *    Destruction of read-write lock

     *    Performs some sanity checks. Abort on errors like: mutex
     *    still locked.
     **/
    inline ~RWLock();

    /**
     * \brief
     *    lock the RW-lock for reading

     *    This is a blocking call that only returns successfully
     *    when the lock could be acquired for reading. This is
     *    only possible when no writer locks are currently active.
     *    Multiple readers may get the lock in parallel however.
     *
     *    The read-lock can be obtained multiple times even by the
     *    same thread.  In this case the lock has to be unlocked
     *    the same number of times by this thread.
     *
     *    The clock used for the timeout in this function is not
     *    necessarily monotonic. On POSIX systems it is always
     *    based on the realtime clock and can jump.
     * \param[in]
     *    p_timeout_ms if set to non zero then the blocking call will
     *    be canceled after the given number of milliseconds in
     *    case the lock can't be obtained within this time.
     *
     *    In this case > 0 is returned and the lock is not owned
     *    by the caller.
     * \return
     *    zero if the lock could be obtained within time, > 0 if
     *    the timeout occured and the lock could thus not be
     *    acquired, < 0 if an error occured.
     * \errorindicator
     *    if < 0 is returned then an error occured
     * \errors
     *    RWLock::Error with IDs:
     *
     *    - MAXLOCK_REACHED if the maximum lock count has been
     *    reached for the lock
     *    - DEADLOCK_DETECTED if the current thread already owns
     *    the lock for writing
     *    - LOCK_FAILED on other system specific errors (usually
     *    integrity errors)
     **/
    inline int_fast8_t readLock(
        const uint_fast32_t p_timeout_ms = 0) const;

    /**
     * \brief
     *    lock the RW-lock for writing

     *    This is a blocking call that only returns when the lock
     *    could be acquired for writing. This is only possible
     *    when no read-locks are active. Only one writer can own
     *    the lock at any given time.
     *
     *    The same thread should never try to get the lock for
     *    writing when it already owns the lock for reading. In
     *    this case the behaviour is undefined.
     *
     *    The clock used for the timeout in this function is not
     *    necessarily monotonic. On POSIX systems it is always
     *    based on the realtime clock an can jump.
     * \param[in]
     *    p_timeout_ms if set to non-zero then the blocking call will
     *    be canceled after the given number of milliseconds in
     *    case the lock can't be obtained within this time.
     *
     *    In this case > 0 is returned and the lock is not owned
     *    by the caller.
     * \return
     *    zero if the lock could be obtained within time, > 0 if
     *    the timeout occured and the lock could thus not be
     *    acquired, < 0 if an error occured.
     * \errorindicator
     *    if < 0 is returned then an error occured
     * \errors
     *    RWLock::Error with IDs:
     **/
    inline int_fast8_t writeLock(
        const uint_fast32_t p_timeout_ms = 0) const;

    /**
     * \brief
     *    try to get the lock for reading without blocking

     *    does the same as readLock but only tries to get the lock
     *    for reading immediately and returns without blocking.
     * \warning
     *    Some OS don't allow to try to get the read lock if the
     *    calling thread already owns it. In this case you will
     *    get a deadlock error instead of a > 0 return.
     *    Applications are thus advised not to try to lock a lock
     *    that's already owned by the thread.
     * \return
     *    zero if the lock could be obtained within time, > 0 if
     *    the lock could not be immediatly acquired, < 0 if an
     *    error occured.
     * \errorindicator
     *    if < 0 is returned then an error occured
     * \errors
     *    see readLock()
     **/
    inline int_fast8_t tryReadLock(void) const;

    /**
     * \brief
     *    try to get the lock for writing without blocking

     *    does the same as writeLock but only tries to get the
     *    lock for writing immediately and returns without
     *    blocking.
     * \warning
     *    see tryReadLock()
     * \return
     *    zero if the lock could be obtained within time, > 0 if
     *    the lock could not be immediatly acquired, < 0 if an
     *    error occured.
     * \errorindicator
     *    if < 0 is returned then an error occured
     * \errors
     *    see writeLock()
     **/
    inline int_fast8_t tryWriteLock(void) const;

    /**
     * \brief
     *    return the read or write lock
     * \note
     *    The lock needs to be owned by the calling thread for
     *    reading or writing, otherwise the behaviour is
     *    undefined.
     * \return
     *    true on error, false on success
     * \errorindicator
     *    via return code
     * \errors
     *    SysError with IDs:
     *
     *    - PERMISSION_DENIED if the lock is not owned by the
     *    calling thread for reading or writing
     *
     *    RWLock::Error with IDs:
     *
     *    UNLOCK_FAILED on other, system specific errors (usually
     *    integrity errors)
     **/
    inline bool unlock(void) const;

    //! returns true if construction of the object was successful
    bool isValid() const
    { return m_handle.isValid(); }

private: // members
    mutable RWLockHandle m_handle;
}; // end class

} // end namespace

#if defined IPL_OS_ANDROID
#define OSAL_NEED_COMMON_RWLOCK_API
#include "common/RWLock.inl"
#elif defined IPL_OS_LINUX || defined IPL_OS_QNX
#include "posix/RWLock.inl"
#elif defined IPL_OS_WINPC
#include "win32/RWLock.inl"
#elif defined IPL_OS_INTEGRITY
#define OSAL_NEED_COMMON_RWLOCK_API
#include "common/RWLock.inl"
#else
#error "error undefined IPL_OS_ variant"
#endif

//! \brief Lock for reading (shared) or abort
#define IPL_RWLOCK_RLOCK_OR_ABORT(l) do {                  \
                if( l.readLock() ) { IPL_ABORT("error locking"); } \
        } while(false)

//! \brief Lock for writing (exclusive) or abort
#define IPL_RWLOCK_WLOCK_OR_ABORT(l) do {                   \
                if( l.writeLock() ) { IPL_ABORT("error locking"); } \
        } while(false)

//! \brief Unlock or abort
#define IPL_RWLOCK_UNLOCK_OR_ABORT(l) do {               \
                if( l.unlock() ) { IPL_ABORT("error locking"); } \
        } while(false)

#endif // OSAL_RWLOCK_HXX
