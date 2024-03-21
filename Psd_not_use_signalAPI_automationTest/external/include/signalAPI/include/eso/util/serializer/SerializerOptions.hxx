/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_SERIALIZER_SERIALIZER_OPTIONS_HXX
#define UTIL_SERIALIZER_SERIALIZER_OPTIONS_HXX

#include <util/UInt32Tag.hxx>

#include <map>
#include <array>
#include <vector>


namespace util {

namespace serializer {

enum class OptionTag : uint32_t {

   array_length_size  = UInt32Tag ("alsz"),
   length_size        = UInt32Tag ("slzs"),
   struct_length_size = UInt32Tag ("strs"),
   enum_size          = UInt32Tag ("ensz"),
   big_endian         = UInt32Tag ("bigE"),


};

using SerializerOptions = const std::map<OptionTag, int>;
using MutableSerializerOptions = std::map<OptionTag, int>;


class ArrayOptions {

public:
    enum class ArrayType {
        k_dynamicSize,
        k_fixedSize
    };

    struct Limits {
        uint32_t min;  // min=0 => no m limit
        uint32_t max;  // max=0 => no limit
    };

private:
    std::vector<Limits>   m_limits;  // one entry per dimension

public:

    ArrayOptions () = default;

    Limits getLimits (size_t  dimension = 1)  const {
        if (dimension-1 <  m_limits.size()) {
            return m_limits[dimension-1];
        } else {
            return Limits{0,0};
        }
    }

    ArrayOptions(const std::vector<Limits>&  limits)
     : m_limits(limits)
    {
    }

    ArrayType  getArrayType() const
    {
        for (auto&  val : m_limits) {
            if ((val.min != val.max) || (val.max == 0)) return ArrayType::k_dynamicSize;
        }
        return ArrayType::k_fixedSize;
    }

    bool isValid() const {
        for (auto& val : m_limits) {
            if (val.min > val.max) return false;
        }
        return true;
    }
};

} // namespace serializer
} // namespace util

#endif // UTIL_SERIALIZER_SERIALIZER_OPTIONS_HXX
