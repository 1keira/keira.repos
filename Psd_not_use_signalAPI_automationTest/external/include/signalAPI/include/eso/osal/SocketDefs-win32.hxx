/*
    Copyright e.solutions GmbH
    All rights reserved
*/
#ifndef OSAL_WIN32_SERIALPORTDEFS_HXX
#define OSAL_WIN32_SERIALPORTDEFS_HXX

// socket data types and other data type definitions that are used by generic WIN32 header
#include <iplbase/win32.h>

namespace osal
{

/*
    Generic Socket definitions needed.
    The maximum fd_num should be declared here as well?
*/

struct SocketHandle
{
    using socket_type = SOCKET;
    constexpr static const socket_type INVALID_SOCKET_VALUE=INVALID_SOCKET;

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
