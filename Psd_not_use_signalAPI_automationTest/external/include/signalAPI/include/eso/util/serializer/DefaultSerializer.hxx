/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_SERIALIZER_DEFAULTSERIALIZER_HXX
#define UTIL_SERIALIZER_DEFAULTSERIALIZER_HXX

#include <ipl_config.h>
#include <util/util_dso.h>
#include <util/serializer/SerializerErrors.hxx>
#include <util/serializer/IStreamSerializer.hxx>

namespace util
{
namespace serializer
{

/**
 *     \brief
 *         Default implementation of a stream based, byte oriented serializer

 *         This is only a base class for specialized DefaultSerializers. It handles the states
 *         in attach/detachBuffer and beginSize/endSizeCalc. Streaming operators for primitives
 *         that aren't affected by byte ordering are also implemented here.
 *
 *         All other streaming operators need to be defined by implementing classes.
 *
 *         No special actions are performed upon attachBuffer/detachBuffer.
 *
 *         Byte oriented serializer means that primitives won't be stored aligned or packed, no
 *         padding etc. will be performed. Smallest unit used is a byte.
**/
class UTIL_EXPORT DefaultSerializer :
    public IStreamSerializer
{
public: // public methods
    //! starts without an attached buffer
    DefaultSerializer(Sanity &sanity=insanity) IPL_NOEXCEPT;

    virtual ~DefaultSerializer() IPL_NOEXCEPT { };

    virtual void attachBuffer(const util::transport::Writeable &w) IPL_NOEXCEPT;

    virtual size_t detachBuffer() IPL_NOEXCEPT;

    virtual void beginSizeCalc() IPL_NOEXCEPT;

    virtual size_t endSizeCalc() IPL_NOEXCEPT;

    using IStreamSerializer::operator<<;
    virtual IStreamSerializer& operator<<(bool val) IPL_NOEXCEPT;

    virtual IStreamSerializer& operator<<(int8_t val) IPL_NOEXCEPT;
    virtual IStreamSerializer& operator<<(uint8_t val) IPL_NOEXCEPT;

    virtual IStreamSerializer& operator<<(const serializer::Flags &f) IPL_NOEXCEPT;

    virtual IStreamSerializer& operator<<(const serializer::Array<bool> &a) IPL_NOEXCEPT;
    virtual IStreamSerializer& operator<<(const ipl::vector<bool> &v) IPL_NOEXCEPT;

    virtual IStreamSerializer& operator<<(const serializer::Array<int8_t> &a) IPL_NOEXCEPT;
    virtual IStreamSerializer& operator<<(const serializer::Array<uint8_t> &a) IPL_NOEXCEPT;

protected: // types
    enum State
    {
        //! current state is undecided, user can set a new operating mode
        IDLE,
        //! current state is serialization -> current m_data is valid
        SERIALIZE,
        //! current state is calculating -> current size is valid, m_data isn't
        CALC
    };

protected: // functions

    /**
     *    \brief
     *        Perform preparatory steps for serialization of the given primitive value.

     *        Calls prepareBytes() for the given primitive value. Calculates the amount of
     *        bytes required for the primitive value \c val and calls prepareBytes() with
     *        that information.
     **/
    template <typename PRIMITIVE>
    size_t prepareVal(const PRIMITIVE val)
    {
        return this->prepareBytes(sizeof(val));
    }

    /**
     *    \brief
     *        Perform preparatory steps for serialization of the given array

     *        Calls prepareBytes() but for the given array. Calculates the amount of bytes
     *        required to serialize the given array and calls prepareBytes() with that
     *        information.
     **/
    template <typename PRIMITIVE>
    size_t prepareArray(const Array<PRIMITIVE> val)
    {
        return this->prepareBytes( val.size() * sizeof(PRIMITIVE) );
    }

    /**
     *    \brief
     *        Perform preparatory steps for serialization of the given amount of bytes.

     *        This function is to be called by the implementation of the streaming
     *        operators. It checks two things:
     *
     *        - that m_state is either CALC or SERIALIZE
     *        - that the associated buffer m_data has enough space left to store
     *        \c bytes bytes.
     *
     *        If one of these conditions isn't met then an according exception is thrown.
     *
     *        If the state of the serializer is okay to perform serialization then
     *        m_data_pos will be positioned just after the last byte that will be written
     *        during the upcoming serialization operation. The old m_data_pos is returned
     *        from the function.
     *    \param[in] bytes
     *        Amount of bytes that are needed for upcoming serialization.
     *    \return
     *        Byte position in m_data where to serialize first byte to.
     *    \errorindicator
     *        via hasError()
     *    \errors
     *        serializer::Error with IDs:
     *
     *        - INVALID_MODE if m_state is IDLE
     *        - WRITEABLE_OVERFLOW if there is not enough space for \c bytes bytes.
     **/
    size_t prepareBytes(const size_t bytes)
    {
        resetError();

        // these error checks could be made DEBUG only to speed up things a bit
        if( m_state == IDLE )
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

        for(unsigned i=0; i<3 /* 3 arbitrary */
                          && m_state==SERIALIZE && m_size-m_data_pos<bytes;
            i++)
            if( handle_overflow(m_data_pos+bytes, i) )
                return (size_t)-1;

        m_data_pos += bytes;

        return m_data_pos - bytes;
    }

    //! \brief Raise an error or do something with the buffer
    //!
    //! If you want inefficient autoresizing buffers,
    //! override, resize and return \c false.
    //!
    //! \return \c true on error raised
    virtual bool handle_overflow(size_t requested_size, unsigned attempt) IPL_NOEXCEPT;

protected: // members
    Sanity &m_sanity;

    //! current buffer where serialized data goes to
    const util::transport::Writeable *m_writeable;

    //! pointer to bytes of attached buffer
    uint8_t *m_data;

    //! current writing position in m_data (points to next free byte)
    size_t m_data_pos;

    //! current operational state of the serializer
    State m_state;

    //! cached size of m_writeable
    size_t m_size;
}; // class DefaultSerializer

} // end namespace serializer
} // end namespace util

// inlined code
#include "util/serializer/DefaultSerializer.inl"

#endif
