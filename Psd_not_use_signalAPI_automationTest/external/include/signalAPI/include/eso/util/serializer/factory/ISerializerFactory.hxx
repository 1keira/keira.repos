/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_SERIALIZER_ISERIALIZER_FACTORY_HXX
#define UTIL_SERIALIZER_ISERIALIZER_FACTORY_HXX

#include <util/serializer/IStructuredPullDeserializer.hxx>
#include <util/serializer/IStructuredSerializer.hxx>
#include <util/serializer/IStructuredPushDeserializer.hxx>
#include <util/serializer/ApiCapability.hxx>

namespace util {

namespace serializer {

namespace factory {

class ISerializerFactory {

public:

    using Serializer = std::unique_ptr<IStructuredSerializer>;
    using PullDeserializer = std::unique_ptr<IStructuredPullDeserializer>;
    using PushDeserializer = std::unique_ptr<IStructuredPushDeserializer>;


    ISerializerFactory() = default;
    virtual ~ISerializerFactory() = default;

    virtual Serializer createSerializer() = 0;
    virtual PullDeserializer createPullDeserializer() = 0;
    virtual PushDeserializer createPushDeserializer() = 0;
    virtual ApiCapabilities getCapabilities() = 0;

};

} // namespace factory
} // namespace serializer
} // namespace util

#endif
