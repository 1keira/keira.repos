/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef ASI_SID_LHWAPP_PSD05STRUCT_CSTYLE_HXX
#define ASI_SID_LHWAPP_PSD05STRUCT_CSTYLE_HXX

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
struct PSD05Struct;
}
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const asi::sid::lhwapp::cstyle::PSD05Struct& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, asi::sid::lhwapp::cstyle::PSD05Struct &val);
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
    \brief struct lhwapp::PSD05Struct.
    */
    struct PROXY_EXPORT PSD05Struct
    {
        public:
            PSD05Struct()
            : m_PSD_Pos_Segment_ID_Raw()
            , m_PSD_Pos_Segment_ID_SignalState()
            , m_PSD_Pos_Segmentlaenge_Raw()
            , m_PSD_Pos_Standort_Eindeutig_Raw()
            , m_PSD_Pos_Fehler_Laengsrichtung_Raw()
            , m_PSD_Attribut_1_ID_Raw()
            , m_PSD_Attribut_1_ID_SignalState()
            , m_PSD_Attribut_1_Wert_Raw()
            , m_PSD_Attribut_2_ID_Raw()
            , m_PSD_Attribut_2_ID_SignalState()
            , m_PSD_Attribut_2_Wert_Raw()
            , m_PduState()
            { }

            PSD05Struct (const PSD05Struct& other)
            : m_PSD_Pos_Segment_ID_Raw()
            , m_PSD_Pos_Segment_ID_SignalState()
            , m_PSD_Pos_Segmentlaenge_Raw()
            , m_PSD_Pos_Standort_Eindeutig_Raw()
            , m_PSD_Pos_Fehler_Laengsrichtung_Raw()
            , m_PSD_Attribut_1_ID_Raw()
            , m_PSD_Attribut_1_ID_SignalState()
            , m_PSD_Attribut_1_Wert_Raw()
            , m_PSD_Attribut_2_ID_Raw()
            , m_PSD_Attribut_2_ID_SignalState()
            , m_PSD_Attribut_2_Wert_Raw()
            , m_PduState()
            {
              *this = other;
            }

            ~PSD05Struct () {
            }
            bool operator==(const PSD05Struct& rhs) const {
                bool equal = true;
                if (m_PSD_Pos_Segment_ID_Raw != rhs.m_PSD_Pos_Segment_ID_Raw)
                    equal = false;
                if (m_PSD_Pos_Segment_ID_SignalState != rhs.m_PSD_Pos_Segment_ID_SignalState)
                    equal = false;
                if (m_PSD_Pos_Segmentlaenge_Raw != rhs.m_PSD_Pos_Segmentlaenge_Raw)
                    equal = false;
                if (m_PSD_Pos_Standort_Eindeutig_Raw != rhs.m_PSD_Pos_Standort_Eindeutig_Raw)
                    equal = false;
                if (m_PSD_Pos_Fehler_Laengsrichtung_Raw != rhs.m_PSD_Pos_Fehler_Laengsrichtung_Raw)
                    equal = false;
                if (m_PSD_Attribut_1_ID_Raw != rhs.m_PSD_Attribut_1_ID_Raw)
                    equal = false;
                if (m_PSD_Attribut_1_ID_SignalState != rhs.m_PSD_Attribut_1_ID_SignalState)
                    equal = false;
                if (m_PSD_Attribut_1_Wert_Raw != rhs.m_PSD_Attribut_1_Wert_Raw)
                    equal = false;
                if (m_PSD_Attribut_2_ID_Raw != rhs.m_PSD_Attribut_2_ID_Raw)
                    equal = false;
                if (m_PSD_Attribut_2_ID_SignalState != rhs.m_PSD_Attribut_2_ID_SignalState)
                    equal = false;
                if (m_PSD_Attribut_2_Wert_Raw != rhs.m_PSD_Attribut_2_Wert_Raw)
                    equal = false;
                if (m_PduState != rhs.m_PduState)
                    equal = false;
                return equal;
            }
            bool operator!=(const PSD05Struct& rhs) const {
                return !operator==(rhs);
            }

            PSD05Struct& operator = (const PSD05Struct& src) {
                if (this == &src) return *this;
                m_PSD_Pos_Segment_ID_Raw = src.m_PSD_Pos_Segment_ID_Raw;
                m_PSD_Pos_Segment_ID_SignalState = src.m_PSD_Pos_Segment_ID_SignalState;
                m_PSD_Pos_Segmentlaenge_Raw = src.m_PSD_Pos_Segmentlaenge_Raw;
                m_PSD_Pos_Standort_Eindeutig_Raw = src.m_PSD_Pos_Standort_Eindeutig_Raw;
                m_PSD_Pos_Fehler_Laengsrichtung_Raw = src.m_PSD_Pos_Fehler_Laengsrichtung_Raw;
                m_PSD_Attribut_1_ID_Raw = src.m_PSD_Attribut_1_ID_Raw;
                m_PSD_Attribut_1_ID_SignalState = src.m_PSD_Attribut_1_ID_SignalState;
                m_PSD_Attribut_1_Wert_Raw = src.m_PSD_Attribut_1_Wert_Raw;
                m_PSD_Attribut_2_ID_Raw = src.m_PSD_Attribut_2_ID_Raw;
                m_PSD_Attribut_2_ID_SignalState = src.m_PSD_Attribut_2_ID_SignalState;
                m_PSD_Attribut_2_Wert_Raw = src.m_PSD_Attribut_2_Wert_Raw;
                m_PduState = src.m_PduState;
                return *this;
            }

                void setPSD_Pos_Segment_ID_Raw(const uint8_t _value) {
                    m_PSD_Pos_Segment_ID_Raw = _value;
                }
                uint8_t getPSD_Pos_Segment_ID_Raw() const {
                    return m_PSD_Pos_Segment_ID_Raw;
                }
                void setPSD_Pos_Segment_ID_SignalState(const uint64_t _value) {
                    m_PSD_Pos_Segment_ID_SignalState = _value;
                }
                uint64_t getPSD_Pos_Segment_ID_SignalState() const {
                    return m_PSD_Pos_Segment_ID_SignalState;
                }
                void setPSD_Pos_Segmentlaenge_Raw(const uint8_t _value) {
                    m_PSD_Pos_Segmentlaenge_Raw = _value;
                }
                uint8_t getPSD_Pos_Segmentlaenge_Raw() const {
                    return m_PSD_Pos_Segmentlaenge_Raw;
                }
                void setPSD_Pos_Standort_Eindeutig_Raw(const bool _value) {
                    m_PSD_Pos_Standort_Eindeutig_Raw = _value;
                }
                bool getPSD_Pos_Standort_Eindeutig_Raw() const {
                    return m_PSD_Pos_Standort_Eindeutig_Raw;
                }
                void setPSD_Pos_Fehler_Laengsrichtung_Raw(const uint8_t _value) {
                    m_PSD_Pos_Fehler_Laengsrichtung_Raw = _value;
                }
                uint8_t getPSD_Pos_Fehler_Laengsrichtung_Raw() const {
                    return m_PSD_Pos_Fehler_Laengsrichtung_Raw;
                }
                void setPSD_Attribut_1_ID_Raw(const uint8_t _value) {
                    m_PSD_Attribut_1_ID_Raw = _value;
                }
                uint8_t getPSD_Attribut_1_ID_Raw() const {
                    return m_PSD_Attribut_1_ID_Raw;
                }
                void setPSD_Attribut_1_ID_SignalState(const uint64_t _value) {
                    m_PSD_Attribut_1_ID_SignalState = _value;
                }
                uint64_t getPSD_Attribut_1_ID_SignalState() const {
                    return m_PSD_Attribut_1_ID_SignalState;
                }
                void setPSD_Attribut_1_Wert_Raw(const uint8_t _value) {
                    m_PSD_Attribut_1_Wert_Raw = _value;
                }
                uint8_t getPSD_Attribut_1_Wert_Raw() const {
                    return m_PSD_Attribut_1_Wert_Raw;
                }
                void setPSD_Attribut_2_ID_Raw(const uint8_t _value) {
                    m_PSD_Attribut_2_ID_Raw = _value;
                }
                uint8_t getPSD_Attribut_2_ID_Raw() const {
                    return m_PSD_Attribut_2_ID_Raw;
                }
                void setPSD_Attribut_2_ID_SignalState(const uint64_t _value) {
                    m_PSD_Attribut_2_ID_SignalState = _value;
                }
                uint64_t getPSD_Attribut_2_ID_SignalState() const {
                    return m_PSD_Attribut_2_ID_SignalState;
                }
                void setPSD_Attribut_2_Wert_Raw(const uint8_t _value) {
                    m_PSD_Attribut_2_Wert_Raw = _value;
                }
                uint8_t getPSD_Attribut_2_Wert_Raw() const {
                    return m_PSD_Attribut_2_Wert_Raw;
                }
                void setPduState(const uint64_t _value) {
                    m_PduState = _value;
                }
                uint64_t getPduState() const {
                    return m_PduState;
                }


        uint8_t m_PSD_Pos_Segment_ID_Raw;
        uint64_t m_PSD_Pos_Segment_ID_SignalState;
        uint8_t m_PSD_Pos_Segmentlaenge_Raw;
        bool m_PSD_Pos_Standort_Eindeutig_Raw;
        uint8_t m_PSD_Pos_Fehler_Laengsrichtung_Raw;
        uint8_t m_PSD_Attribut_1_ID_Raw;
        uint64_t m_PSD_Attribut_1_ID_SignalState;
        uint8_t m_PSD_Attribut_1_Wert_Raw;
        uint8_t m_PSD_Attribut_2_ID_Raw;
        uint64_t m_PSD_Attribut_2_ID_SignalState;
        uint8_t m_PSD_Attribut_2_Wert_Raw;
        uint64_t m_PduState;
    private:
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const asi::sid::lhwapp::cstyle::PSD05Struct& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, asi::sid::lhwapp::cstyle::PSD05Struct &val);
    };

} // cstyle
}//namespace asi
}//namespace sid
}//namespace lhwapp

#endif// ASI_SID_LHWAPP_PSD05STRUCT_CSTYLE_HXX
