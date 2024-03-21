/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_TCPSOCKET_HXX
#define OSAL_TCPSOCKET_HXX

#include <osal/IPSocket.hxx>

namespace osal
{

/**
 * \brief
 *     Specialization of an IPSocket that implements connection
 *     oriented sockets based on the TCP/IP protocol

 *     The TCPSocket can either directly connect to a peer TCP server
 *     or it can be obtained from a TCPServerSocket via the
 *     acceptConnection() function. It can not act itself as a server.
 * \note
 *     The TCP/IP protocol provides a safe way of network communication
 *     by guaranteeing data delivery in the correct order (i.e. in the
 *     order it was sent by sender), no lost data and according error
 *     detections.
 *
 *     In the background the TCP/IP protocol realises a complex
 *     communication scheme including things like flow control. This
 *     complex implementation increases the amount of resources (memory
 *     as well as computation time) needed in the system during
 *     communication. Also there is a higher amount of protocol
 *     overhead and thus the achieved data rate on the communication
 *     channel may be smaller then with simpler protocols.
 *
 *     On the other hand it makes the life much easier for the
 *     application developer as there is no need for error handling,
 *     data reordering, data verification etc.
 **/
class OSAL_EXPORT TCPSocket :
    // inherit the IP based socket interface
    public IPSocket
{
    // friendships
    friend class TCPServerSocket;
public: // types
    //! \brief
    //!    An opaque socket description for already existing
    //!    sockets returned from TCPServerSocket
    class Description;

    /**
     * \brief
     *     Settings for the TCP keepalive option used at
     *     setKeepalive()
     *
     * \link2req{satisfies,req~FW_OSAL_TCP_KEEPALIVE~1}
     * \link2req{satisfies,req~FW_UTIL_KEEPALIVE_KEEPCNT_DEFAULT_VALUE~1}
     * \link2req{satisfies,req~FW_UTIL_KEEPALIVE_KEEPIDLE_DEFAULT_VALUE~1}
     * \link2req{satisfies,req~FW_UTIL_KEEPALIVE_KEEPINTVL_DEFAULT_VALUE~1}
     **/
    struct KeepaliveSettings
    {
        //! whether keepalive algorithm is enabled or not
        bool enabled{true};
        //! \brief
        //! the time in seconds of no data being processed over
        //! the socket before the keepalive algorithm starts
        //! working
        size_t idle_time{5};
        //! \brief
        //! the number of probes that will be sent out after \c
        //! idle_time seconds before the connection is dropped
        size_t probe_count{5};
        //! \brief
        //! the number of seconds that is waited between
        //! individual probes sent
        size_t probe_interval{1};

        KeepaliveSettings() = default;

        explicit KeepaliveSettings(bool enable)
        : enabled{enable}
        {}

        KeepaliveSettings(bool enable
                        , size_t idle_time
                        , size_t probe_count
                        , size_t probe_interval)
        : enabled{enable}
        , idle_time{idle_time}
        , probe_count{probe_count}
        , probe_interval{probe_interval}
        {}

        bool operator==(const KeepaliveSettings& other) const {
            return
                (enabled == other.enabled)
                && (idle_time == other.idle_time)
                && (probe_count == other.probe_count)
                && (probe_interval == other.probe_interval)
                ;
        }

        bool operator!=(const KeepaliveSettings& other) const {
            return !operator==(other);
        }

    };

public: // functions

    /**
     * \brief
     *     Construct a new TCPSocket of type ServerSocket acting as
     *     a client and using either IP version 4 or 6

     *     If a network name instead of a raw IP address is given
     *     in p_address then a resolve operation will be performed.
     *     If this fails then an according error will be raised.
     * \param[in]
     *     p_src The local address:port to operate on. If address
     *     and/or port is NULL then a suitable address is chosen by
     *     the system.
     * \param[in]
     *     p_dst The peer address:port to operate on.
     * \param[in]
     *     p_blocking Wheter this should be a blocking or a
     *     non-blocking socket. This affect all socket system
     *     operations including accept().
     * \param[in]
     *     p_ip_version The IP protocol version to use. Default is
     *     IPv4.
     * \param[in]
     *     p_reuse If set to \c true then if the given address \c
     *     p_src might still get packets from a previous connection
     *     then opening the new socket on it still succeeds.
     *     Otherwise opening the new socket will fail in that
     *     situation.
     * \note
     *     The operation address can only be set at construction
     *     time. It cannot be changed during runtime any more. This
     *     is an explicit design decision to avoid too much
     *     interface and logic confusion.
     * \note
     *     If you don't care or know what the local address:port to
     *     use are then you can simply specify NULL for
     *     p_src.address and/or p_src.port to use "any" suitable
     *     src address and/or port.
     *
     *     This nice trick doesn't work on the p_dst though, sorry.
     * \errorindicator
     *     via isValid()
     * \errors
     *     see IPSocket(), Socket::setSendBuffer(), plus:
     *
     *     SysError with IDs:
     *
     *     - PERMISSION_DENIED if not allowed to bind to address \c
     *     p_src
     *     - SYSTEM_RESSOURCES_EXHAUSTED if ressources other than
     *     memory are lacking (e.g. maximum number of open files
     *     reached)
     *     - OUT_OF_MEMORY if not enough memory ressources are left
     *     (e.g. kernel/stack buffers)
     *     - UNKNOWN_ERROR on other occasions (e.g. setting of
     *     non-blocking mode failed if p_blocking is set to false)
     *
     *     Socket::Error with IDs:
     *
     *     - CREATE_FAILED on prinicple, internal problems to
     *     create the underlying socket descriptor
     **/
    TCPSocket(
        const bool p_blocking, const size_t p_input_buffer,
        const size_t p_output_buffer,
        const IPAddress &p_src, const IPAddress &p_dst,
        const bool p_reuse,
        const IPProtocolVersion p_ip_version = IPV4);

    /**
     * \brief
     *     Does the same as TCPSocket(const bool, const
     *     size_t, const size_t, const IPAddress&,
     *     const IPAddress&, const bool, const IPProtocolVersion),
     *     but takes a description object provided from a
     *     TCPServerSocket

     *     TCPServerSocket returns \c Description objects upon
     *     successful calls to acceptConnection(). These objects
     *     can be used to construct an actual TCPSocket object from
     *     it.
     * \note
     *     On success \c p_desc will be "consumed" i.e. it becomes
     *     invalid, because it cannot be used more than once to
     *     create a TCPSocket object.
     * \errorindicator
     *     via isValid()
     * \errors
     *     ipl::CommonError with IDs:
     *
     *     - INVALID_USAGE if p_desc is not valid
     *
     *     for other errors see Socket::setSendBuffer()
     **/
    TCPSocket(const bool p_blocking, const size_t p_input_buffer,
        const size_t p_output_buffer, const Description &p_desc);

    /**
     * \brief
     *     The majority of destruction work is done by ~IPSocket().
     * \pre
     *     If the socket is in state OPEN then communication must
     *     be ceased prior to destruction. This is to motivate the
     *     definition of a clear lifecycle model of the socket
     *     communication. This is done via close().
     **/
    ~TCPSocket();

    /**
     * \brief
     *     Connect to the peer address on TCP/IP level

     *     Establishes the TCP/IP connection to the remote address.
     *
     *     The remote host must be listening at the specified
     *     address:port for the connection to be successful.
     *
     *     Only after the connection has been successfully
     *     established communication will be possible.
     * \pre
     *     Socket must be in state INACTIVE
     * \post
     *     Socket will be in state CONNECTED. Communication will be
     *     possible.
     * \return
     *     A boolean return value that indicates wheter the
     *     connection is going to be established asynchronously. If
     *     true is returned then this is the case. This condition
     *     may frequently occur if you have a TCPSocket in
     *     non-blocking mode.  It may also occur on a blocking
     *     TCPSocket under certain conditions involving interrupted
     *     system calls.
     *     <br>
     *     In any case if true is returned then the connection
     *     result cannot be considered determined. The application
     *     can check the connection result check in a blocking or
     *     non-blocking way via the Socket::selectSocket function.
     *     As soon as the socket is marked as writable the
     *     connection can be considered established successfully.
     * \note
     *     on error the socket will be kept in the state INACTIVE
     *     and another connect() attempt can be made at a later
     *     time
     * \errorindicator
     *     via hasError()
     * \errors
     *     ipl::CommonError with IDs:
     *
     *     - INVALID_USAGE if the socket is not in state INACTIVE
     *
     *     SysError with IDs:
     *
     *     - PERMISSION_DENIED if the caller doesn't have required
     *     privileges to perform the operation or firewall rules
     *     prevented the access
     *     - INTEGRITY_ERROR if severe internal problems occur
     *     - SYSTEM_RESSOURCES_EXHAUSTED if ressources like stack
     *     buffers are missing or the maximum number of open files
     *     has been reached.
     *     - OUT_OF_MEMORY if memory ressources are exhausted in
     *     kernel/stack
     *
     *     Socket::Error with IDs:
     *
     *     - ADDRESS_IN_USE if the local IP address is already in
     *     use by another socket in the system
     *     - ADDRESS_INVALID if the local IP address has no
     *     matching network interface or the address is not local,
     *     or if destination IP address is not available through
     *     any networks
     *     - CONNRESET if the peer canceled the connection before
     *     it could be established.
     *     - NO_PEER if the peer is not reachable but the network
     *     would be available in principle. Or the peer is
     *     reachable but no application is active at the given
     *     address.
     *     - NO_NETWORK if the network interface is down or the
     *     target network is not reachable due to other reasons.
     **/
    bool connect() override;

    /**
     * \brief
     *     Enable or disable the TCP "Nagle" algorithm

     *     The TCP "Nagle" algorithm is responsible for TCP logic
     *     that causes small amount of data not to be transmitted
     *     immediatly. Instead the data is only sent out when more
     *     data is gathered for the connection or a timeout applies
     *     such that the small data portion is sent out.
     *
     *     This behaviour is bad in some application contexts.
     *     Imagine an interactive shell session running over a TCP
     *     connection on a network. Here single characters have to
     *     be sent to the peer quickly such that the user gets
     *     feedback.
     *
     *     Also if you know in general that you will not send out
     *     more data for some time then it might be sensible to
     *     active this option permanently or only for a certain
     *     time frame depending on the application context.
     *
     *     On the other hand of course the "Nagle" algorithm has
     *     its reasons for doing this. In utilizes the network
     *     better and you should only disable this logic if you
     *     know you have a different network access pattern.
     *
     *     Note that the timeout for small data transmissions with
     *     Nagle active can reach several seconds.
     *
     *     The initial default setting is that the "Nagle"
     *     algorithm is enabled.
     * \pre
     *     Socket must be in state INACTIVE or OPEN.
     * \param[in]
     *     p_val If set to true then the "nagle" algorithm will be
     *     disabled. Otherwise is will be enabled.
     * \errorindicator
     *     via hasError()
     * \errors
     *     see description of Socket::setSendBuffer()
     **/
    void setTCPNoDelay(const bool p_val);

    /**
     * \brief
     *     Enable keepalive algorithm for TCP
     * \pre
     *     Socket must be in state INACTIVE or OPEN.

     *     If enabled then a keepalive algorithm will be utilized
     *     on TCP protocol level. This algorithm regularly sends
     *     keepalive packets to the peer to ensure it is still
     *     available and reacting.
     *
     *     If this is not the case then the connection will be
     *     aborted by the network stack.
     *
     *     The way this algorithm operates is controlled by the
     *     given \c settings. The settings determine if the
     *     algorithm is applied at all via the \c enable member.
     *
     *     The \c idle_time member determines the idle time in
     *     seconds after which the algorithm starts its work. Idle
     *     time here refers to an amount of time within which no
     *     network traffic occured on the given socket.
     *
     *     The \c probe_count member determines the number of
     *     keepalive packets that will be sent after \c idle_time,
     *     before the connection will be dropped by the networking
     *     stack. This, of course, on happens if this amount of
     *     keepalive packets haven't been replied to by the peer.
     *
     *     The \c probe_interval member determines the time in
     *     seconds between individual keepalive packets being sent.
     * \note
     *     This is a not well standardized features of TCP among
     *     the different operating systems. By default the \c
     *     idle_time is set to two hours and the rest is configured
     *     in such a way that after ten minutes of missing
     *     responses the connection is dropped.
     *
     *     On IPL_OS_LINUX all members of \c settings are respected.
     *     On IPL_OS_QNX only the idle_time member is respected. The
     *     other settings probably can be changed system wide or
     *     stack wide with apropriate sysctls. Otherwise defaults
     *     apply. On IPL_OS_WIN32 all but the probe_count member are
     *     respected. The number of probes sent can be set on OSs
     *     prior to Windows Vista via the registry on a system wide
     *     level (default is five). Starting with Windows Vista it
     *     is hard coded an set to ten.
     * \errorindicator
     *     via hasError()
     * \errors
     *     see description of Socket::setSendBuffer()
     *
     * \link2req{satisfies,req~FW_OSAL_TCP_KEEPALIVE~1}
     * \{
     **/
    void setKeepalive(const KeepaliveSettings &settings) IPL_NOEXCEPT {
        setKeepalive(settings.enabled, settings.idle_time,
                     settings.probe_count, settings.probe_interval);
    }
    void setKeepalive(bool enabled, size_t idle_time,
                      size_t probe_count, size_t probe_interval) IPL_NOEXCEPT;
    /*! \} */

    /**
     *     Sets the TCP_USER_TIMEOUT socket option.
     * \pre
     *     Socket must be in state INACTIVE or OPEN.
     *
     *     A value greater than 0 will set the maximum time in milliseconds
     *     that transmitted data on the socket can be unacknowledged
     *     before the tcp connection will be forcibly closed.
     *     For more details on the user timeout feature see RFCs 793 and 5482.
     *
     *     A value of 0 will set the system default.
     * \note
     *     This is a not well standardized feature of TCP among
     *     the different operating systems.
     *     For some OS or TCP stacks setting this option may be
     *     ignored  and return false.
     * \errorindicator
     *     via return value. True indicates failure. An error is raised
     *     if true is returned.
     *     An error in this call will not set the error state.
     *     hasError() will not return true if called after setUserTimeout() even
     *     if setUserTimeout() returned true.
     *     Calling setUserTimeout() will reset the error state though.
     *
     * \link2req{satisfies,req~FW_OSAL_SOCKET_TCP_USER_TIMEOUT~1}
     **/
    bool setUserTimeout(unsigned time_ms);

    size_t maxTxSize() const IPL_NOEXCEPT override
    {
        // send buffer size limits maximum send (usually)
        const size_t BUFSIZE = getSendBuffer();

        if( this->hasError() ) // BRANCH_COVERAGE_UNTESTABLE
        {
            // don't know what to do then. will return zero.
            ipl_error.ack();
            IPL_WARN("error getting buffer size");
        }

        return BUFSIZE > MAX_SEGMENT_SIZE ? MAX_SEGMENT_SIZE : BUFSIZE;
    }

protected:  // IoMultiplexer::Channel
    Status finish_connect() IPL_NOEXCEPT override;
    
protected: // constants
    //! \brief
    //!    Maximum size of a single TCP segment. This is no hard
    //!    limit for write(...) but performance will probably be
    //!    better if no messages bigger than that are used.
    static const size_t MAX_SEGMENT_SIZE = 65495;

    // member
    /**
     * \brief Add behaviour after the tcp socket did connect successfully.

     * Add behaviour after a successful connect of the TCP socket, e.g. SSL handshake.
     * connected() is only called when connect() returns false (successful synchronous connect).
     * E.g. not for an asynchronous connect approach, not in case of error.
     * In case of error a connected() implementation must raise and return true, false otherwise.
     * The default implementation is empty.
     */
    virtual bool connected() { return false; }

private:
}; // end class


class OSAL_EXPORT TCPSocket::Description
{
public: // functions

    //! \brief Creates an invalid description!
    Description():
        valid(false),
        socket_handle(SocketHandle()),
        peer_handle(IPSocketHandle()),
        ip_version(IPV4 /* don't care... */) {}

    //! \brief
    //!    This allows for if( desc ) queries to check for
    //!    validity
    //! \see
    //!    isValid()
    explicit operator bool() const
    { return isValid(); }

    //! \brief
    //! Returns true in case the description refers to a valid,
    //! unused socket
    bool isValid() const
    { return valid; }

    //! \brief
    //!    If the object is destroyed while still being valid then
    //!    the associated OS-level socket will be closed.
    ~Description();

protected: // functions

    /**
     * \brief
     *     Create a new socket descriptoin from the given parameters

     *     \a socket_handle refers to the socket handle associated
     *     with the accepted socket. The other parameters are
     *     copies of the members found in the originating
     *     TCPServerSocket object.
     **/
    Description(
        const SocketHandle socket_handle,
        const IPSocketHandle peer_handle,
        const IPAddress local_address, IPProtocolVersion ip_version) :
        valid(true),
        socket_handle(socket_handle), peer_handle(peer_handle),
        local_address(local_address), ip_version(ip_version) {}

public:
    /**
     * \brief
     *     Copy constructor with special semantics regarding
     *     invalidation

     *     Copying a description is a dangerous thing as the
     *     destructor closes the socket handle if the description
     *     is still valid. A flat copy would cause a socket to be
     *     closed that has actually been put to good use.
     *
     *     Thus if we ever copy a description then we invalidate
     *     the object we copied from. This can only be called from
     *     TCPSocket or TCPServerSocket to avoid too much trouble.
     *
     *     Still this is very ugly. A reference counting would save
     *     us that but would increase complexity as well.
     **/
    Description(const Description &other) :
        valid(other.valid),
        socket_handle(other.socket_handle),
        peer_handle(other.peer_handle),
        local_address(other.local_address),
        ip_version(other.ip_version)
    {
        other.valid = false;
    }

    IPAddress getPeerAddress() const {
        if ( ip_version == IPV4 ) {
            return IPAddress(peer_handle.dst_addr);
        } else if ( ip_version == IPV6 ) {
            return IPAddress(peer_handle.dst_addr6);
        } else {
           return IPAddress();
        }
    }

protected: // members
    // needs to be mutable for copy-constructor and for TCPSocket s(
    // x, y, z, server->acceptConnection() ) to work (as TCPSocket
    // constructor takes non-const Description reference,
    // acceptConnection returns temporary object and compiler
    // complains about that thus TCPSocket constructor needs to take
    // const Description but needs still to be able to invalidate
    // it.
    //! true if the object is still valid, false otherwise
    mutable bool valid;
    //! the OS handle associated with the socket
    const SocketHandle socket_handle;
    //! the addresses associated with local and peer node
    const IPSocketHandle peer_handle;
    //! the listening address this socket was accepted at
    const IPAddress local_address;
    //! the IP version used by this socket connection
    const IPProtocolVersion ip_version;

    // friendships

    //! For TCPSocket to access protected members
    friend class TCPSocket;
    //! For TCPServerSocket to use protected constructor
    friend class TCPServerSocket;
};

} // end namespace

#endif
