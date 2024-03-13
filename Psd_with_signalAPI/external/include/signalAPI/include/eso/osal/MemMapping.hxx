/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_MEMMAPPING_HXX
#define OSAL_MEMMAPPING_HXX

#include <ipl_config.h>

#include <osal/osal_dso.h>
#include <osal/osal.hxx>

#if defined IPL_OS_POSIX || defined IPL_OS_INTEGRITY
#    include "posix/BinFileDefs.hxx"
#    include "posix/MemMappingDefs.hxx"
#elif defined IPL_OS_WINPC
#    include "win32/BinFileDefs.hxx"
#    include "win32/MemMappingDefs.hxx"
#else
#    error "error undefined IPL_OS_ variant"
#endif

namespace osal
{

struct SharedMemoryHandle;

/**
 * \brief
 *     Creation of memory mappings from memory-mappable objects

 *     This type is used by MemBinFileBase, MemBinFileR,
 *     MemBinFileRW and SharedMemoryBase to create actual memory
 *     mappings for an open file or shared memory object.
 *
 *     In this context this type can only be validly constructed by way
 *     of MemBinFileR::createMapping(),
 *     MemBinFileRW::createMapping() or
 *     SharedMemoryBase::createMapping(). It also can only be correctly
 *     destructed by way of MemBinFileBase::removeMapping() or
 *     ShareddMemoryBase::removeMapping().
 *
 *     This object contains actual information about a setup memory
 *     mapping.
 **/
class OSAL_EXPORT MemMapping
{
public:
    /**
     * \brief
     *     Access flags for memory mappings

     *     Access flags involve three classic permissions:
     *
     *     - read access to memory locations
     *     - write access to memory locations
     *     - execution of code in memory locations
     *
     *     The access mode is enforced by the OS via hardware
     *     support. Violation of the access mode usually results in
     *     termination of the calling process (on POSIX you will
     *     get a SIGSEGV signal with the violating memory address
     *     as data).
     *
     *     Note that due to the low-level nature of how these
     *     access modes are realised it is often not possible to
     *     use arbitrary combination of the flags. In general the
     *     following can be assumed:
     *
     *     - if write permission is denied then trying to write to
     *     the memory location will result in an access violation
     *
     *     The following can, however, not be assumed:
     *
     *     - that reading is not possible if read permission is
     *     denied but write permission is granted
     *     - that reading is not possible if execute permission is
     *     granted but read permission is denied
     *
     *     This is only sometimes possible:
     *
     *     - that executing is not possible if read or write
     *     permission is granted but execute permission is denied
     *
     *     Additionally there are the \c uninitialized_memory and
     *     \c sensitive_data flags. These two flags deal with the
     *     initialization of memory mappings. If a memory mapping
     *     is larger than its underlying file object (thereby
     *     possibly increasing the size of the file), or if a
     *     memory mapping is done for a shared memory object then
     *     usually the operating system initializes that undefined
     *     memory content with zeroes the first time the data is
     *     mapped in the system.
     *
     *     Especially in embedded environments initializing some
     *     megabytes of memory with zeroes can take a considerable
     *     amount of time. That is why there are, under certain
     *     conditions, possibilities not to initialize such memory
     *     mappings with zero.
     *
     *     There are usage and security implications, however. If a
     *     part of memory is mapped, used and unmapped first by one
     *     process and then at a later time mapped by another
     *     process then the latter process may get access to
     *     remaining, sensitive data from the first process (think
     *     of passwords, encryption keys, file contents etc.). On
     *     the other hand an application may require defined
     *     initial contents of shared memory for correct operation,
     *     because it expects certain areas of the memory mapping
     *     to be zero initially.
     *
     *     That is where the \c uninitialized_memory and \c
     *     sensitive_data flags come into play. If \c
     *     uninitialized_memory is set to \c true then this
     *     expresses the applications desire to get uninitialized
     *     memory mappings, if possible, to reduce initialization
     *     time. If \c sensitive_data is \c true then this
     *     expresses that the data that will be put into the memory
     *     mapping by the application is considered sensitive and
     *     should not be given to another process without
     *     initializing the memory with zeroes.
     *
     *     So in a perfect world an application would only get an
     *     uninitialized memory mapping without setting \c
     *     uninitialized_memory to \c true and if the mapped in
     *     memory area was previously not used by an application
     *     that set \c sensitive_data to \c true. Sadly there are
     *     vast differences between operating sytems. Currently the
     *     following happens:
     *
     *     - On WIN32 systems both flags are without effect, there
     *     is no possibility not to zero-initialize memory mappings
     *     - On Linux \c sensitive_data is always ignored, only \c
     *     uninitialized_memory is honored. But this only, if the
     *     Linux kernel of the running system was configured to
     *     allow uninitialized memory mappings (only possible
     *     starting with 2.6.33)
     *     - On QNX both flags are honored starting from QNX 6.3.2
     **/
    class MemAccessFlags
    {
    public:
        MemAccessFlags(const bool read = false,
            const bool write = false,
            const bool exec = false,
            const bool uninitialized_memory = false,
            const bool sensitive_data = true) :
            m_flags(0)
        {
            setflags(read, write, exec,
                uninitialized_memory,
                sensitive_data);
        }

        void setflags(const bool read, const bool write,
            const bool exec, const bool uninitialized_memory,
            const bool sensitive_data)
        {
            if( read )
                m_flags |= READ;

            if( write )
                m_flags |= WRITE;

            if( exec )
                m_flags |= EXEC;

            if( uninitialized_memory )
                m_flags |= UNINIT_MEM;

            if( sensitive_data )
                m_flags |= SENSITIVE_DATA;
        }

        bool readable() const
        { return (m_flags & READ) != 0; }

        bool writeable() const
        { return (m_flags & WRITE) != 0; }

        bool executable() const
        { return (m_flags & EXEC) != 0; }

        bool uninitializedMemory() const
        { return (m_flags & UNINIT_MEM) != 0; }

        bool sensitiveData() const
        { return (m_flags & SENSITIVE_DATA) != 0; }

    private:
        static const uint_least32_t READ = 1 << 0;
        static const uint_least32_t WRITE = 1 << 1;
        static const uint_least32_t EXEC = 1 << 2;
        static const uint_least32_t UNINIT_MEM = 1 << 3;
        static const uint_least32_t SENSITIVE_DATA = 1 << 4;

        uint_least32_t m_flags;
    };

public: // functions

    //! Constructs an invalid memory mapping
    MemMapping() : m_handle(), m_offset(), m_length() { }

    //! \brief
    //! get a read-write pointer to the beginning of the mapped
    //! area
    inline void* addr();

    //! \brief
    //! get a read-only pointer to the beginning of the mapped
    //! area
    inline const void* constAddr() const;

    //! \brief
    //! get the offset of the mapping relative to the beginning of
    //! the underlying object
    size_t offset() const
    { return m_offset; }

    //! get the length of the mapping in bytes
    size_t length() const
    { return m_length; }

    /**
     * \brief
     *     Get the alignment requirement for memory mappings

     *     When mapping objects into process memory alignment
     *     requirements need to be fulfilled. These requirements
     *     differ between operating systems and hardware
     *     architectures. But they don't change between different
     *     memory mappable objects, file systems or processes on
     *     the same system.
     *
     *     The alignment needs to be handled explicitly by clients
     *     of memory mapped objects. There is no easy way of
     *     abstracting this. The alignment comes into play when
     *     selecting offsets for operations on memory mapped areas,
     *     the size of memory mappings and similar.
     *
     *     The alignment requirements are documented at the
     *     according functions where they apply.
     *
     *     The alignment value returned by this function is always
     *     a power of two and usually ranges in the area of a few
     *     kilobytes.
     * \note
     *     Although on some OSs the aligment requirement for memory
     *     mappings equals the pagesize of the current system it is
     *     not the case on all systems. Thus you can only rely on
     *     the value returned by this function.
     **/
    inline static size_t getAlignment();

    /**
     * \brief
     *     Get the alignment requirement for start addresses of
     *     memory mappings

     *     This is a special alignment requirement for the start
     *     address of new memory mappings. It is currently only
     *     used for the \c suggested_addr parameter of the
     *     MemMapping constructor.
     *
     *     This is necessary, because on some systems the page
     *     alignment requirement is different from the mapping
     *     alignment requirement.
     **/
    inline static size_t getStartAddrAlignment();

    /**
     * \brief
     *     Get the access flags that apply to this mapping area
     **/
    MemAccessFlags getAccess() const
    { return m_flags; }

    /**
     * \brief
     *     Determines whether this object contains a valid memory
     *     mapped area
     **/
    inline bool isValid() const;

    /**
     * \brief
     *     Synchronize mapped data with underlying system object

     *     The call will handle the memory area defined by the
     *     starting address of the current object plus the given \c
     *     offset in bytes and the given \c length in bytes.
     *
     *     Any data that was modified by the current process in the
     *     given memory area will be made sure to be reflected in
     *     the underyling system object, if necessary. This
     *     especially applies to memory mapped files. Shared memory
     *     segments don't need to be synchronized.
     *
     *     This call only makes sure that after returning from it
     *     synchronization occured for sure. The system may still
     *     decide on its own at arbitrary times to actually write
     *     data into the system object (e.g. file).
     * \note
     *     For \c offset the alignment requirements defined by
     *     MemMapping::getAlignment() apply.
     * \note
     *     In case the underlying system object is modified by
     *     other means than this memory mapping then those changes
     *     are not necessarily made visible in the memory mapping.
     *     The call of this function also don't makes such changes
     *     visible for sure.
     *
     *     It is best not to create such a scenario in the first
     *     place as it is very hard to handle in a
     *     platform-independent manner.
     **/
    bool sync(const size_t length, const size_t offset);

protected:
    // allows MemBinFileBase, SharedMemoryBase to construct
    // MemMappings from file handles
    friend class MemBinFileBase;
    friend class SharedMemoryBase;

    /**
     * \brief
     *     Creates a memory mapping for the given file handle acc.
     *     to parameters

     *     The access flags given by \c flags need to be compatible
     *     with the flags used to open the underlying memory
     *     mappable object \c file. Otherwise the mapping operation
     *     may fail.
     *
     *     The memory mapping created will start at \c off bytes
     *     relative to the beginning of the underlying object \c
     *     file and provide \c length bytes from that position
     *     onward.
     *
     *    if \c suggested_addr is set then the system will attempt
     *    to put the memory mapping exactly or near that address.
     *    For this to succeed \c suggested_addr needs be placed
     *    at an address that is a multiple of the value returned
     *    by getStartAddrAlignment() and that is not otherwise
     *    occupied by the system. This is for example useful to
     *    setup a memory mapping just after an already existing
     *    memory mapping such that both mappings are merged into a
     *    consecutive memory range. You should *not* use this to
     *    setup a memory mapping at a address that is determined
     *    at compile time.
     *
     *    Note the suggestive character of \c suggested_addr. The
     *    only actually valid address will be the one returned by
     *    addr() and constAddr() after successful setup of the
     *    mapping.
     *
     *    If \c suggested_addr does not fulfill the alignment
     *    requirements then the call may either fail completely or
     *    a different address that matches the requirements will
     *    be used for the memory mapping.
     *
     *    If \c get_ringbuffer is set to \c true then OSAL will
     *    attempt to create the requested mapping twice in a
     *    consecutive memory range. This allows you to get a
     *    "real" ring buffer in memory i.e. if you have a range of
     *    data that start somewhere at the end and wraps around to
     *    the beginning of the memory range then mapping the
     *    memory range twice into memory one just after the other
     *    then you can treat that range of data as if it didn't
     *    wrap around the end of the ring buffer.
     *
     *    Getting a ring buffer requires complex adjustments by
     *    OSAL and there's not guarantee that this actually works.
     *    In case the attemps fail NOT_IMPLEMENTED will be
     *    returned as an error.
     * \note
     *     For \c off the alignment requirements defined by
     *     MemMapping::getAlignment() apply
     * \errorindicator
     *     via isValid()
     * \errors
     *     osal::SysError with IDs:
     *
     *     - PERMISSION_DENIED the underlying object was not opened
     *     with permissions that allow \c flags to apply to the
     *     mapping
     *     - INTEGRITY_ERROR on severe logical, internal errors
     *     - NOT_IMPLEMENTED if the underlying object doesn't
     *     support memory mapping or if \c get_ringbuffer was set
     *     to \c true and a ring buffer couldn't be acquired by
     *     OSAL
     *     - SYSTEM_RESSOURCES_EXHAUSTED if no more mappings can be
     *     created, because a limit has been reached
     *     - OUT_OF_MEMORY if there is not enough memory available
     *     to setup the mapping
     *     - INVALID_ARGUMENT if \c off doesn't fulfill the
     *     alignment requirements or if the requested area is
     *     outside the possibilities of the underlying object
     *     - UNKNOWN_ERROR on other occasions
     **/
    MemMapping(const FileHandle &file,
        const MemAccessFlags& flags, const size_t length,
        const size_t off, void *suggested_addr = NULL,
        const bool get_ringbuffer = false);

    /**
     * \brief
     *     same as MemMapping(const FileHandle&, const
     *     MemAccessFlags&, const size_t, const size_t) but for
     *     creating mappings on shared memory
     **/
    MemMapping(const SharedMemoryHandle &shm,
        const MemAccessFlags& flags, const size_t length,
        const size_t off, void *suggested_addr = NULL,
        const bool get_ringbuffer = false);

    /**
     * \brief
     *     Destroys the mapping, if one is present

     *     After return of this function the memory mapping
     *     is to be considered invalid and further accesses
     *     to it will fail.
     * \errorindicator
     *     via return code
     * \errors
     *     osal::SysError with IDs:
     *
     *     - INTEGRITY_ERROR if the address of the mapping
     *     is in some way invalid
     * \return
     *     true on error, false otherwise
     **/
    bool destroy();
private:
    MemMappingHandle m_handle;
    size_t m_offset;
    size_t m_length;
    MemAccessFlags m_flags;
}; // end class

} // end osal

#if defined IPL_OS_POSIX
#    include "posix/MemMapping.inl"
#elif defined IPL_OS_WINPC
#    include "win32/MemMapping.inl"
#elif defined IPL_OS_INTEGRITY
#    include "integrity/MemMapping.inl"
#else
#    error "error undefined IPL_OS_ variant"
#endif

#endif // OSAL_MEMMAPPING_HXX
