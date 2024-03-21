/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_ANTENNAINFO_CSTYLE_HXX
#define ASI_CONNECTIVITY_AL_ANTENNAINFO_CSTYLE_HXX

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
struct AntennaInfo;
}
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const asi::connectivity::al::cstyle::AntennaInfo& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::al::cstyle::AntennaInfo &val);
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
    \brief struct al::AntennaInfo.
    */
    struct PROXY_EXPORT AntennaInfo
    {
        public:
            AntennaInfo()
            : m_state()
            , m_channel()
            { }

            AntennaInfo (const AntennaInfo& other)
            : m_state()
            , m_channel()
            {
              *this = other;
            }

            ~AntennaInfo () {
            }
            bool operator==(const AntennaInfo& rhs) const {
                bool equal = true;
                if (m_state != rhs.m_state)
                    equal = false;
                if (m_channel != rhs.m_channel)
                    equal = false;
                return equal;
            }
            bool operator!=(const AntennaInfo& rhs) const {
                return !operator==(rhs);
            }

            AntennaInfo& operator = (const AntennaInfo& src) {
                if (this == &src) return *this;
                m_state = src.m_state;
                m_channel = src.m_channel;
                return *this;
            }

                void setstate(const asi::connectivity::al::cstyle::AntennaState _value) {
                    m_state = _value;
                }
                asi::connectivity::al::cstyle::AntennaState getstate() const {
                    return m_state;
                }
                void setchannel(const int32_t _value) {
                    m_channel = _value;
                }
                int32_t getchannel() const {
                    return m_channel;
                }


        asi::connectivity::al::cstyle::AntennaState m_state;
        int32_t m_channel;
    private:
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const asi::connectivity::al::cstyle::AntennaInfo& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::al::cstyle::AntennaInfo &val);
    };

} // cstyle
}//namespace asi
}//namespace connectivity
}//namespace al

#endif// ASI_CONNECTIVITY_AL_ANTENNAINFO_CSTYLE_HXX
