/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef ASI_SID_LHWAPP_ESP24STRUCT_CSTYLE_HXX
#define ASI_SID_LHWAPP_ESP24STRUCT_CSTYLE_HXX

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
struct ESP24Struct;
}
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const asi::sid::lhwapp::cstyle::ESP24Struct& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, asi::sid::lhwapp::cstyle::ESP24Struct &val);
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
    \brief struct lhwapp::ESP24Struct.
    */
    struct PROXY_EXPORT ESP24Struct
    {
        public:
            ESP24Struct()
            : m_ESP_Lampe_Raw()
            , m_ABS_Lampe_Raw()
            , m_BK_Lampe_02_Raw()
            , m_PduState()
            { }

            ESP24Struct (const ESP24Struct& other)
            : m_ESP_Lampe_Raw()
            , m_ABS_Lampe_Raw()
            , m_BK_Lampe_02_Raw()
            , m_PduState()
            {
              *this = other;
            }

            ~ESP24Struct () {
            }
            bool operator==(const ESP24Struct& rhs) const {
                bool equal = true;
                if (m_ESP_Lampe_Raw != rhs.m_ESP_Lampe_Raw)
                    equal = false;
                if (m_ABS_Lampe_Raw != rhs.m_ABS_Lampe_Raw)
                    equal = false;
                if (m_BK_Lampe_02_Raw != rhs.m_BK_Lampe_02_Raw)
                    equal = false;
                if (m_PduState != rhs.m_PduState)
                    equal = false;
                return equal;
            }
            bool operator!=(const ESP24Struct& rhs) const {
                return !operator==(rhs);
            }

            ESP24Struct& operator = (const ESP24Struct& src) {
                if (this == &src) return *this;
                m_ESP_Lampe_Raw = src.m_ESP_Lampe_Raw;
                m_ABS_Lampe_Raw = src.m_ABS_Lampe_Raw;
                m_BK_Lampe_02_Raw = src.m_BK_Lampe_02_Raw;
                m_PduState = src.m_PduState;
                return *this;
            }

                void setESP_Lampe_Raw(const bool _value) {
                    m_ESP_Lampe_Raw = _value;
                }
                bool getESP_Lampe_Raw() const {
                    return m_ESP_Lampe_Raw;
                }
                void setABS_Lampe_Raw(const bool _value) {
                    m_ABS_Lampe_Raw = _value;
                }
                bool getABS_Lampe_Raw() const {
                    return m_ABS_Lampe_Raw;
                }
                void setBK_Lampe_02_Raw(const uint8_t _value) {
                    m_BK_Lampe_02_Raw = _value;
                }
                uint8_t getBK_Lampe_02_Raw() const {
                    return m_BK_Lampe_02_Raw;
                }
                void setPduState(const uint64_t _value) {
                    m_PduState = _value;
                }
                uint64_t getPduState() const {
                    return m_PduState;
                }


        bool m_ESP_Lampe_Raw;
        bool m_ABS_Lampe_Raw;
        uint8_t m_BK_Lampe_02_Raw;
        uint64_t m_PduState;
    private:
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const asi::sid::lhwapp::cstyle::ESP24Struct& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, asi::sid::lhwapp::cstyle::ESP24Struct &val);
    };

} // cstyle
}//namespace asi
}//namespace sid
}//namespace lhwapp

#endif// ASI_SID_LHWAPP_ESP24STRUCT_CSTYLE_HXX
