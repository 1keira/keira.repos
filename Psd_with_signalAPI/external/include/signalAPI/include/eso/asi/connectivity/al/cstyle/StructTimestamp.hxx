/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_TIMESTAMP_CSTYLE_HXX
#define ASI_CONNECTIVITY_AL_TIMESTAMP_CSTYLE_HXX

#include <comm/commidltypes.hxx>

// Forward declaration of the struct needed for the forward declaration of the deserializer
namespace asi
{
namespace connectivity
{
namespace al
{
namespace  cstyle
{
struct Timestamp;
}
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const asi::connectivity::al::cstyle::Timestamp& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::al::cstyle::Timestamp &val);
}
}

namespace asi
{
namespace connectivity
{
namespace al
{
namespace  cstyle
{

    /**
    \brief struct al::Timestamp.
    */
    struct PROXY_EXPORT Timestamp
    {
        public:
            Timestamp()
            : m_year(-1)
            , m_month(-1)
            , m_day(-1)
            , m_hours(-1)
            , m_minutes(-1)
            , m_seconds(-1)
            { }

            Timestamp (const Timestamp& other)
            : m_year(-1)
            , m_month(-1)
            , m_day(-1)
            , m_hours(-1)
            , m_minutes(-1)
            , m_seconds(-1)
            {
              *this = other;
            }

            ~Timestamp () {
            }
            bool operator==(const Timestamp& rhs) const {
                bool equal = true;
                if (m_year != rhs.m_year)
                    equal = false;
                if (m_month != rhs.m_month)
                    equal = false;
                if (m_day != rhs.m_day)
                    equal = false;
                if (m_hours != rhs.m_hours)
                    equal = false;
                if (m_minutes != rhs.m_minutes)
                    equal = false;
                if (m_seconds != rhs.m_seconds)
                    equal = false;
                return equal;
            }
            bool operator!=(const Timestamp& rhs) const {
                return !operator==(rhs);
            }

            Timestamp& operator = (const Timestamp& src) {
                if (this == &src) return *this;
                m_year = src.m_year;
                m_month = src.m_month;
                m_day = src.m_day;
                m_hours = src.m_hours;
                m_minutes = src.m_minutes;
                m_seconds = src.m_seconds;
                return *this;
            }

                void setyear(const int16_t _value) {
                    m_year = _value;
                }
                int16_t getyear() const {
                    return m_year;
                }
                void setmonth(const int16_t _value) {
                    m_month = _value;
                }
                int16_t getmonth() const {
                    return m_month;
                }
                void setday(const int16_t _value) {
                    m_day = _value;
                }
                int16_t getday() const {
                    return m_day;
                }
                void sethours(const int16_t _value) {
                    m_hours = _value;
                }
                int16_t gethours() const {
                    return m_hours;
                }
                void setminutes(const int16_t _value) {
                    m_minutes = _value;
                }
                int16_t getminutes() const {
                    return m_minutes;
                }
                void setseconds(const int16_t _value) {
                    m_seconds = _value;
                }
                int16_t getseconds() const {
                    return m_seconds;
                }


        int16_t m_year;
        int16_t m_month;
        int16_t m_day;
        int16_t m_hours;
        int16_t m_minutes;
        int16_t m_seconds;
    private:
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const asi::connectivity::al::cstyle::Timestamp& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::al::cstyle::Timestamp &val);
    };

} // cstyle
}//namespace asi
}//namespace connectivity
}//namespace al

#endif// ASI_CONNECTIVITY_AL_TIMESTAMP_CSTYLE_HXX
