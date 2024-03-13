/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_SERIALIZER_ESOCOMM_PULL_DESERIALIZER_HXX
#define UTIL_SERIALIZER_ESOCOMM_PULL_DESERIALIZER_HXX

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

class UTIL_EXPORT EsoCommPullDeserializer : public IStructuredPullDeserializer {
    public:
        EsoCommPullDeserializer() IPL_NOEXCEPT ;
        virtual ~EsoCommPullDeserializer() IPL_NOEXCEPT;

        bool beginDeserialize(util::ByteBufferReader* reader, const SerializerOptions* options=nullptr) IPL_NOEXCEPT override;
        bool endDeserialize() IPL_NOEXCEPT override ;
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
        bool getEmptyElement(bool& isEmpty) IPL_NOEXCEPT override;

        bool beginStruct(const SerializerOptions* options = nullptr) IPL_NOEXCEPT override;
        bool isStructEnd() IPL_NOEXCEPT override;
        bool endStruct() IPL_NOEXCEPT override;

        bool beginMandatoryField(const std::string& name, int32_t id = NO_ID) IPL_NOEXCEPT  override;
        bool endMandatoryField() IPL_NOEXCEPT override;
        // for optional field
        bool beginOptionalField(const std::string& name, int32_t id, bool& isAvailable) IPL_NOEXCEPT override;
        bool endOptionalField() IPL_NOEXCEPT override;

        // unsuppported  by EsoCommPullDeserializer
        bool beginField(std::string& name) IPL_NOEXCEPT override
        { return unsupportedAPI();}

        bool skipField() IPL_NOEXCEPT override
        { return unsupportedAPI();}

        bool endField() IPL_NOEXCEPT override
        { return unsupportedAPI();}

        ApiCapabilities getApiCapibilites() IPL_NOEXCEPT override { return ApiCapability::applicationControlsFieldOrder;};

        const IStructuredPullDeserializer::EntryContent& getNextEntry() IPL_NOEXCEPT override;

        const IStructuredPullDeserializer::EntryContent& peekNextEntry() IPL_NOEXCEPT override;

    private:

        enum State {
                /* == states of the deserializer == */
                S_IDLE = 0,
                S_STARTED = 1,
                S_DONE = 2,
                S_FAILED = 4
        };

        struct ArrayScope {
            uint32_t        m_saved_elem_count;
            uint32_t        m_saved_elem_count_expected;
        };

        struct SerializerScope {
            bool m_do_options;
        };

        struct ArrayOptionScope {
            const ArrayOptions*      m_saved_array_options{nullptr};
        };

        struct StructScope {
            bool                     m_do_options;
            const ArrayOptions*      m_saved_array_options;
            int                      m_saved_array_dim;
        };

        struct OptionScope {
            bool     m_saved_endian;
        };

        struct FieldScope {
            const uint8_t*   m_saved_cursor;
        };

        void changeEndian (bool isBig) IPL_NOEXCEPT;


        static constexpr uint8_t STREAM_STRING_ENCODING_UTF8{0};
        static constexpr uint8_t STREAM_STRING_ENCODING_UTF16{1};
        static constexpr uint8_t STREAM_STRING_ENCODING_UTF32{2};

        bool deserializeUnicode( util::UnicodeString::Encoding &encoding,
                                 uint32_t &size, void **data) IPL_NOEXCEPT;

        bool deserializeStringSize(uint32_t& length) IPL_NOEXCEPT;

        inline bool checkArrayLimits(unsigned int elemCount) {
            auto limits = m_array_options->getLimits(m_array_dim);

            if (((limits.max >0) && (elemCount > limits.max)) ||
                (elemCount < limits.min))
            {
                ipl_raise( serializer::Error, SerializerErrors::ARRAY_LIMIT_VIOLATION);
                return true;
            }
            return false;
       }

        uint32_t                 m_state{S_IDLE};
        bool                     m_bigEndian{true};
        bool                     m_endianMatch;
        unsigned int             m_elemCount{0};
        unsigned int             m_elemCountExpected{0};
        const ArrayOptions*      m_array_options{&m_defaultArrayOptions};
        int                      m_array_dim{0};  // current dimension in array, 0 means not in an array
        bool                     m_validFlagVerified{false};

        util::ByteBufferReader*  m_reader{nullptr};

        util::serializer::SerializerScope<SerializerScope, 1>  m_serializer_scope{};
        util::serializer::SerializerScope<ArrayScope,  4>      m_arr_scope{};
        util::serializer::SerializerScope<StructScope, 4>      m_struct_scope{};
        util::serializer::SerializerScope<OptionScope, 4>      m_option_scope{};
        util::serializer::SerializerScope<FieldScope,  4>      m_field_scope{};
        util::serializer::SerializerScope<ArrayOptionScope, 4> m_array_option_scope{};

        static const ArrayOptions m_defaultArrayOptions;

        bool getFromReader(bool& value) IPL_NOEXCEPT {
            if (!m_reader) {
                ipl_raise( serializer::Error, INVALID_MODE );
                return true;
            }
            uint8_t val;
            if (m_reader->get(val)) return true;
            if (val == 0xff) {
                value  = true;
            } else if (val == 0x00) {
                value = false;
            } else {
                ipl_raise( serializer::Error, SerializerErrors::UNEXPECTED_TOKEN, val);
                return true;
            }
            return false;
        }
        template<class T>
        bool getFromReader(T& value) IPL_NOEXCEPT {
            if (!m_reader) {
                ipl_raise( serializer::Error, INVALID_MODE );
                return true;
            }
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

        bool unsupportedAPI() IPL_NOEXCEPT {

             ipl_raise( serializer::Error, INVALID_MODE);
             return true;
        }

        template<class T>
        bool getPrimitiveArray(std::vector<T>& v) IPL_NOEXCEPT
        {
            uint32_t elemCount;
            if (!m_validFlagVerified) {
                uint8_t flag; if (getUInt8(flag)) return true;
                if (flag == 0xff) {
                    elemCount = 0;
                } else if (flag != 0) {
                    ipl_raise( serializer::Error, SerializerErrors::UNEXPECTED_TOKEN, flag);
                    return true;
                }  else  {
                    if (getUInt32(elemCount)) return true;
                }
            } else {
               if (getUInt32(elemCount)) return true;
            }
            m_validFlagVerified = false;

            // we don't have beginArray endArray calss  for primitive arrays where m_array_dim is maintained
            // So increment/deccrement here.
            ++m_array_dim;
            if (checkArrayLimits(elemCount)) return true;
            --m_array_dim;

            v.clear();
            while (elemCount--){
                T val;
                if (getFromReader(val)) return true;
                v.push_back(val);
            }
            return false;
        }
};

} // namespace serializer
} // namespace util

#endif
