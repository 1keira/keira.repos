/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#include <util/serializer/DefaultSerializerBE.hxx>

#include <common/const_assert.hxx>
#include <type_traits>

namespace util
{
namespace serializer
{

template <typename PRIM>
inline void DefaultDeserializerBE::deserialize(PRIM &to, const uint8_t *from) IPL_NOEXCEPT
{
    typedef typename std::make_unsigned<PRIM>::type UPRIM;

    to = 0;

    for( uint_fast8_t byte = 0; byte < sizeof(to); byte++ )
    {
        to = (PRIM) ((UPRIM)to | *from);
        if( byte != sizeof(to) - 1 )
            to = (PRIM) ((UPRIM)to << 8);
        from++;
    }
}
    
inline IStreamDeserializer& DefaultDeserializerBE::operator>>(int16_t &val) IPL_NOEXCEPT
{
    const size_t pos = this->prepareVal(val);

    if( ! hasError() )
        deserialize(val, &m_data[pos]);

    return *(static_cast<IStreamDeserializer*>(this));
}

inline IStreamDeserializer& DefaultDeserializerBE::operator>>(uint16_t &val) IPL_NOEXCEPT
{
    const size_t pos = this->prepareVal(val);

    if(!hasError())
        deserialize(val, &m_data[pos]);

    return *(static_cast<IStreamDeserializer*>(this));
}

inline IStreamDeserializer& DefaultDeserializerBE::operator>>(int32_t &val) IPL_NOEXCEPT
{
    const size_t pos = this->prepareVal(val);

    if(!hasError())
        deserialize(val, &m_data[pos]);

    return *(static_cast<IStreamDeserializer*>(this));
}

inline IStreamDeserializer& DefaultDeserializerBE::operator>>(uint32_t &val) IPL_NOEXCEPT
{
    const size_t pos = this->prepareVal(val);

    if(!hasError())
        deserialize(val, &m_data[pos]);

    return *(static_cast<IStreamDeserializer*>(this));
}

inline IStreamDeserializer& DefaultDeserializerBE::operator>>(int64_t &val) IPL_NOEXCEPT
{
    const size_t pos = this->prepareVal(val);

    if(!hasError())
        deserialize(val, &m_data[pos]);

    return *(static_cast<IStreamDeserializer*>(this));
}

inline IStreamDeserializer& DefaultDeserializerBE::operator>>(uint64_t &val) IPL_NOEXCEPT
{
    const size_t pos = this->prepareVal(val);

    if(!hasError())
        deserialize(val, &m_data[pos]);

    return *(static_cast<IStreamDeserializer*>(this));
}

inline IStreamDeserializer& DefaultDeserializerBE::operator>>(float &val) IPL_NOEXCEPT
{
    IPL_CONST_ASSERT( sizeof(float) == sizeof(uint32_t) );
    const size_t pos = this->prepareBytes(4);

    if(!hasError())
        deserialize(*(uint32_t*)(void*)&val, &m_data[pos]);
    
    return *(static_cast<IStreamDeserializer*>(this));
}

inline IStreamDeserializer& DefaultDeserializerBE::operator>>(double &val) IPL_NOEXCEPT
{
    IPL_CONST_ASSERT( sizeof(double) == sizeof(uint64_t) );
    const size_t pos = this->prepareBytes(8);

    if(!hasError())
        deserialize(*(uint64_t*)(void*)&val, &m_data[pos]);
    
    return *(static_cast<IStreamDeserializer*>(this));
}

inline IStreamDeserializer& DefaultDeserializerBE::operator>>(serializer::Array<int16_t> &a) IPL_NOEXCEPT
{
    size_t pos = this->prepareArray(a);

    if( ! hasError() )
    {
        const uint8_t *data = m_data + pos;

        for( size_t elem = 0; elem < a.size(); elem++ )
            deserialize(a[elem], data+sizeof(int16_t)*elem);
    }

    return *(static_cast<IStreamDeserializer*>(this));
}

inline IStreamDeserializer& DefaultDeserializerBE::operator>>(serializer::Array<uint16_t> &a) IPL_NOEXCEPT
{
    size_t pos = this->prepareArray(a);

    if( ! hasError() )
    {
        const uint8_t *data = m_data + pos;

        for( size_t elem = 0; elem < a.size(); elem++ )
            deserialize(a[elem], data+sizeof(uint16_t)*elem);
    }

    return *(static_cast<IStreamDeserializer*>(this));
}

inline IStreamDeserializer& DefaultDeserializerBE::operator>>(serializer::Array<int32_t> &a) IPL_NOEXCEPT
{
    size_t pos = this->prepareArray(a);

    if( ! hasError() )
    {
        const uint8_t *data = m_data + pos;

        for( size_t elem = 0; elem < a.size(); elem++ )
            deserialize(a[elem], data+sizeof(int32_t)*elem);
    }

    return *(static_cast<IStreamDeserializer*>(this));
}

inline IStreamDeserializer& DefaultDeserializerBE::operator>>(serializer::Array<uint32_t> &a) IPL_NOEXCEPT
{
    size_t pos = this->prepareArray(a);

    if( ! hasError() )
    {
        const uint8_t *data = m_data + pos;
        for( size_t elem = 0; elem < a.size(); elem++ )
            deserialize(a[elem], data+sizeof(uint32_t)*elem);
    }

    return *(static_cast<IStreamDeserializer*>(this));
}

inline IStreamDeserializer& DefaultDeserializerBE::operator>>(serializer::Array<int64_t> &a) IPL_NOEXCEPT
{
    size_t pos = this->prepareArray(a);

    if( ! hasError() )
    {
        const uint8_t *data = m_data + pos;
        for( size_t elem = 0; elem < a.size(); elem++ )
            deserialize(a[elem], data+sizeof(int64_t)*elem);
    }

    return *(static_cast<IStreamDeserializer*>(this));
}

inline IStreamDeserializer& DefaultDeserializerBE::operator>>(serializer::Array<uint64_t> &a) IPL_NOEXCEPT
{
    size_t pos = this->prepareArray(a);

    if( ! hasError() )
    {
        const uint8_t *data = m_data + pos;
        for( size_t elem = 0; elem < a.size(); elem++ )
            deserialize(a[elem], data+sizeof(uint64_t)*elem);
    }

    return *(static_cast<IStreamDeserializer*>(this));
}

inline IStreamDeserializer& DefaultDeserializerBE::operator>>(serializer::Array<float> &a) IPL_NOEXCEPT
{
    size_t pos = this->prepareArray(a);

    if( ! hasError() )
    {
        const uint8_t *data = m_data + pos;
        for( size_t elem = 0; elem < a.size(); elem++ )
            deserialize(*(uint32_t*)(void*)&a[elem], data+sizeof(uint32_t)*elem);
    }

    return *(static_cast<IStreamDeserializer*>(this));
}

inline IStreamDeserializer& DefaultDeserializerBE::operator>>(serializer::Array<double> &a) IPL_NOEXCEPT
{
    size_t pos = this->prepareArray(a);

    if( ! hasError() )
    {
        const uint8_t *data = m_data + pos;
        for( size_t elem = 0; elem < a.size(); elem++ )
            deserialize(*(uint64_t*)(void*)&a[elem], data+sizeof(uint64_t)*elem);
    }

    return *(static_cast<IStreamDeserializer*>(this));
}

} // end namespace serializer
} // end namespace
