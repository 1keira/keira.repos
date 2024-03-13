/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_CALLSTACKENTRY_CSTYLE_HXX
#define ASI_CONNECTIVITY_AL_CALLSTACKENTRY_CSTYLE_HXX

#include <comm/commidltypes.hxx>
#include <asi/connectivity/al/cstyle/StructTimestamp.hxx>

// Forward declaration of the struct needed for the forward declaration of the deserializer
namespace asi
{
namespace connectivity
{
namespace al
{
namespace  cstyle
{
struct CallStackEntry;
}
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const asi::connectivity::al::cstyle::CallStackEntry& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::al::cstyle::CallStackEntry &val);
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
    \brief struct al::CallStackEntry.
    */
    struct PROXY_EXPORT CallStackEntry
    {
        public:
            CallStackEntry()
            : m_name(nullptr)
            , m_number(nullptr)
            , m_timestamp(nullptr)
            , m_time(nullptr)
            , m_date(nullptr)
            , m_uid(nullptr)
            { }

            CallStackEntry (const CallStackEntry& other)
            : m_name(nullptr)
            , m_number(nullptr)
            , m_timestamp(nullptr)
            , m_time(nullptr)
            , m_date(nullptr)
            , m_uid(nullptr)
            {
              *this = other;
            }

            ~CallStackEntry () {
                if (m_name) {
                    delete m_name;
                }
                if (m_number) {
                    delete m_number;
                }
                if (m_timestamp) {
                    delete m_timestamp;
                }
                if (m_time) {
                    delete m_time;
                }
                if (m_date) {
                    delete m_date;
                }
                if (m_uid) {
                    delete m_uid;
                }
            }
            bool operator==(const CallStackEntry& rhs) const {
                bool equal = true;
                if (m_name == nullptr && rhs.m_name != nullptr)
                    equal = false;
                else if (m_name != nullptr && rhs.m_name == nullptr)
                    equal = false;
                else if ((m_name != nullptr) && (rhs.m_name != nullptr) && (*m_name != *rhs.m_name))
                    equal = false;
                if (m_number == nullptr && rhs.m_number != nullptr)
                    equal = false;
                else if (m_number != nullptr && rhs.m_number == nullptr)
                    equal = false;
                else if ((m_number != nullptr) && (rhs.m_number != nullptr) && (*m_number != *rhs.m_number))
                    equal = false;
                if (m_timestamp == nullptr && rhs.m_timestamp != nullptr)
                    equal = false;
                else if (m_timestamp != nullptr && rhs.m_timestamp == nullptr)
                    equal = false;
                else if ((m_timestamp != nullptr) && (rhs.m_timestamp != nullptr) && (*m_timestamp != *rhs.m_timestamp))
                    equal = false;
                if (m_time == nullptr && rhs.m_time != nullptr)
                    equal = false;
                else if (m_time != nullptr && rhs.m_time == nullptr)
                    equal = false;
                else if ((m_time != nullptr) && (rhs.m_time != nullptr) && (*m_time != *rhs.m_time))
                    equal = false;
                if (m_date == nullptr && rhs.m_date != nullptr)
                    equal = false;
                else if (m_date != nullptr && rhs.m_date == nullptr)
                    equal = false;
                else if ((m_date != nullptr) && (rhs.m_date != nullptr) && (*m_date != *rhs.m_date))
                    equal = false;
                if (m_uid == nullptr && rhs.m_uid != nullptr)
                    equal = false;
                else if (m_uid != nullptr && rhs.m_uid == nullptr)
                    equal = false;
                else if ((m_uid != nullptr) && (rhs.m_uid != nullptr) && (*m_uid != *rhs.m_uid))
                    equal = false;
                return equal;
            }
            bool operator!=(const CallStackEntry& rhs) const {
                return !operator==(rhs);
            }

            CallStackEntry& operator = (const CallStackEntry& src) {
                if (this == &src) return *this;
                if (m_name)
                    delete m_name;
                if (src.m_name) {
                    m_name = new (ipl::nothrow)ipl::string(*(src.m_name));
                } else {
                    m_name = nullptr;
                }
                if (m_number)
                    delete m_number;
                if (src.m_number) {
                    m_number = new (ipl::nothrow)ipl::string(*(src.m_number));
                } else {
                    m_number = nullptr;
                }
                if (m_timestamp)
                    delete m_timestamp;
                if (src.m_timestamp) {
                    m_timestamp = new (ipl::nothrow)asi::connectivity::al::cstyle::Timestamp(*(src.m_timestamp));
                } else {
                    m_timestamp = nullptr;
                }
                if (m_time)
                    delete m_time;
                if (src.m_time) {
                    m_time = new (ipl::nothrow)ipl::string(*(src.m_time));
                } else {
                    m_time = nullptr;
                }
                if (m_date)
                    delete m_date;
                if (src.m_date) {
                    m_date = new (ipl::nothrow)ipl::string(*(src.m_date));
                } else {
                    m_date = nullptr;
                }
                if (m_uid)
                    delete m_uid;
                if (src.m_uid) {
                    m_uid = new (ipl::nothrow)ipl::string(*(src.m_uid));
                } else {
                    m_uid = nullptr;
                }
                return *this;
            }

                void setname(const ipl::string* _value) {
                    if (m_name)
                        delete m_name;
                    if (_value) {
                        m_name = new (ipl::nothrow)ipl::string(*_value);
                    } else {
                        m_name = nullptr;
                    }
                }
                const ipl::string* getname() const {
                    return m_name;
                }
                    bool nameValid() const {
                        return m_name != nullptr;
                    }
                void setnumber(const ipl::string* _value) {
                    if (m_number)
                        delete m_number;
                    if (_value) {
                        m_number = new (ipl::nothrow)ipl::string(*_value);
                    } else {
                        m_number = nullptr;
                    }
                }
                const ipl::string* getnumber() const {
                    return m_number;
                }
                    bool numberValid() const {
                        return m_number != nullptr;
                    }
                void settimestamp(const asi::connectivity::al::cstyle::Timestamp* _value) {
                    if (m_timestamp)
                        delete m_timestamp;
                    if (_value) {
                        m_timestamp = new (ipl::nothrow)asi::connectivity::al::cstyle::Timestamp(*_value);
                    } else {
                        m_timestamp = nullptr;
                    }
                }
                const asi::connectivity::al::cstyle::Timestamp* gettimestamp() const {
                    return m_timestamp;
                }
                    bool timestampValid() const {
                        return m_timestamp != nullptr;
                    }
                void settime(const ipl::string* _value) {
                    if (m_time)
                        delete m_time;
                    if (_value) {
                        m_time = new (ipl::nothrow)ipl::string(*_value);
                    } else {
                        m_time = nullptr;
                    }
                }
                const ipl::string* gettime() const {
                    return m_time;
                }
                    bool timeValid() const {
                        return m_time != nullptr;
                    }
                void setdate(const ipl::string* _value) {
                    if (m_date)
                        delete m_date;
                    if (_value) {
                        m_date = new (ipl::nothrow)ipl::string(*_value);
                    } else {
                        m_date = nullptr;
                    }
                }
                const ipl::string* getdate() const {
                    return m_date;
                }
                    bool dateValid() const {
                        return m_date != nullptr;
                    }
                void setuid(const ipl::string* _value) {
                    if (m_uid)
                        delete m_uid;
                    if (_value) {
                        m_uid = new (ipl::nothrow)ipl::string(*_value);
                    } else {
                        m_uid = nullptr;
                    }
                }
                const ipl::string* getuid() const {
                    return m_uid;
                }
                    bool uidValid() const {
                        return m_uid != nullptr;
                    }


    private:
        ipl::string* m_name;
        ipl::string* m_number;
        asi::connectivity::al::cstyle::Timestamp* m_timestamp;
        ipl::string* m_time;
        ipl::string* m_date;
        ipl::string* m_uid;
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const asi::connectivity::al::cstyle::CallStackEntry& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::al::cstyle::CallStackEntry &val);
    };

} // cstyle
}//namespace asi
}//namespace connectivity
}//namespace al

#endif// ASI_CONNECTIVITY_AL_CALLSTACKENTRY_CSTYLE_HXX
