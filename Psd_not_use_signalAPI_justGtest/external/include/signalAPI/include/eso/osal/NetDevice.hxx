/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_NET_DEVICE_H_NOWARN
#ifdef _MSC_VER
#pragma message(__FILE__)
#pragma message("This file is being deprecated. Consider using NetworkInterface.hxx and NetDeviceMonitor.hxx instead.")
#else
#warning This file is being deprecated. Consider using NetworkInterface.hxx and NetDeviceMonitor.hxx instead.
#endif
#endif

#ifndef OSAL_NETDEVICE_HXX
#define OSAL_NETDEVICE_HXX

#include <ipl_config.h>

#include <common/NonCopyable.hxx>
#include <common/types/vector.hxx>

#include <osal/osal.hxx>
#include <osal/osal_dso.h>
#include <osal/IPSocket.hxx>
#include <osal/NetworkInterface.hxx>

#if defined IPL_OS_ANDROID || defined IPL_OS_LINUX
#    include "linux/NetDeviceDefs.hxx"
#elif defined IPL_OS_QNX
#    include "qnx/NetDeviceDefs.hxx"
#elif defined IPL_OS_WINPC
#    include "win32/NetDeviceDefs.hxx"
#elif defined IPL_OS_INTEGRITY
#    include "integrity/NetDeviceDefs.hxx"
#else
#    error "error undefined IPL_OS_ variant"
#endif

#include <string.h>

namespace osal {

    /**
    * \brief
    *     Get and set configuration of system network interfaces

    *     This class allows you to obtain a list of available network
    *     interfaces in the system and their associated configuration.
    *
    *     It also allows you to obtain the configuration of a specific
    *     network interface.
    *
    *     Additionally it allows you to set addressing information and
    *     operation modes of available devices.
    *
    *     This functionality is currently restricted to IPv4 network
    *     devices in that only those addresses are returned. There may
    *     also be interfaces returned that don't do any IP at all. For
    *     these you won't get any address information.
    *
    *     If IPv6 support is needed please contact Sebastian.Duell@esolutions.de
    *
    *     While reading the network device configuration can usually be
    *     done by any user, setting network device configuration typically
    *     requires administrative priveleges for the calling process. If
    *     the caller is lacking that privelege than according
    *     osal::SysErrors with osal::PERMISSION_DENIED IDs will be raised.
    **/
    class OSAL_EXPORT NetDevice :
        public ipl::NonCopyable
    {
    public: // types

        //! differentation of network device classes
        enum DeviceType
        {
            //! loopback-device
            LOOP,
            //! point-to-point device
            PTP,
            //! \brief
            //! point-to-multi-point device (typically
            //! ethernet-like)
            MULTI
        };

        //! gathered netework device information
        struct InterfaceInfo
        {
            //! device name
            ipl::string name;
            //! IPv4 address assigned to the interface
            osal::IPSocket::IPAddress address;
            //! IPv4 netmask assigned to the interface
            osal::IPSocket::IPAddress netmask;
            //! IPv4 broadcast address for the interface
            //! for point-to-point interfaces this is the destination address
            osal::IPSocket::IPAddress broadcast;
            //! \brief
            //! whether a valid broadcast address is set \c
            //! broadcast
            bool have_broadcast;
            //! whether a valid address is set in \c address
            bool have_address;
            //! whether a valid address is set in \c netmask
            bool have_netmask;
            //! \brief
            //! 48-bit MAC address e.g. for ethernet devices, not
            //! set for LOOP type
            uint8_t hw_addr[6];
            //! whether a valid harware address is set in \c hw_addr
            bool have_hwaddr;
            //! whether the interface is set to operational mode
            bool enabled;
            //! \brief
            //! whether the interface has detected a carrier on
            //! physical level
            bool carrier;
            //! \brief
            //! whether the interface is in promiscuous mode (set to
            //! receive also data that is not directed to itself)
            bool promiscuous;
            //! multicasting is supported
            bool support_multicast;
            //! broadcasting is supported
            bool support_broadcast;
            //! maximum transfer unit of the interface in bytes
            size_t mtu;
            //! the network device class of the device
            DeviceType type;
            NetworkInterface::Index index;

            //! set device information back to zero and empty values
            void reset()
            {
                address.address.clear();
                broadcast.address.clear();
                netmask.address.clear();
                enabled = false;
                carrier = false;
                promiscuous = false;
                have_broadcast = false;
                have_address = false;
                have_netmask = false;
                support_multicast = false;
                support_broadcast = false;
                have_hwaddr = false;
                mtu = 0;
                type = MULTI;
                ::memset(hw_addr, 0, 6);
                index=NetworkInterface::INVALID;
            }

            InterfaceInfo()
            { reset(); }

            InterfaceInfo(const NetworkInterface::Info &info):
                have_broadcast(false), have_address(false), have_netmask(false),
                have_hwaddr(false),
                enabled(info.enabled), carrier(info.carrier), promiscuous(false),
                support_multicast(false), support_broadcast(false), mtu(info.mtu),
                type(info.pointtopoint? PTP : info.loopback? LOOP : MULTI),
                index(info.index)
            {
                memset(hw_addr, 0, 6);
                for(NetworkInterface::Info::AddrInfos::const_iterator i=info.addrinfos.begin();
                    i!=info.addrinfos.end(); i++)
                    switch(i->address.type) {

                    default:
                        // ignore unsupported address types
                        break;

                    case NetworkAddress::MAC:
                        break;

                    case NetworkAddress::IPv4:
                        have_address=i->address.string.size();
                        address.address=i->address.string;
                        have_broadcast=i->broadcast.string.size();
                        support_broadcast=have_broadcast;
                        broadcast.address=i->broadcast.string;
                        have_netmask=i->netmask.string.size();
                        netmask.address=i->netmask.string;
                        break;
                    }
            }

            operator NetworkInterface::Info () const {
                NetworkInterface::Info result(index, name, mtu,
                                              enabled, carrier, support_broadcast,
                                              type==PTP, type==LOOP);
                NetworkInterface::AddrInfo a;
                if(have_hwaddr) {
                    a.address=NetworkAddress(NetworkAddress::MAC, hw_addr);
                    result.addrinfos.push_back(a);
                }
                if(have_address) {
                    a.address=NetworkAddress(NetworkAddress::IPv4,
                                             address.address);
                    if(have_broadcast)
                        a.broadcast=NetworkAddress(NetworkAddress::IPv4,
                                                   broadcast.address);
                    if(have_netmask)
                        a.netmask=NetworkAddress(NetworkAddress::IPv4,
                                                 netmask.address);
                    result.addrinfos.push_back(a);
                }
                return result;
            }
        };

    public: // functions

        /**
        * \brief
        *     Get a list of InterfaceInfos for the selected network
        *     devices

        *    If \c device is not NULL then a query is made for the
        *    existence of a network device of that name and its
        *    associated InterfaceInfo is returned at getNextInfo().
        *
        *    If \c device is NULL then a list of InterfaceInfos for
        *    all network devices in the system is available via
        *    getNextInfo(). If there are no devices at all then
        *    getNextInfo() will immediatly return > 1 to indicate the
        *    end of the list.
        * \errorindicator
        *     via isValid()
        * \errors
        *     osal::SysError with IDs
        *
        *     - INVALID_DEVICE if the selected device \c device is not
        *     existing
        *     - UNKNOWN_ERROR on other errors
        **/
        NetDevice(const char *device = NULL);

        /**
        * \brief
        *     Cleans up any associated resources
        **/
        ~NetDevice();

        /**
        * \brief
        *     Determines whether the list of network devices could be
        *     initialized successfully at construction time
        **/
        bool isValid()
        {
            return m_handle.isValid();
        }

        /**
        * \brief
        *     Selects and returns the next InterfaceInfo from the list
        *     of network devices gathered during construction time

        *     After successful return getInfo(InterfaceInfo&) will
        *     return information for the next network device in the
        *     list.
        * \return
        *    zero if \c info could be filled with information about
        *    the next list entry.
        *
        *    < 0 if an error occured trying to obtain the
        *    information and \c info was not filled. But there may be
        *    more list entries available.
        *
        *    > 0 if the list end has been reached and \c info was not
        *    filled. Further calls will always return > 0.
        * \errorindicator
        *     return of < 0
        **/
        int_fast8_t getNextInfo(InterfaceInfo &info);

        /**
        * \brief
        *     Set the IP address of the currently selected network
        *     device to \a a

        *     \a a can be a numbers and dots IP address or a hostname
        *     that will resolve into a numbers and dots IP address.
        *
        *     If a resolve operation becomes necessary and fails then
        *     the operation is aborted and the resolve error returned.
        * \note
        *     On Win32 there's no easy way to set IP addresses
        *     so OSAL returns NOT_IMPLEMENTED for these OSs right now.
        * \return
        *     \c true on error, \c false on success
        * \errors
        *     osal::SysError with IDs
        *
        *     - PERMISSION_DENIED if you lack privelege to perform the
        *     operation
        *     - NOT_IMPLEMENTED if the operation can't be performed on
        *     the current OS
        *     - UNKNOWN_ERROR otherwise
        **/
        bool setAddress(const char *a);

        /**
        * \brief
        *     Set the netmask of the currently selected network device
        *     to \c a

        *     The same rules as to setAddress(const char*) apply
        * \see
        *     setAddress(const char*)
        * \note
        *     On Win32 there's no easy way to set netmasks so
        *     OSAL returns NOT_IMPLEMENTED for these OSs right now.
        * \return
        *     \c true on error, \c false on success
        * \errors
        *     osal::SysError with IDs
        *
        *     - PERMISSION_DENIED if you lack privelege to perform the
        *     operation
        *     - NOT_IMPLEMENTED if the operation can't be performed on
        *     the current OS
        *     - UNKNOWN_ERROR otherwise
        **/
        bool setNetmask(const char *a);

        /**
        * \brief
        *     Enable or disable the currently selected network device

        *     Enables or disables the currently selected network
        *     device according to the value of \c enable. Disabling a
        *     network device causes it not to be running any more. It
        *     is possible that its current address configuration is
        *     lost due to disabling it.
        *
        *     Enabling a device will bring it into a running state but
        *     suitable addresses may be still be missing for it to be
        *     usable.
        * \return
        *     \c true on error, \c false on success
        * \errors
        *     osal::SysError with IDs
        *
        *     - PERMISSION_DENIED if you lack privelege to perform the
        *     operation
        *     - UNKNOWN_ERROR otherwise
        **/
        bool setInterfaceStatus(bool enable);

        /**
        * \brief
        *     Enable or disable the promiscuous mode of the currently
        *     selected network device

        *     If promiscuous mode is enabled for a network device then
        *     you're able to receive network packets via that device
        *     that aren't destined for the device/the host but only
        *     passing through or passing to other applications.
        *
        *     This can typically be used via raw socket APIs which are
        *     provided in OSAL via osal::RawSocket
        * \note
        *     On Win32 there is no way to set promsicuous mode on
        *     a per-interface level. We can only set individual
        *     sockets into promiscuous mode there. This, in the end,
        *     still causes the device to become promiscuous, but
        *     probably the device will only be promiscuous as long as
        *     there are promiscuous sockets around. We can set
        *     promiscuous sockets via osal::RawSocket.
        * \return
        *     \c true on error, \c false on success
        * \errors
        *     osal::SysError with IDs
        *
        *     - PERMISSION_DENIED if you lack privelege to perform the
        *     operation
        *     - NOT_IMPLEMENTED if for the given network device
        *     there's no way to enable promiscuous mode
        *     - UNKNOWN_ERROR otherwise
        **/
        bool setPromiscuous(bool promiscuous);

    protected: // data

        //! OS handle
        NetDeviceHandle m_handle;

    };

}  // end of namespace osal

#endif
