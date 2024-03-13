/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_TRANSPORT_QNXRESOURCEMANAGERTRANSPORT_HXX
#define UTIL_TRANSPORT_QNXRESOURCEMANAGERTRANSPORT_HXX

#include <ipl_config.h>

#include <common/types/queue.hxx>

#include <osal/Mutex.hxx>
#include <osal/Condition.hxx>
#include <osal/qnx/qnxresourcemanager/Session.hxx>

#include <util/util_dso.h>
#include <util/transport/ITransport.hxx>
#include <util/transport/PacketSizeLimit.hxx>
#include "MessageSizeSerialization.hxx"
#include <util/transport/factory/QnxResourceManagerTransportFactoryUnderwear.hxx>
#include <util/transport/PosixProcessPeerInfo.hxx>
namespace osal
{
    namespace qnxresourcemanager
    {
        class Mountpoint;
    }
}

namespace util
{

namespace transport
{

/**
 * \brief
 *    Transport implementation based on a QNX Resource Manager

 *    This is the server side, i.e. it gets spawned from a QNX
 *    Resource Manager (consequently you cannot use it on other
 *    systems).
 *
 *    Use FileTransport for the client side.
**/
class UTIL_EXPORT QnxResourceManagerTransport :
    // this transport implements the i/o callback interface for
    // resource managers
    public osal::qnxresourcemanager::Session,
    public IDisposableTransport
{
public: // functions

    /**
     * \brief
     *     Create a new QnxResourceManagerTransport on the given
     *     Mountpoint

     *     This class inherits from Session which owns an Ocb. This
     *     Ocb needs to be returned in ocb_calloc such that this
     *     new transport can actually be called back from the
     *     resmgr library.
     * \param[in] mount
     *     The Mountpoint on which our transport runs. It is passed
     *     on to the Session base class which in turn passes it on
     *     to the Ocb.
     * \param[in] factory
     *     A SharedPtr to the factory that created us. This is
     *     necessary for making lazy publishing possible as the
     *     transport needs to tell the factory when we're actually
     *     communicating and thus are ready for publishing.
     * \param[in] rx_buffer_size
     *     Number of bytes to cache in the transport on the
     *     receiving side before the client's write() call will
     *     block. Zero for sensible default.
     * \param[in] tx_buffer_size
     *     Number of bytes to cache in the transport on the sending
     *     side before the users send() call will block. Zero for
     *     sensible default.
     **/
    QnxResourceManagerTransport(
        osal::qnxresourcemanager::Mountpoint &mount,
        QnxResourceManagerTransportFactoryUnderwear::UnderwearPtr factory,
        const size_t rx_buffer_size = 0,
        const size_t tx_buffer_size = 0
    ) IPL_NOEXCEPT;

protected: // functions

    // may only be disposed
    ~QnxResourceManagerTransport() IPL_NOEXCEPT;

public: // functions

    /*
     * transport interface
     */

    virtual State getState() const IPL_NOEXCEPT;

    virtual bool send(const size_t bytes, IMsgWriter *writer) IPL_NOEXCEPT;
    virtual bool send(const size_t bytes, MsgWriterPtr writer) IPL_NOEXCEPT;
    virtual Readable receive() IPL_NOEXCEPT;
    virtual void flush() IPL_NOEXCEPT;
    virtual void open() IPL_NOEXCEPT;
    virtual bool close() IPL_NOEXCEPT;

    virtual bool detectsPeerReset() const IPL_NOEXCEPT;
    virtual bool isReliable() const IPL_NOEXCEPT;
    virtual size_t maxMsgSize() const IPL_NOEXCEPT;
    virtual bool keepsRecordBoundaries() const IPL_NOEXCEPT;
    virtual PeerInfoPtr getPeerInfo() const IPL_NOEXCEPT;

    virtual void enablePacketSizeLimit(size_t limit) IPL_NOEXCEPT;
    virtual void disablePacketSizeLimit() IPL_NOEXCEPT;

    virtual void dispose();

    // timeout in ms until a warning is traced if we can't send
    static const unsigned SEND_WARN_TIMEOUT;

protected: // resmgr. i/o callbacks
    virtual int read(resmgr_context_t *ctp, io_read_t *msg) IPL_NOEXCEPT;
    virtual int write(resmgr_context_t *ctp, io_write_t *msg) IPL_NOEXCEPT;
    virtual int close_ocb(resmgr_context_t *ctp, void *reserved) IPL_NOEXCEPT;
    virtual int unblock(resmgr_context_t *ctp, io_pulse_t *msg) IPL_NOEXCEPT;

protected: // functions

    /**
     * \brief
     *     reads a single message from data provided by the client
     *     in a write() call
     * \param[in]
     *     rcv_id The QNX rcv. ID for the client call
     * \param[in,out]
     *     present_data A pointer to client payload already
     *     accessible in our process, needs to be updated if data
     *     from there is processed by the function
     * \param[in]
     *     present_bytes The amount of bytes already available in
     *     present_data, needs to be updated if data from there is
     *     processed by the function
     * \param[in]
     *     missing_bytes The amount of bytes additionally present
     *     at the client, can be obtained via MsgRead(), needs to
     *     be updated if data from there is processed by the
     *     function
     * \param[in]
     *     read_offset Where to find \c missing_bytes bytes in the
     *     clients remote buffer, needs to be updated if data from the
     *     client is processed
     * \return
     *     error code or EOK on success
     **/
    int readClientMsg(
        int rcv_id,
        const char *& present_data,
        size_t &present_bytes,
        size_t &missing_bytes,
        size_t &read_offset) IPL_NOEXCEPT;

    /**
     * \brief
     *     Writes a single message into the buffer provided by the
     *     client in a read() call
     * \param[in]
     *     rcv_id The QNX rcv. ID for the client call
     * \param[in,out]
     *     client_buffer A pointer to the clients buffer where the
     *     message is to be written. The buffer position is to be
     *     updated by the function.
     * \param[in,out]
     *     buffer_size The amount of bytes left in \c
     *     client_buffer. This number is to be updated by the
     *     function
     * \return
     *     error core or EOK on success
     **/
    int writeClientMsg(
        int rcv_id,
        char *& client_buffer,
        size_t &buffer_size,
        size_t &write_offset) IPL_NOEXCEPT;

    virtual ReqWriteable getWriteable(const size_t bytes) IPL_NOEXCEPT;
    virtual bool sendWriteable(ReqWriteable &w) IPL_NOEXCEPT;

    /**
     * \brief
     *     Checks whether the transport is currently open and not
     *     disposed, raises apropriate error if not so

     *     If \c false is returned then errors have been raised by
     *     the function describing the problem and setError() has
     *     been called.
     *
     *     The caller should own an apropriate lock for the
     *     function being able to safely check the transport state.
     * \return
     *     \c true if the transport is operable \c false if not
     **/
    bool checkTransportOperable() IPL_NOEXCEPT;

    /**
     * \brief
     *     Central function to obtain suitable writeables for the
     *     resman transport

     *     Adds any necessary headers to a Writeable that is then
     *     able to hold \c bytes bytes of transport user data.
     * \return
     *     Writeable plus the Window that we've added. Check the
     *     Writeable for validBuf(), if it returns \c false then an
     *     error occured.
     **/
    ReqWriteable prepareWriteable(size_t bytes) IPL_NOEXCEPT;

    /**
     * \brief
     *     Actually send the given Readable to the client

     *     Common code for send(const size_t, IMsgWriter*) and
     *     sendWriteable()
     *
     *     The caller must not hold m_send_mutex for the call to
     *     work!
     **/
    bool send(Readable &r) IPL_NOEXCEPT;

    /**
     * \brief
     *     This function checks whether the transport is already
     *     published and if not then does so
     **/
    void checkPublishing(resmgr_context_t *ctp) IPL_NOEXCEPT;

protected: // data

    //! lock for sending operations
    osal::Mutex m_send_mutex;
    //! condition for sending operations
    osal::Condition m_send_condition;
    //! \brief
    //! a buffer for a single message that will be provided to
    //! clients read() call
    ipl::queue<Readable> m_send_msgs;
    //! \brief
    //! the number of bytes from m_send_data that have already been
    //! sent to the client during read() calls
    size_t m_cur_tx_msg_pos;
    //! if a pending read() is present the ID is stored here
    int m_send_rcvid;
    //! priority of the client's read() that is pending, if any
    int16_t m_send_prio;

    //! lock for receive operations
    osal::Mutex m_receive_mutex;
    //! condition for receive operations
    osal::Condition m_receive_condition;
    //! currently worked on receive message from a write() call
    Writeable m_cur_rx_msg;
    //! \brief
    //! position where to write the next incoming data for
    //! m_cur_rx_msg or m_cur_rx_msg_size
    size_t m_cur_rx_msg_pos;
    //! used for reading in the header in readClientMsg
    MessageSizeSerialization m_cur_rx_msg_size;
    //! \brief
    //! queue of messages received and cached from client's write
    //! call
    ipl::queue<Readable> m_received_msgs;
    //! if a pending write() is present the ID is stored here
    int m_receive_rcvid;
    //! priority of the client's write() that is pending, if any
    int16_t m_receive_prio;

    //! a general lock for the transport aside from tx/rx operation
    osal::Mutex m_tp_lock;
    //! \brief
    //! set to true if the transport has already been disposed
    volatile bool m_disposed;
    //! the client's visible open state (set after open()/close() is called)
    volatile bool m_open;
    //! whether we've published ourselves at m_factory
    bool m_published;

    //! amount of bytes cached on rx
    size_t m_rx_cached;
    //! amount of bytes cached on tx
    size_t m_tx_cached;

    //! maximum number of bytes to cache on rx
    const size_t m_rx_buffer_size;
    //! maximum number of bytes to cache on tx
    const size_t m_tx_buffer_size;

    //! the factory that created us
    QnxResourceManagerTransportFactoryUnderwear::UnderwearPtr m_factory;

    PacketSizeLimit m_limit;
    PeerInfoPtr     m_peer_info;
};

}  // end of namespace transport
}  // end of namespace util

#endif
