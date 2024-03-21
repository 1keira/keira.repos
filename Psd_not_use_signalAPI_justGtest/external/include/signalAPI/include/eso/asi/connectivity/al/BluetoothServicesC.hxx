/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceC_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_BLUETOOTHSERVICESC_HXX
#define ASI_CONNECTIVITY_AL_BLUETOOTHSERVICESC_HXX

#include <ipl_config.h>
#include <comm/commidltypes.hxx>
#include <asi/connectivity/al/StructBluetoothDevice.hxx>
#include <asi/connectivity/al/StructBtDeviceRecord.hxx>
#include <asi/connectivity/al/StructServiceVersions.hxx>
#include <asi/connectivity/al/StructSimplePairingInformation.hxx>
#include <asi/connectivity/al/Definitions.hxx>

namespace asi
{
namespace connectivity
{
namespace al
{

    /**
    \brief The al::BluetoothServices interface on the client side.
    \details
            A proxy implements this interface.
    **/
    class BluetoothServicesC
    {
    public:
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
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool startBtStack(
            const int16_t vendorID,
            const int16_t productID,
            const int16_t version,
            const bool voiceRecSupported,
            const CIPtr< CIPtrArray< asi::connectivity::al::BtDeviceRecord > >& trustedDevices,
            const CIPtr< CIUInt8Array >& irk
        ) const IPL_NOEXCEPT = 0;

        /**
            
         * addDeviceRecord. Adds a link key to the Database. Used to insert a new link
         * key which was received over Out-Of-Band pairing (OOB) during runtime.
         
            addDeviceRecord Method ID: 11
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool addDeviceRecord(
            const CIPtr< asi::connectivity::al::BtDeviceRecord >& trustedDevices
        ) const IPL_NOEXCEPT = 0;

        /**
            
         * Refreshes the IRK after a factory reset.
         
            refreshIRK Method ID: 29
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool refreshIRK(
            const CIPtr< CIUInt8Array >& irk
        ) const IPL_NOEXCEPT = 0;

        /**
            startInquiry Method ID: 47
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool startInquiry(
            const int32_t inquiryLength,
            const asi::connectivity::al::InquiryMode mode,
            const int64_t address
        ) const IPL_NOEXCEPT = 0;

        /**
            abortInquiry Method ID: 0
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool abortInquiry(
            
        ) const IPL_NOEXCEPT = 0;

        /**
            *
         * Disconnect device completely (incl. ACL)
         * @param address Bluetooth address of device to disconnect
         * @param force false = clean disconnect, true = force disconnection of ACL
         
            disconnectDevice Method ID: 15
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool disconnectDevice(
            const int64_t address,
            const bool force
        ) const IPL_NOEXCEPT = 0;

        /**
            *
         * Initiate pairing to untrusted device.
         * @param address Bluetooth address of device to initiate pairing to
         * @param mitm_no_io Allow pairing to devices without I/O capabilities (might result in pairing without MITM protection, e.g. headsets)
         * @param pin In case of legacy pairing callee must provide 4 or 16 digit PIN
         
            pairUntrustedDevice Method ID: 27
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool pairUntrustedDevice(
            const int64_t address,
            const bool mitm_no_io,
            const CIPtr< CIString >& pin
        ) const IPL_NOEXCEPT = 0;

        /**
            acceptIncomingPairing Method ID: 6
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool acceptIncomingPairing(
            const int64_t address,
            const CIPtr< CIString >& pin
        ) const IPL_NOEXCEPT = 0;

        /**
            rejectIncomingPairing Method ID: 30
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool rejectIncomingPairing(
            const int64_t address
        ) const IPL_NOEXCEPT = 0;

        /**
            abortPairingRequest Method ID: 2
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool abortPairingRequest(
            
        ) const IPL_NOEXCEPT = 0;

        /**
            startService Method ID: 49
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool startService(
            const int64_t address,
            const asi::connectivity::al::BluetoothService service,
            const int32_t serviceInstance
        ) const IPL_NOEXCEPT = 0;

        /**
            stopService Method ID: 51
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool stopService(
            const int64_t address,
            const asi::connectivity::al::BluetoothService service,
            const int32_t serviceInstance
        ) const IPL_NOEXCEPT = 0;

        /**
            getFriendlyName Method ID: 24
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool getFriendlyName(
            
        ) const IPL_NOEXCEPT = 0;

        /**
            setFriendlyName Method ID: 40
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool setFriendlyName(
            const CIPtr< CIString >& friendlyName
        ) const IPL_NOEXCEPT = 0;

        /**
            getDiscoverableMode Method ID: 22
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool getDiscoverableMode(
            
        ) const IPL_NOEXCEPT = 0;

        /**
            setDiscoverableMode Method ID: 37
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool setDiscoverableMode(
            const bool isDiscoverable
        ) const IPL_NOEXCEPT = 0;

        /**
            getConnectableMode Method ID: 19
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool getConnectableMode(
            
        ) const IPL_NOEXCEPT = 0;

        /**
            setConnectableMode Method ID: 35
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool setConnectableMode(
            const bool isConnectable
        ) const IPL_NOEXCEPT = 0;

        /**
            getBluetoothEnabled Method ID: 17
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool getBluetoothEnabled(
            
        ) const IPL_NOEXCEPT = 0;

        /**
            setBluetoothEnabled Method ID: 33
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool setBluetoothEnabled(
            const bool isEnabled
        ) const IPL_NOEXCEPT = 0;

        /**
            deletePairing Method ID: 13
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool deletePairing(
            const int64_t address
        ) const IPL_NOEXCEPT = 0;

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
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool setServiceConnectable(
            const asi::connectivity::al::BluetoothService service,
            const bool connectable,
            const uint32_t bluetoothServiceDetails
        ) const IPL_NOEXCEPT = 0;

        /**
            setSniffMode Method ID: 45
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool setSniffMode(
            const asi::connectivity::al::BtSniffMode mode
        ) const IPL_NOEXCEPT = 0;

        /**
            acceptIncomingServiceRequest Method ID: 8
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool acceptIncomingServiceRequest(
            const int64_t address,
            const asi::connectivity::al::BluetoothService service,
            const int32_t serviceInstance,
            const bool accept
        ) const IPL_NOEXCEPT = 0;

        /**
            acceptIncomingObexAuthRequest Method ID: 4
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool acceptIncomingObexAuthRequest(
            const int64_t address,
            const CIPtr< CIString >& userId,
            const CIPtr< CIString >& passwd
        ) const IPL_NOEXCEPT = 0;

        /**
            stringRequest Method ID: 53
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool stringRequest(
            const CIPtr< CIString >& str
        ) const IPL_NOEXCEPT = 0;

        /**
            selectAudioSource Method ID: 32
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool selectAudioSource(
            const int64_t address
        ) const IPL_NOEXCEPT = 0;

        /**
            setEnhancedSafetyIndicator Method ID: 39
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool setEnhancedSafetyIndicator(
            const bool active
        ) const IPL_NOEXCEPT = 0;

        /**
            getCurrentRSSI Method ID: 21
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool getCurrentRSSI(
            const int64_t address
        ) const IPL_NOEXCEPT = 0;

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
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool keepLinkAlive(
            const int64_t address,
            const bool use_sdp,
            const int32_t timeout
        ) const IPL_NOEXCEPT = 0;

        /**
            *
         * Accept or reject the currently active pairing request.
         * @param address The address of the device which requested the pairing.
         * @param accept If true, the pairing will be accepted, if false, it will be rejected.
         
            acceptLeIncomingPairing Method ID: 9
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool acceptLeIncomingPairing(
            const int64_t address,
            const bool accept
        ) const IPL_NOEXCEPT = 0;

        /**
            *
         * Set paging timeout for any further paging attempts (SDP query, remote name, connection attempt).
         * @param timeout Timeout is given in clock cycles (clock = 0.625ms, default is 5.12s = 8192 clocks * 0.625ms)
         
            setPagingTimeout Method ID: 42
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool setPagingTimeout(
            const uint32_t timeout
        ) const IPL_NOEXCEPT = 0;

        BluetoothServicesC()  {}
        virtual ~BluetoothServicesC() {}
    protected:
        friend class BluetoothServicesProxy;
    };

}//namespace asi
}//namespace connectivity
}//namespace al
#endif// ASI_CONNECTIVITY_AL_BLUETOOTHSERVICESC_HXX
