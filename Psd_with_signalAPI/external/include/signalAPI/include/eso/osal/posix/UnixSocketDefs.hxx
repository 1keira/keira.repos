/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_POSIX_UNIXSOCKETDEFS_HXX
#define OSAL_POSIX_UNIXSOCKETDEFS_HXX

#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>

namespace osal
{

typedef sockaddr_un UnixAddressHandle;

struct UnixSocketHandle
{
    sockaddr_un src_addr;
    sockaddr_un dst_addr;

    UnixSocketHandle()
    {
        ::memset(&src_addr, 0, sizeof(sockaddr_un));
        ::memset(&dst_addr, 0, sizeof(sockaddr_un));
    }
};

} // end ns osal

#endif /* OSAL_POSIX_UNIXSOCKETDEFS_HXX */
