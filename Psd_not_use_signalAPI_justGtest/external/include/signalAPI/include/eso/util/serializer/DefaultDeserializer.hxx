/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_SERIALIZER_DEFAULTDESERIALIZER_HXX
#define UTIL_SERIALIZER_DEFAULTDESERIALIZER_HXX

#include <ipl_config.h>
#include <util/util_dso.h>

#include <util/serializer/IStreamDeserializer.hxx>
#include <util/serializer/SerializerErrors.hxx>

namespace util
{
namespace serializer
{

/**
 *     \brief
 *         Default implementation of a stream based, byte oriented deserializer

 *         This is only a base class for specialized DefaultDeserializers. It handles the
 *         states in attach/detachBuffer. Streaming operators for primitives that aren't
 *         affected by byte ordering are also implemented here.
 *
 *         All other streaming operators need to be defined by implementing classes.
 *
 *         No special actions are performed upon attachBuffer/detachBuffer.
 *
 *         Byte oriented serializer means that primitives aren't stored aligned or packed, no
 *         padding etc. will be performed. Smallest unit used is a byte.
**/
class UTIL_EXPORT DefaultDeserializer :
    public IStreamDeserializer
{
public: // methods
    //! Starts without an attached buffer
    DefaultDeserializer(Sanity &sanity=insanity) IPL_NOEXCEPT;

    virtual void attachBuffer(util::transport::Readable r) IPL_NOEXCEPT;

    virtual size_t detachBuffer() IPL_NOEXCEPT;

    using IStreamDeserializer::operator>>;
    virtual IStreamDeserializer& operator>>(bool &val) IPL_NOEXCEPT;

    virtual IStreamDeserializer& operator>>(int8_t &val) IPL_NOEXCEPT;
    virtual IStreamDeserializer& operator>>(uint8_t &val) IPL_NOEXCEPT;

    virtual IStreamDeserializer& operator>>(serializer::Flags &f) IPL_NOEXCEPT;

    virtual IStreamDeserializer& operator>>(serializer::Array<bool> &a) IPL_NOEXCEPT;

    virtual IStreamDeserializer& operator>>(ipl::vector<bool> &v) IPL_NOEXCEPT;

    virtual IStreamDeserializer& operator>>(serializer::Array<int8_t> &a) IPL_NOEXCEPT;
    virtual IStreamDeserializer& operator>>(serializer::Array<uint8_t> &a) IPL_NOEXCEPT;

protected: // methods
    /**
     *    \brief
     *        Perform preparatory steps for deserialization of the given primitive value.

     *        Calls prepareBytes() for a primtive value. It calculates the size of the
     *        primitive in bytes and calls prepareBytes() with that information.
     **/
    template <typename PRIMITIVE>
    size_t prepareVal(const PRIMITIVE val) IPL_NOEXCEPT
    {
        return this->prepareBytes(sizeof(val));
    }

    /**
     *    \brief
     *        Perform preparatory steps for deserialization of the given array

     *        Calls prepareBytes() for an array of primitives. It calculates the amount of
     *        bytes needed for serialization of the given array and calls prepareBytes()
     *        with that information.
     **/
    template <typename PRIMITIVE>
    size_t prepareArray(const Array<PRIMITIVE> val) IPL_NOEXCEPT
    {
        return this->prepareBytes( val.size() * sizeof(PRIMITIVE) );
    }

    /**
     *    \brief
     *        Perform preparatory steps for deserialization of the given number of bytes

     *        This function is to be called by the implementation of the streaming
     *        operators. It checks two things:
     *
     *        - that m_data_attached is true
     *        - that the associated buffer m_data has enough space left to read \c bytes
     *        bytes.
     *
     *        If one of these conditions isn't met then an according exception is thrown.
     *
     *        If the state of the deserializer is okay to perform deserialization then
     *        m_data_pos will be positioned just after the last byte that will be read
     *        during the upcoming deserialization operation. The old m_data_pos is
     *        returned from the function.
     *    \param[in] bytes
     *        Number of bytes needed to be read for deserialization
     *    \errorindicator
     *        via hasError()
     *    \errors
     *        serializer::Error with IDs:
     *
     *        - INVALID_MODE if m_data_attached is false
     *        - READABLE_UNDERFLOW if there is not enough space left to read \c bytes
     *        bytes from.
     *    \return
     *        Byte position in m_data where to start deserialization from.
     **/
    size_t prepareBytes(const size_t bytes) IPL_NOEXCEPT
    {
        if( ! m_data_attached )
        {
            ipl_raise( serializer::Error, INVALID_MODE );
            setError();
            return (size_t)-1;
        }

        if(bytes>=m_sanity.dont_warn_below_bytes)
            if(m_sanity.block_size(bytes)) {
                ipl_raise(serializer::Error, INSANE_SIZE, m_size);
                setError();
                return (size_t)-1;
            }

        if( (m_size - m_data_pos) < bytes )
        {
            ipl_raise( serializer::Error, READABLE_UNDERFLOW, m_size, m_data_pos + bytes );
            setError();
            return (size_t)-1;
        }

        m_data_pos += bytes;

        return m_data_pos - bytes;
    }

protected: // protected members
    Sanity &m_sanity;

    //! whether m_data is a valid attached buffer
    bool m_data_attached;

    //! current buffer where serialized data goes to
    util::transport::Readable m_readable;

    //! attached byte buffer
    const uint8_t *m_data;

    //! current reading position in m_data
    size_t m_data_pos;

    //! cached size of m_readable
    size_t m_size;
}; // class IStreamDeserializer

} // end namespace serializer
} // end namespace util

// inlined code
#include <util/serializer/DefaultDeserializer.inl>


#endif
