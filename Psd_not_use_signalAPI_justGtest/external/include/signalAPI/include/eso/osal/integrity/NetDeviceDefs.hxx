/*
    Copyright esolutions GmbH
    All rights reserved
    Authors:
        Matthias Gerstner
    $Id: $
*/

#ifndef OSAL_LINUX_NETDEVICEDEFS_HXX
#define OSAL_LINUX_NETDEVICEDEFS_HXX

// #include <net/if.h>

namespace osal {

    struct NetDeviceHandle
    {
//         // some pseudo socket to do ioctl on
//         int netdev_socket;
//         // the array of index:name pairs
//         struct if_nameindex* devices;
//         // index into devices
//         int current_device;
//         // do we have to cleanup devices ourselves or call if_freenameindex
//         bool cleanup_self;
// 
//         NetDeviceHandle()
//         { invalidate(); }
// 
//         void invalidate()
//         {
//             netdev_socket = -1;
//             devices = 0;
//             current_device = -1;
//             cleanup_self = true;
//         }
// 
        bool isValid() const
        {
            return 0;
//             return netdev_socket != -1;
        }
        
        NetworkInterface::Index index() const {
//             if(isValid())
//                 return devices[current_device].if_index;
//             else
                return NetworkInterface::INVALID;
        }
    };

}  // end of namespace osal

#endif
