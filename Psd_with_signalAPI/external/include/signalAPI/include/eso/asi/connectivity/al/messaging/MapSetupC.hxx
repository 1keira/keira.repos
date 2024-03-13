/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceC_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_MESSAGING_MAPSETUPC_HXX
#define ASI_CONNECTIVITY_AL_MESSAGING_MAPSETUPC_HXX

#include <ipl_config.h>
#include <comm/commidltypes.hxx>
#include <asi/connectivity/al/messaging/Definitions.hxx>

namespace asi
{
namespace connectivity
{
namespace al
{
namespace messaging
{

    /**
    \brief The messaging::MapSetup interface on the client side.
    \details
            A proxy implements this interface.
        *
    * Interface to setup map, because the Bluetooth application does the service startup/teardown.
    **/
    class MapSetupC
    {
    public:
        // List of request methods
        /**
            *
       * @brief Informs Messaging of connected/disconnected devices for MAP.
       *
       * @param friendlyName Friendly name of connected device (if connected)
       * @param address MAC address of the device.
       * @param isMapConnected Is MAP connected for the device?
       * @param isSapConnected Is the device connected via SAP?
       * @param isHfpConnected Is the device connected via HFP?
       * @param slotNumber Slot number that device is currently assigned to
       
            updateDeviceStatus Method ID: 0
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool updateDeviceStatus(
            const CIPtr< CIString >& friendlyName,
            const int64_t address,
            const bool isMapConnected,
            const bool isSapConnected,
            const bool isHfpConnected,
            const bool isPbapConnected,
            const bool isPimDevice
        ) const IPL_NOEXCEPT = 0;

        MapSetupC()  {}
        virtual ~MapSetupC() {}
    protected:
        friend class MapSetupProxy;
    };

}//namespace asi
}//namespace connectivity
}//namespace al
}//namespace messaging
#endif// ASI_CONNECTIVITY_AL_MESSAGING_MAPSETUPC_HXX
