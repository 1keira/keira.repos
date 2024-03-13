/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef ASI_SID_V2XSTACK_KLEMMENSTATUS01STRUCT_CSTYLE_HXX
#define ASI_SID_V2XSTACK_KLEMMENSTATUS01STRUCT_CSTYLE_HXX

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
struct KlemmenStatus01Struct;
}
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const asi::sid::v2xstack::cstyle::KlemmenStatus01Struct& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, asi::sid::v2xstack::cstyle::KlemmenStatus01Struct &val);
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
    \brief struct v2xstack::KlemmenStatus01Struct.
    */
    struct PROXY_EXPORT KlemmenStatus01Struct
    {
        public:
            KlemmenStatus01Struct()
            : m_ZAS_Kl_15_Raw()
            , m_PduState()
            { }

            KlemmenStatus01Struct (const KlemmenStatus01Struct& other)
            : m_ZAS_Kl_15_Raw()
            , m_PduState()
            {
              *this = other;
            }

            ~KlemmenStatus01Struct () {
            }
            bool operator==(const KlemmenStatus01Struct& rhs) const {
                bool equal = true;
                if (m_ZAS_Kl_15_Raw != rhs.m_ZAS_Kl_15_Raw)
                    equal = false;
                if (m_PduState != rhs.m_PduState)
                    equal = false;
                return equal;
            }
            bool operator!=(const KlemmenStatus01Struct& rhs) const {
                return !operator==(rhs);
            }

            KlemmenStatus01Struct& operator = (const KlemmenStatus01Struct& src) {
                if (this == &src) return *this;
                m_ZAS_Kl_15_Raw = src.m_ZAS_Kl_15_Raw;
                m_PduState = src.m_PduState;
                return *this;
            }

                void setZAS_Kl_15_Raw(const bool _value) {
                    m_ZAS_Kl_15_Raw = _value;
                }
                bool getZAS_Kl_15_Raw() const {
                    return m_ZAS_Kl_15_Raw;
                }
                void setPduState(const uint64_t _value) {
                    m_PduState = _value;
                }
                uint64_t getPduState() const {
                    return m_PduState;
                }


        bool m_ZAS_Kl_15_Raw;
        uint64_t m_PduState;
    private:
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const asi::sid::v2xstack::cstyle::KlemmenStatus01Struct& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, asi::sid::v2xstack::cstyle::KlemmenStatus01Struct &val);
    };

} // cstyle
}//namespace asi
}//namespace sid
}//namespace v2xstack

#endif// ASI_SID_V2XSTACK_KLEMMENSTATUS01STRUCT_CSTYLE_HXX
