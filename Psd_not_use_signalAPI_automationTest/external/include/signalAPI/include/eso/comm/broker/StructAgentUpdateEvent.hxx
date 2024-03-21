/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef COMM_BROKER_AGENTUPDATEEVENT_HXX
#define COMM_BROKER_AGENTUPDATEEVENT_HXX

#include <comm/commidltypes.hxx>
#include <comm/attributes/commattributes.hxx>

#undef unix

namespace comm
{
namespace broker
{

    /**
    \brief struct broker::AgentUpdateEvent.
    */
    struct PROXY_EXPORT AgentUpdateEvent
    {
        uint16_t agent_id; // optional=False
        uint16_t agent_epoch; // optional=False
        private:
            AgentUpdateEvent()
            :
            agent_id(),
            agent_epoch()
            { }
            friend class AgentUpdateEventFactory;
            friend class CIFactory<AgentUpdateEvent>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<comm::broker::AgentUpdateEvent> >;
            friend class ipl::vector<AgentUpdateEvent>;
            friend class ipl::allocator<AgentUpdateEvent>;
#endif
    };

    typedef CIPtrArray<AgentUpdateEvent> CIAgentUpdateEventArray;

    /** \brief factory for broker::AgentUpdateEvent. */
    class PROXY_EXPORT AgentUpdateEventFactory  : CIFactory<AgentUpdateEvent> {
    public:
        static inline CIPtr<AgentUpdateEvent> createAgentUpdateEvent() {
            return CIFactory<AgentUpdateEvent>::createObject();
        }
        static inline void createAgentUpdateEvent(CIPtr<AgentUpdateEvent> & s) {
            CIFactory<AgentUpdateEvent>::createObject(s);
        }
        static inline CIPtr<CIAgentUpdateEventArray> createAgentUpdateEventArray(size_t size) {
            return CIFactory<AgentUpdateEvent>::createArray(size);
        }
        static inline void createAgentUpdateEventArray(CIPtr<CIAgentUpdateEventArray>& a, size_t size) {
            CIFactory<AgentUpdateEvent>::createArray(a, size);
        }
    };
}//namespace comm
}//namespace broker


#endif// COMM_BROKER_AGENTUPDATEEVENT_HXX
