/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_SERIALIZER_STRUCTUREDPULLDESERIALIZERADAPTER_HXX
#define UTIL_SERIALIZER_STRUCTUREDPULLDESERIALIZERADAPTER_HXX

#include <util/serializer/IStructuredPullDeserializer.hxx>
#include <util/serializer/IStructuredPushDeserializer.hxx>
#include <util/serializer/IStructuredSerializer.hxx>
#include <util/serializer/SerializerErrors.hxx>
#include <common/error/Error.hxx>

namespace util
{
namespace serializer
{

/*!
 *  \brief This class wraps around an IStructuredPushDeserializer and provides an IStructuredPullDeserializer interface to the outside.
 *
 *  \details Integer types are converted automatically into each other, Floating types are also converted automatically. (Same for arrays of these types)
 */
class UTIL_EXPORT PullFromPushDeserializer : public IStructuredPullDeserializer {
    public:
        PullFromPushDeserializer( IStructuredPushDeserializer& deser ) IPL_NOEXCEPT : m_deser(deser) {}

        virtual ~PullFromPushDeserializer() IPL_NOEXCEPT override {}

        virtual bool beginDeserialize(util::ByteBufferReader* reader, const SerializerOptions* options = nullptr) IPL_NOEXCEPT override;
        virtual bool endDeserialize() IPL_NOEXCEPT override;
        virtual void reset() IPL_NOEXCEPT override {}

        virtual bool getNull() IPL_NOEXCEPT override;
        virtual bool getBoolean(bool& v) IPL_NOEXCEPT override;
        virtual bool getInt8(int8_t& v) IPL_NOEXCEPT override;
        virtual bool getUInt8(uint8_t& v) IPL_NOEXCEPT override;
        virtual bool getInt16(int16_t& v) IPL_NOEXCEPT override;
        virtual bool getUInt16(uint16_t& v) IPL_NOEXCEPT override;
        virtual bool getInt32(int32_t& v) IPL_NOEXCEPT override;
        virtual bool getUInt32(uint32_t& v) IPL_NOEXCEPT override;
        virtual bool getInt64(int64_t& v) IPL_NOEXCEPT override;
        virtual bool getUInt64(uint64_t& v) IPL_NOEXCEPT override;
        virtual bool getFloat(float& v) IPL_NOEXCEPT override;
        virtual bool getDouble(double& v) IPL_NOEXCEPT override;
        virtual bool getEnum(int32_t& v, int bitsize=32, bool is_signed=false) IPL_NOEXCEPT override { return getInt32(v); }

        using IStructuredPullDeserializer::getString;
        virtual bool getString(std::string& v) IPL_NOEXCEPT override;
        virtual bool getString(util::UnicodeString8& str) IPL_NOEXCEPT override { return true; }
        virtual bool getString(util::UnicodeString16& str) IPL_NOEXCEPT override { return true; }

        virtual bool getNullArray(size_t& size) IPL_NOEXCEPT override;
        virtual bool getBooleanArray(std::vector<bool>& v) IPL_NOEXCEPT override;
        virtual bool getInt8Array(std::vector<int8_t>& v) IPL_NOEXCEPT override;
        virtual bool getUInt8Array(std::vector<uint8_t>& v) IPL_NOEXCEPT override;
        virtual bool getInt16Array(std::vector<int16_t>& v) IPL_NOEXCEPT override;
        virtual bool getUInt16Array(std::vector<uint16_t>& v) IPL_NOEXCEPT override;
        virtual bool getInt32Array(std::vector<int32_t>& v) IPL_NOEXCEPT override;
        virtual bool getUInt32Array(std::vector<uint32_t>& v) IPL_NOEXCEPT override;
        virtual bool getInt64Array(std::vector<int64_t>& v) IPL_NOEXCEPT override;
        virtual bool getUInt64Array(std::vector<uint64_t>& v) IPL_NOEXCEPT override;
        virtual bool getFloatArray(std::vector<float>& v) IPL_NOEXCEPT override;
        virtual bool getDoubleArray(std::vector<double>& v) IPL_NOEXCEPT override;
        virtual bool getStringArray(std::vector<std::string>& v) IPL_NOEXCEPT override;
        //virtual bool getEnumArray(int32_t& v) IPL_NOEXCEPT override;

        virtual bool beginArrayOption(const ArrayOptions* options) IPL_NOEXCEPT override { return false; }
        virtual bool endArrayOption() IPL_NOEXCEPT override { return false; }
        virtual bool beginOption(const SerializerOptions* options) IPL_NOEXCEPT override { return false; }
        virtual bool endOption() IPL_NOEXCEPT override { return false; }

        virtual bool beginArray() IPL_NOEXCEPT override;
        virtual bool isArrayEnd() IPL_NOEXCEPT override;
        virtual bool endArray() IPL_NOEXCEPT override;
        virtual bool beginElement() IPL_NOEXCEPT override;
        virtual bool endElement() IPL_NOEXCEPT override;
        virtual bool beginStruct(const SerializerOptions* options = nullptr) IPL_NOEXCEPT override;
        virtual bool isStructEnd() IPL_NOEXCEPT override;
        virtual bool endStruct() IPL_NOEXCEPT override;

        // ApiCapability deserializerControlsFieldOrder
        virtual bool beginField(std::string& out_name) IPL_NOEXCEPT override;
        virtual bool skipField() IPL_NOEXCEPT override;
        virtual bool endField() IPL_NOEXCEPT override;
        virtual const EntryContent& getNextEntry() IPL_NOEXCEPT override;
        virtual const EntryContent& peekNextEntry() IPL_NOEXCEPT override;

        // ApiCapability applicatationControlsFieldOrder
        static const int32_t NO_ID = -1;
        // for mandotary field
        virtual bool beginMandatoryField(const std::string& name, int32_t id = NO_ID) IPL_NOEXCEPT override { return true; }
        virtual bool endMandatoryField() IPL_NOEXCEPT override { return true; }
        // for optional field
        virtual bool beginOptionalField(const std::string& name, int32_t id, bool& isAvailable) IPL_NOEXCEPT override { return true; }
        virtual bool endOptionalField() IPL_NOEXCEPT override { return true; }

        virtual ApiCapabilities getApiCapibilites() IPL_NOEXCEPT override { return ApiCapability::deserializerControlsFieldOrder; }

    private:
        class PushCallbackHandler : public IStructuredSerializer {
            public:
                virtual ~PushCallbackHandler() IPL_NOEXCEPT {}

                virtual bool beginSerialize(util::ByteBufferWriter* buffer, const SerializerOptions* opt = nullptr) IPL_NOEXCEPT override { return true; }
                virtual bool endSerialize(size_t& number_uint8_ts) IPL_NOEXCEPT override { return true; }
                virtual void reset() IPL_NOEXCEPT override {}
                virtual size_t size() const IPL_NOEXCEPT override { return 0; }
                virtual bool get(uint8_t* destination, size_t size, size_t& got) const IPL_NOEXCEPT  override { return true; }

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
                virtual bool putString(const util::UnicodeString8& str) IPL_NOEXCEPT override { return true; }
                virtual bool putString(const util::UnicodeString16& str) IPL_NOEXCEPT override { return true; }
                virtual bool putString(const std::string& str) IPL_NOEXCEPT override;

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

                virtual bool beginField(const std::string& name, int32_t id = NO_ID, bool isOptional=false) IPL_NOEXCEPT override;
                virtual bool endField() IPL_NOEXCEPT override;

                virtual bool beginElement() IPL_NOEXCEPT override;
                virtual bool endElement() IPL_NOEXCEPT override;

                /* stored data element */
                IStructuredPullDeserializer::EntryContent m_current_entry;
                IStructuredPullDeserializer::EntryType m_current_type;
                size_t m_size;
                std::vector<bool> m_bool_buffer;
                std::vector<int8_t> m_int8_buffer;
                std::vector<uint8_t> m_uint8_buffer;
                std::vector<int16_t> m_int16_buffer;
                std::vector<uint16_t> m_uint16_buffer;
                std::vector<int32_t> m_int32_buffer;
                std::vector<uint32_t> m_uint32_buffer;
                std::vector<int64_t> m_int64_buffer;
                std::vector<uint64_t> m_uint64_buffer;
                std::vector<float> m_float_buffer;
                std::vector<double> m_double_buffer;
                std::vector<std::string> m_string_buffer;
        };

        enum GetArrayElementResult {
            GetArrayElementResultFailed,
            GetArrayElementResultUnexpected,
            GetArrayElementResultArrayEndFound,
            GetArrayElementResultElementFound,
        };

        bool getAnyInt(int64_t& v) IPL_NOEXCEPT;

        GetArrayElementResult getArrayElement(IStructuredPullDeserializer::EntryType which) IPL_NOEXCEPT;

        bool receiveExpectedValue(IStructuredPullDeserializer::EntryType which) IPL_NOEXCEPT;
        IStructuredPullDeserializer::EntryType peekNextType() IPL_NOEXCEPT;

        IStructuredPushDeserializer& m_deser;
        PushCallbackHandler m_current;
};

} /* namespace serializer */
} /* namespace util */

#endif /* UTIL_SERIALIZER_STRUCTUREDPULLDESERIALIZERADAPTER_HXX */

