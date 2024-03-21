/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_ROUTINEREQUESTINFO_CSTYLE_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_ROUTINEREQUESTINFO_CSTYLE_HXX

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
struct RoutineRequestInfo;
}
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const asi::connectivity::diagnostic::cstyle::RoutineRequestInfo& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::RoutineRequestInfo &val);
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
    \brief struct diagnostic::RoutineRequestInfo.
    */
    struct PROXY_EXPORT RoutineRequestInfo
    {
        public:
            RoutineRequestInfo()
            : m_id()
            , m_requestType()
            { }

            RoutineRequestInfo (const RoutineRequestInfo& other)
            : m_id()
            , m_requestType()
            {
              *this = other;
            }

            ~RoutineRequestInfo () {
            }
            bool operator==(const RoutineRequestInfo& rhs) const {
                bool equal = true;
                if (m_id != rhs.m_id)
                    equal = false;
                if (m_requestType != rhs.m_requestType)
                    equal = false;
                return equal;
            }
            bool operator!=(const RoutineRequestInfo& rhs) const {
                return !operator==(rhs);
            }

            RoutineRequestInfo& operator = (const RoutineRequestInfo& src) {
                if (this == &src) return *this;
                m_id = src.m_id;
                m_requestType = src.m_requestType;
                return *this;
            }

                void setid(const uint32_t _value) {
                    m_id = _value;
                }
                uint32_t getid() const {
                    return m_id;
                }
                void setrequestType(const asi::connectivity::diagnostic::cstyle::RoutineRequestType _value) {
                    m_requestType = _value;
                }
                asi::connectivity::diagnostic::cstyle::RoutineRequestType getrequestType() const {
                    return m_requestType;
                }


        uint32_t m_id;
        asi::connectivity::diagnostic::cstyle::RoutineRequestType m_requestType;
    private:
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const asi::connectivity::diagnostic::cstyle::RoutineRequestInfo& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::RoutineRequestInfo &val);
    };

} // cstyle
}//namespace asi
}//namespace connectivity
}//namespace diagnostic

#endif// ASI_CONNECTIVITY_DIAGNOSTIC_ROUTINEREQUESTINFO_CSTYLE_HXX
