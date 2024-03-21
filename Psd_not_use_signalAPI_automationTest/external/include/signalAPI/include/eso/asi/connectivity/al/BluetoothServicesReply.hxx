/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceReply_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_BLUETOOTHSERVICESREPLY_HXX
#define ASI_CONNECTIVITY_AL_BLUETOOTHSERVICESREPLY_HXX

#include <comm/commtypes.hxx>
#include <comm/commidltypes.hxx>
#include <comm/CallEvent.hxx>
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
    \brief  Declaration of the reply interface, which must be implemented by any user of this interface
    **/
    class BluetoothServicesReply {

    public:
    // List of reply methods
            /**
             Is called when bluetooth commands are accepted by HSTI 
            bluetoothReady Method ID: 12
            **/
        virtual void bluetoothReady(
            const bool ready,
            const int64_t bluetoothAddress,
            const CIPtr< CIString >& firmwareVersion,
            const uint32_t CoD
        ) = 0;
            /**
            startInquiryResponse Method ID: 48
            **/
        virtual void startInquiryResponse(
            const asi::connectivity::al::ResultType result,
            const int32_t extendedErrorCode
        ) = 0;
            /**
            abortInquiryResponse Method ID: 1
            **/
        virtual void abortInquiryResponse(
            const asi::connectivity::al::ResultType result,
            const int32_t extendedErrorCode
        ) = 0;
            /**
            updDiscoveredDevices Method ID: 62
            **/
        virtual void updDiscoveredDevices(
            const CIPtr< asi::connectivity::al::BluetoothDevice >& device
        ) = 0;
            /**
            updEndOfInquiry Method ID: 63
            **/
        virtual void updEndOfInquiry(
            
        ) = 0;
            /**
            disconnectDeviceResponse Method ID: 16
            **/
        virtual void disconnectDeviceResponse(
            const asi::connectivity::al::ResultType result,
            const int32_t extendedErrorCode
        ) = 0;
            /**
            pairUntrustedDeviceResponse Method ID: 28
            **/
        virtual void pairUntrustedDeviceResponse(
            const asi::connectivity::al::ResultType result,
            const int32_t extendedErrorCode
        ) = 0;
            /**
            *
        * The pairing status to a specific device has changed
         *
         * @param device This is the affected device
         * @param state The new pairing state
         
            updPairingStatus Method ID: 71
            **/
        virtual void updPairingStatus(
            const CIPtr< asi::connectivity::al::BluetoothDevice >& device,
            const asi::connectivity::al::PairingState state
        ) = 0;
            /**
            * Called if a device is brutally disconnected
         *
         * @param address This was the device that has been disconnected brutally 
            updBrutalDisconnected Method ID: 58
            **/
        virtual void updBrutalDisconnected(
            const int64_t address
        ) = 0;
            /**
            * Update the device information like capabilities, friendly name
         *
         * @param device The device where new information is available 
            updDeviceInformation Method ID: 60
            **/
        virtual void updDeviceInformation(
            const CIPtr< asi::connectivity::al::BluetoothDevice >& device,
            const CIPtr< asi::connectivity::al::ServiceVersions >& versions
        ) = 0;
            /**
            updIncomingPairingRequest Method ID: 66
            **/
        virtual void updIncomingPairingRequest(
            const CIPtr< asi::connectivity::al::BluetoothDevice >& device,
            const CIPtr< asi::connectivity::al::SimplePairingInformation >& sspInfo
        ) = 0;
            /**
            acceptIncomingPairingResponse Method ID: 7
            **/
        virtual void acceptIncomingPairingResponse(
            const asi::connectivity::al::ResultType result,
            const int32_t extendedErrorCode
        ) = 0;
            /**
            rejectIncomingPairingResponse Method ID: 31
            **/
        virtual void rejectIncomingPairingResponse(
            const asi::connectivity::al::ResultType result,
            const int32_t extendedErrorCode
        ) = 0;
            /**
            abortPairingResponse Method ID: 3
            **/
        virtual void abortPairingResponse(
            const asi::connectivity::al::ResultType result,
            const int32_t extendedErrorCode
        ) = 0;
            /**
            updDeviceRecord Method ID: 61
            **/
        virtual void updDeviceRecord(
            const CIPtr< asi::connectivity::al::BtDeviceRecord >& record
        ) = 0;
            /**
            startServiceResponse Method ID: 50
            **/
        virtual void startServiceResponse(
            const asi::connectivity::al::ResultType result,
            const int32_t extendedErrorCode
        ) = 0;
            /**
            stopServiceResponse Method ID: 52
            **/
        virtual void stopServiceResponse(
            const asi::connectivity::al::ResultType result,
            const int32_t extendedErrorCode
        ) = 0;
            /**
            updServiceStatus Method ID: 72
            **/
        virtual void updServiceStatus(
            const int64_t address,
            const asi::connectivity::al::BluetoothService service,
            const int32_t serviceInstance,
            const asi::connectivity::al::BluetoothServiceStatus status
        ) = 0;
            /**
            getFriendlyNameResponse Method ID: 25
            **/
        virtual void getFriendlyNameResponse(
            const CIPtr< CIString >& friendlyName,
            const asi::connectivity::al::ResultType result,
            const int32_t extendedErrorCode
        ) = 0;
            /**
            setFriendlyNameResponse Method ID: 41
            **/
        virtual void setFriendlyNameResponse(
            const asi::connectivity::al::ResultType result,
            const int32_t extendedErrorCode
        ) = 0;
            /**
            getDiscoverableModeResponse Method ID: 23
            **/
        virtual void getDiscoverableModeResponse(
            const bool isDiscoverable,
            const asi::connectivity::al::ResultType result,
            const int32_t extendedErrorCode
        ) = 0;
            /**
            setDiscoverableModeResponse Method ID: 38
            **/
        virtual void setDiscoverableModeResponse(
            const asi::connectivity::al::ResultType result,
            const int32_t extendedErrorCode
        ) = 0;
            /**
            getConnectableModeResponse Method ID: 20
            **/
        virtual void getConnectableModeResponse(
            const bool isConnectable,
            const asi::connectivity::al::ResultType result,
            const int32_t extendedErrorCode
        ) = 0;
            /**
            setConnectableModeResponse Method ID: 36
            **/
        virtual void setConnectableModeResponse(
            const asi::connectivity::al::ResultType result,
            const int32_t extendedErrorCode
        ) = 0;
            /**
            getBluetoothEnabledResponse Method ID: 18
            **/
        virtual void getBluetoothEnabledResponse(
            const asi::connectivity::al::ResultType result,
            const int32_t extendedErrorCode
        ) = 0;
            /**
            setBluetoothEnabledResponse Method ID: 34
            **/
        virtual void setBluetoothEnabledResponse(
            const asi::connectivity::al::ResultType result,
            const int32_t extendedErrorCode
        ) = 0;
            /**
            updBluetoothEnabled Method ID: 56
            **/
        virtual void updBluetoothEnabled(
            const bool isEnabled
        ) = 0;
            /**
            deletePairingResponse Method ID: 14
            **/
        virtual void deletePairingResponse(
            const int64_t address,
            const asi::connectivity::al::ResultType result
        ) = 0;
            /**
            setServiceConnectableResponse Method ID: 44
            **/
        virtual void setServiceConnectableResponse(
            const asi::connectivity::al::ResultType result,
            const int32_t extendedErrorCode
        ) = 0;
            /**
            updIncomingServiceRequest Method ID: 67
            **/
        virtual void updIncomingServiceRequest(
            const int64_t address,
            const asi::connectivity::al::BluetoothService service,
            const int32_t serviceInstance,
            const bool isPending
        ) = 0;
            /**
            updMasterSlaveMode Method ID: 69
            **/
        virtual void updMasterSlaveMode(
            const int64_t address,
            const bool isMaster
        ) = 0;
            /**
            updBluetoothStreamingState Method ID: 57
            **/
        virtual void updBluetoothStreamingState(
            const int64_t address,
            const bool streamingActive
        ) = 0;
            /**
            updIncomingObexAuthRequest Method ID: 65
            **/
        virtual void updIncomingObexAuthRequest(
            const int64_t address,
            const bool isUserNeeded,
            const bool isReadOnly,
            const CIPtr< CIString >& realm
        ) = 0;
            /**
            acceptIncomingObexAuthRequestResponse Method ID: 5
            **/
        virtual void acceptIncomingObexAuthRequestResponse(
            const int64_t address,
            const asi::connectivity::al::ResultType result,
            const int32_t extendedErrorCode
        ) = 0;
            /**
            updBTError Method ID: 55
            **/
        virtual void updBTError(
            const int64_t address,
            const int32_t errorCode
        ) = 0;
            /**
            stringResponse Method ID: 54
            **/
        virtual void stringResponse(
            const CIPtr< CIString >& str
        ) = 0;
            /**
            updIapDevicePath Method ID: 64
            **/
        virtual void updIapDevicePath(
            const int64_t address,
            const CIPtr< CIString >& path
        ) = 0;
            /**
            updMobileDeviceInfoType Method ID: 70
            **/
        virtual void updMobileDeviceInfoType(
            const int64_t address,
            const asi::connectivity::al::MobileDeviceInfoType type,
            const CIPtr< CIString >& value
        ) = 0;
            /**
            updCurrentRSSI Method ID: 59
            **/
        virtual void updCurrentRSSI(
            const asi::connectivity::al::ResultType result,
            const int64_t address,
            const int32_t value,
            const int32_t extendedErrorCode
        ) = 0;
            /**
            *
         * Indicates an infoming pairing request from a bluetooth LE device.
         * @param device The device requesting the connection.
         * @sspInfo Pairing information.
         
            updLeIncomingPairingRequest Method ID: 68
            **/
        virtual void updLeIncomingPairingRequest(
            const CIPtr< asi::connectivity::al::BluetoothDevice >& device,
            const CIPtr< asi::connectivity::al::SimplePairingInformation >& sspInfo
        ) = 0;
            /**
            acceptLeIncomingPairingResponse Method ID: 10
            **/
        virtual void acceptLeIncomingPairingResponse(
            const asi::connectivity::al::ResultType result,
            const int32_t extendedErrorCode
        ) = 0;

        /*!
        \brief Informs the service about a connected client
        \param count The number of connected clients
        */
        virtual void clientConnected(uint32_t count) {}

        /*!
        \brief Informs the service that a client disconnected
        \param count the number of connected clients
        */
        virtual void clientDisconnected(uint32_t count) {}

        // call ids
        void
        bluetoothReadyCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<BluetoothServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 12;
            ce.assign(inst, mid);
        }

        void
        startInquiryResponseCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<BluetoothServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 48;
            ce.assign(inst, mid);
        }

        void
        abortInquiryResponseCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<BluetoothServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 1;
            ce.assign(inst, mid);
        }

        void
        updDiscoveredDevicesCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<BluetoothServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 62;
            ce.assign(inst, mid);
        }

        void
        updEndOfInquiryCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<BluetoothServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 63;
            ce.assign(inst, mid);
        }

        void
        disconnectDeviceResponseCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<BluetoothServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 16;
            ce.assign(inst, mid);
        }

        void
        pairUntrustedDeviceResponseCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<BluetoothServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 28;
            ce.assign(inst, mid);
        }

        void
        updPairingStatusCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<BluetoothServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 71;
            ce.assign(inst, mid);
        }

        void
        updBrutalDisconnectedCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<BluetoothServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 58;
            ce.assign(inst, mid);
        }

        void
        updDeviceInformationCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<BluetoothServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 60;
            ce.assign(inst, mid);
        }

        void
        updIncomingPairingRequestCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<BluetoothServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 66;
            ce.assign(inst, mid);
        }

        void
        acceptIncomingPairingResponseCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<BluetoothServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 7;
            ce.assign(inst, mid);
        }

        void
        rejectIncomingPairingResponseCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<BluetoothServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 31;
            ce.assign(inst, mid);
        }

        void
        abortPairingResponseCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<BluetoothServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 3;
            ce.assign(inst, mid);
        }

        void
        updDeviceRecordCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<BluetoothServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 61;
            ce.assign(inst, mid);
        }

        void
        startServiceResponseCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<BluetoothServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 50;
            ce.assign(inst, mid);
        }

        void
        stopServiceResponseCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<BluetoothServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 52;
            ce.assign(inst, mid);
        }

        void
        updServiceStatusCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<BluetoothServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 72;
            ce.assign(inst, mid);
        }

        void
        getFriendlyNameResponseCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<BluetoothServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 25;
            ce.assign(inst, mid);
        }

        void
        setFriendlyNameResponseCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<BluetoothServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 41;
            ce.assign(inst, mid);
        }

        void
        getDiscoverableModeResponseCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<BluetoothServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 23;
            ce.assign(inst, mid);
        }

        void
        setDiscoverableModeResponseCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<BluetoothServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 38;
            ce.assign(inst, mid);
        }

        void
        getConnectableModeResponseCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<BluetoothServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 20;
            ce.assign(inst, mid);
        }

        void
        setConnectableModeResponseCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<BluetoothServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 36;
            ce.assign(inst, mid);
        }

        void
        getBluetoothEnabledResponseCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<BluetoothServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 18;
            ce.assign(inst, mid);
        }

        void
        setBluetoothEnabledResponseCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<BluetoothServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 34;
            ce.assign(inst, mid);
        }

        void
        updBluetoothEnabledCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<BluetoothServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 56;
            ce.assign(inst, mid);
        }

        void
        deletePairingResponseCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<BluetoothServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 14;
            ce.assign(inst, mid);
        }

        void
        setServiceConnectableResponseCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<BluetoothServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 44;
            ce.assign(inst, mid);
        }

        void
        updIncomingServiceRequestCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<BluetoothServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 67;
            ce.assign(inst, mid);
        }

        void
        updMasterSlaveModeCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<BluetoothServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 69;
            ce.assign(inst, mid);
        }

        void
        updBluetoothStreamingStateCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<BluetoothServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 57;
            ce.assign(inst, mid);
        }

        void
        updIncomingObexAuthRequestCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<BluetoothServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 65;
            ce.assign(inst, mid);
        }

        void
        acceptIncomingObexAuthRequestResponseCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<BluetoothServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 5;
            ce.assign(inst, mid);
        }

        void
        updBTErrorCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<BluetoothServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 55;
            ce.assign(inst, mid);
        }

        void
        stringResponseCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<BluetoothServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 54;
            ce.assign(inst, mid);
        }

        void
        updIapDevicePathCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<BluetoothServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 64;
            ce.assign(inst, mid);
        }

        void
        updMobileDeviceInfoTypeCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<BluetoothServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 70;
            ce.assign(inst, mid);
        }

        void
        updCurrentRSSICallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<BluetoothServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 59;
            ce.assign(inst, mid);
        }

        void
        updLeIncomingPairingRequestCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<BluetoothServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 68;
            ce.assign(inst, mid);
        }

        void
        acceptLeIncomingPairingResponseCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<BluetoothServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 10;
            ce.assign(inst, mid);
        }


        virtual ~BluetoothServicesReply() {}
    };

}//namespace asi
}//namespace connectivity
}//namespace al

#endif// ASI_CONNECTIVITY_AL_BLUETOOTHSERVICESREPLY_HXX
