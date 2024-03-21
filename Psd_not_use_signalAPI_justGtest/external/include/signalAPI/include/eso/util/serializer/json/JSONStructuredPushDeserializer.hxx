/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_SERIALIZER_JSONSTRUCTUREDPUSHDESERIALIZER_HXX
#define UTIL_SERIALIZER_JSONSTRUCTUREDPUSHDESERIALIZER_HXX

#include <stack>
#include <util/util_dso.h>
#include <util/ByteBuffer.hxx>
#include <util/serializer/IStructuredPushDeserializer.hxx>
#include <util/serializer/StructuredPushDeserializerStepAdapter.hxx>

namespace util
{
namespace serializer
{

/*! \brief deserializes a json stream to a IStructuredSerializer; does not support the deserializeStep() method.
 *
 *  \details if deserializeStep is needed, use the StructuredPushDeserializerStepAdapter.
 *  \see StructuredPushDeserializerStepAdapter
 */
class UTIL_EXPORT JSONStructuredPushDeserializerSinglePass : public IStructuredPushDeserializerSinglePass {
public:
    JSONStructuredPushDeserializerSinglePass() IPL_NOEXCEPT : IStructuredPushDeserializerSinglePass()
    {}

    virtual ~JSONStructuredPushDeserializerSinglePass() IPL_NOEXCEPT override
    {}

    virtual bool beginDeserialize(util::ByteBufferReader* reader, IStructuredSerializer* target) IPL_NOEXCEPT override;

    virtual bool endDeserialize() IPL_NOEXCEPT override;

    virtual IStructuredPushDeserializer::DeserializerResult deserialize() IPL_NOEXCEPT override;
};

/*! \brief provides a JSON deserializing interface for use cases where the application expects callbacks for each token
 */
class
IPL_DEPRECATED_PRE("use JsonStructuredPushDeserializer instead.")
RapidJsonStructuredPushDeserializer : public StructuredPushDeserializerStepAdapter
{
    IPL_DISABLE_WARNING_PUSH
    IPL_DISABLE_WARNING_DEPRECATION
    util::serializer::JSONStructuredPushDeserializerSinglePass m_deser_singlepass;
    IPL_DISABLE_WARNING_POP
public:
    RapidJsonStructuredPushDeserializer(): StructuredPushDeserializerStepAdapter(m_deser_singlepass) {}
}
IPL_DEPRECATED_POST("use JsonStructuredPushDeserializer instead.")
;

#define ENABLE_JSONStructuredPushDeserializerOld
#ifdef ENABLE_JSONStructuredPushDeserializerOld

class UTIL_EXPORT JSONStructuredPushDeserializerOld : public IStructuredPushDeserializer {
    public:
        JSONStructuredPushDeserializerOld() IPL_NOEXCEPT
        : m_current_state(StateIdle)
        , m_is_first{false}
        , m_is_string{false} 
        {}
        
        ~JSONStructuredPushDeserializerOld() IPL_NOEXCEPT {}

        virtual bool beginDeserialize(util::ByteBufferReader* reader, IStructuredSerializer* target) IPL_NOEXCEPT;
        virtual bool endDeserialize() IPL_NOEXCEPT;
        virtual DeserializerResult deserialize() IPL_NOEXCEPT;
        virtual DeserializerResult deserializeStep() IPL_NOEXCEPT;

    private:
        enum State {
            StateIdle,
            StateCollectDictField,
            StateCollectDictSep,
            StateCollectDictValue,
            StateReportDictEndField,
            StateReportDictBegin,
            StateReportArrayBegin,
            StateReportArrayElement,
            StateReportArrayEndElement,
            StateCollectDictNext,
            StateCollectDictEnd,
            StateCollectArrayValue,
            StateCollectArrayNext,
            StateCollectArrayEnd,
        };

        bool arrayEnd();
        bool structEnd();

        // get next element from the stream
        bool getElement(std::string& e, bool& is_string);
        char getToken();
        char peekToken();
        // guess the type of the element and reported it to the target
        bool putElement(std::string& element, bool is_string);

        State               m_current_state;
        bool                m_is_first;
        std::stack<State>   m_states;

        std::string         m_key;

        std::string         m_current_element;
        bool                m_is_string;
};

typedef JSONStructuredPushDeserializerOld JSONStructuredPushDeserializer;
#else
typedef RapidJsonStructuredPushDeserializer JSONStructuredPushDeserializer;
#endif

} /* namespace serializer */
} /* namespace util */

#endif
