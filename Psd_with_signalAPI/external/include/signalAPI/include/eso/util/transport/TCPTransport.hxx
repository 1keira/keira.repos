/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_TCPTRANSPORT_HXX
#define UTIL_TCPTRANSPORT_HXX

#include <ipl_config.h>
#include <util/util_dso.h>

#include <common/ByteOrder.hxx>
#include <common/align.hxx>

#include <util/transport/ITransport.hxx>
#include <util/transport/PacketSizeLimit.hxx>
#include <util/transport/StreamFraming.hxx>
#include <util/transport/StreamIOHandler.hxx>
#include <util/transport/DefaultBufferAllocator.hxx>
#include <util/transport/factory/TransportConfig.hxx>
#include <util/transport/factory/tcp.hxx>
#include <util/transport/ISelectable.hxx>
#include <osal/TCPSocket.hxx>

namespace util
{
namespace transport
{


/**
 * \brief
 *     Implementation of a transport facility for TCP communication
**/
class UTIL_EXPORT TCPTransport : public IDisposableTransport
{
public: // methods

    /**
     * \brief
     *     Constructor from a transport-url

     * \errorindicator
     *      via isValid()
     * \errors
     *      errors as indicated by osal::TCPSocket()
     **/
    TCPTransport(const ipl::string& url) IPL_NOEXCEPT;

    /**
     * \brief
     *     Constructor from a socket descriptor

     *     Use for in a server context where accept returns socket descriptors
     *     when clients connect
     *
     * \param socket
     *     The socket descriptor
     * \param[in] config
     *     a configuration string for the server socket that produced the description
     *     used in error messages
     * \errorindicator
     *     via isValid()
     **/
    TCPTransport(const osal::TCPSocket::Description& socket, const ipl::string& config) IPL_NOEXCEPT;

    /**
     * \brief
     *     Removes any ressources associated with the transport
     * \preconds
     *     The transports needs to be closed before the destructor
     *     runs
     **/
    ~TCPTransport() IPL_NOEXCEPT;

    TCPTransport() IPL_NOEXCEPT = delete;
    TCPTransport(const TCPTransport&) IPL_NOEXCEPT = delete;
    TCPTransport(TCPTransport&&) IPL_NOEXCEPT = delete;
    TCPTransport& operator=(const TCPTransport&) IPL_NOEXCEPT = delete;
    TCPTransport& operator=(TCPTransport&&) IPL_NOEXCEPT = delete;

    bool isValid() const IPL_NOEXCEPT { return m_valid; }

public: // implementation of transport interface

    virtual void open() IPL_NOEXCEPT override;

    /**
     * \see
     *     util::ITransport::close()
     * \errorindicator
     *     via return code instead of via hasError() to avoid race
     *     condition with parallel send/receive calls regarding
     *     error indication
     * \return
     *     true on error, false otherwise
     **/
    virtual bool close() IPL_NOEXCEPT override;

    /**
     * \brief
     *     Call \c writer with a buffer suitable to hold \c p_size
     *     bytes
     * \param[in] p_size
     *    is the number of bytes to be send
     * \param[in] writer
     *     The Writer that will be provided with a suitable buffer
    */
    virtual bool send(const size_t p_size, IMsgWriter *writer) IPL_NOEXCEPT override;

    //! \brief
    //! variant of send(const size_t, IMsgWriter*) for asynchronous
    //! writes
    virtual bool send(const size_t p_size, MsgWriterPtr writer) IPL_NOEXCEPT override;

    virtual Readable receive() IPL_NOEXCEPT override;

    //! perform a flush on the transport channel
    virtual void flush() IPL_NOEXCEPT override;

    //! request the state of the transport. It's not thread safe
    virtual State getState() const IPL_NOEXCEPT override
    { return m_state; }

    ///////////////////////////////
    // transport feature queries //
    ///////////////////////////////

    //! TCP detects peer reset (under certain restrictions)
    inline virtual bool detectsPeerReset() const IPL_NOEXCEPT override { return true; };
    //! TCP is reliable
    inline virtual bool isReliable() const IPL_NOEXCEPT override { return true; };
    //! We've added record boundaries in the implementation
    inline virtual bool keepsRecordBoundaries() const IPL_NOEXCEPT override { return true; };
    //! \brief
    //! As we add record headers and tcp doesn't reorder we can send
    //! very long messages
    virtual size_t maxMsgSize() const IPL_NOEXCEPT override
    { return UINT32_MAX; };

    virtual PeerInfoPtr getPeerInfo() const IPL_NOEXCEPT override;

    virtual void enablePacketSizeLimit(size_t limit) IPL_NOEXCEPT override;
    virtual void disablePacketSizeLimit() IPL_NOEXCEPT override;

public: // IDisposable interface
    virtual void dispose() override;

    // ISelectable interface
    bool isSelectableBy (size_t index) const IPL_NOEXCEPT override {
        return index == util::transport::ISelectable::SOCKET_INDEX;
    }

    SelectableResource getResource() const IPL_NOEXCEPT override {
        if ( m_socket ) {
            return SelectableResource(SocketPair{m_socket->getHandle().rxfd, m_socket->getHandle().txfd});
        }
        // construct from invalid value in default-constructed handle
        return SelectableResource(SocketPair{osal::SocketHandle().rxfd, osal::SocketHandle().txfd});
    }

protected: // ITransport interface
    virtual ReqWriteable getWriteable(const size_t p_size) IPL_NOEXCEPT override;

    virtual bool sendWriteable(ReqWriteable &w) IPL_NOEXCEPT override;

protected:

    tcp::Param              m_param;
    osal::TCPSocket*        m_socket;

    StreamIOHandler*        m_io;
    StreamFramingPtr        m_framing;
    DefaultBufferAllocator  m_allocator;

    // the current transport state
    State m_state;
    bool                    m_valid;
    PacketSizeLimit         m_limit;

    PeerInfoPtr             m_peer_info;
    bool                    m_is_spawn;
private:
    osal::TCPSocket* makeClientSocket() const IPL_NOEXCEPT;
    osal::TCPSocket* makeClientSocket( const osal::TCPSocket::Description& desc) const IPL_NOEXCEPT;
    bool configureSocket( osal::TCPSocket* socket ) const IPL_NOEXCEPT;
    bool connectSocket() IPL_NOEXCEPT;
    void closeSocket() IPL_NOEXCEPT;
    bool downgrade(StreamFraming::Buffered& buffered) IPL_NOEXCEPT;

}; // class

} // end namespace transport
} // end namespace util

#endif
