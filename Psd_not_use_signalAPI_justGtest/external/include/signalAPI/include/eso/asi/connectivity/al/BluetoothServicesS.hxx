/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceS_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_BLUETOOTHSERVICESS_HXX
#define ASI_CONNECTIVITY_AL_BLUETOOTHSERVICESS_HXX

#include <common/Macros.hxx>

#include <comm/commtypes.hxx>
#include <comm/commidltypes.hxx>
#include <comm/CallEvent.hxx>
#include <asi/connectivity/al/BluetoothServicesServiceRegistration.hxx>
#include <asi/connectivity/al/StructBluetoothDevice.hxx>
#include <asi/connectivity/al/StructBtDeviceRecord.hxx>
#include <asi/connectivity/al/StructServiceVersions.hxx>
#include <asi/connectivity/al/StructSimplePairingInformation.hxx>

#include <asi/connectivity/al/Definitions.hxx>

#include <asi/connectivity/al/BluetoothServicesProxyReply.hxx>
#include <asi/connectivity/al/BluetoothServicesReplyS.hxx>

namespace asi
{
namespace connectivity
{
namespace al
{

    /**
    \brief  The al::BluetoothServices interface on tthe service side.
    \details
            A service instance needs to implement this interface.
    **/
    class BluetoothServicesS
    {
    public:
        BluetoothServicesS () {}
    // List of request methods
        /**
            
         * Start BT stack
         * @param vendorID VendorID to use (AUDI AG = 0x010E)
         * @param productID product identification to use (C7PA High Nav + LTE 0x0021)
         * @param version version information (P324 = 0x0324)
         * @param voiceRecSupported true if external speech recognition shall be supported
         * @param trustedDevices a list of known trusted devices
         * @param irk Byte array of 16bytes (generated random 128bit value)
         *
         * @startuml
         * BtApp -> BtStack: startBtStack([{X, linkey, ...}, [Y, linkkey, ...}])
         * alt INIT_OK
         * BtStack -> BtApp: bluetoothReady(true, LOCAL_ADDR, "14.44.xpY")
         * else INIT_NOK
         *  BtStack -> BtApp: bluetoothReady(false, LOCAL_ADDR, NULL)
         * end
         * @enduml
         
            startBtStack Method ID: 46
        **/
        virtual void startBtStack(
            const int16_t vendorID,
            const int16_t productID,
            const int16_t version,
            const bool voiceRecSupported,
            const CIPtr< CIPtrArray< asi::connectivity::al::BtDeviceRecord > >& trustedDevices,
            const CIPtr< CIUInt8Array >& irk
            ,BluetoothServicesProxyReply& reply
        ) = 0;
        /**
            
         * addDeviceRecord. Adds a link key to the Database. Used to insert a new link
         * key which was received over Out-Of-Band pairing (OOB) during runtime.
         
            addDeviceRecord Method ID: 11
        **/
        virtual void addDeviceRecord(
            const CIPtr< asi::connectivity::al::BtDeviceRecord >& trustedDevices
            ,BluetoothServicesProxyReply& reply
        ) = 0;
        /**
            
         * Refreshes the IRK after a factory reset.
         
            refreshIRK Method ID: 29
        **/
        virtual void refreshIRK(
            const CIPtr< CIUInt8Array >& irk
            ,BluetoothServicesProxyReply& reply
        ) = 0;
        /**
            startInquiry Method ID: 47
        **/
        virtual void startInquiry(
            const int32_t inquiryLength,
            const asi::connectivity::al::InquiryMode mode,
            const int64_t address
            ,BluetoothServicesProxyReply& reply
        ) = 0;
        /**
            abortInquiry Method ID: 0
        **/
        virtual void abortInquiry(
            
            BluetoothServicesProxyReply& reply
        ) = 0;
        /**
            *
         * Disconnect device completely (incl. ACL)
         * @param address Bluetooth address of device to disconnect
         * @param force false = clean disconnect, true = force disconnection of ACL
         
            disconnectDevice Method ID: 15
        **/
        virtual void disconnectDevice(
            const int64_t address,
            const bool force
            ,BluetoothServicesProxyReply& reply
        ) = 0;
        /**
            *
         * Initiate pairing to untrusted device.
         * @param address Bluetooth address of device to initiate pairing to
         * @param mitm_no_io Allow pairing to devices without I/O capabilities (might result in pairing without MITM protection, e.g. headsets)
         * @param pin In case of legacy pairing callee must provide 4 or 16 digit PIN
         
            pairUntrustedDevice Method ID: 27
        **/
        virtual void pairUntrustedDevice(
            const int64_t address,
            const bool mitm_no_io,
            const CIPtr< CIString >& pin
            ,BluetoothServicesProxyReply& reply
        ) = 0;
        /**
            acceptIncomingPairing Method ID: 6
        **/
        virtual void acceptIncomingPairing(
            const int64_t address,
            const CIPtr< CIString >& pin
            ,BluetoothServicesProxyReply& reply
        ) = 0;
        /**
            rejectIncomingPairing Method ID: 30
        **/
        virtual void rejectIncomingPairing(
            const int64_t address
            ,BluetoothServicesProxyReply& reply
        ) = 0;
        /**
            abortPairingRequest Method ID: 2
        **/
        virtual void abortPairingRequest(
            
            BluetoothServicesProxyReply& reply
        ) = 0;
        /**
            startService Method ID: 49
        **/
        virtual void startService(
            const int64_t address,
            const asi::connectivity::al::BluetoothService service,
            const int32_t serviceInstance
            ,BluetoothServicesProxyReply& reply
        ) = 0;
        /**
            stopService Method ID: 51
        **/
        virtual void stopService(
            const int64_t address,
            const asi::connectivity::al::BluetoothService service,
            const int32_t serviceInstance
            ,BluetoothServicesProxyReply& reply
        ) = 0;
        /**
            getFriendlyName Method ID: 24
        **/
        virtual void getFriendlyName(
            
            BluetoothServicesProxyReply& reply
        ) = 0;
        /**
            setFriendlyName Method ID: 40
        **/
        virtual void setFriendlyName(
            const CIPtr< CIString >& friendlyName
            ,BluetoothServicesProxyReply& reply
        ) = 0;
        /**
            getDiscoverableMode Method ID: 22
        **/
        virtual void getDiscoverableMode(
            
            BluetoothServicesProxyReply& reply
        ) = 0;
        /**
            setDiscoverableMode Method ID: 37
        **/
        virtual void setDiscoverableMode(
            const bool isDiscoverable
            ,BluetoothServicesProxyReply& reply
        ) = 0;
        /**
            getConnectableMode Method ID: 19
        **/
        virtual void getConnectableMode(
            
            BluetoothServicesProxyReply& reply
        ) = 0;
        /**
            setConnectableMode Method ID: 35
        **/
        virtual void setConnectableMode(
            const bool isConnectable
            ,BluetoothServicesProxyReply& reply
        ) = 0;
        /**
            getBluetoothEnabled Method ID: 17
        **/
        virtual void getBluetoothEnabled(
            
            BluetoothServicesProxyReply& reply
        ) = 0;
        /**
            setBluetoothEnabled Method ID: 33
        **/
        virtual void setBluetoothEnabled(
            const bool isEnabled
            ,BluetoothServicesProxyReply& reply
        ) = 0;
        /**
            deletePairing Method ID: 13
        **/
        virtual void deletePairing(
            const int64_t address
            ,BluetoothServicesProxyReply& reply
        ) = 0;
        /**
            *
         * @brief Tell the bluetooth services that a service is connectible or
         * not.
         *
         * @param service The bluetooth service in question.
         * @param connectable True for a connectible service, false otherwise.
         * @param bluetoothServiceDetails Certain settings for the service
         * connection. The settings depend on the BluetoothService in question.
         * Currently, the settings are:
         * <ul>
         *  <li>BLUETOOTH_SERVICE_A2DP_SRC<br />
         *   The lowest 8 Bit are used to dis-/enable specific audio codecs.
         *   Default codec is SBC which is always enabled. (0x0 equals SBC only).
         *   Further current codec-bit-assignments:
         *   <ul start="0">
         *    <li>AAC</li>
         *    <li>MP3</li>
         *    <li>aptX</li>
         *   </ul>
         *   Default value is 0xFF - all codecs supported.<br />
         *   The remainder of bluetoothServiceDetails is not evaluated as of right now.
         *  </li>
         * </ul>
         
            setServiceConnectable Method ID: 43
        **/
        virtual void setServiceConnectable(
            const asi::connectivity::al::BluetoothService service,
            const bool connectable,
            const uint32_t bluetoothServiceDetails
            ,BluetoothServicesProxyReply& reply
        ) = 0;
        /**
            setSniffMode Method ID: 45
        **/
        virtual void setSniffMode(
            const asi::connectivity::al::BtSniffMode mode
            ,BluetoothServicesProxyReply& reply
        ) = 0;
        /**
            acceptIncomingServiceRequest Method ID: 8
        **/
        virtual void acceptIncomingServiceRequest(
            const int64_t address,
            const asi::connectivity::al::BluetoothService service,
            const int32_t serviceInstance,
            const bool accept
            ,BluetoothServicesProxyReply& reply
        ) = 0;
        /**
            acceptIncomingObexAuthRequest Method ID: 4
        **/
        virtual void acceptIncomingObexAuthRequest(
            const int64_t address,
            const CIPtr< CIString >& userId,
            const CIPtr< CIString >& passwd
            ,BluetoothServicesProxyReply& reply
        ) = 0;
        /**
            stringRequest Method ID: 53
        **/
        virtual void stringRequest(
            const CIPtr< CIString >& str
            ,BluetoothServicesProxyReply& reply
        ) = 0;
        /**
            selectAudioSource Method ID: 32
        **/
        virtual void selectAudioSource(
            const int64_t address
            ,BluetoothServicesProxyReply& reply
        ) = 0;
        /**
            setEnhancedSafetyIndicator Method ID: 39
        **/
        virtual void setEnhancedSafetyIndicator(
            const bool active
            ,BluetoothServicesProxyReply& reply
        ) = 0;
        /**
            getCurrentRSSI Method ID: 21
        **/
        virtual void getCurrentRSSI(
            const int64_t address
            ,BluetoothServicesProxyReply& reply
        ) = 0;
        /**
            *
         * This is called by Bluetooth to give BtStack a hint about the link usage. This is usually called
         * on start of an action which involves creation of an ACL (get supported services, connect service).
         * BtStack will try to keep ACL as soon as it is established.
         * @param address Bluetooth address of the device to keep link
         * @param use_sdp If true, the stack will establish a SDP client connection to keep the link alive.
         *                This is a more aggressive approach and may force some phones to start pairing or
         *                something else.
         * @param timeout timeout <  0 link may be dropped immediately
         *                timeout == 0 keep link forever
         *                timeout >  0 delay in seconds after link may be dropped
         
            keepLinkAlive Method ID: 26
        **/
        virtual void keepLinkAlive(
            const int64_t address,
            const bool use_sdp,
            const int32_t timeout
            ,BluetoothServicesProxyReply& reply
        ) = 0;
        /**
            *
         * Accept or reject the currently active pairing request.
         * @param address The address of the device which requested the pairing.
         * @param accept If true, the pairing will be accepted, if false, it will be rejected.
         
            acceptLeIncomingPairing Method ID: 9
        **/
        virtual void acceptLeIncomingPairing(
            const int64_t address,
            const bool accept
            ,BluetoothServicesProxyReply& reply
        ) = 0;
        /**
            *
         * Set paging timeout for any further paging attempts (SDP query, remote name, connection attempt).
         * @param timeout Timeout is given in clock cycles (clock = 0.625ms, default is 5.12s = 8192 clocks * 0.625ms)
         
            setPagingTimeout Method ID: 42
        **/
        virtual void setPagingTimeout(
            const uint32_t timeout
            ,BluetoothServicesProxyReply& reply
        ) = 0;

        /*!
        \brief Informs the service about a connected client
        \param count The number of connected clients
        \param reply A proxy that can be used to reply to the connected client. If the client did
        not register its reply interface, calling valid() or isAlive() on reply will return false.
        In this case calling any other methods of the proxy will yield in undefined behaviour.
        */
        virtual void clientConnected(uint32_t count
            ,BluetoothServicesProxyReply& reply
        ) {}

        /*!
        \brief Informs the service that a client disconnected
        \param count the number of connected clients
        \param reply The proxy to the disconnected client. It is not alive any more, but can be used for comparison
        if it ever was valid.
        */
        virtual void clientDisconnected(uint32_t count
            ,BluetoothServicesProxyReply& reply
        ) {}

        /*!
        \brief  Registers this service instance.
        \param  instance_no is the instance number for the service.
        \param  p a user provided ActiveObject factory. This gives control over the threads that call the service.
        \return false on success, true on error
        \errorindicator
                return code
        \errors
                any possible error generated from COMM
        */
        bool registerSelf(uint32_t instance_no, const comm::ActiveObjectFactoryPtr& factory, comm::LifecycleListener* l=nullptr)
        {
            if (m_registration.isAlive()) {
                ipl_raise(comm::Error, comm::error::SELF_ALREADY_REGISTERED
                            ,((ipl::string)m_registration.getInstanceID()).c_str());
                return true;
            }

            m_registration =
                BluetoothServicesServiceRegistration(comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_AL_BLUETOOTHSERVICES_REQUEST), instance_no), static_cast<BluetoothServicesS*>(this), l, factory );
            if (!m_registration.valid()) {
                comm::error::fatal( "can't create ServiceRegistration, OOM ", COMM_HERE);
                return true;
            }
            return m_registration.registerService();
        }

        /*!
        \brief  Registers this service instance.
        \param  instance_no is the instance number for the service interface.
        \param  l is the lifecycle listern instance
        \return false on success, true on error
        \errorindicator
                return code
        \errors
                any possible error generated from COMM
        */
        bool registerSelf(uint32_t instance_no, comm::LifecycleListener* l=nullptr)
        {
            if (m_registration.isAlive()) {
                ipl_raise(comm::Error, comm::error::SELF_ALREADY_REGISTERED
                            ,((ipl::string)m_registration.getInstanceID()).c_str());
                return true;
            }

            m_registration =
                BluetoothServicesServiceRegistration(comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_AL_BLUETOOTHSERVICES_REQUEST), instance_no), static_cast<BluetoothServicesS*>(this), l );
            if (!m_registration.valid()) {
                comm::error::fatal( "can't create ServiceRegistration, OOM ", COMM_HERE);
                return true;
            }
            return m_registration.registerService();
        }

        /*!
        \brief  Registers this service instance.
        \param  instance_no is the instance number for the service interface
        \param  l is the lifecycle listern instance
        \return false on success, true on error
        \errorindicator
                return code
        \errors
                any possible error generated from COMM
        */
        bool registerSelf(uint32_t instance_no, comm::LifecycleListener& l)
        {
            return registerSelf (instance_no, &l);
        }

        /*!
        \brief  Unregisters this service instance.
        \return false on success, true on error
        \errorindicator
                return code
        \errors
                none
        */
        bool unregisterSelf()
        {
            if (!m_registration.isAlive()) {
                // not registered -> nothing to do.
                return false;
            }
            m_registration.unregisterService();
            // must not be alive after unregistration
            IPL_ASSERT(!m_registration.isAlive());
            // let go of the reference
            m_registration = BluetoothServicesServiceRegistration();
            return false;
        }

        /*!
        \brief  Unregisters this service instance and calls a callback.
        \return false if the service is being unregistered, true on error
                The callback is called only if false is returned.
                Errors are:
                <ul>
                <li>the service registration is not valid
                <li>an unregisterSelf() or ServiceRegistration::unregisterService() or
                    or ServiceRegistration::unregisterAndNotify had already been called.
                <li>the callback is NULL.
                </ul>
        \errorindicator
                return code
        \errors
                \see comm::ServiceRegistration::unregisterAndNotify
        */
        bool unregisterSelf(comm::ServiceReleasedFct callback, void* ctx) // NOSONAR - must not be changed because of API compatibility
        {
            // to not race with the callback. we can't touch m_registration after
            // calling unregisterAndNotify
            // make a temporary copy
            BluetoothServicesServiceRegistration tmp{m_registration};
            // let go of the reference the member holds
            m_registration = BluetoothServicesServiceRegistration();
            // call unregisterAndNotify
            return tmp.unregisterAndNotify(callback, ctx);
        }

        virtual ~BluetoothServicesS()
        {
            // unregister in case it wasn't done by the caller.
            unregisterSelf();
        }

        // call ids
        void
        startBtStackCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<BluetoothServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 46;
            ce.assign(inst, mid);
        }
        void
        addDeviceRecordCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<BluetoothServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 11;
            ce.assign(inst, mid);
        }
        void
        refreshIRKCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<BluetoothServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 29;
            ce.assign(inst, mid);
        }
        void
        startInquiryCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<BluetoothServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 47;
            ce.assign(inst, mid);
        }
        void
        abortInquiryCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<BluetoothServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 0;
            ce.assign(inst, mid);
        }
        void
        disconnectDeviceCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<BluetoothServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 15;
            ce.assign(inst, mid);
        }
        void
        pairUntrustedDeviceCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<BluetoothServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 27;
            ce.assign(inst, mid);
        }
        void
        acceptIncomingPairingCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<BluetoothServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 6;
            ce.assign(inst, mid);
        }
        void
        rejectIncomingPairingCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<BluetoothServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 30;
            ce.assign(inst, mid);
        }
        void
        abortPairingRequestCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<BluetoothServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 2;
            ce.assign(inst, mid);
        }
        void
        startServiceCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<BluetoothServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 49;
            ce.assign(inst, mid);
        }
        void
        stopServiceCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<BluetoothServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 51;
            ce.assign(inst, mid);
        }
        void
        getFriendlyNameCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<BluetoothServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 24;
            ce.assign(inst, mid);
        }
        void
        setFriendlyNameCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<BluetoothServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 40;
            ce.assign(inst, mid);
        }
        void
        getDiscoverableModeCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<BluetoothServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 22;
            ce.assign(inst, mid);
        }
        void
        setDiscoverableModeCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<BluetoothServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 37;
            ce.assign(inst, mid);
        }
        void
        getConnectableModeCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<BluetoothServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 19;
            ce.assign(inst, mid);
        }
        void
        setConnectableModeCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<BluetoothServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 35;
            ce.assign(inst, mid);
        }
        void
        getBluetoothEnabledCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<BluetoothServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 17;
            ce.assign(inst, mid);
        }
        void
        setBluetoothEnabledCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<BluetoothServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 33;
            ce.assign(inst, mid);
        }
        void
        deletePairingCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<BluetoothServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 13;
            ce.assign(inst, mid);
        }
        void
        setServiceConnectableCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<BluetoothServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 43;
            ce.assign(inst, mid);
        }
        void
        setSniffModeCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<BluetoothServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 45;
            ce.assign(inst, mid);
        }
        void
        acceptIncomingServiceRequestCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<BluetoothServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 8;
            ce.assign(inst, mid);
        }
        void
        acceptIncomingObexAuthRequestCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<BluetoothServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 4;
            ce.assign(inst, mid);
        }
        void
        stringRequestCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<BluetoothServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 53;
            ce.assign(inst, mid);
        }
        void
        selectAudioSourceCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<BluetoothServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 32;
            ce.assign(inst, mid);
        }
        void
        setEnhancedSafetyIndicatorCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<BluetoothServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 39;
            ce.assign(inst, mid);
        }
        void
        getCurrentRSSICallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<BluetoothServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 21;
            ce.assign(inst, mid);
        }
        void
        keepLinkAliveCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<BluetoothServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 26;
            ce.assign(inst, mid);
        }
        void
        acceptLeIncomingPairingCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<BluetoothServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 9;
            ce.assign(inst, mid);
        }
        void
        setPagingTimeoutCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<BluetoothServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 42;
            ce.assign(inst, mid);
        }

    protected:
        BluetoothServicesServiceRegistration m_registration;
    };

} //namespace asi
} //namespace connectivity
} //namespace al
#endif// ASI_CONNECTIVITY_AL_BLUETOOTHSERVICESS_HXX
