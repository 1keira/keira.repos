/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_SOKTIME_CSTYLE_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_SOKTIME_CSTYLE_HXX

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
struct SokTime;
}
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const asi::connectivity::diagnostic::cstyle::SokTime& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::SokTime &val);
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
    \brief struct diagnostic::SokTime.
    */
    struct PROXY_EXPORT SokTime
    {
        public:
            SokTime()
            : m_currentTime()
            , m_isJitterExceeded()
            , m_isTimeValid()
            { }

            SokTime (const SokTime& other)
            : m_currentTime()
            , m_isJitterExceeded()
            , m_isTimeValid()
            {
              *this = other;
            }

            ~SokTime () {
            }
            bool operator==(const SokTime& rhs) const {
                bool equal = true;
                if (m_currentTime != rhs.m_currentTime)
                    equal = false;
                if (m_isJitterExceeded != rhs.m_isJitterExceeded)
                    equal = false;
                if (m_isTimeValid != rhs.m_isTimeValid)
                    equal = false;
                return equal;
            }
            bool operator!=(const SokTime& rhs) const {
                return !operator==(rhs);
            }

            SokTime& operator = (const SokTime& src) {
                if (this == &src) return *this;
                m_currentTime = src.m_currentTime;
                m_isJitterExceeded = src.m_isJitterExceeded;
                m_isTimeValid = src.m_isTimeValid;
                return *this;
            }

                void setcurrentTime(const uint64_t _value) {
                    m_currentTime = _value;
                }
                uint64_t getcurrentTime() const {
                    return m_currentTime;
                }
                void setisJitterExceeded(const bool _value) {
                    m_isJitterExceeded = _value;
                }
                bool getisJitterExceeded() const {
                    return m_isJitterExceeded;
                }
                void setisTimeValid(const bool _value) {
                    m_isTimeValid = _value;
                }
                bool getisTimeValid() const {
                    return m_isTimeValid;
                }


        uint64_t m_currentTime;
        bool m_isJitterExceeded;
        bool m_isTimeValid;
    private:
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const asi::connectivity::diagnostic::cstyle::SokTime& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::SokTime &val);
    };

} // cstyle
}//namespace asi
}//namespace connectivity
}//namespace diagnostic

#endif// ASI_CONNECTIVITY_DIAGNOSTIC_SOKTIME_CSTYLE_HXX
