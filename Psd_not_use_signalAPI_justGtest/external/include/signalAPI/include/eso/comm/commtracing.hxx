/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/
#ifndef COMM_COMMTRACING_HXX
#define COMM_COMMTRACING_HXX

#include <common/tracing/tracing.hxx>
#include <common/tracing/MessageTypes.hxx>
#include <comm/comm_dso.h>
#include <comm/commtypes.hxx>
#include <util/serializer/serializer.hxx>
#include <util/serializer/SerializerTag.hxx>

#include <memory>
#include <cstddef>
#include <cstdint>

namespace comm {

class Connection;
using ConnectionPtr = std::shared_ptr<Connection>;
class Proxy;
struct ProxyState;

enum CommTracingContent {
    COMM_TRACING_CONTENT_ALL,
    COMM_TRACING_CONTENT_METHODS,
    COMM_TRACING_CONTENT_NONE
};

COMM_EXPORT extern uint16_t COMM_TRACING_UNDEFINED_AGENT_ID;
COMM_EXPORT extern uint16_t COMM_TRACING_UNDEFINED_ENTITY_ID;
COMM_EXPORT extern uint32_t COMM_TRACING_UNDEFINED_SEQ_NUMBER;
COMM_EXPORT extern bool COMM_TRACING_IS_REQUEST;
COMM_EXPORT extern bool COMM_TRACING_IS_REPLY;


#ifndef NTRACE

// updated signatures for comm v7, tracing header v3
void COMM_EXPORT traceCOMMProxy(util::UInt32Tag         ser_tag
                    ,comm::AgentID                      peer_agent
                    ,comm::StubID                       sid
                    ,const comm::ProxyState*            pstate
                    ,comm::V7MethodID                   method_id
                    ,bool                               is_reply
                    ,size_t                             data_size
                    ,const uint8_t*                     data
                    ,tracing::Channel*                  trace_channel
                    ,bool                               only_method_calls=false
                    );

void COMM_EXPORT traceCOMMStub (util::UInt32Tag         ser_tag
                    ,const comm::CallContext&           ctx
                    ,comm::V7MethodID                   method_id
                    ,const comm::Proxy&                 reply_proxy
                    ,bool                               is_reply
                    ,size_t                             data_size
                    ,const uint8_t*                     data
                    ,tracing::Channel*                  trace_channel
                    ,bool                               only_method_calls=false
                    );

#endif

}
#endif // COMM_COMMTRACING_HXX
