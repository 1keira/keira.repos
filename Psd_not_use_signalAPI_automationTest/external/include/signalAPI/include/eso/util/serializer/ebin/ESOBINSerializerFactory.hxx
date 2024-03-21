/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_SERIALIZER_ESOBIN_FACTORY_HXX
#define UTIL_SERIALIZER_ESOBIN_FACTORY_HXX

#include <util/serializer/factory/ISerializerFactory.hxx>
#include <util/serializer/ebin/ESOBinStructuredSerializerBE.hxx>
#include <util/serializer/ebin/ESOBinStructuredPullDeserializer.hxx>
#include <util/serializer/ebin/ESOBinStructuredPushDeserializer.hxx>


namespace util
{
namespace serializer
{
namespace esobin
{

class ESOBINSerializerFactory : public factory::ISerializerFactory {

public:
    ESOBINSerializerFactory() = default;
    ~ESOBINSerializerFactory() override = default;

    Serializer createSerializer() override
    {
        return std::make_unique<ESOBinStructuredSerializerBE>();
    }
    PullDeserializer createPullDeserializer() override
    {
        return std::make_unique<ESOBinStructuredPullDeserializer>(ESOBinStructuredSerializer::Endianess::BE_SERIALIZATION);
    }

    PushDeserializer createPushDeserializer() override
    {
        return std::make_unique<ESOBinStructuredPushDeserializer>(ESOBinStructuredSerializer::Endianess::BE_SERIALIZATION);
    }

    ApiCapabilities getCapabilities() override
    {
        return ApiCapability::deserializerControlsFieldOrder | ApiCapability::applicationControlsFieldOrder | ApiCapability::hasPushDeserializer;
    }
};

} //esobin
} //serializer
} //util

#endif
