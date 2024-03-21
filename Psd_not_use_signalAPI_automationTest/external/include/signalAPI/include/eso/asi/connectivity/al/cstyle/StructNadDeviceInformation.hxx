/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_NADDEVICEINFORMATION_CSTYLE_HXX
#define ASI_CONNECTIVITY_AL_NADDEVICEINFORMATION_CSTYLE_HXX

#include <comm/commidltypes.hxx>

// Forward declaration of the struct needed for the forward declaration of the deserializer
namespace asi
{
namespace connectivity
{
namespace al
{
namespace  cstyle
{
struct NadDeviceInformation;
}
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const asi::connectivity::al::cstyle::NadDeviceInformation& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::al::cstyle::NadDeviceInformation &val);
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
    \brief struct al::NadDeviceInformation.
    */
    struct PROXY_EXPORT NadDeviceInformation
    {
        public:
            NadDeviceInformation()
            : m_manufacturer(nullptr)
            , m_model(nullptr)
            , m_fwVersion(nullptr)
            , m_hwVersion(nullptr)
            , m_imei(nullptr)
            { }

            NadDeviceInformation (const NadDeviceInformation& other)
            : m_manufacturer(nullptr)
            , m_model(nullptr)
            , m_fwVersion(nullptr)
            , m_hwVersion(nullptr)
            , m_imei(nullptr)
            {
              *this = other;
            }

            ~NadDeviceInformation () {
                if (m_manufacturer) {
                    delete m_manufacturer;
                }
                if (m_model) {
                    delete m_model;
                }
                if (m_fwVersion) {
                    delete m_fwVersion;
                }
                if (m_hwVersion) {
                    delete m_hwVersion;
                }
                if (m_imei) {
                    delete m_imei;
                }
            }
            bool operator==(const NadDeviceInformation& rhs) const {
                bool equal = true;
                if (m_manufacturer == nullptr && rhs.m_manufacturer != nullptr)
                    equal = false;
                else if (m_manufacturer != nullptr && rhs.m_manufacturer == nullptr)
                    equal = false;
                else if ((m_manufacturer != nullptr) && (rhs.m_manufacturer != nullptr) && (*m_manufacturer != *rhs.m_manufacturer))
                    equal = false;
                if (m_model == nullptr && rhs.m_model != nullptr)
                    equal = false;
                else if (m_model != nullptr && rhs.m_model == nullptr)
                    equal = false;
                else if ((m_model != nullptr) && (rhs.m_model != nullptr) && (*m_model != *rhs.m_model))
                    equal = false;
                if (m_fwVersion == nullptr && rhs.m_fwVersion != nullptr)
                    equal = false;
                else if (m_fwVersion != nullptr && rhs.m_fwVersion == nullptr)
                    equal = false;
                else if ((m_fwVersion != nullptr) && (rhs.m_fwVersion != nullptr) && (*m_fwVersion != *rhs.m_fwVersion))
                    equal = false;
                if (m_hwVersion == nullptr && rhs.m_hwVersion != nullptr)
                    equal = false;
                else if (m_hwVersion != nullptr && rhs.m_hwVersion == nullptr)
                    equal = false;
                else if ((m_hwVersion != nullptr) && (rhs.m_hwVersion != nullptr) && (*m_hwVersion != *rhs.m_hwVersion))
                    equal = false;
                if (m_imei == nullptr && rhs.m_imei != nullptr)
                    equal = false;
                else if (m_imei != nullptr && rhs.m_imei == nullptr)
                    equal = false;
                else if ((m_imei != nullptr) && (rhs.m_imei != nullptr) && (*m_imei != *rhs.m_imei))
                    equal = false;
                return equal;
            }
            bool operator!=(const NadDeviceInformation& rhs) const {
                return !operator==(rhs);
            }

            NadDeviceInformation& operator = (const NadDeviceInformation& src) {
                if (this == &src) return *this;
                if (m_manufacturer)
                    delete m_manufacturer;
                if (src.m_manufacturer) {
                    m_manufacturer = new (ipl::nothrow)ipl::string(*(src.m_manufacturer));
                } else {
                    m_manufacturer = nullptr;
                }
                if (m_model)
                    delete m_model;
                if (src.m_model) {
                    m_model = new (ipl::nothrow)ipl::string(*(src.m_model));
                } else {
                    m_model = nullptr;
                }
                if (m_fwVersion)
                    delete m_fwVersion;
                if (src.m_fwVersion) {
                    m_fwVersion = new (ipl::nothrow)ipl::string(*(src.m_fwVersion));
                } else {
                    m_fwVersion = nullptr;
                }
                if (m_hwVersion)
                    delete m_hwVersion;
                if (src.m_hwVersion) {
                    m_hwVersion = new (ipl::nothrow)ipl::string(*(src.m_hwVersion));
                } else {
                    m_hwVersion = nullptr;
                }
                if (m_imei)
                    delete m_imei;
                if (src.m_imei) {
                    m_imei = new (ipl::nothrow)ipl::string(*(src.m_imei));
                } else {
                    m_imei = nullptr;
                }
                return *this;
            }

                void setmanufacturer(const ipl::string* _value) {
                    if (m_manufacturer)
                        delete m_manufacturer;
                    if (_value) {
                        m_manufacturer = new (ipl::nothrow)ipl::string(*_value);
                    } else {
                        m_manufacturer = nullptr;
                    }
                }
                const ipl::string* getmanufacturer() const {
                    return m_manufacturer;
                }
                    bool manufacturerValid() const {
                        return m_manufacturer != nullptr;
                    }
                void setmodel(const ipl::string* _value) {
                    if (m_model)
                        delete m_model;
                    if (_value) {
                        m_model = new (ipl::nothrow)ipl::string(*_value);
                    } else {
                        m_model = nullptr;
                    }
                }
                const ipl::string* getmodel() const {
                    return m_model;
                }
                    bool modelValid() const {
                        return m_model != nullptr;
                    }
                void setfwVersion(const ipl::string* _value) {
                    if (m_fwVersion)
                        delete m_fwVersion;
                    if (_value) {
                        m_fwVersion = new (ipl::nothrow)ipl::string(*_value);
                    } else {
                        m_fwVersion = nullptr;
                    }
                }
                const ipl::string* getfwVersion() const {
                    return m_fwVersion;
                }
                    bool fwVersionValid() const {
                        return m_fwVersion != nullptr;
                    }
                void sethwVersion(const ipl::string* _value) {
                    if (m_hwVersion)
                        delete m_hwVersion;
                    if (_value) {
                        m_hwVersion = new (ipl::nothrow)ipl::string(*_value);
                    } else {
                        m_hwVersion = nullptr;
                    }
                }
                const ipl::string* gethwVersion() const {
                    return m_hwVersion;
                }
                    bool hwVersionValid() const {
                        return m_hwVersion != nullptr;
                    }
                void setimei(const ipl::string* _value) {
                    if (m_imei)
                        delete m_imei;
                    if (_value) {
                        m_imei = new (ipl::nothrow)ipl::string(*_value);
                    } else {
                        m_imei = nullptr;
                    }
                }
                const ipl::string* getimei() const {
                    return m_imei;
                }
                    bool imeiValid() const {
                        return m_imei != nullptr;
                    }


    private:
        ipl::string* m_manufacturer;
        ipl::string* m_model;
        ipl::string* m_fwVersion;
        ipl::string* m_hwVersion;
        ipl::string* m_imei;
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const asi::connectivity::al::cstyle::NadDeviceInformation& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::al::cstyle::NadDeviceInformation &val);
    };

} // cstyle
}//namespace asi
}//namespace connectivity
}//namespace al

#endif// ASI_CONNECTIVITY_AL_NADDEVICEINFORMATION_CSTYLE_HXX
