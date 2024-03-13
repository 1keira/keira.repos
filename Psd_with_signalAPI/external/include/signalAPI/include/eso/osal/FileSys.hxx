/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_FILESYS_HXX
#define OSAL_FILESYS_HXX

#include <ipl_config.h>

#include <common/types/string.hxx>
#include <common/types/list.hxx>
#include <osal/osal.hxx>
#include <osal/osal_dso.h>
#include <osal/UnicodeString.hxx>
#include <osal/FileInfo.hxx>
#include <osal/FileAccess.hxx>

namespace osal {

    class Directory;  /* forward declaration is sufficient, no include necessary */

    /**
    * \brief
    *    General file system information and operations

    *    Note that these are the lowest level file system operations
    *    available. They provide only little convenience e.g. they don't
    *    provide recursive operations or moving of files between file
    *    systems.
    *
    *    Non-primitive operations are added in util::FileSys (i.e.
    *    recursive copy, move, delete, directory creation).
    **/
    class OSAL_EXPORT FileSys
    {
    public: // functions

        /**
        * \brief
        *    Check for existence of a file system object at the given
        *    \a path.

        *    For the meaning of \a resolve_links see
        *    osal::FileInfo(const char*, const bool).
        *
        *    This static member function merely checks for existence
        *    of the given file.
        *
        *    If you desire to query additional file information you
        *    can directly construct a FileInfo object for \a path. If
        *    the construction succeeds then the file exists and you
        *    can query additional information. If construction fails
        *    then the file probably doesn't exist (check error
        *    return).
        *
        *    Similarly if you want to open a file it is better to
        *    directly construct an osal::File and check for success.
        *
        *    Note that there are inherent race conditions if you
        *    first check for existence of a file and then perform
        *    additional operations in a second step on the file (e.g.
        *    opening it). For example the file could have disappeared
        *    between the first and the second operation or been
        *    replaced by a different file.
        * \return
        *    If the string given in \a path refers to an existing
        *    file system object of any kind then this function
        *    returns zero. > 0 is returned if it doesn't exist. < 0
        *    is returned on error.
        * \errorindicator
        *    if < 0 is returned an error occured.
        * \errors
        *     FileAccessError attached with SysError with IDs:
        *
        *     - NO_ACCESS / PERMISSION_DENIED if part of \a path is
        *     inaccessible to the caller (this does not necessarily
        *     mean that \a path exists. it only means a part of it it
        *     is inaccessible).
        *     - BAD_PATH / INVALID_PATH if the given \a path is in
        *     principle erroneous (e.g. too long than any valid path)
        *     - DEVICE_FAILURE / IO_FAILURE if reading from file
        *     system failed
        *
        *     SysError with IDs:
        *
        *     - OUT_OF_MEMORY
        *     - UNKNOWN_ERROR on other errors.
        **/
        static int_fast8_t exists(const char* path,
            const bool resolve_links = true);

        //! \brief
        //! the same as exists(const char*, const bool) but with an
        //! ipl::string object as parameter
        static int_fast8_t exists(const ipl::string &p,
            const bool rl = true)
        { return exists(p.c_str(), rl); }

        //! the same as exists(const char*, const bool) but takes a
        //! UnicodeString as parameter
        static int_fast8_t exists(const UnicodeString &ucs,
            const bool rl = true);

        /*!
        * \brief
        *    Checks for the existance of file/directory in the directory \c parent.
        *
        * \details
        *    as exists(const char*, const bool), but the query is limited to \c parent directory.
        *
        *    Note: This function only retrieves information,
        *    this information may already be outdated when the call returns.
        *
        * \param[in] parent the parent directory
        * \param[in] name name of the file to check
        * \param[in] resolve_links indicates if a symbolic link shall be followed.
        * \return 0 in case the file exists
        * \link2req{satisfies,req~FW_OSAL_TOCTOU_SAFE_DIR_SCAN~1}
        */
        static int_fast8_t existsAt(const Directory &parent, const char* name,
            bool resolve_links = false);

        /**
        * \brief
        *    Create a new Directory at \c path

        *    The directory denoted by \c path will be created with
        *    read and write permissions for the current process
        *    execution context set.
        *
        *    Only the last component of \c path may not exist. This
        *    means you cannot create multiple directories in one go
        *    using this call.
        *
        *    You will need write permission in the parent directory
        *    of the new directory to create.
        *
        *    It is possible that the newly created directory inherits
        *    properties from its parent directory. It is also
        *    possible that certain access rights are removed/added by
        *    global system masks.
        * \return
        *    true on error, false otherwise
        * \errorindicator
        *    via return code
        * \errors
        *    FileAccessError attached with osal::SysError with IDs:
        *
        *    - NO_ACCESS / PERMISSION_DENIED search permission denied
        *    for part of \c path or parent of the to be created
        *    directory doesn't allow write for the caller
        *    - ALREADY_EXISTS / FILE_EXISTS if a file system object
        *    already exists at \c path
        *    - BAD_PATH / INVALID_PATH if part of \c path isn't valid
        *    (not existing directories, too long, broken symlinks,
        *    loops)
        *    - UNKNOWN_ACCESS_ERROR attached with
        *        - SYSTEM_RESSOURCES_EXHAUSTED if the directory
        *        cannot be created due to file system ressources
        *        limitations
        *        - UNKNOWN_ERROR on other occasions
        **/
        static bool createDir(const char *path);

        //! \brief
        //! the same as createDir(const char*) but with an ipl::string
        //! object as parameter
        static bool createDir(const ipl::string &p)
        { return createDir(p.c_str()); }

        //! \brief
        //! the same as createDir(const char*) but with a unicode string
        //! as parameter
        static bool createDir(const osal::UnicodeString &ucs);

        /*!
        * \brief
        *    Create a new Directory named \c name in directory \c parent
        *
        * \details
        *    as createDir(const char*), but the request is limited to \c parent directory
        *
        * \param[in] parent the parent directory
        * \param[in] name name of the directory to create
        * \return true on error
        * \link2req{satisfies,req~FW_OSAL_TOCTOU_SAFE_DIR_CREATE~1}
        */
        static bool createDirAt(const Directory &parent, const char* name);

        /**
        * \brief
        *    Remove the File System Object at \c path

        *    The given object will be removed provided the caller has
        *    got the required permissions to do that. If the object
        *    is of type DIRECTORY then removal may fail. Note that it
        *    *may* fail. Some systems may even allow to remove
        *    directories with this call. You just shouldn't rely on
        *    it and should not be surprised if it does or does not
        *    handle directories.
        *
        *    To safely remove directories use removeDir().
        *
        *    On some systems (notably POSIX compatible ones) removal
        *    of the file system object usually merely means to remove
        *    the name from the file system. I.e.  the file will not
        *    be visible any more by others. Actual deletion of the
        *    file on the file system will only happen in case no
        *    other users in the system have references left to that
        *    file (even on POSIX this depends on the POSIX
        *    implementation, the file system implementation etc.).
        *
        *    It is also possible that the name of the object is
        *    removed but other names for the object are still on the
        *    system (e.g. hard links) and the content of the object
        *    will still be available somewhere.
        *
        *    On other systems (notably WIN32) removal will only
        *    succeed in case nobody else has the file opened at the
        *    time (except for some special cases not discussed here).
        *
        *    Note that on WIN32 if the file system object at \c path
        *    has the read-only attribute set then this call will
        *    still remove it. Also on POSIX if read permission isn't
        *    set for the file but the current process is the owner of
        *    the file then deletion will succeed.
        * \return
        *    true on error, false otherwise
        * \errorindicator
        *    via return code
        * \errors
        *    FileAccessError attached with osal::SysError with IDs:
        *
        *    - NO_ACCESS / PERMISSION_DENIED search permission denied
        *    for part of \c path or parent of the to be created
        *    directory doesn't allow write for the caller or the file
        *    system is read-only
        *    - BAD_PATH / INVALID_PATH if part of \c path isn't valid
        *    (not existing directories, too long, broken symlinks,
        *    loops) or if \c path denotes a directory.
        *    - FILE_BUSY / OBJECT_BUSY if the file system object is
        *    used by other processes or the system or in case of a
        *    directory if the directory is not empty
        *    - UNKNOWN_ACCESS_ERROR / UNKNOWN_ERROR on other
        *    occasions
        *    - IS_DIR / INVALID_PATH if \c path is a directory
        *
        *    osal::SysError with IDs:
        *
        *    - OUT_OF_MEMORY if not enough memory is left to perform
        *    the operation
        *    - UNKNOWN_ERROR on other occasions
        **/
        static bool removeFile(const char*);

        //! \brief
        //! the same as removeFile(const char*) but with an ipl::string
        //! object as parameter
        static bool removeFile(const ipl::string &p)
        { return removeFile(p.c_str()); }

        //! \brief
        //! the same as removeFile(const char*) but with a unicode
        //! string object as parameter
        static bool removeFile(const osal::UnicodeString &ucs);

        /*!
        * \brief
        *    Delete the file named \c name in directory \c parent
        *
        * \details
        *    as removeFile(const char*), but the request is limited to \c parent directory
        *
        * \param[in] parent the parent directory
        * \param[in] name name of the file to remove
        * \return true on error
        * \link2req{satisfies,req~FW_OSAL_TOCTOU_SAFE_FILE_UNLINK~1}
        */
        static bool removeFileAt(const Directory &parent, const char* name);

        /**
        * \brief
        *    Remove the Directory at \c path

        *    Does the same as removeFile() but for directory file
        *    system objects.
        *
        *    This call only succeeds in case the directory denoted by
        *    \c path is empty.
        * \return
        *    true on error, false otherwise
        * \errorindicator
        *    via return code
        * \errors
        *    FileAccessError attached with osal::SysError with IDs:
        *
        *    - NO_ACCESS / PERMISSION_DENIED search permission denied
        *    for part of \c path or parent of the to be created
        *    directory doesn't allow write for the caller or the file
        *    system is read-only
        *    - BAD_PATH / INVALID_PATH if part of \c path isn't valid
        *    (not existing directories, too long, broken symlinks,
        *    loops), or if the \c path is not denoting a directory.
        *    - FILE_BUSY / OBJECT_BUSY if the file system object is
        *    used by other processes or the system
        *    - FILE_BUSY / DIR_NOT_EMPTY if the directory cannot be
        *    deleted, because it contains other files
        *    - UNKNOWN_ACCESS_ERROR / UNKNOWN_ERROR on other
        *    occasions
        *
        *    osal::SysError with IDs:
        *
        *    - OUT_OF_MEMORY
        **/
        static bool removeDir(const char *path);

        //! \brief
        //! the same as removeDir(const char*) but with an ipl::string
        //! object as parameter
        static bool removeDir(const ipl::string &p)
        { return removeDir(p.c_str()); }


        //! \brief
        //! the same as removeDir(const char*) but with a unicode string
        //! object as parameter
        static bool removeDir(const osal::UnicodeString &ucs);

        /*!
        * \brief
        *    Delete the directory named \c name in directory \c parent
        *
        * \details
        *    as removeDir(const char*), but the request is limited to \c parent directory
        *
        * \param[in] parent the parent directory
        * \param[in] name name of the directory to remove
        * \return true on error
        * \link2req{satisfies,req~FW_OSAL_TOCTOU_SAFE_FILE_UNLINK~1}
        */
        static bool removeDirAt(const Directory &parent, const char* name);

        /**
        * \brief
        *    Move the given Object at Location \c source to Location
        *    \c target

        *    If \c target doesn't point to an existing file system
        *    object then the object at \c source will be put at
        *    location \c target. All but the last component of the
        *    path \c target must exist in this case.
        *
        *    \c target must not contain a prefix that names \c source
        *    (e.g. renaming a directory into a subdirectory of
        *    itself).
        *
        *    If both \c source and \c target name an existing file
        *    system object of type DIRECTORY then \c target will be
        *    removed and \c source will be put at location \c target.
        *    This only succeeds if the directory at \c target is
        *    empty.
        *
        *    If both \c source and \c target name an existing file
        *    system object of type REGULAR then \c target will be
        *    removed and \c source will be put at location \c target.
        *
        *    If both \c source and \c target name existing file
        *    system objects of different types then the operation
        *    will fail.
        *
        *    Note that systems usually don't support moving files
        *    between different file systems. You need to perform a
        *    copy of \c source to \c target and remove source
        *    manually in those cases.
        * \return
        *    true on error, false on success
        * \errorindicator
        *    via return code
        * \errors
        *     FileAccessError attached with osal::SysError with IDs:
        *
        *    - NO_ACCESS / PERMISSION_DENIED if part of \c source or
        *    \c target cannot be searched; or directory containing \c
        *    source or \c target cannot be written
        *    - DEVICE_FAILURE / IO_FAILURE on physical device errors
        *    - BAD_PATH / INVALID_PATH if \c target contains a path
        *    prefix of \c source; if \c source and \c target name
        *    different types of file system objects; too many
        *    symlinks/loops in \c source or \c target; if path or
        *    path component of \c source or \c target is too long; \c
        *    source is not existing or any of the paths is empty; or
        *    part of \c source or \c target is no directory
        *    - UNKNOWN_ACCESS_ERROR attached with IDs
        *        - SYSTEM_RESSOURCES_EXHAUSTED if file system
        *        ressources other than disk space are lacking
        *        (e.g. file descriptors, inodes)
        *        - NOT_IMPLEMENTED if you're trying to move a
        *        file system object between different file
        *        systems and this isn't possible on this system
        *        - UNKNOWN_ERROR on other occasions
        *    - NOT_ENOUGH_SPACE / FS_NO_SPACE if file system is
        *    lacking space to create the file system object at \c
        *    target
        *    - FILE_BUSY / OBJECT_BUSY if \c source or \c target are
        *    in use by the system or other processes and the move
        *    operation can thus not be performed
        **/
        static bool move(const char *source,
            const char *target);

        //! \brief
        //! the same as move(const char*, const char*) but with
        //! ipl::string objects as parameters
        static bool move(const ipl::string &source,
            const ipl::string &target)
        { return move(source.c_str(), target.c_str()); }

        //! \brief
        //! the same as move(const char*, const char*) but with unicode
        //! string objects as parameters
        static bool move(
            const osal::UnicodeString &source,
            const osal::UnicodeString &target);

        /*!
        * \brief
        *    Moves the file or directory named \c src_name in directory \c src_parent
        *    to file/directory named \c dst_name in directory \c dst_parent
        *
        * \details
        *    as move(const char*,const char*), but the request is limited
        *    to \c src_parent and \c dst_parent directories
        *
        * \param[in] src_parent the source parent directory
        * \param[in] src_name source name of the file/directory to move
        * \param[in] dst_parent the destination parent directory
        * \param[in] dst_name destionation name of the file/directory to move
        * \return true on error
        * \link2req{satisfies,req~FW_OSAL_TOCTOU_SAFE_FILE_MOVE_COPY~1}
        */
        static bool moveAt(const Directory &src_parent, const char* src_name,
            const Directory &dst_parent, const char* dst_name);

        /**
        * \brief
        *    Copy file at \c source to location \c target

        *    Copies the file system object at \c source to the
        *    location \c target. Both \c source and \c target must
        *    name valid paths to non-directory file system objects.
        *    The object at \c target must not exist.
        *
        *    If \c buf is NULL then the function will create a
        *    temporary buffer of size \c bufsize bytes for copying
        *    data from \c source to \c target. If you intend to copy
        *    multiple files then it might be better to provide an
        *    external buffer in \c buf that has room for \c bufsize
        *    bytes.
        * \return
        *    true on error, false on success
        * \errorindicator
        *    via return code
        * \errors
        *    The errors described at StreamBinFileR(...),
        *    StreamBinFileW(...), StreamBinFileR::performRead(),
        *    StreamBinFileW::performWrite(),
        *    StreamBinFileBase::close() can occur.
        **/
        inline static bool copy(const char *source, const char *target,
            const size_t bufsize, void *buf = NULL);

        //! the same as copy(const char*, const char*, const size_t, void*)
        inline static bool copy(const ipl::string &source,
            const ipl::string &target,
            const size_t bufsize, void *buf = NULL)
        {
            return copy(source.c_str(), target.c_str(), bufsize, buf);
        }

        //! \brief
        //! unicode variant of copy(const char*, const char*, const
        //! size_t, void*)
        static bool copy(const osal::UnicodeString &source,
            const osal::UnicodeString &target,
            const size_t bufsize, void *buf = NULL);

        /*!
        * \brief
        *    Copies the file named \c src_name in directory \c src_parent
        *    to file named \c dst_name in directory \c dst_parent
        *
        * \details
        *    as copy(const char*,const char*,const size_t, void*),
        *    but the request is limited
        *    to \c src_parent and \c dst_parent directories
        *
        * \param[in] src_parent the source parent directory
        * \param[in] src_name source name of the file/directory to move
        * \param[in] dst_parent the destination parent directory
        * \param[in] dst_name destionation name of the file/directory to move
        * \param[in] bufsize size of the provided buffer \c buf
        * \param buf pointer to a temporary data buffer or NULL
        * \return true on error
        * \link2req{satisfies,req~FW_OSAL_TOCTOU_SAFE_FILE_MOVE_COPY~1}
        */
        static bool copyAt(const Directory &src_parent, const char* src_name,
            const Directory &dst_parent, const char* dst_name,
            const size_t bufsize, void *buf = NULL );

        /**
        * \brief
        *     Change the access rights for the file system object at
        *     \c path

        *     You need appropriate permissions to alter the access
        *     rights of \c path. On POSIX systems this usually means
        *     that you need to be the owner of \c path.
        *
        *     On POSIX systems this function alters the user mode bits
        *     to the settings provided in \c access.
        *
        *     On WIN32 systems this function does nothing currently.
        * \return
        *     true on error, false on success
        * \errorindicator
        *     via return code
        * \errors
        *     FileAccessError attached with an SysError with IDs:
        *
        *     - NO_ACCESS / PERMISSION_DENIED if part of \c path can't be
        *     accessed, if \c path is not owned by the caller or if \c
        *     path resides on a read-only file system
        *     - BAD_PATH / INVALID_PATH if part of all of \c path
        *     isn't existing, if part of \c path is not a directory,
        *     if \c path is not existing or errors with symlinks
        *     occured
        *     - DEVICE_FAILURE / IO_FAILURE if a hardware error
        *     occured
        *     - UNKNOWN_ACCESS_ERROR / INTEGRITY_ERROR, UNKNOWN_ERROR
        *     on severe or unexpected errors
        *
        *
        *     SysError with ID OUT_OF_MEMORY if the operation could
        *     not be performed due to lack of memory
        **/
        static bool changeAccess(const char *path, const FileAccess &access);

        /**
        * \brief
        *     Variant of changeAccess taking an STL string object
        * \see
        *     changeAccess(const char*, const FileAccess&)
        **/
        static bool changeAccess(const ipl::string &path, const FileAccess &access)
        {
            return changeAccess(path.c_str(), access);
        }

        /**
        * \brief
        *     Variant of changeAccess taking a unicode string
        * \see
        *     changeAccess(const char*, const FileAccess&)
        **/
        inline static bool changeAccess(const UnicodeString &ucs,
                                        const FileAccess &access);

        /*!
        * \brief
        *    Change the access rights for the object named \c name in directory \c parent
        *
        * \details
        *    as changeAccess(const char*, const FileAccess&),
        *    but the request is limited to \c parent directory
        *
        * \param[in] parent the parent directory
        * \param[in] name name of the object to modify
        * \param[in] access access rights to set
        * \param[in] resolve_links true if a symlink shall be followed,
        *                          false if the access of the link shall be updated
        * \return true on error
        * \link2req{satisfies,req~FW_OSAL_TOCTOU_SAFE_FILE_CHANGE_META~1}
        */
        static bool changeAccessAt(const Directory &parent, const char* name, const FileAccess &access,
                                   bool resolve_links=false);

        static FileAccess getAccess(const UnicodeString &filename) {
            return FileInfo(filename).getAccess();
        }

        /*!
        * \brief
        *    Get the access rights for the object named \c name in directory \c parent
        *
        * \details
        *    as getAccess(const UnicodeString&), but the request is limited to \c parent directory
        *
        *    Note: This function only retrieves information,
        *    this information may already be outdated when the call returns.
        *
        * \param[in] parent the parent directory
        * \param[in] name name of the object to query
        * \param[in] resolve_links true if a symlink shall be followed
        * \return FileAccess of the object
        * \link2req{satisfies,req~FW_OSAL_TOCTOU_SAFE_FILE_CHANGE_META~1}
        */
        static FileAccess getAccessAt(const Directory &parent, const char* name, bool resolve_links=false)
        {
            return FileInfo(parent,name,resolve_links).getAccess();
        }

        //! \brief Set owner and group of file \a filename to \a user and \a group, respectively
        static bool changeOwnerGroup(const UnicodeString &filename,
                                    const User &user, const Group &group);

        /*!
        * \brief
        *    Change the owner and group for the object \c name in directory \c parent
        *
        * \details
        *    as changeOwnerGroup(const UnicodeString&,const User&, const Group&),
        *    but the request is limited to \c parent directory
        *
        * \param[in] parent the parent directory
        * \param[in] name name of the object to modify
        * \param[in] user new owner
        * \param[in] group new group
        * \param[in] resolve_links true if a symlink shall be followed,
        *                          false if the owner/Group of the link shall be updated
        * \return true on error
        * \link2req{satisfies,req~FW_OSAL_TOCTOU_SAFE_FILE_CHANGE_META~1}
        */
        static bool changeOwnerGroupAt(const Directory &parent, const char* name, const User &user,
                                       const Group &group, bool resolve_links=false);

        //! \brief Set owner of file \a filename to \a user
        static bool changeOwner(const osal::UnicodeString &filename, const osal::User &user)
        {
            return changeOwnerGroup(filename, user, Group(-1));
        }

        //! \brief Retrieve owner of file \a filename
        static User getOwner(const UnicodeString &filename) {
            return FileInfo(filename).getOwner();
        }

        /*!
        * \brief
        *    Get the owner for the object named \c name in directory \c parent
        *
        * \details
        *    as getOwner(const UnicodeString&), but the request is limited to \c parent directory
        *
        *    Note: This function only retrieves information,
        *    this information may already be outdated when the call returns.
        *
        * \param[in] parent the parent directory
        * \param[in] name name of the object to query
        * \param[in] resolve_links true if a symlink shall be followed
        * \return User who is the owner of the object
        * \link2req{satisfies,req~FW_OSAL_TOCTOU_SAFE_FILE_CHANGE_META~1}
        */
        static User getOwnerAt(const Directory &parent, const char* name, bool resolve_links=false)
        {
            return FileInfo(parent,name,resolve_links).getOwner();
        }

        //! \brief Set group of file \a filename to \a group
        static bool changeGroup(const osal::UnicodeString &filename, const osal::Group &group)
        {
            return changeOwnerGroup(filename, User(-1), group);
        }

        //! \brief Retrieve group of file \a filename
        static Group getGroup(const UnicodeString &filename) {
            return FileInfo(filename).getGroup();
        }

        /*!
        * \brief
        *    Get the group for the object named \c name in directory \c parent
        *
        * \details
        *    as getGroup(const UnicodeString&), but the request is limited to \c parent directory
        *
        *    Note: This function only retrieves information,
        *    this information may already be outdated when the call returns.
        *
        * \param[in] parent the parent directory
        * \param[in] name name of the object to query
        * \param[in] resolve_links true if a symlink shall be followed
        * \return Group of the object
        * \link2req{satisfies,req~FW_OSAL_TOCTOU_SAFE_FILE_CHANGE_META~1}
        */
        static Group getGroupAt(const Directory &parent, const char* name, bool resolve_links=false)
        {
            return FileInfo(parent,name,resolve_links).getGroup();
        }

        /**
        * \brief
        *    Returns the Maximum Length of a Filename on the given
        *    File System

        *    On some systems the maximum length of a filename may
        *    differ between different file systems. This function
        *    returns for a specific file system path the maximum
        *    filename length.
        *
        *    Note that this length is merely the maximum length that
        *    the underlying file system supports. There still is the
        *    maximum path component length imposed by the system API.
        *    This size is given by osal::Path::MAX_COMPONENT_LEN.
        * \param[in]
        *     path The path to the file system for which to query the
        *     maximum component length. This needs to be an existing
        *     file system object residing on the desired file system.
        * \param[out]
        *    length Maximum length of a filename in characters in \c
        *    path
        * \errors
        *     osal::FileAccessError attached with SysError with IDs:
        *
        *     - BAD_PATH / INVALID_PATH
        *     - NO_ACCESS / PERMISSION_DENIED
        *     - DEVICE_FAILURE / IO_FAILURE
        *     - UNKNOWN_ACCESS_ERROR / UNKNOWN_ERROR
        *
        *     common::CommonError with id NOT_SUPPORTED
        *     if the file system does not provide a maximum component length
        *
        * \return
        *    true on error, false otherwise
        **/
        static bool maxComponentLength(
            const char *path,
            uint_fast32_t &length);

        //! \brief
        //!    the same as maxComponentLength(const char*,
        //!    uint_fast32_t&) but with an ipl::string object as
        //!    parameter
        static bool maxComponentLength(const ipl::string &path,
            uint_fast32_t &length)
        { return maxComponentLength(path.c_str(), length); }

        //! \brief
        //!    the same as maxComponentLength(const char*,
        //!    uint_fast32_t&) but with a unicode string object as
        //!    parameter
        static bool maxComponentLength(
            const osal::UnicodeString &path,
            uint_fast32_t &length);

        /**
        * \brief
        *    Get a List of File System Entry Points in the System

        *    On some systems (notably WinPC) there doesn't exist a
        *    single-rooted file system hierarchy but a number of
        *    "drives" that aren't connected to each other from a file
        *    system point of view.
        *
        *    To be able to search all file systems in the system you
        *    can get a list of all recognized file system entry
        *    points in the system via this function.
        *
        *    On systems that don't have a notion of drives you will
        *    simply get a single entry point for the file system
        *    root.
        * \errorindicator
        *    On error an empty list is returned. No error is raised.
        **/
        static ipl::list<ipl::string> getEntryPoints();

        /**
        * \brief
        *     Does the same as getEntryPoints() but returns a list of
        *     unicode string objects as an out parameter.
        **/
        static void getEntryPoints(ipl::list<osal::UnicodeString> &list);

        /**
        * \brief
        *    Returns the current working directory of the calling
        *    process to \c wd

        *    The current working directory determines from which
        *    position relative file system paths are interpreted.
        *
        *    If parts of the current working directory path happen to
        *    be of type LINK then these links will be resolved and
        *    the resulting path returned.
        * \return
        *    true on error, false on success
        * \errorindicator
        *    via return code
        * \errors
        *    SysError with reason:
        *
        *    - OUT_OF_MEMORY on out of memory condition
        *    - INTEGRITY_ERROR on serious logical, internal errors
        *    - INVALID_PATH if the current working directory has
        *    become invalid (e.g.  deleted)
        *    - PERMISSION_DENIED permission denied for access of the
        *    current working directory (or one of its path
        *    components)
        *    - UNKNOWN_ERROR on other errors.
        **/
        static bool currentWD(ipl::string &wd);

        //! \brief
        //!    same as currentWD(ipl::string&) but taking a unicode
        //!    string instead
        static bool currentWD(osal::UnicodeString &wd);

        /**
        * \brief
        *    Change the current working directory of the calling
        *    process to the given path
        * \note
        *    As this is a per-process attribute multi-threaded access
        *    without proper synchronization will soon blow up things.
        *
        *    \c path may be an absolute path or a path relative to
        *    the current working directory returned from currentWD().
        * \return
        *    true on error, false on success
        * \errorindicator
        *    via return code
        * \errors
        *    FileAccessError attached with SysError with IDs:
        *
        *    - BAD_PATH / INVALID_PATH if \c path is not valid
        *    - NO_ACCESS / PERMISSION_DENIED if \c path it is not
        *    accessible to the caller.
        *    - NO_DIR / NO_DIRECTORY if \c path doesn't point to an
        *    object of type DIRECTORY
        *    - UNKNOWN_ACCESS_ERROR attached with
        *        - INTEGRITY_ERROR on serious internal errors,
        *        addressing errors
        *        - UNKNOWN_ERROR on other errors.
        *    - DEVICE_FAILURE / IO_FAILURE if an error accessing the
        *    file system occured
        **/
        static bool changeWD(const char *path);

        //! \brief
        //! does the same as changeWD(const char*) but with an
        //! ipl::string object as parameter
        static bool changeWD(const ipl::string &path)
        { return changeWD(path.c_str()); }

        //! \brief
        //! does the same as changeWD(const char*) but takes a unicode
        //! string as parameter instead
        static bool changeWD(
            const osal::UnicodeString &path);

        /**
        * \brief
        *    Get the Path to the System's Directory for Temporary
        *    Data

        *    The directory for temporary data can be used by
        *    applications to place files of temporary nature i.e.
        *    deletion of the data stored there is non-critical to
        *    applications.
        *
        *    The path to this directory is influenced by environment
        *    variables i.e. it is possible that the path changes
        *    between invocations of a program. This call determines
        *    the path that is currently set.
        *
        *    The call does not assert that the directory actually
        *    exists (the directory not existing can be considered a
        *    severe configuration error).
        *
        *    As the call is reading environment variables for the
        *    current process you need to assure that no other threads
        *    are modifying the environment in parallel to the
        *    execution of this call.
        * \return
        *    A string defining the file system location where
        *    temporary data for this process can be stored. If an
        *    error occured then an empty string is returned. No error
        *    raised. To avoid copy operations the returned string may
        *    origin from system libraries and thus may be subject to
        *    changes of the current process's environment
        *    information.
        **/
        static const char* getTempPath();

        //! \brief
        //!    Does the same as getTempPath() but returns the path into
        //!    a unicode string out parameter
        static void getTempPath(osal::UnicodeString &path);

        /**
        * \brief
        *    Get the Path to the Home Directory Associated with the
        *    current Process

        *    The home directory is associated to a specific system
        *    user. I.e. if a program is called from different user
        *    contexts then different home directories will be
        *    returned.
        *
        *    In the home directory persistent application data can be
        *    stored that is specific to a user context i.e. not
        *    system-wide.
        *
        *    This call does not assert that the directory actually
        *    exists (the directory not existing can be considered a
        *    severe configuration error).
        *
        *    The home directory path is determined via reading the
        *    current process's environment variables. Thus you need
        *    to ensure that the process environment is not modified
        *    in parallel by other threads during the execution of
        *    this call.
        * \return
        *    A string defining the file system location where user
        *    data for this process can be stored. If an error occured
        *    then an empty string is returned. No error is raised. To
        *    avoid copy operations the returned string may origin
        *    from system libraries and thus may be subject to changes
        *    of the current process's environment information.
        **/
        static const char* getHomePath();

        /**
        * \brief
        *    Does the same as getHomePath() but returns the
        *    path in a unicode string out parameter.
        **/
        static void getHomePath(osal::UnicodeString &path);

        /**
        * \brief
        *    Get a List of Available File System Mount Points

        *    On most systems additional file systems can be
        *    transparently mounted anywhere below the entry points as
        *    determined by getEntryPoints(). This call returns a list
        *    of all those file systems.
        *
        *    This information can for example be used to
        *    pre-determine possible file system transitions in
        *    recursive file system operations.
        *
        *    The returned list will always contain any entry points
        *    as returned by getEntryPoints() plus any mounted file
        *    systems below the entry points.
        * \note
        *    The operations for obtain this list of mount points is
        *    potentially expensive (notably on QNX, WinPC) thus you
        *    should get this list only as often as necessary (usually
        *    once).
        * \warning
        *    This call may returned certain mount points more than
        *    once under special conditions (e.g. union mounts). Also
        *    it is possible that the same file system is mounted
        *    multiple times in the file system hierarchy. Use
        *    osal::FileInfo::getFsId() to determine such duplicates.
        * \return
        *    On success the available file system mount points. On
        *    error an empty list.  No error will be raised.
        **/
        static ipl::list<ipl::string> getMountPoints();

        /**
        * \brief
        *    Does the same as getMountPoints() but returns a list of
        *    unicode strings as an out parameter instead
        **/
        static void
            getMountPoints(ipl::list<osal::UnicodeString> &list);

        /**
        * \brief
        *    read the content of the symlink located at \c path

        *    The symlink located at \c path is looked up and the
        *    target it is pointing to is returned in the given buffer
        *    \c buffer.
        *
        *    At max \c size bytes will be put into \c buffer. The
        *    last byte put into the buffer is always a
        *    null-terminator. If the symlink target is longer than \c
        *    size - 1 bytes then the string put in \c buffer is
        *    truncated to \c size - 1 bytes. There is no possibility
        *    to detect this condition.
        *
        *    It is suggested to set \c size to
        *    osal::Path::MAX_PATH_LEN to avoid this condition
        *    completely.
        *
        *     The number of characters put into \c buffer (not
        *     including the null terminator) is put into \c size upon
        *     return of the function call. On error \c size is set to
        *     zero and an empty string is returned in \c buffer for
        *     safety reasons.
        * \note
        *     Symlinks are only supported on POSIX platforms i.e.
        *     especially not on WIN32 platforms. This facility is
        *     still provided by OSAL, because symlinks are an
        *     important concept on POSIX platforms and not being able
        *     to work with them at all would be a great loss.
        * \note
        *     You can determine whether a file is a symlink by using
        *     osal::FileInfo on \c path with the \c resolve_links set
        *     to \c false.
        * \return
        *     true on error, false otherwise
        * \errorindicator
        *    via return code
        * \errors
        *     FileAccessError attached with osal::SysError with IDs:
        *
        *     - NO_ACCESS / PERMISSION_DENIED if lookup of \c path is
        *     not allowed
        *     - BAD_PATH INVALID_PATH if something is wrong with \c
        *     path e.g.  \c path is not a symlink, \c path doesn't
        *     point to any file system object or \c path is too long.
        *     - DEVICE_FAILURE / IO_FAILURE if reading from the file
        *     system failed
        *     - UNKNOWN_ACCESS_ERROR / NOT_IMPLEMENTED if symlinks
        *     aren't supported on the current platform
        *     - UNKNOWN_ACCESS_ERROR / UNKNOWN_ERROR on other
        *     occasions
        **/
        static bool readLink(const char *path, char *buffer,
            size_t &size);

        /**
        * \brief
        *    Read a symlink content into an ipl::string

        *    Calls readLink(const char*, char*, size_t) with a
        *    suitably large buffer to contain the link target and
        *    returns the string in \c target.
        *
        *    Note that this requires an additional copy operation
        *    compared to using a plain c string.
        **/
        inline static bool readLink(const ipl::string &path,
            ipl::string &target);

        /**
        * \brief
        *     Does the same as readLink(const char*, char*, size_t)
        *     but reads \c path and returns \c target from/into
        *     unicode string objects
        **/
        inline static bool readLink(const osal::UnicodeString &path,
            osal::UnicodeString &target);

        /*!
        * \brief
        *    Reads the link named \c name in directory \c parent
        *
        * \details
        *    as readLink(const char*, char*, size_t&), but the request is limited to \c parent directory
        *
        *    Note: This function only retrieves information,
        *    this information may already be outdated when the call returns.
        *
        * \param[in] parent the parent directory
        * \param[in] name name of the link to retrieve
        * \param buffer buffer where to store the result
        * \param size when calling this function: the size of the buffer;
        *     when returning: the size of the contents (excluding the terminating zero).
        * \return true on error
        * \link2req{satisfies,req~FW_OSAL_TOCTOU_SAFE_LINK_CREATE_READ~1}
        */
        static bool readLinkAt(const Directory &parent, const char* name, char *buffer,
            size_t &size);

        /**
        * \brief
        *    Create a symlink at path \c link containing the path \c
        *    target

        *    On POSIX systems we can have symlinks which are simple
        *    redirections in the file system. A symlink is merely a
        *    file that contains the path of another file. The target
        *    path needs not to exist during creation.
        *
        *    On WIN32 systems symlinks cannot be created.
        * \return
        *    true on error, false on success
        * \errorindicator
        *    via return code
        * \errors
        *    FileAccessError attached with osal::SysError with IDs:
        *
        *    - NO_ACCESS / PERMISSION_DENIED if \c link cannot be
        *    accessed, write-permission is denied or the file system
        *    where \c link would reside is read-only
        *    - ALREADY_EXISTS / FILE_EXISTS if \c link is already an
        *    existing file system object
        *    - DEVICE_FAILURE / IO_FAILURE if an error while writing
        *    to the file system occured
        *    - BAD_PATH / INVALID_PATH if an error in the path \c
        *    link was detected
        *    - NOT_ENOUGH_SPACE / FS_NO_SPACE if the file system
        *    where \c link would reside has run out of space or out
        *    of file allocation ressources
        *    - UNKNOWN_ACCESS_ERROR / NOT_IMPLEMENTED if the current
        *    platform doesn't support symlinks in principal or if the
        *    file system where \c link would reside doesn't support
        *    symlinks.
        *    - UNKNOWN_ACCESS_ERROR / UNKNOWN_ERROR on other
        *    occasions.
        **/
        static bool createLink(const char *target, const char *link);

        //! \brief
        //! variant of createLink(const char*, const char*) using
        //! ipl::string objects
        static bool createLink(const ipl::string &target,
            const ipl::string &link)
        {
            // on win32 this call will always fail
            return createLink(target.c_str(), link.c_str());
        }

        //! \brief
        //! variant of createLink(const char*, const char*) using osal
        //! unicode string objects
        static bool createLink(
            const osal::UnicodeString &target,
            const osal::UnicodeString &link)
        {
            // on win32 this call will always fail
            return createLink(target.data(), link.data());
        }

        /*!
        * \brief
        *    Create a symlink named \c name in directory \c parent linking to \c link
        *
        * \details
        *    as createLink(const char*, const char*), but the request is limited to \c parent directory
        *
        * \param[in] target name of the destinatoin, where the link points to
        * \param[in] parent the parent directory of the link source
        * \param[in] link_name link target
        * \return true on error
        * \link2req{satisfies,req~FW_OSAL_TOCTOU_SAFE_LINK_CREATE_READ~1}
        */
        static bool createLinkAt(const char* target, const Directory &parent, const char *link_name);

    };

}  // end of namespace osal

#include "common/FileSys.inl"

#if defined IPL_OS_POSIX || defined IPL_OS_INTEGRITY
#    include "posix/FileSys.inl"
#elif defined IPL_OS_WINPC
#    include "win32/FileSys.inl"
#else
#    error "error undefined IPL_OS_ variant"
#endif

#endif
