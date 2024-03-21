/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

/*****************************************************************************/
#ifndef OSAL_FILEINFO_HXX
#define OSAL_FILEINFO_HXX
/*****************************************************************************/

#include <ipl_config.h>

#include <string.h> // memcpy

#include <common/Macros.hxx>

#include <osal/osal_dso.h>
#include <osal/osal.hxx>
#include <osal/FileAccess.hxx>
#include <osal/userinfo.hxx>
#include <osal/UnicodeString.hxx>

#if defined IPL_OS_POSIX || defined IPL_OS_INTEGRITY
    #include "posix/FileInfoDefs.hxx"
#elif defined IPL_OS_WINPC
    #include "win32/FileInfoDefs.hxx"
#else
    #error "error undefined IPL_OS_ variant"
#endif

/*****************************************************************************/

namespace osal {

/*****************************************************************************/

    class Directory;  /* forward declaration is sufficient, no include necessary */

    /*!
        \brief Information about file system objects

        This class queries metadata from file system objects.

        It is notable that the metadata is retrieved at construction
        time from the system.  Any member function calls operate on that
        initially retrieved data. To get updated metadata information of
        the file system object the object needs to be constructed anew.

        Alternatively an update() method or something similar could have
        been provided that allows to update the information stored in an
        already constructed object. This would have required to remember
        the path of the file system object (by copying it), however, to
        be able to query the system again. This could cost a significant
        amount of time in case of processing a large number of file
        system objects. Thus this variant is not provided.
    */
    class OSAL_EXPORT FileInfo {

    public:

        //! \brief \b Deprecated! Use osal::FileAccess instead!
        typedef osal::FileAccess FileAccess;

        //! \brief Kind of file system object
        enum EntryType
        {
            INVALID_ENTRY_TYPE=0,  //!< \brief Error
            REGULAR,               //!< \brief normal file containing data
            DIRECTORY,             //!< \brief a directory
            LINK,                  //!< \brief a symbolic link to another file system object
            SPECIAL,               //!< \brief special file like device file, pipe, socket etc.
            ENTRY_TYPE_END         //!< \brief No file type, just the maximum number of the enum
        };

        /*!
            \brief Construct from platform-dependent FileInfoHandle

            Takes over the information provided from \a fih.
            If \a fih is non-NULL then the object will always be valid.
            If \a fih is NULL then the object will always be invalid,
            no error raised (this way the constructor can also be
            used as default constructor for empty objects).
        */
        FileInfo(const FileInfoHandle *fih=NULL): m_valid( fih != NULL ) {
            if(fih)
                ::memcpy(&m_handle, fih, sizeof(FileInfoHandle));
            else
                // to have defined data in the invalid case
                ::memset(&m_handle, 0, sizeof(FileInfoHandle));
        }

        /*!
            \brief Retrieve information for \a path

            If \a resolve_links is \c true then in case \a path is of type
            LINK the properties of the file system object the link points to
            are queried.
            If \a resolve_links is \c false then the properties of
            the link itself are queried.

            \note If you intend to open the file \a path then it
            might be cheaper to first construct an osal::BinFile[R,W,RW] for it
            and call osal::BinFileBase::getFileInfo() to obtain an FileInfo.
            This way \a path needs only to be looked up once.

            \errorindicator via isValid()

            \errors
            FileAccessError with attached SysError with IDs:
            - NO_ACCESS / PERMISSION_DENIED if part of \c path is
            inaccessible
            to the caller (this does not necessarily mean that \c
            path exists. it only means a part of it it is
            inaccessible).
            - BAD_PATH / INVALID_PATH if the given \c path is in
            principle erroneous (e.g. too long than any valid path)
            - DEVICE_FAILURE / IO_FAILURE if reading from filesystem
            failed
            - UNKNOWN_ACCESS_ERROR attached with
                * OUT_OF_MEMORY
                * INTEGRITY_ERROR on addressing issues
                * UNKNOWN_ERROR on other errors.
        */
        FileInfo(const char *path, bool resolve_links=true);

        //! \overload
        FileInfo(const ipl::string &path, bool resolve_links=true);
        //! \overload
        FileInfo(const UnicodeString &path, bool resolve_links=true);

        /*!
            \brief
            Retrieve information for the object \c name in directory \c parent

            \param[in] parent the parent directory
            \param[in] name name of the object to query
            \param[in] resolve_links true if a symlink shall be followed
            \return true on error
            \link2req{satisfies,req~FW_OSAL_TOCTOU_SAFE_DIR_SCAN~1}
        */
        FileInfo(const Directory &parent, const char* name, bool resolve_links=false);

        inline ~FileInfo();

        //! \brief Whether construction succeeded
        bool isValid() const { return m_valid; }

        /*!
            \brief Type of the file system object or INVALID_ENTRY_TYPE if the
            object is not valid

            \errorindicator via return of INVALID_ENTRY_TYPE. No error is raised.
        */
        inline EntryType getType() const;

        /*!
            \brief Size of the File in Bytes

            For file system objects of type REGULAR this gives the
            visible size of the file (i.e. data contained). The
            actual disk capacity occupied by files is often bigger.
            The latter information can be acquired via getBlocks()
            and getBlockSize().

            In some cases it is also possible that the returned size
            is greater than the actually used disk capacity. This
            can happen in case the file was setup to contain "holes"
            that aren't filled with data.

            For objects of type LINK that haven't been resolved
            during construction time this function returns the
            length of the pathname it points to, not including a
            null-byte character.

            Directory file system objects can also have sizes that
            depend on the amount of file system objects contained.

            \errors If the object is invalid zero is returned. No error is raised.
        */
        inline uint64_t getSize() const;

        /*!
            \brief Number of blocks the file occupies on the file system

            Determines the actual space occupied by the file system
            object on the filesystem it resides on. The returned
            datum is of an operating system and implementation
            specific unit.

            To determine the unit use the getBlockSize() function.

            This datum is valid for any kind of file system object.

            \note The information about the disk usage is a pretty
            low-level detail of the file system. Under some
            circumstances you may get slightly wrong results.

            One example is the presence of hard-links on UNIX file
            systems. Hard links are different names for the same
            file system entity. In this case two or more file system
            paths refer to the same data and thus accumulating their
            block size results in a larger disk usage than actually
            present. OSAL doesn't currently allow to efficiently
            detect the presence of such hard links. Two files refer
            to the same file system entitity if getFileID() returns
            the same ID.

            Another example is on WINPC systems using NTFS file
            systems. Here it seems to be the case that files can
            share file system blocks. Thus when you compare the
            accumulated block sizes you compute with getBlocks() can
            be larger than the sizes that are reported by the
            Windows Explorer.

            \errors If the object is invalid zero is returned. No error is raised.

        */
        inline uint64_t getBlocks() const;

        /*!
            \brief Size of a Block as Returned by getBlocks()

            Gives size of a block in bytes. If multiplied by the value returned
            from getBlocks() you will retrieve the actual number of bytes
            occupied by a file system object on the file system.

            Beware that this block size has not necessarily anything to do with
            actual block sizes used by the file system.
            It is merely a unit for calculation of disk space usage.

            Usually the block size doesn't differ between different
            files on the same file system.

            For efficient calculation of actual space occupied by a file system
            object instead of multiplying the values returned by getBlocks()
            and this function you may determine the power-of-2 that the
            block size represents (the block size is a power-of-2).
            Then you can shift the value returned by getBlocks() by that amount
            to determine the actual file system object size.

            \warning This information may become inaccurate on some special
            filesystems like e.g.  NFS mounts on POSIX systems.

            \errors If the object is invalid zero is returned. No error is raised.
        */
        inline uint_fast32_t getBlockSize() const;

        /*!
            \brief Preferred block size for I/O to this file

            When doing I/O operations on this file system object it is best to
            perform I/O in chunks of this size. This is a per-object value that
            may differ between filesystems or even between different files on
            the same file system.

            Note that this number only makes sense in the context of a
            file system object that you can actually perform I/O on.

            \errors If the object is invalid zero is returned. No error is raised.
        */
        inline uint_fast32_t IOBlockSize() const;

        /*!
            \brief File system identifier for this file system object

            Using this identifier you can determine when file system boundaries
            are crossed or whether two files belong to the same file system.

            This way you can e.g. restrict operations onto one file system.

            The only operations permitted for the returned FileSysID
            type are comparison for equality/inequality.

            \errors If the object is invalid INVALID_FILESYSID is returned. No error is raised.
        */
        inline FileSysID getFsId() const;

        /*!
            \brief Unique Identifier for the given file system object

            The returned value uniquely identifies a file system object on the
            local computer system independent of the file system it resides on.

            This is the best way to determine whether two file system paths
            refer to the same file system objects. Also it can be used as a
            hash-value for a file system object (but not its content, of course).

            \note On UNIX file systems that can contain hard links it can
            happen that two different paths return the same FileID
            in case they refer to the same file system entity.

            \errors If the object is invalid INVALID_FILEID is returned. No error is raised.
        */
        inline FileID getFileID() const;

        /*!
            \brief Last time of modification

            The modification time of a file system object is updated every time
            its content is changed by writing, overwriting, truncating etc.
            It is not updated by changes to the object's properties like
            access rights and alike (on POSIX this means any changes to the
            file's inode won't change the modification time).

            The actual content of the returned timestamp differs between
            operating systems. The only supported operations are comparisons of
            timestamps for equality, greater(-equal) or less(-equal).
            Storing the integer is also supported. But note that different
            platforms may have different sizes for this integer. Also note that
            the time units and time bases differ between platforms.

            In case of directories file system objects the modification time
            may also change if any contained file system objects are modified.

            \errors If the object is invalid, zero is returned. No error is raised.

            \note The modification time is the only time-related data available
            from file system objects across different operating systems.

            On POSIX-compatible systems there is no creation time record for
            example. In principle there would exist an access time record that
            gives the last time of read access.  This record is often not kept
            by the system, however, as it is expensive to update this time stamp
            time and again.

            On WIN32 there would be creation and access time records present
            in the API but there also exist complex rules depending on the
            underlying file system that determine whether and when these records
            are updated (and usually they're not).

            \note To transform the OS dependent FileTime timestamp into a
            well-known UNIX timestamp use FileInfo::convertFileTime(const FileTime&)

            \warning In embedded environments it is often the case that there
            is no RTC present in the system and the time is reset after each
            reboot. In these cases comparisons of timestamps taken between
            boot cycles won't work correctly without precaution.
        */
        inline FileTime getModTime() const;

        /*!
            \brief Get access rights of the file system object

            On Win32 always read/write/execute permissions will be returned
            regardless of what actual permissions are due to complexities and
            performance problems in the area of access control lists on WIN32.
        */
        FileAccess getAccess() const;

        //! \brief Retrieve owner of the file
        User getOwner() const;
        //! \brief Retrieve group of the file
        Group getGroup() const;

        /*!
            \brief Set the modification time of the object at \a path to \a time

            If access times are recorded by the system (see getModTime()) for
            \a path then the access time will also be set to \a time.
            If \a time is zero then the modification time of \a path
            will be set to the current system time.

            To set the modification time you usually need write permission
            for the file system object denoted by \a path.
            Also the underlying filesystem needs to be writeable.

            The given \a time might be rounded by the system to the closest
            representable time value. This resolution often is in seconds.

            \note If \a path denotes a LINK object then always the modification
            time of the target of the link will be set.
            There is currently no way to modify the modification time of LINKs
            themselves (due to OS restrictions).

            \note To convert well-known osal::TimeT unix-timestamps to
            FileTime timestamps use FileInfo::getFiletime(const osal::TimeT&).

            \param[in] time An OS dependent file timestamp

            \return true on error, false otherwise

            \errorindicator via return code

            \errors osal::SysError with IDs:
            - INVALID_PATH if \c path is an invalid symlink, too
            long, not existent
            - PERMISSION_DENIED if part of \c path is inaccessible,
            the denoted object is inaccessible or the filesystem
            doesn't allow writes
            - UNKNOWN_ERROR on other occasions
        */
        static bool setModTime(const ipl::string &path, FileTime time=0);

        //! \overload
        static bool setModTime(const osal::UnicodeString &path, FileTime time=0);

        /*!
            \brief
            Set the modification time of the object \c name in directory \c parent

            \details
            as setModTime(const UnicodeString&, FileTime), but the request is limited to \c parent directory

            \param[in] parent the parent directory
            \param[in] name name of the object to modify
            \param[in] time An OS dependent file timestamp
            \param[in] resolve_links true if a symlink shall be followed,
                                     false if the mod time of the link shall be updated
            \return true on error
            \link2req{satisfies,req~FW_OSAL_TOCTOU_SAFE_FILE_CHANGE_META~1}
        */
        static bool setModTimeAt(const Directory &parent, const char* name, FileTime time=0,
                                 bool resolve_links=false);

        /*!
            \brief Compare whether two FileInfo refer to the same file
            (as determined by getFileID())

            Two invalid objects compare equal.
        */
        bool operator == (const osal::FileInfo &other) const {
            return other.getFileID()==this->getFileID();
        }
        /*!
            \brief Compare whether two FileInfo refer to different files
            (as determined by getFileID())

            Two invalid objects compare equal.
        */
        bool operator != (const osal::FileInfo &other) const {
            return !operator == (other);
        }

        //! \brief Order by getFileID()
        bool operator < (const osal::FileInfo &other) const {
            return other.getFileID()<this->getFileID();
        }
        //! \brief Order by getFileID()
        bool operator <= (const osal::FileInfo &other) const {
            return operator < (other) || operator == (other);
        }

        //! \brief Order by getFileID()
        bool operator > (const osal::FileInfo &other) const {
            return !operator <= (other);
        }
        //! \brief Order by getFileID()
        bool operator >= (const osal::FileInfo &other) const {
            return !operator < (other);
        }

        /*!
            \brief Convert \a ft into OS independent format

            The returned timestamp has the same properties as described at
            osal::getTimestamp().
        */
        static inline osal::TimeT convertFileTime(const osal::FileTime &ft);

        /*!
            \brief Convert \a t into OS dependent timestamp

            The parameter \c t is expected to have the same properties as
            described at osal::getTimestamp().
        */
        static inline osal::FileTime getFileTime(const osal::TimeT &t);

    protected:
        //! \brief Common construction code for ASCII and unicode paths
        void init(const native_utf *, const bool);

    private:
        bool m_valid;

        FileInfoHandle m_handle;
    };

/*****************************************************************************/

}  // end of namespace osal

/*****************************************************************************/

#if defined IPL_OS_POSIX || defined IPL_OS_INTEGRITY
    #include "posix/FileInfo.inl"
#elif defined IPL_OS_WINPC
    #include "win32/FileInfo.inl"
#else
    #error "error undefined IPL_OS_ variant"
#endif

/*****************************************************************************/
#endif
