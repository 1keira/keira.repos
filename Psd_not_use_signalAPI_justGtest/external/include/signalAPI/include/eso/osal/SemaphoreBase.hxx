/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_SEMAPHOREBASE_HXX
#define OSAL_SEMAPHOREBASE_HXX

#include <ipl_config.h>

#include <common/Macros.hxx>
#include <common/NonCopyable.hxx>

#include <osal/osal_dso.h>
#include <osal/osal.hxx>

#if defined IPL_OS_POSIX
#    include "posix/SemaphoreDefs.hxx"
#elif defined IPL_OS_WINPC
#    include "win32/SemaphoreDefs.hxx"
#elif defined IPL_OS_INTEGRITY
#    include "integrity/SemaphoreDefs.hxx"
#else
#    error "error undefined IPL_OS_ variant"
#endif

namespace osal {

    /*!
        \brief Semaphore Object for Inter-Process-Synchronization

        A semaphore is a locking object for use between different processes
        on the system. It is a named object that can be created/opened by
        any process via a common identifier.

        A semaphore is generally considerably less efficient than an
        osal::Mutex, because a system call is performed upon locking it,
        even if there is no contention for the lock.

        For that reason a semaphore should only be used for
        inter-process-synchronization and then only if there is no better
        suitable mechanism available like e.g. an ShmMutex when shared memory
        is available between the processes.

        A semaphore works differently than other locking mechanisms. There is a
        counter associated with it that can be incremented multiple times by any
        process that has access to it. The increment is equivalent to unlocking
        the semaphore. Any other process can also decrement the counter which
        is the equivalent of locking the semaphore.

        Locking the semaphore will only cause the calling process to block if
        the current count of the semaphore is zero. Then the call will block
        until some other process in the system unlocks the semaphore by means
        of incrementing it again.

        This way a semaphore can also be used to manage a limited number of
        ressources in the system e.g. 10 buffers that are available for a
        certain operation. Then if no more buffers are available locking the
        semaphore blocks the caller until somebody returns one again via
        unlocking the semaphore.

        So the difference to an osal::Mutex is that a semaphore is always
        recursive. But even more so, a semaphore does not have a dedicated
        "owner". Instead different processes can lock/unlock the semaphore in
        parallel as long as the semaphore count doesn't hit zero in which case
        locking will block until another process unlocks.

        To make this difference more clear the operations on the semaphore
        aren't called lock/unlock but take/release.

        This class is only a base class that cannot be used on its own.
        Please refer to SemaphoreMgr and SemaphoreClient for actually
        accessible classes.
    */
    class OSAL_EXPORT SemaphoreBase: public ipl::NonCopyable {

    public:

        //! \brief Closes Semaphore if needed
        virtual ~SemaphoreBase() {
            if(isValid() && SemaphoreBase::close()) { // BRANCH_COVERAGE_UNTESTABLE
                IPL_WARN("error closing semaphore!");
                ipl_error.ack();
            }
        }

        /*!
            \brief Release the Semaphore by Incrementing its Counter by one

            If the semaphore counter was zero upon calling this function and
            there are other processes waiting to take the semaphore then one of
            those waiters will be waked up for decrementing the semaphore.

            \return \c true on error, \c false on success

            \errorindicator via return code

            \errors ipl::CommonError with ID INVALID_USAGE if the current
            object is not valid.

            osal::SysError with IDs:
            - INTEGRITY_ERROR on severe errors
            - SYSTEM_RESSOURCES_EXHAUSTED if the maximum count has been reached
              for the semaphore. In that case release() can't be called before
              at least one process in the system called take() on it to decrease
              the semaphore counter again
        */
        bool release() const;

        /*!
            \brief Take the Semaphore by Decrementing its Counter by one

            If the semaphore counter is currently zero then the call won't
            return before some other process in the system releases the
            semaphore by means of incrementing its counter.

            Otherwise the semaphore counter will be decremented and the call
            returns immediatly.

            \return \c true on error, \c false otherwise

            \errorindicator via return code

            \errors
            - ipl::CommonError with ID INVALID_USAGE if isValid()
              returns \c false
            - osal::SysError with ID INTEGRITY_ERROR on severe
              errors, or on deadlocks
        */
        bool take() const;

        /*!
            \brief Attempt Decrementing the Semaphore

            Does the same as take() does but if the semaphore counter is
            currently zero and the call would need to block until somebody
            calls release() on the semaphore then the call will return without
            taking the semaphore.

            \return TRY_TAKE_SUCCESS if the semaphore counter could be
            decremented, TRY_TAKE_ERROR on error, TRY_TAKE_NOLUCK if immediatly
            decrementing the semaphore counter without blocking was not possible

            \errorindicator via TRY_TAKE_ERROR return

            \errors same as with take()
        */
        int_fast8_t tryTake() const;

        /*!
            \brief Attempt Decrementing the Semaphore until \c p_when

            Does the same as tryTake() but allows the call to block for a
            certain time to wait for the semaphore to become available.
            \c p_when denotes the relative time in milliseconds before the call
            gives up and returns TRY_TAKE_NOLUCK.

            \return same as tryTake()

            \errorindicator via return code

            \errors same as with tryTake()
        */
        int_fast8_t tryTakeTimeout(const osal::TimeT &p_timeout_ms) const;

        bool isValid() const { return m_handle.isValid(); }

        /*!
            \brief Close Semaphore if opened

            \errorindicator via return code

            \return \c true on error, \c false otherwise

            \errors SysError with ID INTEGRITY_ERROR on severe errors
        */
        virtual bool close();

        /*!
            \brief Return values for tryTake() and tryTakeTimeout()
            \{
        */
        static const int_fast8_t TRY_TAKE_SUCCESS = 0;  //!< \brief Success
        static const int_fast8_t TRY_TAKE_ERROR = -1;   //!< \brief Error
        static const int_fast8_t TRY_TAKE_NOLUCK = 1;   //!< \brief Couldn't acquire lock
        /*!
            \}
        */

    protected:
        SemaphoreBase() {};

        mutable SemaphoreHandle m_handle;
    };

}  // end of namespace osal

#define IPL_SEM_TAKE_OR_ABORT(SEM) do if( SEM.take() )\
    { IPL_ABORT("error taking semaphore"); } while(false)

#define IPL_SEM_RELEASE_OR_ABORT(SEM) do if( SEM.release() )\
    { IPL_ABORT("error releasing semaphore"); } while(false)

#endif
