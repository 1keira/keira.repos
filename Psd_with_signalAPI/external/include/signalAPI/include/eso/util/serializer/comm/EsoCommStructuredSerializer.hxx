/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_SERIALIZER_ESOCOMMSTRUCTURED_SERIALIZER_HXX
#define UTIL_SERIALIZER_ESOCOMMSTRUCTURED_SERIALIZER_HXX

#include <functional>
#include <vector>
#include <util/serializer/IStructuredSerializer.hxx>
#include <util/serializer/SerializerErrors.hxx>
#include <util/serializer/SerializerScope.hxx>


namespace util
{
namespace serializer
{

///!@brief StructuredSerializer for eso COMM protocol using classic comm serialization



class UTIL_EXPORT EsoCommStructuredSerializer : public IStructuredSerializer {
    public:

        EsoCommStructuredSerializer() IPL_NOEXCEPT;

        virtual ~EsoCommStructuredSerializer() IPL_NOEXCEPT {}

        virtual bool beginSerialize(util::ByteBufferWriter* buffer, const SerializerOptions* = nullptr) IPL_NOEXCEPT override;
        virtual bool endSerialize(size_t& number_uint8_ts) IPL_NOEXCEPT override;

        virtual void reset() IPL_NOEXCEPT override;

        //! retrieve number of serialized bytes. The value
        //  is available AFTER endSerialize. Before this
        //  a value of 0 is returned
        virtual size_t size() const IPL_NOEXCEPT override;

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

        virtual bool putEnum(int32_t e, int bitsize=32) IPL_NOEXCEPT override;

        virtual bool putString(const util::UnicodeString8& str) IPL_NOEXCEPT override;
        virtual bool putString(const util::UnicodeString16& str) IPL_NOEXCEPT override;
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
        //virtual bool putEnumArray(EnumData ed[]) = 0;
        // ----- Complex -----

        virtual bool beginArray() IPL_NOEXCEPT override;
        virtual bool endArray() IPL_NOEXCEPT  override;

        virtual bool beginStruct(const SerializerOptions*) IPL_NOEXCEPT override;
        virtual bool endStruct() IPL_NOEXCEPT override;

        virtual bool beginField(const std::string& name,
                                int32_t id = NO_ID,
                                bool isOptional = false) IPL_NOEXCEPT override;

        virtual bool endField() IPL_NOEXCEPT override;

        virtual bool putMissingField(const std::string& name,
                                     int32_t id = NO_ID) IPL_NOEXCEPT override;

        virtual bool beginElement() IPL_NOEXCEPT override;
        virtual bool endElement() IPL_NOEXCEPT override;
        virtual bool putEmptyElement() IPL_NOEXCEPT override;

        virtual bool beginArrayOption(const ArrayOptions* options) override;
        virtual bool endArrayOption()  override;
        virtual bool beginOption(const SerializerOptions* options) override;
        virtual bool endOption() override;

private:

       inline bool checkArrayLimits(unsigned int elemCount) {
            auto limits = m_array_options->getLimits(m_array_dim);
            if (((limits.max >0) && (elemCount > limits.max))  ||
                (elemCount < limits.min)) {
                ipl_raise( serializer::Error, SerializerErrors::ARRAY_LIMIT_VIOLATION);
                return true;
            }
            return false;
       }

       ByteBufferWriter*  m_writer{nullptr};

       enum State {
            /* == states of the serializer == */
            S_IDLE = 0,
            S_STARTED = 1,
            S_DONE = 2,
            S_FAILED = 4
        };

        struct ArrayScope {
            int                      m_saved_element_count;
            ByteBufferWriter::Cursor m_cursor;
        };

        struct SerializerScope {
            bool m_do_options;
        };

        struct ArrayOptionScope {
            const ArrayOptions*      m_saved_array_options{nullptr};
        };

        struct StructScope {
            bool                     m_do_options;
            int                      m_saved_array_dim;
            const ArrayOptions*      m_saved_array_options;
        };

        struct OptionScope {
            bool     m_saved_endian;
        };

        bool serializeStringSize(uint32_t length) IPL_NOEXCEPT;
        bool serializeUnicode(util::UnicodeString::Encoding encoding, size_t size, const uint8_t* data) IPL_NOEXCEPT;
        void changeEndian (bool isBig) IPL_NOEXCEPT;

        bool addValidFlag() IPL_NOEXCEPT;

        uint32_t                  m_state{S_IDLE};
        bool                      m_bigEndian{true};
        bool                      m_endianMatch;
        int                       m_elemCount{0};
        bool                      m_validFlagPresent{0};

        const ArrayOptions*       m_array_options{&m_defaultArrayOptions};
        int                       m_array_dim{0};  // current dimension in array, 0 means not in an array
        static const ArrayOptions m_defaultArrayOptions;

        util::serializer::SerializerScope<SerializerScope, 1>  m_serializer_scope{};
        util::serializer::SerializerScope<ArrayScope,  4>      m_arr_scope{};
        util::serializer::SerializerScope<StructScope, 4>      m_struct_scope{};
        util::serializer::SerializerScope<OptionScope, 2>      m_option_scope{};
        util::serializer::SerializerScope<ArrayOptionScope, 4> m_array_option_scope{};

};

} /* namespace serializer */
} /* namespace util */

#endif /* UTIL_SERIALIZER_ESOCOMMSTRUCTURED_SERIALIZER_HXX */

