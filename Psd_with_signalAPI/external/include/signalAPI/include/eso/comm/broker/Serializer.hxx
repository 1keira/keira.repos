/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Serializer_hxx.tmpl
*/
#ifndef COMM_BROKER_SERIALIZER_HXX
#define COMM_BROKER_SERIALIZER_HXX

#include <comm/comm_dso.h>
// serializer for types from other IDL files
// own types
#include <comm/broker/StructUUID844412Blob.hxx>
#include <comm/broker/StructInstanceID.hxx>
#include <comm/broker/StructUpdateEvent.hxx>
#include <comm/broker/StructAgentUpdateEvent.hxx>
#include <comm/commidltypes.hxx>
#include <util/serializer/IStructuredPullDeserializer.hxx>
#include <util/serializer/IStructuredSerializer.hxx>

namespace util
{
    namespace serializer
    {

    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, comm::broker::UUID844412Blob& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, comm::broker::UUID844412Blob &val);
    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, comm::broker::InstanceID& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, comm::broker::InstanceID &val);
    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, comm::broker::UpdateEvent& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, comm::broker::UpdateEvent &val);
    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, comm::broker::AgentUpdateEvent& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, comm::broker::AgentUpdateEvent &val);

    }  // end of namespace serializer
}  // end of namespace util

#endif// COMM_BROKER_DEFINITIONS_HXX
