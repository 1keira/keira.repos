/*
    Copyright esolutions GmbH
    All rights reserved
    Authors:
        Matthias Gerstner
    $Id: $
*/

#ifndef OSAL_QNX_NETDEVICEDEFS_HXX
#define OSAL_QNX_NETDEVICEDEFS_HXX

#include <sys/types.h>
#include <ifaddrs.h>
#include <net/if.h>

namespace osal {

    struct NetDeviceHandle
    {
        NetDeviceHandle()
        {
            invalidate();
        }

        bool isValid() const
        {
            return first != NULL && netdev_socket != -1;
        }

        void invalidate()
        {
            index_=0;
            selected = next = first = NULL;
            netdev_socket = -1;
            seldevice[0] = '\0';
            device_fd = -1;
        }
        
        NetworkInterface::Index index() const {
            if(isValid())
                return index_;
            else
                return NetworkInterface::INVALID;
        }

        int index_;
        // the currently selected entry
        struct ifaddrs *selected;
        // the next list entry to check
        struct ifaddrs *next;
        // the start of the list
        struct ifaddrs *first;
        // some pseudo socket to do ioctl on
        int netdev_socket;
        // file descriptor of the current device, if any (lo0 has no
        // device for instance)
        int device_fd;
        // the only desired device, if constructed this way
        char seldevice[IFNAMSIZ];
    };

}  // end of namespace osal

#endif
