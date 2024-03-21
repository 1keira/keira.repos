/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_EMERGENCYINFORMATIONSERVICESETTINGS_CSTYLE_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_EMERGENCYINFORMATIONSERVICESETTINGS_CSTYLE_HXX

#include <comm/commidltypes.hxx>

// Forward declaration of the struct needed for the forward declaration of the deserializer
namespace asi
{
namespace connectivity
{
namespace diagnostic
{
namespace  cstyle
{
struct EmergencyInformationServiceSettings;
}
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const asi::connectivity::diagnostic::cstyle::EmergencyInformationServiceSettings& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::EmergencyInformationServiceSettings &val);
}
}

namespace asi
{
namespace connectivity
{
namespace diagnostic
{
namespace  cstyle
{

    /**
    \brief struct diagnostic::EmergencyInformationServiceSettings.
    */
    struct PROXY_EXPORT EmergencyInformationServiceSettings
    {
        public:
            EmergencyInformationServiceSettings()
            : m_offlineTimeInterval()
            , m_onlineDuration()
            { }

            EmergencyInformationServiceSettings (const EmergencyInformationServiceSettings& other)
            : m_offlineTimeInterval()
            , m_onlineDuration()
            {
              *this = other;
            }

            ~EmergencyInformationServiceSettings () {
            }
            bool operator==(const EmergencyInformationServiceSettings& rhs) const {
                bool equal = true;
                if (m_offlineTimeInterval != rhs.m_offlineTimeInterval)
                    equal = false;
                if (m_onlineDuration != rhs.m_onlineDuration)
                    equal = false;
                return equal;
            }
            bool operator!=(const EmergencyInformationServiceSettings& rhs) const {
                return !operator==(rhs);
            }

            EmergencyInformationServiceSettings& operator = (const EmergencyInformationServiceSettings& src) {
                if (this == &src) return *this;
                m_offlineTimeInterval = src.m_offlineTimeInterval;
                m_onlineDuration = src.m_onlineDuration;
                return *this;
            }

                void setofflineTimeInterval(const uint32_t _value) {
                    m_offlineTimeInterval = _value;
                }
                uint32_t getofflineTimeInterval() const {
                    return m_offlineTimeInterval;
                }
                void setonlineDuration(const uint16_t _value) {
                    m_onlineDuration = _value;
                }
                uint16_t getonlineDuration() const {
                    return m_onlineDuration;
                }


        uint32_t m_offlineTimeInterval;
        uint16_t m_onlineDuration;
    private:
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const asi::connectivity::diagnostic::cstyle::EmergencyInformationServiceSettings& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::EmergencyInformationServiceSettings &val);
    };

} // cstyle
}//namespace asi
}//namespace connectivity
}//namespace diagnostic

#endif// ASI_CONNECTIVITY_DIAGNOSTIC_EMERGENCYINFORMATIONSERVICESETTINGS_CSTYLE_HXX
