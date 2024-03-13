/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_SERIALIZER_ISTRUCTUREDPULLDESERIALIZER_HXX
#define UTIL_SERIALIZER_ISTRUCTUREDPULLDESERIALIZER_HXX

#include <common/types/map.hxx>
#include <common/types/string.hxx>
#include <util/ByteBuffer.hxx>
#include <util/util_dso.h>
#include <util/serializer/SerializerOptions.hxx>
#include <util/UnicodeString.hxx>
#include <util/serializer/ApiCapability.hxx>

namespace util
{
namespace serializer
{

class UTIL_EXPORT IStructuredPullDeserializer {
    public:
        enum EntryType {
            TypeFailed,
            TypeNone,
            TypeNull,
            TypeBool,
            TypeInt8,
            TypeUInt8,
            TypeInt16,
            TypeUInt16,
            TypeInt32,
            TypeUInt32,
            TypeInt64,
            TypeUInt64,
            TypeFloat,
            TypeDouble,
            TypeString,
            TypeBeginArray,
            TypeNullArray,
            TypeBooleanArray,
            TypeInt8Array,
            TypeUInt8Array,
            TypeInt16Array,
            TypeUInt16Array,
            TypeInt32Array,
            TypeUInt32Array,
            TypeInt64Array,
            TypeUInt64Array,
            TypeFloatArray,
            TypeDoubleArray,
            TypeEnumArray,
            TypeStringArray,
            TypeEndArray,
            TypeBeginStruct,
            TypeEndStruct,
            TypeBeginField,
            TypeEndField,
            TypeBeginElement,
            TypeEndElement
        };

        struct EntryContent {
            union {
                bool            v_bool;
                int8_t          v_int8;
                uint8_t         v_uint8;
                int16_t         v_int16;
                uint16_t        v_uint16;
                int32_t         v_int32;
                uint32_t        v_uint32;
                int64_t         v_int64;
                uint64_t        v_uint64;
                float           v_float;
                double          v_double;
            } u;
            std::string         v_string;
            EntryType           v_type;
        };

        virtual ~IStructuredPullDeserializer() IPL_NOEXCEPT {}

        virtual bool beginDeserialize(util::ByteBufferReader* reader, const SerializerOptions* options = nullptr) IPL_NOEXCEPT = 0;
        virtual bool endDeserialize() IPL_NOEXCEPT = 0;
        virtual void reset() IPL_NOEXCEPT = 0;

        virtual bool getNull() IPL_NOEXCEPT = 0;
        virtual bool getBoolean(bool& v) IPL_NOEXCEPT = 0;
        virtual bool getInt8(int8_t& v) IPL_NOEXCEPT = 0;
        virtual bool getUInt8(uint8_t& v) IPL_NOEXCEPT = 0;
        virtual bool getInt16(int16_t& v) IPL_NOEXCEPT = 0;
        virtual bool getUInt16(uint16_t& v) IPL_NOEXCEPT = 0;
        virtual bool getInt32(int32_t& v) IPL_NOEXCEPT = 0;
        virtual bool getUInt32(uint32_t& v) IPL_NOEXCEPT = 0;
        virtual bool getInt64(int64_t& v) IPL_NOEXCEPT = 0;
        virtual bool getUInt64(uint64_t& v) IPL_NOEXCEPT = 0;
        virtual bool getFloat(float& v) IPL_NOEXCEPT = 0;
        virtual bool getDouble(double& v) IPL_NOEXCEPT = 0;
        virtual bool getEnum(int32_t& v, int bitsize=32, bool is_signed=false) IPL_NOEXCEPT { return getInt32(v);}
        virtual bool getString(std::string& v) IPL_NOEXCEPT = 0;
        virtual bool getString(util::UnicodeString8& str) IPL_NOEXCEPT  { return true;}
        virtual bool getString(util::UnicodeString16& str) IPL_NOEXCEPT { return true;}
        virtual bool getString(ipl::unicode::String& str) IPL_NOEXCEPT {
            std::string tmp;
            if (getString(tmp)) {
                return true;
            }
            str = tmp;
            return false;
        }
        virtual bool getNullArray(size_t& size) IPL_NOEXCEPT = 0;
        virtual bool getBooleanArray(std::vector<bool>& v) IPL_NOEXCEPT = 0;
        virtual bool getInt8Array(std::vector<int8_t>& v) IPL_NOEXCEPT = 0;
        virtual bool getUInt8Array(std::vector<uint8_t>& v) IPL_NOEXCEPT = 0;
        virtual bool getInt16Array(std::vector<int16_t>& v) IPL_NOEXCEPT = 0;
        virtual bool getUInt16Array(std::vector<uint16_t>& v) IPL_NOEXCEPT = 0;
        virtual bool getInt32Array(std::vector<int32_t>& v) IPL_NOEXCEPT = 0;
        virtual bool getUInt32Array(std::vector<uint32_t>& v) IPL_NOEXCEPT = 0;
        virtual bool getInt64Array(std::vector<int64_t>& v) IPL_NOEXCEPT = 0;
        virtual bool getUInt64Array(std::vector<uint64_t>& v) IPL_NOEXCEPT = 0;
        virtual bool getFloatArray(std::vector<float>& v) IPL_NOEXCEPT = 0;
        virtual bool getDoubleArray(std::vector<double>& v) IPL_NOEXCEPT = 0;
        virtual bool getStringArray(std::vector<std::string>& v) IPL_NOEXCEPT = 0;
        //virtual bool getEnumArray(int32_t& v) IPL_NOEXCEPT = 0;

        virtual bool beginArrayOption(const ArrayOptions* options) IPL_NOEXCEPT { return false; }
        virtual bool endArrayOption() { return false; }
        virtual bool beginOption(const SerializerOptions* options) IPL_NOEXCEPT { return false; }
        virtual bool endOption() { return false; }

        virtual bool beginArray() IPL_NOEXCEPT = 0;
        virtual bool isArrayEnd() IPL_NOEXCEPT = 0;
        virtual bool endArray() IPL_NOEXCEPT = 0;
        virtual bool beginElement() IPL_NOEXCEPT = 0;
        virtual bool endElement() IPL_NOEXCEPT = 0;
        virtual bool getEmptyElement(bool& isEmpty) IPL_NOEXCEPT  { isEmpty=false; return false; }
        virtual bool beginStruct(const SerializerOptions* options = nullptr) IPL_NOEXCEPT = 0;
        virtual bool isStructEnd() IPL_NOEXCEPT = 0;
        virtual bool endStruct() IPL_NOEXCEPT = 0;

        // ApiCapability deserializerControlsFieldOrder
        virtual bool beginField(std::string& name) IPL_NOEXCEPT = 0;
        virtual bool skipField() IPL_NOEXCEPT = 0;
        virtual bool endField() IPL_NOEXCEPT = 0;
        virtual const EntryContent& getNextEntry() IPL_NOEXCEPT = 0;
        virtual const EntryContent& peekNextEntry() IPL_NOEXCEPT = 0;

        // ApiCapability applicatationControlsFieldOrder
        static const int32_t NO_ID = -1;
        static const int32_t NO_ID_BUT_IDS_WILL_FOLLOW = -2;
        // for mandotary field
        virtual bool beginMandatoryField(const std::string& name, int32_t id = NO_ID) IPL_NOEXCEPT {return true;};
        virtual bool endMandatoryField() IPL_NOEXCEPT { return true;};
        // for optional field
        virtual bool beginOptionalField(const std::string& name, int32_t id, bool& isAvailable) IPL_NOEXCEPT {return true;};
        virtual bool endOptionalField() IPL_NOEXCEPT {return true;};

        virtual ApiCapabilities getApiCapibilites() IPL_NOEXCEPT { return ApiCapability::deserializerControlsFieldOrder;};

        static std::string type2name(EntryType type) IPL_NOEXCEPT;

    private:
        static std::map<EntryType, std::string>& m_entry2name;
};

// overlaoded functions used for code generation

inline bool deserialize(IStructuredPullDeserializer& s, bool& v) {
    return s.getBoolean(v);
}

inline bool deserialize(IStructuredPullDeserializer& s, uint8_t& v) {
    return s.getUInt8(v);
}

inline bool deserialize(IStructuredPullDeserializer& s, int8_t& v) {
    return s.getInt8(v);
}

inline bool deserialize(IStructuredPullDeserializer& s, uint16_t& v) {
    return s.getUInt16(v);
}

inline bool deserialize(IStructuredPullDeserializer& s, int16_t& v) {
    return s.getInt16(v);
}

inline bool deserialize(IStructuredPullDeserializer& s, uint32_t& v) {
    return s.getUInt32(v);
}

inline bool deserialize(IStructuredPullDeserializer& s, int32_t& v) {
    return s.getInt32(v);
}

inline bool deserialize(IStructuredPullDeserializer& s, uint64_t& v) {
    return s.getUInt64(v);
}

inline bool deserialize(IStructuredPullDeserializer& s, int64_t& v) {
    return s.getInt64(v);
}

inline bool deserialize(IStructuredPullDeserializer& s, float& v) {
    return s.getFloat(v);
}

inline bool deserialize(IStructuredPullDeserializer& s, double& v) {
    return s.getDouble(v);
}

inline bool deserialize(IStructuredPullDeserializer& s, std::string& v) {
    return s.getString(v);
}

inline bool deserialize(IStructuredPullDeserializer& s, util::UnicodeString8& v) {
    return s.getString(v);
}

inline bool deserialize(IStructuredPullDeserializer& s, util::UnicodeString16& v) {
    return s.getString(v);
}

inline bool deserialize(IStructuredPullDeserializer& s, ipl::unicode::String& v) {
    return s.getString(v);
}

inline bool deserialize(IStructuredPullDeserializer& s, std::vector<bool>& v) {
    return s.getBooleanArray(v);
}

inline bool deserialize(IStructuredPullDeserializer& s, std::vector<uint8_t>& v) {
    return s.getUInt8Array(v);
}

inline bool deserialize(IStructuredPullDeserializer& s, std::vector<int8_t>& v) {
    return s.getInt8Array(v);
}

inline bool deserialize(IStructuredPullDeserializer& s, std::vector<uint16_t>& v) {
    return s.getUInt16Array(v);
}

inline bool deserialize(IStructuredPullDeserializer& s, std::vector<int16_t>& v) {
    return s.getInt16Array(v);
}

inline bool deserialize(IStructuredPullDeserializer& s, std::vector<uint32_t>& v) {
    return s.getUInt32Array(v);
}

inline bool deserialize(IStructuredPullDeserializer& s, std::vector<int32_t>& v) {
    return s.getInt32Array(v);
}

inline bool deserialize(IStructuredPullDeserializer& s, std::vector<uint64_t>& v) {
    return s.getUInt64Array(v);
}

inline bool deserialize(IStructuredPullDeserializer& s, std::vector<int64_t>& v) {
    return s.getInt64Array(v);
}

inline bool deserialize(IStructuredPullDeserializer& s, std::vector<float>& v) {
    return s.getFloatArray(v);
}

inline bool deserialize(IStructuredPullDeserializer& s, std::vector<double>& v) {
    return s.getDoubleArray(v);
}


template<class T>
bool deserialize(util::serializer::IStructuredPullDeserializer& s, std::vector<T>& v) {
    v.clear();
    if (s.beginArray()) return true;
    while (!s.isArrayEnd()) {
        T value;
        if (s.beginElement()) return true;
        if (deserialize(s, value)) return true;
        v.emplace_back(std::move(value));
        if (s.endElement()) return true;
    }
    return s.endArray();
}

template<class T,std::size_t N>
bool deserialize(util::serializer::IStructuredPullDeserializer& s, std::array<T,N>& a) {
    if (s.beginArray()) return true;
    auto it = a.begin();
    while (!s.isArrayEnd() && it!= a.end()) {
        T& value = *it++;
        if (s.beginElement()) return true;
        if (deserialize(s, value)) return true;
        if (s.endElement()) return true;
    }
    return s.endArray();
}



} /* namespace serializer */
} /* namespace util */

#endif /* UTIL_SERIALIZER_ISTRUCTUREDPULLDESERIALIZER_HXX */

