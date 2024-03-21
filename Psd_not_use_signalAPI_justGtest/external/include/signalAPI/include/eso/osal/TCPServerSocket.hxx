/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_TCPSERVERSOCKET_HXX
#define OSAL_TCPSERVERSOCKET_HXX

#include <ipl_config.h>

#include <osal/IPSocket.hxx>
#include <osal/TCPSocket.hxx>

namespace osal
{

/**
 * \brief
 *    Specialization of an IPSocket that implements connection
 *    oriented sockets based on the TCP/IP protocol. This variant is
 *    only used for server sockets.

 *    The TCPServerSocket is bound to a local address, enters a
 *    listening state and then is able to accept connections that fork
 *    the actual socket connection by means of a new socket object.
 * \note
 *    The TCP/IP protocol provides a safe way of network communication
 *    by guaranteeing data delivery in the correct order (i.e. in the
 *    order it was sent by sender), no lost data and according error
 *    detections.
 *
 *    In the background the TCP/IP protocol realises a complex
 *    communication scheme including things like flow control. This
 *    complex implementation increases the amount of resources (memory
 *    as well as computation time) needed in the system during
 *    communication. Also there is a higher amount of protocol
 *    overhead and thus the achieved data rate on the communication
 *    channel may be smaller then with simpler protocols.
 *
 *    On the other hand it makes the life much easier for the
 *    application developer as there is no need for error handling,
 *    data reordering, data verification etc.
 **/
class OSAL_EXPORT TCPServerSocket :
    // inherit the IP based socket interface
    public IPSocket
{
public:
    /**
     * \brief
     *    Construct a new TCPServerSocket using either IP version
     *    4 or 6.

     *    If a network name instead of a raw IP address is given
     *    in p_address then a resolve operation will be performed.
     *    If this fails then an according error will be raised.
     *
     *    It will be immediatly checked wheter the given address
     *    can be transformed into a valid binary address
     *    representation. If this is not possible an according
     *    error will be raised.
     * \param[in]
     *     p_listen_address The address the server will act upon.
     *     If the address is NULL/empty then the server will listen
     *     on all available IP based interfaces on the given port
     *     number. The port number must not be zero.
     * \param[in]
     *    p_blocking Wheter this should be a blocking or a
     *    non-blocking socket. This affect all socket system
     *    operations including acceptConnection().
     * \param[in]
     *    p_reuse This boolean determines wheter the system should
     *    allow to use the given ip:port pair immediatly again
     *    even if there might still be coming in packets from a
     *    previous connection. If this is the case and reuse is
     *    set to false then an error is raised.
     * \errorindicator
     *    via isValid()
     * \errors
     *    see IPSocket(), Socket::setSendBuffer(), plus:
     *
     *    SysError with IDs:
     *
     *    - PERMISSION_DENIED if not allowed to bind to address \c
     *    p_src
     *    - SYSTEM_RESSOURCES_EXHAUSTED if ressources other than
     *    memory are lacking (e.g. maximum number of open files
     *    reached)
     *    - OUT_OF_MEMORY if not enough memory ressources are left
     *    (e.g. kernel/stack buffers)
     *    - UNKNOWN_ERROR on other occasions (e.g. setting of
     *    non-blocking mode failed if p_blocking is set to false)
     *
     *    Socket::Error with IDs:
     *
     *    - CREATE_FAILED on prinicple, internal problems to
     *    create the underlying socket descriptor
     **/
    TCPServerSocket(const IPAddress &p_listen_address,
        const bool p_blocking, const bool p_reuse = false,
        const IPProtocolVersion p_ip_version = IPV4) IPL_NOEXCEPT;

    /**
     * \brief
     *    Nothing special. The majority of destruction work is
     *    done by ~IPSocket().
     * \pre
     *    If the socket is in state OPEN then it needs to be
     *    closed via close() before it is destroyed.
     **/
    ~TCPServerSocket() IPL_NOEXCEPT;

    /**
     * \brief
     *    Sets the TCPServerSocket into a listening mode that
     *    allows clients to connect to the ServerSocket.

     *    After successful return the socket will be in a
     *    listening state reflected via the OPEN socket state.
     *
     *    Before entering the listening state the socket will be
     *    bound to the listen address specified at construction
     *    time. Thus if this binding is not possible an errors is
     *    raised.
     *
     *    In this state clients are allowed to enqueue for
     *    connection establishement on the given IP address:port
     *    pair. It does not mean that those connection attempts
     *    will succeed. They will only be honoured if you call
     *    acceptConnection() in time.
     *
     *    Before a ServerSocket is in listening state it will not
     *    be possible for clients to establish any kind of
     *    connection with the ServerSocket.
     * \param[in]
     *    p_max_connections The maximum number of connections that
     *    may be queued in the system as pending to be accepted.
     *    If this maximum number of pending connections is reached
     *    then additional connection requests are rejected or
     *    ignored depending on the actual implementation.
     *    <br>
     *    If you pass zero for this parameter then the system
     *    _may_ choose a minimum number of allowable connections
     *    to be queued in for the socket. It is discouraged to
     *    count on this, however.
     * \note
     *    The OPEN state once reached, cannot be disabled again
     *    except via closing the ServerSocket.
     * \note
     *    On error the socket becomes invalid and enters state
     *    DEAD.
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
     **/
    void enableListen(const uint32_t p_max_connections) IPL_NOEXCEPT;

    /**
     * \brief
     *    For a TCP ServerSocket that reached the OPEN state (via
     *    enableListen()) this function allows to accept an
     *    incoming connection request.

     *    After listen has been enabled for a TCPServerSocket via
     *    enableListen() you may accept incoming connections via
     *    this function call. If this is a blocking socket then
     *    this function call blocks until an actual connection
     *    request is coming in. Otherwise, if no connection
     *    request is currently pending then an invalid Description
     *    is returned.
     *
     *    If this call returns a valid description then it can be
     *    used to construct a TCPSocket object with it. That
     *    socket then represents the communication endpoint for
     *    the newly created connection. This socket object can
     *    then be used for normal communication with the new
     *    client.
     * \pre
     *    enableListen() has been successfully called, i.e. the
     *    ServerSocket is in state OPEN.
     * \errorindicator
     *    via hasError()
     * \errors
     *    ipl::CommonError with IDs:
     *
     *    - INVALID_LOGIC if getState() != OPEN
     *
     *    SysError with IDs:
     *
     *    - INTEGRITY_ERROR on severe, internal errors
     *    - SYSTEM_RESSOURCES_EXHAUSTED if the maximum of open
     *    files has been reached
     *    - OUT_OF_MEMORY if the required data structures could
     *    not be allocated in kernel/stack
     *
     *    Socket::Error with IDs:
     *
     *    - SOCKET_INVALID if the underlying socket is invalid for
     *    some reason
     *    - CONNECTION_CLOSED if a started connection attempt has
     *    been aborted unexpectedly (by the peer or locally by
     *    closing the server socket)
     *    - COMMUNICATON_FAILED on network or protocol specific
     *    errors during connection attempt
     *    - PERMISSION_DENIED if firewall rules prevent connection
     *    - NO_NETWORK if on QNX the TCP/IP stack is not
     *    running/present.
     * \return
     *    An invalid Description object if the ServerSocket is in
     *    non-blocking mode and there are currently no pending
     *    connection requests. Otherwise a valid Description
     *    object representing a new client connection.
     **/
    TCPSocket::Description acceptConnection() IPL_NOEXCEPT;

    inline size_t maxTxSize() const IPL_NOEXCEPT override
    {
        // send buffer size limits maximum send (usually)
        const size_t BUFSIZE = this->getSendBuffer();
        if( this->hasError() ) // BRANCH_COVERAGE_UNTESTABLE
        {
            // don't know what to do but return zero
            ipl_error.ack();
        }

        return BUFSIZE > TCPSocket::MAX_SEGMENT_SIZE ?
            TCPSocket::MAX_SEGMENT_SIZE : BUFSIZE;
    }

#ifdef IPL_OS_WIN32
    // on win32 shutdown on server socket is not possible (returns
    // ENOTCONN).  On other OS, however this is the only possibility
    // to cancel blocking accept calls.  We need to make this
    // transparent. Win32 cancels blocking accept with simple
    // close(false).
    bool close(const bool discard_pending=false) IPL_NOEXCEPT
    { return IPSocket::close(false); }
#endif

protected:
    /**
     * \brief
     *    Leaf implementation of performRead to prevent read on
     *    server socket
     **/
    virtual bool performRead(void* const p_read_buffer,
        const size_t p_max_bytes, size_t &p_bytes_read) IPL_NOEXCEPT;

    /**
     * \brief
     *    Leaf implementation of performWrite to prevent write on
     *    server socket
     **/
    virtual bool performWrite(const void* const p_write_buffer,
        const size_t p_max_bytes, size_t &p_bytes_written) IPL_NOEXCEPT;

    /**
     * \brief
     *    Leaf implementation of performFlush to prevent flush on
     *    server socket
     **/
    virtual bool performFlush() IPL_NOEXCEPT;
}; // end class

} // end namespace

#endif // OSAL_TCPSERVERSOCKET_HXX
