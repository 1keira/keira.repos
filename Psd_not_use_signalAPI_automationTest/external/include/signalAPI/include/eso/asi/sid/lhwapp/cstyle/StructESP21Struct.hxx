/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef ASI_SID_LHWAPP_ESP21STRUCT_CSTYLE_HXX
#define ASI_SID_LHWAPP_ESP21STRUCT_CSTYLE_HXX

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
struct ESP21Struct;
}
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const asi::sid::lhwapp::cstyle::ESP21Struct& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, asi::sid::lhwapp::cstyle::ESP21Struct &val);
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
    \brief struct lhwapp::ESP21Struct.
    */
    struct PROXY_EXPORT ESP21Struct
    {
        public:
            ESP21Struct()
            : m_ESP_v_Signal_Raw()
            , m_ESP_v_Signal_SignalState()
            , m_ESP_QBit_v_Signal_Raw()
            , m_ABS_Bremsung_Raw()
            , m_ASR_Anf_Raw()
            , m_ESP_Eingriff_Raw()
            , m_PduState()
            { }

            ESP21Struct (const ESP21Struct& other)
            : m_ESP_v_Signal_Raw()
            , m_ESP_v_Signal_SignalState()
            , m_ESP_QBit_v_Signal_Raw()
            , m_ABS_Bremsung_Raw()
            , m_ASR_Anf_Raw()
            , m_ESP_Eingriff_Raw()
            , m_PduState()
            {
              *this = other;
            }

            ~ESP21Struct () {
            }
            bool operator==(const ESP21Struct& rhs) const {
                bool equal = true;
                if (m_ESP_v_Signal_Raw != rhs.m_ESP_v_Signal_Raw)
                    equal = false;
                if (m_ESP_v_Signal_SignalState != rhs.m_ESP_v_Signal_SignalState)
                    equal = false;
                if (m_ESP_QBit_v_Signal_Raw != rhs.m_ESP_QBit_v_Signal_Raw)
                    equal = false;
                if (m_ABS_Bremsung_Raw != rhs.m_ABS_Bremsung_Raw)
                    equal = false;
                if (m_ASR_Anf_Raw != rhs.m_ASR_Anf_Raw)
                    equal = false;
                if (m_ESP_Eingriff_Raw != rhs.m_ESP_Eingriff_Raw)
                    equal = false;
                if (m_PduState != rhs.m_PduState)
                    equal = false;
                return equal;
            }
            bool operator!=(const ESP21Struct& rhs) const {
                return !operator==(rhs);
            }

            ESP21Struct& operator = (const ESP21Struct& src) {
                if (this == &src) return *this;
                m_ESP_v_Signal_Raw = src.m_ESP_v_Signal_Raw;
                m_ESP_v_Signal_SignalState = src.m_ESP_v_Signal_SignalState;
                m_ESP_QBit_v_Signal_Raw = src.m_ESP_QBit_v_Signal_Raw;
                m_ABS_Bremsung_Raw = src.m_ABS_Bremsung_Raw;
                m_ASR_Anf_Raw = src.m_ASR_Anf_Raw;
                m_ESP_Eingriff_Raw = src.m_ESP_Eingriff_Raw;
                m_PduState = src.m_PduState;
                return *this;
            }

                void setESP_v_Signal_Raw(const uint16_t _value) {
                    m_ESP_v_Signal_Raw = _value;
                }
                uint16_t getESP_v_Signal_Raw() const {
                    return m_ESP_v_Signal_Raw;
                }
                void setESP_v_Signal_SignalState(const uint64_t _value) {
                    m_ESP_v_Signal_SignalState = _value;
                }
                uint64_t getESP_v_Signal_SignalState() const {
                    return m_ESP_v_Signal_SignalState;
                }
                void setESP_QBit_v_Signal_Raw(const bool _value) {
                    m_ESP_QBit_v_Signal_Raw = _value;
                }
                bool getESP_QBit_v_Signal_Raw() const {
                    return m_ESP_QBit_v_Signal_Raw;
                }
                void setABS_Bremsung_Raw(const bool _value) {
                    m_ABS_Bremsung_Raw = _value;
                }
                bool getABS_Bremsung_Raw() const {
                    return m_ABS_Bremsung_Raw;
                }
                void setASR_Anf_Raw(const bool _value) {
                    m_ASR_Anf_Raw = _value;
                }
                bool getASR_Anf_Raw() const {
                    return m_ASR_Anf_Raw;
                }
                void setESP_Eingriff_Raw(const bool _value) {
                    m_ESP_Eingriff_Raw = _value;
                }
                bool getESP_Eingriff_Raw() const {
                    return m_ESP_Eingriff_Raw;
                }
                void setPduState(const uint64_t _value) {
                    m_PduState = _value;
                }
                uint64_t getPduState() const {
                    return m_PduState;
                }


        uint16_t m_ESP_v_Signal_Raw;
        uint64_t m_ESP_v_Signal_SignalState;
        bool m_ESP_QBit_v_Signal_Raw;
        bool m_ABS_Bremsung_Raw;
        bool m_ASR_Anf_Raw;
        bool m_ESP_Eingriff_Raw;
        uint64_t m_PduState;
    private:
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const asi::sid::lhwapp::cstyle::ESP21Struct& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, asi::sid::lhwapp::cstyle::ESP21Struct &val);
    };

} // cstyle
}//namespace asi
}//namespace sid
}//namespace lhwapp

#endif// ASI_SID_LHWAPP_ESP21STRUCT_CSTYLE_HXX
