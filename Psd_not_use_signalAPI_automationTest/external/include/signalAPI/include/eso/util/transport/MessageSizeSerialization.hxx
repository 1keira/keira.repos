/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_TRANSPORT_SIZESERIALIZATION_HXX
#define UTIL_TRANSPORT_SIZESERIALIZATION_HXX

#include <ipl_config.h>

#include <common/const_assert.hxx>
#include <util/util_dso.h>

#include <common/stdint.h>

#include <string.h>  // for size_t

namespace util
{

namespace transport
{

/**
 * \brief
 *    Central facility to (de)serialize message sizes

 *    This is a simple struct of a serialized and a non-serialized
 *    version of a message size, to be used for transports that
 *    preserve message borders over a streaming medium.
 *
 *    It is done centrally so that related transport implementations
 *    (like QnxResourceManagerTransport and FileTransport) stay
 *    compatible without further efforts.
**/
class UTIL_EXPORT MessageSizeSerialization
{
public: // types, constants

    // the type for deserialized message sizes
    typedef uint32_t value_type;
    // the type representing the number of bytes for something
    typedef size_t size_type;

    //! \brief
    //! number of bytes needed to represent value_type serialized
    static const size_type DATASIZE = sizeof(value_type);

public: // functions

    /**
     * \brief
     *     Initalizes the current message size value with \c value
     **/
    MessageSizeSerialization(const value_type &value = 0) IPL_NOEXCEPT :
        m_value(value)
    {
        IPL_CONST_ASSERT( DATASIZE == 4 );
        ::memset(m_data, 0, DATASIZE);
    }

    //! sets the current message size value to \c value
    void setValue(const value_type &value) IPL_NOEXCEPT
    {
        m_value = value;
    }

    //! returns the currently set message size value
    value_type getValue() const IPL_NOEXCEPT
    {
        return m_value;
    }

    //! \brief
    //! returns the current serialized representation of the message
    //! size. Contains DATASIZE bytes of valid data.
    unsigned char* getData() IPL_NOEXCEPT
    {
        return &(m_data[0]);
    }

    /**
     * \brief
     *     serialize the currently set value

     *     getData() will return the serialized representation of
     *     the currently set value
     **/
    void serialize() IPL_NOEXCEPT;

    /**
     * \brief
     *     Parse data found in getData() and fill value from it
     **/
    void deserialize() IPL_NOEXCEPT;

protected: // data

    /**
     * \brief
     *     The value to be serialized / the value deserialized

     *     Represents the length of a message in bytes
     **/
    value_type m_value;

    //! \brief serialized representation of \c value
    unsigned char m_data[DATASIZE];
};

}  // end of namespace transport

}  // end of namespace util

#endif
