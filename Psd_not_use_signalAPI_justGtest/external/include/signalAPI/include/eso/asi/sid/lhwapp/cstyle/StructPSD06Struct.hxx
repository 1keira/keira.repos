/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef ASI_SID_LHWAPP_PSD06STRUCT_CSTYLE_HXX
#define ASI_SID_LHWAPP_PSD06STRUCT_CSTYLE_HXX

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
struct PSD06Struct;
}
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const asi::sid::lhwapp::cstyle::PSD06Struct& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, asi::sid::lhwapp::cstyle::PSD06Struct &val);
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
    \brief struct lhwapp::PSD06Struct.
    */
    struct PROXY_EXPORT PSD06Struct
    {
        public:
            PSD06Struct()
            : m_PSD_06_Mux_Raw()
            , m_PSD_Attribut_5_ID_Raw()
            , m_PSD_Attribut_5_ID_SignalState()
            , m_PSD_Attribut_3_Wert_Raw()
            , m_PSD_Attribut_5_Wert_Raw()
            , m_PSD_Attribut_4_ID_Raw()
            , m_PSD_Attribut_4_ID_SignalState()
            , m_PSD_Attribut_4_Wert_Raw()
            , m_PSD_Attribut_Segment_ID_Raw()
            , m_PSD_Attribut_Segment_ID_SignalState()
            , m_PSD_Attribut_3_ID_Raw()
            , m_PSD_Attribut_3_ID_SignalState()
            , m_PduState()
            { }

            PSD06Struct (const PSD06Struct& other)
            : m_PSD_06_Mux_Raw()
            , m_PSD_Attribut_5_ID_Raw()
            , m_PSD_Attribut_5_ID_SignalState()
            , m_PSD_Attribut_3_Wert_Raw()
            , m_PSD_Attribut_5_Wert_Raw()
            , m_PSD_Attribut_4_ID_Raw()
            , m_PSD_Attribut_4_ID_SignalState()
            , m_PSD_Attribut_4_Wert_Raw()
            , m_PSD_Attribut_Segment_ID_Raw()
            , m_PSD_Attribut_Segment_ID_SignalState()
            , m_PSD_Attribut_3_ID_Raw()
            , m_PSD_Attribut_3_ID_SignalState()
            , m_PduState()
            {
              *this = other;
            }

            ~PSD06Struct () {
            }
            bool operator==(const PSD06Struct& rhs) const {
                bool equal = true;
                if (m_PSD_06_Mux_Raw != rhs.m_PSD_06_Mux_Raw)
                    equal = false;
                if (m_PSD_Attribut_5_ID_Raw != rhs.m_PSD_Attribut_5_ID_Raw)
                    equal = false;
                if (m_PSD_Attribut_5_ID_SignalState != rhs.m_PSD_Attribut_5_ID_SignalState)
                    equal = false;
                if (m_PSD_Attribut_3_Wert_Raw != rhs.m_PSD_Attribut_3_Wert_Raw)
                    equal = false;
                if (m_PSD_Attribut_5_Wert_Raw != rhs.m_PSD_Attribut_5_Wert_Raw)
                    equal = false;
                if (m_PSD_Attribut_4_ID_Raw != rhs.m_PSD_Attribut_4_ID_Raw)
                    equal = false;
                if (m_PSD_Attribut_4_ID_SignalState != rhs.m_PSD_Attribut_4_ID_SignalState)
                    equal = false;
                if (m_PSD_Attribut_4_Wert_Raw != rhs.m_PSD_Attribut_4_Wert_Raw)
                    equal = false;
                if (m_PSD_Attribut_Segment_ID_Raw != rhs.m_PSD_Attribut_Segment_ID_Raw)
                    equal = false;
                if (m_PSD_Attribut_Segment_ID_SignalState != rhs.m_PSD_Attribut_Segment_ID_SignalState)
                    equal = false;
                if (m_PSD_Attribut_3_ID_Raw != rhs.m_PSD_Attribut_3_ID_Raw)
                    equal = false;
                if (m_PSD_Attribut_3_ID_SignalState != rhs.m_PSD_Attribut_3_ID_SignalState)
                    equal = false;
                if (m_PduState != rhs.m_PduState)
                    equal = false;
                return equal;
            }
            bool operator!=(const PSD06Struct& rhs) const {
                return !operator==(rhs);
            }

            PSD06Struct& operator = (const PSD06Struct& src) {
                if (this == &src) return *this;
                m_PSD_06_Mux_Raw = src.m_PSD_06_Mux_Raw;
                m_PSD_Attribut_5_ID_Raw = src.m_PSD_Attribut_5_ID_Raw;
                m_PSD_Attribut_5_ID_SignalState = src.m_PSD_Attribut_5_ID_SignalState;
                m_PSD_Attribut_3_Wert_Raw = src.m_PSD_Attribut_3_Wert_Raw;
                m_PSD_Attribut_5_Wert_Raw = src.m_PSD_Attribut_5_Wert_Raw;
                m_PSD_Attribut_4_ID_Raw = src.m_PSD_Attribut_4_ID_Raw;
                m_PSD_Attribut_4_ID_SignalState = src.m_PSD_Attribut_4_ID_SignalState;
                m_PSD_Attribut_4_Wert_Raw = src.m_PSD_Attribut_4_Wert_Raw;
                m_PSD_Attribut_Segment_ID_Raw = src.m_PSD_Attribut_Segment_ID_Raw;
                m_PSD_Attribut_Segment_ID_SignalState = src.m_PSD_Attribut_Segment_ID_SignalState;
                m_PSD_Attribut_3_ID_Raw = src.m_PSD_Attribut_3_ID_Raw;
                m_PSD_Attribut_3_ID_SignalState = src.m_PSD_Attribut_3_ID_SignalState;
                m_PduState = src.m_PduState;
                return *this;
            }

                void setPSD_06_Mux_Raw(const uint8_t _value) {
                    m_PSD_06_Mux_Raw = _value;
                }
                uint8_t getPSD_06_Mux_Raw() const {
                    return m_PSD_06_Mux_Raw;
                }
                void setPSD_Attribut_5_ID_Raw(const uint8_t _value) {
                    m_PSD_Attribut_5_ID_Raw = _value;
                }
                uint8_t getPSD_Attribut_5_ID_Raw() const {
                    return m_PSD_Attribut_5_ID_Raw;
                }
                void setPSD_Attribut_5_ID_SignalState(const uint64_t _value) {
                    m_PSD_Attribut_5_ID_SignalState = _value;
                }
                uint64_t getPSD_Attribut_5_ID_SignalState() const {
                    return m_PSD_Attribut_5_ID_SignalState;
                }
                void setPSD_Attribut_3_Wert_Raw(const uint8_t _value) {
                    m_PSD_Attribut_3_Wert_Raw = _value;
                }
                uint8_t getPSD_Attribut_3_Wert_Raw() const {
                    return m_PSD_Attribut_3_Wert_Raw;
                }
                void setPSD_Attribut_5_Wert_Raw(const uint8_t _value) {
                    m_PSD_Attribut_5_Wert_Raw = _value;
                }
                uint8_t getPSD_Attribut_5_Wert_Raw() const {
                    return m_PSD_Attribut_5_Wert_Raw;
                }
                void setPSD_Attribut_4_ID_Raw(const uint8_t _value) {
                    m_PSD_Attribut_4_ID_Raw = _value;
                }
                uint8_t getPSD_Attribut_4_ID_Raw() const {
                    return m_PSD_Attribut_4_ID_Raw;
                }
                void setPSD_Attribut_4_ID_SignalState(const uint64_t _value) {
                    m_PSD_Attribut_4_ID_SignalState = _value;
                }
                uint64_t getPSD_Attribut_4_ID_SignalState() const {
                    return m_PSD_Attribut_4_ID_SignalState;
                }
                void setPSD_Attribut_4_Wert_Raw(const uint8_t _value) {
                    m_PSD_Attribut_4_Wert_Raw = _value;
                }
                uint8_t getPSD_Attribut_4_Wert_Raw() const {
                    return m_PSD_Attribut_4_Wert_Raw;
                }
                void setPSD_Attribut_Segment_ID_Raw(const uint8_t _value) {
                    m_PSD_Attribut_Segment_ID_Raw = _value;
                }
                uint8_t getPSD_Attribut_Segment_ID_Raw() const {
                    return m_PSD_Attribut_Segment_ID_Raw;
                }
                void setPSD_Attribut_Segment_ID_SignalState(const uint64_t _value) {
                    m_PSD_Attribut_Segment_ID_SignalState = _value;
                }
                uint64_t getPSD_Attribut_Segment_ID_SignalState() const {
                    return m_PSD_Attribut_Segment_ID_SignalState;
                }
                void setPSD_Attribut_3_ID_Raw(const uint8_t _value) {
                    m_PSD_Attribut_3_ID_Raw = _value;
                }
                uint8_t getPSD_Attribut_3_ID_Raw() const {
                    return m_PSD_Attribut_3_ID_Raw;
                }
                void setPSD_Attribut_3_ID_SignalState(const uint64_t _value) {
                    m_PSD_Attribut_3_ID_SignalState = _value;
                }
                uint64_t getPSD_Attribut_3_ID_SignalState() const {
                    return m_PSD_Attribut_3_ID_SignalState;
                }
                void setPduState(const uint64_t _value) {
                    m_PduState = _value;
                }
                uint64_t getPduState() const {
                    return m_PduState;
                }


        uint8_t m_PSD_06_Mux_Raw;
        uint8_t m_PSD_Attribut_5_ID_Raw;
        uint64_t m_PSD_Attribut_5_ID_SignalState;
        uint8_t m_PSD_Attribut_3_Wert_Raw;
        uint8_t m_PSD_Attribut_5_Wert_Raw;
        uint8_t m_PSD_Attribut_4_ID_Raw;
        uint64_t m_PSD_Attribut_4_ID_SignalState;
        uint8_t m_PSD_Attribut_4_Wert_Raw;
        uint8_t m_PSD_Attribut_Segment_ID_Raw;
        uint64_t m_PSD_Attribut_Segment_ID_SignalState;
        uint8_t m_PSD_Attribut_3_ID_Raw;
        uint64_t m_PSD_Attribut_3_ID_SignalState;
        uint64_t m_PduState;
    private:
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const asi::sid::lhwapp::cstyle::PSD06Struct& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, asi::sid::lhwapp::cstyle::PSD06Struct &val);
    };

} // cstyle
}//namespace asi
}//namespace sid
}//namespace lhwapp

#endif// ASI_SID_LHWAPP_PSD06STRUCT_CSTYLE_HXX
