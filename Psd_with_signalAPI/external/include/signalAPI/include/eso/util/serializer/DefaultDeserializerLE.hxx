/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_SERIALIZERLE_DEFAULTDESERIALIZERLE_HXX
#define UTIL_SERIALIZERLE_DEFAULTDESERIALIZERLE_HXX

#include <ipl_config.h>
#include <util/util_dso.h>

#include <util/serializer/DefaultDeserializer.hxx>

namespace util
{
namespace serializer
{

//! Implementation of a deserializer for little-endian deserialization
class DefaultDeserializerLE :
    public DefaultDeserializer
{
public: // public methods
    DefaultDeserializerLE(Sanity &sanity=insanity) IPL_NOEXCEPT : DefaultDeserializer(sanity)  {}

    virtual uint8_t getSerializerID() IPL_NOEXCEPT
    { return LE_SERIALIZER_ID; }

    virtual bool canHandleSerializer(const uint8_t id) IPL_NOEXCEPT
    {
        if( id == LE_SERIALIZER_ID )
            return true;
        else
            return false;
    }

    // import >>bool, >>int8_t, >>uint8_t and friends:
    using DefaultDeserializer::operator>>;

    virtual IStreamDeserializer& operator>>(int16_t &val) IPL_NOEXCEPT;
    virtual IStreamDeserializer& operator>>(uint16_t &val) IPL_NOEXCEPT;

    virtual IStreamDeserializer& operator>>(int32_t &val) IPL_NOEXCEPT;
    virtual IStreamDeserializer& operator>>(uint32_t &val) IPL_NOEXCEPT;

    virtual IStreamDeserializer& operator>>(int64_t &val) IPL_NOEXCEPT;
    virtual IStreamDeserializer& operator>>(uint64_t &val) IPL_NOEXCEPT;

    virtual IStreamDeserializer& operator>>(float &val) IPL_NOEXCEPT;
    virtual IStreamDeserializer& operator>>(double &val) IPL_NOEXCEPT;

    virtual IStreamDeserializer& operator>>(serializer::Array<int16_t> &a) IPL_NOEXCEPT;
    virtual IStreamDeserializer& operator>>(serializer::Array<uint16_t> &a) IPL_NOEXCEPT;

    virtual IStreamDeserializer& operator>>(serializer::Array<int32_t> &a) IPL_NOEXCEPT;
    virtual IStreamDeserializer& operator>>(serializer::Array<uint32_t> &a) IPL_NOEXCEPT;

    virtual IStreamDeserializer& operator>>(serializer::Array<int64_t> &a) IPL_NOEXCEPT;
    virtual IStreamDeserializer& operator>>(serializer::Array<uint64_t> &a) IPL_NOEXCEPT;

    virtual IStreamDeserializer& operator>>(serializer::Array<float> &a) IPL_NOEXCEPT;
    virtual IStreamDeserializer& operator>>(serializer::Array<double> &a) IPL_NOEXCEPT;
protected:
    /**
     *    \brief
     *        copies data from \c from in native byte order to \c to.
     **/
    template <typename PRIM>
    void deserialize(PRIM &to, const uint8_t *from) IPL_NOEXCEPT;

}; // class DefaultDeserializerLE

} // end namespace serializer
} // end namespace util

// inlined code
#include <util/serializer/DefaultDeserializerLE.inl>

#endif
