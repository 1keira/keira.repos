/*
    Copyright e.solutions GmbH
    All rights reserved
*/
#ifndef OSAL_POSIX_SOCKETDEFS_HXX
#define OSAL_POSIX_SOCKETDEFS_HXX

namespace osal
{

struct SocketHandle
{
    using socket_type = int;
    constexpr static const socket_type INVALID_SOCKET_VALUE=-1;

    //! the socket file descriptors
    socket_type rxfd;
    socket_type txfd;

    SocketHandle() IPL_NOEXCEPT { invalidate(); }

    bool isValid() const IPL_NOEXCEPT {
        return rxfd!=INVALID_SOCKET_VALUE || txfd!=INVALID_SOCKET_VALUE;
    }

    void invalidate() IPL_NOEXCEPT {
        rxfd=INVALID_SOCKET_VALUE;
        txfd=INVALID_SOCKET_VALUE;
    }
};

} // end ns osal

#endif // inc. guard
