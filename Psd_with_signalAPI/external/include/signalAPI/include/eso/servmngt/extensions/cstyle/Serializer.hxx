/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleSerializer_hxx.tmpl
*/
#ifndef SERVMNGT_EXTENSIONS_SERIALIZER_CSTYLE_HXX
#define SERVMNGT_EXTENSIONS_SERIALIZER_CSTYLE_HXX

#include <comm/comm_dso.h>
#include <comm/commidltypes.hxx>
#include <common/types/vector.hxx>
#include <servmngt/extensions/cstyle/StructWatchdogMissedEvent.hxx>
#include <util/serializer/IStructuredSerializer.hxx>
#include <util/serializer/IStructuredPullDeserializer.hxx>

namespace servmngt
{
namespace extensions
{
namespace  cstyle
{
struct WatchdogMissedEvent;
} // cstyle
} // namespace servmngt
} // namespace extensions

namespace util
{
    namespace serializer
    {

    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const servmngt::extensions::cstyle::WatchdogMissedEvent& val);
    bool deserialize (IStructuredPullDeserializer &s, servmngt::extensions::cstyle::WatchdogMissedEvent &val);

    }  // end of namespace serializer
}  // end of namespace util

#endif// SERVMNGT_EXTENSIONS_SERIALIZER_CSTYLE_HXX
