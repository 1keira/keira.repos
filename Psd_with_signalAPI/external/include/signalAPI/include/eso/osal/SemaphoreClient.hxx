/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_SEMAPHORECLIENT_HXX
#define OSAL_SEMAPHORECLIENT_HXX

#include <ipl_config.h>

#include <osal/osal_dso.h>
#include <osal/osal.hxx>
#include <osal/SemaphoreBase.hxx>
#include <osal/UnicodeString.hxx>

namespace osal {

    /**
    * \brief
    *     Client side for Semaphore Objects

    *     This class implements the client side for semaphore objects.
    *     Client in this context means that this class is not responsible
    *     for creating a semaphore object in the system but only attached
    *     to an existing one.
    *
    *     For creating a semaphore object please refer to \c
    *     SemaphoreCreator.
    *
    *     The general properties of a semaphore are defined and explained
    *     by \c SemaphoreBase. This class merely adds the possibility to
    *     actually open a named semaphore such that the operations
    *     provided by SemaphoreBase become accessible.
    **/
    class OSAL_EXPORT SemaphoreClient :
        public SemaphoreBase
    {
    public: // member functions
        /**
        * \brief
        *     Creates an invalid object
        **/
        SemaphoreClient()
        {}

        /**
        * \brief
        *     Attach to Given Semaphore Object

        *     If currently a semaphore object is already opened then
        *     first an attempt is made to close it. If closing fails
        *     then the operation will not continue and \c true is
        *     returned.
        *
        *     If there doesn't exist an object under the given name
        *     then attaching fails.
        *
        *     Regarding the requirements for the \c name parameter please
        *     refer to SemaphoreCreator::create().
        * \return
        *     \c true on error, \c false on success
        * \errorindicator
        *     via return code, isValid() member function
        * \errors
        *    If close() fails then the error from it will be kept.
        *    Otherwise:
        *
        *    ipl::CommonError with IDs:
        *
        *    - INVALID_PARAMETER if the given \c name is invalid
        *    - PAR_OUT_OF_RANGE if \c name is too long
        *
        *    osal::FileAccessError attached with an osal::SysError
        *    with IDs:
        *
        *    - NO_ACCESS / PERMISSION_DENIED if the caller has been
        *    denied access to \c name
        *    - BAD_PATH / INVALID_PATH if the system doesn't allow \c
        *    name for semaphores, if \c name is too long or if \c
        *    name is simply not existing
        *    - TOO_MANY_OPEN_FILES / SYSTEM_RESSOURCES_EXHAUSTED if
        *    no more files can be opened in the callers process or
        *    the system
        *    - UNKNOWN_ACCESS_ERROR with
        *        - INTEGRITY_ERROR on severe, unexpected errors
        *        - UNKNOWN_ERROR on unknown errors
        **/
        bool attach(const char *name);

        //! variant of attach(const char*) taking an STL string
        bool attach(const ipl::string &name)
        {
            return this->attach(name.c_str());
        }

        //! variant of attach(const char*) taking a unicode string
        bool attach(const osal::UnicodeString &name);
    };

}  // end of namespace osal

#if defined IPL_OS_POSIX || defined IPL_OS_INTEGRITY
#    include "posix/SemaphoreClient.inl"
#elif defined IPL_OS_WINPC
#    include "win32/SemaphoreClient.inl"
#else
#    error "error undefined IPL_OS_ variant"
#endif

#endif
