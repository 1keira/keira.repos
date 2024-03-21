/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_UNIXSERVERSOCKET_HXX
#define OSAL_UNIXSERVERSOCKET_HXX

#include <ipl_config.h>

#include <osal/UnixSocketBase.hxx>
#include <osal/UnixSocket.hxx>
#include <osal/Path.hxx>

namespace osal
{

class OSAL_EXPORT UnixServerSocket :
    public UnixSocketBase
{
public:
    UnixServerSocket(const osal::Path & p_listen_address,
            const bool p_blocking,
            const NameSpace p_name_space = FILESYSTEM,
            SocketType type=SocketType::STREAM) IPL_NOEXCEPT;

    virtual ~UnixServerSocket() IPL_NOEXCEPT;
    void enableListen(const uint32_t p_max_connections) IPL_NOEXCEPT;
    UnixSocket::Description acceptConnection() IPL_NOEXCEPT;

protected:
    /**
     * \brief
     *  Leaf implementation of performRead to prevent read on server socket.
     **/
    virtual bool performRead(void* const p_read_buffer,
            const size_t p_max_bytes, size_t &p_bytes_read) IPL_NOEXCEPT;

    /**
     * \brief
     *  Leaf implementation of performWrite to prevent write on server socket.
     **/
    virtual bool performWrite(const void* const p_write_buffer,
            const size_t p_max_bytes, size_t &p_bytes_written) IPL_NOEXCEPT;

    /**
     * \brief
     *  Leaf implementation of performFlush to prevent flush on server socket.
     **/
    virtual bool performFlush() IPL_NOEXCEPT;
};

} // end namespace osal

#endif /* OSAL_UNIXSERVERSOCKET_HXX */

