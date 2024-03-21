/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef ASI_SID_LHWAPP_BLINKMODI02STRUCT_CSTYLE_HXX
#define ASI_SID_LHWAPP_BLINKMODI02STRUCT_CSTYLE_HXX

#include <comm/commidltypes.hxx>

// Forward declaration of the struct needed for the forward declaration of the deserializer
namespace asi
{
namespace sid
{
namespace lhwapp
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
bool serialize (util::serializer::IStructuredSerializer &ser, const asi::sid::lhwapp::cstyle::Blinkmodi02Struct& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, asi::sid::lhwapp::cstyle::Blinkmodi02Struct &val);
}
}

namespace asi
{
namespace sid
{
namespace lhwapp
{
namespace  cstyle
{

    /**
    \brief struct lhwapp::Blinkmodi02Struct.
    */
    struct PROXY_EXPORT Blinkmodi02Struct
    {
        public:
            Blinkmodi02Struct()
            : m_BM_Recas_Raw()
            , m_BM_Crash_Raw()
            , m_BM_Warnblinken_Raw()
            , m_BM_Not_Bremsung_Raw()
            , m_PduState()
            { }

            Blinkmodi02Struct (const Blinkmodi02Struct& other)
            : m_BM_Recas_Raw()
            , m_BM_Crash_Raw()
            , m_BM_Warnblinken_Raw()
            , m_BM_Not_Bremsung_Raw()
            , m_PduState()
            {
              *this = other;
            }

            ~Blinkmodi02Struct () {
            }
            bool operator==(const Blinkmodi02Struct& rhs) const {
                bool equal = true;
                if (m_BM_Recas_Raw != rhs.m_BM_Recas_Raw)
                    equal = false;
                if (m_BM_Crash_Raw != rhs.m_BM_Crash_Raw)
                    equal = false;
                if (m_BM_Warnblinken_Raw != rhs.m_BM_Warnblinken_Raw)
                    equal = false;
                if (m_BM_Not_Bremsung_Raw != rhs.m_BM_Not_Bremsung_Raw)
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
                m_BM_Recas_Raw = src.m_BM_Recas_Raw;
                m_BM_Crash_Raw = src.m_BM_Crash_Raw;
                m_BM_Warnblinken_Raw = src.m_BM_Warnblinken_Raw;
                m_BM_Not_Bremsung_Raw = src.m_BM_Not_Bremsung_Raw;
                m_PduState = src.m_PduState;
                return *this;
            }

                void setBM_Recas_Raw(const bool _value) {
                    m_BM_Recas_Raw = _value;
                }
                bool getBM_Recas_Raw() const {
                    return m_BM_Recas_Raw;
                }
                void setBM_Crash_Raw(const bool _value) {
                    m_BM_Crash_Raw = _value;
                }
                bool getBM_Crash_Raw() const {
                    return m_BM_Crash_Raw;
                }
                void setBM_Warnblinken_Raw(const bool _value) {
                    m_BM_Warnblinken_Raw = _value;
                }
                bool getBM_Warnblinken_Raw() const {
                    return m_BM_Warnblinken_Raw;
                }
                void setBM_Not_Bremsung_Raw(const bool _value) {
                    m_BM_Not_Bremsung_Raw = _value;
                }
                bool getBM_Not_Bremsung_Raw() const {
                    return m_BM_Not_Bremsung_Raw;
                }
                void setPduState(const uint64_t _value) {
                    m_PduState = _value;
                }
                uint64_t getPduState() const {
                    return m_PduState;
                }


        bool m_BM_Recas_Raw;
        bool m_BM_Crash_Raw;
        bool m_BM_Warnblinken_Raw;
        bool m_BM_Not_Bremsung_Raw;
        uint64_t m_PduState;
    private:
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const asi::sid::lhwapp::cstyle::Blinkmodi02Struct& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, asi::sid::lhwapp::cstyle::Blinkmodi02Struct &val);
    };

} // cstyle
}//namespace asi
}//namespace sid
}//namespace lhwapp

#endif// ASI_SID_LHWAPP_BLINKMODI02STRUCT_CSTYLE_HXX
