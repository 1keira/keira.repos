/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_SERIALIZER_FACTORY_SERIALIZER_REGISTRY_HXX
#define UTIL_SERIALIZER_FACTORY_SERIALIZER_REGISTRY_HXX
#include <util/serializer/SerializerTag.hxx>
#include <util/serializer/factory/ISerializerFactory.hxx>
#include <shared_mutex>


namespace util {
namespace serializer {
namespace factory {

class UTIL_EXPORT SerializerRegistry {

public:

    using  TagList = std::vector<UInt32Tag>;

    using Serializer = ISerializerFactory::Serializer;
    using PullDeserializer = ISerializerFactory::PullDeserializer;
    using PushDeserializer = ISerializerFactory::PushDeserializer;

    using Deserializer = std::unique_ptr<IStructuredPullDeserializer>;


    // singleton pattern
    static  SerializerRegistry&  getInstance() IPL_NOEXCEPT;


    void getTagList (TagList& list, ApiCapabilities cap) const IPL_NOEXCEPT;

    ISerializerFactory* getFactory(UInt32Tag tag) const IPL_NOEXCEPT;

    Serializer   createSerializer(UInt32Tag tag) const IPL_NOEXCEPT;
    PullDeserializer createPullDeserializer(UInt32Tag tag) const IPL_NOEXCEPT;
    PushDeserializer createPushDeserializer(UInt32Tag tag) const IPL_NOEXCEPT;

     /*!\brief
     * returns a non owning pointer for thread local usage
     * must not be passed to other threads.
     */
    IStructuredPullDeserializer*
    getLocalPullDeserializer(UInt32Tag tag) const IPL_NOEXCEPT;

    /*!\brief
     * returns a non owning pointer for thread local usage
     * must not be passed to other threads.
     */
    IStructuredSerializer*
    getLocalSerializer(UInt32Tag tag) const IPL_NOEXCEPT;



private:
    /// singleton
    SerializerRegistry();
    SerializerRegistry(const SerializerRegistry&) = delete;
    SerializerRegistry& operator= (const SerializerRegistry&) = delete;

    bool registerSerializer(UInt32Tag tag, ISerializerFactory* factory) IPL_NOEXCEPT;

    mutable std::shared_timed_mutex  m_mutex; // protects the map
    std::map<uint32_t, ISerializerFactory*>  m_supportedSerializers;

};

} // namespace factory
} // namespace serializer
} // namespace util

#endif
