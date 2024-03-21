/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_SERIALIZER_STRUCTUREDPUSHDESERIALIZERSTEPADAPTER_HXX
#define UTIL_SERIALIZER_STRUCTUREDPUSHDESERIALIZERSTEPADAPTER_HXX

#include <util/serializer/IStructuredPushDeserializer.hxx>
#include <util/serializer/IStructuredSerializer.hxx>
#include <util/serializer/SerializerErrors.hxx>
#include <common/error/Error.hxx>
#include <common/error/ErrorType.hxx>
#include <deque>

namespace util
{
namespace serializer
{

/*! \brief records the sequence of calls and parameters to play this back later
 *
 *  \details This class needs memory linear to the input size: For every input token, a CapturedCall struct is stored on a stack
 */
class UTIL_EXPORT
IPL_DEPRECATED_PRE("do not record json parser callbacks for a later playback")
StructuredSerializerRecorder : public IStructuredSerializer
{
public:
    StructuredSerializerRecorder( size_t expected_count = 200 ) IPL_NOEXCEPT : m_calllist( expected_count ) {}
    ~StructuredSerializerRecorder() IPL_NOEXCEPT override = default;
    StructuredSerializerRecorder(const StructuredSerializerRecorder&)=default;
    StructuredSerializerRecorder(StructuredSerializerRecorder&&)=default;
    StructuredSerializerRecorder& operator=(const StructuredSerializerRecorder&)=default;
    StructuredSerializerRecorder& operator=(StructuredSerializerRecorder&&)=default;

    virtual void reset() IPL_NOEXCEPT override;

    IStructuredPushDeserializer::DeserializerResult playbackAll( IStructuredSerializer* target );
    IStructuredPushDeserializer::DeserializerResult playbackStep( IStructuredSerializer* target );

    /*! number of recorded steps that have not yet been played back */
    size_t remainingSteps() const IPL_NOEXCEPT {return m_calllist.size();}

    /*! this method always returns 0 because it is an adapter, it does not produce binary output */
    virtual size_t size() const IPL_NOEXCEPT override {return 0;}

    /*! this method always returns 0 bytes because it is an adapter, it does not produce binary output */
    virtual bool get(uint8_t* destination, size_t size, size_t& got) const IPL_NOEXCEPT override { got=0; return false; }

    // ----- calls to capture/record and playback later -----
    virtual bool beginSerialize(util::ByteBufferWriter* buffer, const SerializerOptions* options = nullptr) IPL_NOEXCEPT override;
    virtual bool endSerialize(size_t& number_uint8_ts) IPL_NOEXCEPT override;
    virtual bool putNull() IPL_NOEXCEPT override;
    virtual bool putBool(bool b) IPL_NOEXCEPT override;
    virtual bool putInt8(int8_t int_param) IPL_NOEXCEPT override;
    virtual bool putUInt8(uint8_t int_param) IPL_NOEXCEPT override;
    virtual bool putInt16(int16_t int_param) IPL_NOEXCEPT override;
    virtual bool putUInt16(uint16_t int_param) IPL_NOEXCEPT override;
    virtual bool putInt32(int32_t int_param) IPL_NOEXCEPT override;
    virtual bool putUInt32(uint32_t int_param) IPL_NOEXCEPT override;
    virtual bool putInt64(int64_t int_param) IPL_NOEXCEPT override;
    virtual bool putUInt64(uint64_t int_param) IPL_NOEXCEPT override;
    virtual bool putFloat(float f) IPL_NOEXCEPT override;
    virtual bool putDouble(double d) IPL_NOEXCEPT override;
    virtual bool putEnum(int32_t e, int bitsize=32) IPL_NOEXCEPT override;

    using IStructuredSerializer::putString;
    virtual bool putString(const std::string& str) IPL_NOEXCEPT override;
    virtual bool putString(const util::UnicodeString8& str) override;
    virtual bool putString(const util::UnicodeString16& str) override;
    virtual bool putNullArray(size_t size) IPL_NOEXCEPT override;
    virtual bool putBooleanArray(const std::vector<bool>& b) IPL_NOEXCEPT override;
    virtual bool putInt8Array(const std::vector<int8_t>& b) IPL_NOEXCEPT override;
    virtual bool putUInt8Array(const std::vector<uint8_t>& int_arr) IPL_NOEXCEPT override;
    virtual bool putInt16Array(const std::vector<int16_t>& int_arr) IPL_NOEXCEPT override;
    virtual bool putUInt16Array(const std::vector<uint16_t>& int_arr) IPL_NOEXCEPT override;
    virtual bool putInt32Array(const std::vector<int32_t>& int_arr) IPL_NOEXCEPT override;
    virtual bool putUInt32Array(const std::vector<uint32_t>& int_arr) IPL_NOEXCEPT override;
    virtual bool putInt64Array(const std::vector<int64_t>& int_arr) IPL_NOEXCEPT override;
    virtual bool putUInt64Array(const std::vector<uint64_t>& int_arr) IPL_NOEXCEPT override;
    virtual bool putFloatArray(const std::vector<float>& f) IPL_NOEXCEPT override;
    virtual bool putDoubleArray(const std::vector<double>& d) IPL_NOEXCEPT override;
    virtual bool putStringArray(const std::vector<std::string>& s) IPL_NOEXCEPT override;
    virtual bool beginArray() IPL_NOEXCEPT override;
    virtual bool beginElement() IPL_NOEXCEPT override;
    virtual bool endElement() IPL_NOEXCEPT override;
    virtual bool putEmptyElement()  IPL_NOEXCEPT override;
    virtual bool endArray() IPL_NOEXCEPT override;
    virtual bool beginStruct(const SerializerOptions* options=nullptr) IPL_NOEXCEPT override;
    virtual bool endStruct() IPL_NOEXCEPT override;
    virtual bool beginField(const std::string& name, int32_t id = NO_ID, bool isOptional=false) IPL_NOEXCEPT override;
    virtual bool endField() IPL_NOEXCEPT override;
    virtual bool putMissingField(const std::string& name, int32_t id = NO_ID) IPL_NOEXCEPT override;
    virtual bool beginArrayOption(const ArrayOptions* options) override;
    virtual bool endArrayOption() override;
    virtual bool beginOption(const SerializerOptions* options) override;
    virtual bool endOption() override;
private:
    struct CapturedCall final {
        enum class Method {
            MethodNONE,
            MethodBeginSerialize,
            MethodEndSerialize,
            MethodPutNull,
            MethodPutBool,
            MethodPutInt8,
            MethodPutUInt8,
            MethodPutInt16,
            MethodPutUInt16,
            MethodPutInt32,
            MethodPutUInt32,
            MethodPutInt64,
            MethodPutUInt64,
            MethodPutFloat,
            MethodPutDouble,
            MethodPutEnum,
            MethodPutStringStd,
            MethodPutStringU8,
            MethodPutStringU16,
            MethodPutNullArray,
            MethodPutBooleanArray,
            MethodPutInt8Array,
            MethodPutUInt8Array,
            MethodPutInt16Array,
            MethodPutUInt16Array,
            MethodPutInt32Array,
            MethodPutUInt32Array,
            MethodPutInt64Array,
            MethodPutUInt64Array,
            MethodPutFloatArray,
            MethodPutDoubleArray,
            MethodPutStringArray,
            MethodBeginArray,
            MethodBeginElement,
            MethodEndElement,
            MethodPutEmptyElement,
            MethodEndArray,
            MethodBeginStruct,
            MethodEndStruct,
            MethodBeginField,
            MethodEndField,
            MethodPutMissingField,
            MethodBeginArrayOption,
            MethodEndArrayOption,
            MethodBeginOption,
            MethodEndOption,
        };

        CapturedCall() IPL_NOEXCEPT
        : m_method(Method::MethodNONE)
        , m_param_bool{false}
        , m_param_int{0}
        , m_param_double{0.0}
        , m_param_size{0}
        , m_param_seropt{}
        , m_param2_int{0}
        , m_param_bufferwriter{nullptr}
        , m_cnt(0)
        {}

        ~CapturedCall() IPL_NOEXCEPT = default;
        CapturedCall(const CapturedCall&)=default;
        CapturedCall(CapturedCall&&)=default;
        CapturedCall& operator=(const CapturedCall&)=default;
        CapturedCall& operator=(CapturedCall&&)=default;

        explicit CapturedCall(Method zero_param_method) IPL_NOEXCEPT
        : m_method(zero_param_method)
        , m_param_bool{false}
        , m_param_int{0}
        , m_param_double{0.0}
        , m_param_size{0}
        , m_param_seropt{}
        , m_param2_int{0}
        , m_param_bufferwriter{nullptr}
        , m_cnt(0)
        {}

        explicit CapturedCall(bool bool_param) IPL_NOEXCEPT
        : m_method(Method::MethodPutBool)
        , m_param_bool(bool_param)
        , m_param_int{0}
        , m_param_double{0.0}
        , m_param_size{0}
        , m_param_seropt{}
        , m_param2_int{0}
        , m_param_bufferwriter{nullptr}
        , m_cnt(1)
        {}

        explicit CapturedCall(int8_t int_param) IPL_NOEXCEPT
        : m_method(Method::MethodPutInt8)
        , m_param_bool{false}
        , m_param_int{int_param}
        , m_param_double{0.0}
        , m_param_size{0}
        , m_param_seropt{}
        , m_param2_int{0}
        , m_param_bufferwriter{nullptr}
        , m_cnt(1)
        {}

        explicit CapturedCall(uint8_t int_param) IPL_NOEXCEPT
        : m_method(Method::MethodPutUInt8)
        , m_param_bool{false}
        , m_param_int{int_param}
        , m_param_double{0.0}
        , m_param_size{0}
        , m_param_seropt{}
        , m_param2_int{0}
        , m_param_bufferwriter{nullptr}
        , m_cnt(1)
        {}
        explicit CapturedCall(int16_t int_param) IPL_NOEXCEPT
        : m_method(Method::MethodPutInt16)
        , m_param_bool{false}
        , m_param_int{int_param}
        , m_param_double{0.0}
        , m_param_size{0}
        , m_param_seropt{}
        , m_param2_int{0}
        , m_param_bufferwriter{nullptr}
        , m_cnt(1)
        {}
        explicit CapturedCall(uint16_t int_param) IPL_NOEXCEPT
        : m_method(Method::MethodPutUInt16)
        , m_param_bool{false}
        , m_param_int{int_param}
        , m_param_double{0.0}
        , m_param_size{0}
        , m_param_seropt{}
        , m_param2_int{0}
        , m_param_bufferwriter{nullptr}
        , m_cnt(1)
        {}
        explicit CapturedCall(int32_t int_param) IPL_NOEXCEPT
        : m_method(Method::MethodPutInt32)
        , m_param_bool{false}
        , m_param_int{int_param}
        , m_param_double{0.0}
        , m_param_size{0}
        , m_param_seropt{}
        , m_param2_int{0}
        , m_param_bufferwriter{nullptr}
        , m_cnt(1)
        {}
        explicit CapturedCall(uint32_t int_param) IPL_NOEXCEPT
        : m_method(Method::MethodPutUInt32)
        , m_param_bool{false}
        , m_param_int{int_param}
        , m_param_double{0.0}
        , m_param_size{0}
        , m_param_seropt{}
        , m_param2_int{0}
        , m_param_bufferwriter{nullptr}
        , m_cnt(1)
        {}
        explicit CapturedCall(int64_t int_param) IPL_NOEXCEPT
        : m_method(Method::MethodPutInt64)
        , m_param_bool{false}
        , m_param_int{int_param}
        , m_param_double{0.0}
        , m_param_size{0}
        , m_param_seropt{}
        , m_param2_int{0}
        , m_param_bufferwriter{nullptr}
        , m_cnt(1)
        {}
        explicit CapturedCall(uint64_t int_param) IPL_NOEXCEPT
        : m_method(Method::MethodPutUInt64)
        , m_param_bool{false}
        , m_param_int{(int64_t)int_param}
        , m_param_double{0.0}
        , m_param_size{0}
        , m_param_seropt{}
        , m_param2_int{0}
        , m_param_bufferwriter{nullptr}
        , m_cnt(1)
        {}

        explicit CapturedCall(float double_param) IPL_NOEXCEPT
        : m_method(Method::MethodPutFloat)
        , m_param_bool{false}
        , m_param_int{0}
        , m_param_double(double_param)
        , m_param_size{0}
        , m_param_seropt{}
        , m_param2_int{0}
        , m_param_bufferwriter{nullptr}
        , m_cnt(1)
        {}

        explicit CapturedCall(double double_param) IPL_NOEXCEPT
        : m_method(Method::MethodPutDouble)
        , m_param_bool{false}
        , m_param_int{0}
        , m_param_double(double_param)
        , m_param_size{0}
        , m_param_seropt{}
        , m_param2_int{0}
        , m_param_bufferwriter{nullptr}
        , m_cnt(1)
        {}

        CapturedCall(Method int_int_param_method, int64_t int_param1, int64_t int_param2) IPL_NOEXCEPT
        : m_method(int_int_param_method)
        , m_param_bool{false}
        , m_param_int{int_param1}
        , m_param_double{0.0}
        , m_param_size{0}
        , m_param_seropt{}
        , m_param2_int{int_param2}
        , m_param_bufferwriter{nullptr}
        , m_cnt(2)
        {}


        explicit CapturedCall(const std::string& str_param) IPL_NOEXCEPT
        : m_method(Method::MethodPutStringStd)
        , m_param_bool{false}
        , m_param_int{0}
        , m_param_double{0.0}
        , m_param_strstd(str_param)
        , m_param_size{0}
        , m_param_seropt{}
        , m_param2_int{0}
        , m_param_bufferwriter{nullptr}
        , m_cnt(1)
        {}
        explicit CapturedCall(const util::UnicodeString8& str_param) IPL_NOEXCEPT
        : m_method(Method::MethodPutStringU8)
        , m_param_bool{false}
        , m_param_int{0}
        , m_param_double{0.0}
        , m_param_stru8(str_param)
        , m_param_size{0}
        , m_param_seropt{}
        , m_param2_int{0}
        , m_param_bufferwriter{nullptr}
        , m_cnt(1)
        {}
        explicit CapturedCall(const util::UnicodeString16& str_param) IPL_NOEXCEPT
        : m_method(Method::MethodPutStringU16)
        , m_param_bool{false}
        , m_param_int{0}
        , m_param_double{0.0}
        , m_param_stru16(str_param)
        , m_param_size{0}
        , m_param_seropt{}
        , m_param2_int{0}
        , m_param_bufferwriter{nullptr}
        , m_cnt(1)
        {}

        CapturedCall(Method size_param_method, size_t size_param) IPL_NOEXCEPT
        : m_method(size_param_method)
        , m_param_bool{false}
        , m_param_int{0}
        , m_param_double{0.0}
        , m_param_size{size_param}
        , m_param_seropt{}
        , m_param2_int{0}
        , m_param_bufferwriter{nullptr}
        , m_cnt(1)
        {}

        explicit CapturedCall(const std::vector<bool>& bool_arr_param) IPL_NOEXCEPT
        : m_method(Method::MethodPutBooleanArray)
        , m_param_bool{false}
        , m_param_int{0}
        , m_param_double{0.0}
        , m_param_size{0}
        , m_param_seropt{}
        , m_param2_int{0}
        , m_param_bool_vec(bool_arr_param)
        , m_param_bufferwriter{nullptr}
        , m_cnt(1)
        {}
        explicit CapturedCall(const std::vector<int8_t>& int_arr_param) IPL_NOEXCEPT
        : m_method(Method::MethodPutInt8Array)
        , m_param_bool{false}
        , m_param_int{0}
        , m_param_double{0.0}
        , m_param_size{0}
        , m_param_seropt{}
        , m_param2_int{0}
        , m_param_int8_vec(int_arr_param)
        , m_param_bufferwriter{nullptr}
        , m_cnt(1)
        {}
        explicit CapturedCall(const std::vector<uint8_t>& int_arr_param) IPL_NOEXCEPT
        : m_method(Method::MethodPutUInt8Array)
        , m_param_bool{false}
        , m_param_int{0}
        , m_param_double{0.0}
        , m_param_size{0}
        , m_param_seropt{}
        , m_param2_int{0}
        , m_param_uint8_vec(int_arr_param)
        , m_param_bufferwriter{nullptr}
        , m_cnt(1)
        {}
        explicit CapturedCall(const std::vector<int16_t>& int_arr_param) IPL_NOEXCEPT
        : m_method(Method::MethodPutInt16Array)
        , m_param_bool{false}
        , m_param_int{0}
        , m_param_double{0.0}
        , m_param_size{0}
        , m_param_seropt{}
        , m_param2_int{0}
        , m_param_int16_vec(int_arr_param)
        , m_param_bufferwriter{nullptr}
        , m_cnt(1)
        {}
        explicit CapturedCall(const std::vector<uint16_t>& int_arr_param) IPL_NOEXCEPT
        : m_method(Method::MethodPutUInt16Array)
        , m_param_bool{false}
        , m_param_int{0}
        , m_param_double{0.0}
        , m_param_size{0}
        , m_param_seropt{}
        , m_param2_int{0}
        , m_param_uint16_vec(int_arr_param)
        , m_param_bufferwriter{nullptr}
        , m_cnt(1)
        {}
        explicit CapturedCall(const std::vector<int32_t>& int_arr_param) IPL_NOEXCEPT
        : m_method(Method::MethodPutInt32Array)
        , m_param_bool{false}
        , m_param_int{0}
        , m_param_double{0.0}
        , m_param_size{0}
        , m_param_seropt{}
        , m_param2_int{0}
        , m_param_int32_vec(int_arr_param)
        , m_param_bufferwriter{nullptr}
        , m_cnt(1)
        {}
        explicit CapturedCall(const std::vector<uint32_t>& int_arr_param) IPL_NOEXCEPT
        : m_method(Method::MethodPutUInt32Array)
        , m_param_bool{false}
        , m_param_int{0}
        , m_param_double{0.0}
        , m_param_size{0}
        , m_param_seropt{}
        , m_param2_int{0}
        , m_param_uint32_vec(int_arr_param)
        , m_param_bufferwriter{nullptr}
        , m_cnt(1)
        {}
        explicit CapturedCall(const std::vector<int64_t>& int_arr_param) IPL_NOEXCEPT
        : m_method(Method::MethodPutInt64Array)
        , m_param_bool{false}
        , m_param_int{0}
        , m_param_double{0.0}
        , m_param_size{0}
        , m_param_seropt{}
        , m_param2_int{0}
        , m_param_int64_vec(int_arr_param)
        , m_param_bufferwriter{nullptr}
        , m_cnt(1)
        {}
        explicit CapturedCall(const std::vector<uint64_t>& int_arr_param) IPL_NOEXCEPT
        : m_method(Method::MethodPutUInt64Array)
        , m_param_bool{false}
        , m_param_int{0}
        , m_param_double{0.0}
        , m_param_size{0}
        , m_param_seropt{}
        , m_param2_int{0}
        , m_param_uint64_vec(int_arr_param)
        , m_param_bufferwriter{nullptr}
        , m_cnt(1)
        {}
        explicit CapturedCall(const std::vector<float>& float_arr_param) IPL_NOEXCEPT
        : m_method(Method::MethodPutFloatArray)
        , m_param_bool{false}
        , m_param_int{0}
        , m_param_double{0.0}
        , m_param_size{0}
        , m_param_seropt{}
        , m_param2_int{0}
        , m_param_float_vec(float_arr_param)
        , m_param_bufferwriter{nullptr}
        , m_cnt(1) {}

        explicit CapturedCall(const std::vector<double>& double_arr_param) IPL_NOEXCEPT
        : m_method(Method::MethodPutDoubleArray)
        , m_param_bool{false}
        , m_param_int{0}
        , m_param_double{0.0}
        , m_param_size{0}
        , m_param_seropt{}
        , m_param2_int{0}
        , m_param_double_vec(double_arr_param)
        , m_param_bufferwriter{nullptr}
        , m_cnt(1)
        {}
        explicit CapturedCall(const std::vector<std::string>& std_str_arr_param) IPL_NOEXCEPT
        : m_method(Method::MethodPutStringArray)
        , m_param_bool{false}
        , m_param_int{0}
        , m_param_double{0.0}
        , m_param_size{0}
        , m_param_seropt{}
        , m_param2_int{0}
        , m_param_std_string_vec(std_str_arr_param)
        , m_param_bufferwriter{nullptr}
        , m_cnt(1)
        {}

        CapturedCall(Method opt_param_method, const SerializerOptions& ser_opt_param) IPL_NOEXCEPT
            : m_method{opt_param_method}
            , m_param_bool{true}
            , m_param_int{0}
            , m_param_double{0.0}
            , m_param_size{0}
            , m_param_seropt{ser_opt_param}
            , m_param2_int{0}
            , m_param_bufferwriter{nullptr}
            , m_cnt{2/*bool+opt*/} {}

        CapturedCall(Method opt_param_method, const ArrayOptions& arr_opt_param) IPL_NOEXCEPT
            : m_method{opt_param_method}
            , m_param_bool{true}
            , m_param_int{0}
            , m_param_double{0.0}
            , m_param_size{0}
            , m_param_arropt{arr_opt_param}
            , m_param2_int{0}
            , m_param_bufferwriter{nullptr}
            , m_cnt{2/*bool+opt*/} {}

        CapturedCall(Method opt_param_method, bool bool_param) IPL_NOEXCEPT
            : m_method{opt_param_method}
            , m_param_bool{bool_param}
            , m_param_int{0}
            , m_param_double{0.0}
            , m_param_size{0}
            , m_param2_int{0}
            , m_param_bufferwriter{nullptr}
            , m_cnt{1} {}

        CapturedCall(Method opt_param_method, util::ByteBufferWriter* writer_param, const SerializerOptions& ser_opt_param) IPL_NOEXCEPT
            : m_method{opt_param_method}
            , m_param_bool{true}
            , m_param_int{0}
            , m_param_double{0.0}
            , m_param_size{0}
            , m_param_seropt{ser_opt_param}
            , m_param2_int{0}
            , m_param_bufferwriter{writer_param}
            , m_cnt{3/*ptr+bool+opt*/} {}

        CapturedCall(Method opt_param_method, util::ByteBufferWriter* writer_param, bool bool_param) IPL_NOEXCEPT
            : m_method{opt_param_method}
            , m_param_bool{bool_param}
            , m_param_int{0}
            , m_param_double{0.0}
            , m_param_size{0}
            , m_param2_int{0}
            , m_param_bufferwriter{writer_param}
            , m_cnt{2/*ptr+bool*/} {}

        CapturedCall(Method str_int_bool_param_method, const std::string& str_param1, int64_t int_param2, bool bool_param3) IPL_NOEXCEPT
            : m_method{str_int_bool_param_method}
            , m_param_bool{bool_param3}
            , m_param_int{int_param2}
            , m_param_double{0.0}
            , m_param_strstd{str_param1}
            , m_param_size{0}
            , m_param2_int{0}
            , m_param_bufferwriter{nullptr}
            , m_cnt{3} {}

        CapturedCall(Method str_int_param_method, const std::string& str_param1, int64_t int_param2) IPL_NOEXCEPT
            : m_method{str_int_param_method}
            , m_param_bool{false}
            , m_param_int{int_param2}
            , m_param_double{0.0}
            , m_param_strstd{str_param1}
            , m_param_size{0}
            , m_param2_int{0}
            , m_param_bufferwriter{nullptr}
            , m_cnt{2} {}

        Method m_method;
        bool m_param_bool;
        int64_t m_param_int;
        double m_param_double;
        std::string m_param_strstd;
        util::UnicodeString8 m_param_stru8;
        util::UnicodeString16 m_param_stru16;
        size_t m_param_size;
        ArrayOptions m_param_arropt;
        MutableSerializerOptions m_param_seropt;    // this needs to be non-const to get assignment
        int64_t m_param2_int;
        std::vector<bool> m_param_bool_vec;
        std::vector<int8_t> m_param_int8_vec;
        std::vector<uint8_t> m_param_uint8_vec;
        std::vector<int16_t> m_param_int16_vec;
        std::vector<uint16_t> m_param_uint16_vec;
        std::vector<int32_t> m_param_int32_vec;
        std::vector<uint32_t> m_param_uint32_vec;
        std::vector<int64_t> m_param_int64_vec;
        std::vector<uint64_t> m_param_uint64_vec;
        std::vector<float> m_param_float_vec;
        std::vector<double> m_param_double_vec;
        std::vector<std::string> m_param_std_string_vec;
        util::ByteBufferWriter* m_param_bufferwriter;
        /*! \brief number of defined parameters, can be used to check if all recorded parameters are used at playback (Method::Method is not counted) */
        unsigned int m_cnt;
    };  /* end inner class CapturedCall */

    std::deque<CapturedCall> m_calllist;

}
IPL_DEPRECATED_POST("do not record json parser callbacks for a later playback")
;

/*!
 *  \brief This class provides a fully implemented IStructuredPushDeserializer interface
 *  even if the provided IStructuredPushDeserializer has not implemented the deserializeStep() method.
 *
 *  \details For memory consumption, see StructuredSerializerRecorder
 *  \see StructuredSerializerRecorder
 */
class UTIL_EXPORT IPL_DEPRECATED_PRE("use the JSONStructuredPushDeserializer instead.")
StructuredPushDeserializerStepAdapter : public IStructuredPushDeserializer {
public:
    StructuredPushDeserializerStepAdapter( IStructuredPushDeserializerSinglePass& deser ) IPL_NOEXCEPT : IStructuredPushDeserializer(), m_deser(deser), m_rec(), m_rec_finished(false) {}
    ~StructuredPushDeserializerStepAdapter() IPL_NOEXCEPT override = default;
    // - cannot be assigned to because of reference type member m_deser.
    // - should not b copy-constructed because then two StepAdapter would use the same underlying
    //   IStructuredPushDeserializerSinglePass im m_deser
    // - could be move-constructed, but for consistency they all are deleted
    StructuredPushDeserializerStepAdapter(const StructuredPushDeserializerStepAdapter&)=delete;
    StructuredPushDeserializerStepAdapter(StructuredPushDeserializerStepAdapter&&)=delete;
    StructuredPushDeserializerStepAdapter& operator=(const StructuredPushDeserializerStepAdapter&)=delete;
    StructuredPushDeserializerStepAdapter& operator=(StructuredPushDeserializerStepAdapter&&)=delete;

    virtual bool beginDeserialize(util::ByteBufferReader* reader, IStructuredSerializer* target) IPL_NOEXCEPT override;

    virtual bool endDeserialize() IPL_NOEXCEPT override;

    virtual IStructuredPushDeserializer::DeserializerResult deserialize() IPL_NOEXCEPT override;

    virtual IStructuredPushDeserializer::DeserializerResult deserializeStep() IPL_NOEXCEPT override;

protected:
    /*! number of remaining steps that have not yet been executed */
    size_t remainingSteps() const IPL_NOEXCEPT {return m_rec.remainingSteps();}

protected:
    IStructuredPushDeserializerSinglePass& m_deser;
IPL_DISABLE_WARNING_PUSH
IPL_DISABLE_WARNING_DEPRECATION
    StructuredSerializerRecorder m_rec;
IPL_DISABLE_WARNING_POP
    bool m_rec_finished;
}
IPL_DEPRECATED_POST("use the JSONStructuredPushDeserializer instead.")
;

} /* namespace serializer */
} /* namespace util */

#endif /* UTIL_SERIALIZER_STRUCTUREDPUSHDESERIALIZERSTEPADAPTER_HXX */

