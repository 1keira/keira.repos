/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_UNIXSOCKET_HXX
#define OSAL_UNIXSOCKET_HXX

#include <ipl_config.h>

#if !defined IPL_OS_POSIX && !defined IPL_OS_INTEGRITY
#error Unix sockets not available on this OS
#endif

#include <osal/UnixSocketBase.hxx>

namespace osal
{

class OSAL_EXPORT UnixSocket :
    public UnixSocketBase
{
    friend class UnixServerSocket;

public: // types
    class Description;

public: // functions

    UnixSocket(
            const bool p_blocking, const size_t p_input_buffer,
            const size_t p_output_buffer,
            const osal::Path &p_src, const osal::Path &p_dst,
            const NameSpace p_name_space = FILESYSTEM,
            SocketType type=SocketType::STREAM);

    UnixSocket(const bool p_blocking, const size_t p_input_buffer,
            const size_t p_output_buffer, const Description &p_desc);

    virtual ~UnixSocket();

    bool connect() override;

};

class UnixSocket::Description
{
public: // functions

    //! \brief Creates an invalid description!
    Description():
        valid(false),
        socket_handle(SocketHandle()),
        peer_handle(UnixSocketHandle()),
        name_space(FILESYSTEM) {}

    //! \brief
    //!     This allows for if( desc ) queries to check for validity
    //! \see
    //!     isValid()
    operator bool() const
    { return isValid(); }

    //! \brief
    //!     Returns true in case the description refers to a valid, unused socket
    bool isValid() const
    { return valid; }

    //! \brief
    //!     If the object is destroyed while still being valid then the
    //!     associated OS-level socket will be closed.
    ~Description();

protected: // functions

    Description(
            const SocketHandle &socket_handle,
            const UnixSocketHandle &peer_handle,
            const osal::Path &local_address, NameSpace name_space) :
        valid(true),
        socket_handle(socket_handle), peer_handle(peer_handle),
        local_address(local_address), name_space(name_space) {}

public:
    Description(const Description &other) :
        valid(other.valid),
        socket_handle(other.socket_handle),
        peer_handle(other.peer_handle),
        local_address(other.local_address),
        name_space(other.name_space)
    {
        other.valid = false;
    }

protected: // members
    //! true if the object is still valid, false otherwise
    mutable bool valid;
    //! the OS handle associated with the socket
    const SocketHandle socket_handle;
    //! the addresses associated with local and peer node
    const UnixSocketHandle peer_handle;
    //! the listening address this socket was accepted at
    const osal::Path local_address;
    //! the IP version used by this socket connection
    const NameSpace name_space;

    friend class UnixSocket;
    friend class UnixServerSocket;
    friend class UnixSocketDatagram;
};

} // end namespace osal

#endif /* OSAL_UNIXSOCKET_HXX */

