/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_BINTEMPFILERW_HXX
#define OSAL_BINTEMPFILERW_HXX

#include <ipl_config.h>

#include <common/NonCopyable.hxx>
#include <common/Macros.hxx>

#include <osal/osal_dso.h>
#include <osal/osal.hxx>
#include <osal/Path.hxx>

#if defined IPL_OS_POSIX || defined IPL_OS_INTEGRITY
#    include "posix/BinFileDefs.hxx"
#elif defined IPL_OS_WINPC
#    include "win32/BinFileDefs.hxx"
#else
#    error "error undefined IPL_OS_ variant"
#endif

namespace osal {

    /**
    * \brief
    *    Creates a unique temporary file only accessible to the calling
    *    process

    *    This class implements a special creation strategy for a
    *    read-write file. It asks the system to determine a unique
    *    temporary file name. It ensures that the file really is a new
    *    file and is owned by the caller.
    *
    *    Due to this changed creation strategy there are no open flags to
    *    pass to the object.  The file will always be created, it is
    *    ensure that no file of that name already exists and the
    *    access-mode is read-write. Thus the corresponding
    *    osal::BinFileBase::ReadWriteFlags are createFile(),
    *    mustNotExist() and readWrite() set to \c true.
    *
    *    The filename chosen by the system can be retrieved after
    *    successful construction.
    *
    *    The object itself cannot be used for accessing the file.
    *    Construction of the object only makes sure that the file is
    *    created and opened by the calling process. To make it usable you
    *    need to use the object to construct a suitable type like
    *    StreamBinFileRW or MemBinFileRW.
    **/
    class OSAL_EXPORT BinTempFileRW :
        ipl::NonCopyable
    {
    public: // functions
        /**
        * \brief
        *    Creates and opens a unique temporary file for read-write
        *    access

        *    The given template path \c templ is used for creating a
        *    unique file path to use. The file will be created for
        *    in- and output by the caller. It is guaranteed that no
        *    race condition between checking whether there is already
        *    a suitable file and creating it occurs.
        *
        *    The actually associated path of the created file will be
        *    available via getFilename() after successful
        *    construction (i.e. if isValid() returns true).
        * \param[in] templ
        *    the relative or absolute pathname including part of the
        *    basename of the filename to use. A unique identifier
        *    will be added to that filename.  Note that some systems
        *    only use part of this basename and the rest is
        *    overwritten (currently on WinPC).
        * \note
        *    If you intend to create a large amount of temporary
        *    files in the same directory in this way then you may
        *    experience low performance as the system needs to check
        *    against more and more already existing files until a
        *    unique filename is finally found (especially on WinPC).
        * \warning
        *    The path length restrictions are different here then
        *    with other file system functions. This is because the OS
        *    is adding characters to the given \c templ to make the
        *    filename unique. It is best to use conservative path
        *    lengths.  OSAL can't give a precise maximum allowed
        *    length in this case.
        * \warning
        *    On WinPC we don't have a real possibility to avoid the
        *    race condition of checking the filename, creating the
        *    file and opening it. This an operating-system
        *    limitation. On WinPC the check for existence and
        *    creation is possibly atomic. But the opening part is a
        *    second step. Thus other processes/threads with suitable
        *    permission could open the file before the caller.
        * \errorindicator
        *    via isValid()
        * \errors
        *    Apart from the errors that can occur in
        *    BinFileBase::open() the following can occur:
        *
        *    osal::FileAccessError with IDs
        *      - ALREADY_EXISTS attached with osal::SysError with IDs
        *        - FILE_EXISTS if no unique filename could be
        *        determined for \c templ
        **/
        explicit BinTempFileRW(const osal::WidePath &templ);

        //! ASCII variant of BinTempFileRW(const osal::WidePath)
        BinTempFileRW(const osal::Path &templ) :
            m_file(OSAL_INVALID_FILE_HANDLE)
        {
            new(this) BinTempFileRW( osal::WidePath(UnicodeString(templ)) );
        }

        /**
        * \brief
        *    Removes the created file in case it's not been used

        *    If an instance of this class wasn't used to construct an
        *    actual file object like StremBinFileRW then upon
        *    destruction the file that was created at construction
        *    time will be removed from the file system again.
        **/
        ~BinTempFileRW();

        bool isValid() const
        { return m_file != OSAL_INVALID_FILE_HANDLE; }

        //! \brief
        //! contains the unique filename for the file in case isValid()
        //! returns \c true
        ipl::string getFilename() const
        { return m_filename; }

        ipl::wstring getFilenameWide() const
        { return m_filename; }
    protected:
        friend class BinFileBase;

        /**
        *  \brief
        *      invalidates the opened file handle

        *    Allows another class that uses this object to actually
        *    use the file to invalidate the local handle such that
        *    it's marked as "used" and ownership is moved to the
        *    caller.
        **/
        void invalidate()
        { m_file = OSAL_INVALID_FILE_HANDLE; }

        /**
        * \brief
        *     retrieve the handle of the currently opened file
        **/
        FileHandle getHandle() const
        { return m_file; }
    private:
        osal::FileHandle m_file;
        osal::WidePath m_filename;
    };

}  // end of namespace osal

#endif
