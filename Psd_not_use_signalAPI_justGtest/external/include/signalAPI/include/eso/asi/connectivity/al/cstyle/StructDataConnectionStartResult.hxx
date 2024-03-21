/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_DATACONNECTIONSTARTRESULT_CSTYLE_HXX
#define ASI_CONNECTIVITY_AL_DATACONNECTIONSTARTRESULT_CSTYLE_HXX

#include <comm/commidltypes.hxx>
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
struct DataConnectionStartResult;
}
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const asi::connectivity::al::cstyle::DataConnectionStartResult& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::al::cstyle::DataConnectionStartResult &val);
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
    \brief struct al::DataConnectionStartResult.
    */
    struct PROXY_EXPORT DataConnectionStartResult
    {
        public:
            DataConnectionStartResult()
            : m_asiDataConnectionId()
            , m_result()
            { }

            DataConnectionStartResult (const DataConnectionStartResult& other)
            : m_asiDataConnectionId()
            , m_result()
            {
              *this = other;
            }

            ~DataConnectionStartResult () {
            }
            bool operator==(const DataConnectionStartResult& rhs) const {
                bool equal = true;
                if (m_asiDataConnectionId != rhs.m_asiDataConnectionId)
                    equal = false;
                if (m_result != rhs.m_result)
                    equal = false;
                return equal;
            }
            bool operator!=(const DataConnectionStartResult& rhs) const {
                return !operator==(rhs);
            }

            DataConnectionStartResult& operator = (const DataConnectionStartResult& src) {
                if (this == &src) return *this;
                m_asiDataConnectionId = src.m_asiDataConnectionId;
                m_result = src.m_result;
                return *this;
            }

                void setasiDataConnectionId(const int32_t _value) {
                    m_asiDataConnectionId = _value;
                }
                int32_t getasiDataConnectionId() const {
                    return m_asiDataConnectionId;
                }
                void setresult(const asi::connectivity::al::cstyle::ResultType _value) {
                    m_result = _value;
                }
                asi::connectivity::al::cstyle::ResultType getresult() const {
                    return m_result;
                }


        int32_t m_asiDataConnectionId;
        asi::connectivity::al::cstyle::ResultType m_result;
    private:
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const asi::connectivity::al::cstyle::DataConnectionStartResult& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::al::cstyle::DataConnectionStartResult &val);
    };

} // cstyle
}//namespace asi
}//namespace connectivity
}//namespace al

#endif// ASI_CONNECTIVITY_AL_DATACONNECTIONSTARTRESULT_CSTYLE_HXX
