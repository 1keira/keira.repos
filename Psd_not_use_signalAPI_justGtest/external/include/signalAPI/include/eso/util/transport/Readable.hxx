/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_READABLE_HXX
#define UTIL_READABLE_HXX

#include <ipl_config.h>

#include <common/Macros.hxx>
#include <common/types/utility.hxx> // ipl::pair

#include <util/util_dso.h>

#include <util/transport/Buffer.hxx>
#include <util/transport/EmptyBuffer.hxx>

namespace util
{
namespace transport
{

// fwd. declaration
class Writeable;

/**
 * \brief
 *     read-only frontend to a Buffer

 *     Holds only a pointer an actual Buffer object. Exports a
 *     read-only frontend to that Buffer. Read-only access involves
 *     getting buffer size, const pointer to data or const reference to
 *     individual bytes in the buffer.
 **/
class Readable
{
    // friends

    // our sibling class needs access to our protected members (for
    // Writeable(Readable&))
    friend class util::transport::Writeable;

public: // member functions

    /**
     * \brief
     *     Default constructor uses an empty buffer.
     **/
    inline Readable() IPL_NOEXCEPT :
        // delFunc is important to prevent deletion of
        // EmptyBuffer
        m_buf((Buffer*)&Buffer::EMPTY,
            Buffer::EmptyBuffer::delFunc),
        m_offsets(0, 0)
    { }

    /**
     * \brief
     *     Be a frontend to provided buffer buf.
     **/
    inline Readable(const Buffer::BufferPtr buf) IPL_NOEXCEPT :
        m_buf(buf),
        m_offsets(0, 0)
    { }

    /**
     * \brief
     *     Simple copy constructor.

     *     Also takes over any buffer windows from other.
     **/
    inline Readable(const Readable &other) IPL_NOEXCEPT :
        m_buf(other.m_buf),
        m_offsets(other.m_offsets)
    { }

    /**
     * \brief
     *     Assignment
     **/
    inline Readable& operator=(const Readable &other) IPL_NOEXCEPT {
        if ( this != &other ) {
            m_buf = other.m_buf;
            m_offsets = other.m_offsets;
        }
        return *this;
    }

    /**
     * \brief
     *     Destructor does nothing special (SharedPtr cares for
     *     ref. counting)
     **/
    inline virtual ~Readable() IPL_NOEXCEPT
    { }

    /**
     * \brief
     *     Return a new Readable object with an added buffer window

     *     This function is suitable if you have a const Readable
     *     to which you can't add a buffer window directly. Or if
     *     you simply don't want to modify an existing Readable.
     *
     *     The semantics of p_start_offset and p_length are equal
     *     to those of setBuffer().
     **/
    inline Readable subBuffer(
        const size_t p_start_offset,
        size_t p_length = SIZE_MAX) const IPL_NOEXCEPT
    {
        Readable ret(*this);

        ret.setWindow(p_start_offset, p_length);

        return ret;
    }

    /**
     * \brief
     *     Reduce the visible buffer area via a buffer window

     *     The buffer window that will be visible is the byte range
     *     from [p_offset to (p_offset + p_length)] of the
     *     currently visible buffer. After return of this function
     *     size() returns the reduced size of the now visible
     *     sub-buffer.
     *
     *     data() will return a pointer to the address of the prior
     *     buffer start plus p_offset bytes. dataAt() and
     *     operator[]() will count the provided offsets starting at
     *     p_offset.
     *
     *     It is possible to call subBuffer multiple times which
     *     will continuously shrink the visible buffer window to
     *     the given ranges. It will not be possible to grow the
     *     visible buffer window once shrank.
     *
     *     If p_length is greater than (size() - p_offset) (i.e.
     *     beyond the actual length of the currently visible
     *     buffer) then p_length will be treated as being (size() -
     *     p_offset).
     * \param[in] p_offset
     *     The start offset in bytes to use for the new sub-buffer
     *     window. May not be greater then current size(). May be
     *     zero which will have no effect on the buffer start
     *     address then.
     * \param[in] p_length
     *     Length of the buffer that should be visible. May range
     *     from zero to current (size() - p_offset). If greater
     *     then it will be reduced to that maximum value.
     * \return
     *     A reference to the current object.
     **/
    inline void setWindow(
        const size_t p_offset,
        size_t p_length = SIZE_MAX) IPL_NOEXCEPT
    {
        IPL_ASSERT( p_offset <= size() );

        const size_t new_size = size() - p_offset;

        // don't grow already existing window or outside of
        // buffer area.
        if( p_length > new_size )
            p_length = new_size;

        const size_t length_offset = new_size - p_length;

        // add the new offsets
        m_offsets.first = p_offset + m_offsets.first;
        m_offsets.second = length_offset + m_offsets.second;
    }

    //! returns the size of the current buffer
    inline size_t size() const IPL_NOEXCEPT
    {
        return m_buf->size() - m_offsets.first -
            m_offsets.second;
    }

    /**
     * \brief
     *     Return a reference to the byte in the buffer data at the
     *     given offset position
     **/
    inline const uint8_t& operator[](const size_t p_offset) const IPL_NOEXCEPT
    {
        return *(data() + p_offset);
    }

    /**
     * \brief
     *     Return pointer to buffer data with byte offset at the
     *     beginning
     **/
    inline const uint8_t* dataAt(const size_t p_offset) const IPL_NOEXCEPT
    {
        return data() + p_offset;
    }

    /**
     * \brief
     *     Return data from the buffer.
     * \return
     *     read-write byte pointer to the beginning of the buffer
     *     data
     **/
    inline const uint8_t* data() const IPL_NOEXCEPT
    {
        // we need to perform static_cast in C++ to cast void
        // pointer
        return static_cast<uint8_t*>(m_buf->data()) +
            m_offsets.first;
    }

protected: // data
    //! SharedPtr to Buffer we're interfacing to
    Buffer::BufferPtr m_buf;
    //! current sub-buffer start and length offsets that are active
    ipl::pair<size_t, size_t> m_offsets;
}; // class Readable

} // end namespace transport
} // end namespace util

#endif
