/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef ASI_SID_V2XSTACK_ESC51AUTHSTRUCT_CSTYLE_HXX
#define ASI_SID_V2XSTACK_ESC51AUTHSTRUCT_CSTYLE_HXX

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
struct ESC51AuthStruct;
}
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const asi::sid::v2xstack::cstyle::ESC51AuthStruct& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, asi::sid::v2xstack::cstyle::ESC51AuthStruct &val);
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
    \brief struct v2xstack::ESC51AuthStruct.
    */
    struct PROXY_EXPORT ESC51AuthStruct
    {
        public:
            ESC51AuthStruct()
            : m_ESP_HR_Bremsmoment_Raw()
            , m_ESP_HR_Bremsmoment_SignalState()
            , m_ESP_VR_Bremsmoment_Raw()
            , m_ESP_VR_Bremsmoment_SignalState()
            , m_ESP_VL_Bremsmoment_Raw()
            , m_ESP_VL_Bremsmoment_SignalState()
            , m_ESP_HL_Bremsmoment_Raw()
            , m_ESP_HL_Bremsmoment_SignalState()
            , m_PduState()
            { }

            ESC51AuthStruct (const ESC51AuthStruct& other)
            : m_ESP_HR_Bremsmoment_Raw()
            , m_ESP_HR_Bremsmoment_SignalState()
            , m_ESP_VR_Bremsmoment_Raw()
            , m_ESP_VR_Bremsmoment_SignalState()
            , m_ESP_VL_Bremsmoment_Raw()
            , m_ESP_VL_Bremsmoment_SignalState()
            , m_ESP_HL_Bremsmoment_Raw()
            , m_ESP_HL_Bremsmoment_SignalState()
            , m_PduState()
            {
              *this = other;
            }

            ~ESC51AuthStruct () {
            }
            bool operator==(const ESC51AuthStruct& rhs) const {
                bool equal = true;
                if (m_ESP_HR_Bremsmoment_Raw != rhs.m_ESP_HR_Bremsmoment_Raw)
                    equal = false;
                if (m_ESP_HR_Bremsmoment_SignalState != rhs.m_ESP_HR_Bremsmoment_SignalState)
                    equal = false;
                if (m_ESP_VR_Bremsmoment_Raw != rhs.m_ESP_VR_Bremsmoment_Raw)
                    equal = false;
                if (m_ESP_VR_Bremsmoment_SignalState != rhs.m_ESP_VR_Bremsmoment_SignalState)
                    equal = false;
                if (m_ESP_VL_Bremsmoment_Raw != rhs.m_ESP_VL_Bremsmoment_Raw)
                    equal = false;
                if (m_ESP_VL_Bremsmoment_SignalState != rhs.m_ESP_VL_Bremsmoment_SignalState)
                    equal = false;
                if (m_ESP_HL_Bremsmoment_Raw != rhs.m_ESP_HL_Bremsmoment_Raw)
                    equal = false;
                if (m_ESP_HL_Bremsmoment_SignalState != rhs.m_ESP_HL_Bremsmoment_SignalState)
                    equal = false;
                if (m_PduState != rhs.m_PduState)
                    equal = false;
                return equal;
            }
            bool operator!=(const ESC51AuthStruct& rhs) const {
                return !operator==(rhs);
            }

            ESC51AuthStruct& operator = (const ESC51AuthStruct& src) {
                if (this == &src) return *this;
                m_ESP_HR_Bremsmoment_Raw = src.m_ESP_HR_Bremsmoment_Raw;
                m_ESP_HR_Bremsmoment_SignalState = src.m_ESP_HR_Bremsmoment_SignalState;
                m_ESP_VR_Bremsmoment_Raw = src.m_ESP_VR_Bremsmoment_Raw;
                m_ESP_VR_Bremsmoment_SignalState = src.m_ESP_VR_Bremsmoment_SignalState;
                m_ESP_VL_Bremsmoment_Raw = src.m_ESP_VL_Bremsmoment_Raw;
                m_ESP_VL_Bremsmoment_SignalState = src.m_ESP_VL_Bremsmoment_SignalState;
                m_ESP_HL_Bremsmoment_Raw = src.m_ESP_HL_Bremsmoment_Raw;
                m_ESP_HL_Bremsmoment_SignalState = src.m_ESP_HL_Bremsmoment_SignalState;
                m_PduState = src.m_PduState;
                return *this;
            }

                void setESP_HR_Bremsmoment_Raw(const uint8_t _value) {
                    m_ESP_HR_Bremsmoment_Raw = _value;
                }
                uint8_t getESP_HR_Bremsmoment_Raw() const {
                    return m_ESP_HR_Bremsmoment_Raw;
                }
                void setESP_HR_Bremsmoment_SignalState(const uint64_t _value) {
                    m_ESP_HR_Bremsmoment_SignalState = _value;
                }
                uint64_t getESP_HR_Bremsmoment_SignalState() const {
                    return m_ESP_HR_Bremsmoment_SignalState;
                }
                void setESP_VR_Bremsmoment_Raw(const uint8_t _value) {
                    m_ESP_VR_Bremsmoment_Raw = _value;
                }
                uint8_t getESP_VR_Bremsmoment_Raw() const {
                    return m_ESP_VR_Bremsmoment_Raw;
                }
                void setESP_VR_Bremsmoment_SignalState(const uint64_t _value) {
                    m_ESP_VR_Bremsmoment_SignalState = _value;
                }
                uint64_t getESP_VR_Bremsmoment_SignalState() const {
                    return m_ESP_VR_Bremsmoment_SignalState;
                }
                void setESP_VL_Bremsmoment_Raw(const uint8_t _value) {
                    m_ESP_VL_Bremsmoment_Raw = _value;
                }
                uint8_t getESP_VL_Bremsmoment_Raw() const {
                    return m_ESP_VL_Bremsmoment_Raw;
                }
                void setESP_VL_Bremsmoment_SignalState(const uint64_t _value) {
                    m_ESP_VL_Bremsmoment_SignalState = _value;
                }
                uint64_t getESP_VL_Bremsmoment_SignalState() const {
                    return m_ESP_VL_Bremsmoment_SignalState;
                }
                void setESP_HL_Bremsmoment_Raw(const uint8_t _value) {
                    m_ESP_HL_Bremsmoment_Raw = _value;
                }
                uint8_t getESP_HL_Bremsmoment_Raw() const {
                    return m_ESP_HL_Bremsmoment_Raw;
                }
                void setESP_HL_Bremsmoment_SignalState(const uint64_t _value) {
                    m_ESP_HL_Bremsmoment_SignalState = _value;
                }
                uint64_t getESP_HL_Bremsmoment_SignalState() const {
                    return m_ESP_HL_Bremsmoment_SignalState;
                }
                void setPduState(const uint64_t _value) {
                    m_PduState = _value;
                }
                uint64_t getPduState() const {
                    return m_PduState;
                }


        uint8_t m_ESP_HR_Bremsmoment_Raw;
        uint64_t m_ESP_HR_Bremsmoment_SignalState;
        uint8_t m_ESP_VR_Bremsmoment_Raw;
        uint64_t m_ESP_VR_Bremsmoment_SignalState;
        uint8_t m_ESP_VL_Bremsmoment_Raw;
        uint64_t m_ESP_VL_Bremsmoment_SignalState;
        uint8_t m_ESP_HL_Bremsmoment_Raw;
        uint64_t m_ESP_HL_Bremsmoment_SignalState;
        uint64_t m_PduState;
    private:
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const asi::sid::v2xstack::cstyle::ESC51AuthStruct& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, asi::sid::v2xstack::cstyle::ESC51AuthStruct &val);
    };

} // cstyle
}//namespace asi
}//namespace sid
}//namespace v2xstack

#endif// ASI_SID_V2XSTACK_ESC51AUTHSTRUCT_CSTYLE_HXX
