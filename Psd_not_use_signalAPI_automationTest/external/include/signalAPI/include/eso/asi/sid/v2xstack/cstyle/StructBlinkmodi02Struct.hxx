/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef ASI_SID_V2XSTACK_BLINKMODI02STRUCT_CSTYLE_HXX
#define ASI_SID_V2XSTACK_BLINKMODI02STRUCT_CSTYLE_HXX

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
struct Blinkmodi02Struct;
}
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const asi::sid::v2xstack::cstyle::Blinkmodi02Struct& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, asi::sid::v2xstack::cstyle::Blinkmodi02Struct &val);
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
    \brief struct v2xstack::Blinkmodi02Struct.
    */
    struct PROXY_EXPORT Blinkmodi02Struct
    {
        public:
            Blinkmodi02Struct()
            : m_BM_Warnblinken_Raw()
            , m_BM_links_Raw()
            , m_BM_rechts_Raw()
            , m_PduState()
            { }

            Blinkmodi02Struct (const Blinkmodi02Struct& other)
            : m_BM_Warnblinken_Raw()
            , m_BM_links_Raw()
            , m_BM_rechts_Raw()
            , m_PduState()
            {
              *this = other;
            }

            ~Blinkmodi02Struct () {
            }
            bool operator==(const Blinkmodi02Struct& rhs) const {
                bool equal = true;
                if (m_BM_Warnblinken_Raw != rhs.m_BM_Warnblinken_Raw)
                    equal = false;
                if (m_BM_links_Raw != rhs.m_BM_links_Raw)
                    equal = false;
                if (m_BM_rechts_Raw != rhs.m_BM_rechts_Raw)
                    equal = false;
                if (m_PduState != rhs.m_PduState)
                    equal = false;
                return equal;
            }
            bool operator!=(const Blinkmodi02Struct& rhs) const {
                return !operator==(rhs);
            }

            Blinkmodi02Struct& operator = (const Blinkmodi02Struct& src) {
                if (this == &src) return *this;
                m_BM_Warnblinken_Raw = src.m_BM_Warnblinken_Raw;
                m_BM_links_Raw = src.m_BM_links_Raw;
                m_BM_rechts_Raw = src.m_BM_rechts_Raw;
                m_PduState = src.m_PduState;
                return *this;
            }

                void setBM_Warnblinken_Raw(const bool _value) {
                    m_BM_Warnblinken_Raw = _value;
                }
                bool getBM_Warnblinken_Raw() const {
                    return m_BM_Warnblinken_Raw;
                }
                void setBM_links_Raw(const bool _value) {
                    m_BM_links_Raw = _value;
                }
                bool getBM_links_Raw() const {
                    return m_BM_links_Raw;
                }
                void setBM_rechts_Raw(const bool _value) {
                    m_BM_rechts_Raw = _value;
                }
                bool getBM_rechts_Raw() const {
                    return m_BM_rechts_Raw;
                }
                void setPduState(const uint64_t _value) {
                    m_PduState = _value;
                }
                uint64_t getPduState() const {
                    return m_PduState;
                }


        bool m_BM_Warnblinken_Raw;
        bool m_BM_links_Raw;
        bool m_BM_rechts_Raw;
        uint64_t m_PduState;
    private:
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const asi::sid::v2xstack::cstyle::Blinkmodi02Struct& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, asi::sid::v2xstack::cstyle::Blinkmodi02Struct &val);
    };

} // cstyle
}//namespace asi
}//namespace sid
}//namespace v2xstack

#endif// ASI_SID_V2XSTACK_BLINKMODI02STRUCT_CSTYLE_HXX
