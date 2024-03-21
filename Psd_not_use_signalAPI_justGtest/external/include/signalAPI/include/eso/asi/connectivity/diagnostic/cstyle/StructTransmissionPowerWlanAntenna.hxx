/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_TRANSMISSIONPOWERWLANANTENNA_CSTYLE_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_TRANSMISSIONPOWERWLANANTENNA_CSTYLE_HXX

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
struct TransmissionPowerWlanAntenna;
}
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const asi::connectivity::diagnostic::cstyle::TransmissionPowerWlanAntenna& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::TransmissionPowerWlanAntenna &val);
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
    \brief struct diagnostic::TransmissionPowerWlanAntenna.
    */
    struct PROXY_EXPORT TransmissionPowerWlanAntenna
    {
        public:
            TransmissionPowerWlanAntenna()
            : m__2_4Ghz()
            , m__5Ghz()
            { }

            TransmissionPowerWlanAntenna (const TransmissionPowerWlanAntenna& other)
            : m__2_4Ghz()
            , m__5Ghz()
            {
              *this = other;
            }

            ~TransmissionPowerWlanAntenna () {
            }
            bool operator==(const TransmissionPowerWlanAntenna& rhs) const {
                bool equal = true;
                if (m__2_4Ghz != rhs.m__2_4Ghz)
                    equal = false;
                if (m__5Ghz != rhs.m__5Ghz)
                    equal = false;
                return equal;
            }
            bool operator!=(const TransmissionPowerWlanAntenna& rhs) const {
                return !operator==(rhs);
            }

            TransmissionPowerWlanAntenna& operator = (const TransmissionPowerWlanAntenna& src) {
                if (this == &src) return *this;
                m__2_4Ghz = src.m__2_4Ghz;
                m__5Ghz = src.m__5Ghz;
                return *this;
            }

                void set_2_4Ghz(const uint8_t _value) {
                    m__2_4Ghz = _value;
                }
                uint8_t get_2_4Ghz() const {
                    return m__2_4Ghz;
                }
                void set_5Ghz(const uint8_t _value) {
                    m__5Ghz = _value;
                }
                uint8_t get_5Ghz() const {
                    return m__5Ghz;
                }


        uint8_t m__2_4Ghz;
        uint8_t m__5Ghz;
    private:
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const asi::connectivity::diagnostic::cstyle::TransmissionPowerWlanAntenna& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::TransmissionPowerWlanAntenna &val);
    };

} // cstyle
}//namespace asi
}//namespace connectivity
}//namespace diagnostic

#endif// ASI_CONNECTIVITY_DIAGNOSTIC_TRANSMISSIONPOWERWLANANTENNA_CSTYLE_HXX
