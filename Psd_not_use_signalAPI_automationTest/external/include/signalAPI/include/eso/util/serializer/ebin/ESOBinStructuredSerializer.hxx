/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_SERIALIZER_ESOBINSTRUCTUREDSERIALIZER_HXX
#define UTIL_SERIALIZER_ESOBINSTRUCTUREDSERIALIZER_HXX

#include <common/streams/sstream.hxx>
#include <common/types/string.hxx>
#include <common/types/map.hxx>

#include <util/util_dso.h>
#include <util/serializer/IStructuredSerializer.hxx>
#include <util/ByteBuffer.hxx>

namespace util
{
namespace serializer
{

class UTIL_EXPORT ESOBinStructuredSerializer : public IStructuredSerializer {
    public:
        // NOTE: We use this enum values as characters in the stream
        enum ElementType {
            KEY_UNDEFINED = 0,
            KEY_BEGIN_SERIALIZE = '^',
            KEY_END_SERIALIZE = '$',
            KEY_NULL = 'a',
            KEY_BOOLEAN = 'b',
            KEY_INT8 = 'c',
            KEY_UINT8 = 'd',
            KEY_INT16 = 'e',
            KEY_UINT16 = 'f',
            KEY_INT32 = 'g',
            KEY_UINT32 = 'h',
            KEY_INT64 = 'i',
            KEY_UINT64 = 'j',
            KEY_FLOAT = 'k',
            KEY_DOUBLE = 'l',
            KEY_ENUM = 'm',
            KEY_STRING = 'n',

            KEY_NULL_ARRAY = 'A',
            KEY_BOOLEAN_ARRAY = 'B',
            KEY_INT8_ARRAY = 'C',
            KEY_UINT8_ARRAY = 'D',
            KEY_INT16_ARRAY = 'E',
            KEY_UINT16_ARRAY = 'F',
            KEY_INT32_ARRAY = 'G',
            KEY_UINT32_ARRAY = 'H',
            KEY_INT64_ARRAY = 'I',
            KEY_UINT64_ARRAY = 'J',
            KEY_FLOAT_ARRAY = 'K',
            KEY_DOUBLE_ARRAY = 'L',
            KEY_ENUM_ARRAY = 'M',
            KEY_STRING_ARRAY = 'N',

            KEY_ARRAY_BEGIN = '[',
            KEY_ARRAY_END = ']',
            KEY_ENTRY_BEGIN = '(',
            KEY_ENTRY_END = ')',
            KEY_STRUCT_BEGIN = '{',
            KEY_STRUCT_END = '}',
            KEY_FIELD_BEGIN = '<',
            KEY_FIELD_END = '>',
            KEY_ANNOTATION = '@',
            KEY_TAG_ID = '!',
            KEY_TAG_KEY = ':',
            KEY_TAG_VALUE = '=',
            KEY_TAG_END = '.'
        };

        static const char VALUE_TRUE = 'T';
        static const char VALUE_FALSE = 'U';

        enum Endianess {
            LE_SERIALIZATION,
            BE_SERIALIZATION
        };

        ESOBinStructuredSerializer() IPL_NOEXCEPT
        : m_writer(NULL)
        , m_state(S_IDLE)
        , m_omit_element_type(false)
        {}

        virtual ~ESOBinStructuredSerializer() {}

        virtual bool beginSerialize(util::ByteBufferWriter* buffer, const SerializerOptions* opt = nullptr) IPL_NOEXCEPT override;
        virtual bool endSerialize(size_t& number_bytes) IPL_NOEXCEPT override;

        virtual void reset() IPL_NOEXCEPT override;

        virtual size_t size() const  IPL_NOEXCEPT override { return m_writer ? m_writer->size() : 0; }

        //! retrieve the data
        virtual bool get(uint8_t* destination, size_t size, size_t& got) const IPL_NOEXCEPT override;

        // ----- Scalars -----
        virtual bool putNull() IPL_NOEXCEPT override;
        virtual bool putBool(bool b) IPL_NOEXCEPT override;

        using IStructuredSerializer::putString;

        virtual bool putString(const util::UnicodeString8& str) IPL_NOEXCEPT override {return true;}
        virtual bool putString(const util::UnicodeString16& str) IPL_NOEXCEPT override {return true;}
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

        virtual bool beginArray() IPL_NOEXCEPT override;
        virtual bool endArray() IPL_NOEXCEPT override;

        virtual bool beginStruct(const SerializerOptions* opt = nullptr) IPL_NOEXCEPT override;
        virtual bool endStruct() IPL_NOEXCEPT override;

        virtual bool beginField(const std::string& name,  int32_t id = NO_ID, bool isOptional = false) IPL_NOEXCEPT override;
        virtual bool endField() IPL_NOEXCEPT override;

        virtual bool beginElement() IPL_NOEXCEPT override;
        virtual bool endElement() IPL_NOEXCEPT override;

        static std::string type2name(ElementType type) IPL_NOEXCEPT;

    protected:

        void omitElementType(bool o) IPL_NOEXCEPT { m_omit_element_type = o; }
        bool isOmitElementType() const IPL_NOEXCEPT { return m_omit_element_type; }

        //static std::map<char, std::string>& m_entry2name;
        bool addCharacter(char c) IPL_NOEXCEPT;
        bool addElementType(ElementType c) IPL_NOEXCEPT;

        ByteBufferWriter*   m_writer;
        enum State {
            /* == states of the serializer == */

            S_IDLE = 0,
            S_STARTED = 1,
            S_DONE = 2,
            S_FAILED = 4
        };
        uint32_t            m_state;
        bool                m_omit_element_type;
};


} /* namespace serializer */
} /* namespace util */
#endif /* UTIL_SERIALIZER_ESOBINSTRUCTUREDSERIALIZER_HXX */

