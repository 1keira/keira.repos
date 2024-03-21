/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/
#ifndef OSAL_STREAMBINFILEW_HXX
#define OSAL_STREAMBINFILEW_HXX

#include <ipl_config.h>

#include <common/Macros.hxx>
#include <common/IBinOutputStream.hxx>
#include <common/types/string.hxx>
#include <osal/osal_dso.h>
#include <osal/osal.hxx>
#include <osal/StreamBinFileBase.hxx>

namespace osal {

    /**
    * \brief
    *    write-only, stream-based, binary access to files

    *    This class adds actual write access to a stream based binary
    *    file. It additionally inherits from IBinOutputStream and thus
    *    can be used in a generic way for doing output to files.
    *
    *    For writing see IBinOutputStream::write() and
    *    IBinOutputStream::flush(). For specific errors see
    *    StreamBinFileW::performWrite() and
    *    StreamBinFileW::performFlush().
    **/
    class OSAL_EXPORT StreamBinFileW :
        public ipl::IBinOutputStream,
        virtual public StreamBinFileBase
    {
    public: // functions
        using BinFileBase::truncateSize;

        /**
        * \brief
        *    Creates an invalid file with a local buffer of \c
        *    write_buffer bytes

        *    The write buffer parameter is given in case the file is
        *    opened later on, because the write buffer can only be
        *    assigned during construction time currently.
        *
        *    This constructor will not open any file. isValid() will
        *    return false and no error is raised.
        **/
        explicit StreamBinFileW(const size_t write_buffer = 0) IPL_NOEXCEPT :
            StreamBinFileBase(),
            IBinOutputStream(true, write_buffer)
        { }

        /**
        * \brief
        *    Open the file located at path \c p using a local write
        *    buffer of \c write_buffer bytes size and open flags \c
        *    flags
        * \errorindicator
        *    via isValid()
        * \errors
        *    \see StreamBinFileW::open(const char*, WriteFlags&, FileAccess&)
        **/
        explicit StreamBinFileW(const char *p,
            const WriteFlags &flags = WriteFlags(),
            const FileAccess &access =
                FileAccess::owner_read|FileAccess::owner_write|
                FileAccess::group_read|FileAccess::group_write,
            const size_t write_buffer = 0) IPL_NOEXCEPT :
            IBinOutputStream(flags().blocking(), write_buffer)
        {
            if( IBinOutputStream::isValid() )
            {
                BinFileBase::open(p,
                    static_cast<OpenFlags>(flags), access);
            }
        }

        //! \see StreamBinFileW(const char*, const WriteFlags&, FileAccess&, const ! size_t)
        explicit StreamBinFileW(const ipl::string &p,
            const WriteFlags &flags = WriteFlags(),
            const FileAccess &access =
                FileAccess::owner_read|FileAccess::owner_write|
                FileAccess::group_read|FileAccess::group_write,
            const size_t write_buffer = 0) IPL_NOEXCEPT :
            IBinOutputStream(flags().blocking(), write_buffer)
        {
            if( IBinOutputStream::isValid() )
            {
                this->open(p, flags, access);
            }
        }

        //! \brief
        //!    unicode variant of StreamBinFileW(const char*, const
        //!    WriteFlags&, const size_t)
        //! \see
        //!    StreamBinFileW(const char*, const WriteFlags&, FileAccess&, const size_t)
        explicit StreamBinFileW(const osal::UnicodeString &ucs,
            const WriteFlags &flags = WriteFlags(),
            const FileAccess &access =
                FileAccess::owner_read|FileAccess::owner_write|
                FileAccess::group_read|FileAccess::group_write,
            const size_t write_buffer = 0) IPL_NOEXCEPT :
            IBinOutputStream(flags().blocking(), write_buffer)
        {
            if( IBinOutputStream::isValid() )
            {
                this->open(ucs, flags, access);
            }
        }

        /**
        * \brief
        *    Open the file located in directory \c parent named \c name using a local write
        *    buffer of \c write_buffer bytes size and open flags \c
        *    flags
        * \errorindicator
        *    via isValid()
        * \errors
        *    \see osal::BinFileBase::openAt(const Directory&, const char*, bool, ReadFlags&, FileAccess&)
        **/
        explicit StreamBinFileW(const Directory& parent, const char *name, bool resolve_links = false,
            const WriteFlags &flags = WriteFlags(),
            const FileAccess &access =
                FileAccess::owner_read|FileAccess::owner_write|
                FileAccess::group_read|FileAccess::group_write,
            const size_t write_buffer = 0) IPL_NOEXCEPT :
            IBinOutputStream(flags().blocking(), write_buffer)
        {
            if( IBinOutputStream::isValid() )
            {
                BinFileBase::openAt(parent,name,resolve_links,
                    static_cast<OpenFlags>(flags), access);
            }
        }

        /**
        * \brief
        *    Create a StreamBinFileW from the given pipe object
        * \see
        *    StreamBinFileW::open(Pipe&)
        * \errors
        *    the pipe open won't fail but the IBinOutputStream
        *    construction may fail.
        * \errorindicator
        *    via isValid()
        **/
        explicit StreamBinFileW(Pipe &pipe,
            const size_t write_buffer = 0) IPL_NOEXCEPT :
            IBinOutputStream(true, write_buffer)
        {
            if( IBinOutputStream::isValid() )
            {
                this->open(pipe);
            }
        }

        //! \brief provide destructor again to make sure output stream
        //! is flushed at the right time via close()
        ~StreamBinFileW() IPL_NOEXCEPT
        {
            if( StreamBinFileW::close() ) // BRANCH_COVERAGE_UNTESTABLE
            {
                IPL_WARN("Error closing BinFileW");
                ipl_error.ack();
            }
        }

        /**
        * \brief
        *    Opens the file located at \c p using open flags \c flags

        *    If a file is already opened then an attempt is made to
        *    close it
        *
        *    Default open flags will be applied if none are given
        *    i.e. write-only access in blocking mode, no additional
        *    flags set.
        * \return
        *    true on error, false on success
        * \errorindicator
        *    via isValid(), return code
        * \errors
        *    \see BinFileBase::open(const char*, OpenFlags&, FileAccess&)
        **/
        bool open(const char *p,
            const WriteFlags &flags = WriteFlags(),
            const FileAccess &access =
                FileAccess::owner_read|FileAccess::owner_write|
                FileAccess::group_read|FileAccess::group_write) IPL_NOEXCEPT;

        //! \see open(const char*, const WriteFlags)
        bool open(const ipl::string &p,
            const WriteFlags &flags = WriteFlags(),
            const FileAccess &access =
                FileAccess::owner_read|FileAccess::owner_write|
                FileAccess::group_read|FileAccess::group_write) IPL_NOEXCEPT
        {
            return StreamBinFileW::open(p.c_str(), flags, access);
        }

        //! \brief
        //!    Unicode variant of open
        //! \see
        //!    StreamBinFileW::open(const char*, const WriteFlags&, FileAccess&)
        bool open(const osal::UnicodeString &ucs,
            const WriteFlags &flags = WriteFlags(),
            const FileAccess &access =
                FileAccess::owner_read|FileAccess::owner_write|
                FileAccess::group_read|FileAccess::group_write) IPL_NOEXCEPT;

        /**
        * \brief
        *    Open the file located in directory \c parent named \c name using open flags \c flags

        *    If a file is already opened then an attempt is made to
        *    close it
        *
        *    Default open flags will be applied if none are given
        *    i.e. write-only access in blocking mode, no additional
        *    flags set.
        * \return
        *    true on error, false on success
        * \errorindicator
        *    via isValid(), return code
        * \errors
        *    \see BinFileBase::open(const char*, OpenFlags&, FileAccess&)
        **/
        bool openAt(const Directory& parent, const char *name, bool resolve_links = false,
            const WriteFlags &flags = WriteFlags(),
            const FileAccess &access =
                FileAccess::owner_read|FileAccess::owner_write|
                FileAccess::group_read|FileAccess::group_write) IPL_NOEXCEPT;

        /**
        * \brief
        *    Opens the given pipe object for writing

        *    Any previously opened file will be closed. On error
        *    closing nothing else is done.
        *
        *     Uses the write end of \c pipe for output, if it is still
        *     valid
        *
        *     On success the ownership of the write end of \c pipe
        *     will be taken over into the current object. The write
        *     end of \c pipe will be invalidated such that \c pipe's
        *     write end cannot be used any more for other purposes and
        *     it won't be closed at destruction time of \c pipe.
        * \see
        *    BinFileBase::open(Pipe&, const bool)
        * \errors
        *    the pipe open won't fail but closing a previously opened
        *    file may fail
        * \errorindicator
        *    via isValid()
        **/
        bool open(osal::Pipe &p) IPL_NOEXCEPT;

        /**
        * \brief
        *    Returns true if currently a file is opened

        *    In case an internal buffer has been requested and the
        *    IBinOutputStream failed to allocate that buffer then the
        *    object will never be usable.
        **/
        bool isValid() const IPL_NOEXCEPT
        {
            return StreamBinFileBase::isValid()
                && IBinOutputStream::isValid();
        }

        /**
        * \brief
        *    Flushes any unwritten data from the local buffer before
        *    closing the file via StreamBinFileBase
        **/
        virtual bool close() IPL_NOEXCEPT
        {
            bool err = false;

            if( ! isValid() )
                return err;

            err = this->flush();

            return StreamBinFileBase::close() || err; // BRANCH_COVERAGE_UNTESTABLE
        }

        /**
        * \brief
        *    Corrective logic for seek in case a local write buffer
        *    is present

        *    If the IBinOutputStream has unwritten data then seeking
        *    would produce unexpected results. Thus we need to
        *    correct stuff such that the seek operation becomes
        *    predictable again.
        *
        *    Note that as this requires a potential flush operation
        *    the seek may fail due to data cannot be written or not
        *    be written completely onto the stream. Thus you're best
        *    off caring yourself that the stream is flushed before
        *    seeking.
        **/
        virtual bool seek(int offset,
            const SeekDirection direction,
            size_t &newpos) IPL_NOEXCEPT;

    protected:
        //! see StreamBinFileBase(FileHandle&, ReadWriteFlags&)
        StreamBinFileW(const FileHandle &fh, const WriteFlags &wf,
            const size_t write_buffer = 0) IPL_NOEXCEPT :
            IBinOutputStream(wf().blocking(), write_buffer)
        {
            if( IBinOutputStream::isValid() )
            {
                BinFileBase::open(fh, wf);
            }
        }

        /**
        * \brief
        *    Actually perform a write operation on the file

        *    According to the requirements of IBinOutputStream,
        *    StreamErrors will be raised in case of problems.
        *    Attached to them are usually osal::SysErrors describing
        *    the concrete problem.
        * \errors
        *    StreamError with IDs:
        *
        *    - STREAM_BROKEN
        *      - attached with ipl::CommonError with IDs
        *        - ipl::INVALID_USAGE in case the file is currently
        *        invalid
        *      - attached wit osal::SysError with IDs
        *        - INTEGRITY_ERROR on servere internal errors
        *        - INVALID_DEVICE if the file is a device file and
        *        the device isn't present/ready/capable of performing
        *        the operation
        *    - OPERATION_FAILED
        *      - attached with osal::SysError with IDs
        *        - IO_FAILURE if the operation failed for
        *        OS-implementation specific reasons
        *        - INVALID_ARGUMENT if the file position pointer has
        *        become too large (e.g. > 32-bit). In write context
        *        this can also mean the file has reached the maximum
        *        size allowed for the caller.
        *        - SYSTEM_RESSOURCES_EXHAUSTED if ressources other
        *        then memory are lacking for the operation to succeed
        *        - OUT_OF_MEMORY if not enough memory is available
        *        for the operation to succeed
        *        - PERMISSION_DENIED if you're not allowed to write
        *        to this file
        *        - FS_NO_SPACE if the file system the file is
        *        residing on is full or the device is full - depends
        *        on the underlying file
        *    - UNKNOWN_STREAM_ERROR
        *      - attached with osal::SysError with IDs
        *        - UNKNOWN_ERROR on other occasions
        **/
        virtual bool performWrite(const void* const p_write_buffer,
            const size_t p_max_bytes,
            size_t &p_bytes_written) IPL_NOEXCEPT;

        /**
        * \brief
        *    Actually perform a flush operation on the file

        *    According to the requirements of IBinOutputStream,
        *    StreamErrors will be raised in case of problems.
        *    Attached to them are usually osal::SysErrors describing
        *    the concrete problem.
        * \errors
        *    StreamError with IDs:
        *
        *    - STREAM_BROKEN
        *      - attached with ipl::CommonError with IDs
        *        - ipl::INVALID_USAGE in case the file is currently
        *        invalid
        *      - attached wit osal::SysError with IDs
        *        - INTEGRITY_ERROR on servere internal errors
        *    - OPERATION_FAILED
        *      - attached with osal::SysError with IDs
        *        - IO_FAILURE if the operation failed for
        *        OS-implementation specific reasons
        *    - UNKNOWN_STREAM_ERROR
        *      - attached with osal::SysError with IDs
        *        - UNKNOWN_ERROR on other occasions
        **/
        virtual bool performFlush() IPL_NOEXCEPT;

    };

}  // end of namespace osal

#endif
