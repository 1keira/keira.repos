/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_SERIALIZER_APICAPABILITY_HXX
#define UTIL_SERIALIZER_APICAPABILITY_HXX


namespace util {

namespace serializer {

    /*! @brief defines the ApiCapability of a a structured serializer
     *
     */
enum ApiCapability {
   deserializerControlsFieldOrder = 1,  // deserializer controls fields to be deserialized
   applicationControlsFieldOrder = 2,   // application controls fields to be deserialized
   hasPushDeserializer = 4              // has implemented a pushDeserializer
};

using ApiCapabilities = uint32_t; // bitmap of enum ApiCapability

} // namespace serializer
} // namespace util

#endif
