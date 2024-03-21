/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_SOKFRESHNESS_CSTYLE_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_SOKFRESHNESS_CSTYLE_HXX

#include <comm/commidltypes.hxx>

// Forward declaration of the struct needed for the forward declaration of the deserializer
namespace asi
{
namespace connectivity
{
namespace diagnostic
{
namespace  cstyle
{
struct SokFreshness;
}
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const asi::connectivity::diagnostic::cstyle::SokFreshness& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::SokFreshness &val);
}
}

namespace asi
{
namespace connectivity
{
namespace diagnostic
{
namespace  cstyle
{

    /**
    \brief struct diagnostic::SokFreshness.
    */
    struct PROXY_EXPORT SokFreshness
    {
        public:
            SokFreshness()
            : m_activeCounterValue()
            , m_consumedCounterValues()
            , m_isActive()
            , m_pduId()
            , m_timestampOfLastSuccessfulVerification()
            { }

            SokFreshness (const SokFreshness& other)
            : m_activeCounterValue()
            , m_consumedCounterValues()
            , m_isActive()
            , m_pduId()
            , m_timestampOfLastSuccessfulVerification()
            {
              *this = other;
            }

            ~SokFreshness () {
            }
            bool operator==(const SokFreshness& rhs) const {
                bool equal = true;
                if (m_activeCounterValue != rhs.m_activeCounterValue)
                    equal = false;
                if (m_consumedCounterValues != rhs.m_consumedCounterValues)
                    equal = false;
                if (m_isActive != rhs.m_isActive)
                    equal = false;
                if (m_pduId != rhs.m_pduId)
                    equal = false;
                if (m_timestampOfLastSuccessfulVerification != rhs.m_timestampOfLastSuccessfulVerification)
                    equal = false;
                return equal;
            }
            bool operator!=(const SokFreshness& rhs) const {
                return !operator==(rhs);
            }

            SokFreshness& operator = (const SokFreshness& src) {
                if (this == &src) return *this;
                m_activeCounterValue = src.m_activeCounterValue;
                m_consumedCounterValues = src.m_consumedCounterValues;
                m_isActive = src.m_isActive;
                m_pduId = src.m_pduId;
                m_timestampOfLastSuccessfulVerification = src.m_timestampOfLastSuccessfulVerification;
                return *this;
            }

                void setactiveCounterValue(const uint8_t _value) {
                    m_activeCounterValue = _value;
                }
                uint8_t getactiveCounterValue() const {
                    return m_activeCounterValue;
                }
                void setconsumedCounterValues(const uint16_t _value) {
                    m_consumedCounterValues = _value;
                }
                uint16_t getconsumedCounterValues() const {
                    return m_consumedCounterValues;
                }
                void setisActive(const bool _value) {
                    m_isActive = _value;
                }
                bool getisActive() const {
                    return m_isActive;
                }
                void setpduId(const uint16_t _value) {
                    m_pduId = _value;
                }
                uint16_t getpduId() const {
                    return m_pduId;
                }
                void settimestampOfLastSuccessfulVerification(const uint64_t _value) {
                    m_timestampOfLastSuccessfulVerification = _value;
                }
                uint64_t gettimestampOfLastSuccessfulVerification() const {
                    return m_timestampOfLastSuccessfulVerification;
                }


        uint8_t m_activeCounterValue;
        uint16_t m_consumedCounterValues;
        bool m_isActive;
        uint16_t m_pduId;
        uint64_t m_timestampOfLastSuccessfulVerification;
    private:
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const asi::connectivity::diagnostic::cstyle::SokFreshness& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::SokFreshness &val);
    };

} // cstyle
}//namespace asi
}//namespace connectivity
}//namespace diagnostic

#endif// ASI_CONNECTIVITY_DIAGNOSTIC_SOKFRESHNESS_CSTYLE_HXX
