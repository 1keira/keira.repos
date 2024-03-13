/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleSerializer_hxx.tmpl
*/
#ifndef ASI_VEHICLE_SERIALIZER_CSTYLE_HXX
#define ASI_VEHICLE_SERIALIZER_CSTYLE_HXX

#include <comm/comm_dso.h>
#include <comm/commidltypes.hxx>
#include <common/types/vector.hxx>
#include <asi/vehicle/cstyle/StructKlemmenStatus01Struct.hxx>
#include <util/serializer/IStructuredSerializer.hxx>
#include <util/serializer/IStructuredPullDeserializer.hxx>

namespace asi
{
namespace vehicle
{
namespace  cstyle
{
struct KlemmenStatus01Struct;
} // cstyle
} // namespace asi
} // namespace vehicle

namespace util
{
    namespace serializer
    {

    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::vehicle::cstyle::KlemmenStatus01Struct& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::vehicle::cstyle::KlemmenStatus01Struct &val);

    }  // end of namespace serializer
}  // end of namespace util

#endif// ASI_VEHICLE_SERIALIZER_CSTYLE_HXX
