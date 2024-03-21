/*
    Copyright e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_POSIX_IPOBJECTDEFS_HXX
#define OSAL_POSIX_IPOBJECTDEFS_HXX

#include <common/types/vector.hxx>

#include <netinet/in.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>

namespace osal
{

//! Socket address structure for IPv4
typedef sockaddr_in IPAddressHandle;

//! Socket address structure for IPv6
typedef sockaddr_in6 IPAddressHandle6;

//! Socket address structure large enough for v4 and v6
typedef sockaddr_storage IPAddressHandleAny;

//! for IPSockets we need a special set of parameters unknown to the generic socket
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

    void setSrcAddr( const IPAddressHandle& src) {
        src_addr = src;
    }
    void setSrcAddr( const IPAddressHandle6& src) {
        src_addr6 = src;
    }
    void setSrcAddr( const IPAddressHandleAny& src) {
        if ( src.ss_family==AF_INET ) {
            src_addr = (const IPAddressHandle&)src;
        }
        if ( src.ss_family==AF_INET6 ) {
            src_addr6 = (const IPAddressHandle6&)src;
        }
    }
    void setDstAddr( const IPAddressHandle& dst) {
        dst_addr = dst;
    }
    void setDstAddr( const IPAddressHandle6& dst) {
        dst_addr6 = dst;
    }
    void setDstAddr( const IPAddressHandleAny& dst) {
        if ( dst.ss_family==AF_INET ) {
            dst_addr = (const IPAddressHandle&)dst;
        }
        if ( dst.ss_family==AF_INET6 ) {
            dst_addr6 = (const IPAddressHandle6&)dst;
        }
    }
};

//! the addrinfo structure is needed for keeping resolve results
struct ResolveHandle
{
    //! a linked listed returned by the POSIX getaddrinfo call
    struct ::addrinfo* resolve_list;
    //! just a list for quick access to resolved names and the total count
    ipl::vector<std::string> entries;
};

} // end ns osal

#endif // inc. guard
