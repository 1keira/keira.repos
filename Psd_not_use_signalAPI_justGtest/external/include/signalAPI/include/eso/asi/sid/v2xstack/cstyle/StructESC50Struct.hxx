/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef ASI_SID_V2XSTACK_ESC50STRUCT_CSTYLE_HXX
#define ASI_SID_V2XSTACK_ESC50STRUCT_CSTYLE_HXX

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
struct ESC50Struct;
}
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const asi::sid::v2xstack::cstyle::ESC50Struct& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, asi::sid::v2xstack::cstyle::ESC50Struct &val);
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
    \brief struct v2xstack::ESC50Struct.
    */
    struct PROXY_EXPORT ESC50Struct
    {
        public:
            ESC50Struct()
            : m_ESP_QBit_Gierrate_Raw()
            , m_ESP_QBit_Laengsbeschl_Raw()
            , m_ESP_QBit_Querb_Raw()
            , m_ESP_Querbeschleunigung_Raw()
            , m_ESP_Querbeschleunigung_SignalState()
            , m_ESP_Eingr_HL_Raw()
            , m_ESP_Eingr_HR_Raw()
            , m_ESP_Eingr_VL_Raw()
            , m_ESP_Eingr_VR_Raw()
            , m_ESP_Laengsbeschl_Raw()
            , m_ESP_Laengsbeschl_SignalState()
            , m_ESP_Gierrate_Raw()
            , m_ESP_Gierrate_SignalState()
            , m_ESP_VZ_Gierrate_Raw()
            , m_ESP_Notbremsanzeige_Raw()
            , m_ESP_Fahrer_bremst_Raw()
            , m_PduState()
            { }

            ESC50Struct (const ESC50Struct& other)
            : m_ESP_QBit_Gierrate_Raw()
            , m_ESP_QBit_Laengsbeschl_Raw()
            , m_ESP_QBit_Querb_Raw()
            , m_ESP_Querbeschleunigung_Raw()
            , m_ESP_Querbeschleunigung_SignalState()
            , m_ESP_Eingr_HL_Raw()
            , m_ESP_Eingr_HR_Raw()
            , m_ESP_Eingr_VL_Raw()
            , m_ESP_Eingr_VR_Raw()
            , m_ESP_Laengsbeschl_Raw()
            , m_ESP_Laengsbeschl_SignalState()
            , m_ESP_Gierrate_Raw()
            , m_ESP_Gierrate_SignalState()
            , m_ESP_VZ_Gierrate_Raw()
            , m_ESP_Notbremsanzeige_Raw()
            , m_ESP_Fahrer_bremst_Raw()
            , m_PduState()
            {
              *this = other;
            }

            ~ESC50Struct () {
            }
            bool operator==(const ESC50Struct& rhs) const {
                bool equal = true;
                if (m_ESP_QBit_Gierrate_Raw != rhs.m_ESP_QBit_Gierrate_Raw)
                    equal = false;
                if (m_ESP_QBit_Laengsbeschl_Raw != rhs.m_ESP_QBit_Laengsbeschl_Raw)
                    equal = false;
                if (m_ESP_QBit_Querb_Raw != rhs.m_ESP_QBit_Querb_Raw)
                    equal = false;
                if (m_ESP_Querbeschleunigung_Raw != rhs.m_ESP_Querbeschleunigung_Raw)
                    equal = false;
                if (m_ESP_Querbeschleunigung_SignalState != rhs.m_ESP_Querbeschleunigung_SignalState)
                    equal = false;
                if (m_ESP_Eingr_HL_Raw != rhs.m_ESP_Eingr_HL_Raw)
                    equal = false;
                if (m_ESP_Eingr_HR_Raw != rhs.m_ESP_Eingr_HR_Raw)
                    equal = false;
                if (m_ESP_Eingr_VL_Raw != rhs.m_ESP_Eingr_VL_Raw)
                    equal = false;
                if (m_ESP_Eingr_VR_Raw != rhs.m_ESP_Eingr_VR_Raw)
                    equal = false;
                if (m_ESP_Laengsbeschl_Raw != rhs.m_ESP_Laengsbeschl_Raw)
                    equal = false;
                if (m_ESP_Laengsbeschl_SignalState != rhs.m_ESP_Laengsbeschl_SignalState)
                    equal = false;
                if (m_ESP_Gierrate_Raw != rhs.m_ESP_Gierrate_Raw)
                    equal = false;
                if (m_ESP_Gierrate_SignalState != rhs.m_ESP_Gierrate_SignalState)
                    equal = false;
                if (m_ESP_VZ_Gierrate_Raw != rhs.m_ESP_VZ_Gierrate_Raw)
                    equal = false;
                if (m_ESP_Notbremsanzeige_Raw != rhs.m_ESP_Notbremsanzeige_Raw)
                    equal = false;
                if (m_ESP_Fahrer_bremst_Raw != rhs.m_ESP_Fahrer_bremst_Raw)
                    equal = false;
                if (m_PduState != rhs.m_PduState)
                    equal = false;
                return equal;
            }
            bool operator!=(const ESC50Struct& rhs) const {
                return !operator==(rhs);
            }

            ESC50Struct& operator = (const ESC50Struct& src) {
                if (this == &src) return *this;
                m_ESP_QBit_Gierrate_Raw = src.m_ESP_QBit_Gierrate_Raw;
                m_ESP_QBit_Laengsbeschl_Raw = src.m_ESP_QBit_Laengsbeschl_Raw;
                m_ESP_QBit_Querb_Raw = src.m_ESP_QBit_Querb_Raw;
                m_ESP_Querbeschleunigung_Raw = src.m_ESP_Querbeschleunigung_Raw;
                m_ESP_Querbeschleunigung_SignalState = src.m_ESP_Querbeschleunigung_SignalState;
                m_ESP_Eingr_HL_Raw = src.m_ESP_Eingr_HL_Raw;
                m_ESP_Eingr_HR_Raw = src.m_ESP_Eingr_HR_Raw;
                m_ESP_Eingr_VL_Raw = src.m_ESP_Eingr_VL_Raw;
                m_ESP_Eingr_VR_Raw = src.m_ESP_Eingr_VR_Raw;
                m_ESP_Laengsbeschl_Raw = src.m_ESP_Laengsbeschl_Raw;
                m_ESP_Laengsbeschl_SignalState = src.m_ESP_Laengsbeschl_SignalState;
                m_ESP_Gierrate_Raw = src.m_ESP_Gierrate_Raw;
                m_ESP_Gierrate_SignalState = src.m_ESP_Gierrate_SignalState;
                m_ESP_VZ_Gierrate_Raw = src.m_ESP_VZ_Gierrate_Raw;
                m_ESP_Notbremsanzeige_Raw = src.m_ESP_Notbremsanzeige_Raw;
                m_ESP_Fahrer_bremst_Raw = src.m_ESP_Fahrer_bremst_Raw;
                m_PduState = src.m_PduState;
                return *this;
            }

                void setESP_QBit_Gierrate_Raw(const bool _value) {
                    m_ESP_QBit_Gierrate_Raw = _value;
                }
                bool getESP_QBit_Gierrate_Raw() const {
                    return m_ESP_QBit_Gierrate_Raw;
                }
                void setESP_QBit_Laengsbeschl_Raw(const bool _value) {
                    m_ESP_QBit_Laengsbeschl_Raw = _value;
                }
                bool getESP_QBit_Laengsbeschl_Raw() const {
                    return m_ESP_QBit_Laengsbeschl_Raw;
                }
                void setESP_QBit_Querb_Raw(const bool _value) {
                    m_ESP_QBit_Querb_Raw = _value;
                }
                bool getESP_QBit_Querb_Raw() const {
                    return m_ESP_QBit_Querb_Raw;
                }
                void setESP_Querbeschleunigung_Raw(const uint8_t _value) {
                    m_ESP_Querbeschleunigung_Raw = _value;
                }
                uint8_t getESP_Querbeschleunigung_Raw() const {
                    return m_ESP_Querbeschleunigung_Raw;
                }
                void setESP_Querbeschleunigung_SignalState(const uint64_t _value) {
                    m_ESP_Querbeschleunigung_SignalState = _value;
                }
                uint64_t getESP_Querbeschleunigung_SignalState() const {
                    return m_ESP_Querbeschleunigung_SignalState;
                }
                void setESP_Eingr_HL_Raw(const bool _value) {
                    m_ESP_Eingr_HL_Raw = _value;
                }
                bool getESP_Eingr_HL_Raw() const {
                    return m_ESP_Eingr_HL_Raw;
                }
                void setESP_Eingr_HR_Raw(const bool _value) {
                    m_ESP_Eingr_HR_Raw = _value;
                }
                bool getESP_Eingr_HR_Raw() const {
                    return m_ESP_Eingr_HR_Raw;
                }
                void setESP_Eingr_VL_Raw(const bool _value) {
                    m_ESP_Eingr_VL_Raw = _value;
                }
                bool getESP_Eingr_VL_Raw() const {
                    return m_ESP_Eingr_VL_Raw;
                }
                void setESP_Eingr_VR_Raw(const bool _value) {
                    m_ESP_Eingr_VR_Raw = _value;
                }
                bool getESP_Eingr_VR_Raw() const {
                    return m_ESP_Eingr_VR_Raw;
                }
                void setESP_Laengsbeschl_Raw(const uint16_t _value) {
                    m_ESP_Laengsbeschl_Raw = _value;
                }
                uint16_t getESP_Laengsbeschl_Raw() const {
                    return m_ESP_Laengsbeschl_Raw;
                }
                void setESP_Laengsbeschl_SignalState(const uint64_t _value) {
                    m_ESP_Laengsbeschl_SignalState = _value;
                }
                uint64_t getESP_Laengsbeschl_SignalState() const {
                    return m_ESP_Laengsbeschl_SignalState;
                }
                void setESP_Gierrate_Raw(const uint16_t _value) {
                    m_ESP_Gierrate_Raw = _value;
                }
                uint16_t getESP_Gierrate_Raw() const {
                    return m_ESP_Gierrate_Raw;
                }
                void setESP_Gierrate_SignalState(const uint64_t _value) {
                    m_ESP_Gierrate_SignalState = _value;
                }
                uint64_t getESP_Gierrate_SignalState() const {
                    return m_ESP_Gierrate_SignalState;
                }
                void setESP_VZ_Gierrate_Raw(const bool _value) {
                    m_ESP_VZ_Gierrate_Raw = _value;
                }
                bool getESP_VZ_Gierrate_Raw() const {
                    return m_ESP_VZ_Gierrate_Raw;
                }
                void setESP_Notbremsanzeige_Raw(const bool _value) {
                    m_ESP_Notbremsanzeige_Raw = _value;
                }
                bool getESP_Notbremsanzeige_Raw() const {
                    return m_ESP_Notbremsanzeige_Raw;
                }
                void setESP_Fahrer_bremst_Raw(const bool _value) {
                    m_ESP_Fahrer_bremst_Raw = _value;
                }
                bool getESP_Fahrer_bremst_Raw() const {
                    return m_ESP_Fahrer_bremst_Raw;
                }
                void setPduState(const uint64_t _value) {
                    m_PduState = _value;
                }
                uint64_t getPduState() const {
                    return m_PduState;
                }


        bool m_ESP_QBit_Gierrate_Raw;
        bool m_ESP_QBit_Laengsbeschl_Raw;
        bool m_ESP_QBit_Querb_Raw;
        uint8_t m_ESP_Querbeschleunigung_Raw;
        uint64_t m_ESP_Querbeschleunigung_SignalState;
        bool m_ESP_Eingr_HL_Raw;
        bool m_ESP_Eingr_HR_Raw;
        bool m_ESP_Eingr_VL_Raw;
        bool m_ESP_Eingr_VR_Raw;
        uint16_t m_ESP_Laengsbeschl_Raw;
        uint64_t m_ESP_Laengsbeschl_SignalState;
        uint16_t m_ESP_Gierrate_Raw;
        uint64_t m_ESP_Gierrate_SignalState;
        bool m_ESP_VZ_Gierrate_Raw;
        bool m_ESP_Notbremsanzeige_Raw;
        bool m_ESP_Fahrer_bremst_Raw;
        uint64_t m_PduState;
    private:
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const asi::sid::v2xstack::cstyle::ESC50Struct& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, asi::sid::v2xstack::cstyle::ESC50Struct &val);
    };

} // cstyle
}//namespace asi
}//namespace sid
}//namespace v2xstack

#endif// ASI_SID_V2XSTACK_ESC50STRUCT_CSTYLE_HXX
