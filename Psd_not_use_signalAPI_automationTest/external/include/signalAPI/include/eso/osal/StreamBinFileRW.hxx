/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_STREAMBINFILERW_HXX
#define OSAL_STREAMBINFILERW_HXX

#include <ipl_config.h>

#include <common/types/string.hxx>

#include <osal/osal_dso.h>
#include <osal/osal.hxx>
#include <osal/StreamBinFileR.hxx>
#include <osal/StreamBinFileW.hxx>
#include <osal/BinTempFileRW.hxx>

namespace osal {

    /**
    * \brief
    *    read-write, stream-based, binary access to files

    *    This class adds merges the read and write functionality from
    *    StreamBinFileR and StreamBinFileW to provide read-write
    *    arbitrary stream-based access to binary files.
    *
    *    Note that in difference to the std C++ streams library fstream
    *    this file class doesn't maintain a single buffer for reads and
    *    writes but still two independent buffers. This is especially
    *    noteworthy when doing seek operations as they can get less
    *    performant.
    **/
    class OSAL_EXPORT StreamBinFileRW :
        public StreamBinFileR,
        public StreamBinFileW
    {
    public:

        //! \brief
        //! construct an invalid RW file using the given stream buffer
        //! sizes in bytes
        explicit StreamBinFileRW(const size_t read_buffer = 0,
            const size_t write_buffer = 0) IPL_NOEXCEPT :
            StreamBinFileBase(),
            StreamBinFileR(read_buffer),
            StreamBinFileW(write_buffer),
            m_stream_mode(READ)
        { }

        /**
        * \brief
        *    Open the file located at path \c p using a local read
        *    buffer of \c read_buffer bytes size, a local write
        *    buffer of \c write_buffer bytes and open flags \c flags
        * \errorindicator
        *    via isValid()
        * \errors
        *     see StreamBinFileRW::open(const char*, ReadWriteFlags&, FileAccess&)
        **/
        explicit StreamBinFileRW(const char *p,
                const ReadWriteFlags &flags = ReadWriteFlags(),
                const FileAccess &access =
                    FileAccess::owner_read|FileAccess::owner_write|
                    FileAccess::group_read|FileAccess::group_write,
                const size_t read_buffer = 0,
                const size_t write_buffer = 0) IPL_NOEXCEPT :
            StreamBinFileR(read_buffer),
            StreamBinFileW(write_buffer),
            m_stream_mode(READ)
        {
            // be careful with these RW constructors: don't call the
            // base class constructors with path, otherwise be get
            // multiple opens/closes for the file. Only our
            // constructor is now responsible for opening the file.
            if( IBinInputStream::isValid() &&
                IBinOutputStream::isValid() )
            {
                this->open(p, flags, access);
            }
        }

        //! \see StreamBinFileRW(const char*, const ReadWriteFlags, FileAccess&, const size_t, const size_t)
        explicit StreamBinFileRW(const ipl::string &p,
                const ReadWriteFlags &flags = ReadWriteFlags(),
                const FileAccess &access =
                    FileAccess::owner_read|FileAccess::owner_write|
                    FileAccess::group_read|FileAccess::group_write,
                const size_t read_buffer = 0,
                const size_t write_buffer = 0) IPL_NOEXCEPT :
            StreamBinFileR(read_buffer),
            StreamBinFileW(write_buffer),
            m_stream_mode(READ)
        {
            if( IBinInputStream::isValid() &&
                IBinOutputStream::isValid() )
            {
                this->open(p, flags, access);
            }
        }

        //! \brief unicode constructor variant
        //! \see StreamBinFileRW(const char*, const ReadWriteFlags, FileAccess&, const size_t, const size_t)
        explicit StreamBinFileRW(const osal::UnicodeString &ucs,
                const ReadWriteFlags &flags = ReadWriteFlags(),
                const FileAccess &access =
                    FileAccess::owner_read|FileAccess::owner_write|
                    FileAccess::group_read|FileAccess::group_write,
                const size_t read_buffer = 0,
                const size_t write_buffer = 0) IPL_NOEXCEPT :
            StreamBinFileR(read_buffer),
            StreamBinFileW(write_buffer),
            m_stream_mode(READ)
        {
            if( IBinInputStream::isValid() &&
                IBinOutputStream::isValid() )
            {
                this->open(ucs, flags, access);
            }
        }

        /**
        * \brief
        *    Open the file located in directory \c parent named \c name using a local read
        *    buffer of \c read_buffer bytes size, a local write
        *    buffer of \c write_buffer bytes and open flags \c flags
        * \errorindicator
        *    via isValid()
        * \errors
        *    \see osal::BinFileBase::openAt(const Directory&, const char*, bool, ReadFlags&, FileAccess&)
        **/
        explicit StreamBinFileRW(const Directory& parent, const char *name, bool resolve_links = false,
                const ReadWriteFlags &flags = ReadWriteFlags(),
                const FileAccess &access =
                    FileAccess::owner_read|FileAccess::owner_write|
                    FileAccess::group_read|FileAccess::group_write,
                const size_t read_buffer = 0,
                const size_t write_buffer = 0) IPL_NOEXCEPT :
            StreamBinFileR(read_buffer),
            StreamBinFileW(write_buffer),
            m_stream_mode(READ)
        {
            // be careful with these RW constructors: don't call the
            // base class constructors with path, otherwise be get
            // multiple opens/closes for the file. Only our
            // constructor is now responsible for opening the file.
            if( IBinInputStream::isValid() &&
                IBinOutputStream::isValid() )
            {
                this->openAt( parent, name, resolve_links, flags, access);
            }
        }

        /**
        * \brief
        *    Create a StreamBinFileRW from the given BinTempFileRW
        *    object
        * \see
        *    BinBase::open(BinTempFileRW&, const bool)
        * \errors
        *    the file open won't fail but the IBinInputStream and
        *    IBinOutputStream construction may fail.
        * \errorindicator
        *    via isValid()
        **/
        explicit StreamBinFileRW(BinTempFileRW &tempfile,
            const bool auto_delete, const size_t read_buffer = 0,
                const size_t write_buffer = 0) IPL_NOEXCEPT :
            StreamBinFileR(read_buffer),
            StreamBinFileW(write_buffer),
            m_stream_mode(READ)
        {
            if( IBinInputStream::isValid() &&
                IBinOutputStream::isValid() )
            {
                BinFileBase::open(tempfile, auto_delete);
            }
        }

        /**
        * \brief
        *    Opens the file located at \c p using open flags \c flags

        *    If a file is already opened then an attempt is made to
        *    close it
        *
        *    Default open flags will be applied if none are given
        *    i.e. read-write access in blocking mode, no additional
        *    flags set.
        * \return
        *    true on error, false on success
        * \errorindicator
        *    via isValid(), return code
        * \errors
        *     see BinFileBase::open(const char*, const OpenFlags&, FileAccess&)
        **/
        bool open(const char *p,
            const ReadWriteFlags &flags = ReadWriteFlags(),
            const FileAccess &access =
                FileAccess::owner_read|FileAccess::owner_write|
                FileAccess::group_read|FileAccess::group_write) IPL_NOEXCEPT;

        //! \see
        //!    BinStreamFileRW::open(const char*, const ReadWriteFlags&, FileAccess&)
        bool open(const ipl::string &p,
            const ReadWriteFlags &flags = ReadWriteFlags(),
            const FileAccess &access =
                FileAccess::owner_read|FileAccess::owner_write|
                FileAccess::group_read|FileAccess::group_write) IPL_NOEXCEPT
        {
            return StreamBinFileRW::open(p.c_str(), flags, access);
        }

        /**
        * \brief
        *     unicode variant of open
        * \see
        *     BinStreamFileRW::open(const char*, const ReadWriteFlags&, FileAccess&)
        **/
        bool open(const osal::UnicodeString &ucs,
            const ReadWriteFlags &flags = ReadWriteFlags(),
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
        *    i.e. read-write access in blocking mode, no additional
        *    flags set.
        * \return
        *    true on error, false on success
        * \errorindicator
        *    via isValid(), return code
        * \errors
        *     see BinFileBase::open(const char*, const OpenFlags&, FileAccess&)
        **/
        bool openAt(const Directory& parent, const char *name, bool resolve_links = false,
            const ReadWriteFlags &flags = ReadWriteFlags(),
            const FileAccess &access =
                FileAccess::owner_read|FileAccess::owner_write|
                FileAccess::group_read|FileAccess::group_write) IPL_NOEXCEPT;

        /**
        * \brief
        *    Open the given BinTempFileRW for stream-based access
        * \see
        *    BinFileBase::open(BinTempFileRW&, const bool)
        **/
        bool open(BinTempFileRW &tempfile, const bool auto_delete) IPL_NOEXCEPT;

        /**
        * \brief
        *    Returns true if both streams are valid and a file is
        *    currently opened
        **/
        bool isValid() const IPL_NOEXCEPT
        {
            return StreamBinFileR::isValid()
                && StreamBinFileW::isValid();
        }

        /**
        * \brief
        *    Calls StreamBinFileW::close() to flush possible
        *    unwritten data
        **/
        virtual bool close() IPL_NOEXCEPT
        {
            return StreamBinFileW::close();
        }

        /**
        * \brief
        *    Adapted seek function that ensure that all buffers are
        *    in a correct state and the file position moves correctly
        *    from the client point of view
        **/
        virtual bool seek(int offset,
            const SeekDirection direction,
            size_t &newpos) IPL_NOEXCEPT;

    protected: // functions
        /**
        * \brief
        *    Ensure read buffer consistency upon read() calls

        *    This function checks before each read() call is
        *    performed whether the stream mode has changed from write
        *    to read. If so then any buffered unwritten data is
        *    flushed before continuing.
        **/
        virtual bool checkReadBufferConsistency() IPL_NOEXCEPT;

        /**
        * \brief
        *    Ensure write buffer consistency upon write() calls

        *    This function checks before each write() call is
        *    performed whether the stream mode has changed from read
        *    to write. If so and any read-ahead data is buffered then
        *    the read buffer is discarded and the file position
        *    pointer is corrected such that writes occur at the
        *    correct position.
        **/
        virtual bool checkWriteBufferConsistency() IPL_NOEXCEPT;

    protected: // types

        //! type to differentiate read/write mode of the stream
        enum StreamMode
        {
            READ,
            WRITE
        };

    protected: // data

        //! the currently active stream mode
        StreamMode m_stream_mode;
    private:
    };

}  // end of namespace osal

#endif
