/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Serializer_hxx.tmpl
*/
#ifndef PERSISTENCE_SERIALIZER_HXX
#define PERSISTENCE_SERIALIZER_HXX

#include <comm/comm_dso.h>
// serializer for types from other IDL files
// own types
#include <persistence/StructPartitionHandle.hxx>
#include <comm/commidltypes.hxx>
#include <util/serializer/IStructuredPullDeserializer.hxx>
#include <util/serializer/IStructuredSerializer.hxx>

namespace util
{
    namespace serializer
    {

    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, persistence::PartitionHandle& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, persistence::PartitionHandle &val);

    }  // end of namespace serializer
}  // end of namespace util

#endif// PERSISTENCE_DEFINITIONS_HXX
