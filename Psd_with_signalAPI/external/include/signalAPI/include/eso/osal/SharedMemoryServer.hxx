/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_SHAREDMEMORYSERVER_HXX
#define OSAL_SHAREDMEMORYSERVER_HXX

#include <ipl_config.h>

#include <osal/osal_dso.h>
#include <osal/osal.hxx>
#include <osal/IPC.hxx>
#include <osal/SharedMemoryBase.hxx>
#include <osal/UnicodeString.hxx>

namespace osal {

    /**
    * \brief
    *     Server Side Implementation of Shared Memory

    *     The server side of a shared memory object is responsible for
    *     initially creating an object of a certain size in the system
    *     that other processes can attach to via \c SharedMemoryClient.
    *
    *     There is a peculiarity of IPC objects like shared memory or
    *     semaphores on POSIX. These objects persist in the system even if
    *     there are no processes around that reference them any more. Thus
    *     the applications needs to deal with removing the objects' names
    *     from the system. This is different on WIN32 where IPC objects
    *     are always deleted automatically if no users are left.
    *
    *     If deletion of those IPC objects is not dealt with correctly on
    *     POSIX system than the associated memory will not be freed
    *     automatically. Also if an application tries to setup a new
    *     shared memory server under the same name at a later time then
    *     the object will already exist, although no users are around.
    *     See create() and \c CreationStrategy for a discussion of what
    *     can be done in such cases.
    *
    *    For handling deletion see the \c delete_on_close flag in the
    *    constructor, the close() function and the deleteName() function.
    **/
    class OSAL_EXPORT SharedMemoryServer :
        public SharedMemoryBase,
        public Creatable
    {
    public: // types

    public: // functions

        /**
        * \brief
        *     Creates an Invalid Shared Memory Object
        * \param[in]
        *     delete_on_close Determines whether at close() time a
        *     previously created/opened shared memory object will be
        *     attempted to be deleted.
        **/
        SharedMemoryServer(const bool delete_on_close = true) :
            m_server_handle(delete_on_close)
        { }

        //! close object if one is currently opened
        virtual ~SharedMemoryServer()
        {
            // needs to be implemented here, to get overriden close
            // function called.
            if( this->isValid() && SharedMemoryServer::close() ) // BRANCH_COVERAGE_UNTESTABLE
            {
                IPL_WARN("Error closing SharedMemory");
                ipl_error.ack();
            }
        }

        /**
        * \brief
        *     Create a New Shared Memory Object in the System

        *    Shared memory objects, though treated very similarly to
        *    files, are not generally accessed via the file system
        *    (although on some systems they are put there). Thus \c
        *    name does not refer to a file system path but is simply
        *    an identifier for the shared memory object in the
        *    system.
        *
        *    Still the properties for \c name are similar to those of
        *    a path. The maximum length of \c name is limited by
        *    osal::Path::MAX_COMPONENT_LEN. The application should
        *    not put any path separators (see osal::Path::SEPARATOR)
        *    into \c name for portability reasons. OSAL will adjust
        *    \c name to fit whatever requirements the underlying
        *    operating system has got. Thus the application should
        *    merely treat \c name as a label for the to be created
        *    shared memory object.
        *
        *    What happens if there is already an object of the same
        *    name present is determined by \c strategy. Please refer
        *    to \c CreationStrategy for more information. Regarding
        *    the circumstances when shared memory objects are deleted
        *    again from the system please see
        *    SharedMemoryServer::close().
        *
        *     The server side will always have read/write/execute
        *     access to the shared memory area, if it is actually
        *     created. If due to \c strategy an existing object is
        *     opened then the access rights may differ.
        *
        *    The given size determines the desired size of the newly
        *    created shared memory object. This size cannot be
        *    changed after creation anymore. Arbitrary mappings of
        *    the available shared memory area can be created by
        *    server and clients via
        *    SharedMemoryBase::createMapping(), however.
        *
        *    Note that while there are no specific requirements for
        *    \c size, that the operating system will always allocate
        *    whole pages i.e. if you allocate only a few bytes there
        *    will still be a complete memory page be allocated for
        *    this purpose. See osal::SystemInfo::getPagesize() for
        *    obtaining that number.
        *
        *    There can also be restrictions in minimum or maximum
        *    size of a shared memory object. Usually the minimum size
        *    is one byte while the maximum size varies from system to
        *    system. The allocation of up to several megabytes can be
        *    considered portable, however.
        *
        *    If there is currently already a shared memory object
        *    associated with this object then an attempt is made to
        *    close that one before a new object is created. If
        *    closing fails then the operation will not continue and
        *    \c true is returned.
        *
        *    The access rights for the newly created shared memory
        *    object will be such that any other process with the same
        *    authority (i.e. user ID) or higher (i.e.
        *    root/Administrator) will be able to access it.
        * \return
        *     \c true on error, \c false otherwise
        * \errorindicator
        *     via return code, via isValid()
        * \errors
        *    If close() fails then the error from it is kept.
        *    Otherwise:
        *
        *     FileAccessError attached with SystemError with IDs:
        *
        *     - NO_ACCESS / PERMISSION_DENIED
        *         - if the object aready exists and the caller
        *         doesn't have permission to access it
        *         - object does not exist and creation is not
        *         allowed
        *         - due to \c strategy resizing or deleting of an
        *         existing object was attempted but permission is
        *         denied
        *     - ALREADY_EXISTS / FILE_EXISTS if the object already
        *         exists and \c strategy does not allow that
        *     - BAD_PATH / PATH_TOO_LONG if \c name is too long
        *     - NOT_ENOUGH_SPACE / FS_NO_SPACE if there is not enough
        *     space for creation of the object with that size
        *
        *     SystemError with IDs:
        *
        *     - SYSTEM_RESSOURCES_EXHAUSTED if too many files or
        *     shared memory objects are open in the process or the
        *     system
        *
        *     - NOT_IMPLEMENTED the shared memory cannot be created
        *     due to lack in hardware or software support
        *
        *     - UNKNOWN_ERROR on other occasions
        *
        *    ipl::CommonError with IDs:
        *
        *    - INVALID_PARAMETER if the given \c name is invalid
        *    - PAR_OUT_OF_RANGE if \c name is too long
        **/
        bool create(const char *name, const size_t size,
            const CreationStrategy &strategy = FAIL_IF_EXISTS);

        //! \brief
        //! variant of create(const char*, const
        //! size_t) taking an STL string
        bool create(const ipl::string &name, const size_t size,
            const CreationStrategy &strategy = FAIL_IF_EXISTS)
        { return this->create(name.c_str(), size, strategy); }

        //! \brief
        //! variant of create(const char*, const
        //! size_t) taking a unicode string
        bool create(const osal::UnicodeString &name,
            const size_t size,
            const CreationStrategy &strategy = FAIL_IF_EXISTS);

        /**
        * \brief
        *     Delete the Shared Memory Object Identifier from the
        *     System

        *     This function only has an effect on POSIX sytems. WIN32
        *     always returns \c false without doing anything.
        *
        *     On POSIX systems this function attempts to remove the
        *     name associated with the currently opened shared memory
        *     object from the system.
        *
        *     If currently no valid shared memory object is opened
        *     (i.e. isValid() returns \c false) or if the shared
        *     memory object's name has already been removed previously
        *     then nothing is done and \c false is returned.
        *
        *     This function is automatically called during a call to
        *     close() in case \c delete_on_close was set to \c true
        *     during construction time.
        *
        *     If the system indicates that the shared memory object's
        *     name is not present then OSAL assumes the object has
        *     already been deleted by someone else in the system and
        *     returns \c false without raising an error.
        *
        *     Deleting the shared memory object name has the following
        *     consequences:
        *
        *     - no new clients will be able to attach to the shared
        *     memory object any more (not true on WIN32, on WIN32 the
        *     object is only automatically deleted by the system as
        *     soon as all clients release it)
        *     - as soon as any left clients have detached from the
        *     shared memory object the system will erase the shared
        *     memory object automatically
        *     - it is possible to create a new shared memory object
        *     under the same name (not true on WIN32)
        *
        *     An explicit call to this function without closing the
        *     shared memory object makes sense in case there is a
        *     defined number of users of the shared memory object.
        *     Then as soon as all users got access to the object the
        *     server can remove the object's name from the system,
        *     thereby making it reference counted by the system and
        *     avoiding dead shared memory objects lingering in the
        *     system in case of application crashes.
        * \return
        *     \c true on error, \c false on success
        * \errorindicator
        *     via return code
        * \errors
        *     FileAccessError attached with a SysError with IDs:
        *
        *     - PERMISSION_DENIED / NO_ACCESS in case the caller is
        *     lacking permission to remove the shared memory name
        *
        *     - UNKNOWN_ACCESS_ERROR / UNKNOWN_ERROR on other problems
        **/
        bool deleteName();

        /**
        * \brief
        *     Detach from Shared Memory Object and Possibly Delete it

        *     Additionally to what SharedMemoryBase::close() does this
        *     function attempts to delete the shared memory object
        *     from the system if the class was instantiated with \c
        *     delete_on_close set to \c true. This is done via calling
        *     deleteName().
        * \return
        *     \c true on error,  \c false on success
        * \errorindicator
        *     via return code
        * \errors
        *     osal::SysError with ID INTEGRITY_ERROR on severe errors
        **/
        virtual bool close();

    public: // static functions
        /**
        * \brief
        *     Does the same as deleteName() but can be called without
        *     an object for identifier \c name
        * \see
        *     deleteName()
        **/
        static bool deleteName(const char *name);

        //! variant of deleteName(const char*) taking STL string objects
        static bool deleteName(const ipl::string &name)
        {
            return deleteName(name.c_str());
        }

        //! \brief
        //! variant of deleteName(const char*) taking unicode string
        //! objects
        static inline bool deleteName(const osal::UnicodeString &name);

    private: // data
        SharedMemoryServerHandle m_server_handle;
    };

}  // end of namespace osal

#if defined IPL_OS_POSIX || defined IPL_OS_INTEGRITY
#    include "posix/SharedMemoryServer.inl"
#elif defined IPL_OS_WINPC
#    include "win32/SharedMemoryServer.inl"
#else
#    error "error undefined IPL_OS_ variant"
#endif

#endif
