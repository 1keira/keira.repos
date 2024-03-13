/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Serializer_hxx.tmpl
*/
#ifndef SERVMNGT_EXTENSIONS_SERIALIZER_HXX
#define SERVMNGT_EXTENSIONS_SERIALIZER_HXX

#include <comm/comm_dso.h>
// serializer for types from other IDL files
// own types
#include <servmngt/extensions/StructWatchdogMissedEvent.hxx>
#include <comm/commidltypes.hxx>
#include <util/serializer/IStructuredPullDeserializer.hxx>
#include <util/serializer/IStructuredSerializer.hxx>

namespace util
{
    namespace serializer
    {

    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, servmngt::extensions::WatchdogMissedEvent& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, servmngt::extensions::WatchdogMissedEvent &val);

    }  // end of namespace serializer
}  // end of namespace util

#endif// SERVMNGT_EXTENSIONS_DEFINITIONS_HXX
