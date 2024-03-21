/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_SERIALIZER_SOMEIPSTRUCTURED_SERIALIZER_HXX
#define UTIL_SERIALIZER_SOMEIPSTRUCTURED_SERIALIZER_HXX

#include <functional>
#include <vector>
#include <util/serializer/IStructuredSerializer.hxx>
#include <util/serializer/SerializerScope.hxx>


namespace util
{
namespace serializer
{

///!@brief StructuredSerializer for SOME/IP protocol



class UTIL_EXPORT SOMEIPStructuredSerializer : public IStructuredSerializer {
    public:

        SOMEIPStructuredSerializer() IPL_NOEXCEPT;

        ~SOMEIPStructuredSerializer() IPL_NOEXCEPT override {}

        bool beginSerialize(util::ByteBufferWriter* buffer, const SerializerOptions* = nullptr) IPL_NOEXCEPT override;
        bool endSerialize(size_t& number_uint8_ts) IPL_NOEXCEPT override;

        void reset() IPL_NOEXCEPT override;

        //! retrieve number of serialized bytes. The value
        //  is available AFTER endSerialize. Before this
        //  a value of 0 is returned
        size_t size() const IPL_NOEXCEPT override;

        //! retrieve the data
        bool get(uint8_t* destination, size_t size, size_t& got) const IPL_NOEXCEPT override;

        // ----- Scalars -----

        bool putNull() IPL_NOEXCEPT override;
        bool putBool(bool b) IPL_NOEXCEPT override;
        bool putInt8(int8_t b) IPL_NOEXCEPT override;
        bool putUInt8(uint8_t b) IPL_NOEXCEPT override;
        bool putInt16(int16_t b) IPL_NOEXCEPT override;
        bool putUInt16(uint16_t b) IPL_NOEXCEPT override;
        bool putInt32(int32_t i) IPL_NOEXCEPT override;
        bool putUInt32(uint32_t i) IPL_NOEXCEPT override;
        bool putInt64(int64_t l) IPL_NOEXCEPT override;
        bool putUInt64(uint64_t l) IPL_NOEXCEPT override;
        bool putFloat(float f) IPL_NOEXCEPT override;
        bool putDouble(double d) IPL_NOEXCEPT override;

        bool putEnum(int32_t e, int bitsize=32) IPL_NOEXCEPT override;

        using IStructuredSerializer::putString;
        bool putString(const util::UnicodeString8& str) IPL_NOEXCEPT override;
        bool putString(const util::UnicodeString16& str) IPL_NOEXCEPT override;
        bool putString(const std::string& str) IPL_NOEXCEPT override;
        bool putString(const ipl::unicode::String& v) IPL_NOEXCEPT override;

        // ----- Arrays -----
        bool putNullArray(size_t size) IPL_NOEXCEPT override;
        bool putBooleanArray(const std::vector<bool>& b) IPL_NOEXCEPT override;
        bool putInt8Array(const std::vector<int8_t>& b) IPL_NOEXCEPT override;
        bool putUInt8Array(const std::vector<uint8_t>& b) IPL_NOEXCEPT override;
        bool putInt16Array(const std::vector<int16_t>& s) IPL_NOEXCEPT override;
        bool putUInt16Array(const std::vector<uint16_t>& s) IPL_NOEXCEPT override;
        bool putInt32Array(const std::vector<int32_t>& i) IPL_NOEXCEPT override;
        bool putUInt32Array(const std::vector<uint32_t>& i) IPL_NOEXCEPT override;
        bool putInt64Array(const std::vector<int64_t>& l) IPL_NOEXCEPT override;
        bool putUInt64Array(const std::vector<uint64_t>& l) IPL_NOEXCEPT override;
        bool putFloatArray(const std::vector<float>& f) IPL_NOEXCEPT override;
        bool putDoubleArray(const std::vector<double>& d) IPL_NOEXCEPT override;
        bool putStringArray(const std::vector<std::string>& s) IPL_NOEXCEPT override;
        //virtual bool putEnumArray(EnumData ed[]) = 0;
        // ----- Complex -----

        bool beginArray() IPL_NOEXCEPT override;
        bool endArray() IPL_NOEXCEPT  override;

        bool beginStruct(const SerializerOptions*) IPL_NOEXCEPT override;
        bool endStruct() IPL_NOEXCEPT override;

        bool beginField(const std::string& name,
                        int32_t id = NO_ID,
                        bool isOptional = false) IPL_NOEXCEPT override;

        bool endField() IPL_NOEXCEPT override;

        bool putMissingField(const std::string& name,
                             int32_t id = NO_ID) IPL_NOEXCEPT override;

        bool beginArrayOption(const ArrayOptions* options) IPL_NOEXCEPT override;
        bool endArrayOption() IPL_NOEXCEPT override;

        bool beginOption(const SerializerOptions* options) IPL_NOEXCEPT override;
        bool endOption() IPL_NOEXCEPT override;


        bool beginElement() IPL_NOEXCEPT override;
        bool endElement() IPL_NOEXCEPT override;
        bool putEmptyElement() IPL_NOEXCEPT override;

protected:

        template <class Vector>
        bool checkVectorLimits(const Vector& v);
        bool checkStringAndLimit(const uint8_t*, size_t size);

        ByteBufferWriter*  m_writer{nullptr};

        enum State {
            /* == states of the serializer == */
            S_IDLE = 0,
            S_STARTED = 1,
            S_DONE = 2,
            S_FAILED = 4
        };

        enum WireType {
            base_type_8bit   = 0,  // 8 bit base type, no length field
            base_type_16bit  = 1,  //16 bit base type, no length field
            base_type_32bit  = 2,  //32 bit base type, no length field
            base_type_64bit  = 3,  //64 bit base type, no length field
            complex_type_dfl   = 4,  // complex type (struct, array or string) length field determined by DFL
            complex_type_8bit  = 5,  // complex type (struct, array or string) length field 8 bit
            complex_type_16bit = 6,  // complex type (struct, array or string) length field 16 bit
            complex_type_32bit = 7   // complex type (struct, array or string) length field 32 bit

        };

        struct SerializerScope {
            bool m_do_options;
        };

        struct StructScope {
            bool                     m_do_options;
            bool                     m_saved_struct_extensible;
            bool                     m_saved_struct_has_length;
            int                      m_saved_array_dim;
            const ArrayOptions*      m_saved_array_options;
            int                      m_saved_field_count;
            ByteBufferWriter::Cursor m_cursor{};
            size_t                   m_start_size{0};
        };

        struct ArrayScope {
            int                      m_saved_element_count{0};
            ByteBufferWriter::Cursor m_cursor{};
            size_t                   m_start_size{0};
        };

        struct ArrayOptionScope {
            const ArrayOptions*      m_saved_array_options{nullptr};
        };

        struct OptionScope {
            uint8_t  m_saved_length_size;
            uint8_t  m_saved_array_length_size;
            uint8_t  m_saved_struct_length_size;
            bool     m_saved_endian;
        };

        struct FieldScope {
            int  m_saved_field_id;
            int  m_saved_wire_type;
            ByteBufferWriter::Cursor m_cursor{};
            size_t                   m_start_size{0};
        };

        bool serializeLengthField(uint32_t length, int bitsize) IPL_NOEXCEPT;

        void changeEndian (bool isBig);

        uint32_t                 m_state{S_IDLE};
        bool                     m_bigEndian{true};
        bool                     m_endianMatch;

        uint8_t                  m_length_size{32};
        uint8_t                  m_array_length_size{32};
        uint8_t                  m_struct_length_size{0}; // used for none tlv only
        unsigned int             m_elemCount{0};

        const ArrayOptions*      m_array_options{&m_defaultArrayOptions};

        int                      m_array_dim{0};  // current dimension in array, 0 means not in an array

        int                      m_field_id{-1};  // field id of current field
        int                      m_wireType{-1};  // wire type of current field
        int                      m_field_count {0}; // field count of current struct
        bool                     m_struct_has_length {true};
        bool                     m_currentStructExtensible{false};

        util::serializer::SerializerScope<SerializerScope, 0>  m_serializer_scope{};
        util::serializer::SerializerScope<ArrayScope,  0>      m_arr_scope{};
        util::serializer::SerializerScope<StructScope, 0>      m_struct_scope{};
        util::serializer::SerializerScope<OptionScope, 0>      m_option_scope{};
        util::serializer::SerializerScope<FieldScope,  0>      m_field_scope{};
        util::serializer::SerializerScope<ArrayOptionScope, 0> m_array_option_scope{};

        static const ArrayOptions   m_defaultArrayOptions;
};

} /* namespace serializer */
} /* namespace util */

#endif /* UTIL_SERIALIZER_SOMEIPSTRUCTURED_SERIALIZER_HXX */

