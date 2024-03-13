/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Serializer_hxx.tmpl
*/
#ifndef ASI_SID_V2XSTACK_SERIALIZER_HXX
#define ASI_SID_V2XSTACK_SERIALIZER_HXX

#include <comm/comm_dso.h>
// serializer for types from other IDL files
// own types
#include <asi/sid/v2xstack/StructESC50Struct.hxx>
#include <asi/sid/v2xstack/StructEBKV03AuthStruct.hxx>
#include <asi/sid/v2xstack/StructESC51AuthStruct.hxx>
#include <asi/sid/v2xstack/StructESP21Struct.hxx>
#include <asi/sid/v2xstack/StructLichtAnf01Struct.hxx>
#include <asi/sid/v2xstack/StructLichtvorne01Struct.hxx>
#include <asi/sid/v2xstack/StructBlinkmodi02Struct.hxx>
#include <asi/sid/v2xstack/StructVMM02AuthStruct.hxx>
#include <asi/sid/v2xstack/StructESP24Struct.hxx>
#include <asi/sid/v2xstack/StructMotor14Struct.hxx>
#include <asi/sid/v2xstack/StructLWI01Struct.hxx>
#include <asi/sid/v2xstack/StructGetriebe11Struct.hxx>
#include <asi/sid/v2xstack/StructKlemmenStatus01Struct.hxx>
#include <asi/sid/v2xstack/StructPersonalisierung01Struct.hxx>
#include <comm/commidltypes.hxx>
#include <util/serializer/IStructuredPullDeserializer.hxx>
#include <util/serializer/IStructuredSerializer.hxx>

namespace util
{
    namespace serializer
    {

    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::sid::v2xstack::ESC50Struct& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::sid::v2xstack::ESC50Struct &val);
    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::sid::v2xstack::EBKV03AuthStruct& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::sid::v2xstack::EBKV03AuthStruct &val);
    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::sid::v2xstack::ESC51AuthStruct& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::sid::v2xstack::ESC51AuthStruct &val);
    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::sid::v2xstack::ESP21Struct& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::sid::v2xstack::ESP21Struct &val);
    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::sid::v2xstack::LichtAnf01Struct& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::sid::v2xstack::LichtAnf01Struct &val);
    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::sid::v2xstack::Lichtvorne01Struct& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::sid::v2xstack::Lichtvorne01Struct &val);
    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::sid::v2xstack::Blinkmodi02Struct& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::sid::v2xstack::Blinkmodi02Struct &val);
    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::sid::v2xstack::VMM02AuthStruct& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::sid::v2xstack::VMM02AuthStruct &val);
    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::sid::v2xstack::ESP24Struct& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::sid::v2xstack::ESP24Struct &val);
    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::sid::v2xstack::Motor14Struct& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::sid::v2xstack::Motor14Struct &val);
    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::sid::v2xstack::LWI01Struct& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::sid::v2xstack::LWI01Struct &val);
    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::sid::v2xstack::Getriebe11Struct& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::sid::v2xstack::Getriebe11Struct &val);
    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::sid::v2xstack::KlemmenStatus01Struct& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::sid::v2xstack::KlemmenStatus01Struct &val);
    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::sid::v2xstack::Personalisierung01Struct& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::sid::v2xstack::Personalisierung01Struct &val);

    }  // end of namespace serializer
}  // end of namespace util

#endif// ASI_SID_V2XSTACK_DEFINITIONS_HXX
