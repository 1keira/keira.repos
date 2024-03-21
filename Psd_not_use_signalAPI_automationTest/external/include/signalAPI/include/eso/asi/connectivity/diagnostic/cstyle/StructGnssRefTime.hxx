/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_GNSSREFTIME_CSTYLE_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_GNSSREFTIME_CSTYLE_HXX

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
struct GnssRefTime;
}
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const asi::connectivity::diagnostic::cstyle::GnssRefTime& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::GnssRefTime &val);
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
    \brief struct diagnostic::GnssRefTime.
    */
    struct PROXY_EXPORT GnssRefTime
    {
        public:
            GnssRefTime()
            : m_day()
            , m_month()
            , m_year()
            { }

            GnssRefTime (const GnssRefTime& other)
            : m_day()
            , m_month()
            , m_year()
            {
              *this = other;
            }

            ~GnssRefTime () {
            }
            bool operator==(const GnssRefTime& rhs) const {
                bool equal = true;
                if (m_day != rhs.m_day)
                    equal = false;
                if (m_month != rhs.m_month)
                    equal = false;
                if (m_year != rhs.m_year)
                    equal = false;
                return equal;
            }
            bool operator!=(const GnssRefTime& rhs) const {
                return !operator==(rhs);
            }

            GnssRefTime& operator = (const GnssRefTime& src) {
                if (this == &src) return *this;
                m_day = src.m_day;
                m_month = src.m_month;
                m_year = src.m_year;
                return *this;
            }

                void setday(const uint8_t _value) {
                    m_day = _value;
                }
                uint8_t getday() const {
                    return m_day;
                }
                void setmonth(const uint8_t _value) {
                    m_month = _value;
                }
                uint8_t getmonth() const {
                    return m_month;
                }
                void setyear(const uint16_t _value) {
                    m_year = _value;
                }
                uint16_t getyear() const {
                    return m_year;
                }


        uint8_t m_day;
        uint8_t m_month;
        uint16_t m_year;
    private:
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const asi::connectivity::diagnostic::cstyle::GnssRefTime& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::GnssRefTime &val);
    };

} // cstyle
}//namespace asi
}//namespace connectivity
}//namespace diagnostic

#endif// ASI_CONNECTIVITY_DIAGNOSTIC_GNSSREFTIME_CSTYLE_HXX
