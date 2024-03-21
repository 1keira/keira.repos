/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_DIRECTORY_HXX
#define OSAL_DIRECTORY_HXX

#include <ipl_config.h>

#if defined IPL_OS_POSIX || defined IPL_OS_INTEGRITY
#    include "posix/DirectoryDefs.hxx"
#elif defined IPL_OS_WINPC
#    include "win32/DirectoryDefs.hxx"
// #elif defined IPL_OS_INTEGRITY
// #    include "integrity/DirectoryDefs.hxx"
#else
#    error "error undefined IPL_OS_ variant"
#endif

#include <osal/osal_dso.h>
#include <osal/RefCounted.hxx>
#include <osal/UnicodeString.hxx>

#include <osal/FileInfo.hxx>

namespace osal {

    /**
    * \brief
    *    Access to Directory Content in the File System.

    *    This class allows you to access a directory in the file system
    *    and browse through its content.
    *
    *    There are two different patterns to directory access.  One is to
    *    simply list the content of a single directory by means of
    *    getting the names of the contained files.  This is good if you
    *    don't need recursive directory tree scanning and only need the
    *    names contained and not the additional osal::FileInfo associated
    *    with the content.
    *
    *    If you need the osal::FileInfo for much or all of the directory
    *    content or if you require recursive operation then you're better
    *    off using the osal::TreeWalker algorithm which efficiently
    *    delivers the osal::FileInfo for each directory entry.  This
    *    algorithm also allows to recursively search a complete directory
    *    tree.
    *
    *    Alternatively you can pass \c true for the \c need_file_info
    *    parameter of the Directory constructor in which case you can
    *    efficiently access FileInfo of contained files via curInfo().
    *
    *    osal::Directory is a reference counted class such that flat
    *    copies become possible.  Only when the last copy of an
    *    osal::Directory instance is destroyed the underlying ressources
    *    are actually freed. This thus not imply thread-safety, however.
    *    It is recommended to only use the most recent copy of an
    *    osal::Directory object.
    * \note
    *    In case you perform write-access to a directory object in
    *    parallel with other threads or processes on the system without
    *    proper synchronization then the numbers of entries in a
    *    directory, the type and/or existence of entries as well as the
    *    existence of the directory itself may change at any time.
    **/
    class OSAL_EXPORT Directory :
        public osal::RefCounted
    {
    public: // functions
        /**
        * \brief
        *    Construct an Empty Directory

        *    No directory will be opened. isValid() will always
        *    return false. atEnd() will always return true. No error
        *    is raised.
        * \errors
        *    none
        **/
        Directory() :
            m_is_valid(false),
            m_at_end(true)
        { }

        /**
        * \brief
        *    Open the given \c path to a directory file system object
        *    for browsing its content.

        *    On successful construction the object will be bound to
        *    this directory. The first entry in the directory will be
        *    selected (currentEntry() will return its name). A
        *    Directory will never be empty as at least the directory
        *    itself (".") and the parent directory ("..") will be
        *    contained.
        *
        *    Note: This condition does not hold true on some QNX file
        *    systems (and probably some other, rare file systems). In
        *    such cases the resulting Directory object will be valid
        *    but the current entry is invalid, atEnd() returns \c
        *    true. Thus applications should check atEnd() before
        *    trying to access the currentEntry().
        *
        *    Note that usually no special ordering of the directory
        *    content is present (i.e. no alphabetical ordering of
        *    entries).
        *
        *    If \c need_file_info is set to \c true then you will be
        *    able to efficiently acquire FileInfo objects for file
        *    system objects contained in the opened directory via
        *    curInfo(). If this is not set to \c true then calls to
        *    curInfo() will be slower, if not terribly slower (esp.
        *    on QNX sd-cards).
        *
        *    This is especially true if you intend to acquire
        *    FileInfo for all or most of the directory entries.
        * \errorindicator
        *    via isValid()
        * \errors
        *    FileAccessError attached with SysError with IDs:
        *
        *    - BAD_PATH / INVALID_PATH if the given \c path is not
        *    valid
        *    - NO_DIR / NO_DIRECTORY if the given file system object
        *    is not of type DIRECTORY.
        *    - NO_ACCESS / PERMISSION_DENIED if \c path or a
        *    component of it is not accessible
        *    - TOO_MANY_OPEN_FILES / SYSTEM_RESSOURCES_EXHAUSTED if
        *    the system can't open any more directories
        *    - UNKNOWN_ACCESS_ERROR / UNKNOWN_ERROR on other errors
        *
        *    Any errors listed in next() may also occur.
        **/
        Directory(const ipl::string &path,
            const bool need_file_info = false);

        //! \brief
        //! same as Directory(const ipl::string&, const bool) but taking
        //! a UnicodeString as parameter
        //! \see
        //! Directory(const ipl::string&, const bool)
        Directory(const UnicodeString &path,
            const bool need_file_info = false);

        //! \brief opens a sub-directory to a directory without following symlinks.
        //!
        //! This constructor avoids the problem
        //! of following symlinks to folders (introduced by e.g. an untrusted SD card)
        //! that are accessible but not intended to be accessed on the following
        //! platforms: POSIX>=200809
        //!
        //! \param[in] parent the parent directory
        //! \param[in] name the simple name of the sub-directory to open, no path separators are allowed.
        //! \param[in] resolve_links
        //!    Indicates if a symbolic link shall be followed.
        //!    An invalid directory is returned if the current entry
        //!    is a link and \c resolve_links is \c false .
        //! \param[in] need_file_info see need_file_info of other constructor.
        //! \see Directory(const ipl::string&,const bool)
        //!
        //! \return the constructed object
        //! is invalid in case POSIX_VERSION < 200809,
        //! or is invalid in case the function is not yet implemented for the current OS
        //! or is invalid in case the parent and name components do not denote a readable directory
        //! or a valid directory.
        //! \see isValid()
        //! \link2req{satisfies,req~FW_OSAL_TOCTOU_SAFE_DIR_SCAN~1}
        Directory(const Directory &parent, const ipl::string &name, const bool resolve_links,
            const bool need_file_info = false );

        /*
        * \brief
        *    Close the directory, discard any fetched data
        */
        ~Directory()
        {
            this->decrement();
        }

        //! \brief
        //!    returns true if construction was successful and the
        //!    object contains valid data, false otherwise
        bool isValid() const
        { return m_is_valid; }

        //! Returns \c true If the last directory entry has been reached
        bool atEnd() const
        { return m_at_end; }

        /**
        * \brief
        *    Returns the name of the directory entry currently
        *    positioned to.
        * \note
        *    The returned string is a pointer to internal memory of
        *    the Directory object.
        *
        *    It will only be valid until next() is called again.
        *
        *    If isValid() returns \c false or atEnd() returns \c true
        *    then the returned pointer will be invalid.
        * \return
        *    A string identifying the currently selected directory
        *    entry.
        * \errors
        *    none
        **/
        inline const char* curEntry() const;

        /**
        * \brief
        *     Returns the current directory entry in unicode encoding
        * \see
        *     curEntry(void) const
        * \note
        *     Even though the string is returned as an out parameter
        *     into \c ucs the string data is only a shared copy of
        *     internal data. Thus it is only valid until next() is
        *     called again. This is due to performance reasons.
        *
        *     If you need a deep copy then please create a copy of \c
        *     ucs using the osal::UnicodeString::MAKE_COPY StoreMode
        *     at construction time. Or copy the data into some other
        *     string object for further processing.
        **/
        inline void curEntry(osal::UnicodeString &ucs) const;

        /**
        * \brief
        *    Returns a FileInfo object for the currently selected
        *    entry
        *
        *    Using this member function instead of manually
        *    constructing a FileInfo object for curEntry() will
        *    result in better performance if \c need_file_info was
        *    set to \c true during construction time.
        * \param[in] resolve_links
        *    Similar to the parameter passed to the
        *    osal::FileInfo(const char*, const bool) constructor.
        * \errorindicator
        *    via FileInfo.isValid() of returned object
        * \errors
        *    The errors specified at osal::FileInfo(const char*,
        *    const bool) are valid here, too.
        **/
        osal::FileInfo curInfo(
            const bool resolve_links = true) const;

        /**
        * \brief
        *    Returns a Directory object for the currently selected
        *    entry
        *
        *    If the currently selected directory entry is of a
        *    directory type then this member functions allows you to
        *    efficiently open that directory by means of a new
        *    osal::Directory object.
        *
        *    This can be more efficient on some systems than
        *    constructing a new osal::Directory from curEntry()
        *    manually.
        * \errorindicator
        *    via isValid() of returned object
        * \errors
        *    The errors specified at osal::Directory are valid here,
        *    too.
        **/
        osal::Directory curDir(
            const bool need_file_info = false) const;

        /**
        * \brief
        *    Returns a Directory object for the currently selected
        *    entry
        *
        *    If the currently selected directory entry is of a
        *    directory type then this member functions allows you to
        *    efficiently open that directory by means of a new
        *    osal::Directory object.
        *
        *    This can be more efficient on some systems than
        *    constructing a new osal::Directory from curEntry()
        *    manually.
        *
        *    This function does not re-evaluate the directory path
        *    and thereby protects from opening an unintended directory on the following
        *    platforms: POSIX>=200809
        *
        *    A mnemonic for the parameter order is the sequence of tasks:
        *    first check if to follow links, then define if to pre-fetch file info.
        * \param[in] resolve_links
        *    Indicates if a symbolic link shall be followed.
        *    An invalid directory is returned if the current entry
        *    is a link and \c resolve_links is \c false .
        * \param[in] need_file_info see \c need_file_info of constructor.
        * \see Directory(const ipl::string&,const bool)
        * \errorindicator
        *    via isValid() of returned object
        * \errors
        *    The errors specified at osal::Directory are valid here,
        *    too.
        * \link2req{satisfies,req~FW_OSAL_TOCTOU_SAFE_DIR_SCAN~1}
        **/
        osal::Directory curDir(
            const bool resolve_links,
            const bool need_file_info ) const;

        /**
        * \brief
        *    Position to the Next Directory Entry

        *    If the last directory entry has been reached a value > 0
        *    is returned and nothing is done. Otherwise the next
        *    directory entry will be selected as the current
        *    directory entry.
        *
        *    If the last directory entry has been reached or an error
        *    occured the atEnd() member function will return true
        *    from this time forward.
        *
        *    This function is not thread safe i.e. using multiple
        *    threads to access a single osal::Directory will fail
        *    horribly.
        * \note
        *    You cannot select previous directory entries again. You
        *    need to create a new Dir object to rescan the directory
        *    contents.
        * \return
        *    zero if the next directory entry could be selected, > 0
        *    if the last directory entry has been reached or the
        *    directory is empty. < 0 if an error occured.
        * \errorindicator
        *    on < 0 return an error occured.
        * \errors
        *    SysError with IDs:
        *
        *    - INTEGRITY_ERROR on severe system errors
        *    - UNKNOWN_ERROR on other errors
        **/
        int_fast8_t next();
    protected: // functions
        //! actually destruction after refcount hits zero
        virtual void destroy();

        /**
        * \brief
        *    Common constructor code
        **/
        void init();

        /**
        * \brief
        *    Special constructor for internal use
        **/
        inline Directory(const DirectoryHandle *dh);
    protected: // members
        bool m_is_valid;
        bool m_at_end;
    private: // members
        DirectoryHandle m_handle;

        friend class ::osal::BinFileBase;
        friend class ::osal::FileSys;
        friend class ::osal::FileInfo;
    };

}  // end of namespace osal

#if defined IPL_OS_POSIX || defined IPL_OS_INTEGRITY
#    include "posix/Directory.inl"
#elif defined IPL_OS_WINPC
#    include "win32/Directory.inl"
// #elif defined IPL_OS_INTEGRITY
// #    include "integrity/Directory.inl"
#else
#    error "error undefined IPL_OS_ variant"
#endif

#endif
