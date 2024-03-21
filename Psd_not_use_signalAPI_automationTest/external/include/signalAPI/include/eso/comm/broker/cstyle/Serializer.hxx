/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleSerializer_hxx.tmpl
*/
#ifndef COMM_BROKER_SERIALIZER_CSTYLE_HXX
#define COMM_BROKER_SERIALIZER_CSTYLE_HXX

#include <comm/comm_dso.h>
#include <comm/commidltypes.hxx>
#include <common/types/vector.hxx>
#include <comm/broker/cstyle/StructUUID844412Blob.hxx>
#include <comm/broker/cstyle/StructInstanceID.hxx>
#include <comm/broker/cstyle/StructUpdateEvent.hxx>
#include <comm/broker/cstyle/StructAgentUpdateEvent.hxx>
#include <util/serializer/IStructuredSerializer.hxx>
#include <util/serializer/IStructuredPullDeserializer.hxx>

namespace comm
{
namespace broker
{
namespace  cstyle
{
struct UUID844412Blob;
struct InstanceID;
struct UpdateEvent;
struct AgentUpdateEvent;
} // cstyle
} // namespace comm
} // namespace broker

namespace util
{
    namespace serializer
    {

    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const comm::broker::cstyle::UUID844412Blob& val);
    bool deserialize (IStructuredPullDeserializer &s, comm::broker::cstyle::UUID844412Blob &val);
    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const comm::broker::cstyle::InstanceID& val);
    bool deserialize (IStructuredPullDeserializer &s, comm::broker::cstyle::InstanceID &val);
    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const comm::broker::cstyle::UpdateEvent& val);
    bool deserialize (IStructuredPullDeserializer &s, comm::broker::cstyle::UpdateEvent &val);
    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const comm::broker::cstyle::AgentUpdateEvent& val);
    bool deserialize (IStructuredPullDeserializer &s, comm::broker::cstyle::AgentUpdateEvent &val);

    }  // end of namespace serializer
}  // end of namespace util

#endif// COMM_BROKER_SERIALIZER_CSTYLE_HXX
