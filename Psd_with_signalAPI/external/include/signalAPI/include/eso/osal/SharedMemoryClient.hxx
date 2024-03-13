/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_SHAREDMEMORYCLIENT_HXX
#define OSAL_SHAREDMEMORYCLIENT_HXX

#include <ipl_config.h>

#include <osal/osal_dso.h>
#include <osal/osal.hxx>
#include <osal/SharedMemoryBase.hxx>
#include <osal/UnicodeString.hxx>

namespace osal {

    /**
    * \brief
    *     Client Side Implementation of Shared Memory

    *     The client side of a shared memory object attaches to a shared
    *     memory object already present in the system, created by
    *     \c SharedMemoryServer.
    **/
    class OSAL_EXPORT SharedMemoryClient :
        public SharedMemoryBase
    {
    public: // functions

        //! creates an invalid shared memory object
        SharedMemoryClient() { }

        /**
        * \brief
        *     Attach to the given Shared Memory Object

        *    If currently a shared memory object is already opened
        *    then first an attempt is made to close it. If closing
        *    fails then the operation will not continue and \c true
        *    is returned.
        *
        *     Regarding the requirements and semantics of \c name
        *     please have a look at SharedMemoryServer::create(const
        *     char*, const MemMapping::MemAccessFlags&, const size_t).
        *
        *     The access flags determine what kinds of memory mapping
        *     can be obtained for the shared memory object later on.
        *     Note, however, that the granularity of those access
        *     flags is limited. Please see \c MemAccessFlags for more
        *     information about that.
        *
        *     After successful attachment to the shared memory object
        *     its size is available via SharedMemoryBase::getSize().
        * \return
        *     \c true on error, \c false otherwise
        * \errorindicator
        *     via return code, via isValid()
        * \errors
        *    If close() fails then the error from it is kept.
        *    Otherwise:
        *
        *     osal::SysError with IDs:
        *
        *     - PERMISSION_DENIED if you're not allowed to access \c
        *     name at all or using the given \c access
        *     - SYSTEM_RESSOURCES_EXHAUSTED if there are too many file
        *     descriptors open in the system or process
        *     - NOT_IMPLEMENTED if the OS doesn't support shared
        *     memory, or doesn't support shared memory using \c access
        *
        *     osal::FileAccessError with IDs:
        *
        *     - PATH_TOO_LONG if \c name is too long
        *     - BAD_PATH if \c name isn't existing
        *
        *    ipl::CommonError with IDs:
        *
        *    - INVALID_PARAMETER if the given \c name is invalid
        *    - PAR_OUT_OF_RANGE if \c name is too long
        **/
        bool attach(const char *name,
            const MemMapping::MemAccessFlags &access);

        //! \brief
        //! variant of attach(const char*, const
        //! MemMapping::MemAccessFlags&) taking an STL string
        bool attach(const ipl::string &name,
            const MemMapping::MemAccessFlags &access)
        {
            return this->attach(name.c_str(), access);
        }

        //! \brief
        //! variant of attach(const char*, const
        //! MemMapping::MemAccessFlags&) taking a unicode string
        bool attach(const osal::UnicodeString &name,
            const MemMapping::MemAccessFlags &access);
    };

}  // end of namespace osal

#if defined IPL_OS_POSIX || defined IPL_OS_INTEGRITY
#    include "posix/SharedMemoryClient.inl"
#elif defined IPL_OS_WINPC
#    include "win32/SharedMemoryClient.inl"
#else
#    error "error undefined IPL_OS_ variant"
#endif

#endif
