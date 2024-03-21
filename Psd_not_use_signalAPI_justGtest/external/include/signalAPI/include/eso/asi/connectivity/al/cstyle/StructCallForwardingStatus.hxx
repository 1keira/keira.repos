/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_CALLFORWARDINGSTATUS_CSTYLE_HXX
#define ASI_CONNECTIVITY_AL_CALLFORWARDINGSTATUS_CSTYLE_HXX

#include <comm/commidltypes.hxx>
#include <asi/connectivity/al/cstyle/Definitions.hxx>
#include <asi/connectivity/al/cstyle/Definitions.hxx>

// Forward declaration of the struct needed for the forward declaration of the deserializer
namespace asi
{
namespace connectivity
{
namespace al
{
namespace  cstyle
{
struct CallForwardingStatus;
}
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const asi::connectivity::al::cstyle::CallForwardingStatus& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::al::cstyle::CallForwardingStatus &val);
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
    \brief struct al::CallForwardingStatus.
    */
    struct PROXY_EXPORT CallForwardingStatus
    {
        public:
            CallForwardingStatus()
            : m_reason()
            , m_service_class()
            , m_time()
            , m_number(nullptr)
            { }

            CallForwardingStatus (const CallForwardingStatus& other)
            : m_reason()
            , m_service_class()
            , m_time()
            , m_number(nullptr)
            {
              *this = other;
            }

            ~CallForwardingStatus () {
                if (m_number) {
                    delete m_number;
                }
            }
            bool operator==(const CallForwardingStatus& rhs) const {
                bool equal = true;
                if (m_reason != rhs.m_reason)
                    equal = false;
                if (m_service_class != rhs.m_service_class)
                    equal = false;
                if (m_number == nullptr && rhs.m_number != nullptr)
                    equal = false;
                else if (m_number != nullptr && rhs.m_number == nullptr)
                    equal = false;
                else if ((m_number != nullptr) && (rhs.m_number != nullptr) && (*m_number != *rhs.m_number))
                    equal = false;
                if (m_time != rhs.m_time)
                    equal = false;
                return equal;
            }
            bool operator!=(const CallForwardingStatus& rhs) const {
                return !operator==(rhs);
            }

            CallForwardingStatus& operator = (const CallForwardingStatus& src) {
                if (this == &src) return *this;
                m_reason = src.m_reason;
                m_service_class = src.m_service_class;
                if (m_number)
                    delete m_number;
                if (src.m_number) {
                    m_number = new (ipl::nothrow)ipl::string(*(src.m_number));
                } else {
                    m_number = nullptr;
                }
                m_time = src.m_time;
                return *this;
            }

                void setreason(const asi::connectivity::al::cstyle::CfcReason _value) {
                    m_reason = _value;
                }
                asi::connectivity::al::cstyle::CfcReason getreason() const {
                    return m_reason;
                }
                void setservice_class(const asi::connectivity::al::cstyle::ServiceClass _value) {
                    m_service_class = _value;
                }
                asi::connectivity::al::cstyle::ServiceClass getservice_class() const {
                    return m_service_class;
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
                void settime(const uint32_t _value) {
                    m_time = _value;
                }
                uint32_t gettime() const {
                    return m_time;
                }


        asi::connectivity::al::cstyle::CfcReason m_reason;
        asi::connectivity::al::cstyle::ServiceClass m_service_class;
        uint32_t m_time;
    private:
        ipl::string* m_number;
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const asi::connectivity::al::cstyle::CallForwardingStatus& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::al::cstyle::CallForwardingStatus &val);
    };

} // cstyle
}//namespace asi
}//namespace connectivity
}//namespace al

#endif// ASI_CONNECTIVITY_AL_CALLFORWARDINGSTATUS_CSTYLE_HXX
