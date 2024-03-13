/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_BLUETOOTHDEVICE_CSTYLE_HXX
#define ASI_CONNECTIVITY_AL_BLUETOOTHDEVICE_CSTYLE_HXX

#include <comm/commidltypes.hxx>
#include <asi/connectivity/al/cstyle/Definitions.hxx>
#include <asi/connectivity/al/cstyle/Definitions.hxx>

// Forward declaration of the struct needed for the forward declaration of the deserializer
namespace asi
{
namespace connectivity
{
namespace al
{
namespace  cstyle
{
struct BluetoothDevice;
}
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const asi::connectivity::al::cstyle::BluetoothDevice& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::al::cstyle::BluetoothDevice &val);
}
}

namespace asi
{
namespace connectivity
{
namespace al
{
namespace  cstyle
{

    /**
    \brief struct al::BluetoothDevice.
    */
    struct PROXY_EXPORT BluetoothDevice
    {
        public:
            BluetoothDevice()
            : m_address()
            , m_deviceClass()
            , m_serviceTypes()
            , m_pairingMethod()
            , m_linkkeyType()
            , m_rssi()
            , m_name(nullptr)
            { }

            BluetoothDevice (const BluetoothDevice& other)
            : m_address()
            , m_deviceClass()
            , m_serviceTypes()
            , m_pairingMethod()
            , m_linkkeyType()
            , m_rssi()
            , m_name(nullptr)
            {
              *this = other;
            }

            ~BluetoothDevice () {
                if (m_name) {
                    delete m_name;
                }
            }
            bool operator==(const BluetoothDevice& rhs) const {
                bool equal = true;
                if (m_name == nullptr && rhs.m_name != nullptr)
                    equal = false;
                else if (m_name != nullptr && rhs.m_name == nullptr)
                    equal = false;
                else if ((m_name != nullptr) && (rhs.m_name != nullptr) && (*m_name != *rhs.m_name))
                    equal = false;
                if (m_address != rhs.m_address)
                    equal = false;
                if (m_deviceClass != rhs.m_deviceClass)
                    equal = false;
                if (m_serviceTypes != rhs.m_serviceTypes)
                    equal = false;
                if (m_pairingMethod != rhs.m_pairingMethod)
                    equal = false;
                if (m_linkkeyType != rhs.m_linkkeyType)
                    equal = false;
                if (m_rssi != rhs.m_rssi)
                    equal = false;
                return equal;
            }
            bool operator!=(const BluetoothDevice& rhs) const {
                return !operator==(rhs);
            }

            BluetoothDevice& operator = (const BluetoothDevice& src) {
                if (this == &src) return *this;
                if (m_name)
                    delete m_name;
                if (src.m_name) {
                    m_name = new (ipl::nothrow)ipl::string(*(src.m_name));
                } else {
                    m_name = nullptr;
                }
                m_address = src.m_address;
                m_deviceClass = src.m_deviceClass;
                m_serviceTypes = src.m_serviceTypes;
                m_pairingMethod = src.m_pairingMethod;
                m_linkkeyType = src.m_linkkeyType;
                m_rssi = src.m_rssi;
                return *this;
            }

                void setname(const ipl::string* _value) {
                    if (m_name)
                        delete m_name;
                    if (_value) {
                        m_name = new (ipl::nothrow)ipl::string(*_value);
                    } else {
                        m_name = nullptr;
                    }
                }
                const ipl::string* getname() const {
                    return m_name;
                }
                    bool nameValid() const {
                        return m_name != nullptr;
                    }
                void setaddress(const int64_t _value) {
                    m_address = _value;
                }
                int64_t getaddress() const {
                    return m_address;
                }
                void setdeviceClass(const int32_t _value) {
                    m_deviceClass = _value;
                }
                int32_t getdeviceClass() const {
                    return m_deviceClass;
                }
                void setserviceTypes(const int32_t _value) {
                    m_serviceTypes = _value;
                }
                int32_t getserviceTypes() const {
                    return m_serviceTypes;
                }
                void setpairingMethod(const asi::connectivity::al::cstyle::SupportedPairingMethod _value) {
                    m_pairingMethod = _value;
                }
                asi::connectivity::al::cstyle::SupportedPairingMethod getpairingMethod() const {
                    return m_pairingMethod;
                }
                void setlinkkeyType(const asi::connectivity::al::cstyle::LinkkeyType _value) {
                    m_linkkeyType = _value;
                }
                asi::connectivity::al::cstyle::LinkkeyType getlinkkeyType() const {
                    return m_linkkeyType;
                }
                void setrssi(const int8_t _value) {
                    m_rssi = _value;
                }
                int8_t getrssi() const {
                    return m_rssi;
                }


        int64_t m_address;
        int32_t m_deviceClass;
        int32_t m_serviceTypes;
        asi::connectivity::al::cstyle::SupportedPairingMethod m_pairingMethod;
        asi::connectivity::al::cstyle::LinkkeyType m_linkkeyType;
        int8_t m_rssi;
    private:
        ipl::string* m_name;
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const asi::connectivity::al::cstyle::BluetoothDevice& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::al::cstyle::BluetoothDevice &val);
    };

} // cstyle
}//namespace asi
}//namespace connectivity
}//namespace al

#endif// ASI_CONNECTIVITY_AL_BLUETOOTHDEVICE_CSTYLE_HXX
