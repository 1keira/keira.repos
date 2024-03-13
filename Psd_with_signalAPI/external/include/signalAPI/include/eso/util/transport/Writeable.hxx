/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_WRITEABLE_HXX
#define UTIL_WRITEABLE_HXX

#include <ipl_config.h>

#include <common/Macros.hxx>
#include <common/error/ErrorHelper.hxx>

#include <util/util_dso.h>

#include <util/transport/Buffer.hxx>
#include <util/transport/Readable.hxx>
#include <util/transport/DefaultBuffer.hxx>
#include <string.h> // ::memcpy

namespace util
{
namespace transport
{

/**
 * \brief
 *     read-write frontend to a Buffer

 *     Provides frontend to a Buffer with read-write-access.
 *
 *     A problem needs to be addresses here regarding unnecessary copy
 *     operations. When a software component is passed a Writeable
 *     Buffer frontend then it can never now whether the buffer content
 *     will be modified any more. Thus a mechanism is needed to
 *     determine when buffer data is frozen and can safely be
 *     processed.
 *
 *     The way this is done here is via a double buffering scheme. A
 *     Writeable buffer contains a second buffer (so called front
 *     buffer). That is where actual write access goes to. Meanwhile
 *     read accesses go to the second buffer that is accessible via the
 *     Readable frontend. When a writer is done generating buffer data
 *     then he has to swap buffer contents moving the front buffer data
 *     to the other buffer. This has to be done via commitData().
 *
 *     The only place where currently a commit is done is upon a send
 *     operation at ITransport::send(). After all IMsgWriter objects
 *     have been called in the stack the Writeable will be commited to
 *     be able to send the finished object.
 *
 *     The const semantic of Writeable is as follows: The only
 *     non-const operation is resize() and grow() as these are
 *     dangerous operations in case of complex code involving buffer
 *     windows. Everything else like reading and writing the buffer
 *     data as well as adding/removing buffer windows are considered
 *     const operations.
 * \note
 *     Writeable is intentionally not derived from Readable to avoid
 *     accidental casts to Readable or usage of inherited readable
 *     member functions.
 * \warning
 *     Writeable frontend is not intended to be thread safe. Each
 *     thread working with a buffer is supposed to have its own view
 *     and thus its own frontend for a buffer.
 **/
class Writeable
{
public: // types

    //! a type able to store a Writeable window setting
    typedef ipl::pair<size_t, size_t> Window;
public: // methods
    /**
     * \brief
     *     Create a new Writeable frontend with an empty front, and
     *     no back buffer (NULL pointer).
     **/
    inline Writeable() IPL_NOEXCEPT :
        m_frontbuf((Buffer*)&Buffer::EMPTY,
            Buffer::EmptyBuffer::delFunc),
        m_backbuf(),
        m_offsets(0, 0)
    { }

    /**
     * \brief
     *     Create a new Writeable frontend with a DefaultBuffer
     *     front buffer able to hold size bytes of data.
     **/
    inline Writeable(const size_t size) IPL_NOEXCEPT :
        m_frontbuf(DefaultBuffer::create(size)),
        m_backbuf(),
        m_offsets(0, 0)
    { }

    /**
     * \brief
     *     Create a writeable frontend for buffer frontbuf
     **/
    inline Writeable(Buffer::BufferPtr frontbuf) IPL_NOEXCEPT :
        m_frontbuf(frontbuf),
        m_backbuf(),
        m_offsets(0, 0)
    { }

    /**
     * \brief
     *     Create a read-write frontend from the given readable
     *     frontend

     *     This constructor variant implies that you want to write
     *     to the data turned in from other at some time. To avoid
     *     deep-copy of data from other into the front buffer in
     *     advance without knowing whether the user will actually
     *     write to the buffer, the copy operation will only be
     *     done at the first access to the frontbuffer data (copy
     *     on write).
     *
     *     An applied buffer window in other will be taken over
     *     into the new Writeable.
     **/
    inline Writeable(const Readable &other) IPL_NOEXCEPT :
        // shared copy!
        m_frontbuf( other.m_buf ),
        m_offsets( other.m_offsets )
    { }

    /**
     * \brief
     *    Does nothing special (ref. counting handled by
     *    SharedPtr)
     **/
    inline virtual ~Writeable() IPL_NOEXCEPT
    { }

    /**
     * \brief
     *     Only make a buffer window visible to the client

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
     *     The offset in bytes to use for the new sub-buffer
     *     window. May not be greater then current size(). May be
     *     zero which will have no effect on the buffer start
     *     address then.
     * \param[in] p_length
     *     Length of the buffer that should be visible. May range
     *     from zero to current (size() - p_offset). If greater
     *     then it will be reduced to that maximum value.
     * \return
     *     The previously active window setting will be returned.
     *     It can be used at restoreWindow to get the previous view
     *     on the buffer.
     **/
    inline Window setWindow(const size_t p_offset,
        size_t p_length = SIZE_MAX) const IPL_NOEXCEPT
    {
        IPL_ASSERT( p_offset <= size() );

        const size_t new_size = size() - p_offset;

        // don't grow already existing window or outside of
        // buffer area.
        if( p_length > new_size )
            p_length = new_size;

        const size_t length_offset = new_size - p_length;

        // previous window setting will be returned
        const Window ret = m_offsets;

        // add the new offsets
        m_offsets.first = p_offset + m_offsets.first;
        m_offsets.second = length_offset + m_offsets.second;

        return ret;
    }

    /**
     * \brief
     *     Restores a previous window setting.

     *     Upon a call to setWindow a Window object is returned
     *     that contains the information about the previous window
     *     settings. Calling this function with that Window object
     *     you are able to restore this window settings thus making
     *     it possible to access the data area hidden by setWindow.
     * \param[in] win
     *     A Window object returned by setWindow.
     **/
    inline void restoreWindow(const Window &win) const IPL_NOEXCEPT
    {
        // any additional security checks?
        m_offsets = win;

        return;
    }

    /**
     * \brief
     *     Return a reference to the byte in the buffer data at the
     *     given offset position
     **/
    inline uint8_t& operator[](const size_t p_offset) const IPL_NOEXCEPT
    {
        return *(data() + p_offset);
    }

    /**
     * \brief
     *     Return pointer to buffer data with byte offset at the
     *     beginning
     **/
    inline uint8_t* dataAt(const size_t p_offset) const IPL_NOEXCEPT
    {
        return data() + p_offset;
    }

    /**
     * \brief
     *     For writer-frontend clients we return the data from the
     *     front buffer.

     *     This is also possible for const objects. A const
     *     Writeable object has the meaning of a writeable buffer
     *     that can be written to but that cannot be changed in
     *     size via resize(const size_t).
     *
     *     This function also takes care of copy on write in case
     *     this Writeable was flat copied from a Readable.
     * \return
     *     read-write byte pointer to the beginning of the buffer
     *     data
     **/
    inline uint8_t* data() const IPL_NOEXCEPT
    {
        // We should be the only one having the buffer
        IPL_ASSERT(m_frontbuf.use_count() == 1);

        // we need to perform static_cast in C++ to cast void
        // pointer
        return static_cast<uint8_t*>(m_frontbuf->data()) +
            m_offsets.first;
    }

    //! Returns the size of the front buffer
    inline size_t size() const IPL_NOEXCEPT
    {
        return m_frontbuf->size() - m_offsets.first -
            m_offsets.second;
    }

    /**
     * \brief
     *     Resize the front buffer to a capacity of size bytes

     *     If a buffer window is active then any data following the
     *     current end of the buffer window will be moved to the
     *     new end of the buffer window after resize. The new
     *     buffer window will have room for size bytes.
     *
     *    If size is greater than the current size of the buffer
     *    then any previous content in the buffer window will be
     *    kept. The new bytes available after resize will have
     *    undefined content.
     *
     *     If size is less than the current size of the buffer then
     *     the last bytes in the current buffer window will be
     *     overwritten.
     **/
    inline void resize(const size_t size) const IPL_NOEXCEPT
    /* const: conceptually this still points to the same buffer, that's why
       m_frontbuf is already mutable. To be discussed. S.M. */
    {
        const bool is_grow = size > this->size();

        const size_t change = is_grow ? size - this->size() :
            this->size() - size;
        uint8_t *backup = NULL;
        while( ! backup )
        {
            backup = new(ipl::raise_error)
                uint8_t[m_offsets.second];

            if( ! backup ) // BRANCH_COVERAGE_UNTESTABLE
            {
                IPL_OOM("Writeable resize");
            }
        }

        // backup the current footer
        ::memcpy( backup, dataAt( this->size() ),
            m_offsets.second );

        // we can simply shift anything from end of the old
        // buffer window to the new end of the buffer window.
        m_frontbuf = m_frontbuf->resize( (size_t)((int32_t)m_frontbuf->size() +
            (is_grow ? (int32_t)change : -(int32_t)change)), m_frontbuf);

        // restore the footer
        memcpy( dataAt( this->size() ),
            backup, m_offsets.second );

        delete[] backup;
    }

    /**
     * \brief
     *     Increase the front buffer capacity by delta bytes.

     *     The semantic is the same as at resize().
     **/
    inline void grow(const size_t delta) IPL_NOEXCEPT
    {
        m_frontbuf = m_frontbuf->resize( size() + delta,
            m_frontbuf );
    }

    /**
     * \brief
     *     Commit the front buffer and make it visible to the
     *     Readable part of the frontend

     *     The front buffer will be set to a new buffer able to
     *     hold newsize bytes. Any sub-buffer settings will be
     *     discarded. The Readable part of the frontend will not
     *     inherit any sub-buffer windows from the front buffer.
     * \param[in] newsize
     *     Size of the new front buffer in bytes
     * \return
     *     Reference to the readable back buffer.
     **/
    inline const Buffer::BufferPtr& commitBuffer(
        const size_t newsize = 0) IPL_NOEXCEPT
    {
        // reset buffer windows
        m_offsets.first = m_offsets.second = 0;

        // switch buffers
        m_backbuf.m_buf = m_frontbuf;

        // reset front buffer
        if( newsize )
            m_frontbuf = m_frontbuf->build( newsize );
        else
            m_frontbuf = Buffer::BufferPtr(
                (Buffer*)&Buffer::EMPTY,
                Buffer::EmptyBuffer::delFunc );

        // return back buffer ptr.
        return m_backbuf.m_buf;
    }

    //! Returns a readable for the backbuffer
    inline Readable& getReadable() IPL_NOEXCEPT
    {
        return m_backbuf;
    }

    //! returns whether m_frontbuf has been successfully allocated
    bool validBuf() const IPL_NOEXCEPT
    { return (bool)m_frontbuf; }

protected: // protected members
    //! \brief
    //! SharedPtr to front buffer where is written to (needs to be
    //! mutable for copy-on-write)
    mutable Buffer::BufferPtr m_frontbuf;
    //! Readable back buffer
    Readable m_backbuf;
    //! \brief
    //! Any sub-buffer start and length offsets active for this
    //! frontend
    mutable Window m_offsets;
}; // class Writeable

} // end namespace transport
} // end namespace util

#endif
