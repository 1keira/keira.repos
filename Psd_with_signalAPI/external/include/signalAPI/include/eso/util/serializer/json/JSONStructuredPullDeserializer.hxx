/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_SERIALIZER_JSONSTRUCTUREDPULLDESERIALIZER_HXX
#define UTIL_SERIALIZER_JSONSTRUCTUREDPULLDESERIALIZER_HXX

#include <util/serializer/json/JSONStructuredPushDeserializer.hxx>
#include <util/serializer/PullFromPushDeserializer.hxx>

namespace util
{
namespace serializer
{

/*! \brief provides a well-usable interface for JSON deserializing for use cases where the JSON structure is roughly known in advance
 */
class
IPL_DEPRECATED_PRE("use JSONStructuredPullDeserializer instead.")
RapidJsonStructuredPullDeserializer : public PullFromPushDeserializer
{
    IPL_DISABLE_WARNING_PUSH
    IPL_DISABLE_WARNING_DEPRECATION
    util::serializer::RapidJsonStructuredPushDeserializer m_deser_push;
    IPL_DISABLE_WARNING_POP
public:
    RapidJsonStructuredPullDeserializer(): PullFromPushDeserializer(m_deser_push) {}
}
IPL_DEPRECATED_POST("use JSONStructuredPullDeserializer instead.")
;

#define ENABLE_JSONStructuredPullDeserializerOld
#ifdef ENABLE_JSONStructuredPullDeserializerOld

class JSONStructuredPullDeserializerOld : public PullFromPushDeserializer
{
    util::serializer::JSONStructuredPushDeserializerOld m_deser_push;
public:
    JSONStructuredPullDeserializerOld(): PullFromPushDeserializer(m_deser_push) {}
};

typedef JSONStructuredPullDeserializerOld JSONStructuredPullDeserializer;
#else
typedef RapidJsonStructuredPullDeserializer JSONStructuredPullDeserializer;
#endif

} /* namespace serializer */
} /* namespace util */

#endif /* UTIL_SERIALIZER_JSONSTRUCTUREDPULLDESERIALIZER_HXX */

