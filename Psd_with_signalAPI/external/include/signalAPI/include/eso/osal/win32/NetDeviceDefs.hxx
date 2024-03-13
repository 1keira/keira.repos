/*
    Copyright e.solutions GmbH
    All rights reserved
    Authors:
        Matthias Gerstner
    $Id: $
*/

#ifndef OSAL_WIN32_NETDEVICEDEFS_HXX
#define OSAL_WIN32_NETDEVICEDEFS_HXX

// this is a special header from a special "ip helper library"
// a rare occasion on windows
#include <Iphlpapi.h>

namespace osal {

    struct NetDeviceHandle
    {
        NetDeviceHandle()
        { invalidate(); }

        void invalidate()
        {
            begin = NULL;
            no_data = false;
            next = NULL;
            netdev_socket = INVALID_SOCKET;
            specific_device.clear();
            addr_begin = NULL;
            selected = NULL;
        }

        bool isValid() const
        {
            // if no data was there we're still valid, just no info
            // there
            return (begin != NULL || no_data) &&
                netdev_socket != INVALID_SOCKET && addr_begin;
        }
        
        NetworkInterface::Index index() const {
            if(isValid())
                return selected->IfIndex;
            else
                return NetworkInterface::INVALID;
        }

        // pointer to a buffer that will contain a list of adapter
        // information structs, this is the first element
        ::PIP_ADAPTER_ADDRESSES begin;
        // the next to inspect element, NULL if end of list has been
        // reached
        ::PIP_ADAPTER_ADDRESSES next;
        // the currently selected device
        ::PIP_ADAPTER_ADDRESSES selected;
        // ipv4 address table for all ifs
        ::PMIB_IPADDRTABLE addr_begin;
        // true if no data was returned during construction
        bool no_data;
        // as on the other OSs we need to do some ioctl's for which we
        // need some generic socket
        SOCKET netdev_socket;
        // if required during construction then this contains the
        // specific device name we want to see
        ipl::string specific_device;
    };

}  // end of namespace osal

#endif
