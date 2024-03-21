/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_LINUX_OSALFSDEFS_HXX
#define OSAL_LINUX_OSALFSDEFS_HXX

#include <dirent.h>

#ifdef HAVE_OSAL_USERFS
#include <fuse.h>

#include <common/types/string.hxx>
#include <osal/Thread.hxx>

// fwd. declaration from dirent.h
struct dirent;

namespace osal
{

// fwd. declaration
class IFileSystem;

// we directly inherit from the struct stat here
struct UserFSEntityHandle :
    public stat
{
    UserFSEntityHandle() :
        m_use_count()
    {
        ::memset( (char*)this + sizeof(intptr_t),
            '\0', sizeof(struct stat));
    }

    size_t m_use_count;
};

/*
 * we need to additionally store the entity and callback pointers for
 *
 * 1) being able to provide the entity even if we only have the request
 * (e.g. in ocb_close)
 * 2) being able to actually dispatch Session callback to the UserFS
 * client
 */
struct OSAL_EXPORT UserFSRequestHandle
{
    UserFSRequestHandle()
    { /* NOP */ }

    void setCallback(IFileSystem *cb)
    {
        callback = cb;
    }

protected: // io functions

protected:
    IFileSystem *callback;
};

class UserFSHandle
{
public:
    UserFSHandle(const bool multithreaded) :
        m_user_cb(),
        m_event_thread(),
        m_fuse_channel(),
        m_fuse_handle()
    { }
    
    bool registerPath(
        const char *path,
        osal::IFileSystem *cb);

    bool unregisterPath();

protected: // functions

    //! forwarded osal::UserFS::init
    static bool init();

    //! thread entry function
    static void fuse_event_thread(void *);

    int dispatch_open(
        const char *path,
        struct fuse_file_info *info,
        const bool dir,
        const mode_t mode = S_IRUSR);

protected: // wrapped fuse c++ callbacks
    int open(
        const char *path,
        struct fuse_file_info *info);

    int getattr(
        const char *path,
        struct stat *s);

    int opendir(
        const char *path,
        struct fuse_file_info *info);

    int release(
        const char *path,
        struct fuse_file_info *info);

    int releasedir(
        const char *path,
        struct fuse_file_info *info);
    
    int readdir(
        const char *path,
        void *buf,
        fuse_fill_dir_t filler,
        off_t offset,
        struct fuse_file_info *info);

    int readlink(
        const char *path,
        char *link,
        size_t size);
    
    int read(
        const char *path,
        char *buf,
        size_t size,
        off_t offset,
        struct fuse_file_info *info);
    
    int write(
        const char *path,
        const char *buf,
        size_t size,
        off_t offset,
        struct fuse_file_info *info);

    int truncate(
        const char *path,
        off_t size);

    int create(
        const char *path,
        mode_t mode,
        struct fuse_file_info *info);

    int mkdir(
        const char *path,
        mode_t mode);

    int unlink(
        const char *path);

    int rename(
        const char *path,
        const char *newpath);

    int rmdir(
        const char *path);

    int symlink(
        const char *path,
        const char *link);

    int chmod(
        const char *path,
        mode_t mode);

    int utimens(
        const char *path,
        const struct timespec tv[2]);

protected: // fuse C callbacks
    
    static int userfs_getattr(
        const char *path,
        struct stat *s);

    static int userfs_opendir(
        const char *path,
        struct fuse_file_info *info);

    static int userfs_release(
        const char *path,
        struct fuse_file_info *info);

    static int userfs_releasedir(
        const char *path,
        struct fuse_file_info *info);

    static int userfs_readdir(
        const char *path,
        void *buf,
        fuse_fill_dir_t filler,
        off_t offset,
        struct fuse_file_info *info);

    static int userfs_readlink(
        const char *path,
        char *link,
        size_t size);

    static int userfs_open(
        const char *path,
        struct fuse_file_info *info);

    static int userfs_read(
        const char *path,
        char *buf,
        size_t size,
        off_t offset,
        struct fuse_file_info *info);
    
    static int userfs_write(
        const char *path,
        const char *buf,
        size_t size,
        off_t offset,
        struct fuse_file_info *info);

    static int userfs_truncate(
        const char *path,
        off_t size);

    static int userfs_create(
        const char *path,
        mode_t mode,
        struct fuse_file_info *info);

    static int userfs_mkdir(
        const char *path,
        mode_t mode);

    static int userfs_utimens(
        const char *path,
        const struct timespec tv[2]);

    static int userfs_unlink(
        const char *path);

    static int userfs_rename(
        const char *path,
        const char *newpath);

    static int userfs_rmdir(
        const char *path);

    static int userfs_symlink(
        const char *path,
        const char *link);

    static int userfs_chmod(
        const char *path,
        mode_t mode);

protected: // data
    osal::IFileSystem *m_user_cb;
    osal::Thread *m_event_thread;

    //! the mount point we're running at
    ipl::string m_mount_path;

    //! structure returned from fuse_mount
    struct fuse_chan *m_fuse_channel;
    //! a Fuse handle for the Fuse file system
    struct fuse *m_fuse_handle;

    //! low-level fuse callback definitions
    static struct fuse_operations s_fuse_ops;

    // let our exclusive user fiddle with our members
    friend class UserFS;
};

// this simply holds the necessary data to fill in a QNX message with struct
// dirents and calculate the correct alignment and free size counters
struct DirFillerHandle
{
    DirFillerHandle(void *b, fuse_fill_dir_t &fill, off_t o):
        full(false),
        buf(b),
        filler(fill),
        offset(o)
    {
    }

    bool full;
    void *buf;
    fuse_fill_dir_t &filler;
    // the current offset
    off_t offset;
};

typedef ino_t EntityID;

} // end ns osal
#else // HAVE_OSAL_USERFS

typedef ino_t EntityID;

struct DirFillerHandle { };

struct UserFSRequestHandle { };

struct UserFSEntityHandle { };

struct UserFSHandle { };

#endif

#endif // inc. guard
