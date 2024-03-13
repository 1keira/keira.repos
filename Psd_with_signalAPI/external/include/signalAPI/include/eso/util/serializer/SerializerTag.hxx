/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_SERIALIZER_SERIALIZER_TAG_HXX
#define UTIL_SERIALIZER_SERIALIZER_TAG_HXX

#include <util/UInt32Tag.hxx>

namespace util {
namespace serializer {

    enum SerializerTag {
       k_UNDEFINED    = UInt32Tag (0u),
       k_CLASSIC_COMM = UInt32Tag ("CCOM"),
       k_SOMEIP       = UInt32Tag ("SOIP"),
       k_JSON         = UInt32Tag ("JSON"),
       k_BIN          = UInt32Tag ("EBIN"),
    };


} // namespace serializer
} // namespace util

#endif // UTIL_SERIALIZER_SERIALIZER_TAG_HXX
