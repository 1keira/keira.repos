/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Serializer_hxx.tmpl
*/
#ifndef ASI_VEHICLE_SERIALIZER_HXX
#define ASI_VEHICLE_SERIALIZER_HXX

#include <comm/comm_dso.h>
// serializer for types from other IDL files
// own types
#include <asi/vehicle/StructKlemmenStatus01Struct.hxx>
#include <comm/commidltypes.hxx>
#include <util/serializer/IStructuredPullDeserializer.hxx>
#include <util/serializer/IStructuredSerializer.hxx>

namespace util
{
    namespace serializer
    {

    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::vehicle::KlemmenStatus01Struct& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::vehicle::KlemmenStatus01Struct &val);

    }  // end of namespace serializer
}  // end of namespace util

#endif// ASI_VEHICLE_DEFINITIONS_HXX
