/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_BLUETOOTHDEVICE_HXX
#define ASI_CONNECTIVITY_AL_BLUETOOTHDEVICE_HXX

#include <comm/commidltypes.hxx>
#include <comm/attributes/commattributes.hxx>
#include <asi/connectivity/al/Definitions.hxx>
#include <asi/connectivity/al/Definitions.hxx>

#undef unix

namespace asi
{
namespace connectivity
{
namespace al
{

    /**
    \brief struct al::BluetoothDevice.
    */
    struct PROXY_EXPORT BluetoothDevice
    {
        CIPtr< CIString > name; // optional=True
        int64_t address; // optional=False
        int32_t deviceClass; // optional=False
        int32_t serviceTypes; // optional=False
        asi::connectivity::al::SupportedPairingMethod pairingMethod; // optional=False
        asi::connectivity::al::LinkkeyType linkkeyType; // optional=False
        int8_t rssi; // optional=False
        private:
            BluetoothDevice()
            :
            name(),
            address(),
            deviceClass(),
            serviceTypes(),
            pairingMethod(),
            linkkeyType(),
            rssi()
            { }
            friend class BluetoothDeviceFactory;
            friend class CIFactory<BluetoothDevice>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<asi::connectivity::al::BluetoothDevice> >;
            friend class ipl::vector<BluetoothDevice>;
            friend class ipl::allocator<BluetoothDevice>;
#endif
    };

    typedef CIPtrArray<BluetoothDevice> CIBluetoothDeviceArray;

    /** \brief factory for al::BluetoothDevice. */
    class PROXY_EXPORT BluetoothDeviceFactory  : CIFactory<BluetoothDevice> {
    public:
        static inline CIPtr<BluetoothDevice> createBluetoothDevice() {
            return CIFactory<BluetoothDevice>::createObject();
        }
        static inline void createBluetoothDevice(CIPtr<BluetoothDevice> & s) {
            CIFactory<BluetoothDevice>::createObject(s);
        }
        static inline CIPtr<CIBluetoothDeviceArray> createBluetoothDeviceArray(size_t size) {
            return CIFactory<BluetoothDevice>::createArray(size);
        }
        static inline void createBluetoothDeviceArray(CIPtr<CIBluetoothDeviceArray>& a, size_t size) {
            CIFactory<BluetoothDevice>::createArray(a, size);
        }
    };
}//namespace asi
}//namespace connectivity
}//namespace al


#endif// ASI_CONNECTIVITY_AL_BLUETOOTHDEVICE_HXX
