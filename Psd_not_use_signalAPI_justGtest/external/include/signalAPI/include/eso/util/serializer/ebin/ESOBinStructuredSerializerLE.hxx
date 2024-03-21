/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_SERIALIZER_ESOBINSTRUCTUREDSERIALIZERLE_HXX
#define UTIL_SERIALIZER_ESOBINSTRUCTUREDSERIALIZERLE_HXX

#include <common/streams/sstream.hxx>
#include <common/types/string.hxx>

#include <util/util_dso.h>
#include <util/serializer/ebin/ESOBinStructuredSerializer.hxx>
#include <util/ByteBuffer.hxx>

namespace util
{
namespace serializer
{

class UTIL_EXPORT ESOBinStructuredSerializerLE : public ESOBinStructuredSerializer {
    public:

        ESOBinStructuredSerializerLE() IPL_NOEXCEPT
        : ESOBinStructuredSerializer()
        {}

        virtual ~ESOBinStructuredSerializerLE() {}

        virtual bool putInt8(int8_t b) IPL_NOEXCEPT;
        virtual bool putUInt8(uint8_t b) IPL_NOEXCEPT;
        virtual bool putInt16(int16_t b) IPL_NOEXCEPT;
        virtual bool putUInt16(uint16_t b) IPL_NOEXCEPT;
        virtual bool putInt32(int32_t i) IPL_NOEXCEPT;
        virtual bool putUInt32(uint32_t i) IPL_NOEXCEPT;
        virtual bool putInt64(int64_t l) IPL_NOEXCEPT;
        virtual bool putUInt64(uint64_t l) IPL_NOEXCEPT;
        virtual bool putFloat(float f) IPL_NOEXCEPT;
        virtual bool putDouble(double d) IPL_NOEXCEPT;

    protected:
        template<typename TYPE>
        bool addToStreamLE(TYPE value) {
            bool failed = false;
            for( uint_fast8_t byte = 0; byte < sizeof(value) && !failed; byte++ ) {
                failed = m_writer->put((uint8_t)(value >> (byte * 8)));
            }
            return failed;
        }
};

} /* namespace serializer */
} /* namespace util */
#endif /* UTIL_SERIALIZER_ESOBINSTRUCTUREDSERIALIZERLE_HXX */

