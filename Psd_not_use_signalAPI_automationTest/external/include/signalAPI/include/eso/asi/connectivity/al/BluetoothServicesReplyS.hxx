/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceReplyS_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_BLUETOOTHSERVICES_REPLYS_HXX
#define ASI_CONNECTIVITY_AL_BLUETOOTHSERVICES_REPLYS_HXX
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
    \brief  Interface declaration, which is implemented by the proxy, and used/called by any user of this interface
    **/
    class BluetoothServicesReplyS
    {
    public:
        // List of reply methods
            /**
             Is called when bluetooth commands are accepted by HSTI 
            bluetoothReady Method ID: 12
            **/
        virtual bool bluetoothReady (
            const bool ready,
            const int64_t bluetoothAddress,
            const CIPtr< CIString >& firmwareVersion,
            const uint32_t CoD
        ) IPL_NOEXCEPT = 0;

            /**
            startInquiryResponse Method ID: 48
            **/
        virtual bool startInquiryResponse (
            const asi::connectivity::al::ResultType result,
            const int32_t extendedErrorCode
        ) IPL_NOEXCEPT = 0;

            /**
            abortInquiryResponse Method ID: 1
            **/
        virtual bool abortInquiryResponse (
            const asi::connectivity::al::ResultType result,
            const int32_t extendedErrorCode
        ) IPL_NOEXCEPT = 0;

            /**
            updDiscoveredDevices Method ID: 62
            **/
        virtual bool updDiscoveredDevices (
            const CIPtr< asi::connectivity::al::BluetoothDevice >& device
        ) IPL_NOEXCEPT = 0;

            /**
            updEndOfInquiry Method ID: 63
            **/
        virtual bool updEndOfInquiry (
            
        ) IPL_NOEXCEPT = 0;

            /**
            disconnectDeviceResponse Method ID: 16
            **/
        virtual bool disconnectDeviceResponse (
            const asi::connectivity::al::ResultType result,
            const int32_t extendedErrorCode
        ) IPL_NOEXCEPT = 0;

            /**
            pairUntrustedDeviceResponse Method ID: 28
            **/
        virtual bool pairUntrustedDeviceResponse (
            const asi::connectivity::al::ResultType result,
            const int32_t extendedErrorCode
        ) IPL_NOEXCEPT = 0;

            /**
            *
        * The pairing status to a specific device has changed
         *
         * @param device This is the affected device
         * @param state The new pairing state
         
            updPairingStatus Method ID: 71
            **/
        virtual bool updPairingStatus (
            const CIPtr< asi::connectivity::al::BluetoothDevice >& device,
            const asi::connectivity::al::PairingState state
        ) IPL_NOEXCEPT = 0;

            /**
            * Called if a device is brutally disconnected
         *
         * @param address This was the device that has been disconnected brutally 
            updBrutalDisconnected Method ID: 58
            **/
        virtual bool updBrutalDisconnected (
            const int64_t address
        ) IPL_NOEXCEPT = 0;

            /**
            * Update the device information like capabilities, friendly name
         *
         * @param device The device where new information is available 
            updDeviceInformation Method ID: 60
            **/
        virtual bool updDeviceInformation (
            const CIPtr< asi::connectivity::al::BluetoothDevice >& device,
            const CIPtr< asi::connectivity::al::ServiceVersions >& versions
        ) IPL_NOEXCEPT = 0;

            /**
            updIncomingPairingRequest Method ID: 66
            **/
        virtual bool updIncomingPairingRequest (
            const CIPtr< asi::connectivity::al::BluetoothDevice >& device,
            const CIPtr< asi::connectivity::al::SimplePairingInformation >& sspInfo
        ) IPL_NOEXCEPT = 0;

            /**
            acceptIncomingPairingResponse Method ID: 7
            **/
        virtual bool acceptIncomingPairingResponse (
            const asi::connectivity::al::ResultType result,
            const int32_t extendedErrorCode
        ) IPL_NOEXCEPT = 0;

            /**
            rejectIncomingPairingResponse Method ID: 31
            **/
        virtual bool rejectIncomingPairingResponse (
            const asi::connectivity::al::ResultType result,
            const int32_t extendedErrorCode
        ) IPL_NOEXCEPT = 0;

            /**
            abortPairingResponse Method ID: 3
            **/
        virtual bool abortPairingResponse (
            const asi::connectivity::al::ResultType result,
            const int32_t extendedErrorCode
        ) IPL_NOEXCEPT = 0;

            /**
            updDeviceRecord Method ID: 61
            **/
        virtual bool updDeviceRecord (
            const CIPtr< asi::connectivity::al::BtDeviceRecord >& record
        ) IPL_NOEXCEPT = 0;

            /**
            startServiceResponse Method ID: 50
            **/
        virtual bool startServiceResponse (
            const asi::connectivity::al::ResultType result,
            const int32_t extendedErrorCode
        ) IPL_NOEXCEPT = 0;

            /**
            stopServiceResponse Method ID: 52
            **/
        virtual bool stopServiceResponse (
            const asi::connectivity::al::ResultType result,
            const int32_t extendedErrorCode
        ) IPL_NOEXCEPT = 0;

            /**
            updServiceStatus Method ID: 72
            **/
        virtual bool updServiceStatus (
            const int64_t address,
            const asi::connectivity::al::BluetoothService service,
            const int32_t serviceInstance,
            const asi::connectivity::al::BluetoothServiceStatus status
        ) IPL_NOEXCEPT = 0;

            /**
            getFriendlyNameResponse Method ID: 25
            **/
        virtual bool getFriendlyNameResponse (
            const CIPtr< CIString >& friendlyName,
            const asi::connectivity::al::ResultType result,
            const int32_t extendedErrorCode
        ) IPL_NOEXCEPT = 0;

            /**
            setFriendlyNameResponse Method ID: 41
            **/
        virtual bool setFriendlyNameResponse (
            const asi::connectivity::al::ResultType result,
            const int32_t extendedErrorCode
        ) IPL_NOEXCEPT = 0;

            /**
            getDiscoverableModeResponse Method ID: 23
            **/
        virtual bool getDiscoverableModeResponse (
            const bool isDiscoverable,
            const asi::connectivity::al::ResultType result,
            const int32_t extendedErrorCode
        ) IPL_NOEXCEPT = 0;

            /**
            setDiscoverableModeResponse Method ID: 38
            **/
        virtual bool setDiscoverableModeResponse (
            const asi::connectivity::al::ResultType result,
            const int32_t extendedErrorCode
        ) IPL_NOEXCEPT = 0;

            /**
            getConnectableModeResponse Method ID: 20
            **/
        virtual bool getConnectableModeResponse (
            const bool isConnectable,
            const asi::connectivity::al::ResultType result,
            const int32_t extendedErrorCode
        ) IPL_NOEXCEPT = 0;

            /**
            setConnectableModeResponse Method ID: 36
            **/
        virtual bool setConnectableModeResponse (
            const asi::connectivity::al::ResultType result,
            const int32_t extendedErrorCode
        ) IPL_NOEXCEPT = 0;

            /**
            getBluetoothEnabledResponse Method ID: 18
            **/
        virtual bool getBluetoothEnabledResponse (
            const asi::connectivity::al::ResultType result,
            const int32_t extendedErrorCode
        ) IPL_NOEXCEPT = 0;

            /**
            setBluetoothEnabledResponse Method ID: 34
            **/
        virtual bool setBluetoothEnabledResponse (
            const asi::connectivity::al::ResultType result,
            const int32_t extendedErrorCode
        ) IPL_NOEXCEPT = 0;

            /**
            updBluetoothEnabled Method ID: 56
            **/
        virtual bool updBluetoothEnabled (
            const bool isEnabled
        ) IPL_NOEXCEPT = 0;

            /**
            deletePairingResponse Method ID: 14
            **/
        virtual bool deletePairingResponse (
            const int64_t address,
            const asi::connectivity::al::ResultType result
        ) IPL_NOEXCEPT = 0;

            /**
            setServiceConnectableResponse Method ID: 44
            **/
        virtual bool setServiceConnectableResponse (
            const asi::connectivity::al::ResultType result,
            const int32_t extendedErrorCode
        ) IPL_NOEXCEPT = 0;

            /**
            updIncomingServiceRequest Method ID: 67
            **/
        virtual bool updIncomingServiceRequest (
            const int64_t address,
            const asi::connectivity::al::BluetoothService service,
            const int32_t serviceInstance,
            const bool isPending
        ) IPL_NOEXCEPT = 0;

            /**
            updMasterSlaveMode Method ID: 69
            **/
        virtual bool updMasterSlaveMode (
            const int64_t address,
            const bool isMaster
        ) IPL_NOEXCEPT = 0;

            /**
            updBluetoothStreamingState Method ID: 57
            **/
        virtual bool updBluetoothStreamingState (
            const int64_t address,
            const bool streamingActive
        ) IPL_NOEXCEPT = 0;

            /**
            updIncomingObexAuthRequest Method ID: 65
            **/
        virtual bool updIncomingObexAuthRequest (
            const int64_t address,
            const bool isUserNeeded,
            const bool isReadOnly,
            const CIPtr< CIString >& realm
        ) IPL_NOEXCEPT = 0;

            /**
            acceptIncomingObexAuthRequestResponse Method ID: 5
            **/
        virtual bool acceptIncomingObexAuthRequestResponse (
            const int64_t address,
            const asi::connectivity::al::ResultType result,
            const int32_t extendedErrorCode
        ) IPL_NOEXCEPT = 0;

            /**
            updBTError Method ID: 55
            **/
        virtual bool updBTError (
            const int64_t address,
            const int32_t errorCode
        ) IPL_NOEXCEPT = 0;

            /**
            stringResponse Method ID: 54
            **/
        virtual bool stringResponse (
            const CIPtr< CIString >& str
        ) IPL_NOEXCEPT = 0;

            /**
            updIapDevicePath Method ID: 64
            **/
        virtual bool updIapDevicePath (
            const int64_t address,
            const CIPtr< CIString >& path
        ) IPL_NOEXCEPT = 0;

            /**
            updMobileDeviceInfoType Method ID: 70
            **/
        virtual bool updMobileDeviceInfoType (
            const int64_t address,
            const asi::connectivity::al::MobileDeviceInfoType type,
            const CIPtr< CIString >& value
        ) IPL_NOEXCEPT = 0;

            /**
            updCurrentRSSI Method ID: 59
            **/
        virtual bool updCurrentRSSI (
            const asi::connectivity::al::ResultType result,
            const int64_t address,
            const int32_t value,
            const int32_t extendedErrorCode
        ) IPL_NOEXCEPT = 0;

            /**
            *
         * Indicates an infoming pairing request from a bluetooth LE device.
         * @param device The device requesting the connection.
         * @sspInfo Pairing information.
         
            updLeIncomingPairingRequest Method ID: 68
            **/
        virtual bool updLeIncomingPairingRequest (
            const CIPtr< asi::connectivity::al::BluetoothDevice >& device,
            const CIPtr< asi::connectivity::al::SimplePairingInformation >& sspInfo
        ) IPL_NOEXCEPT = 0;

            /**
            acceptLeIncomingPairingResponse Method ID: 10
            **/
        virtual bool acceptLeIncomingPairingResponse (
            const asi::connectivity::al::ResultType result,
            const int32_t extendedErrorCode
        ) IPL_NOEXCEPT = 0;

        virtual ~BluetoothServicesReplyS() {}
    };

}// namespace asi
}// namespace connectivity
}// namespace al


#endif// ASI_CONNECTIVITY_AL_BLUETOOTHSERVICES_REPLYS_HXX
