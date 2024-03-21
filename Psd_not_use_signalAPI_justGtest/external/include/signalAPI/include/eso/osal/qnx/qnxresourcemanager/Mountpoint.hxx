#ifndef OSAL_QNXRESOURCEMANAGER_MOUNTPOINT_HXX
#define OSAL_QNXRESOURCEMANAGER_MOUNTPOINT_HXX

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

#include <common/types/string.hxx>
#include <common/CommonError.hxx>
#include <common/NonCopyable.hxx>

#include <osal/osal_dso.h>

#include "sys.hxx"
#include "Attr.hxx"

namespace osal
{
    namespace qnxresourcemanager
    {
        class Engine;
    }
}

namespace util
{
    namespace transport
    {
        class QnxResourceManagerTransport;
    }
}

namespace osal
{

namespace qnxresourcemanager
{

/**
 * \brief
 *     Base class for one mount point

 *     The term mount point is not official QNX resource manager
 *     terminology (mage2618: this is not entirely true. QNX knows of a
 *     mount point structure. this structure is kept per "file system"
 *     i.e. it contains settings shared by the complete resource
 *     manager. This is not to be confused with the Mountpoint we're
 *     talking about *here*).
 *
 *     We use it here to denote a name in the file system where a
 *     resource manager is attached.
 *
 *     We need some term for this as one resource manager instance
 *     (with a single dispatcher, a single thread pool etc.) may attach
 *     to several names, i.e. inhabit several mount points.
 *
 *     By separating the mount point from the lower level resource
 *     manager engine you can attach different behaviour to different
 *     names with only one instance of lowlevel stuff.
 *
 *     Inherit this and override the connect methods as needed.
 *
 *     The Mountpoint class basically registers an actual file system
 *     path that is connected to the provided Engine's dispatch
 *     context.
 *
 *     This class provides the first level of C++ interface for
 *     incoming connect and ocb callbacks.
 **/
class OSAL_EXPORT Mountpoint :
    public ipl::NonCopyable,
    public Engine::Again
{
public:
    /**
     * \brief
     *    Create a Mountpoint using \c resourcemanager on the
     *    given path/mode
     * \param[in] engine
     *    The underyling resourcemanager engine to use
     * \param[in] dir
     *    Whether this is supposed to be a directory or file
     *    otherwise.
     *    If a directory is registered then you will also receive
     *    callbacks for files below registered paths.
     * \param[in] mode
     *    The access mode for the new mount point
     * \errorindicator
     *    via isValid()
     * \errors
     *
     **/
    Mountpoint(
        Engine &engine,
        bool dir,
        mode_t mode);

    ~Mountpoint()
    {
        IPL_ASSERT( m_id == -1 );
    }

    //! whether the mountpoint is healthy
    bool isValid() const
    {
        return m_engine.isValid() && m_id != -1;
    }

protected: // functions

    /**
     * \brief
     *     Register the mountpoint at the given path

     *     After return of this function actual client calls can
     *     come in for this Mountpoint. You may only register one
     *     path at once at a Mountpoint object. You can unregister
     *     the path and register another one at a later time.
     * \param[in] path
     *    The path for which to register the mountpoint
     **/
    bool registerPath(const char *path)
    {
        if( m_id != -1 )
        {
            ipl_raise( ipl::CommonError,
                ipl::INVALID_USAGE,
                "there's already a path registered");
            return true;
        }

        m_id = m_engine.registerPath(
            path, &m_attr, m_is_dir);

        return m_id == -1;
    }

    
    /**
     * \brief
     *     Unregister the path previously registered via
     *     registerPath(const char*)

     *     Unregistering a path means that the mountpoint will no
     *     longer be visible in the file system. After return of
     *     this function further client connections won't be
     *     possible for this Mountpoint object.
     *
     *     If \c remove_clients is set to \c true then any already
     *     active connections for the registered path will be
     *     severed.
     * \see
     *     Engine::unregisterPath(int, bool)
     **/
    void unregisterPath(bool remove_clients = false)
    {
        if( m_id == -1 )
            return;

        if( m_engine.unregisterPath(m_id, remove_clients) )
        {
            IPL_WARN("error detaching resman path!");
            ipl_error.ack();
        }

        m_id = -1;
    }

protected: // forwarded function calls from engine c-callbacks

    // Engine wants to call the iofunc and connect funcs
    friend class Engine;

    // iofunc funcs
    //
    // the OCB is a context that is kept per client of a file i.e.
    // is is per client file descriptor. Thus we can keep per client
    // connection data in our extended OCB that we can then access
    // in subsequent read and write calls etc.
    //
    // these functions are responsible for allocating the extended
    // structure. This structure must contain the standard fields
    // expected by QNX.
    //
    // these functions are called in the context of the default open
    // handler iofunc_open_default()
    virtual Ocb *ocb_calloc(resmgr_context_t *ctp, Attr *attr) = 0;

    virtual void ocb_free(Ocb *ocb) = 0;

    // connect funcs
    
    /**
     * \brief
     *     Open request from a client

     *     The default implementation in Mountpoint calls the QNX
     *     iofunc_open_default which must be called in order for an
     *     OCB to be allocated by the resman library.
     *
     *     The iofunc_open_default associates an iofunc_attr_t with
     *     the OCB. If the current Mountpoint represents a file
     *     then there is only one iofunc_attr_t which member of the
     *     Mountpoint instance. In this case you should *always*
     *     call the Mountpoint::open for correctly allocating the
     *     OCB and passing on the Attr struct *if* you override
     *     this function in derived classes.
     *
     *     If, however, your Mountpoint represents a directory then
     *     you need a unique iofunc_attr_t for each file in your
     *     file system. In that case you should *not* call
     *     Mountpoint::open but instead call iofunc_open_default
     *     yourself with an appropriate iofunc_attr_t for the given
     *     path.
     **/
    virtual int open(resmgr_context_t *ctp, io_open_t *msg, void *extra);
    virtual int unlink(resmgr_context_t *ctp, io_unlink_t *msg,
                    void *reserved);
    virtual int rename(resmgr_context_t *ctp, io_rename_t *msg,
                    io_rename_extra_t *extra);
    //! called if a fifo or directory (!) is to be created
    virtual int mknod(resmgr_context_t *ctp, io_mknod_t *msg,
                    void *reserved);
    virtual int readlink(resmgr_context_t *ctp, io_readlink_t *msg,
                         void *reserved);
    virtual int link(resmgr_context_t *ctp, io_link_t *msg,
                     io_link_extra_t *extra);
    virtual int unblock(resmgr_context_t *ctp, io_pulse_t *msg,
                        void *reserved);
    virtual int mount(resmgr_context_t *ctp, io_mount_t *msg,
                    io_mount_extra_t *extra);

    Engine& getEngine()
    {
        return m_engine;
    }

protected: // data

    //! the resmgr. engine to use for registering our Mountpoint
    Engine &m_engine;

    /**
     * \brief
     *    The attribute information for the registered path

     *     Each path has on of these structures associated (in
     *     contrast to the OCB which is per client open)
     ***/
    Attr m_attr;
    
    //! \brief
    //! the id of the path name, needed for detaching at a later
    //! time
    int m_id;

    //! whether a directory is desired instead of a file
    bool m_is_dir;
};

} // end of namespace qnxresourcemanager
} // end of namespace osal

#endif // inc. guard
