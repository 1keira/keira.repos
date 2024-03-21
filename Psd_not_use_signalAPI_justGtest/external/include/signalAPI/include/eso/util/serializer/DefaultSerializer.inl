/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#include <util/serializer/DefaultSerializer.hxx>
#include <common/ByteOrder.hxx>

namespace util
{
namespace serializer
{
    
inline IStreamSerializer& DefaultSerializer::operator<<(bool val) IPL_NOEXCEPT
{
    // don't use sizeof here as it might return something different than 1
    const size_t pos = this->prepareBytes(1);

    if( !hasError() && m_state != CALC )
        // acc. to serializer spec. uses ff for true
        m_data[pos] = val ? 0xFF : 0x00;

    return *(static_cast<IStreamSerializer*>(this));
}

inline IStreamSerializer& DefaultSerializer::operator<<(int8_t val) IPL_NOEXCEPT
{
    const size_t pos = this->prepareVal(val);

    if( !hasError() && m_state != CALC )
        m_data[pos] = val;

    return *(static_cast<IStreamSerializer*>(this));
}

inline IStreamSerializer& DefaultSerializer::operator<<(uint8_t val) IPL_NOEXCEPT
{
    return operator<<(static_cast<int8_t>(val));
}

inline IStreamSerializer& DefaultSerializer::operator<<(const serializer::Flags &f) IPL_NOEXCEPT
{
    size_t bits = f.getBitAmount();
    size_t needed_bytes = bits ? 1 : 0;
    
    // flags are serialized with byte granularity i.e. so only many bytes are serialized that
    // are needed to store all required bits from f.

    while( bits > 8 )
    {
        bits -= 8;
        needed_bytes++;
    }

    size_t pos = this->prepareBytes(needed_bytes);

    // bytes are stored with highest byte first in the binary stream (independent of endianess)

    if( ! hasError() )
    {
        for( size_t byte = needed_bytes; byte > 0 && m_state != CALC; byte-- )
        {
            // get the desired byte
            const uint32_t byte_val = f.getValue() >> ( 8 * (byte - 1) );
            m_data[pos] = static_cast<uint8_t>(byte_val);
            pos++;
        }
    }

    return *(static_cast<IStreamSerializer*>(this));
}

inline IStreamSerializer& DefaultSerializer::operator<<(const serializer::Array<bool> &a) IPL_NOEXCEPT
{
    // don't use sizeof here as it might return something different than 1
    const size_t needed_bytes = a.size() * 1;

    size_t pos = this->prepareBytes(needed_bytes);

    if( ! hasError() )
    {
        for( size_t elem = 0; elem < a.size() && m_state != CALC; elem++ )
        {
            // acc. to serializer spec. uses ff for true
            m_data[pos] = a[elem] ? 0xFF : 0x00;
            pos++;
        }
    }

    return *(static_cast<IStreamSerializer*>(this));
}

inline IStreamSerializer& DefaultSerializer::operator<<(const ipl::vector<bool> &v) IPL_NOEXCEPT
{
    const size_t needed_bytes = v.size() * 1;
    size_t pos = this->prepareBytes(needed_bytes);

    if( ! hasError() )
    {
        for( size_t elem = 0; elem < v.size() && m_state != CALC; elem++ )
        {
            // acc. to serializer spec. uses ff for true
            m_data[pos] = v[elem] ? 0xFF : 0x00;
            pos++;
        }
    }

    return *(static_cast<IStreamSerializer*>(this));
}

inline IStreamSerializer& DefaultSerializer::operator<<(const serializer::Array<int8_t> &a) IPL_NOEXCEPT
{
    size_t pos = this->prepareArray(a);

    if( ! hasError() )
    {
        if(m_state != CALC) {
            memcpy(m_data + pos, a.data(), a.size());
        }
    }

    return *(static_cast<IStreamSerializer*>(this));
}
inline IStreamSerializer& DefaultSerializer::operator<<(const serializer::Array<uint8_t> &a) IPL_NOEXCEPT
{
    size_t pos = this->prepareArray(a);

    if( ! hasError() )
    {
        if(m_state != CALC) {
            memcpy(m_data + pos, a.data(), a.size());
        }
    }

    return *(static_cast<IStreamSerializer*>(this));
}

} // end namespace serializer
} // end namespace
