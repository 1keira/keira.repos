/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_TRANSPORT_QNXRESOURCEMANAGERTRANSPORTFACTORYUNDERWEAR_HXX
#define UTIL_TRANSPORT_QNXRESOURCEMANAGERTRANSPORTFACTORYUNDERWEAR_HXX

#include <ipl_config.h>

#include <common/types/queue.hxx>
#include <osal/Mutex.hxx>
#include <osal/Condition.hxx>
#include <osal/qnx/qnxresourcemanager/File.hxx>
#include <osal/qnx/qnxresourcemanager/Engine.hxx>

#include <util/SharedPtr.hxx>
#include <util/transport/factory/IFactory.hxx>

#include <util/util_dso.h>
#include <util/SharedPtr.hxx>
#include <util/sharedptr/SharedFromThisBase.hxx>

// fwd. decl. the transport type
namespace util
{
    namespace transport
    {
        class QnxResourceManagerTransport;
    }
}

namespace util
{

namespace transport
{

/**
 * \brief
 *     Implementation of the QnxResourceManagerTransport's internals

 *     This implements the interface towards the resource manager
 *     underwear.
 *
 *     It is decoupled from the implementation of IFactory because it
 *     needs to live longer, in order to avoid race conditions between
 *     the factory being deleted and an incoming connection being
 *     registered.
 * \internal
**/
class QnxResourceManagerTransportFactoryUnderwear :
    // we implement a device file
    public osal::qnxresourcemanager::File,
    // we implement shared from this, which allows the underwear to
    // forward shared-ptrs to itself to instances of
    // QnxResourceManagerTransport
    public util::SharedFromThisBase<QnxResourceManagerTransportFactoryUnderwear>
{
public: // types

    //! a magical ptr. type pointing to this very type
    typedef util::SharedPtr
        <QnxResourceManagerTransportFactoryUnderwear>
        UnderwearPtr;
public: // functions
    /**
     * \brief
     *     Setup new underwear
     * \param[in] engine
     *     The low-level engine to use for the factory and newly
     *     created transports
     **/
    QnxResourceManagerTransportFactoryUnderwear(
        /*osal::qnxresourcemanager::Engine &engine,*/
        const SharedPtr<osal::qnxresourcemanager::Engine> &engine,
        const ipl::string &filename,
        const size_t rx_buffer,
        const size_t tx_buffer) IPL_NOEXCEPT;

    virtual ~QnxResourceManagerTransportFactoryUnderwear() IPL_NOEXCEPT;

    /**
     * \brief
     *     Actually implements
     *     QnxSpawnResourceManagerTransportFactory::createTransport()
     **/
    QnxResourceManagerTransport* createTransport() IPL_NOEXCEPT;

    /**
     * \brief
     *     Actually implements
     *     QnxSpawnResourceManagerTransportFactory::enableFactory()

     *     Registers the resource manager path that allows clients
     *     to connect to us
     **/
    bool enableUnderwear() IPL_NOEXCEPT;

    /**
     * \brief
     *     Actually implements
     *     QnxSpawnResourceManagerTransportFactory::closeFactory()

     *     Removes the resource manager path that allows clients to
     *     connect to us, thus avoiding further connection
     *     attempts.
     *
     *     Already pending transport connections will be discarded.
     **/
    bool disableUnderwear() IPL_NOEXCEPT;

    /**
     * \brief
     *     Actually publishes the given transport at the factory
     *     client
     **/
    void publish(QnxResourceManagerTransport *transport) IPL_NOEXCEPT;

//    /**
//     * \brief
//     *     Returns only if all transports spawned from this factory
//     *     have been disposed
//     **/
//    void waitUntilTransportsGone() IPL_NOEXCEPT
//    {
//        util::MutexGuard g(m_new_transports_mutex);
//
//        while( m_open_transports )
//        {
//            IPL_CONDITION_WAIT_OR_ABORT(m_new_transports_condition,
//                m_new_transports_mutex);
//        }
//    }

protected: // functions

    /**
     * \brief
     *     Disposes of any transports that are currently pending in
     *     m_new_transports, client will be disconnected thus
     **/
    void disposePendingTransports() IPL_NOEXCEPT;

    /**
     * \brief
     *     Called from the resman engine upon open requests to
     *     allocate client data

     *     The open request is considered to be a new connection
     *     from a client and thus creates a new transport
     **/
    virtual osal::qnxresourcemanager::Ocb *ocb_calloc(
        resmgr_context_t *ctp,
        osal::qnxresourcemanager::Attr *handle) IPL_NOEXCEPT;

    /**
     * \brief
     *     Called from the resman engine upon close calls to free
     *     client data

     *     The close calls cleans up the associated resource
     *     manager transport
     **/
    virtual void ocb_free(osal::qnxresourcemanager::Ocb *ocb) IPL_NOEXCEPT;

    /**
     * \brief
     *     Called from the resman engine if we need to unblock a
     *     blocking client due to signal or timeout

     *     This unblocks any pending open calls
     **/
    virtual int unblock(
        resmgr_context_t *ctp,
        io_pulse_t *msg,
        void *reserved) IPL_NOEXCEPT;

protected: // data

    //! \brief Determines the Engine's lifetime!
    SharedPtr<osal::qnxresourcemanager::Engine> m_engine;
    osal::Mutex m_new_transports_mutex;
    osal::Condition m_new_transports_condition;

    ipl::queue<QnxResourceManagerTransport*> m_new_transports;

    //! the resource manager path where new connections are spawned
    ipl::string m_spawn_path;

//    size_t m_open_transports;

    const size_t m_rx_buffer;
    const size_t m_tx_buffer;
};

} // end of namespace transport
} // end of namespace util

#endif
