/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

/****************************************************************************/
#ifndef OSAL_NETWORKINTERFACE_HXX
#define OSAL_NETWORKINTERFACE_HXX
/****************************************************************************/

#include <ipl_config.h>
#include <osal/osal_dso.h>

// For now differences between OSes are miniscule,
// so let’s handle them right here
#ifdef IPL_OS_WINDOWS
#include <iplbase/win32.h>
#endif

#include <common/types/list.hxx>
#include "NetworkAddress.hxx"

/****************************************************************************/

namespace osal {

/****************************************************************************/

    /*!
        \brief Representation of one network interface
        plus some methods to mangle it

    */
    struct OSAL_EXPORT NetworkInterface {

        struct AddrInfo;
        struct Info;

#ifdef IPL_OS_WINDOWS
        typedef ULONG Index;
#else
        typedef unsigned Index;
#endif

        //! \brief OS internal unique interface number
        Index index;

        //! \brief Value of \ref index when invalid
        static const Index INVALID
#ifdef IPL_OS_WINDOWS
            =NET_IFINDEX_UNSPECIFIED;
#else
            =0;
#endif

        NetworkInterface(Index index=INVALID) IPL_NOEXCEPT: index(index) {}
        NetworkInterface(const ipl::string &name) IPL_NOEXCEPT;

        operator ipl::PseudoBool () const IPL_NOEXCEPT {
            return index==INVALID? ipl::PSEUDO_FALSE : &ipl::PSEUDO_TRUE;
        }
        operator Index () const IPL_NOEXCEPT { return index; }

        bool operator == (const NetworkInterface &other) const IPL_NOEXCEPT {
            return index==other.index;
        }
        bool operator != (const NetworkInterface &other) const IPL_NOEXCEPT {
            return !operator == (other);
        }
    };

/****************************************************************************/

    /*!
        \brief All you need to know about one NetworkInterface's address
    */
    struct OSAL_EXPORT NetworkInterface::AddrInfo {

        NetworkAddress address;
        NetworkAddress netmask;
        NetworkAddress broadcast;

        AddrInfo() IPL_NOEXCEPT {}

        //! \brief Equality of address itself, ignoring netmask and broadcast address
        bool operator == (const AddrInfo &other) const IPL_NOEXCEPT {
            return address==other.address;
        }
        //! \brief Equality of address itself, ignoring netmask and broadcast address
        bool operator != (const AddrInfo &other) const IPL_NOEXCEPT {
            return ! operator == (other);
        }

    };

/****************************************************************************/

    /*!
        \brief Description of one network interface

        Note that calling the methods mangles the underlying interface
        but not this description object.
    */
    struct OSAL_EXPORT NetworkInterface::Info: public NetworkInterface {

        ipl::string name;
        //! \brief Might be 0 if no information is available
        size_t mtu;
        //! \brief Switched on
        bool enabled;
        //! \brief Cable connected, radio connection established, whatever
        bool carrier;
        bool can_broadcast;
        bool pointtopoint;
        bool loopback;
        typedef ipl::list<AddrInfo> AddrInfos;
        //! \brief All known addresses of this interface
        AddrInfos addrinfos;

        Info(Index index=0, const ipl::string &name="", size_t mtu=0,
             bool enabled=false, bool carrier=false,
             bool can_broadcast=false, bool pointtopoint=false,
             bool loopback=false,
             const AddrInfos &addrinfos=AddrInfos()) IPL_NOEXCEPT:
            NetworkInterface(index), name(name), mtu(mtu), enabled(enabled),
            carrier(carrier), can_broadcast(can_broadcast),
            pointtopoint(pointtopoint), loopback(loopback),
            addrinfos(addrinfos) {}
    };

/****************************************************************************/

}  // end of namespace osal

/****************************************************************************/
#endif
