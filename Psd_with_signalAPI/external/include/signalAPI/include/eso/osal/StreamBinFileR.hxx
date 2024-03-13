/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_STREAMBINFILER_HXX
#define OSAL_STREAMBINFILER_HXX

#include <ipl_config.h>

#include <common/IBinInputStream.hxx>
#include <common/types/string.hxx>

#include <osal/osal_dso.h>
#include <osal/osal.hxx>
#include <osal/StreamBinFileBase.hxx>

namespace osal {

    /**
    * \brief
    *    read-only, stream-based, binary access to files

    *    This class adds actual read access to a stream based binary
    *    file. It additionally inherits from IBinInputStream and thus can
    *    be used in a generic way for getting input from files.
    *
    *    For reading see IBinInputStream::read(). For specific errors see
    *    StreamBinFileR::performRead().
    **/
    class OSAL_EXPORT StreamBinFileR :
        public ipl::IBinInputStream,
        virtual public StreamBinFileBase
    {
    protected:
        using BinFileBase::open;
    public: // functions

        /**
        * \brief
        *    Creates an invalid file with a local buffer of \c
        *    read_buffer bytes

        *    The read buffer parameter is given in case the file is
        *    opened later on, because the read buffer can only be
        *    assigned during construction time currently.
        *
        *    This constructor will not open any file. isValid() will
        *    return false and no error is raised.
        **/
        explicit StreamBinFileR(const size_t read_buffer = 0) IPL_NOEXCEPT :
            StreamBinFileBase(),
            IBinInputStream(true, read_buffer)
        {}

        /**
        * \brief
        *    Open the file located at path \c p using a local read
        *    buffer of \c read_buffer bytes size and open flags \c
        *    flags
        * \errorindicator
        *    via isValid()
        * \errors
        *    \see Base::open(const char*, ReadFlags&, FileAccess&)
        **/
        explicit StreamBinFileR(const char *p,
            const ReadFlags &flags = ReadFlags(),
            const FileAccess &access =
                FileAccess::owner_read|FileAccess::owner_write|
                FileAccess::group_read|FileAccess::group_write,
            const size_t read_buffer = 0) IPL_NOEXCEPT :
            IBinInputStream(flags().blocking(), read_buffer)
        {
            if( IBinInputStream::isValid() )
            {
                BinFileBase::open(p,
                    static_cast<OpenFlags>(flags), access);
            }
        }

        //! \see StreamBinFileR(const char*, const ReadFlags&, FileAccess&, const size_t)
        explicit StreamBinFileR(const ipl::string &p,
            const ReadFlags &flags = ReadFlags(),
            const FileAccess &access =
                FileAccess::owner_read|FileAccess::owner_write|
                FileAccess::group_read|FileAccess::group_write,
            const size_t read_buffer = 0) IPL_NOEXCEPT :
            IBinInputStream(flags().blocking(), read_buffer)
        {
            if( IBinInputStream::isValid() )
            {
                this->open(p, flags, access);
            }
        }

        //! \brief
        //!    Unicode variant of StreamBinFileR(const char*, const
        //!    ReadFlags&, const size_t)
        //! \see
        //!    StreamBinFileR(const char*, const ReadFlags&, const
        //!    size_t)
        explicit StreamBinFileR(const osal::UnicodeString &ucs,
            const ReadFlags &flags = ReadFlags(),
            const FileAccess &access =
                FileAccess::owner_read|FileAccess::owner_write|
                FileAccess::group_read|FileAccess::group_write,
            const size_t read_buffer = 0) IPL_NOEXCEPT :
            IBinInputStream(flags().blocking(), read_buffer)
        {
            if( IBinInputStream::isValid() )
            {
                this->open(ucs, flags, access);
            }
        }

        /**
        * \brief
        *    Open the file located in directory \a parent named \a name.
        *
        *    To open, a local read
        *    buffer of \a read_buffer bytes size is created and open flags \a
        *    flags are applied.
        * \errorindicator
        *    via isValid()
        * \errors
        *    \see osal::BinFileBase::openAt(const Directory&, const char*, bool, ReadFlags&, FileAccess&)
        **/
        explicit StreamBinFileR(const Directory& parent, const char *name, bool resolve_links = false,
            const ReadFlags &flags = ReadFlags(),
            const FileAccess &access =
                FileAccess::owner_read|FileAccess::owner_write|
                FileAccess::group_read|FileAccess::group_write,
            const size_t read_buffer = 0) IPL_NOEXCEPT :
            IBinInputStream(flags().blocking(), read_buffer)
        {
            if( IBinInputStream::isValid() )
            {
                BinFileBase::openAt( parent, name, resolve_links,
                    static_cast<OpenFlags>(flags), access);
            }
        }

        /**
        * \brief
        *    Create a StreamBinFileR from the given pipe object
        * \see
        *    StreamBinFileR::open(Pipe&)
        * \errors
        *    the pipe open won't fail but the IBinInputStream
        *    construction may fail.
        * \errorindicator
        *    via isValid()
        **/
        explicit StreamBinFileR(Pipe &pipe,
            const size_t read_buffer = 0) IPL_NOEXCEPT :
            IBinInputStream(true, read_buffer)
        {
            if( IBinInputStream::isValid() )
            {
                this->open(pipe);
            }
        }

        /**
        * \brief
        *    Opens the file located at \c p using open flags \c flags

        *    If a file is already opened then an attempt is made to
        *    close it
        *
        *    Default open flags will be applied if none are given
        *    i.e. read-only access in blocking mode.
        * \return
        *    true on error, false on success
        * \errorindicator
        *    via isValid(), return code
        * \errors
        *    \see BinFileBase::open(const char*, OpenFlags&, FileAccess&)
        **/
        bool open(const char *p, const ReadFlags &flags = ReadFlags(),
            const FileAccess &access =
                FileAccess::owner_read|FileAccess::owner_write|
                FileAccess::group_read|FileAccess::group_write) IPL_NOEXCEPT;

        /**
        * \see StreamBinFileR::open(const char*, const ReadFlags)
        **/
        bool open(const ipl::string &p,
            const ReadFlags flags = ReadFlags(),
            const FileAccess &access =
                FileAccess::owner_read|FileAccess::owner_write|
                FileAccess::group_read|FileAccess::group_write) IPL_NOEXCEPT
        {
            return StreamBinFileR::open(p.c_str(), flags, access);
        }

        /**
        * \brief
        *     Opens a unicode path just like SreamBinFileR::open(const
        *     char*, const ReadFlags&) does for ascii paths
        * \see
        *     StreamBinFileFileR::open(const char*, const ReadFlags&, FileAccess&)
        **/
        bool open(const osal::UnicodeString &ucs,
            const ReadFlags flags = ReadFlags(),
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
        *    i.e. read-only access in blocking mode.
        * \return
        *    true on error, false on success
        * \errorindicator
        *    via isValid(), return code
        * \errors
        *    \see BinFileBase::open(const char*, OpenFlags&, FileAccess&)
        **/
        bool openAt(const Directory& parent, const char *name, bool resolve_links = false,
            const ReadFlags &flags = ReadFlags(),
            const FileAccess &access =
                FileAccess::owner_read|FileAccess::owner_write|
                FileAccess::group_read|FileAccess::group_write) IPL_NOEXCEPT;

        /**
        * \brief
        *    Opens the given pipe object for reading

        *     Uses the read end of \c pipe as input, if it is valid.
        *
        *     On success the ownership of the read end of \c pipe will
        *     be taken over into the current object. The read end of
        *     \c pipe will be invalidated such that \c pipe's read end
        *     cannot be used any more for other purposes and it won't
        *     be closed at destruction time of \c pipe.
        * \see
        *    BinFileBase::open(Pipe&, const bool)
        * \errors
        *    the pipe open won't fail but closeing a previously
        *    opened file may fail
        * \errorindicator
        *    via isValid()
        **/
        bool open(osal::Pipe &p) IPL_NOEXCEPT;

        /**
        * \brief
        *    Returns true if currently a file is opened

        *    In case an internal buffer has been requested and the
        *    IBinInputStream failed to allocate that buffer then the
        *    object will never be usable.
        **/
        bool isValid() const IPL_NOEXCEPT
        {
            return StreamBinFileBase::isValid()
                && IBinInputStream::isValid();
        }

        /**
        * \brief
        *    Corrective logic for seek in case a local read buffer is
        *    present

        *    If the IBinInputStream has read-ahead data then seeking
        *    would produce unexpected results. Thus we need to
        *    correct stuff such that the seek operation becomes
        *    predictable again.
        *
        *    Note that this currently can cause poor buffering
        *    performance, because the implementation simply discards
        *    any read-ahead data unconditionally. I.e. if you
        *    selected a local read buffer at construction time and
        *    heavily seek in the file then the read-ahead data
        *    becomes mostly useless and you should consider to
        *    disable the buffer.
        **/
        virtual bool seek(int offset,
            const SeekDirection direction,
            size_t &newpos) IPL_NOEXCEPT;

    protected:

        //! see StreamBinFileBase(FileHandle&, const ReadWriteFlags&)
        StreamBinFileR(const FileHandle &fh, const ReadFlags &flags,
            const size_t read_buffer = 0) IPL_NOEXCEPT :
            IBinInputStream(flags().blocking(), read_buffer)
        {
            if( IBinInputStream::isValid() )
            {
                BinFileBase::open(fh,
                    static_cast<OpenFlags>(flags));
            }
        }

        /**
        * \brief
        *    Actually perform a read operation on the file

        *    According to the requirements of IBinInputStream,
        *    StreamErrors will be raised in case of problems.
        *    Attached to them are usually osal::SysErrors describing
        *    the concrete problem.
        * \errors
        *    StreamError with IDs:
        *
        *    - STREAM_BROKEN
        *      - attached with ipl::CommonError with IDs
        *        - ipl::INVALID_USAGE in case the file is currently invalid
        *      - attached wit osal::SysError with IDs
        *        - INTEGRITY_ERROR on servere internal errors
        *        - INVALID_DEVICE if the file is a device file and
        *        the device isn't present/ready/capable of performing
        *        the operation
        *    - OPERATION_FAILED
        *      - attached with osal::SysError with IDs
        *        - IO_FAILURE if the operation failed for
        *        OS-implementation specific reasons
        *        - INVALID_PATH if the opened file doesn't support
        *        reads (e.g. read on directory)
        *        - INVALID_ARGUMENT if the file position pointer has
        *        become too large (e.g. > 32-bit)
        *        - SYSTEM_RESSOURCES_EXHAUSTED if ressources other
        *        then memory are lacking for the operation to succeed
        *        - OUT_OF_MEMORY if not enough memory is available
        *        for the operation to succeed
        *    - END_OF_STREAM if the end of the file has been reached
        *    and no more data is available
        *    - UNKNOWN_STREAM_ERROR
        *      - attached with osal::SysError with IDs
        *        - UNKNOWN_ERROR on other occasions
        **/
        virtual bool performRead(void* const p_read_buffer,
            const size_t p_max_bytes,
            size_t &p_bytes_read) IPL_NOEXCEPT;
    };

}  // end of namespace osal

#endif
