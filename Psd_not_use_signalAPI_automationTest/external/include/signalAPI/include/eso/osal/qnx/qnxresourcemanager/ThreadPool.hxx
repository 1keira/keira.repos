#ifndef OSAL_QNXRESOURCEMANAGER_THREADPOOL_HXX
#define OSAL_QNXRESOURCEMANAGER_THREADPOOL_HXX

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


namespace osal
{

namespace qnxresourcemanager
{


/**
 * \brief
 *    QNX thread pool to be used by a QnxResourceManager

 *    Uses the thread_pool_* API of QNX for providing a herd of
 *    threads that deal with the resource manager.
 * \internal
*/
class OSAL_EXPORT ThreadPool
{
public: // functions

    /**
     * \brief
     *    Creates a QNX system thread pool
     * \param[in] min_blocking_threads
     *    Number of threads that will be made sure to be
     *    always around in the pool for being in the blocking
     *    state able to accept new requests
     * \param[in] max_blocking_threads
     *    Number of threads that will be tolerated at max in
     *    the blocking state. When this amount is reached no
     *    more threads will be kept in blocking state but
     *    threads will be exited
     * \param[in] creation_step
     *    Number of threads that will be created in one go if
     *    min_blocking_threads is underrun
     * \param[in] max_overall_threads
     *    Maximum number of threads allowed in the pool be it
     *    in blocking or in processing state. This overrides
     *    min_blocking_threads, if necessary.
     **/
    ThreadPool(
        const int min_blocking_threads,
        const int max_blocking_threads,
        const int creation_step,
        const int max_overall_threads);

    ~ThreadPool();

    /**
     * \brief
     *    Start the thread pool for the given dispatch context
     * \warning
     *     The thread pool's job is undetermined at first. Its
     *     purpose only becomes obvious to the QNX library by means
     *     of the given dispatch context.
     *
     *     The dispatch context thus must be attached to some kind
     *     of events first. This is e.g. done by calling
     *     resmgr_attach for the dpp. Otherwise hard to catch
     *     errors might occur!
     **/
    void start(dispatch_t *dpp);

    //! \brief Deadlocks if called from the thread pool!
    void stop();

protected: // c-like functions called from QNX

    // our user-defined function that is called when a new
    // thread-pool thread is created
    static THREAD_POOL_PARAM_T *_context_alloc(
        THREAD_POOL_HANDLE_T *dpp);
    // our user-defined function that is called when a
    // thread-pool thread is destroyed
    static void _context_free(THREAD_POOL_PARAM_T *ctp);

protected: // data

    thread_pool_t *m_pool;
    thread_pool_attr_t m_attr;
};

} // end of namespace qnxresourcemanager

} // end of namespace osal

#endif // inc. guard
