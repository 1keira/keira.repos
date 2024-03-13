/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleSerializer_hxx.tmpl
*/
#ifndef ASI_SID_V2XSTACK_SERIALIZER_CSTYLE_HXX
#define ASI_SID_V2XSTACK_SERIALIZER_CSTYLE_HXX

#include <comm/comm_dso.h>
#include <comm/commidltypes.hxx>
#include <common/types/vector.hxx>
#include <asi/sid/v2xstack/cstyle/StructESC50Struct.hxx>
#include <asi/sid/v2xstack/cstyle/StructEBKV03AuthStruct.hxx>
#include <asi/sid/v2xstack/cstyle/StructESC51AuthStruct.hxx>
#include <asi/sid/v2xstack/cstyle/StructESP21Struct.hxx>
#include <asi/sid/v2xstack/cstyle/StructLichtAnf01Struct.hxx>
#include <asi/sid/v2xstack/cstyle/StructLichtvorne01Struct.hxx>
#include <asi/sid/v2xstack/cstyle/StructBlinkmodi02Struct.hxx>
#include <asi/sid/v2xstack/cstyle/StructVMM02AuthStruct.hxx>
#include <asi/sid/v2xstack/cstyle/StructESP24Struct.hxx>
#include <asi/sid/v2xstack/cstyle/StructMotor14Struct.hxx>
#include <asi/sid/v2xstack/cstyle/StructLWI01Struct.hxx>
#include <asi/sid/v2xstack/cstyle/StructGetriebe11Struct.hxx>
#include <asi/sid/v2xstack/cstyle/StructKlemmenStatus01Struct.hxx>
#include <asi/sid/v2xstack/cstyle/StructPersonalisierung01Struct.hxx>
#include <util/serializer/IStructuredSerializer.hxx>
#include <util/serializer/IStructuredPullDeserializer.hxx>

namespace asi
{
namespace sid
{
namespace v2xstack
{
namespace  cstyle
{
struct ESC50Struct;
struct EBKV03AuthStruct;
struct ESC51AuthStruct;
struct ESP21Struct;
struct LichtAnf01Struct;
struct Lichtvorne01Struct;
struct Blinkmodi02Struct;
struct VMM02AuthStruct;
struct ESP24Struct;
struct Motor14Struct;
struct LWI01Struct;
struct Getriebe11Struct;
struct KlemmenStatus01Struct;
struct Personalisierung01Struct;
} // cstyle
} // namespace asi
} // namespace sid
} // namespace v2xstack

namespace util
{
    namespace serializer
    {

    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::sid::v2xstack::cstyle::ESC50Struct& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::sid::v2xstack::cstyle::ESC50Struct &val);
    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::sid::v2xstack::cstyle::EBKV03AuthStruct& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::sid::v2xstack::cstyle::EBKV03AuthStruct &val);
    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::sid::v2xstack::cstyle::ESC51AuthStruct& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::sid::v2xstack::cstyle::ESC51AuthStruct &val);
    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::sid::v2xstack::cstyle::ESP21Struct& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::sid::v2xstack::cstyle::ESP21Struct &val);
    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::sid::v2xstack::cstyle::LichtAnf01Struct& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::sid::v2xstack::cstyle::LichtAnf01Struct &val);
    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::sid::v2xstack::cstyle::Lichtvorne01Struct& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::sid::v2xstack::cstyle::Lichtvorne01Struct &val);
    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::sid::v2xstack::cstyle::Blinkmodi02Struct& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::sid::v2xstack::cstyle::Blinkmodi02Struct &val);
    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::sid::v2xstack::cstyle::VMM02AuthStruct& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::sid::v2xstack::cstyle::VMM02AuthStruct &val);
    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::sid::v2xstack::cstyle::ESP24Struct& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::sid::v2xstack::cstyle::ESP24Struct &val);
    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::sid::v2xstack::cstyle::Motor14Struct& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::sid::v2xstack::cstyle::Motor14Struct &val);
    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::sid::v2xstack::cstyle::LWI01Struct& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::sid::v2xstack::cstyle::LWI01Struct &val);
    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::sid::v2xstack::cstyle::Getriebe11Struct& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::sid::v2xstack::cstyle::Getriebe11Struct &val);
    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::sid::v2xstack::cstyle::KlemmenStatus01Struct& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::sid::v2xstack::cstyle::KlemmenStatus01Struct &val);
    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::sid::v2xstack::cstyle::Personalisierung01Struct& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::sid::v2xstack::cstyle::Personalisierung01Struct &val);

    }  // end of namespace serializer
}  // end of namespace util

#endif// ASI_SID_V2XSTACK_SERIALIZER_CSTYLE_HXX
