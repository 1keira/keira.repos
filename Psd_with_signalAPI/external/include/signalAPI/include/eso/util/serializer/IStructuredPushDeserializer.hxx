/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_SERIALIZER_ISTRUCTUREDPUSHDESERIALIZER_HXX
#define UTIL_SERIALIZER_ISTRUCTUREDPUSHDESERIALIZER_HXX

#include <util/util_dso.h>
#include <util/ByteBuffer.hxx>
#include <util/serializer/IStructuredSerializer.hxx>

namespace util
{
namespace serializer
{

/*! \brief deserializes a data stream into putTYPE method calls of an IStructuredSerializer in one single step */
class UTIL_EXPORT IStructuredPushDeserializerSinglePass {
    public:
        IStructuredPushDeserializerSinglePass() IPL_NOEXCEPT
        : m_reader(NULL)
        , m_target(NULL)
        {}

        enum DeserializerResult {
            DeserializeDone,
            DeserializeContinue,  /*!< only applicable to results of IStructuredPushDeserializer::deserializeStep */
            DeserializeFailed
        };

        virtual ~IStructuredPushDeserializerSinglePass() IPL_NOEXCEPT {}
        virtual bool beginDeserialize(util::ByteBufferReader* reader, IStructuredSerializer* target) IPL_NOEXCEPT = 0;

        virtual bool endDeserialize() IPL_NOEXCEPT = 0;

        virtual DeserializerResult deserialize() IPL_NOEXCEPT = 0;

    protected:
        util::ByteBufferReader* m_reader;
        IStructuredSerializer*  m_target;

};

/*! \brief deserializes a data stream into putTYPE method calls of an IStructuredSerializer either in one single or in many small steps */
class UTIL_EXPORT IStructuredPushDeserializer : public IStructuredPushDeserializerSinglePass {
    public:
        IStructuredPushDeserializer() IPL_NOEXCEPT
        : IStructuredPushDeserializerSinglePass()
        {}

        virtual ~IStructuredPushDeserializer() IPL_NOEXCEPT override {}
        virtual bool beginDeserialize(util::ByteBufferReader* reader, IStructuredSerializer* target) IPL_NOEXCEPT override = 0;

        virtual bool endDeserialize() IPL_NOEXCEPT override = 0;

        virtual DeserializerResult deserialize() IPL_NOEXCEPT override = 0;

        /*!
         *  \brief reads the next token from the input buffer and calls one method on the IStructuredSerializer target
         *
         *  \return DeserializeContinue if there are more steps to perform, DeserializeDone in case the last token is read
         */
        virtual DeserializerResult deserializeStep() IPL_NOEXCEPT = 0;
};


} /* namespace serializer */
} /* namespace util */

#endif
