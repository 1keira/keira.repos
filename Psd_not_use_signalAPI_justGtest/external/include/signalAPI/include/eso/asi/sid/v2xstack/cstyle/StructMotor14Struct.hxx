/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef ASI_SID_V2XSTACK_MOTOR14STRUCT_CSTYLE_HXX
#define ASI_SID_V2XSTACK_MOTOR14STRUCT_CSTYLE_HXX

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
struct Motor14Struct;
}
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const asi::sid::v2xstack::cstyle::Motor14Struct& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, asi::sid::v2xstack::cstyle::Motor14Struct &val);
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
    \brief struct v2xstack::Motor14Struct.
    */
    struct PROXY_EXPORT Motor14Struct
    {
        public:
            Motor14Struct()
            : m_MO_Fahrer_bremst_Raw()
            , m_MO_QBit_Fahrer_bremst_Raw()
            , m_PduState()
            { }

            Motor14Struct (const Motor14Struct& other)
            : m_MO_Fahrer_bremst_Raw()
            , m_MO_QBit_Fahrer_bremst_Raw()
            , m_PduState()
            {
              *this = other;
            }

            ~Motor14Struct () {
            }
            bool operator==(const Motor14Struct& rhs) const {
                bool equal = true;
                if (m_MO_Fahrer_bremst_Raw != rhs.m_MO_Fahrer_bremst_Raw)
                    equal = false;
                if (m_MO_QBit_Fahrer_bremst_Raw != rhs.m_MO_QBit_Fahrer_bremst_Raw)
                    equal = false;
                if (m_PduState != rhs.m_PduState)
                    equal = false;
                return equal;
            }
            bool operator!=(const Motor14Struct& rhs) const {
                return !operator==(rhs);
            }

            Motor14Struct& operator = (const Motor14Struct& src) {
                if (this == &src) return *this;
                m_MO_Fahrer_bremst_Raw = src.m_MO_Fahrer_bremst_Raw;
                m_MO_QBit_Fahrer_bremst_Raw = src.m_MO_QBit_Fahrer_bremst_Raw;
                m_PduState = src.m_PduState;
                return *this;
            }

                void setMO_Fahrer_bremst_Raw(const bool _value) {
                    m_MO_Fahrer_bremst_Raw = _value;
                }
                bool getMO_Fahrer_bremst_Raw() const {
                    return m_MO_Fahrer_bremst_Raw;
                }
                void setMO_QBit_Fahrer_bremst_Raw(const bool _value) {
                    m_MO_QBit_Fahrer_bremst_Raw = _value;
                }
                bool getMO_QBit_Fahrer_bremst_Raw() const {
                    return m_MO_QBit_Fahrer_bremst_Raw;
                }
                void setPduState(const uint64_t _value) {
                    m_PduState = _value;
                }
                uint64_t getPduState() const {
                    return m_PduState;
                }


        bool m_MO_Fahrer_bremst_Raw;
        bool m_MO_QBit_Fahrer_bremst_Raw;
        uint64_t m_PduState;
    private:
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const asi::sid::v2xstack::cstyle::Motor14Struct& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, asi::sid::v2xstack::cstyle::Motor14Struct &val);
    };

} // cstyle
}//namespace asi
}//namespace sid
}//namespace v2xstack

#endif// ASI_SID_V2XSTACK_MOTOR14STRUCT_CSTYLE_HXX
