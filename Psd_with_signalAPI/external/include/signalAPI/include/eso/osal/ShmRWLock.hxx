/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_SHMRWLOCK_HXX
#define OSAL_SHMRWLOCK_HXX


#include <ipl_config.h>

#include <common/error/Error.hxx>
#include <common/NonCopyable.hxx>

#include <osal/osal_dso.h>

#if defined IPL_OS_ANDROID
// see RWLock.hxx for why osal on Android uses this implementation
#define OSAL_NEED_COMMON_RWLOCK_API
#include "common/ShmRWLockDefs.hxx"
#elif defined IPL_OS_LINUX || defined IPL_OS_QNX
#include "posix/ShmRWLockDefs.hxx"
#elif defined IPL_OS_WINPC
#include "common/ShmRWLockDefs.hxx"
#elif defined IPL_OS_INTEGRITY
#define OSAL_NEED_COMMON_RWLOCK_API
#include "common/ShmRWLockDefs.hxx"
#else
#error "error undefined IPL_OS_ variant"
#endif

#include <osal/osal.hxx>
#include <osal/RWLock.hxx>
#include <osal/SysError.hxx>

namespace osal
{

/**
 * \brief
 *    An RWLock Object for use in Inter-Process Shared Memory

 *     This class offers in principle the same functionality as an
 *     osal::RWLock but allows to synchronize not even different
 *     threads within a single process but also different processes via
 *     a shared memory area.
 *
 *     The ShmRWLock::Data type is the data part that needs to go into
 *     shared memory. This way you can for example define a structure
 *     like that:
 *
 *     struct shm_data
 *     {
 *        ShmRWLock::Data rwlock;
 *        // plus other required data ...
 *     };
 *
 *     shm_data *data = (shm_data*)shm_addr;
 *
 *    // the ShmRWLock can be put on the stack or on the heap as any
 *    // other object. only the ShmRWLock::Data needs to reside in
 *    // SHM.
 *    osal::ShmRWLock shm_rwlock( &(data->rwlock), true, true );
 *
 *    Regarding the shared memory specific handling please refer to
 *    the documencation of \c osal::ShmMutex.
 * \see
 *     osal::RWLock
 * \see
 *     osal::ShmMutex
**/
class OSAL_EXPORT ShmRWLock :
    public ipl::NonCopyable
{
public: // types

    //! the errors from osal::RWLock are reused here
    typedef osal::RWLock::RWLockErrors ShmRWLockErrors;

    //! ShmRWLock specific error type, the same as RWLock::Error
    static ipl::ErrorType &Error;

    //! \brief
    //! return value from tryReadLock(), readLock(), tryWriteLock(),
    //! writeLock() on success
    static const int_fast8_t LOCK_SUCCESS =
        osal::RWLock::LOCK_SUCCESS;

    //! \brief
    //! return value from tryReadLock(), readLock(), tryWriteLock(),
    //! writeLock() on error
    static const int_fast8_t LOCK_ERROR =
        osal::RWLock::LOCK_ERROR;

    //! brief
    //! return value from tryReadLock(), readLock(), tryWriteLock(),
    //! writeLock() on failure to acquire the lock
    static const int_fast8_t LOCK_NOLUCK =
        osal::RWLock::LOCK_NOLUCK;

    //! \brief
    //! this is the type that needs to be stored in SHM
    typedef ShmRWLockHandle::Data Data;
public:
    //! Creates an invalid ShmRWLock object
    ShmRWLock()
    { }

    /**
     * \brief
     *     Construct a new ShmRWLock object, directly attaching to
     *     shared memory
     * \see
     *     attach(void*, const bool, const bool, const)
     * \errorindicator
     *     via isValid()
     * \errors
     *     ShmRWLock::Error with ID CREATE_FAILED
    **/
    ShmRWLock(void *shm_addr,
        const bool initialize,
        const bool auto_destroy)
    {
        this->attach(shm_addr,
            initialize,
            auto_destroy);
    }

    /**
     * \brief
     *     Calls close()
     * \see
     *     close()
     **/
    inline virtual ~ShmRWLock()
    {
        if( this->close() ) // BRANCH_COVERAGE_UNTESTABLE
        {
            IPL_WARN("error closing ShmRWLock");
            ipl_error.ack();
        }
    }

    /*
     * \brief
     *     Attach the current ShmRWLock object to a shared memory
     *     area

     *     The parameter \c shm_addr must point to a valid shared
     *     memory location that is able to hold at least
     *     sizeof(ShmRWLock::Data) consecutive bytes. This is
     *     easiest achieved by putting an object of type
     *     ShmRWLock::Data into the shared memory area.
     *
     *     The data at \c shm_addr must not be altered during the
     *     lifetime of the shared rwlock by applications for the
     *     ShmRWLock to work.
     *
     *     If you pass an unmapped address for \c shm_addr then a
     *     segmentation violation will most probably occur during
     *     the attach process.
     *
     *     The parameter \c initialize determines whether the
     *     ShmRWLock at \c shm_addr is to be initialized. This is
     *     only required one time by one used for being able to use
     *     the rwlock. If an rwlock is initialized more than one
     *     time without destroying it then ressource leaks can
     *     occur as well as undefined behaviour when using the
     *     rwlock.
     *
     *     The parameter \c auto_destroy determines whether the
     *     rwlock at \c shm_addr should be automatically destroyed
     *     when the associated ShmRWLock object is destroyed (via
     *     calling close() or when the destructor runs).  Setting
     *     \c initialize and \c auto_destroy to \c true can for
     *     example be used to have one process responsible for
     *     initialization and destruction of the rwlock in SHM. In
     *     that case the lifetime of the rwlock at \c shm_addr is
     *     coupled to the lifetime of the ShmRWLock object used to
     *     initialize it.
     *
     *     Alternatively initialization and destruction of the
     *     rwlock at \c shm_addr can be performed by different
     *     parties in the system. Destruction can thus also be
     *     performed explicitly by using the static destroy(void*)
     *     member function.
     *
     *     If currently the ShmRWLock is already attached to a
     *     shared memory area then close() is called before
     *     attempting to attach to the new parameters.
     * \note
     *     If an ShmRWLock is constructed without \c initialize set
     *     to \c true and the memory location at \c shm_addr
     *     doesn't contain a valid shared rwlock for any reason
     *     then it is unspecified whether this condition can be
     *     detected at construction time. This means that you might
     *     turn up with a valid ShmRWLock object but still any
     *     operations on the rwlock will fail, because the data at
     *     \c shm_addr is invalid. In the worst case undefined
     *     behaviour will result from such situations (like
     *     deadlocks for example).
     *
     *     Thus the application is advised to carefully design the
     *     initializaton/destruction responsibilities to avoid this
     *     scenario.
     * \errors
     *     ShmRWLock::Error with ID CREATE_FAILED on lack of memory,
     *     other system ressources or if \c shm_addr is invalid in
     *     any way.
     * \return
     *     \c true on error, \c false otherwise
     * \errorindicator
     *     via isValid(), via return code
     */
    bool attach(
        void *shm_addr,
        const bool initialize,
        const bool auto_destroy);


    /**
     * \brief
     *    Detach from ShmRWLock and possibly destroy it, too

     *     If the \c auto_destroy parameter was set to \c true
     *     during construction/attach time then this function will
     *     destroy the shared rwlock in the associated shared memory
     *     data area like destroy(void*) does.
     *
     *     Otherwise only the binding of the ShmRWLock object to the
     *     shared rwlock will be released, further use of the shared
     *     rwlock by other threads and processes will still be
     *     possible.
     *
     *     If currently the object isn't attached to shared memory
     *     then nothing is done and \c false is returned.
     * \return
     *     \c false on success, \c true on error
     * \errorindicator
     *     via return code
     * \errors
     *     ShmRWLock::Error with ID CREATE_FAILED
    **/
    bool close();

    /**
     * \brief
     *     Destroy the rwlock at the given shared memory location

     *     Via this function a shared rwlock that was previously
     *     initialized at the shared memory location \c shm_addr,
     *     by means of constructing an ShmRWLock with the \c
     *     initialize parameter to \c true, will be destroyed.
     *
     *     This means that any ShmRWLock objects that still
     *     reference \c shm_addr will become invalid. Also any
     *     subsequent attempts to construct a ShmRWLock for \c
     *     shm_addr without the \c initialize parameter set to \c
     *     true will fail or result in invalid objects.
     *
     *     After successful return the memory at \c shm_addr can
     *     then be returned to the system or recycled for different
     *     purposes again.
     * \return
     *     \c true on error, \c false on success
     **/
    inline static bool destroy(void *shm_addr);

    /**
     * \brief
     *     Lock the RW-lock for reading
     * \see
     *     osal::RWLock::readLock()
    **/
    inline int_fast8_t readLock(
        const uint_fast32_t p_timeout_ms = 0) const;

    /**
     * \brief
     *     Lock the RW-lock for writing
     * \see
     *     osal::RWLock::writeLock()
    **/
    inline int_fast8_t writeLock(
        const uint_fast32_t p_timeout_ms = 0) const;

    /**
     * \brief
     *     Try to get the lock for reading without blocking
     * \see
     *     osal::RWLock::tryReadLock()
    **/
    inline int_fast8_t tryReadLock(void) const;

    /**
     * \brief
     *     Try to get the lock for writing without blocking
     * \see
     *     osal::RWLock::tryWriteLock()
    **/
    inline int_fast8_t tryWriteLock(void) const;

    /**
     * \brief
     *     Return the read or write lock
     * \see
     *     osal::RWLock::unlock()
    **/
    inline bool unlock() const;

    //! Returns true if construction succeeded, false otherwise
    bool isValid() const
    { return m_handle.isValid(); }
private: // members
    //! The os rwlock handle
    mutable ShmRWLockHandle m_handle;
}; // class

} // end namespace

#if defined IPL_OS_ANDROID
// see RWLock.hxx for why Android uses this implementation
#define OSAL_NEED_COMMON_RWLOCK_API
#include "common/ShmRWLock.inl"
#elif defined IPL_OS_LINUX || defined IPL_OS_QNX
#include "posix/ShmRWLock.inl"
#elif defined IPL_OS_WINPC
#include "win32/ShmRWLock.inl"
#elif defined IPL_OS_INTEGRITY
#define OSAL_NEED_COMMON_RWLOCK_API
#include "common/ShmRWLock.inl"
#else
#error "error undefined IPL_OS_ variant"
#endif

//! a macro that read-locks an rwlock and on error aborts the program
#define IPL_SHMRWLOCK_READLOCK_OR_ABORT(M) do if( M.readLock() != osal::ShmRWLock::LOCK_SUCCESS ) \
    { IPL_ABORT("error read-locking shmrwlock"); } while(false)

//! a macro that write-locks an rwlock and on error aborts the program
#define IPL_SHMRWLOCK_WRITELOCK_OR_ABORT(M) do if( M.writeLock() != osal::ShmRWLock::LOCK_SUCCESS ) \
    { IPL_ABORT("error write-locking shmrwlock"); } while(false)

//! a macro that unlocks an rwlock and on error aborts the program
#define IPL_SHMRWLOCK_UNLOCK_OR_ABORT(M) do if( M.unlock() )\
    { IPL_ABORT("error unlocking shmrwlock"); } while(false)

#endif /* OSAL_SHMRWLOCK_HXX */
