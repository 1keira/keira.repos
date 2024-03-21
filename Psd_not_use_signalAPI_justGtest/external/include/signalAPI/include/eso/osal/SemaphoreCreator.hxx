/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_SEMAPHORECREATOR_HXX
#define OSAL_SEMAPHORECREATOR_HXX

#include <ipl_config.h>

#include <osal/osal_dso.h>
#include <osal/osal.hxx>
#include <osal/IPC.hxx>
#include <osal/SemaphoreBase.hxx>
#include <osal/UnicodeString.hxx>

namespace osal {

    /**
    * \brief
    *     Creator side for Semaphore Objects

    *     This class implements the creator side for semaphore objects.
    *     This means that this class is responsible for creating a
    *     semaphore object in the system and thus providing it to \c
    *     SemaphoreClient.
    *
    *     For merely attaching to an existing semaphore object please
    *     refer to \c SemaphoreClient.
    *
    *     The general properties of a semaphore are defined and explained
    *     by \c SemaphoreBase. This class merely adds the possibility to
    *     actually create/open a named semaphore such that the operations
    *     provided by SemaphoreBase become accessible.
    *
    *     Like it is the case with \c SharedMemoryServer on POSIX systems
    *     there is a peculiarity with regards to creation and deletion of
    *     semaphores. If not correctly deleted, semaphore objects stay
    *     persistent in the system. An application trying to create a
    *     semaphore under the same name will then have to deal with the
    *     situation of the semaphore already existing.
    *
    *     To support handling these situations on POSIX please refer to
    *     the \c delete_on_close flag of the SemaphoreCreator()
    *     constructor, the \c CreationStrategy, the close() function and
    *     the deleteName() function.
    **/
    class OSAL_EXPORT SemaphoreCreator :
        public SemaphoreBase,
        public Creatable
    {
    public: // member functions

        /**
        * \brief
        *     Creates an invalid object
        **/
        SemaphoreCreator(const bool delete_on_close = true) :
            m_creator_handle(delete_on_close)
        {}

        /**
        *
        **/
        virtual ~SemaphoreCreator()
        {
            if( this->isValid() && SemaphoreCreator::close() ) // BRANCH_COVERAGE_UNTESTABLE
            {
                IPL_WARN("error closing semaphore");
                ipl_error.ack();
            }
        }

        /**
        * \brief
        *     Create the Given Semaphore Object

        *    If currently a semaphore object is already opened then first
        *    an attempt is made to close it. If closing fails then the
        *    operation will not continue and \c true is returned.
        *
        *     Attempts to create a new semaphore object in the system using
        *     \a name. If \a name already exists then further handling
        *     depends on \a strategy. Please see CreationStrategy for
        *     more information.
        *
        *     The parameter \a initial_count determines the initial value of
        *     the counter associated with the semaphore object. By default
        *     it is set to one. That allows to use the semaphore like a
        *     binary lock i.e. one process can take the lock via take() and
        *     if others also want to take() the semaphore they will block
        *     until the "owning" process calls release() on it.
        *
        *     The \a initial_count only comes into effect if the semaphore
        *     actually is created. Otherwise the semaphore count is
        *     undefined.
        *
        *    The maximum length of \a name is limited by
        *    osal::Path::MAX_COMPONENT_LEN. The application should not put
        *    any path separators (see osal::Path::SEPARATOR) into \a name
        *    for portability reasons. OSAL will adjust \a name to fit
        *    whatever requirements the underlying operating system has got.
        *    Thus the application should merely treat \a name as a label
        *    for the to be created semaphore object.
        * \return
        *     \c true on error, \c false on success
        * \errorindicator
        *     via return code, isValid() member function
        * \errors
        *    If close() fails then the error from it is kept.
        *    Otherwise:
        *
        *    ipl::CommonError with IDs:
        *
        *    - INVALID_PARAMETER if the given \a name is invalid
        *    - PAR_OUT_OF_RANGE if \a name is too long
        *
        *    osal::FileAccessError attached with an osal::SysError
        *    with IDs:
        *
        *    - ALREADY_EXISTS / FILE_EXISTS if the object already
        *    exists and \a strategy doesn't allow that
        *    - NO_ACCESS / PERMISSION_DENIED if the caller has been
        *    denied access to \a name
        *    - BAD_PATH / INVALID_PATH if the system doesn't allow \a
        *    name for semaphores, if \a name is too long or if \a
        *    name is simply not existing
        *    - TOO_MANY_OPEN_FILES / SYSTEM_RESSOURCES_EXHAUSTED if
        *    no more files can be opened in the callers process or
        *    the system
        *    - UNKNOWN_ACCESS_ERROR with
        *        - INTEGRITY_ERROR on severe, unexpected errors
        *        - UNKNOWN_ERROR on unknown errors
        **/
        bool create(const char *name,
            const size_t initial_count = 1,
            const CreationStrategy strategy = FAIL_IF_EXISTS);

        //! \brief
        //! variant of create(const char*, const size_t, const
        //! CreationStrategy) taking an STL string
        bool create(const ipl::string &name,
            const size_t initial_count = 1,
            const CreationStrategy strategy = FAIL_IF_EXISTS)
        {
            return this->create(name.c_str(),
                initial_count, strategy);
        }

        //! \brief
        //! variant of create(const char*, const size_t, const
        //! CreationStrategy) taking a unicode string
        bool create(const osal::UnicodeString &name,
            const size_t initial_count = 1,
            const CreationStrategy strategy = FAIL_IF_EXISTS);

        /**
        * \brief
        *     Delete the Name of the Current Semaphore from the System

        *     On WIN32 this function does nothing and always returns
        *     \c false.
        *
        *     On POSIX this function attempts to delete the name
        *     of the currently associated semaphore object.
        *
        *     If currently no semaphore object is associated (i.e.
        *     isValid() returns \c false) then nothing is done and \c
        *     false is returned.
        *
        *     If the name of the currently associated semaphore object
        *     has already been deleted previously then nothing is done
        *     and \c false is returned.
        *
        *     If the system indicated that the name of the currently
        *     associated semaphore object isn't existing any more then
        *     OSAL assumes somebody else in the system has already
        *     deleted the semaphore name and returns \c false.
        *
        *     Otherwise the semaphore's name is deleted thereby
        *     causing the following:
        *
        *     - Reference counting is enabled by the operating system
        *     i.e. when the last user of the semaphore goes away the
        *     object is freed
        *     - No more applications can refer to the semaphore object
        *     by means of its name (although an application could
        *     still refer to it by means of its file descriptor e.g.
        *     by passing it on to a child process)
        *     - An application can create a new distict semaphore
        *     object of the same name as the deleted object
        *
        *     This function is automatically called by \c close() in
        *     case \c delete_on_close was set to \c true at
        *     construction time.
        *
        *     Explicitly calling this function without actually
        *     closing the semaphore object itself makes sense if the
        *     semaphore has got a defined number of users. In that
        *     case when all users got access to the semaphore it's
        *     name can be deleted to enable the operating systems
        *     reference counting and avoid having a dead semaphore
        *     object lingering around after all users have gone away.
        **/
        bool deleteName();

        /**
        * \brief
        *     Detach from the Semaphore and Possibly Delete it

        *     Additionally to what SemaphoreBase::close() does this
        *     function calls deleteName() in case \c delete_on_close
        *     was set to \c true during construction time.
        **/
        virtual bool close();
    public: // static functions

        /**
        * \brief
        *     Deletes the Semaphore identifier by \c name

        *     Does the same as deleteName() but without an object.
        * \see
        *     deleteName()
        **/
        static bool deleteName(const char *name);

        //! deleteName(const char*) for STL string objects
        static bool deleteName(const ipl::string &name)
        {
            return deleteName(name.c_str());
        }

        //! deleteName(const char*) for unicode string objects
        inline static bool deleteName(const osal::UnicodeString &name);
    protected:
        SemaphoreCreatorHandle m_creator_handle;
    };

}  // end of namespace osal

#if defined IPL_OS_POSIX || defined IPL_OS_INTEGRITY
#    include "posix/SemaphoreCreator.inl"
#elif defined IPL_OS_WINPC
#    include "win32/SemaphoreCreator.inl"
#else
#    error "error undefined IPL_OS_ variant"
#endif

#endif
