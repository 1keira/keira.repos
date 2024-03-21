/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_SERVICEVERSIONS_CSTYLE_HXX
#define ASI_CONNECTIVITY_AL_SERVICEVERSIONS_CSTYLE_HXX

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
struct ServiceVersions;
}
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const asi::connectivity::al::cstyle::ServiceVersions& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::al::cstyle::ServiceVersions &val);
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
    \brief struct al::ServiceVersions.
    */
    struct PROXY_EXPORT ServiceVersions
    {
        public:
            ServiceVersions()
            : m_hf_ag()
            , m_hf()
            , m_sap()
            , m_pbap()
            , m_map_mse()
            , m_opp()
            , m_a2dp_sink()
            , m_a2dp_source()
            , m_avrcp()
            { }

            ServiceVersions (const ServiceVersions& other)
            : m_hf_ag()
            , m_hf()
            , m_sap()
            , m_pbap()
            , m_map_mse()
            , m_opp()
            , m_a2dp_sink()
            , m_a2dp_source()
            , m_avrcp()
            {
              *this = other;
            }

            ~ServiceVersions () {
            }
            bool operator==(const ServiceVersions& rhs) const {
                bool equal = true;
                if (m_hf_ag != rhs.m_hf_ag)
                    equal = false;
                if (m_hf != rhs.m_hf)
                    equal = false;
                if (m_sap != rhs.m_sap)
                    equal = false;
                if (m_pbap != rhs.m_pbap)
                    equal = false;
                if (m_map_mse != rhs.m_map_mse)
                    equal = false;
                if (m_opp != rhs.m_opp)
                    equal = false;
                if (m_a2dp_sink != rhs.m_a2dp_sink)
                    equal = false;
                if (m_a2dp_source != rhs.m_a2dp_source)
                    equal = false;
                if (m_avrcp != rhs.m_avrcp)
                    equal = false;
                return equal;
            }
            bool operator!=(const ServiceVersions& rhs) const {
                return !operator==(rhs);
            }

            ServiceVersions& operator = (const ServiceVersions& src) {
                if (this == &src) return *this;
                m_hf_ag = src.m_hf_ag;
                m_hf = src.m_hf;
                m_sap = src.m_sap;
                m_pbap = src.m_pbap;
                m_map_mse = src.m_map_mse;
                m_opp = src.m_opp;
                m_a2dp_sink = src.m_a2dp_sink;
                m_a2dp_source = src.m_a2dp_source;
                m_avrcp = src.m_avrcp;
                return *this;
            }

                void sethf_ag(const uint16_t _value) {
                    m_hf_ag = _value;
                }
                uint16_t gethf_ag() const {
                    return m_hf_ag;
                }
                void sethf(const uint16_t _value) {
                    m_hf = _value;
                }
                uint16_t gethf() const {
                    return m_hf;
                }
                void setsap(const uint16_t _value) {
                    m_sap = _value;
                }
                uint16_t getsap() const {
                    return m_sap;
                }
                void setpbap(const uint16_t _value) {
                    m_pbap = _value;
                }
                uint16_t getpbap() const {
                    return m_pbap;
                }
                void setmap_mse(const uint16_t _value) {
                    m_map_mse = _value;
                }
                uint16_t getmap_mse() const {
                    return m_map_mse;
                }
                void setopp(const uint16_t _value) {
                    m_opp = _value;
                }
                uint16_t getopp() const {
                    return m_opp;
                }
                void seta2dp_sink(const uint16_t _value) {
                    m_a2dp_sink = _value;
                }
                uint16_t geta2dp_sink() const {
                    return m_a2dp_sink;
                }
                void seta2dp_source(const uint16_t _value) {
                    m_a2dp_source = _value;
                }
                uint16_t geta2dp_source() const {
                    return m_a2dp_source;
                }
                void setavrcp(const uint16_t _value) {
                    m_avrcp = _value;
                }
                uint16_t getavrcp() const {
                    return m_avrcp;
                }


        uint16_t m_hf_ag;
        uint16_t m_hf;
        uint16_t m_sap;
        uint16_t m_pbap;
        uint16_t m_map_mse;
        uint16_t m_opp;
        uint16_t m_a2dp_sink;
        uint16_t m_a2dp_source;
        uint16_t m_avrcp;
    private:
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const asi::connectivity::al::cstyle::ServiceVersions& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::al::cstyle::ServiceVersions &val);
    };

} // cstyle
}//namespace asi
}//namespace connectivity
}//namespace al

#endif// ASI_CONNECTIVITY_AL_SERVICEVERSIONS_CSTYLE_HXX
