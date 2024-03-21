/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_SERIALIZER_JSONSTRUCTUREDSERIALIZER_HXX
#define UTIL_SERIALIZER_JSONSTRUCTUREDSERIALIZER_HXX

#include <ipl_config.h>

#include <common/streams/sstream.hxx>
#include <common/types/string.hxx>
#include <common/types/vector.hxx>

#include <util/util_dso.h>
#include <util/serializer/IStructuredSerializer.hxx>
#include <util/ByteBuffer.hxx>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

namespace util
{
namespace serializer
{

class UTIL_EXPORT RapidJsonStructuredSerializer : public IStructuredSerializer {
    public:
        RapidJsonStructuredSerializer() IPL_NOEXCEPT:
            RapidJsonStructuredSerializer(true)
        {}

        /**
         * Constructor accepting a flag whether binary data shall be base64 encoded or not. If false, binary data
         * is represented as fixed string '\<binary\>' in the resulting JSON. Default is true.
         * Be aware: setting the boolean flag to false means losing the actual binary data. No deserialization would be possible.
         * It is only intended for pure output use cases such as tracing.
         * @param base64EncodeBinaryData flag to control automatic base64 encoding in case of binary data to be serialized.
         */
        explicit RapidJsonStructuredSerializer(bool base64EncodeBinaryData) IPL_NOEXCEPT;

        virtual ~RapidJsonStructuredSerializer() IPL_NOEXCEPT override {}

        virtual bool beginSerialize(::util::ByteBufferWriter* buffer, const SerializerOptions* options = nullptr) IPL_NOEXCEPT override;
        virtual bool endSerialize(size_t& number_bytes) IPL_NOEXCEPT override;

        virtual void reset() IPL_NOEXCEPT override;

        virtual size_t size() const IPL_NOEXCEPT override { return m_buffer.size(); }

        //! retrieve the data
        virtual bool get(uint8_t* destination, size_t size, size_t& got) const IPL_NOEXCEPT override;

        // ----- Scalars -----

        virtual bool putNull() IPL_NOEXCEPT override;
        virtual bool putBool(bool b) IPL_NOEXCEPT override;
        virtual bool putInt8(int8_t b) IPL_NOEXCEPT override;
        virtual bool putUInt8(uint8_t b) IPL_NOEXCEPT override;
        virtual bool putInt16(int16_t b) IPL_NOEXCEPT override;
        virtual bool putUInt16(uint16_t b) IPL_NOEXCEPT override;
        virtual bool putInt32(int32_t i) IPL_NOEXCEPT override;
        virtual bool putUInt32(uint32_t i) IPL_NOEXCEPT override;
        virtual bool putInt64(int64_t l) IPL_NOEXCEPT override;
        virtual bool putUInt64(uint64_t l) IPL_NOEXCEPT override;
        virtual bool putFloat(float f) IPL_NOEXCEPT override;
        virtual bool putDouble(double d) IPL_NOEXCEPT override;

        using IStructuredSerializer::putString;
        virtual bool putString(const std::string& str) IPL_NOEXCEPT override;
        virtual bool putString(const ::util::UnicodeString8& str) override { return true; /* deprecated string class */ }
        virtual bool putString(const ::util::UnicodeString16& str) override { return true; /* deprecated string class */ }

        // ----- Arrays -----
        virtual bool putNullArray(size_t size) IPL_NOEXCEPT override;
        virtual bool putBooleanArray(const std::vector<bool>& b) IPL_NOEXCEPT override;
        virtual bool putInt8Array(const std::vector<int8_t>& b) IPL_NOEXCEPT override;
        virtual bool putUInt8Array(const std::vector<uint8_t>& b) IPL_NOEXCEPT override;
        virtual bool putInt16Array(const std::vector<int16_t>& s) IPL_NOEXCEPT override;
        virtual bool putUInt16Array(const std::vector<uint16_t>& s) IPL_NOEXCEPT override;
        virtual bool putInt32Array(const std::vector<int32_t>& i) IPL_NOEXCEPT override;
        virtual bool putUInt32Array(const std::vector<uint32_t>& i) IPL_NOEXCEPT override;
        virtual bool putInt64Array(const std::vector<int64_t>& l) IPL_NOEXCEPT override;
        virtual bool putUInt64Array(const std::vector<uint64_t>& l) IPL_NOEXCEPT override;
        virtual bool putFloatArray(const std::vector<float>& f) IPL_NOEXCEPT override;
        virtual bool putDoubleArray(const std::vector<double>& d) IPL_NOEXCEPT override;
        virtual bool putStringArray(const std::vector<std::string>& s) IPL_NOEXCEPT override;

        // ----- Complex -----

        virtual bool beginArray() IPL_NOEXCEPT override;
        virtual bool endArray() IPL_NOEXCEPT override;

        virtual bool beginStruct(const SerializerOptions* options=nullptr) IPL_NOEXCEPT override;
        virtual bool endStruct() IPL_NOEXCEPT override;

        virtual bool beginField(const std::string& name, int32_t id = NO_ID, bool isOptional=false) IPL_NOEXCEPT override;
        virtual bool endField() IPL_NOEXCEPT override;

        virtual bool beginElement() IPL_NOEXCEPT override;
        virtual bool endElement() IPL_NOEXCEPT override;

    private:
        class BufferAdapter
        {
        public:
            typedef char Ch;

            void start(util::ByteBufferWriter* buffer);
            void end();
            void reset();

            size_t size(void) const;
            size_t get(uint8_t* destination, size_t size) const;

            Ch Peek();
            Ch Take();
            size_t Tell();
            Ch* PutBegin();
            void Put(Ch c);
            void Flush();
            size_t PutEnd(Ch*);
        private:
            util::ByteBufferWriter* buffer = nullptr;
        };

        BufferAdapter m_buffer;
        IPL_RAPIDJSON_NAMESPACE::Writer<BufferAdapter> m_writer;
        bool m_serializing_ongoing;
        bool m_base64EncodeBinaryData;
};

/* ############################## OLD: ############################## */
#define ENABLE_JSONStructuredSerializerOld
#ifdef ENABLE_JSONStructuredSerializerOld
class UTIL_EXPORT JSONStructuredSerializerOld : public IStructuredSerializer {
    public:
        JSONStructuredSerializerOld() IPL_NOEXCEPT
        : JSONStructuredSerializerOld(true)
        {}

        /**
         * Constructor accepting a flag whether binary data shall be base64 encoded or not. If false, binary data
         * is represented as fixed string '\<binary\>' in the resulting JSON. Default is true.
         * Be aware: setting the boolean flag to false means losing the actual binary data. No deserialization would be possible.
         * It is only intended for pure output use cases such as tracing.
         * @param base64EncodeBinaryData flag to control automatic base64 encoding in case of binary data to be serialized.
         */
        explicit JSONStructuredSerializerOld(bool base64EncodeBinaryData) IPL_NOEXCEPT
        : m_writer(NULL)
        , m_state(S_IDLE)
        , m_base64EncodeBinaryData(base64EncodeBinaryData)
        {}

        virtual ~JSONStructuredSerializerOld() IPL_NOEXCEPT {}

        virtual bool beginSerialize(::util::ByteBufferWriter* buffer, const SerializerOptions* opt = nullptr) IPL_NOEXCEPT override;
        virtual bool endSerialize(size_t& number_bytes) IPL_NOEXCEPT override;

        virtual void reset() IPL_NOEXCEPT override;

        virtual size_t size() const IPL_NOEXCEPT override { return m_writer ? m_writer->size() : 0; }

        //! retrieve the data
        virtual bool get(uint8_t* destination, size_t size, size_t& got) const IPL_NOEXCEPT override;

        // ----- Scalars -----

        virtual bool putNull() IPL_NOEXCEPT override;
        virtual bool putBool(bool b) IPL_NOEXCEPT override;
        virtual bool putInt8(int8_t b) IPL_NOEXCEPT override;
        virtual bool putUInt8(uint8_t b) IPL_NOEXCEPT override;
        virtual bool putInt16(int16_t b) IPL_NOEXCEPT override;
        virtual bool putUInt16(uint16_t b) IPL_NOEXCEPT override;
        virtual bool putInt32(int32_t i) IPL_NOEXCEPT override;
        virtual bool putUInt32(uint32_t i) IPL_NOEXCEPT override;
        virtual bool putInt64(int64_t l) IPL_NOEXCEPT override;
        virtual bool putUInt64(uint64_t l) IPL_NOEXCEPT override;
        virtual bool putFloat(float f) IPL_NOEXCEPT override;
        virtual bool putDouble(double d) IPL_NOEXCEPT override;

        using IStructuredSerializer::putString;
        virtual bool putString(const ::util::UnicodeString8& str) IPL_NOEXCEPT override {return true;}
        virtual bool putString(const ::util::UnicodeString16& str) IPL_NOEXCEPT override {return true;}
        virtual bool putString(const std::string& str) IPL_NOEXCEPT override;

        // ----- Arrays -----
        virtual bool putNullArray(size_t size) IPL_NOEXCEPT override;
        virtual bool putBooleanArray(const std::vector<bool>& b) IPL_NOEXCEPT override;
        virtual bool putInt8Array(const std::vector<int8_t>& b) IPL_NOEXCEPT override;
        virtual bool putUInt8Array(const std::vector<uint8_t>& b) IPL_NOEXCEPT override;
        virtual bool putInt16Array(const std::vector<int16_t>& s) IPL_NOEXCEPT override;
        virtual bool putUInt16Array(const std::vector<uint16_t>& s) IPL_NOEXCEPT override;
        virtual bool putInt32Array(const std::vector<int32_t>& i) IPL_NOEXCEPT override;
        virtual bool putUInt32Array(const std::vector<uint32_t>& i) IPL_NOEXCEPT override;
        virtual bool putInt64Array(const std::vector<int64_t>& l) IPL_NOEXCEPT override;
        virtual bool putUInt64Array(const std::vector<uint64_t>& l) IPL_NOEXCEPT override;
        virtual bool putFloatArray(const std::vector<float>& f) IPL_NOEXCEPT override;
        virtual bool putDoubleArray(const std::vector<double>& d) IPL_NOEXCEPT override;
        virtual bool putStringArray(const std::vector<std::string>& s) IPL_NOEXCEPT override;

        // ----- Complex -----

        virtual bool beginArray() IPL_NOEXCEPT override;
        virtual bool endArray() IPL_NOEXCEPT override;

        virtual bool beginStruct( const SerializerOptions* opt = nullptr) IPL_NOEXCEPT override;
        virtual bool endStruct() IPL_NOEXCEPT override;

        virtual bool beginField(const std::string& name,
                                int32_t id = NO_ID,
                                bool isOptional = false
                               ) IPL_NOEXCEPT override;

        virtual bool endField() IPL_NOEXCEPT override;

        virtual bool beginElement() IPL_NOEXCEPT override;
        virtual bool endElement() IPL_NOEXCEPT override;

    protected:
        bool addCharacter(char c) IPL_NOEXCEPT;
        bool addSigned(int64_t value) IPL_NOEXCEPT;
        bool addUnsigned(uint64_t value) IPL_NOEXCEPT;

        ByteBufferWriter*   m_writer;
        enum State {
            /* == states of the serializer == */

            S_IDLE = 0,
            S_STARTED = 1,
            S_DONE = 2
        };
        bool                m_isFirst = false;
        uint32_t            m_state;
        bool m_base64EncodeBinaryData;
};

typedef JSONStructuredSerializerOld JSONStructuredSerializer;
#else
typedef RapidJsonStructuredSerializer JSONStructuredSerializer;
#endif

} /* namespace serializer */
} /* namespace util */

#endif /* UTIL_SERIALIZER_JSONSTRUCTUREDSERIALIZER_HXX */
