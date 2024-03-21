/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_TEMPERATUREINFO_CSTYLE_HXX
#define ASI_CONNECTIVITY_AL_TEMPERATUREINFO_CSTYLE_HXX

#include <comm/commidltypes.hxx>
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
struct TemperatureInfo;
}
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const asi::connectivity::al::cstyle::TemperatureInfo& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::al::cstyle::TemperatureInfo &val);
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
         Temperatures in 1/100 °C (e.g. 3753 means 37,53°C) 
    */
    struct PROXY_EXPORT TemperatureInfo
    {
        public:
            TemperatureInfo()
            : m_level()
            , m_temperature1()
            , m_temperature2()
            { }

            TemperatureInfo (const TemperatureInfo& other)
            : m_level()
            , m_temperature1()
            , m_temperature2()
            {
              *this = other;
            }

            ~TemperatureInfo () {
            }
            bool operator==(const TemperatureInfo& rhs) const {
                bool equal = true;
                if (m_level != rhs.m_level)
                    equal = false;
                if (m_temperature1 != rhs.m_temperature1)
                    equal = false;
                if (m_temperature2 != rhs.m_temperature2)
                    equal = false;
                return equal;
            }
            bool operator!=(const TemperatureInfo& rhs) const {
                return !operator==(rhs);
            }

            TemperatureInfo& operator = (const TemperatureInfo& src) {
                if (this == &src) return *this;
                m_level = src.m_level;
                m_temperature1 = src.m_temperature1;
                m_temperature2 = src.m_temperature2;
                return *this;
            }

                void setlevel(const asi::connectivity::al::cstyle::NadTempThresholdLevel _value) {
                    m_level = _value;
                }
                asi::connectivity::al::cstyle::NadTempThresholdLevel getlevel() const {
                    return m_level;
                }
                void settemperature1(const int32_t _value) {
                    m_temperature1 = _value;
                }
                int32_t gettemperature1() const {
                    return m_temperature1;
                }
                void settemperature2(const int32_t _value) {
                    m_temperature2 = _value;
                }
                int32_t gettemperature2() const {
                    return m_temperature2;
                }


        asi::connectivity::al::cstyle::NadTempThresholdLevel m_level;
        int32_t m_temperature1;
        int32_t m_temperature2;
    private:
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const asi::connectivity::al::cstyle::TemperatureInfo& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::al::cstyle::TemperatureInfo &val);
    };

} // cstyle
}//namespace asi
}//namespace connectivity
}//namespace al

#endif// ASI_CONNECTIVITY_AL_TEMPERATUREINFO_CSTYLE_HXX
