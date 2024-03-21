/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_EMPTY_BUFFER_HXX
#define UTIL_EMPTY_BUFFER_HXX

#include <ipl_config.h>

#include <common/types/new.hxx>
#include <common/Macros.hxx>

#include <util/util_dso.h>

#include <util/transport/Buffer.hxx>
#include <util/transport/DefaultBuffer.hxx>

namespace util
{
namespace transport
{

/**
 * \brief
 *     Special empty buffer implementation

 *    As many buffers (default constructors, lingering variables etc.)
 *    will actually be empty buffers we use this optimization shortcut
 *    for those. A static EmptyBuffer object is present in the Buffer
 *    base class that answers most requests with some form of "I'm
 *    empty" and returns a real buffer upon resize(...).
**/
class UTIL_EXPORT util::transport::Buffer::EmptyBuffer :
    // we are a buffer, after all
    public util::transport::Buffer
{
public: // methods
    //! Default constructor doing nothing (just there for debugging purposes)
    EmptyBuffer() IPL_NOEXCEPT { return; }

    /**
     * \brief
     *    Return pointer to the one and almighty single
     *    EmptyBuffer
     **/
    virtual BufferPtr build(const size_t size) const IPL_NOEXCEPT
    {
        return BufferPtr( &EMPTY );
    }

    /**
     * \brief
     *    This buffer is always zero sized.
     * \return
     *    zero.
     **/
    size_t size() const IPL_NOEXCEPT { return 0; };

    /**
     * \brief
     *     This buffer contains no data.
     * \return
     *     NULL
     **/
    virtual const void* data() const IPL_NOEXCEPT { return NULL; };

    /**
     * \brief
     *     This buffer contains no data.
     * \return
     *     NULL
     **/
    virtual void* data() IPL_NOEXCEPT { return NULL; };

    /**
     * \brief
     *     Resize the buffer to size bytes.

     *     As an EmptyBuffer can't have a size != 0 we have to
     *     morph into a different buffer. We choose the
     *     DefaultBuffer due to lack of choice.
     * \see
     *     Buffer::resize()
     **/
    virtual BufferPtr resize(const size_t size, BufferPtr p_old_ptr) IPL_NOEXCEPT
    {
        if( size )
        {
            DefaultBuffer::DefaultBufferPtr b =
                DefaultBuffer::create(size);
            return b;
        }

        // for size zero we stay put
        return p_old_ptr;
    }

    /**
     * \note
     *     A duplicate of an EmptyBuffer is exactly the same, empty buffer.
     **/
    virtual BufferPtr duplicate() const IPL_NOEXCEPT
    {
        return BufferPtr(&EMPTY, delFunc );
    }

    /**
     * \note
     *    As there is only one EmptyBuffer a ptr to exactly that
     *    buffer is returned.  As soon as an EmptyBuffer is
     *    resized to be used for something useful it becomes a
     *    different, non-shared buffer anyway.
     **/
    virtual void makeUnique(BufferPtr &old_ptr) const IPL_NOEXCEPT
    {
        // empty buffers should never be written anyway
        return;
    }

    /**
     * \brief
     *    An EmptyBuffer should _never_ be allocated but just the
     *    address of the single EMPTY instance be returned.
     **/
    void* operator new(const size_t size) IPL_NOEXCEPT
    {
        IPL_ABORT("new on EmptyBuffer!");;
        return &EMPTY;
    }

    /**
     * \brief
     *    As we don't allocate EmptyBuffer we also may not delete
     *    it
     **/
    void operator delete(void *o) IPL_NOEXCEPT
    {
        IPL_ABORT("delete on EmptyBuffer!");
    }

    /**
     * \brief
     *     To be passed to SharedPtr as a custom deletion function
     *     that does nothing
     **/
    static void delFunc(void *o) IPL_NOEXCEPT
    {
        (void)o;
    }
protected:
private:
}; // class EmptyBuffer

} // end namespace transport
} // end namespace util

#endif
