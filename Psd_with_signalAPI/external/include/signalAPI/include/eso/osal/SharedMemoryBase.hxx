/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_SHAREDMEMORY_HXX
#define OSAL_SHAREDMEMORY_HXX

#include <ipl_config.h>

#include <common/Macros.hxx>
#include <common/types/map.hxx>
#include <common/NonCopyable.hxx>

#include <osal/osal_dso.h>
#include <osal/osal.hxx>
#include <osal/MemMapping.hxx>

#ifdef IPL_OS_POSIX
#    include "posix/SharedMemoryDefs.hxx"
#elif defined IPL_OS_WINPC
#    include "win32/SharedMemoryDefs.hxx"
#elif defined IPL_OS_INTEGRITY
#    include "integrity/SharedMemoryDefs.hxx"
#else
#    error "error undefined IPL_OS_ variant"
#endif

namespace osal {

    /**
    * \brief
    *     Base Class for Shared Memory Objects

    *     Shared memory objects allow different processes within the same
    *     system to efficiently share a certain area of memory.
    *
    *     This is realized via the system allocating system memory that is
    *     mapped into the address space of processes that want to
    *     communicate with each other. Changes performed by one process
    *     are immediatly visible to all other participating processes
    *     without the need to copy data between them.
    *
    *     While this provides maximum efficiency for exchanging data, the
    *     shared memory object itself doesn't provide a means of
    *     synchronization between participating processes. In principle
    *     arbitrary other means of synchronization can be used to allow
    *     for safe access of the shared memory region (like any object
    *     that allows to efficiently block at and that can be signaled
    *     from other processes in the system e.g. a socket).
    *
    *     The probably easiest and fastest way of synchronization for
    *     shared memory access, however, are the \c osal::ShmMutex and \c
    *     osal::ShmCondition objects provided by OSAL. Also \c
    *     osal::SemaphoreClient / osal::SemaphoreCreator can be used.
    *
    *     This is a base class that cannot be used by itself. Use
    *     SharedMemoryServer or SharedMemoryClient to actually work with
    *     shared memory objects.
    **/
    class OSAL_EXPORT SharedMemoryBase :
        public ipl::NonCopyable
    {
    protected: // member functions

        //! creates an invalid shared memory object
        SharedMemoryBase() :
            m_handle()
        { }

        /**
        * \brief
        *     Closes the Shared Memory, if one is Opened
        **/
        virtual ~SharedMemoryBase()
        {
            if( this->isValid() && SharedMemoryBase::close() ) // BRANCH_COVERAGE_UNTESTABLE
            {
                IPL_WARN("Error closing SharedMemory");
                ipl_error.ack();
            }
        }

    public: // member functions
        /**
        * \brief
        *     Detach from an Opened Shared Memory Object

        *     If isValid() returns \c false then nothing happens and
        *     \c false is returned.
        *
        *     Otherwise any still active shared memory mappings
        *     registered at createMapping() will be invalidated and
        *     the shared memory object is closed.
        * \errorindicator
        *     via return code
        * \return
        *      \c true on error, \c false otherwise
        * \errors
        *     osal::SysError with ID INTEGRITY_ERROR on severe errors
        **/
        virtual bool close();

        /**
        * \brief
        *     Create an Actual Memory Mapping for a Shared Memory
        *     Object

        *     Creates a memory mapping for the currently opened shared
        *     memory object. The memory mapping will be accessible
        *     according to \c access.
        *
        *     The \c off parameter is restricted by the page size for
        *     memory mappings. Please see
        *     osal::MemMapping::getAlignment().
        *
        *     About the \c suggested_address the MemMapping
        *     constructor. The address is restricted by the start
        *     address alignment. Please see
        *     osal::MemMapping::getStartAddrAlignment().
        * \errorindicator
        *     via isValid() member of the returned MemMapping object
        * \see
        *     MemMapping(const FileHandle&, const MemAccessFlags&,
        *     const size_t, const size_t)
        **/
        MemMapping createMapping(
            const MemMapping::MemAccessFlags &access,
            const size_t length, const size_t off,
            void *suggested_addr = NULL,
            bool get_ringbuffer = false)
        {
            MemMapping mapping(m_handle,
                access, length, off, suggested_addr,
                get_ringbuffer );

            if( mapping.isValid() )
            {
                m_mappings.insert( ipl::make_pair(mapping.constAddr(),
                    mapping) );
            }

            return mapping;
        }

        /**
        * \brief
        *     Remove the Given Memory Mapping

        *     The memory mapping \c mapping needs to be
        *     previously established via createMapping() of the same
        *     object instance as this one.
        *
        *     After return of this function the mapping will no longer
        *     be valid and the object should be discarded.
        * \return
        *     true on error, false on success
        * \errorindicator
        *     via return code
        * \errors
        *     see MemMapping::destroy()
        *
        *     Additionally an ipl::CommonError with ID INVALID_USAGE
        *     is raised if \c mapping is unknown to this instance.
        **/
        bool removeMapping(const MemMapping &mapping);

        //! \brief
        //! returns whether currently a valid shared memory object is
        //! opened
        bool isValid() const
        { return m_handle.isValid(); }

        /**
        * \brief
        *     Returns the size of the Shared Memory Object

        *     The size returned here is not necessarily the size
        *     specified at creation time of the shared memory object.
        *     The value is queried from the system by this function
        *     call.
        *
        *     You might get a size rounded up to the nearest multiple
        *     of the system pagesize. The complete range of memory is
        *     available for use in this case even if it is bigger than
        *     what has been specified at creation time.
        *
        *     On POSIX you will usually get the size that has been
        *     specified on creation time. In theory the size might
        *     change, however, if somebody fiddles with the shared
        *     memory object by terms of calling ftruncate() on it, for
        *     example. This should be considered harmful use, though.
        * \return
        *     zero on error, the size of the associated shared memory
        *     object otherwise
        * \errorindicator
        *     via return of zero size
        * \errors
        *     ipl::CommonError with ID INVALID_USAGE if
        *     this->isValid() returns \c false
        *
        *     osal::SysError with IDs:
        *
        *     - IO_FAILURE
        *     - INTEGRITY_ERROR
        *     - OUT_OF_MEMORY
        *     - UNKNOWN_ERROR
        *
        *     on severe system errors / out of memory condition.
        **/
        size_t getSize() const;

    protected: // data
        SharedMemoryHandle m_handle;
        //! any registered memory mappings
        ipl::map< const void*, MemMapping > m_mappings;
    private: // functions
        //! initializes function for Osal init object
        static bool init(const bool lazy);
        static void exit();

        friend class Osal;
    };

}  // end of namespace osal

#ifdef IPL_OS_POSIX
#    include "posix/SharedMemoryBase.inl"
#elif defined IPL_OS_WINPC
// needs nothing
#elif defined IPL_OS_INTEGRITY
#    include "posix/SharedMemoryBase.inl"
#else
#    error "error undefined IPL_OS_ variant"
#endif

#endif
