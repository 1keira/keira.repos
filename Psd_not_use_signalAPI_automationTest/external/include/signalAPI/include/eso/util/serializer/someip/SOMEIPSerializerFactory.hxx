/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_SERIALIZER_SOMEIP_FACTORY_HXX
#define UTIL_SERIALIZER_SOMEIP_FACTORY_HXX

#include <util/serializer/factory/ISerializerFactory.hxx>
#include <util/serializer/someip/SOMEIPStructuredSerializer.hxx>
#include <util/serializer/someip/SOMEIPPullDeserializer.hxx>


namespace util
{
namespace serializer
{
namespace someip
{

class SOMEIPSerializerFactory : public factory::ISerializerFactory {

public:
    SOMEIPSerializerFactory() = default;
    virtual ~SOMEIPSerializerFactory() = default;

    Serializer createSerializer() override
    {
        return std::make_unique<SOMEIPStructuredSerializer>();
    }
    PullDeserializer createPullDeserializer() override
    {
        return std::make_unique<SOMEIPPullDeserializer>();
    }

    PushDeserializer createPushDeserializer() override
    {
        return nullptr;
    }

    ApiCapabilities getCapabilities() override
    {
        return ApiCapability::applicationControlsFieldOrder;
    }
};

} //comm
} //serializer
} //util

#endif
