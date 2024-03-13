#ifndef OSAL_QNX_OSALFSDEFS_HXX
#define OSAL_QNX_OSALFSDEFS_HXX

// on QNX we can always do this stuff
#define HAVE_OSAL_USERFS

#include <dirent.h>

#include <osal/qnx/qnxresourcemanager/Engine.hxx>
#include <osal/qnx/qnxresourcemanager/Directory.hxx>
#include <osal/qnx/qnxresourcemanager/Session.hxx>

namespace osal
{

// fwd. declaration
class IFileSystem;

typedef qnxresourcemanager::Attr UserFSEntityHandle;

/*
 * we need to additionally store the entity and callback pointers for
 *
 * 1) being able to provide the entity even if we only have the request
 * (e.g. in ocb_close)
 * 2) being able to actually dispatch Session callback to the UserFS
 * client
 */
struct OSAL_EXPORT UserFSRequestHandle :
    public qnxresourcemanager::Session
{
    UserFSRequestHandle(): callback()
    { /* NOP */ }

    void setCallback(IFileSystem *cb)
    {
        callback = cb;
    }

    /*
     * incoming read request for both files and directories
     */
    int read(resmgr_context_t *ctp, io_read_t *msg);

    /*
     * incoming write request for files
     */
    int write(resmgr_context_t *ctp, io_write_t *msg);

    /*
     * request to change the size of the object "truncate"
     */
    int space(resmgr_context_t *ctp, io_space_t *msg);

    /*
     * request to change the permissions of the object
     */
    int chmod(resmgr_context_t *ctp, io_chmod_t *msg);

    /*
     * request to change the modification time of the object
     */
    int utime(resmgr_context_t *ctp, io_utime_t *msg);

protected: // io functions

protected:
    IFileSystem *callback;
};

/*
 * Implements the directory flavour of the qnxresourcemanager framework
 *
 * receives all connect callbacks and forwards them to the UserFS client
 *
 * This can't be done in the Handle directly as we need to pass the
 * engine to the base class directly before it is even constructed ...
 * thus the Engine is kept in the handle alongside a QnxUserFS such that
 * construction order can be controlled again
 */    
class OSAL_EXPORT QnxUserFS :
    public qnxresourcemanager::Directory
{
public:
    QnxUserFS(qnxresourcemanager::Engine &engine) :
        qnxresourcemanager::Directory(engine),
        m_user_cb()
    { }

    bool registerPath(
        const char *path,
        osal::IFileSystem *cb);

    bool unregisterPath()
    {
        Mountpoint::unregisterPath(false);

        m_user_cb = NULL;

        return false;
    }

protected: // functions

    /**
     * \brief
     *     Is called upon new requests, regardless of what type
     *     (open, stat, etc.)
     **/
    qnxresourcemanager::Ocb* ocb_calloc(resmgr_context_t *ctp,
        qnxresourcemanager::Attr *attr);

    /**
     * \brief
     *     Is called upon requests being finished, typically a
     *     close() or finished stat etc.
     **/
    void ocb_free(qnxresourcemanager::Ocb *ocb);

    //! will be called before ocb_calloc to verify access etc.
    int open(resmgr_context_t *ctp, io_open_t *msg, void *extra);

    //! will be called for mkdir() (!), mknod(), mkfifo()
    int mknod(resmgr_context_t *ctp, io_mknod_t *msg, void *reserved);

    int unlink(resmgr_context_t *ctp, io_unlink_t *msg,
                    void *reserved);
    int rename(resmgr_context_t *ctp, io_rename_t *msg,
                    io_rename_extra_t *extra);
    int readlink(resmgr_context_t *ctp, io_readlink_t *msg,
                         void *reserved);
    int link(resmgr_context_t *ctp, io_link_t *msg,
                     io_link_extra_t *extra);


protected: // data
    osal::IFileSystem *m_user_cb;
};

class UserFSHandle
{
public:
    UserFSHandle(const bool multithreaded) :
        m_engine(
            1,
            multithreaded ? 5 : 1,
            1,
            multithreaded ? 10 : 1),
        m_qnx_fs(m_engine)
    { }
protected:
    // we use a whole engine per FS
    osal::qnxresourcemanager::Engine m_engine;
    // QNX native FS stuff
    QnxUserFS m_qnx_fs;

    // let our exclusive user fiddle with our members
    friend class UserFS;
};

// this simply holds the necessary data to fill in a QNX message with struct
// dirents and calculate the correct alignment and free size counters
struct DirFillerHandle
{
    DirFillerHandle(char *buffer, size_t s, size_t o):
        reply_msg(0),
        left(s),
        size(s),
        offset(o)
    {
        nextent = (struct ::dirent*)buffer;
    }

    // a buffer for the complete reply msg. to the client
    char *reply_msg;
    // the pointer to the next free dirent structure in the buffer,
    // correctly aligned
    struct ::dirent *nextent;
    // the left amount of bytes at nextent
    int left;
    // complete size of the underlying buffer
    const int size;
    // the current offset
    size_t offset;
};

typedef ino_t EntityID;

} // end ns osal

#endif // inc. guard
