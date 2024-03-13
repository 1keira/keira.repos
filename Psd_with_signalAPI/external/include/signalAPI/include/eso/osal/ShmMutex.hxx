/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_SHMMUTEX_HXX
#define OSAL_SHMMUTEX_HXX

#include <ipl_config.h>

#include <common/error/Error.hxx>
#include <common/NonCopyable.hxx>

#include <osal/osal_dso.h>

#if defined IPL_OS_POSIX
#       include "posix/MutexDefs.hxx"
#       include "posix/ShmMutexDefs.hxx"
#elif defined IPL_OS_WINPC
#       include "win32/MutexDefs.hxx"
#       include "win32/ShmMutexDefs.hxx"
#elif defined IPL_OS_INTEGRITY
/* we need no steenking defs #       include "integrity/MutexDefs.hxx" */
#       include "integrity/ShmMutexDefs.hxx"
#else
#    error "error undefined IPL_OS_ variant"
#endif

#include <osal/osal.hxx>
#include <osal/Mutex.hxx>
#include <osal/SysError.hxx>

namespace osal
{

/**
 * \brief
 *    A Mutex Object for use in Inter-Process Shared Memory

 *     This class offers in principle the same functionality as an
 *     osal::Mutex but allows to synchronize not even different threads
 *     within a single process but also different processes via a
 *     shared memory area.
 *
 *     Unlike an osal::Semaphore this is not a named object but it is
 *     put directly into shared memory where multiple processes can
 *     access it. Thus creation of an ShmMutex is less complex and
 *     costly as with a Semaphore.
 *
 *     An ShmMutex can be considered more efficient then an
 *     osal::Semaphore. It should not need to enter kernel mode upon
 *     a lock operation when there is no contention for the lock.
 *
 *     Just like for the osal::Mutex there are binary and incremental
 *     mutexes. The MutexType enum as well as the error definitions are
 *     the same as for osal::Mutex.
 *
 *     The ShmMutex::Data type is the data part that needs to go into
 *     shared memory. This way you can for example define a structure
 *     like that:
 *
 *     struct shm_data
 *     {
 *        ShmMutex::Data mutex;
 *        // plus other required data ...
 *     };
 *
 *     shm_data *data = (shm_data*)shm_addr;
 *
 *    // the ShmMutex can be put on the stack or on the heap as any
 *    // other object. only the ShmMutex::Data needs to reside in SHM.
 *     osal::ShmMutex shm_mutex( &(data->mutex), true, true );
 * \note
 *     On WIN32 systems there are no real locking operations on SHM
 *     data structures involved. Instead the data in SHM is used to
 *     connect all users to an anonymous, named Win32 Mutex object.
 *     Thus the efficiency on those systems is not so much better then
 *     for an osal::Semaphore.
**/
class OSAL_EXPORT ShmMutex :
    public ipl::NonCopyable
{
public: // types

    //! \brief
    //! Used to select the type of mutex
    //! \see
    //! osal::Mutex::MutexType
    enum ShmMutexType
    {
        BINARY,
        RECURSIVE
    };

    //! the same errors can occur as with osal::Mutex
    typedef osal::Mutex::MutexErrors ShmMutexErrors;

    //! ShmMutex specific error type, the same as Mutex::Error
    static ipl::ErrorType &Error;

    //! return value from tryLock, tryLockTimeout() on success
    static const int_fast8_t TRY_LOCK_SUCCESS =
        osal::Mutex::TRY_LOCK_SUCCESS;
    //! return value from tryLock, tryLockTimeout() on error
    static const int_fast8_t TRY_LOCK_ERROR =
        osal::Mutex::TRY_LOCK_ERROR;
    //! brief
    //! return value from tryLock, tryLockTimeout() on failure to
    //! acquire the lock
    static const int_fast8_t TRY_LOCK_NOLUCK =
        osal::Mutex::TRY_LOCK_NOLUCK;

    //! \brief
    //! this is the type that needs to be stored in SHM
    typedef ShmMutexHandle::Data Data;
public:
    //! Creates an invalid ShmMutex object
    ShmMutex()
    { }

    /**
     * \brief
     *     Construct a new ShmMutex object, directly attaching to
     *     shared memory
     * \see
     *     attach(void*, const bool, const bool, const
     *     ShmMutexType, const bool)
     * \errorindicator
     *     via isValid()
    **/
    ShmMutex(void *shm_addr,
        const bool initialize,
        const bool auto_destroy,
        const ShmMutexType p_mutex_type = BINARY,
        const bool p_prio_inherit = false)
    {
        this->attach(shm_addr,
            initialize,
            auto_destroy,
            p_mutex_type,
            p_prio_inherit);
    }

    /**
     * \brief
     *     Calls close()
     * \see
     *     close()
     **/
    inline ~ShmMutex()
    {
        if( this->close() ) // BRANCH_COVERAGE_UNTESTABLE
        {
            IPL_WARN("error closing ShmMutex");
            ipl_error.ack();
        }
    }

    /*
     * \brief
     *     Attach the current ShmMutex object to a shared memory
     *     area

     *     The parameter \c shm_addr must point to a valid shared
     *     memory location that is able to hold at least
     *     sizeof(ShmMutex::Data) consecutive bytes. This is
     *     easiest achieved by putting an object of type
     *     ShmMutex::Data into the shared memory area.
     *
     *     The data at \c shm_addr must not be altered during the
     *     lifetime of the shared mutex by applications for the
     *     ShmMutex to work.
     *
     *     If you pass an unmapped address for \c shm_addr then a
     *     segmentation violation will most probably occur during
     *     the attempt to attach to it.
     *
     *     The parameter \c initialize determines whether the
     *     ShmMutex at \c shm_addr is to be initialized. This is
     *     only required one time by one user for being able to use
     *     the mutex. If a mutex is initialized more than one time
     *     without destroying it then ressource leaks can occur as
     *     well as undefined behaviour when using the mutex.
     *
     *     The parameter \c auto_destroy determines whether the
     *     mutex at \c shm_addr should be automatically destroyed
     *     when the associated ShmMutex object is destroyed (via
     *     close() or when the destructor runs). Setting \c
     *     initialize and \c auto_destroy to \c true can for
     *     example be used to have one process responsible for
     *     initialization and destruction of the mutex in SHM. In
     *     that case the lifetime of the mutex at \c shm_addr is
     *     coupled to the lifetime of the ShmMutex object used to
     *     initialize it.
     *
     *     Alternatively initialization and destruction of the
     *     mutex at \c shm_addr can be performed by different
     *     parties in the system. Destruction can thus also be
     *     performed explicitly by using the static destroy(void*)
     *     member function.
     *
     *     The \c p_mutex_type and \c p_prio_inherit parameters
     *     have the same meaning as described at
     *     osal::Mutex(osal::Mutex::MutexType, const bool).
     *
     *     If currently the ShmMutex is already attached to a
     *     shared memory area then close() is called before
     *     attempting to attach to the new parameters.
     * \note
     *     If an ShmMutex is constructed without \c initialize set
     *     to \c true and the memory location at \c shm_addr
     *     doesn't contain a valid shared mutex for any reason
     *     then it is unspecified whether this condition can be
     *     detected at construction time. This means that you might
     *     turn up with a valid ShmMutex object but still any
     *     operations on the mutex will fail, because the data at
     *     \c shm_addr is invalid. In the worst case undefined
     *     behaviour will result from such situations (like
     *     deadlocks for example).
     *
     *     Thus the application is advised to carefully design the
     *     initializaton/destruction responsibilities to avoid this
     *     scenario.
     * \errors
     *     ShmMutex::Error with ID CREATE_FAILED on lack of memory,
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
        const bool auto_destroy,
        const ShmMutexType p_mutex_type = BINARY,
        const bool p_prio_inherit = false);

    /**
     * \brief
     *    Detach from ShmMutex and possibly destroy it, too

     *     If the \c auto_destroy parameter was set to \c true
     *     during construction/attach time then this function will
     *     destroy the shared mutex in the associated shared memory
     *     data area like destroy(void*) does.
     *
     *     Otherwise only the binding of the ShmMutex object to the
     *     shared mutex will be released, further use of the shared
     *     mutex by other threads and processes will still be
     *     possible.
     *
     *     If currently the object isn't attached to shared memory
     *     then nothing is done and \c false is returned.
     * \return
     *     \c false on success, \c true on error
     * \errorindicator
     *     via return code
     * \errors
     *     ShmMutex::Error with ID INCONSISTENCY
    **/
    bool close();

    /**
     * \brief
     *     Destroy the mutex at the given shared memory location

     *     Via this function a shared mutex that was previously
     *     initialized at the shared memory location \c shm_addr,
     *     by means of constructing an ShmMutex with the \c
     *     initialize parameter to \c true, will be destroyed.
     *
     *     This means that any ShmMutex objects that still
     *     reference \c shm_addr will become invalid. Also any
     *     subsequent attempts to construct a ShmMutex for \c
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
     *     Waits for the mutex to become available and acquires it
     * \see
     *     osal::Mutex::lock()
    **/
    bool lock() const;

    /**
     * \brief
     *     Releases the ownership of a mutex previously acquired
     * \see
     *     osal::Mutex::unlock()
    **/
    bool unlock() const;

    /**
     * \brief
     *     Attempts to immediatly obtain ownership of a mutex,
     *     otherwise returns TRY_LOCK_NOLUCK
     * \see
     *     osal::Mutex::tryLock()
    **/
    int_fast8_t tryLock() const;

    /**
     * \brief
     *     Waits maximum \c p_timeout_ms miliseconds for the mutex
     *     to become available, otherwise returns TRY_LOCK_NOLUCK
     * \see
     *     osal::Mutex::tryLockTimeout()
     **/
    int_fast8_t tryLockTimeout(
        const osal::TimeT &p_timeout_ms) const;

    /**
     * \brief
     *     Returns whether the current object is currently bound to
     *     a shared memory mutex
     **/
    bool isValid() const
    { return m_handle.isValid(); }
private: // members
    //! The os mutex handle
    mutable ShmMutexHandle m_handle;

    friend class ShmCondition;
}; // class Mutex

} // end namespace

#if defined IPL_OS_POSIX
#    include "posix/ShmMutex.inl"
#elif defined IPL_OS_WINPC
#    include "win32/ShmMutex.inl"
#elif defined IPL_OS_INTEGRITY
#    include "integrity/ShmMutex.inl"
#else
#    error "error undefined IPL_OS_ variant"
#endif

//! a macro that locks a mutex and on error aborts the program
#define IPL_SHMMUTEX_LOCK_OR_ABORT(M) do if( M.lock() ) \
    { IPL_ABORT("error locking shmmutex"); } while(false)

//! a macro that unlocks a mutex and on error aborts the program
#define IPL_SHMMUTEX_UNLOCK_OR_ABORT(M) do if( M.unlock() )\
    { IPL_ABORT("error unlocking shmmutex"); } while(false)

#endif /* OSAL_SHMMUTEX_HXX */
