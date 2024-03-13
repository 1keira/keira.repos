/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef ASI_SID_V2XSTACK_LICHTVORNE01STRUCT_CSTYLE_HXX
#define ASI_SID_V2XSTACK_LICHTVORNE01STRUCT_CSTYLE_HXX

#include <comm/commidltypes.hxx>

// Forward declaration of the struct needed for the forward declaration of the deserializer
namespace asi
{
namespace sid
{
namespace v2xstack
{
namespace  cstyle
{
struct Lichtvorne01Struct;
}
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const asi::sid::v2xstack::cstyle::Lichtvorne01Struct& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, asi::sid::v2xstack::cstyle::Lichtvorne01Struct &val);
}
}

namespace asi
{
namespace sid
{
namespace v2xstack
{
namespace  cstyle
{

    /**
    \brief struct v2xstack::Lichtvorne01Struct.
    */
    struct PROXY_EXPORT Lichtvorne01Struct
    {
        public:
            Lichtvorne01Struct()
            : m_LV_AFL_aktiv_Anzeige_Raw()
            , m_PduState()
            { }

            Lichtvorne01Struct (const Lichtvorne01Struct& other)
            : m_LV_AFL_aktiv_Anzeige_Raw()
            , m_PduState()
            {
              *this = other;
            }

            ~Lichtvorne01Struct () {
            }
            bool operator==(const Lichtvorne01Struct& rhs) const {
                bool equal = true;
                if (m_LV_AFL_aktiv_Anzeige_Raw != rhs.m_LV_AFL_aktiv_Anzeige_Raw)
                    equal = false;
                if (m_PduState != rhs.m_PduState)
                    equal = false;
                return equal;
            }
            bool operator!=(const Lichtvorne01Struct& rhs) const {
                return !operator==(rhs);
            }

            Lichtvorne01Struct& operator = (const Lichtvorne01Struct& src) {
                if (this == &src) return *this;
                m_LV_AFL_aktiv_Anzeige_Raw = src.m_LV_AFL_aktiv_Anzeige_Raw;
                m_PduState = src.m_PduState;
                return *this;
            }

                void setLV_AFL_aktiv_Anzeige_Raw(const bool _value) {
                    m_LV_AFL_aktiv_Anzeige_Raw = _value;
                }
                bool getLV_AFL_aktiv_Anzeige_Raw() const {
                    return m_LV_AFL_aktiv_Anzeige_Raw;
                }
                void setPduState(const uint64_t _value) {
                    m_PduState = _value;
                }
                uint64_t getPduState() const {
                    return m_PduState;
                }


        bool m_LV_AFL_aktiv_Anzeige_Raw;
        uint64_t m_PduState;
    private:
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const asi::sid::v2xstack::cstyle::Lichtvorne01Struct& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, asi::sid::v2xstack::cstyle::Lichtvorne01Struct &val);
    };

} // cstyle
}//namespace asi
}//namespace sid
}//namespace v2xstack

#endif// ASI_SID_V2XSTACK_LICHTVORNE01STRUCT_CSTYLE_HXX
