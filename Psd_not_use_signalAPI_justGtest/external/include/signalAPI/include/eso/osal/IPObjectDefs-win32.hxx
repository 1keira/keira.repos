/*
    Copyright e.solutions GmbH
    All rights reserved
*/
#ifndef OSAL_WIN32_IPOBJECTDEFS_HXX
#define OSAL_WIN32_IPOBJECTDEFS_HXX

#include <iplbase/win32.h>

#include <common/types/vector.hxx>
#include <common/types/string.hxx>

namespace osal
{

//! Socket address structure definition
typedef struct sockaddr_in IPAddressHandle;
typedef struct sockaddr_in6 IPAddressHandle6;
typedef sockaddr_storage IPAddressHandleAny;


//! \brief
//! For IPSockets we need a special set of parameters unknown to the
//! generic socket
struct IPSocketHandle
{
    union
    {
        //! the socket address structure for the source node
        sockaddr_in src_addr;
        sockaddr_in6 src_addr6;
    };
    union
    {
        //! the socket address structure for the target node
        sockaddr_in dst_addr;
        sockaddr_in6 dst_addr6;
    };

    IPSocketHandle()
    {
        ::memset(&src_addr6, 0, sizeof(sockaddr_in6));
        ::memset(&dst_addr6, 0, sizeof(sockaddr_in6));
    }
};

//! this handle allows for resolution of IP hostnames <-> addresses
struct ResolveHandle
{
    //! a linked listed returned by the POSIX getaddrinfo call
    struct ::addrinfo* resolve_list;
    //! \brief
    //! just a list for quick access to resolved names and the total
    //! count
    ipl::vector<std::string> entries;
};


} // end ns osal

#endif // inc. guard
