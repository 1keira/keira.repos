/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_SHMSPINLOCK_HXX
#define OSAL_SHMSPINLOCK_HXX

#include <ipl_config.h>

#include <common/error/Error.hxx>
#include <common/NonCopyable.hxx>

#include <osal/osal_dso.h>

#if defined IPL_OS_ANDROID
#include "android/ShmSpinLockDefs.hxx"
#elif defined IPL_OS_LINUX || defined IPL_OS_QNX
#include "posix/ShmSpinLockDefs.hxx"
#elif defined IPL_OS_WINPC
#include "win32/ShmSpinLockDefs.hxx"
#elif defined IPL_OS_INTEGRITY
#include "integrity/ShmSpinLockDefs.hxx"
#else
#error "error undefined IPL_OS_ variant"
#endif

#include <osal/osal.hxx>
#include <osal/SpinLock.hxx>

namespace osal
{

/**
 * \brief
 *    A SpinLock Object for use in Inter-Process Shared Memory

 *     This class offers in principle the same functionality as an \c
 *     osal::SpinLock but allows to synchronize not even different
 *     threads within a single process but also different processes via
 *     a shared memory area.
 *
 *     The ShmSpinLock::Data type is the data part that needs to go into
 *     shared memory. This way you can for example define a structure
 *     like that:
 *
 *     struct shm_data
 *     {
 *        ShmSpinLock::Data spinlock;
 *        // plus other required data ...
 *     };
 *
 *     shm_data *data = (shm_data*)shm_addr;
 *
 *    // the ShmSpinLock can be put on the stack or on the heap as any
 *    // other object. only the ShmSpinLock::Data needs to reside in SHM.
 *     osal::ShmSpinLock shm_spinlock( &(data->spinlock), true, true );
 *
 *     Regarding the shared memory specific handling of ShmSpinLock
 *     please refer to the documentation of \c ShmMutex.
 * \see
 *     osal::ShmMutex
 * \see
 *     osal::SpinLock
**/
class OSAL_EXPORT ShmSpinLock :
    public ipl::NonCopyable
{
public: // types

    //! the same errors as for osal::SpinLock are used
    typedef osal::SpinLock::SpinLockErrors ShmSpinLockErrors;

    //! ShmSpinLock specific error type, the same as SpinLock::Error
    static ipl::ErrorType &Error;

    //! return value from tryLock, tryLockTimeout() on success
    static const int_fast8_t TRY_LOCK_SUCCESS =
        osal::SpinLock::TRY_LOCK_SUCCESS;
    //! return value from tryLock, tryLockTimeout() on error
    static const int_fast8_t TRY_LOCK_ERROR =
        osal::SpinLock::TRY_LOCK_ERROR;
    //! brief
    //! return value from tryLock, tryLockTimeout() on failure to
    //! acquire the lock
    static const int_fast8_t TRY_LOCK_NOLUCK =
        osal::SpinLock::TRY_LOCK_NOLUCK;

    //! \brief
    //! this is the type that needs to be stored in SHM
    typedef ShmSpinLockHandle::Data Data;
public:
    //! Creates an invalid SpinLock object
    ShmSpinLock()
    { }

    /**
     * \brief
     *     Creatres a SpinLock object and attaches it to the given
     *     shared memory area.
     * \see
     *     attach(volatile void*, const bool, const bool)
     * \errorindicator
     *     via isValid()
    **/
    ShmSpinLock(volatile void *shm_addr,
        const bool initialize,
        const bool auto_destroy)
    {
        this->attach(shm_addr, initialize, auto_destroy);
    }

    /**
     * \brief
     *     Calls close()
     * \see
     *     close()
     **/
    virtual ~ShmSpinLock()
    {
        if( this->close() )
        {
            IPL_WARN("Error closing spinlock");
        }
    }

    /**
     * \brief
     *     Attach the current ShmSpinLock to the given shared memory
     *     area

     *     The parameter \c shm_addr must point to a valid shared
     *     memory location that is able to hold at least
     *     sizeof(ShmSpinLock::Data) consecutive bytes. This is
     *     easiest achieved by putting an object of type
     *     ShmSpinLock::Data into the shared memory area.
     *
     *     The data at \c shm_addr must not be altered during the
     *     lifetime of the shared spinlock by applications for the
     *     ShmSpinLock to work.
     *
     *     If you pass an unmapped address for \c shm_addr then a
     *     segmentation violation will most probably occur during
     *     the attach process.
     *
     *     The parameter \c initialize determines whether the
     *     ShmSpinLock at \c shm_addr is to be initialized. This is
     *     only required one time by one user for being able to use
     *     the spinlock. If a spinlock is initialized more than one
     *     time without destroying it then ressource leaks can
     *     occur as well as undefined behaviour when using the
     *     spinlock.
     *
     *     The parameter \c auto_destroy determines whether the
     *     spinlock at \c shm_addr should be automatically destroyed
     *     when the associated ShmSpinLock object is destroyed (via
     *     calling close() or when the destructor runs).  Setting
     *     \c initialize and \c auto_destroy to \c true can for
     *     example be used to have one process responsible for
     *     initialization and destruction of the spinlock in SHM.
     *     In that case the lifetime of the spinlock at \c shm_addr
     *     is coupled to the lifetime of the ShmSpinLock object
     *     used to initialize it.
     *
     *     Alternatively initialization and destruction of the
     *     spinlock at \c shm_addr can be performed by different
     *     parties in the system. Destruction can thus also be
     *     performed explicitly by using the static
     *     destroy(volatile void*) member function.
     * \note
     *     If an ShmSpinLock is constructed without \c initialize
     *     set to \c true and the memory location at \c shm_addr
     *     doesn't contain a valid shared spinlock for any reason
     *     then it is unspecified whether this condition can be
     *     detected at construction time. This means that you might
     *     turn up with a valid ShmSpinLock object but still any
     *     operations on the spinlock will fail, because the data
     *     at \c shm_addr is invalid. In the worst case undefined
     *     behaviour will result from such situations (like
     *     deadlocks for example).
     *
     *     Thus the application is advised to carefully design the
     *     initializaton/destruction responsibilities to avoid this
     *     scenario.
     * \errors
     *     ShmSpinLock::Error with ID CREATE_FAILED on lack of memory,
     *     other system ressources or if \c shm_addr is invalid in
     *     any way.
     * \errorindicator
     *     via isValid(), via return code
     * \return
     *     \c false on success, \c true on error
     **/
    inline bool attach(volatile void *shm_addr,
        const bool initialize,
        const bool auto_destroy);

    /**
     * \brief
     *    Detach from ShmSpinLock and possibly destroy it, too

     *     If the \c auto_destroy parameter was set to \c true
     *     during construction time then the destructor will
     *     destroy the shared spinlock in the associated shared memory
     *     data area like destroy(volatile void*) does.
     *
     *     Otherwise only the binding of the ShmSpinLock object to
     *     the shared spinlock will be released, further use of the
     *     shared spinlock by other threads and processes will
     *     still be possible.
     * \return
     *     \c true on error, \c false on success
     * \errors
     *     ShmSpinLock::Error with ID INCONSISTENCY
    **/
    inline bool close();

    /**
     * \brief
     *     Destroy the spinlock at the given shared memory location

     *     Via this function a shared spinlock that was previously
     *     initialized at the shared memory location \c shm_addr,
     *     by means of constructing an ShmSpinLock with the \c
     *     initialize parameter to \c true, will be destroyed.
     *
     *     This means that any ShmSpinLock objects that still
     *     reference \c shm_addr will become invalid. Also any
     *     subsequent attempts to construct a ShmSpinLock for \c
     *     shm_addr without the \c initialize parameter set to \c
     *     true will fail or result in corrupt objects.
     *
     *     After successful return the memory at \c shm_addr can
     *     then be returned to the system or recycled for different
     *     purposes again.
     * \return
     *     \c true on error, \c false on success
     **/
    inline static bool destroy(volatile void *shm_addr);

    /**
     * \brief
     *     Waits for the spinlock to become available and acquires
     *     it
     * \see
     *     osal::SpinLock::lock()
    **/
    inline bool lock() const;

    /**
     * \brief
     *     Releases the ownership of a spinlock previously acquired
     * \see
     *     osal::SpinLock::unlock()
    **/
    inline bool unlock() const;

    /**
     * \brief
     *     Attempts to immediatly obtain ownership of a spinlock,
     *     otherwise returns TRY_LOCK_NOLUCK
     * \see
     *     osal::SpinLock::tryLock()
    **/
    inline int_fast8_t tryLock() const;

    //! Returns true if construction succeeded, false otherwise
    bool isValid() const
    { return m_handle.isValid(); }
private: // members
    //! The os spinlock handle
    mutable ShmSpinLockHandle m_handle;
}; // class Mutex

} // end namespace

#if defined IPL_OS_ANDROID
#include "android/ShmSpinLock.inl"
#elif defined IPL_OS_LINUX || defined IPL_OS_QNX
#include "posix/ShmSpinLock.inl"
#elif defined IPL_OS_WINPC
#include "win32/ShmSpinLock.inl"
#elif defined IPL_OS_INTEGRITY
#include "integrity/ShmSpinLock.inl"
#else
#error "error undefined IPL_OS_ variant"
#endif

//! a macro that locks a spinlock and on error aborts the program
#define IPL_SHMSPINLOCK_LOCK_OR_ABORT(M) if( M.lock() ) \
    { IPL_ABORT("error locking shmspinlock"); }

//! a macro that unlocks a spinlock and on error aborts the program
#define IPL_SHMSPINLOCK_UNLOCK_OR_ABORT(M) if( M.unlock() )\
    { IPL_ABORT("error unlocking shmspinlock"); }

#endif /* OSAL_SHMSPINLOCK_HXX */
