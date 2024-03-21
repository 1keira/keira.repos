/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_ROUTINEREQUEST_CSTYLE_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_ROUTINEREQUEST_CSTYLE_HXX

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
struct RoutineRequest;
}
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const asi::connectivity::diagnostic::cstyle::RoutineRequest& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::RoutineRequest &val);
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
    \brief struct diagnostic::RoutineRequest.
    */
    struct PROXY_EXPORT RoutineRequest
    {
        public:
            RoutineRequest()
            : m_requestType()
            , m_routineId()
            , m_data(nullptr)
            { }

            RoutineRequest (const RoutineRequest& other)
            : m_requestType()
            , m_routineId()
            , m_data(nullptr)
            {
              *this = other;
            }

            ~RoutineRequest () {
                if (m_data) {
                    delete m_data;
                }
            }
            bool operator==(const RoutineRequest& rhs) const {
                bool equal = true;
                if (m_data == nullptr && rhs.m_data != nullptr)
                    equal = false;
                else if (m_data != nullptr && rhs.m_data == nullptr)
                    equal = false;
                else if ((m_data != nullptr) && (rhs.m_data != nullptr) && (*m_data != *rhs.m_data))
                    equal = false;
                if (m_requestType != rhs.m_requestType)
                    equal = false;
                if (m_routineId != rhs.m_routineId)
                    equal = false;
                return equal;
            }
            bool operator!=(const RoutineRequest& rhs) const {
                return !operator==(rhs);
            }

            RoutineRequest& operator = (const RoutineRequest& src) {
                if (this == &src) return *this;
                if (m_data)
                    delete m_data;
                if (src.m_data) {
                    m_data = new (ipl::nothrow)ipl::vector<uint8_t>(*(src.m_data));
                } else {
                    m_data = nullptr;
                }
                m_requestType = src.m_requestType;
                m_routineId = src.m_routineId;
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
                void setrequestType(const asi::connectivity::diagnostic::cstyle::RoutineRequestType _value) {
                    m_requestType = _value;
                }
                asi::connectivity::diagnostic::cstyle::RoutineRequestType getrequestType() const {
                    return m_requestType;
                }
                void setroutineId(const uint32_t _value) {
                    m_routineId = _value;
                }
                uint32_t getroutineId() const {
                    return m_routineId;
                }


        asi::connectivity::diagnostic::cstyle::RoutineRequestType m_requestType;
        uint32_t m_routineId;
    private:
        /**
            data Array Size: unlimited
        */
        ipl::vector<uint8_t>* m_data;
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const asi::connectivity::diagnostic::cstyle::RoutineRequest& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::RoutineRequest &val);
    };

} // cstyle
}//namespace asi
}//namespace connectivity
}//namespace diagnostic

#endif// ASI_CONNECTIVITY_DIAGNOSTIC_ROUTINEREQUEST_CSTYLE_HXX
