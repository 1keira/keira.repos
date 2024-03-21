/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_SERIALIZERBE_DEFAULTSERIALIZERBE_HXX
#define UTIL_SERIALIZERBE_DEFAULTSERIALIZERBE_HXX

#include <ipl_config.h>
#include <util/util_dso.h>
#include <util/serializer/DefaultSerializer.hxx>

namespace util
{
namespace serializer
{

/**
 *     \brief
 *         Implementation of stream based, byte oriented serializer using big-endian
 *         representation.

 *         All streaming operators not defined by DefaultSerializer are implemented in this
 *         class using big-endian byte order.
**/
class DefaultSerializerBE :
    public DefaultSerializer
{
public: // public methods
    DefaultSerializerBE(Sanity &sanity=insanity) IPL_NOEXCEPT : DefaultSerializer(sanity) {}

    virtual uint8_t getSerializerID() IPL_NOEXCEPT
    { return BE_SERIALIZER_ID; }

    // import <<bool, <<int8_t, <<uint8_t and friends:
    using DefaultSerializer::operator<<;

    virtual IStreamSerializer& operator<<(int16_t val) IPL_NOEXCEPT;
    virtual IStreamSerializer& operator<<(uint16_t val) IPL_NOEXCEPT;

    virtual IStreamSerializer& operator<<(int32_t val) IPL_NOEXCEPT;
    virtual IStreamSerializer& operator<<(uint32_t val) IPL_NOEXCEPT;

    virtual IStreamSerializer& operator<<(int64_t val) IPL_NOEXCEPT;
    virtual IStreamSerializer& operator<<(uint64_t val) IPL_NOEXCEPT;

    virtual IStreamSerializer& operator<<(float val) IPL_NOEXCEPT;
    virtual IStreamSerializer& operator<<(double val) IPL_NOEXCEPT;

    virtual IStreamSerializer& operator<<(const serializer::Array<int16_t> &a) IPL_NOEXCEPT;
    virtual IStreamSerializer& operator<<(const serializer::Array<uint16_t> &a) IPL_NOEXCEPT;

    virtual IStreamSerializer& operator<<(const serializer::Array<int32_t> &a) IPL_NOEXCEPT;
    virtual IStreamSerializer& operator<<(const serializer::Array<uint32_t> &a) IPL_NOEXCEPT;

    virtual IStreamSerializer& operator<<(const serializer::Array<int64_t> &a) IPL_NOEXCEPT;
    virtual IStreamSerializer& operator<<(const serializer::Array<uint64_t> &a) IPL_NOEXCEPT;

    virtual IStreamSerializer& operator<<(const serializer::Array<float> &a) IPL_NOEXCEPT;
    virtual IStreamSerializer& operator<<(const serializer::Array<double> &a) IPL_NOEXCEPT;

protected:
    /**
     *    \brief
     *        copies data from \c from in BE byte order to \c to.
     **/
    template <typename PRIM>
    void serialize(uint8_t *to, PRIM from) IPL_NOEXCEPT;
}; // class DefaultSerializer

} // end namespace serializer
} // end namespace util

// inlined code
#include "util/serializer/DefaultSerializerBE.inl"

#endif
