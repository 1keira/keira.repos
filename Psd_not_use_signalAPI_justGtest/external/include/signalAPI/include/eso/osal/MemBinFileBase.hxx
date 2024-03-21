/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_MEMBINFILEBASE_HXX
#define OSAL_MEMBINFILEBASE_HXX

#include <ipl_config.h>

#include <common/types/map.hxx>

#include <osal/osal_dso.h>
#include <osal/osal.hxx>
#include <osal/BinFileBase.hxx>
#include <osal/MemMapping.hxx>

#if defined IPL_OS_POSIX || defined IPL_OS_INTEGRITY
#    include "posix/MemBinFileDefs.hxx"
#elif defined IPL_OS_WINPC
#    include "win32/MemBinFileDefs.hxx"
#else
#    error "error undefined IPL_OS_ variant"
#endif

namespace osal {

    /**
    * \brief
    *     Base class for memory-based, binary access to files

    *     This base class introduces memory-based access to files. This is
    *     a more efficient but also more complicated variant to work with
    *     file contents compared to stream-based access. In this scheme
    *     part or all of a files content is mapped into the current
    *     process's memory by the operating system. This allows to avoid a
    *     lot of copy operations that occur with stream-based access.
    *
    *     On the downside the client has to care about memory alignment
    *     and a bit more peculiar behaviour regarding e.g. flushing data
    *     and reflecting changes of file content back into the mapped
    *     memory area and vice-versa. This also results in somewhat
    *     reduced portability accross operating systems as these
    *     peculiarities also can differ on different platforms.
    *
    *     If the file corresponds to a special device file that supports
    *     it then the client can map special kind of data into the process
    *     (say a graphics device framebuffer or such). Such things depend
    *     completely on the semantics of the device. Also such things will
    *     only work on POSIX systems typically.
    *
    *     Note that it is not possible in a generic way to extend the size
    *     of a file via memory mapping. If you intend to do so use
    *     BinFileBase::truncateSize() before creating a memory mapping.
    *
    *     Opening a file works quite the same way as for stream-based file
    *     access. Only some of the open flags have now no or only reduced
    *     meaning:
    *
    *     - non-blocking mode no longer has an influence to read/write
    *     operations as those operations are not performed via memory
    *     references that don't block. Actual operations are performed
    *     asynchronously to the client. An operation that might still be
    *     influenced by this flag is the open operation
    *     - append-mode has no more meaning as the file-position pointer
    *     isn't used in memory-access and appending can't happen via
    *     memory-access anyway.
    *
    *     Once the file has been opened you can now setup an arbitrary
    *     number of memory mappings on it. The mappings will can be
    *     destroyed individually by explicitly saying so. Otherwise all
    *     mappings are destroyed implicitly before closing the file again.
    *
    *     Defining a mapping for a file is a potentially costly operation
    *     so you should not over-stress this facility by e.g. creating a
    *     mapping for every record in a file that consists of hundreds or
    *     thousands of records. In such cases better create one mapping
    *     for the complete file.
    *
    *    The error handling of memory mapped files also becomes less
    *    comfortable then with stream-based access. This is, because
    *    there are no more system calls involved with accessing file
    *    contents. Thus there is not really a well-defined point for
    *    reporting errors. OSAL can really help improving on this matter.
    *    In general on POSIX systems you will get signals from the
    *    operating-system if something goes wrong i.e.  something like
    *    SIGBUS or SIGSEGV. This causes the program to abort execution in
    *    the usual case. On WIN32 you get so called structured exception
    *    handling which we can't employ on OSAL level, because it is
    *    specific to WIN32. Thus here again the program execution will
    *    terminate.
    *
    *     Such events will mostly occur, because of:
    *
    *     - accessing memory areas outside of defined mappings or outside
    *     the valid data range of the underlying file
    *     - accessing memory areas in a way that is not allowed (e.g.
    *     writing to locations that have been mapped read-only or
    *     executing locations that have not been mapped executable)
    *     - operations on the underlying file failed e.g. due to i/o errors
    *
    *     All but the last error types can be prevented by careful
    *     programming.
    **/
    class OSAL_EXPORT MemBinFileBase :
        public BinFileBase
    {
    public: // functions

        /**
        * \brief
        *     calls MemBinFileBase::close()
        **/
        virtual ~MemBinFileBase()
        {
            if( MemBinFileBase::close() ) // BRANCH_COVERAGE_UNTESTABLE
            {
                IPL_WARN("Error closing membinfile");
                ipl_error.ack();
            }
        }

        /**
        * \brief
        *    Removes memory mappings associated with the file, if any
        *    exist. Then closes the underlying file.
        * \warning
        *     After closing a file any MemMappings that are still
        *     going around for this file will become invalid. It is
        *     best to discard them explicitly before closing the
        *     underlying file.
        * \errorindicator
        *     via return code
        * \return
        *     true on error, false otherwise
        * \see
        *     BinFileBase::close()
        **/
        virtual bool close();

        /**
        * \brief
        *     remove a memory mapping that was previously established
        *     via createMapping()

        *     The previously successfully established memory mapping
        *     \c mapping needs have been obtained at the
        *     createMapping() member of the same object instance with
        *     the same underlying file.
        *
        *     After return of the function the \c mapping is no longer
        *     valid and the object should be discarded.
        * \return
        *     true on error, false on success
        * \errorindicator
        *     via return code
        * \errors
        *     see MemMapping::destroy()
        *
        *     additional an ipl::CommonError with ID INVALID_USAGE if
        *     \c mapping is not known to this instance.
        **/
        bool removeMapping(const MemMapping &mapping);

        /**
        * \brief
        *     Retrieve a reference to the currently registered map of
        *     mappings at this file
        **/
        const ipl::map<const void*, MemMapping>& getMappings()
        { return m_memfile.mappings; }

    protected: // functions

        /**
        * \brief
        *     Creates a memory mapping on top of the already opened
        *     file
        * \errorindicator
        *     via isValid() member of the returned MemMapping object
        * \see
        *     MemMapping(const FileHandle&, const MemAccessFlags&,
        *     const size_t, const size_t)
        **/
        MemMapping createMapping(
            const MemMapping::MemAccessFlags &access,
            const size_t length, const size_t off,
            void *suggested_addr)
        {
            MemMapping mapping( this->m_file, access,
                length, off, suggested_addr );

            if( mapping.isValid() )
            {
                m_memfile.mappings.insert(
                    ipl::make_pair(mapping.addr(),
                    mapping) );
            }

            return mapping;
        }

        //! Constructs an invalid memory binary file
        MemBinFileBase() :
            BinFileBase()
        { }

    private:
        //! additonal handle for memory mapped files
        MemFileHandle m_memfile;
    };

}  // end of namespace osal

#endif
