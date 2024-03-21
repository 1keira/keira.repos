/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_TRANSMISSIONPOWERMOBNETANTENNA_CSTYLE_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_TRANSMISSIONPOWERMOBNETANTENNA_CSTYLE_HXX

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
struct TransmissionPowerMobNetAntenna;
}
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const asi::connectivity::diagnostic::cstyle::TransmissionPowerMobNetAntenna& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::TransmissionPowerMobNetAntenna &val);
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
    \brief struct diagnostic::TransmissionPowerMobNetAntenna.
    */
    struct PROXY_EXPORT TransmissionPowerMobNetAntenna
    {
        public:
            TransmissionPowerMobNetAntenna()
            : m__2g()
            , m__3g()
            , m__4g()
            , m__5g()
            { }

            TransmissionPowerMobNetAntenna (const TransmissionPowerMobNetAntenna& other)
            : m__2g()
            , m__3g()
            , m__4g()
            , m__5g()
            {
              *this = other;
            }

            ~TransmissionPowerMobNetAntenna () {
            }
            bool operator==(const TransmissionPowerMobNetAntenna& rhs) const {
                bool equal = true;
                if (m__2g != rhs.m__2g)
                    equal = false;
                if (m__3g != rhs.m__3g)
                    equal = false;
                if (m__4g != rhs.m__4g)
                    equal = false;
                if (m__5g != rhs.m__5g)
                    equal = false;
                return equal;
            }
            bool operator!=(const TransmissionPowerMobNetAntenna& rhs) const {
                return !operator==(rhs);
            }

            TransmissionPowerMobNetAntenna& operator = (const TransmissionPowerMobNetAntenna& src) {
                if (this == &src) return *this;
                m__2g = src.m__2g;
                m__3g = src.m__3g;
                m__4g = src.m__4g;
                m__5g = src.m__5g;
                return *this;
            }

                void set_2g(const uint8_t _value) {
                    m__2g = _value;
                }
                uint8_t get_2g() const {
                    return m__2g;
                }
                void set_3g(const uint8_t _value) {
                    m__3g = _value;
                }
                uint8_t get_3g() const {
                    return m__3g;
                }
                void set_4g(const uint8_t _value) {
                    m__4g = _value;
                }
                uint8_t get_4g() const {
                    return m__4g;
                }
                void set_5g(const uint8_t _value) {
                    m__5g = _value;
                }
                uint8_t get_5g() const {
                    return m__5g;
                }


        uint8_t m__2g;
        uint8_t m__3g;
        uint8_t m__4g;
        uint8_t m__5g;
    private:
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const asi::connectivity::diagnostic::cstyle::TransmissionPowerMobNetAntenna& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::TransmissionPowerMobNetAntenna &val);
    };

} // cstyle
}//namespace asi
}//namespace connectivity
}//namespace diagnostic

#endif// ASI_CONNECTIVITY_DIAGNOSTIC_TRANSMISSIONPOWERMOBNETANTENNA_CSTYLE_HXX
