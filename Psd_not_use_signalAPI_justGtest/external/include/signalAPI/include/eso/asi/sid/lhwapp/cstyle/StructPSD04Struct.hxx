/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef ASI_SID_LHWAPP_PSD04STRUCT_CSTYLE_HXX
#define ASI_SID_LHWAPP_PSD04STRUCT_CSTYLE_HXX

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
struct PSD04Struct;
}
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const asi::sid::lhwapp::cstyle::PSD04Struct& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, asi::sid::lhwapp::cstyle::PSD04Struct &val);
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
    \brief struct lhwapp::PSD04Struct.
    */
    struct PROXY_EXPORT PSD04Struct
    {
        public:
            PSD04Struct()
            : m_PSD_Endkruemmung_Vorz_Raw()
            , m_PSD_wahrscheinlichster_Pfad_Raw()
            , m_PSD_Geradester_Pfad_Raw()
            , m_PSD_Segment_Komplett_Raw()
            , m_PSD_Anfangskruemmung_Raw()
            , m_PSD_Anfangskruemmung_SignalState()
            , m_PSD_Anfangskruemmung_Vorz_Raw()
            , m_PSD_Abzweigerichtung_Raw()
            , m_PSD_Abzweigewinkel_Raw()
            , m_PSD_Segment_ID_Raw()
            , m_PSD_Segment_ID_SignalState()
            , m_PSD_Vorgaenger_Segment_ID_Raw()
            , m_PSD_Vorgaenger_Segment_ID_SignalState()
            , m_PSD_Segmentlaenge_Raw()
            , m_PSD_Strassenkategorie_Raw()
            , m_PSD_Endkruemmung_Raw()
            , m_PSD_Endkruemmung_SignalState()
            , m_PduState()
            { }

            PSD04Struct (const PSD04Struct& other)
            : m_PSD_Endkruemmung_Vorz_Raw()
            , m_PSD_wahrscheinlichster_Pfad_Raw()
            , m_PSD_Geradester_Pfad_Raw()
            , m_PSD_Segment_Komplett_Raw()
            , m_PSD_Anfangskruemmung_Raw()
            , m_PSD_Anfangskruemmung_SignalState()
            , m_PSD_Anfangskruemmung_Vorz_Raw()
            , m_PSD_Abzweigerichtung_Raw()
            , m_PSD_Abzweigewinkel_Raw()
            , m_PSD_Segment_ID_Raw()
            , m_PSD_Segment_ID_SignalState()
            , m_PSD_Vorgaenger_Segment_ID_Raw()
            , m_PSD_Vorgaenger_Segment_ID_SignalState()
            , m_PSD_Segmentlaenge_Raw()
            , m_PSD_Strassenkategorie_Raw()
            , m_PSD_Endkruemmung_Raw()
            , m_PSD_Endkruemmung_SignalState()
            , m_PduState()
            {
              *this = other;
            }

            ~PSD04Struct () {
            }
            bool operator==(const PSD04Struct& rhs) const {
                bool equal = true;
                if (m_PSD_Endkruemmung_Vorz_Raw != rhs.m_PSD_Endkruemmung_Vorz_Raw)
                    equal = false;
                if (m_PSD_wahrscheinlichster_Pfad_Raw != rhs.m_PSD_wahrscheinlichster_Pfad_Raw)
                    equal = false;
                if (m_PSD_Geradester_Pfad_Raw != rhs.m_PSD_Geradester_Pfad_Raw)
                    equal = false;
                if (m_PSD_Segment_Komplett_Raw != rhs.m_PSD_Segment_Komplett_Raw)
                    equal = false;
                if (m_PSD_Anfangskruemmung_Raw != rhs.m_PSD_Anfangskruemmung_Raw)
                    equal = false;
                if (m_PSD_Anfangskruemmung_SignalState != rhs.m_PSD_Anfangskruemmung_SignalState)
                    equal = false;
                if (m_PSD_Anfangskruemmung_Vorz_Raw != rhs.m_PSD_Anfangskruemmung_Vorz_Raw)
                    equal = false;
                if (m_PSD_Abzweigerichtung_Raw != rhs.m_PSD_Abzweigerichtung_Raw)
                    equal = false;
                if (m_PSD_Abzweigewinkel_Raw != rhs.m_PSD_Abzweigewinkel_Raw)
                    equal = false;
                if (m_PSD_Segment_ID_Raw != rhs.m_PSD_Segment_ID_Raw)
                    equal = false;
                if (m_PSD_Segment_ID_SignalState != rhs.m_PSD_Segment_ID_SignalState)
                    equal = false;
                if (m_PSD_Vorgaenger_Segment_ID_Raw != rhs.m_PSD_Vorgaenger_Segment_ID_Raw)
                    equal = false;
                if (m_PSD_Vorgaenger_Segment_ID_SignalState != rhs.m_PSD_Vorgaenger_Segment_ID_SignalState)
                    equal = false;
                if (m_PSD_Segmentlaenge_Raw != rhs.m_PSD_Segmentlaenge_Raw)
                    equal = false;
                if (m_PSD_Strassenkategorie_Raw != rhs.m_PSD_Strassenkategorie_Raw)
                    equal = false;
                if (m_PSD_Endkruemmung_Raw != rhs.m_PSD_Endkruemmung_Raw)
                    equal = false;
                if (m_PSD_Endkruemmung_SignalState != rhs.m_PSD_Endkruemmung_SignalState)
                    equal = false;
                if (m_PduState != rhs.m_PduState)
                    equal = false;
                return equal;
            }
            bool operator!=(const PSD04Struct& rhs) const {
                return !operator==(rhs);
            }

            PSD04Struct& operator = (const PSD04Struct& src) {
                if (this == &src) return *this;
                m_PSD_Endkruemmung_Vorz_Raw = src.m_PSD_Endkruemmung_Vorz_Raw;
                m_PSD_wahrscheinlichster_Pfad_Raw = src.m_PSD_wahrscheinlichster_Pfad_Raw;
                m_PSD_Geradester_Pfad_Raw = src.m_PSD_Geradester_Pfad_Raw;
                m_PSD_Segment_Komplett_Raw = src.m_PSD_Segment_Komplett_Raw;
                m_PSD_Anfangskruemmung_Raw = src.m_PSD_Anfangskruemmung_Raw;
                m_PSD_Anfangskruemmung_SignalState = src.m_PSD_Anfangskruemmung_SignalState;
                m_PSD_Anfangskruemmung_Vorz_Raw = src.m_PSD_Anfangskruemmung_Vorz_Raw;
                m_PSD_Abzweigerichtung_Raw = src.m_PSD_Abzweigerichtung_Raw;
                m_PSD_Abzweigewinkel_Raw = src.m_PSD_Abzweigewinkel_Raw;
                m_PSD_Segment_ID_Raw = src.m_PSD_Segment_ID_Raw;
                m_PSD_Segment_ID_SignalState = src.m_PSD_Segment_ID_SignalState;
                m_PSD_Vorgaenger_Segment_ID_Raw = src.m_PSD_Vorgaenger_Segment_ID_Raw;
                m_PSD_Vorgaenger_Segment_ID_SignalState = src.m_PSD_Vorgaenger_Segment_ID_SignalState;
                m_PSD_Segmentlaenge_Raw = src.m_PSD_Segmentlaenge_Raw;
                m_PSD_Strassenkategorie_Raw = src.m_PSD_Strassenkategorie_Raw;
                m_PSD_Endkruemmung_Raw = src.m_PSD_Endkruemmung_Raw;
                m_PSD_Endkruemmung_SignalState = src.m_PSD_Endkruemmung_SignalState;
                m_PduState = src.m_PduState;
                return *this;
            }

                void setPSD_Endkruemmung_Vorz_Raw(const bool _value) {
                    m_PSD_Endkruemmung_Vorz_Raw = _value;
                }
                bool getPSD_Endkruemmung_Vorz_Raw() const {
                    return m_PSD_Endkruemmung_Vorz_Raw;
                }
                void setPSD_wahrscheinlichster_Pfad_Raw(const bool _value) {
                    m_PSD_wahrscheinlichster_Pfad_Raw = _value;
                }
                bool getPSD_wahrscheinlichster_Pfad_Raw() const {
                    return m_PSD_wahrscheinlichster_Pfad_Raw;
                }
                void setPSD_Geradester_Pfad_Raw(const bool _value) {
                    m_PSD_Geradester_Pfad_Raw = _value;
                }
                bool getPSD_Geradester_Pfad_Raw() const {
                    return m_PSD_Geradester_Pfad_Raw;
                }
                void setPSD_Segment_Komplett_Raw(const bool _value) {
                    m_PSD_Segment_Komplett_Raw = _value;
                }
                bool getPSD_Segment_Komplett_Raw() const {
                    return m_PSD_Segment_Komplett_Raw;
                }
                void setPSD_Anfangskruemmung_Raw(const uint8_t _value) {
                    m_PSD_Anfangskruemmung_Raw = _value;
                }
                uint8_t getPSD_Anfangskruemmung_Raw() const {
                    return m_PSD_Anfangskruemmung_Raw;
                }
                void setPSD_Anfangskruemmung_SignalState(const uint64_t _value) {
                    m_PSD_Anfangskruemmung_SignalState = _value;
                }
                uint64_t getPSD_Anfangskruemmung_SignalState() const {
                    return m_PSD_Anfangskruemmung_SignalState;
                }
                void setPSD_Anfangskruemmung_Vorz_Raw(const bool _value) {
                    m_PSD_Anfangskruemmung_Vorz_Raw = _value;
                }
                bool getPSD_Anfangskruemmung_Vorz_Raw() const {
                    return m_PSD_Anfangskruemmung_Vorz_Raw;
                }
                void setPSD_Abzweigerichtung_Raw(const bool _value) {
                    m_PSD_Abzweigerichtung_Raw = _value;
                }
                bool getPSD_Abzweigerichtung_Raw() const {
                    return m_PSD_Abzweigerichtung_Raw;
                }
                void setPSD_Abzweigewinkel_Raw(const uint8_t _value) {
                    m_PSD_Abzweigewinkel_Raw = _value;
                }
                uint8_t getPSD_Abzweigewinkel_Raw() const {
                    return m_PSD_Abzweigewinkel_Raw;
                }
                void setPSD_Segment_ID_Raw(const uint8_t _value) {
                    m_PSD_Segment_ID_Raw = _value;
                }
                uint8_t getPSD_Segment_ID_Raw() const {
                    return m_PSD_Segment_ID_Raw;
                }
                void setPSD_Segment_ID_SignalState(const uint64_t _value) {
                    m_PSD_Segment_ID_SignalState = _value;
                }
                uint64_t getPSD_Segment_ID_SignalState() const {
                    return m_PSD_Segment_ID_SignalState;
                }
                void setPSD_Vorgaenger_Segment_ID_Raw(const uint8_t _value) {
                    m_PSD_Vorgaenger_Segment_ID_Raw = _value;
                }
                uint8_t getPSD_Vorgaenger_Segment_ID_Raw() const {
                    return m_PSD_Vorgaenger_Segment_ID_Raw;
                }
                void setPSD_Vorgaenger_Segment_ID_SignalState(const uint64_t _value) {
                    m_PSD_Vorgaenger_Segment_ID_SignalState = _value;
                }
                uint64_t getPSD_Vorgaenger_Segment_ID_SignalState() const {
                    return m_PSD_Vorgaenger_Segment_ID_SignalState;
                }
                void setPSD_Segmentlaenge_Raw(const uint8_t _value) {
                    m_PSD_Segmentlaenge_Raw = _value;
                }
                uint8_t getPSD_Segmentlaenge_Raw() const {
                    return m_PSD_Segmentlaenge_Raw;
                }
                void setPSD_Strassenkategorie_Raw(const uint8_t _value) {
                    m_PSD_Strassenkategorie_Raw = _value;
                }
                uint8_t getPSD_Strassenkategorie_Raw() const {
                    return m_PSD_Strassenkategorie_Raw;
                }
                void setPSD_Endkruemmung_Raw(const uint8_t _value) {
                    m_PSD_Endkruemmung_Raw = _value;
                }
                uint8_t getPSD_Endkruemmung_Raw() const {
                    return m_PSD_Endkruemmung_Raw;
                }
                void setPSD_Endkruemmung_SignalState(const uint64_t _value) {
                    m_PSD_Endkruemmung_SignalState = _value;
                }
                uint64_t getPSD_Endkruemmung_SignalState() const {
                    return m_PSD_Endkruemmung_SignalState;
                }
                void setPduState(const uint64_t _value) {
                    m_PduState = _value;
                }
                uint64_t getPduState() const {
                    return m_PduState;
                }


        bool m_PSD_Endkruemmung_Vorz_Raw;
        bool m_PSD_wahrscheinlichster_Pfad_Raw;
        bool m_PSD_Geradester_Pfad_Raw;
        bool m_PSD_Segment_Komplett_Raw;
        uint8_t m_PSD_Anfangskruemmung_Raw;
        uint64_t m_PSD_Anfangskruemmung_SignalState;
        bool m_PSD_Anfangskruemmung_Vorz_Raw;
        bool m_PSD_Abzweigerichtung_Raw;
        uint8_t m_PSD_Abzweigewinkel_Raw;
        uint8_t m_PSD_Segment_ID_Raw;
        uint64_t m_PSD_Segment_ID_SignalState;
        uint8_t m_PSD_Vorgaenger_Segment_ID_Raw;
        uint64_t m_PSD_Vorgaenger_Segment_ID_SignalState;
        uint8_t m_PSD_Segmentlaenge_Raw;
        uint8_t m_PSD_Strassenkategorie_Raw;
        uint8_t m_PSD_Endkruemmung_Raw;
        uint64_t m_PSD_Endkruemmung_SignalState;
        uint64_t m_PduState;
    private:
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const asi::sid::lhwapp::cstyle::PSD04Struct& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, asi::sid::lhwapp::cstyle::PSD04Struct &val);
    };

} // cstyle
}//namespace asi
}//namespace sid
}//namespace lhwapp

#endif// ASI_SID_LHWAPP_PSD04STRUCT_CSTYLE_HXX
