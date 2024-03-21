/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_BINFILEBASE_HXX
#define OSAL_BINFILEBASE_HXX

#include <ipl_config.h>

#include <common/NonCopyable.hxx>
#include <common/Macros.hxx>
#include <common/types/string.hxx>

#if defined IPL_OS_POSIX || defined IPL_OS_INTEGRITY
#    include "posix/BinFileDefs.hxx"
#elif defined IPL_OS_WINPC
#    include "win32/BinFileDefs.hxx"
#else
#    error "error undefined IPL_OS_ variant"
#endif

#include <osal/osal_dso.h>
#include <osal/osal.hxx>
#include <osal/FileInfo.hxx>
#include <osal/BinTempFileRW.hxx>
#include <osal/Pipe.hxx>
#include <osal/Directory.hxx>

namespace osal {

    /**
    * \brief
    *     Base class for access to file system objects

    *     This class provides basic infrastructure in order to be able to
    *     open file system objects for i/o operations.
    *
    *     File objects are generally non-copyable. This would only be
    *     possible if a reference counting scheme would be applied. But
    *     parallel access to a file is not considered sensible and the
    *     overhead of reference counting would thus be unnecessary.
    *
    *     This class mainly provides the means to open and close a file.
    *     It does not imply any means of how the file is accessed. This is
    *     the job of specializations of this class.
    **/
    class OSAL_EXPORT BinFileBase :
        public ipl::NonCopyable
    {
    public: // types

        /**
        * \brief
        *     File open flag settings

        *     To aggregate the many combinations of how to open files
        *     this complex type is provided instead of a bunch of
        *     separate flags.
        *
        *     The OpenFlags contain settings that apply to both, files
        *     that are opened for reading and files that are opened
        *     for writing.
        *
        *     This type should never be used directly but instead the
        *     \c ReadFlags, \c WriteFlags and \c ReadWriteFlags should
        *     be used.
        **/
        class OpenFlags
        {
        public:
            //! \brief
            //! constructs base flags without any special settings
            //! applied
            OpenFlags()
                : m_flags(0)
            { }

            /**
            * \brief
            *     Sets the given initial open flags
            * \see
            *     setflags(const bool, const bool, const bool,
            *     const bool, const bool, const bool, const bool)
            **/
            explicit OpenFlags(const bool read, const bool write,
                const bool blocking = true,
                const bool create = false,
                const bool truncate = false,
                const bool append = false,
                const bool must_not_exist = false) :
                m_flags(0)
            {
                this->setflags(read, write, blocking, create,
                    truncate, append, must_not_exist);
            }

            //! \brief
            //! returns \c true if the file is to be opened only for
            //! reading
            bool readonly() const
            { return (m_flags & READ) != 0 && (m_flags & WRITE) == 0; }

            //! \brief
            //! returns \c true if the file is to be opened only for
            //! writing
            bool writeonly() const
            { return (m_flags & WRITE) != 0 && (m_flags & READ) == 0; }

            //! \brief
            //! returns \c true if the file is opened for both,
            //! reading and writing
            bool readWrite() const
            { return (m_flags & READ) != 0 && (m_flags & WRITE) != 0; }

            //! \brief
            //! returns \c true if the file is operating in blocking
            //! mode
            bool blocking() const
            { return (m_flags & NON_BLOCKING) == 0; }

            //! \brief
            //! returns true if the file is to be created if it
            //! doesn't yet exist
            bool createFile() const
            { return (m_flags & CREATE_FILE) != 0; }

            //! \brief
            //! returns true if the file is to be truncated if it
            //! exists
            bool truncate() const
            { return (m_flags & TRUNCATE) != 0; }

            //! returns true if append mode is set
            bool append() const
            { return (m_flags & APPEND) != 0; }

            //! \brief
            //! returns true if the file to be opened is not allowed
            //! to exist
            bool mustNotExist() const
            { return (m_flags & MUST_NOT_EXIST) != 0; }

        protected:
            /**
            * \brief
            *     sets base flags with the provided settings
            * \param[in] read
            *     If set to \c true then the file will be opened
            *     for read-access
            * \param[in] write
            *     If set to \c true then the file will be opened
            *     for write-access
            * \param[in] blocking
            *     If set to \c false then the file will be opened
            *     in non-blocking mode
            * \param[in] create
            *     If set to \c true then if the file to be opened
            *     doesn't exist, the file will be created as part
            *     of the open process. Otherwise the open process
            *     will fail in that case
            * \param[in] truncate
            *     If set to \c true then if the file to be opened
            *     is already existing then its content will be
            *     discarded and the file will have an initial size
            *     of zero bytes.
            * \param[in] append
            *     If set to \c true then before of any write
            *     operation the file pointer will be set to the
            *     end of the file i.e. any data will be appended
            *     to the file and it is impossible to overwrite
            *     already existing data.

            *     Note that on Win32 there is no real append mode.
            *     OSAL thus performs the seek to end of file
            *     operation itself internally to obtain the
            *     required behaviour. This emulation fails in case
            *     the underlying file descriptor is even handled
            *     by non-OSAL code e.g. by inheriting it to a
            *     child process that isn't using OSAL.

            *     The append mode actual is something that only
            *     applies to stream-based access to files. It
            *     doesn't have an effect for other access types
            *     like memory mapped access.
            * \param[in] must_not_exist
            *     If set to \c true then the open process will
            *     fail if the file to be opened already exists.
            *     This flag makes only sense if \c create is also
            *     set to \c true.

            *     This mode can be used to make sure that a file
            *     is really owned by the calling process and
            *     doesn't conflict with other users in the system.
            * \note
            *     About the non-blocking option. Non-Blocking
            *     operation generally only means the following:
            *
            *     - If the underlying file cannot currently
            *     perform a requested operation then the system
            *     call will not block until it is possible to
            *     perform the operation but will return
            *     immediatly, doing nothing.  This allows the
            *     client to avoid long waits for e.g. a device
            *     becoming ready
            *     - It does *not* mean that the client won't
            *     experience delays on behalf of an operation
            *     being carried out during a system call
            *     - According to POSIX, regular files are always
            *     readable and writeable thus rendering the
            *     non-blocking mode senseless. I'm not sure about
            *     what is the case with regular files residing on
            *     the network and similar hybrid cases
            *     - On Win32 there is no notion of a real
            *     non-blocking mode at all.  There is a
            *     "communications time out", however. This can be
            *     applied in case the file is a "communications
            *     device". OSAL attempts to set this timeout to
            *     zero for the underlying file, if possible, if
            *     non-blocking mode was set.
            * \note
            *     Note that if conflicting flags are specified
            *     then the safest mode of operation will be
            *     selected by OSAL. This means the following:
            *
            *     - if \a must_not_exist is set to \c true but \a
            *     create is set to \c false then the open
            *     operation will fail even if the file to be
            *     opened doesn't exist
            **/
            inline void setflags(const bool read,
                const bool write,
                const bool blocking = true,
                const bool create = false,
                const bool truncate = false,
                const bool append = false,
                const bool must_not_exist = false);

            void setbaseflags(uint_least32_t flags)
            {
                m_flags = flags;
            }

        private:
            static const uint_least32_t READ = 1 << 0;
            static const uint_least32_t WRITE = 1 << 1;
            static const uint_least32_t NON_BLOCKING = 1 << 2;
            static const uint_least32_t CREATE_FILE = 1 << 3;
            static const uint_least32_t TRUNCATE = 1 << 4;
            static const uint_least32_t APPEND = 1 << 5;
            static const uint_least32_t MUST_NOT_EXIST = 1 << 6;

            uint_least32_t m_flags;
        };

        /**
        * \brief
        *     Type used for setting open flags for readonly files

        *     The only option left for readonly files is the blocking
        *     mode.
        **/
        class ReadFlags
        {
        public:
            explicit ReadFlags(const bool blocking = true) :
                m_flags(true, false, blocking)
            { }

            const OpenFlags& operator()() const
            { return m_flags; }

            operator const OpenFlags&() const
            { return m_flags; }
        protected:
            OpenFlags m_flags;
        };

        /**
        * \brief
        *     Type used for setting open flags for writeonly files

        *     The complete range of flags is open for writeonly files.
        **/
        class WriteFlags
        {
        public:
            explicit WriteFlags(const bool blocking = true,
                    const bool create = false,
                    const bool truncate = false,
                    const bool append = false,
                    const bool must_not_exist = false) :
                m_flags(false, true, blocking, create,
                    truncate, append, must_not_exist)
            { }

            const OpenFlags& operator()() const
            { return m_flags; }

            operator const OpenFlags&() const
            { return m_flags; }

        protected:
            OpenFlags m_flags;
        };

        /**
        * \brief
        *     Type used for setting open flags for read-write files
        **/
        class ReadWriteFlags
        {
        public:
            explicit ReadWriteFlags(const bool blocking = true,
                    const bool create = false,
                    const bool truncate = false,
                    const bool append = false,
                    const bool must_not_exist = false) :
                m_flags(true, true, blocking, create,
                    truncate, append, must_not_exist)
            { }

            const OpenFlags& operator()() const
            { return m_flags; }

            operator const OpenFlags&() const
            { return m_flags; }

        protected:
            OpenFlags m_flags;
        }; // end class ReadWriteFlags

    public: // functions

        /**
        * \brief
        *     tests if currently a valid file is opened
        **/
        virtual bool isValid() const
        {
            return m_file != OSAL_INVALID_FILE_HANDLE;
        }

        /**
        * \brief
        *     Returns whether the last operation on the file failed
        **/
        bool hasError() const
        {
            return m_has_error;
        }

        /**
        * \brief
        *     Explicitly close a currently opened file

        *     If currently no file is opened then false is returned
        *     and nothing is done.
        *
        *     Note that upon close any not yet flushed data might be
        *     written by the operating system and thus the function
        *     call may block for a certain time.
        *
        *     If the currently opened file was opened from a
        *     BinTempFileRW and auto_delete was requested then the
        *     temporary file will be removed from the file system
        *     after closing the file.
        * \return
        *     true on error, false on success
        * \errorindicator
        *     via return code
        * \errors
        *     osal::SysError with IDs
        *
        *     - INTEGRITY_ERROR on bad file descriptor
        *     - IO_FAILURE if an I/O operation involved with closing
        *     the file failed
        *     - NO_PROCESS if the system told us that the owner of the
        *     file isn't there any more
        *     - UNKNOWN_ERROR on unexpected error conditions
        *
        *     if auto deletion of a temp file was requested then the
        *     errors defined at osal::FileSys::removeFile(const
        *     ipl::string&) may occur.
        **/
        virtual bool close();

        /**
        * \brief
        *     Retrieve a FileInfo object for the opened file

        *     If the current object is valid then you can get the
        *     FileInfo object associated with it. Getting the FileInfo
        *     object this way is more efficient then seperately
        *     constructing a FileInfo object for the file path.
        *
        *     Obtaining the FileInfo of a file this way makes most
        *     sense in case you want to open a file anyway regardless
        *     of what the FileInfo contains.
        * \errorindicator
        *     via returned object's isValid() member function
        * \errors
        *     ipl::CommonError with ID INVALID_USAGE if the current
        *     object is invalid.
        *
        *     Otherwise the errors stated at FileInfo::FileInfo(const
        *     char*, const bool)
        **/
        FileInfo getFileInfo() const;

        //! close() will be called
        virtual ~BinFileBase()
        {
            if( BinFileBase::close() ) // BRANCH_COVERAGE_UNTESTABLE
            {
                ipl_error.ack();
                ipl::cerr << __FUNCTION__
                    << "|Warning: Error closing BinFile: "
                    << ipl_error.getReasonList() << ipl::endl;
            }
        }

    protected: // functions
        //! \brief
        //! create an invalid BinFileBase, isValid() will return false,
        //! no error is raised
        BinFileBase() :
            m_file(OSAL_INVALID_FILE_HANDLE),
            m_has_error(false)
        { }

        /**
        * \brief
        *     Create a BinFile representation for the given, already
        *     opened file handle

        *     This construction type is useful for some special
        *     operations that involve getting a file descriptor from
        *     the system without using well-known paths.
        *
        *     The flags \c flags will not cause any effect to the open
        *     procedure but should represent the properties of the
        *     given file handle \c fh.
        *
        *     If there is already a file opened then an attempt is
        *     made to close it previously to opening the new one. If
        *     closing fails then the new file will not be opened.
        **/
        bool open(const FileHandle &fh, const OpenFlags &flags)
        {
            this->resetError();

            if( this->isValid() && this->close() ) // BRANCH_COVERAGE_UNTESTABLE
                return true;

            m_file = fh;
            m_flags = flags;

            return false;
        }

        /**
        * \brief
        *     Open the given file at path \c p with the given open
        *     options

        *     The file located at location \c p in the file system
        *     will be opened using the flags provided in \c flags.
        *
        *     If there is already a file opened then an attempt is
        *     made to close it previously to opening the new one. If
        *     closing fails then the new file will not be opened.
        *
        *     If the flags specified in \c flags cause the file at \c
        *     p to be created during the open process then the file
        *     access rights given in \c access will be applied. This
        *     does not happen on Win32, though.
        * \return
        *     true on error, false on success
        * \errorindicator
        *     via isValid(), return code
        * \errors
        *     osal::FileAccessError with an attached osal::SysError
        *     with IDs:
        *
        *    - NO_ACCESS / PERMISSION_DENIED
        *    - ALREADY_EXISTS / OBJECT_BUSY
        *    - TOO_MANY_OPEN_FILES / SYSTEM_RESSOURCES_EXHAUSTED
        *    - NOT_ENOUGH_SPACE / FS_NO_SPACE
        *    - FILE_BUSY / OBJECT_BUSY
        *    - BAD_PATH / INVALID_PATH
        *    - DEVICE_FAILURE / INVALID_DEVICE
        *    - UNKNOWN_ACCESS_ERROR attached with
        *        - OUT_OF_MEMORY
        *        - INTEGRITY_ERROR
        **/
        bool open(const char *p, const OpenFlags &flags, const FileAccess &access);

        //! \brief Open the given unicode path
        //! \see BinFileBase::open(const char*, const OpenFlags&)
        bool open(const osal::UnicodeString &ucs,
                const OpenFlags &flags, const FileAccess &access);

        //! \brief Open the given name at the given directory
        //!
        //! This function does not re-evaluate the directory path
        //! and thereby protects from opening an unintended file on the following
        //! platforms: POSIX>=200809
        //! \param[in] parent the parent directory
        //! \param[in] name the simple name of the file to open, no path separators are allowed.
        //! \param[in] resolve_links
        //!     Indicates if a symbolic link shall be followed.
        //!     An error is indicated by the return value if the current entry
        //!     is a link and \c resolve_links is \c false .
        //! \param[in] flags see other open command
        //! \param[in] access see other open command
        //! \see BinFileBase::open(const char*, const OpenFlags&)
        //! \errorindicator
        //!     via return code
        //! \errors
        //!     If currently a file is open and closing fails then the
        //!     errors described at BinFileBase::close() can occur.
        //! \link2req{satisfies,req~FW_OSAL_TOCTOU_SAFE_FILE_OPEN~1}
        bool openAt(const Directory &parent, const char* name, bool resolve_links, const OpenFlags &flags,
                    const FileAccess &access = FileAccess::owner_read|FileAccess::owner_write|FileAccess::group_read|FileAccess::group_write );

        /**
        * \brief
        *     Open a file from the given BinTempFileRW object

        *     First of all, if currently a file is open, then an
        *     attempt is made to close it. If that fails then the
        *     operation will not continue and an error is raised.
        *
        *     If \c tempfile is a valid temporary file then the
        *     ownership of the file will be taken over into the
        *     current object and \c tempfile will be invalidated.
        *
        *     If \c tempfile is invalid then the current object will
        *     become invalid, too but no error is raised.
        *
        *     If \c auto_delete is set to \c true then at close() time
        *     the temporary file will be removed from the file system
        *     automatically.
        * \errorindicator
        *     via return code
        * \errors
        *     If currently a file is open and closing fails then the
        *     errors described at BinFileBase::close() can occur.
        **/
        bool open(BinTempFileRW &tempfile, const bool auto_delete);

        /**
        * \brief
        *     Open a file from the given Pipe object

        *     First of all, if currently a file is open, then an
        *     attempt is made to cloase if. If that fails then the
        *     operation will not continue and an error is raised.
        *
        *     If \c for_writing is set to \c true then the write end
        *     of \c pipe will be used in the following operation.
        *     Otherwise the read end is used.
        *
        *     If the selected pipe end in \c pipe is valid (i.e. not
        *     been used already) then the ownership of the pipe will
        *     be taken over into the current object and the selected
        *     pipe end will be invalidated.
        *
        *     If the selected pipe end is invalid then the current
        *     object will become invalid, too but no error is raised.
        * \errorindicator
        *     via return code
        * \errors
        *     If currenty a file is open and closing fails then the
        *     errors described at BinFileBase::close() can occur.
        **/
        bool open(Pipe &pipe, const bool for_writing);

        /**
        * \brief
        *     Changes the size of a currently opened file to exactly
        *     \c bytes.

        *     If the currently opened file is larger then \c bytes
        *     bytes then the file will be reduced to \c bytes bytes,
        *     the extra data is lost.
        *
        *     If the currently opened file is shorter then \c bytes
        *     bytes then the file will be extended to \c bytes bytes,
        *     the new data is initialized with zeroes.
        *
        *     Be careful if using this API while doing processing on
        *     the file contents as the file contents can change due to
        *     this function call, of course.
        *
        *     For non-regular files the behaviour of this function is
        *     undefined.
        * \warning
        *     This call will fail on WIN32 if there are currently
        *     memory mappings defined on the file.
        *
        *     Also on WIN32 this call needs to temporarily change the
        *     file position pointer.
        * \note
        *     This member is protected here, because it only makes
        *     sense for writable files. It is made public in
        *     apropriate derived types, again.
        * \return
        *     true on error, false otherwise
        * \errorindicator
        *     via return code
        * \errors
        *     ipl::CommonError with IDs:
        *         - INVALID_USAGE if the file is currently invalid
        *     osal::SysError with IDs:
        *         - FS_NO_SPACE if the maximum file size is
        *         exceeded
        *         - IO_FAILURE if writing to the file system
        *         failed
        *         - INTEGRITY_ERROR on severe logical errors
        *         - PERMISSION_DENIED if the file is not writable
        *         (read-only file system)
        *         - UNKNOWN_ERROR on other occasions
        **/
        bool truncateSize(const size_t bytes);

        //! sets an error state for the object to active
        void setError()
        { m_has_error = true; }

        //! reset the error state for the object to inactive
        void resetError()
        { m_has_error = false; }

    protected: // data

        //! OS dependent data for file access
        FileHandle m_file;

        //! flags used for opening m_file, if opened at all
        OpenFlags m_flags;

        //! whether currently there's an error state set in the object
        bool m_has_error;

        //! \brief
        //! if a temporary file was opened with auto_delete option
        //! and it was valid then this is the assoc. filename
        ipl::string m_filename;
    }; // end class

    void BinFileBase::OpenFlags::setflags(const bool read,
        const bool write,
        const bool blocking,
        const bool create,
        const bool truncate,
        const bool append,
        const bool must_not_exist)
    {
        m_flags = 0;

        if( read )
        {
            m_flags |= READ;
        }

        if( write )
        {
            m_flags |= WRITE;
        }

        if( !blocking )
        {
            m_flags |= NON_BLOCKING;
        }

        if( create )
        {
            m_flags |= CREATE_FILE;
        }

        if( truncate )
        {
            m_flags |= TRUNCATE;
        }

        if( append )
        {
            m_flags |= APPEND;
        }

        if( must_not_exist )
        {
            m_flags |= MUST_NOT_EXIST;
        }
    }

}  // end of namespace osal

#if defined IPL_OS_POSIX || defined IPL_OS_INTEGRITY
#    include "posix/BinFileBase.inl"
#elif defined IPL_OS_WINPC
#    include "win32/BinFileBase.inl"
// #elif defined IPL_OS_INTEGRITY
// #    include "integrity/BinFileBase.inl"
#else
#    error "error undefined IPL_OS_ variant"
#endif

#endif
