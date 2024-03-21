/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_SERIALIZER_ESOBINDESERIALIZER_HXX
#define UTIL_SERIALIZER_ESOBINDESERIALIZER_HXX

#include <common/const_assert.hxx>
#include <common/streams/sstream.hxx>
#include <common/types/string.hxx>

#include <util/util_dso.h>
#include <util/ByteBuffer.hxx>
#include <util/serializer/SerializerErrors.hxx>

namespace util
{
namespace serializer
{

class UTIL_EXPORT ESOBinDeserializer {
    public:

        ESOBinDeserializer() IPL_NOEXCEPT
        : m_reader(nullptr)
        {}

        virtual ~ESOBinDeserializer() IPL_NOEXCEPT  {}

        void reset(util::ByteBufferReader* reader) IPL_NOEXCEPT { m_reader = reader; }

        virtual bool getInt8(int8_t& b) IPL_NOEXCEPT = 0;
        virtual bool getUInt8(uint8_t& b) IPL_NOEXCEPT = 0;
        virtual bool getInt16(int16_t& b) IPL_NOEXCEPT = 0;
        virtual bool getUInt16(uint16_t& b) IPL_NOEXCEPT = 0;
        virtual bool getInt32(int32_t& i) IPL_NOEXCEPT = 0;
        virtual bool getUInt32(uint32_t& i) IPL_NOEXCEPT = 0;
        virtual bool getInt64(int64_t& l) IPL_NOEXCEPT = 0;
        virtual bool getUInt64(uint64_t& l) IPL_NOEXCEPT = 0;
        virtual bool getFloat(float& f) IPL_NOEXCEPT = 0;
        virtual bool getDouble(double& d) IPL_NOEXCEPT = 0;
        virtual bool getString(std::string& s) IPL_NOEXCEPT {
            if (m_reader == nullptr) {
                ipl_raise( serializer::Error, NO_DATA_FOR_DESERIALIZATION);
                return true;
            }
            uint32_t size = 0;
            if (getUInt32(size)) {
                return true;
            }
            if (m_reader->bytesLeft() < size) {
                ipl_raise( serializer::Error, INSANE_SIZE, m_reader->bytesLeft() );
                return true;
            }
            s.assign((const char*)m_reader->current(), size);
            m_reader->skip(size);
            return false;
        }

    protected:
        util::ByteBufferReader* m_reader;
};

class UTIL_EXPORT ESOBinDeserializerBE : public ESOBinDeserializer {
    public:

        ESOBinDeserializerBE() IPL_NOEXCEPT {}

        virtual ~ESOBinDeserializerBE() IPL_NOEXCEPT {}

        virtual bool getInt8(int8_t& b) IPL_NOEXCEPT { return getFromStream(b) ; }
        virtual bool getUInt8(uint8_t& b) IPL_NOEXCEPT { return getFromStream(b) ; }
        virtual bool getInt16(int16_t& b) IPL_NOEXCEPT { return getFromStream(b) ; }
        virtual bool getUInt16(uint16_t& b) IPL_NOEXCEPT { return getFromStream(b) ; }
        virtual bool getInt32(int32_t& i) IPL_NOEXCEPT { return getFromStream(i) ; }
        virtual bool getUInt32(uint32_t& i) IPL_NOEXCEPT { return getFromStream(i) ; }
        virtual bool getInt64(int64_t& l) IPL_NOEXCEPT { return getFromStream(l) ; }
        virtual bool getUInt64(uint64_t& l) IPL_NOEXCEPT { return getFromStream(l) ; }
        virtual bool getFloat(float& f) IPL_NOEXCEPT {
            IPL_CONST_ASSERT( sizeof(float) == sizeof(uint32_t) );
            return getUInt32(*(uint32_t*)(void*)&f);
        }
        virtual bool getDouble(double& d) IPL_NOEXCEPT {
            IPL_CONST_ASSERT( sizeof(double) == sizeof(uint64_t) );
            return getUInt64(*(uint64_t*)(void*)&d);
        }

    protected:

        template<typename TYPE>
        bool getFromStream(TYPE& value) IPL_NOEXCEPT {
            typedef typename std::make_unsigned<TYPE>::type UTYPE;
            if (m_reader->bytesLeft() < sizeof(value)) {
                ipl_raise( serializer::Error, INSANE_SIZE, m_reader->bytesLeft() );
                return true;
            }
            value = 0;
            const uint8_t* from = m_reader->current();
            for( uint_fast8_t byte = 0; byte < sizeof(value); byte++ ) {
                value = (TYPE) ((UTYPE)value | *from);
                if( byte != sizeof(value) - 1 )
                    value = (TYPE) ((UTYPE)value << 8);
                from++;
            }
            m_reader->skip(sizeof(value));
            return false;
        }
};

class UTIL_EXPORT ESOBinDeserializerLE : public ESOBinDeserializer {
    public:

        ESOBinDeserializerLE() IPL_NOEXCEPT {}

        virtual ~ESOBinDeserializerLE() IPL_NOEXCEPT {}

        virtual bool getInt8(int8_t& b) IPL_NOEXCEPT { return getFromStream(b) ; }
        virtual bool getUInt8(uint8_t& b) IPL_NOEXCEPT { return getFromStream(b) ; }
        virtual bool getInt16(int16_t& b) IPL_NOEXCEPT { return getFromStream(b) ; }
        virtual bool getUInt16(uint16_t& b) IPL_NOEXCEPT { return getFromStream(b) ; }
        virtual bool getInt32(int32_t& i) IPL_NOEXCEPT { return getFromStream(i) ; }
        virtual bool getUInt32(uint32_t& i) IPL_NOEXCEPT { return getFromStream(i) ; }
        virtual bool getInt64(int64_t& l) IPL_NOEXCEPT { return getFromStream(l) ; }
        virtual bool getUInt64(uint64_t& l) IPL_NOEXCEPT { return getFromStream(l) ; }
        virtual bool getFloat(float& f) IPL_NOEXCEPT {
            IPL_CONST_ASSERT( sizeof(float) == sizeof(uint32_t) );
            return getUInt32(*(uint32_t*)(void*)&f);
        }
        virtual bool getDouble(double& d) IPL_NOEXCEPT {
            IPL_CONST_ASSERT( sizeof(double) == sizeof(uint64_t) );
            return getUInt64(*(uint64_t*)(void*)&d);
        }

    protected:

        template<typename TYPE>
        bool getFromStream(TYPE& value) IPL_NOEXCEPT {
            if (m_reader->bytesLeft() < sizeof(value)) {
                ipl_raise( serializer::Error, INSANE_SIZE, m_reader->bytesLeft() );
                return true;
            }
            value = 0;
            const uint8_t* from = m_reader->current();
            from += (sizeof(value) - 1);

            typedef typename std::make_unsigned<TYPE>::type UTYPE;
            for( uint_fast8_t byte = 0; byte < sizeof(value); byte++ ) {
                value = (TYPE) ((UTYPE)value | *from);
                if( byte != sizeof(value) - 1 )
                    value = (TYPE) ((UTYPE)value << 8);
                from--;
            }
            m_reader->skip(sizeof(value));
            return false;
        }
};

} /* namespace serializer */
} /* namespace util */
#endif /* UTIL_SERIALIZER_ESOBINDESERIALIZER_HXX */

