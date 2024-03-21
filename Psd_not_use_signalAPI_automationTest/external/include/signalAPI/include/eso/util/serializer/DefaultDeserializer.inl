/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#include <util/serializer/DefaultDeserializer.hxx>
#include <common/ByteOrder.hxx>
#include <string.h> // memcpy

namespace util
{
namespace serializer
{
    
inline IStreamDeserializer& DefaultDeserializer::operator>>(bool &val) IPL_NOEXCEPT
{
    // don't use sizeof here as it might not be 1
    const size_t pos = this->prepareBytes(1);

    if(!hasError())
        val = (m_data[pos] == 0xFF ? true : false);

    return *(static_cast<IStreamDeserializer*>(this));
}

inline IStreamDeserializer& DefaultDeserializer::operator>>(int8_t &val) IPL_NOEXCEPT
{
    const size_t pos = this->prepareVal(val);

    if(!hasError())
        val = m_data[pos];

    return *(static_cast<IStreamDeserializer*>(this));
}

inline IStreamDeserializer& DefaultDeserializer::operator>>(uint8_t &val) IPL_NOEXCEPT
{
    const size_t pos = this->prepareVal(val);

    if(!hasError())
        val = m_data[pos];

    return *(static_cast<IStreamDeserializer*>(this));
}

inline IStreamDeserializer& DefaultDeserializer::operator>>(serializer::Flags &f) IPL_NOEXCEPT
{
    size_t bits = f.getBitAmount();
    size_t needed_bytes = bits ? 1 : 0;

    // user has to specify expected number of bits for us to know correct number of bytes to
    // deserialize
    
    while( bits > 8 )
    {
        bits -= 8;
        needed_bytes++;
    }

    size_t pos = this->prepareBytes(needed_bytes);

    if( ! hasError() )
    {
        // bytes are expected with highest byte first in the binary stream (independent of
        // endianess)
    
        uint32_t flags = 0;
    
        for( size_t byte = needed_bytes; byte > 0; byte -- )
        {
            flags <<= 8;
            flags |= m_data[pos];
            pos++;
        }

        f.setValue(flags);
    }

    return *(static_cast<IStreamDeserializer*>(this));
}

inline IStreamDeserializer& DefaultDeserializer::operator>>(serializer::Array<bool> &a) IPL_NOEXCEPT
{
    // don't use sizeof here as it might return something different than 1
    const size_t needed_bytes = a.size() * 1;

    size_t pos = this->prepareBytes(needed_bytes);

    if( ! hasError() )
    {
        for( size_t elem = 0; elem < a.size(); elem++ )
        {
            a[elem] = ( m_data[pos] == 0xFF ? true : false);
            pos++;
        }
    }

    return *(static_cast<IStreamDeserializer*>(this));
}

inline IStreamDeserializer& DefaultDeserializer::operator>>(ipl::vector<bool> &v) IPL_NOEXCEPT
{
    const size_t needed_bytes = v.size() * 1;
    size_t pos = this->prepareBytes(needed_bytes);

    if( ! hasError() )
    {
        for( size_t elem = 0; elem < v.size(); elem++ )
        {
            v[elem] = ( m_data[pos] == 0xFF ? true : false);
            pos++;
        }
    }

    return *(static_cast<IStreamDeserializer*>(this));
}

inline IStreamDeserializer& DefaultDeserializer::operator>>(serializer::Array<int8_t> &a) IPL_NOEXCEPT
{
    size_t pos = this->prepareArray(a);

    if(! hasError() )
    {

        memcpy(a.data(), m_data + pos, a.size());
    }

    return *(static_cast<IStreamDeserializer*>(this));
}

inline IStreamDeserializer& DefaultDeserializer::operator>>(serializer::Array<uint8_t> &a) IPL_NOEXCEPT
{
    size_t pos = this->prepareArray(a);

    if(! hasError() )
    {
        memcpy(a.data(), m_data + pos, a.size());
    }

    return *(static_cast<IStreamDeserializer*>(this));
}

} // end namespace serializer
} // end namespace
