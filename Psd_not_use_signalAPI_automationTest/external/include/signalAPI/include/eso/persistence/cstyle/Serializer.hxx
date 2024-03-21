/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleSerializer_hxx.tmpl
*/
#ifndef PERSISTENCE_SERIALIZER_CSTYLE_HXX
#define PERSISTENCE_SERIALIZER_CSTYLE_HXX

#include <comm/comm_dso.h>
#include <comm/commidltypes.hxx>
#include <common/types/vector.hxx>
#include <persistence/cstyle/StructPartitionHandle.hxx>
#include <util/serializer/IStructuredSerializer.hxx>
#include <util/serializer/IStructuredPullDeserializer.hxx>

namespace persistence
{
namespace  cstyle
{
struct PartitionHandle;
} // cstyle
} // namespace persistence

namespace util
{
    namespace serializer
    {

    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const persistence::cstyle::PartitionHandle& val);
    bool deserialize (IStructuredPullDeserializer &s, persistence::cstyle::PartitionHandle &val);

    }  // end of namespace serializer
}  // end of namespace util

#endif// PERSISTENCE_SERIALIZER_CSTYLE_HXX
