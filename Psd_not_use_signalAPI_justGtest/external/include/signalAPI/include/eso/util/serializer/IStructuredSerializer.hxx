/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/
#ifndef UTIL_SERIALIZER_ISTRUCTUREDSERIALIZER_HXX
#define UTIL_SERIALIZER_ISTRUCTUREDSERIALIZER_HXX

#include <common/types/string.hxx>
#include <util/util_dso.h>
#include <util/ByteBuffer.hxx>
#include <util/serializer/SerializerOptions.hxx>
#include <util/UnicodeString.hxx>
#include <array>
#include <vector>

namespace util
{
namespace serializer
{


class UTIL_EXPORT IStructuredSerializer {
    public:

        static const int32_t NO_ID = -1;
        static const int32_t NO_ID_BUT_IDS_WILL_FOLLOW = -2;

        virtual ~IStructuredSerializer() IPL_NOEXCEPT {}

        /*! \brief is called to notify the start of a serialization.
         *
         *  \details beginSerialize must not be called twice in a row without a reset call in between.
         *
         *  \param buffer the output stream where to write the output to
         *  \see IStructuredSerializer::reset
         */
        virtual bool beginSerialize(util::ByteBufferWriter* buffer, const SerializerOptions* options = nullptr) IPL_NOEXCEPT = 0;

        /*! \brief is called to notify the end of a serialization.
         *
         *  \details endSerialize must not be called twice in a row without a beginSerialize call before.
         */
        virtual bool endSerialize(size_t& number_uint8_ts) IPL_NOEXCEPT = 0;

        virtual void reset() IPL_NOEXCEPT = 0;

        //! \brief retrieve number of serialized bytes.
        //!
        //! \details The value
        //! is available AFTER beginSerialize. Before this
        //! a value of 0 is returned
        virtual size_t size() const IPL_NOEXCEPT = 0;

        //! \brief retrieve the data
        //!
        //! \details get shall be called only after endSerialize and before a possible reset
        virtual bool get(uint8_t* destination, size_t size, size_t& got) const IPL_NOEXCEPT = 0;

        // ----- basic types -----
        virtual bool putNull() IPL_NOEXCEPT = 0;
        virtual bool putBool(bool b) IPL_NOEXCEPT = 0;
        virtual bool putInt8(int8_t b) IPL_NOEXCEPT = 0;
        virtual bool putUInt8(uint8_t b) IPL_NOEXCEPT = 0;
        virtual bool putInt16(int16_t b) IPL_NOEXCEPT = 0;
        virtual bool putUInt16(uint16_t b) IPL_NOEXCEPT = 0;
        virtual bool putInt32(int32_t i) IPL_NOEXCEPT = 0;
        virtual bool putUInt32(uint32_t i) IPL_NOEXCEPT = 0;
        virtual bool putInt64(int64_t l) IPL_NOEXCEPT = 0;
        virtual bool putUInt64(uint64_t l) IPL_NOEXCEPT = 0;
        virtual bool putFloat(float f) IPL_NOEXCEPT = 0;
        virtual bool putDouble(double d) IPL_NOEXCEPT = 0;
        virtual bool putEnum(int32_t e, int bitsize=32) IPL_NOEXCEPT { return putInt32(e);}
        virtual bool putString(const char* cstring) IPL_NOEXCEPT {
            return putString (std::string(cstring));
        }
        virtual bool putString(const std::string& str) IPL_NOEXCEPT = 0;
        virtual bool putString(const util::UnicodeString8& str) = 0;
        virtual bool putString(const util::UnicodeString16& str) = 0;
        virtual bool putString(const ipl::unicode::String& v) IPL_NOEXCEPT {
            return  putString(std::string(v)); // default behaviour
        }
        // ----- Arrays -----
        virtual bool putNullArray(size_t size) IPL_NOEXCEPT = 0;
        virtual bool putBooleanArray(const std::vector<bool>& b) IPL_NOEXCEPT = 0;
        virtual bool putInt8Array(const std::vector<int8_t>& b) IPL_NOEXCEPT = 0;
        virtual bool putUInt8Array(const std::vector<uint8_t>& b) IPL_NOEXCEPT = 0;
        virtual bool putInt16Array(const std::vector<int16_t>& s) IPL_NOEXCEPT = 0;
        virtual bool putUInt16Array(const std::vector<uint16_t>& s) IPL_NOEXCEPT = 0;
        virtual bool putInt32Array(const std::vector<int32_t>& i) IPL_NOEXCEPT = 0;
        virtual bool putUInt32Array(const std::vector<uint32_t>& i) IPL_NOEXCEPT = 0;
        virtual bool putInt64Array(const std::vector<int64_t>& l) IPL_NOEXCEPT = 0;
        virtual bool putUInt64Array(const std::vector<uint64_t>& l) IPL_NOEXCEPT = 0;
        virtual bool putFloatArray(const std::vector<float>& f) IPL_NOEXCEPT = 0;
        virtual bool putDoubleArray(const std::vector<double>& d) IPL_NOEXCEPT = 0;
        virtual bool putStringArray(const std::vector<std::string>& s) IPL_NOEXCEPT = 0;

        // ----- Complex -----

        // Serializing arrays containing elements
        virtual bool beginArray() IPL_NOEXCEPT = 0;
        virtual bool beginElement() IPL_NOEXCEPT = 0;
        virtual bool endElement() IPL_NOEXCEPT = 0;
        // replaces beginElement and endElement
        virtual bool putEmptyElement()  IPL_NOEXCEPT {return false;};
        virtual bool endArray() IPL_NOEXCEPT = 0;

        // Serializing structs containing fields
        virtual bool beginStruct(const SerializerOptions* options=nullptr) IPL_NOEXCEPT = 0;
        virtual bool endStruct() IPL_NOEXCEPT = 0;

        virtual bool beginField(const std::string& name, int32_t id = NO_ID, bool isOptional=false) IPL_NOEXCEPT = 0;
        virtual bool endField() IPL_NOEXCEPT = 0;
        virtual bool putMissingField(const std::string& name, int32_t id = NO_ID)  IPL_NOEXCEPT { return false;};

        // passing options to serializers
        virtual bool beginArrayOption(const ArrayOptions* options) {return false;}
        virtual bool endArrayOption() { return false; }
        virtual bool beginOption(const SerializerOptions* options) { return false; }
        virtual bool endOption() { return false; }

};

// overloaded functions used for code generation
inline bool serialize(util::serializer::IStructuredSerializer &s, uint8_t value) {
    return s.putUInt8(value);
}

inline bool serialize(util::serializer::IStructuredSerializer &s, int8_t value) {
    return s.putInt8(value);
}

inline bool serialize(util::serializer::IStructuredSerializer &s, uint16_t value) {
    return s.putUInt16(value);
}

inline bool serialize(util::serializer::IStructuredSerializer &s, int16_t value) {
    return s.putInt16(value);
}

inline bool serialize(util::serializer::IStructuredSerializer &s, uint32_t value) {
    return s.putUInt32(value);
}

inline bool serialize(util::serializer::IStructuredSerializer &s, int32_t value) {
    return s.putInt32(value);
}

inline bool serialize(util::serializer::IStructuredSerializer &s, uint64_t value) {
    return s.putUInt64(value);
}

inline bool serialize(util::serializer::IStructuredSerializer &s, int64_t value) {
    return s.putInt64(value);
}

inline bool serialize(util::serializer::IStructuredSerializer &s, bool value) {
    return s.putBool(value);
}

inline bool serialize(util::serializer::IStructuredSerializer &s, float value) {
    return s.putFloat(value);
}

inline bool serialize(util::serializer::IStructuredSerializer &s, double value) {
    return s.putDouble(value);
}

inline bool serialize(util::serializer::IStructuredSerializer &s, const std::string& value) {
    return s.putString(value);
}

inline bool serialize(util::serializer::IStructuredSerializer &s, const util::UnicodeString8& value)
{
    return s.putString(value);
}

inline bool serialize(util::serializer::IStructuredSerializer &s, const util::UnicodeString16& value)
{
    return s.putString(value);
}

inline bool serialize(util::serializer::IStructuredSerializer& s, const std::vector<bool>& v) {
    return s.putBooleanArray(v);
}

inline bool serialize(util::serializer::IStructuredSerializer& s, const std::vector<uint8_t>& v) {
    return s.putUInt8Array(v);
}

inline bool serialize(util::serializer::IStructuredSerializer& s, const std::vector<int8_t>& v) {
    return s.putInt8Array(v);
}

inline bool serialize(util::serializer::IStructuredSerializer& s, const std::vector<uint16_t>& v) {
    return s.putUInt16Array(v);
}

inline bool serialize(util::serializer::IStructuredSerializer& s, const std::vector<int16_t>& v) {
    return s.putInt16Array(v);
}

inline bool serialize(util::serializer::IStructuredSerializer& s, const std::vector<uint32_t>& v) {
    return s.putUInt32Array(v);
}

inline bool serialize(util::serializer::IStructuredSerializer& s, const std::vector<int32_t>& v) {
    return s.putInt32Array(v);
}

inline bool serialize(util::serializer::IStructuredSerializer& s, const std::vector<uint64_t>& v) {
    return s.putUInt64Array(v);
}

inline bool serialize(util::serializer::IStructuredSerializer& s, const std::vector<int64_t>& v) {
    return s.putInt64Array(v);
}

inline bool serialize(util::serializer::IStructuredSerializer& s, const std::vector<float>& v) {
    return s.putFloatArray(v);
}

inline bool serialize(util::serializer::IStructuredSerializer& s, const std::vector<double>& v) {
    return s.putDoubleArray(v);
}


inline bool serialize(util::serializer::IStructuredSerializer& s, const ipl::unicode::String& v) {
    return s.putString(v);
}


template<typename T>
bool serialize(util::serializer::IStructuredSerializer& s, const std::vector<T>& v) {
    if (s.beginArray()) return true;
    for  (const auto& val : v)
    {
        if (s.beginElement()) return true;
        if (serialize(s, val)) return true;
        if (s.endElement()) return true;
    }
    return s.endArray();
}

template<class T,std::size_t N>
bool serialize(util::serializer::IStructuredSerializer& s, const std::array<T,N>& a) {
    if (s.beginArray()) return true;
    for  (const auto& val : a)
    {
        if (s.beginElement()) return true;
        if (serialize(s, val)) return true;
        if (s.endElement()) return true;
    }
    return s.endArray();
}

} /* namespace serializer */
} /* namespace util */

#endif /* UTIL_SERIALIZER_ISTRUCTUREDSERIALIZER_HXX */

