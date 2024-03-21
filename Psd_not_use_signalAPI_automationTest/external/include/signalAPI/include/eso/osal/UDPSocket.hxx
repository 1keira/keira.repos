/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_UDPSOCKET_HXX
#define OSAL_UDPSOCKET_HXX

#include <ipl_config.h>

#include <osal/IPSocket.hxx>

namespace osal
{

/*!
    \brief \b DO \b NOT \b USE, this does not do what you think,
    use RealUDPSocket instead

    IPSocket is connection oriented, UDP not. This class provides
    UDP "connections, kind of", i.e. it is unsuited for most genuine UDP
    usecases while the better choice for connections is TCPSocket.

      Specialization of an IPSocket that implements connectionless
      datagram sockets based on the UDP/IP protocol

 *    The UDP/IP protocol provides a lightweight method of
 *    communication. In doesn't build up a logical connection between
 *    communication partners. Thus you can immediatly start sending
 *    data to some peer without a previous connection establishement
 *    of any kind.
 *
 *    Due to the lack of any complex protocol logic the communication
 *    via UDP/IP is quite efficient in terms of needed system
 *    ressources and is able to achieve a high bandwidth on the
 *    network.
 *
 *    The downside is that the UDPSocket doesn't give you guarantees
 *    for anything much. It is neither sure whether data reaches your
 *    peer at all nor is it possible to keep the order of network
 *    packets sent over the network.
 *
 *    Thus in this case the application has to deal with this matters
 *    to some extend. It must expect data to be missing from time to
 *    time and it has to be able to handle mixed up order when
 *    receiving packets from the network. Another effect can be that
 *    duplicated packets can be received.
 * \note
 *    On UDP/IP all read operations usually just return one complete
 *    UDP/IP packet. If the packet was too big for the userspace
 *    buffer then only a partial packet is returned and the rest
 *    later.
 **/
class OSAL_EXPORT UDPSocket :
    // inherit the IP based socket interface
    public IPSocket
{
public:
    /**
     * \brief
     *    Construct a new UDPSocket using the specified IP version
     *    4 or 6

     *    If a network name instead of a raw IP address is given
     *    in p_address then a resolve operation will be performed.
     *    If this fails then an an according error will be raised.
     * \param[in]
     *    p_blocking Whether this should be a blocking or a
     *    non-blocking socket. Note that you can only have
     *    blocking semantics on a non-blocking socket via select.
     * \param[in]
     *    p_input_buffer The size of a userspace input/read
     *    buffer, if any (zero to disable buffering). This value
     *    is passed on to the Socket base class.
     * \param[in]
     *    p_output_buffer The size of a userspace output/write
     *    buffer, if any (zero to disable buffering). This value
     *    is passed on to the Socket base class.
     * \param[in]
     *    p_src The local address:port to operate on. If address
     *    and/or port is NULL then a suitable address and/or port
     *    is chosen by the system. The address may be the
     *    appropriate IP numbers and dots notation or a hostname
     *    alternatively.  If it is a hostname then a resolve
     *    operation will be performed. If the resolve operation
     *    fails or is ambigous then an exception will be thrown.
     *    See IPSocket::IPSocket().
     * \param[in]
     *    p_dst The peer address:port to operate on. Address and
     *    port must not be NULL/0. Only data from this address
     *    will be received and all sent data goes to this address.
     * \param[in]
     *    p_ip_version The IP protocol version to use. Default is
     *    IPv4.
     * \note
     *    The operation address can only be set at construction
     *    time. It cannot be changed during runtime any more. This
     *    is an explicit design decision to avoid too much
     *    interface and logic confusion.
     * \note
     *    If you don't care or know what to use for the local
     *    address:port then you can simply specify NULL for
     *    p_src.address and/or p_src.port to use "any" suitable
     *    src address and/or port.
     *
     *    This nice trick doesn't work on the p_dst though, sorry.
     * \warning
     *    The use of buffering will change the behaviour of
     *    read/write on the socket.  As individual data
     *    transmissions are accumulated for write(...) a single
     *    datagram received by the peer will no longer be a single
     *    message but may be multiple messages.
     *
     *    On the read() side instead the buffering will give no
     *    big advantage as the OS will only return complete
     *    datagrams to us an not the maximum data that could be
     *    currently retrieved. However if you pass in a too small
     *    buffer then the received datagram will not be truncated
     *    but the "to be truncated part" will be kept in the
     *    userspace input buffer to be collected later on.
     * \errorindicator
     *    via isValid()
     * \errors
     *    see IPSocket(), plus:
     *
     *    SysError with IDs:
     *
     *    - PERMISSION_DENIED if not allowed to bind to address \c
     *    p_src
     *    - SYSTEM_RESSOURCES_EXHAUSTED if ressources other than
     *    memory are lacking (e.g. maximum number of open files
     *    reached)
     *    - OUT_OF_MEMORY if not enough memory ressources are left
     *    (e.g. kernel/heap buffers)
     *    - UNKNOWN_ERROR on other occasions (e.g. setting of
     *    non-blocking mode failed if p_blocking is set to false)
     *
     *    Socket::Error with IDs:
     *
     *    - CREATE_FAILED on prinicple, internal problems to
     *    create the underlying socket descriptor
     **/
    UDPSocket(
        const bool p_blocking,
        const size_t p_input_buffer,
        const size_t p_output_buffer,
        const IPAddress &p_src,
        const IPAddress &p_dst,
        const IPProtocolVersion p_ip_version = IPV4) IPL_NOEXCEPT;

    /**
     * \brief
     *    Nothing special. Destruction work is done in ~IPSocket()
     * \pre
     *    The socket communication must be ceased prior to
     *    destruction by calling close(). This is to motivate the
     *    definition of a clear lifecycle model of the socket
     *    communication.
     **/
    ~UDPSocket() IPL_NOEXCEPT;

    /**
     * \brief
     *    Binds and opens the UDPSocket for communication to the
     *    peer address

     *    As UDP doesn't realise connections this function call
     *    simply sets up a binding to the local and remote
     *    addresses that causes the socket only to receive packets
     *    from the peer address any more and only send packets to
     *    the peer address accordingly.
     *
     *    For UDP sockets communicating with different addresses/ports
     *    at the same time use RealUDPSocket.
     *
     *    Note that binding can only be performed once for a
     *    socket. I.e. if you open the socket, change socket
     *    options regarding bind then those options won't be in
     *    effect.
     * \pre
     *    Socket must be in state INACTIVE.
     * \post
     *    Socket is in state OPEN and ready to be used for
     *    communication.
     * \note
     *    On error the socket will be become invalid and enters
     *    state DEAD.
     * \errorindicator
     *    via hasError()
     * \errors
     *    ipl::CommonError with IDs:
     *
     *    - INVALID_USAGE if the socket is not in state INACTIVE
     *
     *    SysError with IDs:
     *
     *    - PERMISSION_DENIED if the caller doesn't have required
     *    privileges to perform the operation or firewall rules
     *    prevented the access
     *    - INTEGRITY_ERROR if severe internal problems occur
     *    - SYSTEM_RESSOURCES_EXHAUSTED if ressources like stack
     *    buffers are missing or the maximum number of open files
     *    has been reached.
     *    - OUT_OF_MEMORY if memory ressources are exhausted in
     *    kernel/stack
     *
     *    Socket::Error with IDs:
     *
     *    - ADDRESS_IN_USE if the local IP address is already in
     *    use by another socket in the system
     *    - ADDRESS_INVALID if the local IP address has no
     *    matching network interface or the address is not local
     *    - NO_PEER if the peer is not reachable but the network
     *    would be available in principle. Or the peer is
     *    reachable but no application is active at the given
     *    address.
     *    - NO_NETWORK if the network interface is down or the
     *    target network is not reachable due to other reasons.
     **/
    void open() IPL_NOEXCEPT;

    /**
     * \brief
     *    This option allows to enable or disable broadcast
     *    transmission and reception via the UDPSocket

     *    If you want to be able to receive and send broadcast
     *    messages via UDP then you have to enable this feature
     *    via this option first.
     *
     *    To send out a broadcast message you need to specify a
     *    broadcast address for the peer address. If you specify a
     *    broadcast address but don't enable broadcast then the
     *    system returns an error.
     * \note
     *    If broadcast semantics are needed for application
     *    purposes then it is more efficient to use a multicast
     *    group. This feature is not yet implemented.  Please ask
     *    whoever is currently responsible for OSAL development
     *    about it.
     * \param[in]
     *    enable true if broadcast support should be enabled,
     *    false otherwise.
     * \errorindicator
     *    via hasError()
     * \errors
     *    see Socket::setSendBuffer()
     **/
    void setBroadcast(const bool enable) IPL_NOEXCEPT;

    /**
     * \brief
     *    Retrieves the current broadcast setting from the system.
     * \return
     *    true if broadcast support is currently enabled for this
     *    socket, false otherwise.
     * \errorindicator
     *    via hasError()
     * \errors
     *    see Socket::getSendBuffer()
     **/
    bool getBroadcast() const IPL_NOEXCEPT;

    /**
     * \brief
     *    Retrieves the current multicast state of the socket.
     * \return
     *    true if socket is in multicast mode, false otherwise
     **/
    bool getMulticast() const IPL_NOEXCEPT {return m_is_multicast;}

    size_t maxTxSize() const IPL_NOEXCEPT override
    {
        // send buffer size limits maximum send (usually)
        const size_t BUFSIZE = this->getSendBuffer();
        if( this->hasError() ) // BRANCH_COVERAGE_UNTESTABLE
        {
            // don't know what to do then. will return zero.
            ipl_error.ack();
        }

        return BUFSIZE > MAX_TEL_SIZE ? MAX_TEL_SIZE : BUFSIZE;
    }

protected: // constants
    //! \brief
    //!    Maximum UDP telegram size (hope this isn't PD or IP-dependent)
    //!    (this is a hard limit i.e. bigger write(...) calls will fail
    static const size_t MAX_TEL_SIZE = 65507;

    // overwrite for using sendto()
    bool performWrite(
        const void* const p_write_buffer,
        const size_t p_max_bytes,
        size_t &p_bytes_written) IPL_NOEXCEPT;

    bool m_is_multicast;
}; // end class

} // end namespace

#endif
