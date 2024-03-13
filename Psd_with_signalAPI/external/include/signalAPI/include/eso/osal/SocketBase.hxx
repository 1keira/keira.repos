/*
    Copyright e.solutions GmbH
    All rights reserved
*/
#ifndef OSAL_SOCKETBASE_HXX
#define OSAL_SOCKETBASE_HXX

#include <ipl_config.h>

#include <common/types/set.hxx>
#include <common/NonCopyable.hxx>

#if defined IPL_OS_POSIX || defined IPL_OS_INTEGRITY
#    include "SocketDefs-posix.hxx"
#elif defined IPL_OS_WINPC
#    include "SocketDefs-win32.hxx"
// #elif defined IPL_OS_INTEGRITY
// #    include "SocketDefs-integrity.hxx"
#else
#    error "error undefined IPL_OS_ variant"
#endif
#include <osal/osal_dso.h>
#include <osal/osal.hxx>

#include "IoMultiplexer.hxx"

namespace osal
{

class OSAL_EXPORT SocketBase :
    public IoMultiplexerImpl/* TODO */::Channel
{
public:
    //! specific error IDs
    enum SocketErrors
    {
        //! an invalid socket was encountered
        SOCKET_INVALID = 0,
        //! A socket option is unknown to the system
        UNKNOWN_OPTION,
        //! The value provided for a socket option was invalid
        INVALID_OPTION,
        //! Socket creation failed for some system spec. reason
        CREATE_FAILED,
        //! The socket address used is already busy
        ADDRESS_IN_USE,
        //! The socket address used is invalid
        ADDRESS_INVALID,
        //! Connection has been reset by peer
        CONNRESET,
        //! peer is not reachable
        NO_PEER,
        //! used network is down/unreachable
        NO_NETWORK,
        //! address resolve operation failed
        RESOLVE_FAILED,
        //! \brief
        //! actual data transfer failed (but probably worked
        //! before)
        COMMUNICATION_FAILED,
        //! connection to peer was normally closed
        CONNECTION_CLOSED,
        //! \brief
        //! a send/receive operation could not be completely
        //! finished as the amount of data was too high
        MSG_TOO_BIG
    };

    
    //! \brief Different states that a Socket object can be in
    enum SocketState
    {
        //! \brief The socket is not active currently
        INACTIVE,
        //! \brief The socket is in the process of asynchronously  being connected
        CONNECTING,
        //! \brief
        //! The socket is configured, opened and ready for
        //! communication
        OPEN,
        //! \brief
        //! The socket was OPEN but was disconnected or some
        //! network event occured that broke the socket (e.g.
        //! disconnection on connection oriented socket)
        DEAD
    };

    //! specific error type
    static ipl::ErrorType Error;

    virtual ~SocketBase() IPL_NOEXCEPT;

    SocketBase(const SocketBase&) = delete;
    SocketBase& operator=(const SocketBase&) = delete;

    //! \brief Return the current state the socket object is in
    SocketState getState() const IPL_NOEXCEPT
    { return m_socket_state; }

    //! returns true if the last operation failed
    bool hasError() const IPL_NOEXCEPT
    { return m_has_error; }

    /*! \brief
        returns true if if the socket is currently usable,
        e.g. the state is not dead 

        Derived sockets may have additional conditions*/
    virtual bool isValid() const IPL_NOEXCEPT { return this->getState() != DEAD; }

    /*! \brief
        return wether the socket can be used with poll functionality,
        e.g. IoMultiplexer or IoUring
    */
    virtual bool isPollable() const IPL_NOEXCEPT { return m_pollable; }

    /**
        \brief Sets the SO_LINGER option for the socket

        With SO_LINGER enabled, all queued data will be sent on close
        and the close call will not return until all data is sent or
        the timeout is reached. Without all queued data will be dropped
        on close.

        The \p linger_time_s is the timeout in seconds.
        It is applied if \p on is \p true.
        If \p on is \p false, the \p linger_time_s parameter is ignored and
        the SO_LINGER socket option is turned off.

        \errorindicator
            via return value. Returns True on failure and raises an error.
            Will reset the error state, but not set it: hasError() will
            always return false after a call to setLinger()

       \link2req{satisfies,req~FW_OSAL_SOCKET_SO_LINGER~1}

     **/
    bool setLinger(bool on, unsigned linger_time_s) IPL_NOEXCEPT;


    /**
        \brief Sets the protocol priority if the platform supports it

        Packets with a higher priority might be processed first by the receiver.
        \p priority The desired priority value. Ranges from 0-6.

        \errorindicator
            via return value. Returns True on failure and raises an error.
            Will reset the error state, but not set it: hasError() will
            always return false after a call to setPriority()

     \link2req{satisfies,req~FW_OSAL_SET_PROTOCOL_PRIORITY~1}
    */
    bool setPriority(int priority) IPL_NOEXCEPT;
    bool getPriority(int &priority) IPL_NOEXCEPT;

    /**
        \brief Get access to the OS socket object

        Use this e.g. if you have a third party library that needs access to
        the OS object.
        You need to own the socket and make sure that the third party lib calls and
        osal calls on the socket cooperate nicely.
     */
    SocketHandle getHandle() const IPL_NOEXCEPT {return m_socket_handle;}

    /**
       \brief Set the system's send buffer to the given value

        The operating system buffers on a low level outgoing
        network data to increase efficiency. This avoids
        continous hardware access and/or network packet
        generation for small amounts of data e.g. when an
        application writes out single bytes of data.

        The buffer size determines how much data is cached
        before it is actually sent out on the network. The
        actual behaviour associated with this buffer is
        operating-system and network and driver dependant.
        Usually it isn't always waited until the buffer is full
        but after a certain amount of time has passed even
        smaller units of data are transmitted.

        If you know from your application point of view that
        your specific socket implements a certain access pattern
        regarding data sent out then you may adjust this value
        to a size that matches this access pattern.

        If you don't set the size explicitly then the system
        instruments a sensible default send buffer size.

        Note that the buffer size has system-dependent minimum
        and maximum limits.  In case the desired buffer size is
        not allowed by the system an error is raised. Notably
        disabling of the system buffer by setting it to zero is
        unlikely to succeed. The latter operations may also be
        influenced by the privileges of your process.

        \param[in] p_buffer_size
            The size of the systems send buffer in bytes for this
            specific socket.
        \errorindicator
            via hasError()
        \errors
            Socket::Error with IDs:

            - SOCKET_INVALID if the socket is invalid for some
            reason (e.g. it was closed)
            - INVALID_OPTION if something went wrong with the option
            setting. Either the option values are logically
            incorrect or out of range or also it may be that the
            socket is already in an OPEN state and the option cannot
            apply due to this fact.
            - UNKNOWN_OPTION if the option is not applicable for
            this socket type.

            SysError with IDs:

            - UNKNOWN_ERROR on other occasions
     **/
    void setSendBuffer(const size_t p_buffer_size) IPL_NOEXCEPT;

    /**
       \brief Set the system receive buffer to the given value

        Just like with the setSendBuffer function it is possible
        to set a buffer size for a receive buffer that is used
        on the operating system level for this socket.

        The system buffers incoming data until a reasonable
        amount of data has been received or a certain time span
        has passed. This avoids e.g. unnecessary calls from
        kernel space to user space for single bytes receiptions
        and alike.

        As with the send buffer you may set this buffer size to
        a value that you think it matches your application. Or
        if you're not sure simply don't touch the value as the
        operating system will set a sensible default setting for
        the receive buffer size.

        Again there apply system-dependant minimum and maximum
        limits to the receive buffer size. If your desired
        receive buffer size cannot be set then an error is
        raised.

        \param[in] p_buffer_size
            The size of the systems receive buffer in bytes for this
            specific socket.
        \errorindicator
            via hasError()
        \errors
            see description at setSendBuffer()
     **/
    void setRecvBuffer(const size_t p_buffer_size) IPL_NOEXCEPT;

    /**
        \brief
            Return the currently set system send buffer size for
            this socket
        \warning
            You may find that the value retrieved here is bigger
            than the one set at setSendBuffer. This is due to the
            fact that the operating system is increasing (e.g.
            doubling) the size of the buffer for its own reasons.
        \return
            Size in bytes of the systems send buffer.
        \errorindicator
            via hasError()
        \errors
            Socket::Error with IDs:

            - SOCKET_INVALID if the socket is invalid for some
            reason (e.g. it was closed)
            - UNKNOWN_OPTION if the option is not applicable for
            this socket type.

            SysError with IDs:

            - PERMISSION_DENIED if the operation is not allowed for
            the caller
            - OUT_OF_MEMORY if not enough memory ressources are
            available to perform the operation
            - UNKNOWN_ERROR on other occasions
     **/
    size_t getSendBuffer() const IPL_NOEXCEPT;

    /**
        \brief
            Return the currently set system receive buffer size for
            this socket
        \warning
            You may find that the value retrieved here is bigger
            than the one set at setRecvBuffer. This is due to the
            fact that the operating system is increasing (e.g.
            doubling) the size of the buffer for its own reasons.
        \return
            Size in bytes of the system receive buffer.
        \errorindicator
            via hasError()
        \errors
            see description at getSendBuffer()
     **/
    size_t getRecvBuffer() const IPL_NOEXCEPT;

    /**
        \brief Common close function for all Socket types

        Closes the socket on all communication levels. Further
        communication will not be possible. Another connection
        will not be possible. This object will be DEAD.

        Before closing the socket any buffered but not yet
        written data in the InputStream base class will be
        flushed.

        Under certain conditions (e.g. the mentioned flush, the
        TCP linger option) this call might block for some time
        depending on socket settings and socket type.

        \pre
            Socket must be in state OPEN
        \post
            Socket will be in state DEAD and may not be used for any
            communication neither now nor in the future.
        \param[in]
            discard_pending All not yet send data will be discarded
        \errorindicator
            via return code. true is error, false otherwise. (note:
            needs to be via return code instead of hasError(), as
            multi-threaded use of close() together with read/write
            calls may occur in case one thread wants to get the
            other out of a blocking read/write call by closing the
            socket.
        \errors
            ipl::CommonError with IDs:

            - INVALID_USAGE if the socket is already DEAD

            Failures in flush or shutdown operation are currently
            ignored such that a smooth close of an erroneous socket
            is possible.
     **/
    virtual bool close(const bool discard_pending=false);

    /**
        \brief
            Return the maximum transmission size in bytes for the
            current socket

            This is not constant across a type of socket but
            dependant on the actual socket instance.
     **/
    virtual size_t maxTxSize() const { return getSendBuffer(); }
    
protected:  
    // IoMultiplexer::Channel
#if defined IPL_OS_POSIX || defined IPL_OS_INTEGRITY
    SocketPair fds() const IPL_NOEXCEPT override;
#elif defined IPL_OS_WIN32
    EventPair events() const IPL_NOEXCEPT override;
    uint32_t parseEvents(WSAEVENT event_handle, short poll_events) const IPL_NOEXCEPT override;
#endif
    Status finish_connect() IPL_NOEXCEPT override;
    Status status() const IPL_NOEXCEPT override;


    explicit SocketBase(bool pollable=true) IPL_NOEXCEPT;

    //! \brief Allows derived classes to comfortably set a new socket state
    void setState(const SocketState p_new_state) IPL_NOEXCEPT
    {
        m_socket_state = p_new_state;
    }

    //! \brief
    //! checks if the socket object is valid
    bool checkValidSocket() const IPL_NOEXCEPT;

    void resetError() const IPL_NOEXCEPT
    { m_has_error = false; }

    void setError() const IPL_NOEXCEPT
    { m_has_error = true; }

    /** Allow higher level layers to perform their shutdown before the socket is closed.
       Should raise in case of error and return true, retunr false otherwise.
       Socket though will continue and close the socket in close() no matter what closing returns,
       but it errors returned by closing will appear in the error stack of close().
       The default implementation is empty.
     */
    virtual bool closing() { return false; }

    //! Whether the last operation failed
    mutable bool m_has_error;
    //! The os handle of the socket
    SocketHandle m_socket_handle;
    //! the value can be initialized lazily from isPollable() const
    mutable bool m_pollable;

private:
    //! The state the socket is currently in
    SocketState m_socket_state;

    friend class Osal;

    /**
        \brief
            To do some initialization work prior to access to the
            socket subystem.
     **/
    static bool init() IPL_NOEXCEPT;

    /**
        \brief
            To do some deinitilization work before shutting down the
            OSAL.
     **/
    static void exit() IPL_NOEXCEPT;

}; //end class Socket

// for using osal::SocketHandle as map key
inline bool operator < (const SocketHandle &lhs,
                        const SocketHandle &rhs) IPL_NOEXCEPT {
    if(lhs.rxfd<rhs.rxfd) return true;
    if(lhs.rxfd==rhs.rxfd) return lhs.txfd<rhs.txfd;
    return false;
}

} // end namespace

#endif // OSAL_SOCKETBASE_HXX
