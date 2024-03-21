/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_UDPTRANSPORT_HXX
#define UTIL_UDPTRANSPORT_HXX

#include <ipl_config.h>

#include <util/util_dso.h>
#include <util/transport/ITransport.hxx>
#include <util/transport/PacketSizeLimit.hxx>
#include <osal/UDPSocket.hxx>

namespace util
{
namespace transport
{

/*!
    \brief \b DO \b NOT \b USE

    Transports are meant to be connection oriented and reliable but
    UDP is none of this. Use TCPTransport instead.

 *    Implementation of an IP-based transport facility using the UDP
 *    sockets

 *    Straightforward implementation of the transport interface for
 *    UDP sockets. No fancy additional logic will be provided.
 *    Unreliable UDP as usual. Record boundaries are kept as long as
 *    only the size reported by maxMsgSize is not exceeded.
**/
class UTIL_EXPORT UDPTransport :
    public IDisposableTransport
{
public: // methods

    /**
     * \brief
     *    Construct a new UDPTransport running locally at address
     *    p_src and communicating with address p_dst

     *    UDP socket communication will always be blocking (as
     *    required by Transport semantics), no userspace buffering
     *    will be applied (could be something that might be
     *    incorporated into Transport, however). IPv4 for
     *    addressing is assumed currently (would be no trouble to
     *    extend it to IPv6 some day).
     * \errorindicator
     *    via isValid()
     **/
    UDPTransport(const osal::UDPSocket::IPAddress &p_src,
        const osal::UDPSocket::IPAddress &p_dst) IPL_NOEXCEPT;

    /**
     * \brief
     *    Removes any ressources associated with the transport
     * \pre
     *    Transport needs to be in state NOT_OPEN or DEAD.
     **/
    ~UDPTransport() IPL_NOEXCEPT;

    bool isValid() const IPL_NOEXCEPT
    { return m_udp_socket.isValid(); }

public: // implementation of ITransport

    void open() IPL_NOEXCEPT;

    bool close() IPL_NOEXCEPT;

    /**
     * \brief
     *     send p_size bytes which are contained in the write via
     *     the transport
     * \param[in] p_size
     *    is the number of bytes to be send
     * \param[in] writer
     *    is the instance of the writer, which contains the bytes
     *    to be send
    **/
    virtual bool send(const size_t p_size, MsgWriterPtr writer) IPL_NOEXCEPT;

    /*
     * \brief
     *    send p_size bytes which are contained in the write via
     *    the transport
     * \param[in] p_size
     *    is the number of bytes to be send
     * \param[in] writer
     *    is the instance of the writer, which contains the bytes
     *    to be send
    */
    virtual bool send(const size_t p_size, IMsgWriter *riter) IPL_NOEXCEPT;

    /**
     * \brief
     *    Receive data from the transport and return a new buffer
     *    containing that data

     *    The amount of data received depend completely upon the
     *    properties and state of the actual transport
     *    facility. Especially if the transport doesn't keep
     *    records boundaries (i.e. keepsRecordBoundaries() ==
     *    false) then you might receive partial or multiple
     *    packets.
    */
    virtual Readable receive() IPL_NOEXCEPT;

    //! perform a flush on the transport channel
    virtual void flush() IPL_NOEXCEPT;

    //! request the state of the transport. It's not thread safe
    virtual State getState() const IPL_NOEXCEPT
    { return m_state; }

    // transport feature queries

    //! \brief
    //! UDP is not able to detect peer reset (on a per send basis it
    //! might be detected, though)
    virtual bool detectsPeerReset() const IPL_NOEXCEPT { return false; };
    //! UDP is not reliable, drops and reorders packets
    virtual bool isReliable() const IPL_NOEXCEPT { return false; };
    //! UDP keeps record boundaries within the limits of maxMsgSize()
    virtual bool keepsRecordBoundaries() const IPL_NOEXCEPT { return true; };
    //! \brief
    //! the maximum message size is only valid on open sockets. The
    //! size may vary from socket to socket due to differences in
    //! internal buffering.
    virtual size_t maxMsgSize() const IPL_NOEXCEPT;

    virtual PeerInfoPtr getPeerInfo() const IPL_NOEXCEPT;

    virtual void enablePacketSizeLimit(size_t limit) IPL_NOEXCEPT;
    virtual void disablePacketSizeLimit() IPL_NOEXCEPT;

public:  // implementation of IDisposable
    virtual void dispose();

protected: // part of transport interface

    virtual ReqWriteable getWriteable(const size_t p_size) IPL_NOEXCEPT;
    virtual bool sendWriteable(ReqWriteable &w) IPL_NOEXCEPT;

protected: // member functions
    //! Actually send the given Readable on m_udp_socket
    bool sendUDP(const Readable &buf) IPL_NOEXCEPT;

protected: // data

    //! The UDP socket our transport is running over
    osal::UDPSocket m_udp_socket;

    //! cached maximum tx size
    const size_t m_max_tx_size;

    //! the current transport state
    State m_state;

    PacketSizeLimit    m_limit;

    PeerInfoPtr        m_peer_info;

}; // class

} // end namespace transport
} // end namespace util

#endif
