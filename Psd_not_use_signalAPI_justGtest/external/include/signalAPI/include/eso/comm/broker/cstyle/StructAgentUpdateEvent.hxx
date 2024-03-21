/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef COMM_BROKER_AGENTUPDATEEVENT_CSTYLE_HXX
#define COMM_BROKER_AGENTUPDATEEVENT_CSTYLE_HXX

#include <comm/commidltypes.hxx>

// Forward declaration of the struct needed for the forward declaration of the deserializer
namespace comm
{
namespace broker
{
namespace  cstyle
{
struct AgentUpdateEvent;
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const comm::broker::cstyle::AgentUpdateEvent& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, comm::broker::cstyle::AgentUpdateEvent &val);
}
}

namespace comm
{
namespace broker
{
namespace  cstyle
{

    /**
    \brief struct broker::AgentUpdateEvent.
    */
    struct PROXY_EXPORT AgentUpdateEvent
    {
        public:
            AgentUpdateEvent()
            : m_agent_id()
            , m_agent_epoch()
            { }

            AgentUpdateEvent (const AgentUpdateEvent& other)
            : m_agent_id()
            , m_agent_epoch()
            {
              *this = other;
            }

            ~AgentUpdateEvent () {
            }
            bool operator==(const AgentUpdateEvent& rhs) const {
                bool equal = true;
                if (m_agent_id != rhs.m_agent_id)
                    equal = false;
                if (m_agent_epoch != rhs.m_agent_epoch)
                    equal = false;
                return equal;
            }
            bool operator!=(const AgentUpdateEvent& rhs) const {
                return !operator==(rhs);
            }

            AgentUpdateEvent& operator = (const AgentUpdateEvent& src) {
                if (this == &src) return *this;
                m_agent_id = src.m_agent_id;
                m_agent_epoch = src.m_agent_epoch;
                return *this;
            }

                void setagent_id(const uint16_t _value) {
                    m_agent_id = _value;
                }
                uint16_t getagent_id() const {
                    return m_agent_id;
                }
                void setagent_epoch(const uint16_t _value) {
                    m_agent_epoch = _value;
                }
                uint16_t getagent_epoch() const {
                    return m_agent_epoch;
                }


        uint16_t m_agent_id;
        uint16_t m_agent_epoch;
    private:
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const comm::broker::cstyle::AgentUpdateEvent& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, comm::broker::cstyle::AgentUpdateEvent &val);
    };

} // cstyle
}//namespace comm
}//namespace broker

#endif// COMM_BROKER_AGENTUPDATEEVENT_CSTYLE_HXX
