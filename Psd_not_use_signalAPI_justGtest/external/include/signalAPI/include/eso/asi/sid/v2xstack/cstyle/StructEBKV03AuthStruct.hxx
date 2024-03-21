/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef ASI_SID_V2XSTACK_EBKV03AUTHSTRUCT_CSTYLE_HXX
#define ASI_SID_V2XSTACK_EBKV03AUTHSTRUCT_CSTYLE_HXX

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
struct EBKV03AuthStruct;
}
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const asi::sid::v2xstack::cstyle::EBKV03AuthStruct& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, asi::sid::v2xstack::cstyle::EBKV03AuthStruct &val);
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
    \brief struct v2xstack::EBKV03AuthStruct.
    */
    struct PROXY_EXPORT EBKV03AuthStruct
    {
        public:
            EBKV03AuthStruct()
            : m_EBKV_QBit_Fahrer_bremst_Raw()
            , m_EBKV_Fahrer_bremst_Raw()
            , m_PduState()
            { }

            EBKV03AuthStruct (const EBKV03AuthStruct& other)
            : m_EBKV_QBit_Fahrer_bremst_Raw()
            , m_EBKV_Fahrer_bremst_Raw()
            , m_PduState()
            {
              *this = other;
            }

            ~EBKV03AuthStruct () {
            }
            bool operator==(const EBKV03AuthStruct& rhs) const {
                bool equal = true;
                if (m_EBKV_QBit_Fahrer_bremst_Raw != rhs.m_EBKV_QBit_Fahrer_bremst_Raw)
                    equal = false;
                if (m_EBKV_Fahrer_bremst_Raw != rhs.m_EBKV_Fahrer_bremst_Raw)
                    equal = false;
                if (m_PduState != rhs.m_PduState)
                    equal = false;
                return equal;
            }
            bool operator!=(const EBKV03AuthStruct& rhs) const {
                return !operator==(rhs);
            }

            EBKV03AuthStruct& operator = (const EBKV03AuthStruct& src) {
                if (this == &src) return *this;
                m_EBKV_QBit_Fahrer_bremst_Raw = src.m_EBKV_QBit_Fahrer_bremst_Raw;
                m_EBKV_Fahrer_bremst_Raw = src.m_EBKV_Fahrer_bremst_Raw;
                m_PduState = src.m_PduState;
                return *this;
            }

                void setEBKV_QBit_Fahrer_bremst_Raw(const bool _value) {
                    m_EBKV_QBit_Fahrer_bremst_Raw = _value;
                }
                bool getEBKV_QBit_Fahrer_bremst_Raw() const {
                    return m_EBKV_QBit_Fahrer_bremst_Raw;
                }
                void setEBKV_Fahrer_bremst_Raw(const bool _value) {
                    m_EBKV_Fahrer_bremst_Raw = _value;
                }
                bool getEBKV_Fahrer_bremst_Raw() const {
                    return m_EBKV_Fahrer_bremst_Raw;
                }
                void setPduState(const uint64_t _value) {
                    m_PduState = _value;
                }
                uint64_t getPduState() const {
                    return m_PduState;
                }


        bool m_EBKV_QBit_Fahrer_bremst_Raw;
        bool m_EBKV_Fahrer_bremst_Raw;
        uint64_t m_PduState;
    private:
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const asi::sid::v2xstack::cstyle::EBKV03AuthStruct& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, asi::sid::v2xstack::cstyle::EBKV03AuthStruct &val);
    };

} // cstyle
}//namespace asi
}//namespace sid
}//namespace v2xstack

#endif// ASI_SID_V2XSTACK_EBKV03AUTHSTRUCT_CSTYLE_HXX
