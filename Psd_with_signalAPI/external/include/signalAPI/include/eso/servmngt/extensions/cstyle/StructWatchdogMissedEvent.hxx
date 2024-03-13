/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef SERVMNGT_EXTENSIONS_WATCHDOGMISSEDEVENT_CSTYLE_HXX
#define SERVMNGT_EXTENSIONS_WATCHDOGMISSEDEVENT_CSTYLE_HXX

#include <comm/commidltypes.hxx>

// Forward declaration of the struct needed for the forward declaration of the deserializer
namespace servmngt
{
namespace extensions
{
namespace  cstyle
{
struct WatchdogMissedEvent;
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const servmngt::extensions::cstyle::WatchdogMissedEvent& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, servmngt::extensions::cstyle::WatchdogMissedEvent &val);
}
}

namespace servmngt
{
namespace extensions
{
namespace  cstyle
{

    /**
    \brief struct extensions::WatchdogMissedEvent.
    */
    struct PROXY_EXPORT WatchdogMissedEvent
    {
        public:
            WatchdogMissedEvent()
            : m_timestamp()
            , m_count()
            , m_appName(nullptr)
            { }

            WatchdogMissedEvent (const WatchdogMissedEvent& other)
            : m_timestamp()
            , m_count()
            , m_appName(nullptr)
            {
              *this = other;
            }

            ~WatchdogMissedEvent () {
                if (m_appName) {
                    delete m_appName;
                }
            }
            bool operator==(const WatchdogMissedEvent& rhs) const {
                bool equal = true;
                if (m_timestamp != rhs.m_timestamp)
                    equal = false;
                if (m_appName == nullptr && rhs.m_appName != nullptr)
                    equal = false;
                else if (m_appName != nullptr && rhs.m_appName == nullptr)
                    equal = false;
                else if ((m_appName != nullptr) && (rhs.m_appName != nullptr) && (*m_appName != *rhs.m_appName))
                    equal = false;
                if (m_count != rhs.m_count)
                    equal = false;
                return equal;
            }
            bool operator!=(const WatchdogMissedEvent& rhs) const {
                return !operator==(rhs);
            }

            WatchdogMissedEvent& operator = (const WatchdogMissedEvent& src) {
                if (this == &src) return *this;
                m_timestamp = src.m_timestamp;
                if (m_appName)
                    delete m_appName;
                if (src.m_appName) {
                    m_appName = new (ipl::nothrow)ipl::string(*(src.m_appName));
                } else {
                    m_appName = nullptr;
                }
                m_count = src.m_count;
                return *this;
            }

                void settimestamp(const int64_t _value) {
                    m_timestamp = _value;
                }
                int64_t gettimestamp() const {
                    return m_timestamp;
                }
                void setappName(const ipl::string* _value) {
                    if (m_appName)
                        delete m_appName;
                    if (_value) {
                        m_appName = new (ipl::nothrow)ipl::string(*_value);
                    } else {
                        m_appName = nullptr;
                    }
                }
                const ipl::string* getappName() const {
                    return m_appName;
                }
                    bool appNameValid() const {
                        return m_appName != nullptr;
                    }
                void setcount(const uint64_t _value) {
                    m_count = _value;
                }
                uint64_t getcount() const {
                    return m_count;
                }


        int64_t m_timestamp;
        uint64_t m_count;
    private:
        ipl::string* m_appName;
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const servmngt::extensions::cstyle::WatchdogMissedEvent& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, servmngt::extensions::cstyle::WatchdogMissedEvent &val);
    };

} // cstyle
}//namespace servmngt
}//namespace extensions

#endif// SERVMNGT_EXTENSIONS_WATCHDOGMISSEDEVENT_CSTYLE_HXX
