/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_SERIALIZER_COMM_FACTORY_HXX
#define UTIL_SERIALIZER_COMM_FACTORY_HXX

#include <util/serializer/factory/ISerializerFactory.hxx>
#include <util/serializer/comm/EsoCommStructuredSerializer.hxx>
#include <util/serializer/comm/EsoCommPullDeserializer.hxx>


namespace util
{
namespace serializer
{
namespace comm
{

class COMMSerializerFactory : public factory::ISerializerFactory {

public:
    COMMSerializerFactory() = default;
    virtual ~COMMSerializerFactory() = default;

    Serializer createSerializer() override
    {
        return std::make_unique<EsoCommStructuredSerializer>();
    }
    PullDeserializer createPullDeserializer() override
    {
        return std::make_unique<EsoCommPullDeserializer>();
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
