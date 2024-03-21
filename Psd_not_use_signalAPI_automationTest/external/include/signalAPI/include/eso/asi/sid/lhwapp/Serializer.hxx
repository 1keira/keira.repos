/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Serializer_hxx.tmpl
*/
#ifndef ASI_SID_LHWAPP_SERIALIZER_HXX
#define ASI_SID_LHWAPP_SERIALIZER_HXX

#include <comm/comm_dso.h>
// serializer for types from other IDL files
// own types
#include <asi/sid/lhwapp/StructAirbag01Struct.hxx>
#include <asi/sid/lhwapp/StructBlinkmodi02Struct.hxx>
#include <asi/sid/lhwapp/StructDaempfer01Struct.hxx>
#include <asi/sid/lhwapp/StructESC50Struct.hxx>
#include <asi/sid/lhwapp/StructESP21Struct.hxx>
#include <asi/sid/lhwapp/StructESP24Struct.hxx>
#include <asi/sid/lhwapp/StructESP30Struct.hxx>
#include <asi/sid/lhwapp/StructHVK01Struct.hxx>
#include <asi/sid/lhwapp/StructMotor18Struct.hxx>
#include <asi/sid/lhwapp/StructMotor41Struct.hxx>
#include <asi/sid/lhwapp/StructPOSGNSSDR01Struct.hxx>
#include <asi/sid/lhwapp/StructPSD04Struct.hxx>
#include <asi/sid/lhwapp/StructPSD05Struct.hxx>
#include <asi/sid/lhwapp/StructPSD06Struct.hxx>
#include <asi/sid/lhwapp/StructRKA01Struct.hxx>
#include <comm/commidltypes.hxx>
#include <util/serializer/IStructuredPullDeserializer.hxx>
#include <util/serializer/IStructuredSerializer.hxx>

namespace util
{
    namespace serializer
    {

    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::sid::lhwapp::Airbag01Struct& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::sid::lhwapp::Airbag01Struct &val);
    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::sid::lhwapp::Blinkmodi02Struct& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::sid::lhwapp::Blinkmodi02Struct &val);
    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::sid::lhwapp::Daempfer01Struct& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::sid::lhwapp::Daempfer01Struct &val);
    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::sid::lhwapp::ESC50Struct& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::sid::lhwapp::ESC50Struct &val);
    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::sid::lhwapp::ESP21Struct& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::sid::lhwapp::ESP21Struct &val);
    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::sid::lhwapp::ESP24Struct& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::sid::lhwapp::ESP24Struct &val);
    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::sid::lhwapp::ESP30Struct& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::sid::lhwapp::ESP30Struct &val);
    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::sid::lhwapp::HVK01Struct& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::sid::lhwapp::HVK01Struct &val);
    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::sid::lhwapp::Motor18Struct& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::sid::lhwapp::Motor18Struct &val);
    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::sid::lhwapp::Motor41Struct& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::sid::lhwapp::Motor41Struct &val);
    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::sid::lhwapp::POSGNSSDR01Struct& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::sid::lhwapp::POSGNSSDR01Struct &val);
    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::sid::lhwapp::PSD04Struct& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::sid::lhwapp::PSD04Struct &val);
    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::sid::lhwapp::PSD05Struct& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::sid::lhwapp::PSD05Struct &val);
    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::sid::lhwapp::PSD06Struct& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::sid::lhwapp::PSD06Struct &val);
    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::sid::lhwapp::RKA01Struct& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::sid::lhwapp::RKA01Struct &val);

    }  // end of namespace serializer
}  // end of namespace util

#endif// ASI_SID_LHWAPP_DEFINITIONS_HXX
