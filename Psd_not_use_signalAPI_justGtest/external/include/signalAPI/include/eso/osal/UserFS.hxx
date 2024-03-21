/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_USERFS_HXX
#define OSAL_USERFS_HXX

#include <ipl_config.h>

#include <common/NonCopyable.hxx>

#include <osal/osal.hxx>
#include <osal/Time.hxx>
#include <osal/FileInfo.hxx>

#if defined IPL_OS_ANDROID || defined IPL_OS_LINUX
#    include "linux/UserFSDefs.hxx"
#elif defined IPL_OS_QNX
#    include "qnx/UserFSDefs.hxx"
#elif defined IPL_OS_WINPC || defined IPL_OS_INTEGRITY
#    include "win32/UserFSDefs.hxx"
#else
#    error "error undefined IPL_OS_ variant"
#endif


namespace osal
{

class IFileSystem;

/**
 * \brief
 *     Facility for providing a userspace file system

 *     This class allows you to create your own file system and mount
 *     it somewhere in the file system structure of the operating
 *     system.
 *
 *     You will get callbacks when other programs in the system attempt
 *     to access your file system and you can provide directory
 *     contents and file contents from arbitrary sources.
 *
 *     This implementation aims not at maximum throughput or efficiency
 *     but is rather thought as a convenient way of providing debugging
 *     and state information from the internals of your program to the
 *     outside world. Also setting up control and trigger files that
 *     allow to influence behaviour or start certain operations can
 *     be setup this way.
 *
 *     As it is hard to cover complex file system operations in an
 *     abstract way for all operating sytems (especially between the
 *     very different concepts of the WIN32 world and the POSIX world)
 *     this facility avoids any peculiarities like
 *     blocking/non-blocking behaviour, access rights, permissions and
 *     special files etc.
 *
 *     Essentially you get the ability to provide a file system
 *     hierarchy by means of directories and each directory can contain
 *     certain files that provide/take data from wherever you deem is
 *     suitable.
 * \note
 *     This feature might not be available on all platforms under all
 *     circumstances. If it is available the preprocessor define
 *     HAVE_OSAL_FS is set. Even if it isn't set you can still use this
 *     class but your file system will never appear in the system and
 *     you will never get any callbacks as a result.
 *
 *     - On IPL_OS_QNX this feature is always available
 *     - On IPL_OS_LINUX this feature is available if the FUSE package is
 *     available and if the fuse kernel module is loaded during runtime
 *     - On IPL_OS_WIN32 this feature is currently not available at all
 *     (coming soon)
 * \deprecated since 2020-01-31: This class is deprecated because
 *     implementation is a prototype only, it was not used in a project.
 **/
class OSAL_EXPORT
IPL_DEPRECATED_PRE ( "This class is deprecated because implementation is a prototype only, it was not used in a project." )
UserFS :
    public ipl::NonCopyable
{
public: // types

    // fwd. declarations for sub-types
    class Request;
    class Entity;
    class DirFiller;
    typedef osal::IFileSystem IFileSystem;
public: // member functions

    /**
     * \brief
     *     Construct a new userspace file system
     * \param[in] multithreaded
     *     Determines whether parallel requests are allowed. In this case
     *     your file system implementation needs to be thread-safe.
     *
     *     The multithreaded mode is currently not implemented. The file
     *     system will always be single threaded.
     **/
    UserFS(const bool multithreaded = false);

    /**
     * \brief
     *     Make your file system visible at the given path \c path, using
     *     \c cb to dispatch requests for files and directories

     *     You can't mount the file system on more than one path at the
     *     same time.
     * \param[in] path
     *     The file system path where to mount the file system.  File
     *     system operations on that path or below will cause calls to \c
     *     cb.
     * \param[in] cb
     *     The callback interface that will deal with incoming requests
     *     for the to be mounted file system
     * \return
     *     \c true on error, \c false on success
     **/
    bool mount(
        const char *path,
        IFileSystem *cb);

    /**
     * \brief
     *     Removes the file system from the system

     *     Further calls to the callback registered during mount won't
     *     occur. The file system will no longer be visible under the
     *     path is was previously mounted at.
     *
     *     Still existing associations with your file system will be
     *     severed. Clients will get appropriate error returns.
     * \return
     *     \c true on error, \c false on success
     **/
    bool unmount();

protected: // static functions

    //! init function called from osal init
    static bool init();

    // allow Osal init class to call init
    friend class Osal;

protected: // data

    UserFSHandle m_handle;

}
IPL_DEPRECATED_POST ( "This class is deprecated because implementation is a prototype only, it was not used in a project." )
; // end class

/**
 * \brief
 *     Callback interface for requests to file systems managed by the UserFS
 *     class

 *     You register an instance of this interface at UserFS::mount() to make
 *     it responsible for dealing with file system requests at your mount
 *     point.
 *
 *     You don't need to implement all of the callback function. The only
 *     mandatory function to implement is open(). All others returns default
 *     error codes. All write-accesses will be replied with READ_ONLY
 *     indicating to the user that write accesses are generally not possible
 *     on the file system. This allows you to implement a read-only file
 *     system that only provides data but allows no modifications from
 *     outside.
 *
 *     All path names that are passed to callback functions are relative to
 *     the root of your mounted file system. The initial '/' character is not
 *     present in those strings.
 * \deprecated since 2020-01-31: This class is deprecated because
 *     implementation is a prototype only, it was not used in a project.
 **/
class
IPL_DEPRECATED_PRE ( "This class is deprected because implementation is a prototype only, it was not used in a project." )
IFileSystem
{
public: // types

    /**
     * \brief
     *     Different callback result codes

     *     These are result codes that you can return from your callback
     *     methods that will be translated by the implementation into
     *     appropriate operating system errors on file system level.
     **/
    enum CallResult
    {
        //! permission denied
        NO_PERM = 0,
        //! write access was attempted on a read-only file system
        READ_ONLY,
        //! error handling data source / target
        IO_FAILURE,
        //! a given path was no valid entity in the file system
        NO_ENTITY,
        //! \brief
        //! an operation on a given entity could not be performed as
        //! it is busy
        BUSY_ENTITY,
        //! a given path is a directory where it should be a file
        IS_A_DIR,
        //! a given path is a file where it should be a directory
        IS_NO_DIR,
        //! the request was serviced / is accepted
        CALL_OKAY,
        //! the request cannot be serviced due to missing logic
        NOT_IMPLEMENTED,
        //! a given path already exists when it shouldn't
        FILE_EXISTS,
        //! an operation couldn't be performed due to lack of memory
        NO_MEMORY,
        //! removal of a directory can't happen as it isn't empty
        NOT_EMPTY,
        //! \brief
        //! arguments passed for an operation are invalid, logically
        //! wrong
        INVALID_ARG,
        //! number of types present in this enum
        CR_COUNT,
        // first and last values of the enum for e.g. iterating
        // over all types
        CALL_RESULT_LAST = CR_COUNT - 1,
        CALL_RESULT_FIRST = NO_PERM
    };

    /**
     * \brief
     *     Access mode for files at open() time

     *     This enum is used to differentiate different access
     *     requirements that are expressed at open() time.
     **/
    enum AccessMode
    {
        READ = 0,
        WRITE,
        READ_WRITE
    };

    //! a record describing a single directory entry
    struct DirEntry
    {
        //! the name of the directory entry
        const char *name;
        //! the length of name w/o null terminator
        size_t name_len;
        //! \brief
        //! a unique identifier for the entry across the FS, integer
        //! that is at least word sized, mostly 64 bit, however.
        EntityID id;
    };

public: // functions

    virtual ~IFileSystem() {}

    /**
     * \brief
     *     After an open has been accepted this call will come in
     *     to allocate data for the new client request

     *     ...
     **/
    virtual CallResult newRequest(
        UserFS::Entity *entity,
        UserFS::Request *&request)
    {
        // let the implementation to the right thing
        return NOT_IMPLEMENTED;
    }

    /**
     * \brief
     *     After a client is finished with dealing with a file system
     *     object this call will come in
     **/
    virtual CallResult requestFinished(UserFS::Request *request)
    {
        return NOT_IMPLEMENTED;
    }

    /**
     * \brief
     *     A client wants to open the given path \c path

     *     This call may come in to request to open the given path,
     *     or to create the given path. It is also possible to
     *     overwrite the given path depending on the parameters.
     *
     *     \c path_length gives the length of \c path in characters
     *     plus the null-terminator.
     *
     *     \c a gives the desired access mode for the file. If \c
     *     create is \c true then this also gives the desired
     *     permissions for the to be created file.
     *
     *     If \c create is \c true then the caller desires to
     *     create \c path. If \c truncate is \c true then the
     *     caller desires to empty \c path if it already exists.
     *
     *     If \c must_not_exist is \c true then if \c create is \c
     *     true the caller wants the call only to succeed if the
     *     file didn't exist previously.
     *
     *     If \c create is \c true then this call is coming in for
     *     a regular file. For links and directories createDir() or
     *     createLink() will be called instead.
     *
     *     If \c create is \c false then this call may be coming
     *     for other file types, also.
     *
     *     The \c type determines whether the requestor wants \c
     *     path to be a specific type to be opened/created. If the
     *     type does not match an appropriate error should be
     *     returned. If the type is ANY the type is unspecified by
     *     the caller.
     *
     *     You need to provide a UserFS::Entity object for each file
     *     system entity of your file system. This entity needs to
     *     be *unique* for each entity. If there was no
     *     UserFS::Entity existing previously then you need to
     *     allocate a new one and provide it in \c entity. If there
     *     was already an entity structure present then you need to
     *     provide this one to \c entity again.
     *
     *     The \c entity will be passed to follow-up callbacks like
     *     read or write. It contains a private void-pointer that
     *     can be used by your file system to store context data
     *     for the entity. This can be e.g. the path to the object,
     *     it's basename or some other internal structure that
     *     allows you to know what the read or write call is for.
     *
     *     You need to verify whether you want to accept this
     *     request. If so then return CALL_OKAY and provide the \c
     *     entity for this path. If you reject the request return
     *     an appropriate CallResult and don't set \c entity.
     **/
    virtual CallResult open(
        UserFS::Entity *& entity,
        const char *path,
        size_t path_length,
        AccessMode a,
        FileInfo::EntryType type,
        bool create,
        bool truncate,
        bool must_not_exist) = 0;

    /**
     * \brief
     *     Handle a request to return contents of the directory
     *     associated with \c request
     **/
    virtual CallResult readDir(
        UserFS::Request *request,
        UserFS::DirFiller &filler,
        size_t item_offset)
    {
        return NOT_IMPLEMENTED;
    }

    /**
     * \brief
     *     Handle a request to return file contents of the file
     *     assocaiated with \c request
     * \param[in] buf
     *     The buffer where the read data should go to
     * \param[in] bufsize
     *     The number of bytes that can at max be placed into \c
     *     buf
     * \param[in] offset
     *     The offset into the file from where the caller wants to
     *     read data
     * \param[out] provided
     *     The number of bytes that have actually been put into \c
     *     buf
     **/
    virtual CallResult readData(
        UserFS::Request *request,
        char *buf,
        size_t bufsize,
        size_t offset,
        size_t &provided)
    {
        return NOT_IMPLEMENTED;
    }

    /**
     * \brief
     *     Handle a request to put new data into the file associated with
     *     \c request
     **/
    virtual CallResult writeData(
        UserFS::Request *request,
        const char *buf,
        size_t bufsize,
        size_t offset,
        size_t &written)
    {
        return READ_ONLY;
    }

    /**
     * \brief
     *     Handle a request to change the size of the file associated
     *     with \c request
     **/
    virtual CallResult changeSize(
        UserFS::Request *request,
        const size_t size)
    {
        return READ_ONLY;
    }

    /**
     * \brief
     *     Handle a request to change the access rights of the file
     *     associated with \c request
     **/
    virtual CallResult changeAccess(
        UserFS::Request *request,
        const FileAccess &a)
    {
        return READ_ONLY;
    }

    /**
     * \brief
     *     Handle a request to change the modification time of the file
     *     associated with \c request
     **/
    virtual CallResult changeModTime(
        UserFS::Request *request,
        const osal::FileTime &t)
    {
        return READ_ONLY;
    }

    /**
     * \brief
     *     Handle a request to create a directory in your file system
     *     under the name \c p
     **/
    virtual CallResult createDir(
        const char *p,
        const FileAccess &a)
    {
        return READ_ONLY;
    }

    /**
     * \brief
     *     Handle a request to remove the file found at location \c p

     *     Beware that the Entity object associated with \c p must not be
     *     deleted until the last clients of that entity release it. Only
     *     the path may be removed from the file system, but the entity
     *     needs to stay valid until the last Request objects operating
     *     on it are finished.
     **/
    virtual CallResult remove(
        const char *p,
        const bool dir_requested)
    {
        return READ_ONLY;
    }

    /**
     * \brief
     *     Handle a request to rename the file found at location \c from
     *     to location and name \c to
     **/
    virtual CallResult rename(
        const char *from,
        const char *to)
    {
        return READ_ONLY;
    }

    /**
     * \brief
     *     Handle a request to read the content of the symlink found at
     *     location \c link
     **/
    virtual CallResult readlink(
        const char *link,
        char *buf,
        const size_t bufsize,
        size_t &written)
    {
        return NOT_IMPLEMENTED;
    }

    /**
     * \brief
     *     Handle a request to create a new symlink at location \c from
     *     containg content \c to
     **/
    virtual CallResult createLink(
        const char *from,
        const char *to)
    {
        return READ_ONLY;
    }

}
IPL_DEPRECATED_POST ( "This class is deprecated because implementation is a prototype only, it was not used in a project." )
;

/**
 * \brief
 *     A helper class that eases the creation directory listings

 *     In IFileSystem::readDir() an instance of this type is passed as a
 *     parameter. It is used for easily filling the low level data structures
 *     with the necessary directory information.
 *
 *     It especially cares for the space available on the lower levels to
 *     hold directory entry information.
 *
 *     The callee in IFileSystem::readDir() simply feeds one directory entry
 *     at a time into the DirFiller instance and the fill() function will
 *     return the amount of space still available for the next directory
 *     entry.
 * \deprecated since 2020-01-31: This class is deprecated because
 *     implementation is a prototype only, it was not used in a project.
 **/
class
IPL_DEPRECATED_PRE ( "This class is deprecated because implementation is a prototype only, it was not used in a project." )
UserFS::DirFiller
{
public:
    DirFiller(const DirFillerHandle &handle) :
        m_handle(handle)
    {}

    /**
     * \brief
     *     Adds the given directory entry to the directory listing
     * \return
     *     Returns left()
     **/
    size_t fill(const IFileSystem::DirEntry &e);

    //! returns the left space in characters for the next directory entry,
    //! not counting the null terminator
    inline size_t left() const;

    //! space already occupied with payload data
    inline size_t used() const;

    //! returns the current offset
    inline size_t offset() const;

private:
    // OS dependent data
    DirFillerHandle m_handle;
}
IPL_DEPRECATED_POST ( "This class is deprecated because implementation is a prototype only, it was not used in a project." )
;

/**
 * \brief
 *     Represents an ongoing request in the file system i.e. a single request
 *     from a client to a specific UserFS::Entity

 *     A request can be seen as the representation of a clients file
 *     descriptor that is open for a file system object in your file system.
 * \deprecated since 2020-01-31: This class is deprecated because
 *     implementation is a prototype only, it was not used in a project.
 **/
class
IPL_DEPRECATED_PRE ( "This class is deprecated because implementation is a prototype only, it was not used in a project." )
UserFS::Request :
    public UserFSRequestHandle
{
public: // functions

    /**
     * \brief
     *     Creates a new request for the given file system entity

     *     The \c priv parameter is a datum that will always be available
     *     at the request object to store application specific data.
     **/
    Request(UserFS::Entity *entity, void *priv) :
        m_entity(entity),
        m_priv(priv)
    { }

    /**
     * \brief
     *     Returns the private data that has been associated with the
     *     request
     **/
    void* getPriv()
    {
        return m_priv;
    }

    /**
     * \brief
     *     Returns the entity this request relates to
     **/
    UserFS::Entity* getEntity()
    {
        return m_entity;
    }

protected: // data

    // the entity that this request is dealing with
    UserFS::Entity *m_entity;
    // the private data
    void *m_priv;
}
IPL_DEPRECATED_POST ( "This class is deprecated because implementation is a prototype only, it was not used in a project." )
;

/**
 * \brief
 *     Data structure that is kept per file system entity

 *     An Entity denotes a single file system entry in your application's
 *     file system. The entity also defines a number of default properties of
 *     file system entities like the visible size, access rights and so on.
 * \deprecated since 2020-01-31: This class is deprecated because
 *     implementation is a prototype only, it was not used in a project.
 **/
class
IPL_DEPRECATED_PRE ( "This class is deprecated because implementation is a prototype only, it was not used in a project." )
UserFS::Entity :
    public UserFSEntityHandle
{
public:
    Entity(void *priv,
        const FileInfo::EntryType type,
        const FileAccess access,
        const size_t size) :
            m_priv(priv)
    {
        setType(type);
        setAccess(access);
        setSize(size);
        setEntityID( (EntityID)(this) );

        if( type == osal::FileInfo::DIRECTORY )
            setLinkCount(2);
        else
            setLinkCount(1);

        osal::TimeT now;
        osal::Time::getTimestamp(now);
        this->setModTime( osal::FileInfo::getFileTime(now) );

#ifdef HAVE_OSAL_USERFS
#        ifdef IPL_OS_LINUX
        this->st_uid = ::getuid();
        this->st_gid = ::getgid();
#        elif defined IPL_OS_QNX
        this->m_attr.uid = ::getuid();
        this->m_attr.gid = ::getgid();
#        endif
#endif
    }

    void* getPriv()
    {
        return m_priv;
    }

    /**
     * \brief
     *     Returns the number of active requests for this entity
     **/
    inline size_t useCount() const;

    inline void setType(const FileInfo::EntryType type);

    inline FileInfo::EntryType getType() const;

    inline void setAccess(const FileAccess &access);

    inline FileAccess getAccess() const;

    inline void setSize(const size_t size);

    inline size_t getSize() const;

    inline EntityID getEntityID() const;

    inline void setEntityID(const EntityID &id);

    inline size_t getLinkCount() const;

    inline void setLinkCount(const size_t count);

    inline osal::FileTime getModTime() const;

    inline void setModTime(const osal::FileTime &);

protected:
    void *m_priv;
}
IPL_DEPRECATED_POST ( "This class is deprecated because implementation is a prototype only, it was not used in a project." )
;

} // end osal

#if defined IPL_OS_ANDROID || defined IPL_OS_LINUX
#    include "linux/UserFS.inl"
#elif defined IPL_OS_QNX
#    include "qnx/UserFS.inl"
#elif defined IPL_OS_WINPC || defined IPL_OS_INTEGRITY
#    include "win32/UserFS.inl"
#else
#    error "error undefined IPL_OS_ variant"
#endif

#endif // OSAL_USERFS_HXX
