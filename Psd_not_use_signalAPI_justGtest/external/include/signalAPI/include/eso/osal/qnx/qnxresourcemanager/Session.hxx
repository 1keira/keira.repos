#ifndef OSAL_QNXRESOURCEMANAGER_SESSION_HXX
#define OSAL_QNXRESOURCEMANAGER_SESSION_HXX

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

#include <osal/osal_dso.h>

#include "sys.hxx"
#include "Ocb.hxx"
#include "Mountpoint.hxx"

namespace osal
{

namespace qnxresourcemanager
{

/**
 * \brief
 *     Class representing an individual i/o session with a client

 *    This class provides the first level of C++ interfaces for
 *    incoming i/o callbacks.
 *
 *     Implement dispose() so that it complements the implementation of
 *     \ref Mountpoint::ocb_calloc "ocb_calloc()" and \ref
 *     Mountpoint::ocb_free "ocb_free()" in your Mountpoint derivative.
 **/
class OSAL_EXPORT Session
{
public:
    Session() :
        m_ocb(NULL, this)
    { /* NOP */ }

    /**
     * \brief
     *     Create a new Session operating on the given Mountpoint
     **/
    Session(Mountpoint &mountpoint) :
        m_ocb(&mountpoint, this)
    { }

    virtual ~Session()
    { /* NOP */ }

    /**
     * \brief
     *     Return the extended OCB structure known by QNX
     **/
    Ocb* getOcb()
    {
        return &m_ocb;
    }

    void setMountpoint(Mountpoint &mountpoint)
    {
        m_ocb.mountpoint = &mountpoint;
    }

    // io funcs
    virtual int read(resmgr_context_t *ctp, io_read_t *msg);
    virtual int write(resmgr_context_t *ctp, io_write_t *msg);
    virtual int close_ocb(resmgr_context_t *ctp, void *reserved);
    virtual int stat(resmgr_context_t *ctp, io_stat_t *msg);
    virtual int notify(resmgr_context_t *ctp, io_notify_t *msg);
    virtual int devctl(resmgr_context_t *ctp, io_devctl_t *msg);
    virtual int unblock(resmgr_context_t *ctp, io_pulse_t *msg);
    virtual int pathconf(resmgr_context_t *ctp, io_pathconf_t *msg);
    virtual int lseek(resmgr_context_t *ctp, io_lseek_t *msg);
    virtual int chmod(resmgr_context_t *ctp, io_chmod_t *msg);
    virtual int chown(resmgr_context_t *ctp, io_chown_t *msg);
    virtual int utime(resmgr_context_t *ctp, io_utime_t *msg);
    virtual int openfd(resmgr_context_t *ctp, io_openfd_t *msg);
    virtual int fdinfo(resmgr_context_t *ctp, io_fdinfo_t *msg);
    virtual int lock(resmgr_context_t *ctp, io_lock_t *msg);
    virtual int space(resmgr_context_t *ctp, io_space_t *msg);
    virtual int shutdown(resmgr_context_t *ctp, io_shutdown_t *msg);
    virtual int mmap(resmgr_context_t *ctp, io_mmap_t *msg);
    virtual int msg(resmgr_context_t *ctp, io_msg_t *msg);
    virtual int reserved(resmgr_context_t *ctp, void *msg);
    virtual int lock_ocb(resmgr_context_t *ctp, void *reserved);
    virtual int unlock_ocb(resmgr_context_t *ctp, void *reserved);
    virtual int sync(resmgr_context_t *ctp, io_sync_t *msg);
    virtual int power(resmgr_context_t *ctp, io_power_t *msg);

protected: // functions

    /**
     * \brief
     *     Shortcut wrapper for re-sending the given request with
     *     the given priority
     **/
    void again(int rcvid, int priority)
    {
        (m_ocb.mountpoint)->again(rcvid, priority);
    }

protected: // types

    //! shortcut for invalid RCVID
    static const int RCVID_NONE = Engine::Again::RCVID_NONE;
    
protected: // data

    //! the OCB that our Session object covers
    Ocb m_ocb;
};

} // end of namespace qnxresourcemanager

} // end of namespace osal

#endif // inc. guard
