/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/
#ifndef UTIL_SERIALIZER_ESOBINSTRUCTUREDSERIALIZERBE_HXX
#define UTIL_SERIALIZER_ESOBINSTRUCTUREDSERIALIZERBE_HXX

#include <common/streams/sstream.hxx>
#include <common/types/string.hxx>

#include <util/util_dso.h>
#include <util/serializer/ebin/ESOBinStructuredSerializer.hxx>
#include <util/ByteBuffer.hxx>

namespace util
{
namespace serializer
{

class UTIL_EXPORT ESOBinStructuredSerializerBE : public ESOBinStructuredSerializer {
    public:

        ESOBinStructuredSerializerBE() IPL_NOEXCEPT
        : ESOBinStructuredSerializer()
        {}

        virtual ~ESOBinStructuredSerializerBE() IPL_NOEXCEPT {}

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

    protected:
        template<typename TYPE>
        bool addToStreamBE(TYPE value) IPL_NOEXCEPT {
            bool failed = false;
            for( uint_fast8_t byte = 0; byte < sizeof(value) && !failed; byte++ ) {
                size_t shift = sizeof(value) - byte - 1;
                failed = m_writer->put((uint8_t)(value >> (shift * 8)));
            }
            return failed;
        }
};

} /* namespace serializer */
} /* namespace util */
#endif /* UTIL_SERIALIZER_ESOBINSTRUCTUREDSERIALIZERLE_HXX */

