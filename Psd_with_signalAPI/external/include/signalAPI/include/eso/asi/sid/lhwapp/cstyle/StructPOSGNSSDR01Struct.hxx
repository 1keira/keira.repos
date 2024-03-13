/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef ASI_SID_LHWAPP_POSGNSSDR01STRUCT_CSTYLE_HXX
#define ASI_SID_LHWAPP_POSGNSSDR01STRUCT_CSTYLE_HXX

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
struct POSGNSSDR01Struct;
}
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const asi::sid::lhwapp::cstyle::POSGNSSDR01Struct& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, asi::sid::lhwapp::cstyle::POSGNSSDR01Struct &val);
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
    \brief struct lhwapp::POSGNSSDR01Struct.
    */
    struct PROXY_EXPORT POSGNSSDR01Struct
    {
        public:
            POSGNSSDR01Struct()
            : m_POS_GNSS_DR_Breite_Ortung_Raw()
            , m_POS_GNSS_DR_Breite_Ortung_SignalState()
            , m_POS_GNSS_DR_Guete_E_GrH_Ausr_Raw()
            , m_POS_GNSS_DR_Guete_E_GrH_Ausr_SignalState()
            , m_POS_GNSS_DR_Guete_E_GrHalbachse_Raw()
            , m_POS_GNSS_DR_Guete_E_GrHalbachse_SignalState()
            , m_POS_GNSS_DR_Guete_E_KlHalbachse_Raw()
            , m_POS_GNSS_DR_Guete_E_KlHalbachse_SignalState()
            , m_POS_GNSS_DR_Laenge_Ortung_Raw()
            , m_POS_GNSS_DR_Laenge_Ortung_SignalState()
            , m_POS_GNSS_DR_Ausrichtung_Geschw_Raw()
            , m_POS_GNSS_DR_Ausrichtung_Geschw_SignalState()
            , m_POS_GNSS_DR_Guete_Ausricht_Gesch_Raw()
            , m_POS_GNSS_DR_Guete_Ausricht_Gesch_SignalState()
            , m_PduState()
            { }

            POSGNSSDR01Struct (const POSGNSSDR01Struct& other)
            : m_POS_GNSS_DR_Breite_Ortung_Raw()
            , m_POS_GNSS_DR_Breite_Ortung_SignalState()
            , m_POS_GNSS_DR_Guete_E_GrH_Ausr_Raw()
            , m_POS_GNSS_DR_Guete_E_GrH_Ausr_SignalState()
            , m_POS_GNSS_DR_Guete_E_GrHalbachse_Raw()
            , m_POS_GNSS_DR_Guete_E_GrHalbachse_SignalState()
            , m_POS_GNSS_DR_Guete_E_KlHalbachse_Raw()
            , m_POS_GNSS_DR_Guete_E_KlHalbachse_SignalState()
            , m_POS_GNSS_DR_Laenge_Ortung_Raw()
            , m_POS_GNSS_DR_Laenge_Ortung_SignalState()
            , m_POS_GNSS_DR_Ausrichtung_Geschw_Raw()
            , m_POS_GNSS_DR_Ausrichtung_Geschw_SignalState()
            , m_POS_GNSS_DR_Guete_Ausricht_Gesch_Raw()
            , m_POS_GNSS_DR_Guete_Ausricht_Gesch_SignalState()
            , m_PduState()
            {
              *this = other;
            }

            ~POSGNSSDR01Struct () {
            }
            bool operator==(const POSGNSSDR01Struct& rhs) const {
                bool equal = true;
                if (m_POS_GNSS_DR_Breite_Ortung_Raw != rhs.m_POS_GNSS_DR_Breite_Ortung_Raw)
                    equal = false;
                if (m_POS_GNSS_DR_Breite_Ortung_SignalState != rhs.m_POS_GNSS_DR_Breite_Ortung_SignalState)
                    equal = false;
                if (m_POS_GNSS_DR_Guete_E_GrH_Ausr_Raw != rhs.m_POS_GNSS_DR_Guete_E_GrH_Ausr_Raw)
                    equal = false;
                if (m_POS_GNSS_DR_Guete_E_GrH_Ausr_SignalState != rhs.m_POS_GNSS_DR_Guete_E_GrH_Ausr_SignalState)
                    equal = false;
                if (m_POS_GNSS_DR_Guete_E_GrHalbachse_Raw != rhs.m_POS_GNSS_DR_Guete_E_GrHalbachse_Raw)
                    equal = false;
                if (m_POS_GNSS_DR_Guete_E_GrHalbachse_SignalState != rhs.m_POS_GNSS_DR_Guete_E_GrHalbachse_SignalState)
                    equal = false;
                if (m_POS_GNSS_DR_Guete_E_KlHalbachse_Raw != rhs.m_POS_GNSS_DR_Guete_E_KlHalbachse_Raw)
                    equal = false;
                if (m_POS_GNSS_DR_Guete_E_KlHalbachse_SignalState != rhs.m_POS_GNSS_DR_Guete_E_KlHalbachse_SignalState)
                    equal = false;
                if (m_POS_GNSS_DR_Laenge_Ortung_Raw != rhs.m_POS_GNSS_DR_Laenge_Ortung_Raw)
                    equal = false;
                if (m_POS_GNSS_DR_Laenge_Ortung_SignalState != rhs.m_POS_GNSS_DR_Laenge_Ortung_SignalState)
                    equal = false;
                if (m_POS_GNSS_DR_Ausrichtung_Geschw_Raw != rhs.m_POS_GNSS_DR_Ausrichtung_Geschw_Raw)
                    equal = false;
                if (m_POS_GNSS_DR_Ausrichtung_Geschw_SignalState != rhs.m_POS_GNSS_DR_Ausrichtung_Geschw_SignalState)
                    equal = false;
                if (m_POS_GNSS_DR_Guete_Ausricht_Gesch_Raw != rhs.m_POS_GNSS_DR_Guete_Ausricht_Gesch_Raw)
                    equal = false;
                if (m_POS_GNSS_DR_Guete_Ausricht_Gesch_SignalState != rhs.m_POS_GNSS_DR_Guete_Ausricht_Gesch_SignalState)
                    equal = false;
                if (m_PduState != rhs.m_PduState)
                    equal = false;
                return equal;
            }
            bool operator!=(const POSGNSSDR01Struct& rhs) const {
                return !operator==(rhs);
            }

            POSGNSSDR01Struct& operator = (const POSGNSSDR01Struct& src) {
                if (this == &src) return *this;
                m_POS_GNSS_DR_Breite_Ortung_Raw = src.m_POS_GNSS_DR_Breite_Ortung_Raw;
                m_POS_GNSS_DR_Breite_Ortung_SignalState = src.m_POS_GNSS_DR_Breite_Ortung_SignalState;
                m_POS_GNSS_DR_Guete_E_GrH_Ausr_Raw = src.m_POS_GNSS_DR_Guete_E_GrH_Ausr_Raw;
                m_POS_GNSS_DR_Guete_E_GrH_Ausr_SignalState = src.m_POS_GNSS_DR_Guete_E_GrH_Ausr_SignalState;
                m_POS_GNSS_DR_Guete_E_GrHalbachse_Raw = src.m_POS_GNSS_DR_Guete_E_GrHalbachse_Raw;
                m_POS_GNSS_DR_Guete_E_GrHalbachse_SignalState = src.m_POS_GNSS_DR_Guete_E_GrHalbachse_SignalState;
                m_POS_GNSS_DR_Guete_E_KlHalbachse_Raw = src.m_POS_GNSS_DR_Guete_E_KlHalbachse_Raw;
                m_POS_GNSS_DR_Guete_E_KlHalbachse_SignalState = src.m_POS_GNSS_DR_Guete_E_KlHalbachse_SignalState;
                m_POS_GNSS_DR_Laenge_Ortung_Raw = src.m_POS_GNSS_DR_Laenge_Ortung_Raw;
                m_POS_GNSS_DR_Laenge_Ortung_SignalState = src.m_POS_GNSS_DR_Laenge_Ortung_SignalState;
                m_POS_GNSS_DR_Ausrichtung_Geschw_Raw = src.m_POS_GNSS_DR_Ausrichtung_Geschw_Raw;
                m_POS_GNSS_DR_Ausrichtung_Geschw_SignalState = src.m_POS_GNSS_DR_Ausrichtung_Geschw_SignalState;
                m_POS_GNSS_DR_Guete_Ausricht_Gesch_Raw = src.m_POS_GNSS_DR_Guete_Ausricht_Gesch_Raw;
                m_POS_GNSS_DR_Guete_Ausricht_Gesch_SignalState = src.m_POS_GNSS_DR_Guete_Ausricht_Gesch_SignalState;
                m_PduState = src.m_PduState;
                return *this;
            }

                void setPOS_GNSS_DR_Breite_Ortung_Raw(const uint64_t _value) {
                    m_POS_GNSS_DR_Breite_Ortung_Raw = _value;
                }
                uint64_t getPOS_GNSS_DR_Breite_Ortung_Raw() const {
                    return m_POS_GNSS_DR_Breite_Ortung_Raw;
                }
                void setPOS_GNSS_DR_Breite_Ortung_SignalState(const uint64_t _value) {
                    m_POS_GNSS_DR_Breite_Ortung_SignalState = _value;
                }
                uint64_t getPOS_GNSS_DR_Breite_Ortung_SignalState() const {
                    return m_POS_GNSS_DR_Breite_Ortung_SignalState;
                }
                void setPOS_GNSS_DR_Guete_E_GrH_Ausr_Raw(const uint16_t _value) {
                    m_POS_GNSS_DR_Guete_E_GrH_Ausr_Raw = _value;
                }
                uint16_t getPOS_GNSS_DR_Guete_E_GrH_Ausr_Raw() const {
                    return m_POS_GNSS_DR_Guete_E_GrH_Ausr_Raw;
                }
                void setPOS_GNSS_DR_Guete_E_GrH_Ausr_SignalState(const uint64_t _value) {
                    m_POS_GNSS_DR_Guete_E_GrH_Ausr_SignalState = _value;
                }
                uint64_t getPOS_GNSS_DR_Guete_E_GrH_Ausr_SignalState() const {
                    return m_POS_GNSS_DR_Guete_E_GrH_Ausr_SignalState;
                }
                void setPOS_GNSS_DR_Guete_E_GrHalbachse_Raw(const uint16_t _value) {
                    m_POS_GNSS_DR_Guete_E_GrHalbachse_Raw = _value;
                }
                uint16_t getPOS_GNSS_DR_Guete_E_GrHalbachse_Raw() const {
                    return m_POS_GNSS_DR_Guete_E_GrHalbachse_Raw;
                }
                void setPOS_GNSS_DR_Guete_E_GrHalbachse_SignalState(const uint64_t _value) {
                    m_POS_GNSS_DR_Guete_E_GrHalbachse_SignalState = _value;
                }
                uint64_t getPOS_GNSS_DR_Guete_E_GrHalbachse_SignalState() const {
                    return m_POS_GNSS_DR_Guete_E_GrHalbachse_SignalState;
                }
                void setPOS_GNSS_DR_Guete_E_KlHalbachse_Raw(const uint16_t _value) {
                    m_POS_GNSS_DR_Guete_E_KlHalbachse_Raw = _value;
                }
                uint16_t getPOS_GNSS_DR_Guete_E_KlHalbachse_Raw() const {
                    return m_POS_GNSS_DR_Guete_E_KlHalbachse_Raw;
                }
                void setPOS_GNSS_DR_Guete_E_KlHalbachse_SignalState(const uint64_t _value) {
                    m_POS_GNSS_DR_Guete_E_KlHalbachse_SignalState = _value;
                }
                uint64_t getPOS_GNSS_DR_Guete_E_KlHalbachse_SignalState() const {
                    return m_POS_GNSS_DR_Guete_E_KlHalbachse_SignalState;
                }
                void setPOS_GNSS_DR_Laenge_Ortung_Raw(const uint64_t _value) {
                    m_POS_GNSS_DR_Laenge_Ortung_Raw = _value;
                }
                uint64_t getPOS_GNSS_DR_Laenge_Ortung_Raw() const {
                    return m_POS_GNSS_DR_Laenge_Ortung_Raw;
                }
                void setPOS_GNSS_DR_Laenge_Ortung_SignalState(const uint64_t _value) {
                    m_POS_GNSS_DR_Laenge_Ortung_SignalState = _value;
                }
                uint64_t getPOS_GNSS_DR_Laenge_Ortung_SignalState() const {
                    return m_POS_GNSS_DR_Laenge_Ortung_SignalState;
                }
                void setPOS_GNSS_DR_Ausrichtung_Geschw_Raw(const uint16_t _value) {
                    m_POS_GNSS_DR_Ausrichtung_Geschw_Raw = _value;
                }
                uint16_t getPOS_GNSS_DR_Ausrichtung_Geschw_Raw() const {
                    return m_POS_GNSS_DR_Ausrichtung_Geschw_Raw;
                }
                void setPOS_GNSS_DR_Ausrichtung_Geschw_SignalState(const uint64_t _value) {
                    m_POS_GNSS_DR_Ausrichtung_Geschw_SignalState = _value;
                }
                uint64_t getPOS_GNSS_DR_Ausrichtung_Geschw_SignalState() const {
                    return m_POS_GNSS_DR_Ausrichtung_Geschw_SignalState;
                }
                void setPOS_GNSS_DR_Guete_Ausricht_Gesch_Raw(const uint16_t _value) {
                    m_POS_GNSS_DR_Guete_Ausricht_Gesch_Raw = _value;
                }
                uint16_t getPOS_GNSS_DR_Guete_Ausricht_Gesch_Raw() const {
                    return m_POS_GNSS_DR_Guete_Ausricht_Gesch_Raw;
                }
                void setPOS_GNSS_DR_Guete_Ausricht_Gesch_SignalState(const uint64_t _value) {
                    m_POS_GNSS_DR_Guete_Ausricht_Gesch_SignalState = _value;
                }
                uint64_t getPOS_GNSS_DR_Guete_Ausricht_Gesch_SignalState() const {
                    return m_POS_GNSS_DR_Guete_Ausricht_Gesch_SignalState;
                }
                void setPduState(const uint64_t _value) {
                    m_PduState = _value;
                }
                uint64_t getPduState() const {
                    return m_PduState;
                }


        uint64_t m_POS_GNSS_DR_Breite_Ortung_Raw;
        uint64_t m_POS_GNSS_DR_Breite_Ortung_SignalState;
        uint16_t m_POS_GNSS_DR_Guete_E_GrH_Ausr_Raw;
        uint64_t m_POS_GNSS_DR_Guete_E_GrH_Ausr_SignalState;
        uint16_t m_POS_GNSS_DR_Guete_E_GrHalbachse_Raw;
        uint64_t m_POS_GNSS_DR_Guete_E_GrHalbachse_SignalState;
        uint16_t m_POS_GNSS_DR_Guete_E_KlHalbachse_Raw;
        uint64_t m_POS_GNSS_DR_Guete_E_KlHalbachse_SignalState;
        uint64_t m_POS_GNSS_DR_Laenge_Ortung_Raw;
        uint64_t m_POS_GNSS_DR_Laenge_Ortung_SignalState;
        uint16_t m_POS_GNSS_DR_Ausrichtung_Geschw_Raw;
        uint64_t m_POS_GNSS_DR_Ausrichtung_Geschw_SignalState;
        uint16_t m_POS_GNSS_DR_Guete_Ausricht_Gesch_Raw;
        uint64_t m_POS_GNSS_DR_Guete_Ausricht_Gesch_SignalState;
        uint64_t m_PduState;
    private:
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const asi::sid::lhwapp::cstyle::POSGNSSDR01Struct& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, asi::sid::lhwapp::cstyle::POSGNSSDR01Struct &val);
    };

} // cstyle
}//namespace asi
}//namespace sid
}//namespace lhwapp

#endif// ASI_SID_LHWAPP_POSGNSSDR01STRUCT_CSTYLE_HXX
