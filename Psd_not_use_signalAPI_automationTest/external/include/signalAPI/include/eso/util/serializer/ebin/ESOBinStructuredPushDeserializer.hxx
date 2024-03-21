/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_SERIALIZER_ESOBINSTRUCTUREDPUSHDESERIALIZER_HXX
#define UTIL_SERIALIZER_ESOBINSTRUCTUREDPUSHDESERIALIZER_HXX

#include <stack>
#include <util/util_dso.h>
#include <util/ByteBuffer.hxx>
#include <util/serializer/IStructuredPushDeserializer.hxx>
#include <util/serializer/ebin/ESOBinDeserializer.hxx>
#include <util/serializer/ebin/ESOBinStructuredSerializer.hxx>

namespace util
{
namespace serializer
{

class UTIL_EXPORT ESOBinStructuredPushDeserializer : public IStructuredPushDeserializer {
    public:
        ESOBinStructuredPushDeserializer(ESOBinStructuredSerializer::Endianess endianess) IPL_NOEXCEPT;
        ~ESOBinStructuredPushDeserializer() IPL_NOEXCEPT;
        ESOBinStructuredPushDeserializer(const ESOBinStructuredPushDeserializer&) = delete;
        ESOBinStructuredPushDeserializer& operator=(const ESOBinStructuredPushDeserializer&) = delete;

        virtual bool beginDeserialize(util::ByteBufferReader* reader, IStructuredSerializer* target) IPL_NOEXCEPT;
        virtual bool endDeserialize() IPL_NOEXCEPT;
        virtual DeserializerResult deserialize() IPL_NOEXCEPT;
        virtual DeserializerResult deserializeStep() IPL_NOEXCEPT;

    private:
        enum State {
            StateIdle,
            StateFinished,
            StateCollectDictField,
            StateCollectDictValue,
            StateReportDictEndField,
            StateReportDictBegin,
            StateReportArrayBegin,
            StateReportArrayElement,
            StateReportArrayEndElement,
            StateCollectDictEnd,
            StateCollectArrayValue,
            StateCollectArrayEnd,
            StateCollectNullArray,
            StateCollectBooleanArray,
            StateCollectInt8Array,
            StateCollectUInt8Array,
            StateCollectInt16Array,
            StateCollectUInt16Array,
            StateCollectInt32Array,
            StateCollectUInt32Array,
            StateCollectInt64Array,
            StateCollectUInt64Array,
            StateCollectFloatArray,
            StateCollectDoubleArray,
            StateCollectStringArray,
        };

        bool typedArrayEnd();
        bool arrayEnd();
        bool structEnd();

        // get next element from the stream
        bool pushValue(char token);
        char getToken();

        ESOBinDeserializer*             m_deser;

        State                           m_current_state;
        std::stack<State>               m_states;

        char                            m_current_token;
};

} /* namespace serializer */
} /* namespace util */

#endif
