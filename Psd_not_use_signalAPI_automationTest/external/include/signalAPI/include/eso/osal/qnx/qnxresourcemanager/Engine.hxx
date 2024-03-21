#ifndef OSAL_QNXRESOURCEMANAGER_ENGINE_HXX
#define OSAL_QNXRESOURCEMANAGER_ENGINE_HXX

/*
    Copyright e.solutions GmbH
    All rights reserved
    Authors:
        Stefan Meinlschmidt
        Matthias Gerstner
    $Id$
*/

#include <ipl_config.h>

#ifndef IPL_OS_QNX
#    error "This is system specific code for QNX. You cannot compile it for other systems."
#endif

// for shared object definition
#include <osal/osal_dso.h>

#include "sys.hxx"
#include "ThreadPool.hxx"

#include <common/tracing/tracing.hxx>
#include <osal/AtomicCounter.hxx>
#include <osal/Mutex.hxx>


IPL_TRACE_DECLARE_CHANNEL_EXTERN(FW_QNXRESOURCEMANAGER);

namespace osal
{

namespace qnxresourcemanager
{

/**
 * \brief
 *    Base implementation of a Resource Manager (see QNX programming
 *    docu)

 *    All the C-style connect and i/o functions get redirected to
 *    virtual methods of Mountpoint and Session, so you can implement
 *    them in a derived class.
 *
 *    The Engine basically creates a dispatch context and an
 *    associated thread pool. The low level structures for setting up
 *    a resource manager are all present here. The Engine doesn't bind
 *    itself to an actual file system path, however. This is the job
 *    of the Mountpoint class. The Engine can be used for multiple
 *    mountpoints. It is merely a mechanism for processing incoming
 *    requests and dispatching them to the right place.
 * \warning
 *     The Engine's thread pool must not be started before the Engine
 *     has been registered for some type of events by means of
 *     resmgr_attach
*/
class OSAL_EXPORT Engine
{
public:
    // subclass for dealing with re-receiving messages that we can't
    // process at the moment
    class Again;

    /**
     * \brief
     *    Creates a shiny new Engine
     * \errorindicator
     *    via isValid()
     * \errors
     *    XXX

     *    Regarding the parameters please refer to
     *    osal::qnxresourcemanager::ThreadPool and resmgr_attr_t
     * \param[in] msg_max_size
     *     This is the maximum amount of data that will be
     *     transferred immediatly alongside a write() call from the
     *     client i.e. that data can then be inspected immediatly
     *     and does not need to be transferred from the clients
     *     buffer
     *
     * \todo Some actually usable configurability would be nice.
     **/
    Engine(const int min_blocking_threads=1,
        const int max_blocking_threads=5,
        const int creation_step=1,
        const int max_overall_threads=10,
        /* 8192 is a good size for qnet */
        int msg_max_size = 8192);

    /**
     * \brief
     *     Shut down the engine

     *     No more paths must be registered at the engine at
     *     destruction time.
     *
     *     If any outstanding clients remain that use the Engine
     *     then they will be hard-disconnected, getting EBADF
     *     errors if try to keep communicating with the resource
     *     manager.
     **/
    ~Engine();

    //! returns whether the Engine is healthy
    bool isValid() const
    { return m_dpp != NULL && m_chid >= 0; }

    /**
     * \brief
     *     Initialize the given attribute structure and set its
     *     mount point structure

     *     The engine keeps the io_mount_t structure in
     *     s_mountpoint. A pointer to this structure needs to be
     *     set in each attribute structure.
     *
     *     This is what this function does, additionally to calling
     *     the native QNX function for initializing the attribute
     *     structure with \c mode to set the access permissions.
     **/
    static void initAttr(iofunc_attr_t *attr, const mode_t &mode)
    {
        // initialize the std. QNX part of the attribute
        // structure
        //
        // mode gives the access rights
        //
        // the third parameter is an optional attribute
        // structure from which to take over information into
        // m_attr
        //
        // the last parameter is a client information structure
        // that deals with ownership. We keep defaults.
        iofunc_attr_init(attr, mode, NULL, NULL);

        // directories initially need a link count of two (. and
        // ..)
        if( mode & S_IFDIR )
            attr->nlink = 2;

        // set the mountpoint structure
        attr->mount = &s_mountpoint;
    }

    /**
     * \brief
     *     Register the given path with the resource manager

     *     After return of this function actual client calls can
     *     come in for the given path.
     *
     *     The path will obtain the attributes set in \c attr.
     *
     *     The path will be a regular file if \c is_dir is \c false
     *     and a directory if \c is_dir is \c true.
     *
     *    The returned identifier needs to be specified at
     *    unregisterPath for removing the path from the file
     *    system again.
     * \param[in] path
     *    The path for which to register the mountpoint
     * \param[in] attr
     *     The attributes for the to be registered path
     * \param[in] is_dir
     *     Whether the path should be a regular file or a directory
     *     entry
     * \return
     *     -1 on error, otherwise on success
     * \errorindicator
     *     via return code
     * \errors
     *     osal::FileAccessError with ID
     *
     *     - BAD_PATH if a component of \c path is not a directory
     *
     *     - NO_ACCESS if the caller is not root
     *
     *     osal::SysError with ID
     *
     *     - OUT_OF_MEMORY if there is a lack of memory to perform
     *     the operation
     **/
    int registerPath(
        const char *path,
        Attr *attr,
        bool is_dir);

    /**
     * \brief
     *     Unregister a path previously registered via
     *     registerPath(const char*, Attr*, bool)

     *     Unregistering a path means that the file system entry
     *     will no longer be visible in the file system. After
     *     return of this function further client connections won't
     *     be possible for the previously registered path.
     *
     *     If \c remove_clients is set to \c true then any already
     *     active connections for the registered path will be
     *     severed, the clients will get ESRCH or EBADF when trying
     *     to access their file descriptors.
     * \param[in] id
     *     The identifier obtained at registerPath(const char*,
     *     Attr*, bool)
     * \param[in] remove_clients
     *     Whether already established clients for the given path
     *     should be disconnected
     * \return
     *     \c true on error, \c false on success
     * \errorindicator
     *     via return code
     * \errors
     *     osal::SysError with ID INTEGRITY_ERROR in consistency
     *     errors like:
     *
     *     - \c id is no known registered path
     *     - \c id has already been unregistered
     **/
    bool unregisterPath(
        int id,
        bool remove_clients
        );

protected: // functions

    /**
     * \brief
     *    Call this to make sure the Engine is in an operable
     *    state
     **/
    void threadPoolInit();

    /**
     * \brief
     *     Shut down the thread pool
     **/
    void threadPoolExit();

    friend class osal::Osal;

    //! called during OSAL initialization
    static void init();

protected: // data

    //! dispatch context used by the resmgr. library
    dispatch_t *m_dpp;
    //! QNX channel used for message passing
    int m_chid;

    //! the number of currently registered paths for this Engine
    osal::AtomicCounter m_paths;

private: // data

    //! \brief
    //! defines some basic properties of the resmgr used during
    //! resmgr_attach
    resmgr_attr_t m_resmgr_attr;
    //! the thread-pool that works with our dispatch context
    ThreadPool m_threadpool;

    // pointers to these structures are taken over by the resmgr
    // library thus we must make sure that the structures are
    // valid as long as the library needs to use them.
    //
    // also it means that the structures can only be used for
    // one resmgr instance (as long as instances are supposed to do
    // different things regarding callbacks)

    //! \brief
    //! tells the resmgr library what functions to call when
    //! our file gets fiddled with like open,mount,link etc.
    static resmgr_connect_funcs_t s_connect_funcs;
    //! \brief
    //! tells the resmgr library what functions to call when
    //! actual content of our file or its metadata is fiddled
    //! with like read,write,stat,chmod,chown
    static resmgr_io_funcs_t s_io_funcs;
    //! callbacks for ocb creation/deletion
    static iofunc_funcs_t s_ocb_funcs;
    //! property settings for a mountpoint
    static iofunc_mount_t s_mountpoint;

private: // all the c-callback functions for the QNX API

    // iofunc funcs
    static Ocb *_ocb_calloc(resmgr_context_t *ctp, Attr *attr);
    static void _ocb_free(Ocb *ocb);

    // connect funcs
    static int _open(
        resmgr_context_t *ctp, io_open_t *msg, Attr *handle,
        void *extra);
    static int _unlink(
        resmgr_context_t *ctp, io_unlink_t *msg, Attr *handle,
        void *reserved);
    static int _rename(
        resmgr_context_t *ctp, io_rename_t *msg, Attr *handle,
        io_rename_extra_t *extra);
    static int _mknod(
        resmgr_context_t *ctp, io_mknod_t *msg, Attr *handle,
        void *reserved);
    static int _readlink(
        resmgr_context_t *ctp, io_readlink_t *msg, Attr *handle,
        void *reserved);
    static int _link(
        resmgr_context_t *ctp, io_link_t *msg, Attr *handle,
        io_link_extra_t *extra);
    static int _unblock(
        resmgr_context_t *ctp, io_pulse_t *msg, Attr *handle,
        void *reserved);
    static int _mount(
        resmgr_context_t *ctp, io_mount_t *msg, Attr *handle,
        io_mount_extra_t *extra);

    // io funcs
    static int _read(
        resmgr_context_t *ctp, io_read_t *msg, Ocb *ocb);
    static int _write(
        resmgr_context_t *ctp, io_write_t *msg, Ocb *ocb);
    static int _close_ocb(
        resmgr_context_t *ctp, void *reserved, Ocb *ocb);
    static int _stat(
        resmgr_context_t *ctp, io_stat_t *msg, Ocb *ocb);
    static int _notify(
        resmgr_context_t *ctp, io_notify_t *msg, Ocb *ocb);
    static int _devctl(
        resmgr_context_t *ctp, io_devctl_t *msg, Ocb *ocb);
    static int _unblock(
        resmgr_context_t *ctp, io_pulse_t *msg, Ocb *ocb);
    static int _pathconf(
    resmgr_context_t *ctp, io_pathconf_t *msg, Ocb *ocb);
        static int _lseek(
        resmgr_context_t *ctp, io_lseek_t *msg, Ocb *ocb);
    static int _chmod(
        resmgr_context_t *ctp, io_chmod_t *msg, Ocb *ocb);
    static int _chown(
        resmgr_context_t *ctp, io_chown_t *msg, Ocb *ocb);
    static int _utime(
        resmgr_context_t *ctp, io_utime_t *msg, Ocb *ocb);
    static int _openfd(
        resmgr_context_t *ctp, io_openfd_t *msg, Ocb *ocb);
    static int _fdinfo(
        resmgr_context_t *ctp, io_fdinfo_t *msg, Ocb *ocb);
    static int _lock(
        resmgr_context_t *ctp, io_lock_t *msg, Ocb *ocb);
    static int _space(
        resmgr_context_t *ctp, io_space_t *msg, Ocb *ocb);
    static int _shutdown(
        resmgr_context_t *ctp, io_shutdown_t *msg, Ocb *ocb);
    static int _mmap(
        resmgr_context_t *ctp, io_mmap_t *msg, Ocb *ocb);
    static int _msg(
        resmgr_context_t *ctp, io_msg_t *msg, Ocb *ocb);
    static int _reserved(
        resmgr_context_t *ctp, void *msg, Ocb *ocb);
    static int _lock_ocb(
        resmgr_context_t *ctp, void *reserved, Ocb *ocb);
    static int _unlock_ocb(
        resmgr_context_t *ctp, void *reserved, Ocb *ocb);
    static int _sync(
        resmgr_context_t *ctp, io_sync_t *msg, Ocb *ocb);
    static int _power(
        resmgr_context_t *ctp, io_power_t *msg, Ocb *ocb);
};

/**
 *\brief
 *    Interface/mixin for correct resman_msg_again() use

 *    If your Again descendant needs to put a received message (we're
 *    thinking of a QNX message here i.e. a request to our resource
 *    manager to do whatever) on the shelve for later processing, do
 *    the following:
 *
 *    - store \c ctp->rcvid
 *    - store \c ctp->info.priority
 *    - return \c _RESMGR_NOREPLY to the dispatcher (callback function
 *    called from the Engine)
 *
 *    To redeliver it, call again(), providing the previously stored
 *    ID and priority
 *
 *    This will send an internal pulse so one of the receive threads
 *    wakes up to call resman_msg_again() without hosing locks or
 *    thread priorities.
*/
class Engine::Again
{
public: // constants

    //! \brief Convenience: Use this for storing \e no rcvid
    static const int RCVID_NONE = -1;

public: // functions

    /**
     * \brief
     *     Cause the previously seen request for the given receive
     *     ID and priority to be scheduled again
     **/
    void again(int rcvid, int priority);

protected: // functions

    //! is not usable on its own, you need to derive from it
    Again(const Engine &engine);

    ~Again();

private: // functions
    static int pulsehandler(
        message_context_t *ctp, int code,
        unsigned flags, void *handle);

private: // data

    //! channel ID of ConnectAttach to Engine channel
    int m_coid;
    //! pulse code registration
    int m_code;
    //! we need this context for detaching from the pulse code
    dispatch_t *m_dpp;
};

} // end of namespace qnxresourcemanager
} // end of namespace osal

#endif // inc. guard
