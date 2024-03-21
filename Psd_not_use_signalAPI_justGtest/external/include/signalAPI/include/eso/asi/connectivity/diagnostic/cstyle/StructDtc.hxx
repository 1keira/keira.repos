/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_DTC_CSTYLE_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_DTC_CSTYLE_HXX

#include <comm/commidltypes.hxx>
#include <asi/connectivity/diagnostic/cstyle/Definitions.hxx>

// Forward declaration of the struct needed for the forward declaration of the deserializer
namespace asi
{
namespace connectivity
{
namespace diagnostic
{
namespace  cstyle
{
struct Dtc;
}
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const asi::connectivity::diagnostic::cstyle::Dtc& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::Dtc &val);
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
    \brief struct diagnostic::Dtc.
    */
    struct PROXY_EXPORT Dtc
    {
        public:
            Dtc()
            : m_code()
            , m_errorCondition()
            { }

            Dtc (const Dtc& other)
            : m_code()
            , m_errorCondition()
            {
              *this = other;
            }

            ~Dtc () {
            }
            bool operator==(const Dtc& rhs) const {
                bool equal = true;
                if (m_code != rhs.m_code)
                    equal = false;
                if (m_errorCondition != rhs.m_errorCondition)
                    equal = false;
                return equal;
            }
            bool operator!=(const Dtc& rhs) const {
                return !operator==(rhs);
            }

            Dtc& operator = (const Dtc& src) {
                if (this == &src) return *this;
                m_code = src.m_code;
                m_errorCondition = src.m_errorCondition;
                return *this;
            }

                void setcode(const uint32_t _value) {
                    m_code = _value;
                }
                uint32_t getcode() const {
                    return m_code;
                }
                void seterrorCondition(const asi::connectivity::diagnostic::cstyle::DtcErrorCondition _value) {
                    m_errorCondition = _value;
                }
                asi::connectivity::diagnostic::cstyle::DtcErrorCondition geterrorCondition() const {
                    return m_errorCondition;
                }


        uint32_t m_code;
        asi::connectivity::diagnostic::cstyle::DtcErrorCondition m_errorCondition;
    private:
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const asi::connectivity::diagnostic::cstyle::Dtc& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::Dtc &val);
    };

} // cstyle
}//namespace asi
}//namespace connectivity
}//namespace diagnostic

#endif// ASI_CONNECTIVITY_DIAGNOSTIC_DTC_CSTYLE_HXX
