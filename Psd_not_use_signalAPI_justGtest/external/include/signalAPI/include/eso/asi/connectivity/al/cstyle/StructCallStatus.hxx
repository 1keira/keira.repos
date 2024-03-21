/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_CALLSTATUS_CSTYLE_HXX
#define ASI_CONNECTIVITY_AL_CALLSTATUS_CSTYLE_HXX

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
struct CallStatus;
}
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const asi::connectivity::al::cstyle::CallStatus& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::al::cstyle::CallStatus &val);
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
    \brief struct al::CallStatus.
    */
    struct PROXY_EXPORT CallStatus
    {
        public:
            CallStatus()
            : m_callID()
            , m_callState()
            , m_callDirection()
            , m_isMultiCall()
            , m_telNumber(nullptr)
            { }

            CallStatus (const CallStatus& other)
            : m_callID()
            , m_callState()
            , m_callDirection()
            , m_isMultiCall()
            , m_telNumber(nullptr)
            {
              *this = other;
            }

            ~CallStatus () {
                if (m_telNumber) {
                    delete m_telNumber;
                }
            }
            bool operator==(const CallStatus& rhs) const {
                bool equal = true;
                if (m_callID != rhs.m_callID)
                    equal = false;
                if (m_callState != rhs.m_callState)
                    equal = false;
                if (m_callDirection != rhs.m_callDirection)
                    equal = false;
                if (m_isMultiCall != rhs.m_isMultiCall)
                    equal = false;
                if (m_telNumber == nullptr && rhs.m_telNumber != nullptr)
                    equal = false;
                else if (m_telNumber != nullptr && rhs.m_telNumber == nullptr)
                    equal = false;
                else if ((m_telNumber != nullptr) && (rhs.m_telNumber != nullptr) && (*m_telNumber != *rhs.m_telNumber))
                    equal = false;
                return equal;
            }
            bool operator!=(const CallStatus& rhs) const {
                return !operator==(rhs);
            }

            CallStatus& operator = (const CallStatus& src) {
                if (this == &src) return *this;
                m_callID = src.m_callID;
                m_callState = src.m_callState;
                m_callDirection = src.m_callDirection;
                m_isMultiCall = src.m_isMultiCall;
                if (m_telNumber)
                    delete m_telNumber;
                if (src.m_telNumber) {
                    m_telNumber = new (ipl::nothrow)ipl::string(*(src.m_telNumber));
                } else {
                    m_telNumber = nullptr;
                }
                return *this;
            }

                void setcallID(const int32_t _value) {
                    m_callID = _value;
                }
                int32_t getcallID() const {
                    return m_callID;
                }
                void setcallState(const asi::connectivity::al::cstyle::CallState _value) {
                    m_callState = _value;
                }
                asi::connectivity::al::cstyle::CallState getcallState() const {
                    return m_callState;
                }
                void setcallDirection(const asi::connectivity::al::cstyle::CallDirection _value) {
                    m_callDirection = _value;
                }
                asi::connectivity::al::cstyle::CallDirection getcallDirection() const {
                    return m_callDirection;
                }
                void setisMultiCall(const bool _value) {
                    m_isMultiCall = _value;
                }
                bool getisMultiCall() const {
                    return m_isMultiCall;
                }
                void settelNumber(const ipl::string* _value) {
                    if (m_telNumber)
                        delete m_telNumber;
                    if (_value) {
                        m_telNumber = new (ipl::nothrow)ipl::string(*_value);
                    } else {
                        m_telNumber = nullptr;
                    }
                }
                const ipl::string* gettelNumber() const {
                    return m_telNumber;
                }
                    bool telNumberValid() const {
                        return m_telNumber != nullptr;
                    }


        int32_t m_callID;
        asi::connectivity::al::cstyle::CallState m_callState;
        asi::connectivity::al::cstyle::CallDirection m_callDirection;
        bool m_isMultiCall;
    private:
        ipl::string* m_telNumber;
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const asi::connectivity::al::cstyle::CallStatus& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::al::cstyle::CallStatus &val);
    };

} // cstyle
}//namespace asi
}//namespace connectivity
}//namespace al

#endif// ASI_CONNECTIVITY_AL_CALLSTATUS_CSTYLE_HXX
