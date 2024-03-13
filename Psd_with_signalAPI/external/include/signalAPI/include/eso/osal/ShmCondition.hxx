/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_SHMCONDITION_HXX
#define OSAL_SHMCONDITION_HXX

#include <ipl_config.h>

#include <common/error/Error.hxx>
#include <common/NonCopyable.hxx>

#include <osal/osal_dso.h>

#if defined IPL_OS_POSIX
#       include "posix/ConditionDefs.hxx"
#       include "posix/ShmConditionDefs.hxx"
#elif defined IPL_OS_WINPC
#       include "win32/ConditionDefs.hxx"
#       include "win32/ShmConditionDefs.hxx"
#elif defined IPL_OS_INTEGRITY
#       include "integrity/ShmConditionDefs.hxx"
#else
#    error "error undefined IPL_OS_ variant"
#endif

#include <osal/osal.hxx>
#include <osal/Condition.hxx>
#include <osal/ShmMutex.hxx>
#include <osal/SysError.hxx>

namespace osal
{

/**
 * \brief
 *    A Condition Object for use in Inter-Process Shared Memory

 *     This class offers in principle the same functionality as an
 *     osal::Condition but allows to synchronize not even different threads
 *     within a single process but also different processes via a
 *     shared memory area.
 *
 *     The ShmCondition type is used in conjunction with the ShmMutex
 *     type just like the osal::Condition is used in conjunction with
 *     an osal::Mutex.
 *
 *     The ShmCondition::Data type is the data part that needs to go into
 *     shared memory. This way you can for example define a structure
 *     like that:
 *
 *     struct shm_data
 *     {
 *         // mutex to use with cond
 *         ShmMutex::Data mutex;
 *        ShmCondition::Data cond;
 *        // plus other required data ...
 *     };
 *
 *     shm_data *data = (shm_data*)shm_addr;
 *
 *    // the ShmCondition can be put on the stack or on the heap as
 *    // any other object. only the ShmCondition::Data needs to
 *    // reside in SHM.
 *     osal::ShmCondition shm_cond( &(data->cond), true, true );
 *    // this mutex goes along with shm_cond
 *     osal::ShmMutex shm_mutex( &(data->mutex), true, true );
 *
 *     Regarding the shared memory specific handling of ShmCondition
 *     please refer to \c osal::ShmMutex.
 * \see
 *     osal::Condition
 * \see
 *     osal::ShmMutex
**/
class OSAL_EXPORT ShmCondition :
    public ipl::NonCopyable
{
public: // types

    //! the same errors as for osal::Condition are used here
    typedef osal::Condition::ConditionErrors
        ShmConditionErrors;

    //! \brief
    //! ShmCondition specific error type, the same as
    //! Condition::Error
    static ipl::ErrorType &Error;

    //! \see osal::Condition::WAIT_SIGNALED
    static const int_fast8_t WAIT_SIGNALED =
        osal::Condition::WAIT_SIGNALED;
    //! \see osal::Condition::WAIT_TIMEDOUT
    static const int_fast8_t WAIT_TIMEDOUT =
        osal::Condition::WAIT_TIMEDOUT;
    //! \see osal::Condition::WAIT_ERROR
    static const int_fast8_t WAIT_ERROR =
        osal::Condition::WAIT_ERROR;

    //! \brief
    //! this is the type that needs to be stored in SHM
    typedef ShmConditionHandle::Data Data;
public:
    //! creates an invalid ShmCondition object
    ShmCondition()
    { }

    /**
     * \brief
     *    Create a new ShmConditon and attach to the given shared
     *    memory area
     * \see
     *     attach(void*, const bool, const bool)
     * \errorindicator
     *     via isValid()
     * \errors
     *     \see attach(void*, const bool, const bool)
    **/
    ShmCondition(void *shm_addr,
        const bool initialize,
        const bool auto_destroy)
    {
        this->attach(shm_addr, initialize, auto_destroy);
    }

    //! calls close()
    ~ShmCondition()
    {
        if( this->close() ) // BRANCH_COVERAGE_UNTESTABLE
        {
            IPL_WARN("error closing shm condition");
        }
    }

    /**
     * \brief
     *     Attach the current object to the given shared memory
     *     area

     *     The parameter \c shm_addr must point to a valid shared
     *     memory location that is able to hold at least
     *     sizeof(ShmCondition::Data) consecutive bytes. This is
     *     easiest achieved by putting an object of type
     *     ShmCondition::Data into the shared memory area.
     *
     *     The data at \c shm_addr must not be altered during the
     *     lifetime of the shared condition by applications for the
     *     ShmCondition to work.
     *
     *     If you pass an unmapped address for \c shm_addr then a
     *     segmentation violation will most probably occur during
     *     the attach process.
     *
     *     The parameter \c initialize determines whether the
     *     ShmCondition at \c shm_addr is to be initialized. This is
     *     only required one time by one used for being able to use
     *     the condition. If a condition is initialized more than
     *     one time without destroying it then ressource leaks can
     *     occur as well as undefined behaviour when using the
     *     condition.
     *
     *     The parameter \c auto_destroy determines whether the
     *     condition at \c shm_addr should be automatically
     *     destroyed when the associated ShmCondition object is
     *     destroyed (via calling close() or when the destructor is
     *     run). Setting \c initialize and \c auto_destroy to \c
     *     true can for example be used to have one process
     *     responsible for initialization and destruction of the
     *     condition in SHM. In that case the lifetime of the
     *     condition at \c shm_addr is coupled to the lifetime of
     *     the ShmCondition object used to initialize it.
     *
     *     Alternatively initialization and destruction of the
     *     condition at \c shm_addr can be performed by different
     *     parties in the system. Destruction can thus also be
     *     performed explicitly by using the static destroy(void*)
     *     member function.
     *
     *     If currently the ShmCondition is already attached to a
     *     shared memory area then close() is called before
     *     attaching to the new parameters.
     * \note
     *     If an ShmCondition is constructed without \c initialize
     *     set to \c true and the memory location at \c shm_addr
     *     doesn't contain a valid shared condition for any reason
     *     then it is unspecified whether this condition can be
     *     detected at construction time. This means that you might
     *     turn up with a valid ShmCondition object but still any
     *     operations on the condition will fail, because the data
     *     at \c shm_addr is invalid. In the worst case undefined
     *     behaviour will result from such situations (like
     *     deadlocks for example).
     *
     *     Thus the application is advised to carefully design the
     *     initializaton/destruction responsibilities to avoid this
     *     scenario.
     * \errors
     *     \see osal::Condition::Condition()
     * \errorindicator
     *     via isValid()
     * \return
     *     \c true on error, \c false on success
     **/
    bool attach(void *shm_addr,
        const bool initialize,
        const bool auto_destroy);

    /**
     * \brief
     *    Detach from ShmCondition and possibly destroy it, too

     *     If the \c auto_destroy parameter was set to \c true
     *     during attach time then the destructor will destroy the
     *     shared condition in the associated shared memory data
     *     area like destroy(void*) does.
     *
     *     Otherwise only the binding of the ShmCondition object to
     *     the shared condition will be released, further use of
     *     the shared condition by other threads and processes will
     *     still be possible.
     *
     *     If currently no valid shared condition variable is
     *     attached then \c false is returned without doing
     *     anything.
     * \return
     *     \c true on error, \c false on success
    **/
    bool close();

    /**
     * \brief
     *     Destroy the condition at the given shared memory
     *     location

     *     Via this function a shared condition that was previously
     *     initialized at the shared memory location \c shm_addr,
     *     by means of constructing an ShmCondition with the \c
     *     initialize parameter to \c true, will be destroyed.
     *
     *     This means that any ShmCondition objects that still
     *     reference \c shm_addr will become invalid. Also any
     *     subsequent attempts to construct a ShmCondition for \c
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

    //! Returns true if construction succeeded, false otherwise
    bool isValid() const
    { return m_handle.isValid(); }

    /**
     * \brief
     *     Wait until the ShmCondition will be signaled
     * \see
     *     osal::Condition::wait(osal::Mutex&)
     **/
    inline bool wait(osal::ShmMutex &p_lock);

    /**
     * \brief
     *     Wait until the ShmCondition will be signaled or until \c
     *     end_time is reached
     * \see
     *     osal::Condition::waitTimeout(osal::Mutex&)
     **/
    inline int_fast8_t waitTimeout(osal::ShmMutex &p_lock,
        const osal::AbsTimeT &end_time);

    /**
     * \brief
     *     Signal a thread waiting on the shared condition variable
     * \see
     *     osal::Condition::signal()
     **/
    inline bool signal();

    /**
     * \brief
     *     Signal all threads currently waiting on the shared
     *     condition variable
     * \see
     *     osal::Condition::signalAll()
     **/
    inline bool signalAll();
private: // members
    //! The os condition handle
    mutable ShmConditionHandle m_handle;
}; // class Condition

} // end namespace

#if defined IPL_OS_POSIX
#       include "posix/Condition.inl"
#       include "posix/ShmCondition.inl"
#elif defined IPL_OS_WINPC
// not including "win32/Condition.inl" as there are no ConditionOps for win32
#       include "win32/ShmCondition.inl"
#elif defined IPL_OS_INTEGRITY
// not including "integrity/Condition.inl" as there are no ConditionOps for win32
#       include "integrity/ShmCondition.inl"
#else
#    error "error undefined IPL_OS_ variant"
#endif

//! \brief
//! a macro that waits on a shared condition/mutex pair and on error
//! aborts the program
#define IPL_SHMCONDITION_WAIT_OR_ABORT(C, M) do if( C.wait(M) ) \
    { IPL_ABORT("error waiting on shmcondition"); } while(false)

//! a macro that signals an shmcondition and on error aborts the program
#define IPL_SHMCONDITION_SIGNAL_OR_ABORT(C) do if( C.signal() )\
    { IPL_ABORT("error signaling shmcondition"); } while(false)

#define IPL_SHMCONDITION_SIGNALALL_OR_ABORT(C) do if( C.signalAll() )\
    { IPL_ABORT("error signaling shmcondition"); } while(false)

#endif /* OSAL_SHMCONDITION_HXX */
