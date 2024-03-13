/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_ROUTINERESPONSE_CSTYLE_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_ROUTINERESPONSE_CSTYLE_HXX

#include <comm/commidltypes.hxx>
#include <asi/connectivity/diagnostic/cstyle/Definitions.hxx>

// Forward declaration of the struct needed for the forward declaration of the deserializer
namespace asi
{
namespace connectivity
{
namespace diagnostic
{
namespace  cstyle
{
struct RoutineResponse;
}
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const asi::connectivity::diagnostic::cstyle::RoutineResponse& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::RoutineResponse &val);
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
    \brief struct diagnostic::RoutineResponse.
    */
    struct PROXY_EXPORT RoutineResponse
    {
        public:
            RoutineResponse()
            : m_routineId()
            , m_state()
            , m_data(nullptr)
            { }

            RoutineResponse (const RoutineResponse& other)
            : m_routineId()
            , m_state()
            , m_data(nullptr)
            {
              *this = other;
            }

            ~RoutineResponse () {
                if (m_data) {
                    delete m_data;
                }
            }
            bool operator==(const RoutineResponse& rhs) const {
                bool equal = true;
                if (m_data == nullptr && rhs.m_data != nullptr)
                    equal = false;
                else if (m_data != nullptr && rhs.m_data == nullptr)
                    equal = false;
                else if ((m_data != nullptr) && (rhs.m_data != nullptr) && (*m_data != *rhs.m_data))
                    equal = false;
                if (m_routineId != rhs.m_routineId)
                    equal = false;
                if (m_state != rhs.m_state)
                    equal = false;
                return equal;
            }
            bool operator!=(const RoutineResponse& rhs) const {
                return !operator==(rhs);
            }

            RoutineResponse& operator = (const RoutineResponse& src) {
                if (this == &src) return *this;
                if (m_data)
                    delete m_data;
                if (src.m_data) {
                    m_data = new (ipl::nothrow)ipl::vector<uint8_t>(*(src.m_data));
                } else {
                    m_data = nullptr;
                }
                m_routineId = src.m_routineId;
                m_state = src.m_state;
                return *this;
            }

                void setdata(const ipl::vector<uint8_t>* _value) {
                    if (m_data)
                        delete m_data;
                    if (_value) {
                        m_data = new (ipl::nothrow)ipl::vector<uint8_t>(*_value);
                    } else {
                        m_data = nullptr;
                    }
                }
                const ipl::vector<uint8_t>* getdata() const {
                    return m_data;
                }
                    bool dataValid() const {
                        return m_data != nullptr;
                    }
                void setroutineId(const uint32_t _value) {
                    m_routineId = _value;
                }
                uint32_t getroutineId() const {
                    return m_routineId;
                }
                void setstate(const asi::connectivity::diagnostic::cstyle::RoutineState _value) {
                    m_state = _value;
                }
                asi::connectivity::diagnostic::cstyle::RoutineState getstate() const {
                    return m_state;
                }


        uint32_t m_routineId;
        asi::connectivity::diagnostic::cstyle::RoutineState m_state;
    private:
        /**
            data Array Size: unlimited
        */
        ipl::vector<uint8_t>* m_data;
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const asi::connectivity::diagnostic::cstyle::RoutineResponse& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::RoutineResponse &val);
    };

} // cstyle
}//namespace asi
}//namespace connectivity
}//namespace diagnostic

#endif// ASI_CONNECTIVITY_DIAGNOSTIC_ROUTINERESPONSE_CSTYLE_HXX
