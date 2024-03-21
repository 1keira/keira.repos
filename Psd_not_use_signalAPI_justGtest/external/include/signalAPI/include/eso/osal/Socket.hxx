/*
    Copyright e.solutions GmbH
    All rights reserved
*/
#ifndef OSAL_SOCKET_HXX
#define OSAL_SOCKET_HXX

#include <ipl_config.h>

#include <common/types/set.hxx>
#include <common/NonCopyable.hxx>

#include <common/IBinInOutStream.hxx>
#include <osal/SocketBase.hxx>

#include <osal/osal_dso.h>
#include <osal/osal.hxx>
#include "IoMultiplexer.hxx"

#include <utility>

namespace osal
{

/**
 * \brief
 *    Abstraction for connection oriented stream sockets 
 *    as opposed to SocketDatagram.
 * 
 *    The typical use case for connection oriented socket communication
 *    is communication via TCP/IP on a network like Ethernet or the
 *    Internet.
 * 
 *    In some cases connection oriented UDP socket are used.
 *    Also there might be special socket variants for local IPC
 *    communication in the system.
 *
 *    This base class interface only serves for some common code and
 *    interface between different implementations of connection oriented
 *    sockets. It can thus not be instantiated on its own.
**/
class OSAL_EXPORT Socket :
    // as a socket provides I/O we want to be an input and output
    // stream for binary data
    public ipl::IBinInOutStream,
    public SocketBase
{
public:
    /*!
        \brief Create from existing file descriptor(s) actually opened for
        some OS level socket (or similar)
        
        This is meant for special cases only, e.g. when you get passed an
        open, valid file descriptor (or whatever the OS in question uses)
        and need to create some osal::Socket wrapping it.
        For an underlying socket, \p rxfd and \p txfd are the same,
        for an underlying pair of pipes they can be different.

        Beware when using file descriptors that aren't sockets.
        Functionality can behave differently or may not be available,
        e.g. polling for regular files.
        
        For normal cases, use one of the specialized derived classes like
        TCPSocket or UnixSocket.
    */
    Socket(SocketHandle::socket_type rxfd, SocketHandle::socket_type txfd,
           bool blocking,
           size_t input_buffer_size, size_t output_buffer_size) IPL_NOEXCEPT;
    
    /**
     * \brief
     *    Performs some sanity checks before destruction

     *    Expects m_socket_handle to be invalidated.
     *
     *    Expects m_socket_state to be INACTIVE or DEAD.
    **/
    virtual ~Socket() IPL_NOEXCEPT;


    //! \brief
    //! returns true if construction was successful and currently
    //! the socket is not DEAD
    virtual bool isValid() const IPL_NOEXCEPT
    { return IBinInOutStream::isValid() && m_is_valid
        && this->getState() != DEAD; }

    bool isPollable() const IPL_NOEXCEPT override;
    
    /**
     * \brief \b DEPRECATED
     * 
     * This is outdated technology. \b Do \b not \b use.
     * Use an IoMultiplexer instead.
     * 
     *    Check multiple Socket objects for read and write
     *    possibilities and error conditions

     *    The function takes three different sets as an argument.
     *    The first set contains a number of socket objects to be
     *    checked for the possibility to read. The second set
     *    contains objects to be checked for the possibility to
     *    write.
     *
     *    Possibility to read or write in this context means
     *    whether it would be possible to perform a read or a
     *    write on that socket without blocking. For a
     *    TCPServerSocket the readable state indicates that a new
     *    connection can be accepted on it without blocking.
     *
     *    The third set contains a number of socket objects that
     *    are monitored for error conditions.
     *
     *    If at least one of the socket objects turned in to the
     *    function become ready for the condition monitored then
     *    select returns. Otherwise the function call will block
     *    until the given timeout in milliseconds occurs or
     *    infinitely if the timeout functionality is disabled.
     *
     *    After the function returns, only those sockets remain
     *    the set parameters that are ready in the according sets
     *    context.
     * \param[in,out]
     *    p_read_sockets Sockets to check for being ready to read
     *    without blocking
     * \param[in,out]
     *    p_write_sockets Sockets to check for being ready to
     *    write without blocking
     * \param[in,out]
     *    p_except_sockets Sockets to check for having any
     *    exception conditions.  What these exceptions are is
     *    socket implementation dependant. Usually a connection
     *    loss on TCP is considered an exception.
     * \param[in]
     *    p_timeout_ms Time to wait for at least one of the
     *    objects in one of the sets becoming ready in terms of
     *    its context. If this parameter is zero and
     *    p_timeout_enable is still true then the effect is that
     *    all sockets are polled (i.e. there is no wait for state
     *    changes of any of the sockets but all sockets are
     *    immediatly checked for the conditions and the result is
     *    returned).
     * \param[in]
     *    p_timeout_enable Whether the timeout parameter should
     *    apply. If set to false then the select will never
     *    timeout but block until at least one socket fulfills the
     *    apropriate condition.
     * \return
     *    Accumulated number of sockets that are available for
     *    reading, writing or hit an error condition, or < 0 on
     *    error condition.
     * \warning
     *     Don't use the same sets for \c p_read_sockets,
     *     p_write_sockets and/or p_except_sockets or otherwise
     *     the logic will be screwed up.
     * \note
     *    On error condition the turned in sets will be cleared.
     * \errorindicator
     *    < 0 return code.
     * \errors
     *    Socket::Error with IDs:
     *
     *    - SOCKET_INVALID in case one of the given socket objects
     *    is not in state OPEN. Or if the system thinks one of the
     *    sockets is invalid.
     *
     *    SysError with IDs:
     *
     *    - INTEGRITY_ERROR on severe interal errors
     *    - OUT_OF_MEMORY if not enough memory is available to
     *    perform the operation
     *    - UNKNOWN_ERROR on other errors
    **/
    static int selectSockets(
        ipl::set< const Socket* > &p_read_sockets,
        ipl::set< const Socket* > &p_write_sockets,
        ipl::set< const Socket* > &p_except_sockets,
        const size_t p_timeout_ms,
        const bool p_timeout_enable = true) IPL_NOEXCEPT;


    virtual bool connect() { return true; }

protected:
    /**
     * \brief
     *    This sets up the basic socket information.

     *    The construction time parameters cannot be changed
     *    during the lifetime of the object any more.
     *
     *    Before you can use the Socket you have to configure it
     *    correctly according to the SocketBase implementations'
     *    requirements.
     *
     *    The initial state for the socket object will be
     *    INACTIVE.
     * \param[in]
     *    p_blocking Wheter this is to be blocking or non-blocking
     *    socket. This parameter is passed on to the base classes
     *    InputStream and OutputStream.
     * \param[in]
     *    p_input_buffer The size of an input buffer, if any (zero
     *    if no buffering should be used). This parameter is
     *    passed to the InputStream base class.
     * \param[in]
     *    p_output_buffer The size of an output buffer, if any
     *    (zero if no buffering should be used). This parameter is
     *    passed to the OutputStream base class.
     * \errorindicator
     *    via isValid()
     * \errors
     *    see InputStream() and OutputStream() (they can only
     *    occur if p_input_buffer or p_output_buffer are set.
    **/
    Socket(const bool p_blocking,
        const uint32_t p_input_buffer,
        const uint32_t p_output_buffer) IPL_NOEXCEPT;

protected: // functions from IBinInOutStream
    /**
     * \brief
     *     Implementation of InputStream base class method for any
     *     kind of connection oriented Socket.

     *     This method is called by InputStream base class when the
     *     user calls read and the userspace buffer is empty or
     *     doesn't contain enough data to fullfil the request.
     * \note
     *     If zero bytes will be read from the socket then on a
     *     non-blocking socket no data is currently available.
     * \note
     *     On some systems on regular connection close there the
     *     error ID will not be Socket::CONNECTION_CLOSED but
     *     Socket::CONNRESET.
     * \return
     *     true on error, false on success; also via hasError()
     * \errorindicator
     *     via return code
     * \errors
     *     ipl::CommonError attached to a StreamError with IDs
     *
     *     - INVALID_USAGE / STREAM_BROKEN if getState() != OPEN
     *
     *     SysError attached to a StreamError with IDs:
     *
     *     - SYSTEM_RESSOURCES_EXHAUSTED / OPERATION_FAILED if the
     *     operation could not be performed due to lack of
     *     ressources in the kernel/network stack (typically
     *     buffers)
     *     - OUT_OF_MEMORY / OPERATION_FAILED if the operation
     *     could not be performed due to lack of memory in the
     *     kernel/network stack
     *     - INTEGRITY_ERROR / STREAM_BROKEN on severe internal errors
     *     - UNKNOWN_ERROR / UNKNOWN_STREAM_ERROR on other errors
     *
     *     Socket::Error attached to a StreamError with IDs:
     *
     *     - CONNRESET / STREAM_BROKEN if the peer has unexpectedly
     *     closed the connection
     *     - COMMUNICATION_FAILED / OPERATION_FAILED  under various
     *     network or connection errors (but some data has been
     *     already exchanged somewhen)
     *     - MSG_TOO_BIG / OPERATION_FAILED if the message was too
     *     big to fit into the read buffer and has been truncated.
     *     Part of the data can still be placed in p_read_buffer,
     *     however. Inspect \c p_bytes_read about it.
     *     - CONNECTION_CLOSED / END_OF_STREAM if the connection
     *     has been closed in a normal way by the peer.
     *     - NO_PEER / STREAM_BROKEN if a previous send operation
     *     on the socket failed, because no peer is available or
     *     the respective service is not running at the peer.
     *     - NO_NETWORK / STREAM_BROKEN if the network has failed
     *     in some way (connection timeout, stack error, interface
     *     error)
     *     - SOCKET_INVALID / STREAM_BROKEN if the underlying
     *     socket become invalid (e.g. by parallel close)
     **/
    virtual bool performRead(
        void* const p_read_buffer,
        const size_t p_max_bytes,
        size_t &p_bytes_read) IPL_NOEXCEPT;

    /**
     * \brief
     *     Implementation of OutputStream base class method for any
     *     kind of connection oriented Socket

     *     This method is called by OutputStream base class when
     *     the user calls write and the userspace buffer is full.
     * \return
     *     true on error, false on success
     * \errorindicator
     *     via return code
     * \errors
     *     ipl::CommonError attached to a StreamError with IDs
     *
     *     - INVALID_USAGE / STREAM_BROKEN if getState() != OPEN
     *
     *     SysError attached to a StreamError with IDs:
     *
     *     - SYSTEM_RESSOURCES_EXHAUSTED / OPERATION_FAILED if the
     *     operation could not be performed due to lack of
     *     ressources in the kernel/network stack (typically
     *     buffers)
     *     - INTEGRITY_ERROR / STREAM_BROKEN in case of severe
     *     internal problems
     *     - PERMISSION_DENIED / STREAM_BROKEN if sending is not
     *     allowed (could be firewall rules or privileged port
     *     <1024, or broadcast address not allowed etc.).
     *
     *     Socket::Error attached to a StreamError with IDs:
     *
     *     - CONNRESET / STREAM_BROKEN if the peer has unexpectedly
     *     closed the connection
     *     - ADDRESS_INVALID / STREAM_BROKEN if the destination
     *     Address given during construction time of the Socket
     *     turns out to be unsuitable for sending to
     *     - SOCKET_INVALID / STREAM_BROKEN if the socket has been
     *     closed/shutdown previously or concurrently to the send
     *     operation
     *     - MSG_TOO_BIG / OPERATION_FAILED if the message was too
     *     big to be sent out in one piece. No data has been sent
     *     in this case.
     *     - NO_NETWORK / STREAM_BROKEN under various network or
     *     connection errors (e.g. missing route to destination,
     *     network interface down etc.)
     **/
    virtual bool performWrite(
        const void* const p_write_buffer,
        const size_t p_max_bytes,
        size_t &p_bytes_written) IPL_NOEXCEPT;

    /**
     * \brief
     *     Implemention of OutputStream base class method for any
     *     kind of connection oriented Socket

     *     If the user called flush on the output stream then the
     *     base class calls this function to actually perform a
     *     flush operation.
     * \note
     *     Explicit flushing is usually not possible with sockets
     *     due to the nature of the whole networking stuff. Instead
     *     use the linger options for example to control such
     *     stuff.
     * \errors
     *     none
     **/
    virtual bool performFlush() IPL_NOEXCEPT;

protected: // data
    //! whether construction succeeded
    bool m_is_valid;
    //! the value can be initialized lazily from isPollable() const
    mutable bool m_initialized_pollable;

private:
    friend void postpareSockSet( fd_set&, ipl::set<const SocketBase*>& ) IPL_NOEXCEPT;
#ifdef IPL_OS_WINPC
    friend bool prepareSockSet( ipl::set<const SocketBase*>&, fd_set&) IPL_NOEXCEPT;
#else
    friend bool prepareSockSet( ipl::set<const SocketBase*>&, fd_set&, int&) IPL_NOEXCEPT;
#endif
}; //end class Socket


} // end namespace

#endif