/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

/****************************************************************************/
#ifndef OSAL_NETDEVICEMONITOR_HXX
#define OSAL_NETDEVICEMONITOR_HXX
/****************************************************************************/

#include <ipl_config.h>
#include <string.h>

#include <common/NonCopyable.hxx>
#include <common/types/list.hxx>
#include <common/types/map.hxx>

#include <osal/osal.hxx>
#include <osal/osal_dso.h>
#include "NetworkAddress.hxx"
#include "NetworkInterface.hxx"

#ifdef interface
// Aah, Windows strikes again…
#undef interface
#endif

/****************************************************************************/

namespace osal {

/****************************************************************************/

    class NetworkInterfaceList;
    class NetDeviceMonitorImpl;

/****************************************************************************/

    /*!
        \brief Monitor network interfaces an report changes

        \b Note: There is no unit test for this as that test woule need to
        create, destroy and otherwise mangle network interfaces within the
        test system. To ensure that all works OK, find and run the
        NetDeviceMonitorSample and check its output against the system state.
    */
    class OSAL_EXPORT NetDeviceMonitor:
        public ipl::NonCopyable {

    public:

        typedef NetworkAddress Address;
        typedef NetworkInterface::AddrInfo AddrInfo;
        typedef NetworkInterface::Info Interface;

        /*!
            \brief Callback class for changes in network configuration

            Derive from this class, implement only the virtual methods
            you are interested in, pass the object to your NetDeviceMonitor
            as a listener.
        */
        class OSAL_EXPORT Listener/*: public NetDeviceMonitor_KnowerOfInformation*/ {

        public:

            typedef NetworkAddress Address;
            typedef NetworkInterface::AddrInfo AddrInfo;
            typedef NetworkInterface::Info Interface;

            virtual ~Listener();

            //! \brief There is a new network interface
            virtual void interface_appeared(const Interface &interface);
            //! \brief Some network interface is gone now
            virtual void interface_disappeared(const Interface &interface);
            //! \brief Some network interface's status might have changed
            virtual void interface_status(const Interface &interface);
            //! \brief There is a new network address
            virtual void address_appeared(const AddrInfo &addrinfo,
                                          const Interface &interface);
            //! \brief Some network address is gone now
            virtual void address_disappeared(const AddrInfo &addrinfo,
                                             const Interface &interface);
            //! \brief Some network address (including its interface) can be used now
            virtual void address_operable(const AddrInfo &addrinfo,
                                          const Interface &interface);
            //! \brief Some network address (including its interface) cannot be used anymore
            virtual void address_inoperable(const AddrInfo &addrinfo,
                                            const Interface &interface);
        };

        //! \brief \a l must not be NULL
        NetDeviceMonitor(Listener *l);
        ~NetDeviceMonitor();

        /*!
            \brief Main loop waiting for events and calling callbacks

            Must be called to receive updates on the passed Listener.
            All updates will come from the thread that invokes watch().
            Will block until stopWatching() is called from any thread,
            including Listener::updated()

            \return \c true on error, \c false on stopWatching()
        */
        bool watch();

        /*!
            \brief Make watch() return independently of available updates
        */
        void stopWatching();

    protected:
        friend class NetDeviceMonitorImpl;  // Impl can call us back
        void interface_appeared(unsigned short index, const char *name);
        void interface_up(unsigned short index, bool can_broadcast,
                          bool pointtopoint, bool loopback, int mtu,
                          bool enabled, bool connected);
        void interface_disappeared(int index);
        void address_appeared(unsigned short index, const AddrInfo &addrinfo);
        void address_disappeared(unsigned short index, const AddrInfo &addrinfo);

    private:
        Listener *m_listener;
        typedef ipl::map</*int*/Interface::Index, Interface> Interfaces;
        Interfaces interfaces;
        NetDeviceMonitorImpl *m_impl;
    };

/****************************************************************************/

}  // end of namespace osal

/****************************************************************************/
#endif
