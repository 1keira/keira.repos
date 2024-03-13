/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef ASI_SID_V2XSTACK_LICHTANF01STRUCT_CSTYLE_HXX
#define ASI_SID_V2XSTACK_LICHTANF01STRUCT_CSTYLE_HXX

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
struct LichtAnf01Struct;
}
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const asi::sid::v2xstack::cstyle::LichtAnf01Struct& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, asi::sid::v2xstack::cstyle::LichtAnf01Struct &val);
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
    \brief struct v2xstack::LichtAnf01Struct.
    */
    struct PROXY_EXPORT LichtAnf01Struct
    {
        public:
            LichtAnf01Struct()
            : m_BCM1_Nebellicht_Anf_Raw()
            , m_BCM1_Parklicht_li_Anf_Raw()
            , m_BCM1_Parklicht_re_Anf_Raw()
            , m_BCM1_Nebelschluss_Fzg_Anf_Raw()
            , m_BCM1_Tagfahrlicht_Anf_Raw()
            , m_BCM1_Abblendlicht_Anf_Raw()
            , m_BCM1_Fernlicht_Anf_Raw()
            , m_PduState()
            { }

            LichtAnf01Struct (const LichtAnf01Struct& other)
            : m_BCM1_Nebellicht_Anf_Raw()
            , m_BCM1_Parklicht_li_Anf_Raw()
            , m_BCM1_Parklicht_re_Anf_Raw()
            , m_BCM1_Nebelschluss_Fzg_Anf_Raw()
            , m_BCM1_Tagfahrlicht_Anf_Raw()
            , m_BCM1_Abblendlicht_Anf_Raw()
            , m_BCM1_Fernlicht_Anf_Raw()
            , m_PduState()
            {
              *this = other;
            }

            ~LichtAnf01Struct () {
            }
            bool operator==(const LichtAnf01Struct& rhs) const {
                bool equal = true;
                if (m_BCM1_Nebellicht_Anf_Raw != rhs.m_BCM1_Nebellicht_Anf_Raw)
                    equal = false;
                if (m_BCM1_Parklicht_li_Anf_Raw != rhs.m_BCM1_Parklicht_li_Anf_Raw)
                    equal = false;
                if (m_BCM1_Parklicht_re_Anf_Raw != rhs.m_BCM1_Parklicht_re_Anf_Raw)
                    equal = false;
                if (m_BCM1_Nebelschluss_Fzg_Anf_Raw != rhs.m_BCM1_Nebelschluss_Fzg_Anf_Raw)
                    equal = false;
                if (m_BCM1_Tagfahrlicht_Anf_Raw != rhs.m_BCM1_Tagfahrlicht_Anf_Raw)
                    equal = false;
                if (m_BCM1_Abblendlicht_Anf_Raw != rhs.m_BCM1_Abblendlicht_Anf_Raw)
                    equal = false;
                if (m_BCM1_Fernlicht_Anf_Raw != rhs.m_BCM1_Fernlicht_Anf_Raw)
                    equal = false;
                if (m_PduState != rhs.m_PduState)
                    equal = false;
                return equal;
            }
            bool operator!=(const LichtAnf01Struct& rhs) const {
                return !operator==(rhs);
            }

            LichtAnf01Struct& operator = (const LichtAnf01Struct& src) {
                if (this == &src) return *this;
                m_BCM1_Nebellicht_Anf_Raw = src.m_BCM1_Nebellicht_Anf_Raw;
                m_BCM1_Parklicht_li_Anf_Raw = src.m_BCM1_Parklicht_li_Anf_Raw;
                m_BCM1_Parklicht_re_Anf_Raw = src.m_BCM1_Parklicht_re_Anf_Raw;
                m_BCM1_Nebelschluss_Fzg_Anf_Raw = src.m_BCM1_Nebelschluss_Fzg_Anf_Raw;
                m_BCM1_Tagfahrlicht_Anf_Raw = src.m_BCM1_Tagfahrlicht_Anf_Raw;
                m_BCM1_Abblendlicht_Anf_Raw = src.m_BCM1_Abblendlicht_Anf_Raw;
                m_BCM1_Fernlicht_Anf_Raw = src.m_BCM1_Fernlicht_Anf_Raw;
                m_PduState = src.m_PduState;
                return *this;
            }

                void setBCM1_Nebellicht_Anf_Raw(const bool _value) {
                    m_BCM1_Nebellicht_Anf_Raw = _value;
                }
                bool getBCM1_Nebellicht_Anf_Raw() const {
                    return m_BCM1_Nebellicht_Anf_Raw;
                }
                void setBCM1_Parklicht_li_Anf_Raw(const bool _value) {
                    m_BCM1_Parklicht_li_Anf_Raw = _value;
                }
                bool getBCM1_Parklicht_li_Anf_Raw() const {
                    return m_BCM1_Parklicht_li_Anf_Raw;
                }
                void setBCM1_Parklicht_re_Anf_Raw(const bool _value) {
                    m_BCM1_Parklicht_re_Anf_Raw = _value;
                }
                bool getBCM1_Parklicht_re_Anf_Raw() const {
                    return m_BCM1_Parklicht_re_Anf_Raw;
                }
                void setBCM1_Nebelschluss_Fzg_Anf_Raw(const bool _value) {
                    m_BCM1_Nebelschluss_Fzg_Anf_Raw = _value;
                }
                bool getBCM1_Nebelschluss_Fzg_Anf_Raw() const {
                    return m_BCM1_Nebelschluss_Fzg_Anf_Raw;
                }
                void setBCM1_Tagfahrlicht_Anf_Raw(const bool _value) {
                    m_BCM1_Tagfahrlicht_Anf_Raw = _value;
                }
                bool getBCM1_Tagfahrlicht_Anf_Raw() const {
                    return m_BCM1_Tagfahrlicht_Anf_Raw;
                }
                void setBCM1_Abblendlicht_Anf_Raw(const bool _value) {
                    m_BCM1_Abblendlicht_Anf_Raw = _value;
                }
                bool getBCM1_Abblendlicht_Anf_Raw() const {
                    return m_BCM1_Abblendlicht_Anf_Raw;
                }
                void setBCM1_Fernlicht_Anf_Raw(const bool _value) {
                    m_BCM1_Fernlicht_Anf_Raw = _value;
                }
                bool getBCM1_Fernlicht_Anf_Raw() const {
                    return m_BCM1_Fernlicht_Anf_Raw;
                }
                void setPduState(const uint64_t _value) {
                    m_PduState = _value;
                }
                uint64_t getPduState() const {
                    return m_PduState;
                }


        bool m_BCM1_Nebellicht_Anf_Raw;
        bool m_BCM1_Parklicht_li_Anf_Raw;
        bool m_BCM1_Parklicht_re_Anf_Raw;
        bool m_BCM1_Nebelschluss_Fzg_Anf_Raw;
        bool m_BCM1_Tagfahrlicht_Anf_Raw;
        bool m_BCM1_Abblendlicht_Anf_Raw;
        bool m_BCM1_Fernlicht_Anf_Raw;
        uint64_t m_PduState;
    private:
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const asi::sid::v2xstack::cstyle::LichtAnf01Struct& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, asi::sid::v2xstack::cstyle::LichtAnf01Struct &val);
    };

} // cstyle
}//namespace asi
}//namespace sid
}//namespace v2xstack

#endif// ASI_SID_V2XSTACK_LICHTANF01STRUCT_CSTYLE_HXX
