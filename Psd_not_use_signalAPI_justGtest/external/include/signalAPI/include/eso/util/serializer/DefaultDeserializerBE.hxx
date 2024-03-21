/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_SERIALIZERBE_DEFAULTDESERIALIZERBE_HXX
#define UTIL_SERIALIZERBE_DEFAULTDESERIALIZERBE_HXX

#include <ipl_config.h>
#include <util/util_dso.h>

#include <util/serializer/DefaultDeserializer.hxx>

namespace util
{
namespace serializer
{

/**
 *     \brief
 *         Implementation of stream based, byte oriented deserializer expecting big-endian
 *         representation.

 *         All streaming operators not defined by DefaultDeserializer are implemented in this
 *         class using big-endian byte order.
**/
class DefaultDeserializerBE :
    public DefaultDeserializer
{
public: // public methods
    DefaultDeserializerBE(Sanity &sanity=insanity) IPL_NOEXCEPT : DefaultDeserializer(sanity) {}

    virtual uint8_t getSerializerID() IPL_NOEXCEPT
    { return BE_SERIALIZER_ID; }

    virtual bool canHandleSerializer(const uint8_t id) IPL_NOEXCEPT
    {
        if (id == BE_SERIALIZER_ID)
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

}; // class IStreamDeserializer

} // end namespace serializer
} // end namespace util

// inlined code
#include <util/serializer/DefaultDeserializerBE.inl>

#endif
