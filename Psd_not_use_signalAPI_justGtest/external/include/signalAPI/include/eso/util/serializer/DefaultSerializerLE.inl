/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#include <util/serializer/DefaultSerializerLE.hxx>

namespace util
{
namespace serializer
{

template <typename PRIM>
inline void DefaultSerializerLE::serialize(uint8_t *to, PRIM from) IPL_NOEXCEPT
{
    for( uint_fast8_t byte = 0; byte < sizeof(from); byte++ )
    {
        to[byte] = (uint8_t)(from >> (byte * 8));
    }
}
    
inline IStreamSerializer& DefaultSerializerLE::operator<<(int16_t val) IPL_NOEXCEPT
{
    const size_t pos = this->prepareVal(val);

    if( m_state != CALC && ! hasError() )
        serialize( &m_data[pos], val );

    return *(static_cast<IStreamSerializer*>(this));
}

inline IStreamSerializer& DefaultSerializerLE::operator<<(uint16_t val) IPL_NOEXCEPT
{
    return operator<<(static_cast<int16_t>(val));
}

inline IStreamSerializer& DefaultSerializerLE::operator<<(int32_t val) IPL_NOEXCEPT
{
    const size_t pos = this->prepareVal(val);

    if( m_state != CALC && ! hasError() )
        serialize( &m_data[pos], val );

    return *(static_cast<IStreamSerializer*>(this));
}
inline IStreamSerializer& DefaultSerializerLE::operator<<(uint32_t val) IPL_NOEXCEPT
{
    return operator<<(static_cast<int32_t>(val));
}

inline IStreamSerializer& DefaultSerializerLE::operator<<(int64_t val) IPL_NOEXCEPT
{
    const size_t pos = this->prepareVal(val);

    if( m_state != CALC && ! hasError() )
        serialize( &m_data[pos], val );

    return *(static_cast<IStreamSerializer*>(this));
}

inline IStreamSerializer& DefaultSerializerLE::operator<<(uint64_t val) IPL_NOEXCEPT
{
    return operator<<(static_cast<int64_t>(val));
}

inline IStreamSerializer& DefaultSerializerLE::operator<<(float val) IPL_NOEXCEPT
{
    // floating point seems to be a real trouble with searialization.
    //
    // - binary transmission is hard to come by as of unknown differences between platforms
    // (e.g. ARM LE has mirrored data at 32-bit border of double in respect to x86)
    // - string representation by way sprintf/sscanf is in principle possible but one has to
    // think hardly how to actually parametrize the format string (not to speak of java) to
    // actually read back the same value that you wrote out to the string.
    // - Maybe there also is a possibility to shift the floating point to an integer
    // representation and then transmit that. But that requires good knowledge about IEEE
    // format.
    //
    // don't use sizeof here as it might return something different than 4
    // (but that would be the end of things, would it?)
    const size_t pos = this->prepareBytes(4);

    if( m_state != CALC && ! hasError() )
    {
        void *val_ptr = &val;
        // NOTE: cast to void* is neccessary to disallow optimizations by the compiler that
        // make binary operations impossible (release build warning gcc: "dereferencing
        // type-punned pointer will break stict-aliasing rules)
        serialize( &m_data[pos], *(uint32_t*)val_ptr);
    }

    return *(static_cast<IStreamSerializer*>(this));
}

inline IStreamSerializer& DefaultSerializerLE::operator<<(double val) IPL_NOEXCEPT
{
    // don't use sizeof here as it might return something different than 8
    // (but that would be the end of things, would it?)
    const size_t pos = this->prepareBytes(8);

    if( m_state != CALC && ! hasError() )
    {
        void *val_ptr = &val;
        serialize( &m_data[pos], *(uint64_t*)val_ptr);
    }

    return *(static_cast<IStreamSerializer*>(this));
}

inline IStreamSerializer& DefaultSerializerLE::operator<<(const serializer::Array<int16_t> &a) IPL_NOEXCEPT
{
    size_t pos = this->prepareArray(a);

    if( ! hasError() )
    {
        uint8_t *data = m_data + pos;

        for( size_t elem = 0; elem < a.size() && m_state != CALC; elem++ )
        {
            serialize( data+sizeof(int16_t)*elem, a[elem] );
        }
    }

    return *(static_cast<IStreamSerializer*>(this));
}
inline IStreamSerializer& DefaultSerializerLE::operator<<(const serializer::Array<uint16_t> &a) IPL_NOEXCEPT
{
    Array<int16_t> b( a.size(), (int16_t*)a.data() );

    return operator<<(b);
}

inline IStreamSerializer& DefaultSerializerLE::operator<<(const serializer::Array<int32_t> &a) IPL_NOEXCEPT
{
    size_t pos = this->prepareArray(a);

    if( ! hasError() )
    {
        uint8_t *data = m_data + pos;
    
        for( size_t elem = 0; elem < a.size() && m_state != CALC; elem++ )
        {
            serialize( data+sizeof(int32_t)*elem, a[elem] );
        }
    }

    return *(static_cast<IStreamSerializer*>(this));
}

inline IStreamSerializer& DefaultSerializerLE::operator<<(const serializer::Array<uint32_t> &a) IPL_NOEXCEPT
{
    Array<int32_t> b( a.size(), (int32_t*)a.data() );

    return operator<<(b);
}

inline IStreamSerializer& DefaultSerializerLE::operator<<(const serializer::Array<int64_t> &a) IPL_NOEXCEPT
{
    size_t pos = this->prepareArray(a);

    if( ! hasError() )
    {
        uint8_t *data = m_data + pos;
    
        for( size_t elem = 0; elem < a.size() && m_state != CALC; elem++ )
        {
            serialize( data+sizeof(int64_t)*elem, a[elem] );
        }
    }

    return *(static_cast<IStreamSerializer*>(this));
}

inline IStreamSerializer& DefaultSerializerLE::operator<<(const serializer::Array<uint64_t> &a) IPL_NOEXCEPT
{
    Array<int64_t> b( a.size(), (int64_t*)a.data() );

    return operator<<(b);
}

inline IStreamSerializer& DefaultSerializerLE::operator<<(const serializer::Array<float> &a) IPL_NOEXCEPT
{
    size_t pos = this->prepareArray(a);

    if( ! hasError() )
    {
        uint8_t *data = m_data + pos;

        for( size_t elem = 0; elem < a.size() && m_state != CALC; elem++ )
        {
            serialize( data+sizeof(uint32_t)*elem, *(uint32_t*)(void*)&a[elem] );
        }
    }

    return *(static_cast<IStreamSerializer*>(this));
}

inline IStreamSerializer& DefaultSerializerLE::operator<<(const serializer::Array<double> &a) IPL_NOEXCEPT
{
    size_t pos = this->prepareArray(a);

    if( ! hasError() )
    {
        uint8_t *data = m_data + pos;

        for( size_t elem = 0; elem < a.size() && m_state != CALC; elem++ )
        {
            serialize( data+sizeof(uint64_t)*elem, *(uint64_t*)(void*)&a[elem] );
        }
    }

    return *(static_cast<IStreamSerializer*>(this));
}


} // end namespace serializer
} // end namespace
