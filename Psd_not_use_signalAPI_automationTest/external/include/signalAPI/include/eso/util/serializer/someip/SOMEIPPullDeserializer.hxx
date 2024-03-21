/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_SERIALIZER_SOMEIP_PULL_DESERIALIZER_HXX
#define UTIL_SERIALIZER_SOMEIP_PULL_DESERIALIZER_HXX

#include <util/serializer/IStructuredPullDeserializer.hxx>
#include <util/serializer/SerializerErrors.hxx>
#include <util/serializer/SerializerScope.hxx>
#include <functional>
#include <vector>
#include <algorithm>



namespace util
{
namespace serializer
{

class UTIL_EXPORT SOMEIPPullDeserializer : public IStructuredPullDeserializer {
    public:
        SOMEIPPullDeserializer() IPL_NOEXCEPT ;
        ~SOMEIPPullDeserializer() IPL_NOEXCEPT override;

        bool beginDeserialize(util::ByteBufferReader* reader, const SerializerOptions* options) IPL_NOEXCEPT override;
        bool endDeserialize() IPL_NOEXCEPT override;
        void reset() IPL_NOEXCEPT override;

        bool getNull() IPL_NOEXCEPT override;
        bool getBoolean(bool& v) IPL_NOEXCEPT override;
        bool getInt8(int8_t& v) IPL_NOEXCEPT override;
        bool getUInt8(uint8_t& v) IPL_NOEXCEPT override;
        bool getInt16(int16_t& v) IPL_NOEXCEPT override;
        bool getUInt16(uint16_t& v) IPL_NOEXCEPT override;
        bool getInt32(int32_t& v) IPL_NOEXCEPT override;
        bool getUInt32(uint32_t& v) IPL_NOEXCEPT override;
        bool getInt64(int64_t& v) IPL_NOEXCEPT override;
        bool getUInt64(uint64_t& v) IPL_NOEXCEPT override;
        bool getFloat(float& v) IPL_NOEXCEPT override;
        bool getDouble(double& v) IPL_NOEXCEPT override;
        bool getEnum(int32_t& v, int bitsize=32, bool is_signed=false) IPL_NOEXCEPT override;
        bool getString(std::string& v) IPL_NOEXCEPT override;
        bool getString(util::UnicodeString8& str) IPL_NOEXCEPT override;
        bool getString(util::UnicodeString16& str) IPL_NOEXCEPT override;
        bool getString(ipl::unicode::String& str) IPL_NOEXCEPT override;
        bool getNullArray(size_t& size) IPL_NOEXCEPT override;
        bool getBooleanArray(std::vector<bool>& v) IPL_NOEXCEPT override;
        bool getInt8Array(std::vector<int8_t>& v) IPL_NOEXCEPT override;
        bool getUInt8Array(std::vector<uint8_t>& v) IPL_NOEXCEPT override;
        bool getInt16Array(std::vector<int16_t>& v) IPL_NOEXCEPT override;
        bool getUInt16Array(std::vector<uint16_t>& v) IPL_NOEXCEPT override;
        bool getInt32Array(std::vector<int32_t>& v) IPL_NOEXCEPT override;
        bool getUInt32Array(std::vector<uint32_t>& v) IPL_NOEXCEPT override;
        bool getInt64Array(std::vector<int64_t>& v) IPL_NOEXCEPT override;
        bool getUInt64Array(std::vector<uint64_t>& v) IPL_NOEXCEPT override;
        bool getFloatArray(std::vector<float>& v) IPL_NOEXCEPT override;
        bool getDoubleArray(std::vector<double>& v) IPL_NOEXCEPT override;
        bool getStringArray(std::vector<std::string>& v) IPL_NOEXCEPT override;


        bool beginArrayOption(const ArrayOptions* options) IPL_NOEXCEPT override;
        bool endArrayOption() IPL_NOEXCEPT override;
        bool beginOption(const SerializerOptions* options) IPL_NOEXCEPT override;
        bool endOption() IPL_NOEXCEPT override;

        bool beginArray() IPL_NOEXCEPT override;
        bool isArrayEnd() IPL_NOEXCEPT override;
        bool endArray() IPL_NOEXCEPT override;

        bool beginElement() IPL_NOEXCEPT override;
        bool endElement() IPL_NOEXCEPT override;

        bool beginStruct(const SerializerOptions* options = nullptr) IPL_NOEXCEPT override;
        bool isStructEnd() IPL_NOEXCEPT override;
        bool endStruct() IPL_NOEXCEPT override;

        bool beginMandatoryField(const std::string& name, int32_t id = NO_ID) IPL_NOEXCEPT  override;
        bool endMandatoryField() IPL_NOEXCEPT override;
        // for optional field
        bool beginOptionalField(const std::string& name, int32_t id, bool& isAvailable) IPL_NOEXCEPT override;
        bool endOptionalField() IPL_NOEXCEPT override;

        // unsuppported  by SOMEIPPullDeserializer
        bool beginField(std::string& name) IPL_NOEXCEPT override
        { return unsupportedAPI();}

        bool skipField() IPL_NOEXCEPT override
        { return unsupportedAPI();}

        bool endField() IPL_NOEXCEPT override
        { return unsupportedAPI();}

        const IStructuredPullDeserializer::EntryContent& getNextEntry() IPL_NOEXCEPT override;

        const IStructuredPullDeserializer::EntryContent& peekNextEntry() IPL_NOEXCEPT override;

        ApiCapabilities getApiCapibilites() IPL_NOEXCEPT override { return ApiCapability::applicationControlsFieldOrder;};

    private:

        #define LENGTH_INVALID 0xffffffff

        enum State {
                /* == states of the deserializer == */
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

        struct TlvEntry {
             WireType        type;
             const uint8_t*  begin;
             const uint8_t*  end;
             uint32_t        next_length;  // length field for complex types already deserialized
        };

        void changeEndian (bool isBig) IPL_NOEXCEPT;

        bool deserializeLengthField(uint32_t& length, int bitsize) IPL_NOEXCEPT;

        struct ArrayScope {
            uint32_t        m_elem_count_min;
            uint32_t        m_saved_elem_count;
            const uint8_t*  m_saved_array_end;

        };
        struct SerializerScope {
            bool m_do_options;
        };

        struct ArrayOptionScope {
            const ArrayOptions*      m_saved_array_options{nullptr};
        };

        struct StructScope {
            bool                     m_do_options;
            const uint8_t*           m_saved_struct_end;
            int                      m_saved_array_dim;
            bool                     m_saved_struct_extensible;
            const ArrayOptions*      m_saved_array_options;
        };

        struct OptionScope {
            uint8_t  m_saved_length_size;
            uint8_t  m_saved_array_length_size;
            uint8_t  m_saved_struct_length_size;
            bool     m_saved_endian;
        };

        struct FieldScope {
            const uint8_t*   m_saved_cursor;
            const uint8_t*   m_saved_field_end;
        };

        uint32_t                 m_state{S_IDLE};
        bool                     m_bigEndian{true};
        bool                     m_endianMatch;
        int                      m_length_size{32};
        int                      m_array_length_size{32};
        int                      m_struct_length_size{0}; // only used for non extensible structs (none-tlv)
        unsigned int             m_elemCount{0};
        const uint8_t*           m_arrayEnd{nullptr};
        const uint8_t*           m_structEnd{nullptr};
        const uint8_t*           m_fieldEnd{nullptr};
        const ArrayOptions*      m_array_options{&m_defaultArrayOptions};
        int                      m_array_dim{0};  // current dimension in array, 0 means not in an array
        int                      m_field_id{-1};  // field id of current field
        int                      m_wireType{-1};  // wire type of current field
        bool                     m_currentStructExtensible{false};
        uint32_t                 m_nextLength {LENGTH_INVALID}; // used during deserializeLengthField of complex types

        util::ByteBufferReader*  m_reader{nullptr};

        util::serializer::SerializerScope<SerializerScope, 1>  m_serializer_scope{};
        util::serializer::SerializerScope<ArrayScope,  4>      m_arr_scope{};
        util::serializer::SerializerScope<StructScope, 4>      m_struct_scope{};
        util::serializer::SerializerScope<OptionScope, 4>      m_option_scope{};
        util::serializer::SerializerScope<FieldScope,  4>      m_field_scope{};
        util::serializer::SerializerScope<ArrayOptionScope, 4> m_array_option_scope{};

        static const ArrayOptions m_defaultArrayOptions;

        bool getFromReader(bool& value) IPL_NOEXCEPT {
            uint8_t val;
            if (m_reader->get(val)) return true;
            value = (val & 0x01) == 0x01; // PRS_SOMEIP_00615
            return false;
        }

        template<class T>
        bool getFromReader(T& value) IPL_NOEXCEPT {
            if (m_reader->bytesLeft() < sizeof(value)) {
                ipl_raise( serializer::Error, INSANE_SIZE, m_reader->bytesLeft() );
                return true;
            }
            uint8_t* to = (uint8_t*) &value;
            const uint8_t* from = m_reader->current();
            if (m_endianMatch) {
                std::copy( from, from + sizeof(value), to);
            } else {
                std::reverse_copy( from, from + sizeof(value), to);
            }
            m_reader->skip(sizeof(value));
            return false;
        }

        bool findField( int id, TlvEntry &entry, bool& hasError) IPL_NOEXCEPT;

        bool unsupportedAPI() IPL_NOEXCEPT {

             ipl_raise( serializer::Error, INVALID_MODE);
             return true;
        }

        template<class T>
        bool getPrimitiveArray(std::vector<T>& v) IPL_NOEXCEPT
        {
            auto limits = m_array_options->getLimits(m_array_dim+1);

            uint32_t elemCount;
            uint32_t byteSize;
            uint32_t skipSize{0};
            if (m_array_length_size) {
                if (deserializeLengthField(byteSize, m_array_length_size)) return true;
                elemCount = byteSize/sizeof(T);
                if (elemCount < limits.min) {
                    ipl_raise( serializer::Error, SerializerErrors::ARRAY_LIMIT_VIOLATION);
                    return true;
                }
                if ((limits.max > 0) && (elemCount > limits.max)) {
                    skipSize = (elemCount - limits.max) * sizeof(T);
                    elemCount = limits.max;
                }
            } else {
                // we expect fixed size array here
                if ((limits.min != limits.max) || (limits.min == 0)) {
                    ipl_raise( serializer::Error, SerializerErrors::ARRAY_LIMIT_VIOLATION);
                    return true;
                }
                elemCount = limits.max;
            }

            v.clear();
            while (elemCount--){
                T val;
                if (getFromReader(val)) return true;
                v.push_back(val);
            }
            if (skipSize) {
                if (m_reader->skip(skipSize)) {
                    ipl_raise( serializer::Error, INSANE_SIZE, m_reader->bytesLeft() );
                    return true;
                }
            }
            return false;
        }

        bool checkStringAndLimit(uint32_t& length,  uint32_t& read_size);
};

} // namespace serializer
} // namespace util



#endif
