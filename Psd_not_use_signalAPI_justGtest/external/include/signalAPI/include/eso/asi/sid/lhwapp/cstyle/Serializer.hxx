/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleSerializer_hxx.tmpl
*/
#ifndef ASI_SID_LHWAPP_SERIALIZER_CSTYLE_HXX
#define ASI_SID_LHWAPP_SERIALIZER_CSTYLE_HXX

#include <comm/comm_dso.h>
#include <comm/commidltypes.hxx>
#include <common/types/vector.hxx>
#include <asi/sid/lhwapp/cstyle/StructAirbag01Struct.hxx>
#include <asi/sid/lhwapp/cstyle/StructBlinkmodi02Struct.hxx>
#include <asi/sid/lhwapp/cstyle/StructDaempfer01Struct.hxx>
#include <asi/sid/lhwapp/cstyle/StructESC50Struct.hxx>
#include <asi/sid/lhwapp/cstyle/StructESP21Struct.hxx>
#include <asi/sid/lhwapp/cstyle/StructESP24Struct.hxx>
#include <asi/sid/lhwapp/cstyle/StructESP30Struct.hxx>
#include <asi/sid/lhwapp/cstyle/StructHVK01Struct.hxx>
#include <asi/sid/lhwapp/cstyle/StructMotor18Struct.hxx>
#include <asi/sid/lhwapp/cstyle/StructMotor41Struct.hxx>
#include <asi/sid/lhwapp/cstyle/StructPOSGNSSDR01Struct.hxx>
#include <asi/sid/lhwapp/cstyle/StructPSD04Struct.hxx>
#include <asi/sid/lhwapp/cstyle/StructPSD05Struct.hxx>
#include <asi/sid/lhwapp/cstyle/StructPSD06Struct.hxx>
#include <asi/sid/lhwapp/cstyle/StructRKA01Struct.hxx>
#include <util/serializer/IStructuredSerializer.hxx>
#include <util/serializer/IStructuredPullDeserializer.hxx>

namespace asi
{
namespace sid
{
namespace lhwapp
{
namespace  cstyle
{
struct Airbag01Struct;
struct Blinkmodi02Struct;
struct Daempfer01Struct;
struct ESC50Struct;
struct ESP21Struct;
struct ESP24Struct;
struct ESP30Struct;
struct HVK01Struct;
struct Motor18Struct;
struct Motor41Struct;
struct POSGNSSDR01Struct;
struct PSD04Struct;
struct PSD05Struct;
struct PSD06Struct;
struct RKA01Struct;
} // cstyle
} // namespace asi
} // namespace sid
} // namespace lhwapp

namespace util
{
    namespace serializer
    {

    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::sid::lhwapp::cstyle::Airbag01Struct& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::sid::lhwapp::cstyle::Airbag01Struct &val);
    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::sid::lhwapp::cstyle::Blinkmodi02Struct& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::sid::lhwapp::cstyle::Blinkmodi02Struct &val);
    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::sid::lhwapp::cstyle::Daempfer01Struct& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::sid::lhwapp::cstyle::Daempfer01Struct &val);
    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::sid::lhwapp::cstyle::ESC50Struct& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::sid::lhwapp::cstyle::ESC50Struct &val);
    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::sid::lhwapp::cstyle::ESP21Struct& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::sid::lhwapp::cstyle::ESP21Struct &val);
    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::sid::lhwapp::cstyle::ESP24Struct& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::sid::lhwapp::cstyle::ESP24Struct &val);
    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::sid::lhwapp::cstyle::ESP30Struct& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::sid::lhwapp::cstyle::ESP30Struct &val);
    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::sid::lhwapp::cstyle::HVK01Struct& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::sid::lhwapp::cstyle::HVK01Struct &val);
    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::sid::lhwapp::cstyle::Motor18Struct& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::sid::lhwapp::cstyle::Motor18Struct &val);
    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::sid::lhwapp::cstyle::Motor41Struct& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::sid::lhwapp::cstyle::Motor41Struct &val);
    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::sid::lhwapp::cstyle::POSGNSSDR01Struct& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::sid::lhwapp::cstyle::POSGNSSDR01Struct &val);
    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::sid::lhwapp::cstyle::PSD04Struct& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::sid::lhwapp::cstyle::PSD04Struct &val);
    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::sid::lhwapp::cstyle::PSD05Struct& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::sid::lhwapp::cstyle::PSD05Struct &val);
    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::sid::lhwapp::cstyle::PSD06Struct& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::sid::lhwapp::cstyle::PSD06Struct &val);
    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::sid::lhwapp::cstyle::RKA01Struct& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::sid::lhwapp::cstyle::RKA01Struct &val);

    }  // end of namespace serializer
}  // end of namespace util

#endif// ASI_SID_LHWAPP_SERIALIZER_CSTYLE_HXX
