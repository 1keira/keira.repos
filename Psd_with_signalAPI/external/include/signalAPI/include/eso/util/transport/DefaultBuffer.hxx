/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_DEFAULTBUFFER_HXX
#define UTIL_DEFAULTBUFFER_HXX

#include <ipl_config.h>
#include <util/util_dso.h>
#include <util/transport/Buffer.hxx>

namespace util
{
namespace transport
{

/**
 * \brief
 *    Default Implementation of a Buffer

 *    This is the standard buffer that can be used when no particular
 *    properties for buffer management are needed.
 *
 *    The implementation cares for an efficient memory allocation
 *    strategy from the heap or possibly a memory pool
 *
 *    The DefaultBuffer object and actual data content will be
 *    allocated in one goe via placement-new. This is low-levelish
 *    hackery and needs to be treated carefully.
**/
class UTIL_EXPORT DefaultBuffer :
    // we are a buffer, after all
    public util::transport::Buffer
{
public: // types, fwd. decl. and inner classes

    //! \brief
    //!    SharedPtr definition for DefaultBuffer
    //! \note
    //!    SharedPtr allows assignment of compatible ptr. types i.e. "BufferPtr =
    //!    DefaultBufferPtr" is possible.
    typedef std::shared_ptr<DefaultBuffer> DefaultBufferPtr;

public: // methods

    /**
     * \brief
     *     Create a pristine buffer with reference count of one

     *     Will call static create function for actual allocation.
     **/
    virtual BufferPtr build(const size_t size) const IPL_NOEXCEPT
    {
        return DefaultBuffer::create(size);
    }

    /**
     * \brief
     *     Static member function that actually constructs new
     *     DefaultBuffers. Only place where DefaultBuffers are
     *     supposed to be created.
     * \errors
     *     On allocation error a NULL pointer is returned.
     **/
    static DefaultBufferPtr create(const size_t size) IPL_NOEXCEPT;

    /**
     * \brief
     *     Current size of buffer in bytes
     * \see
     *     Buffer::size()
     **/
    virtual size_t size() const IPL_NOEXCEPT
    {
        return m_size;
    }

    /**
     * \brief
     *     Retrieve const pointer to the buffer data
     **/
    virtual const void* data() const IPL_NOEXCEPT
    {
        // be careful with this add (adds sizeof ptr-type!)
        return ((const uint8_t*)this) - m_capacity;
    }

    /**
     * \brief
     *     Retrieve non-const pointer to the buffer data
     **/
    virtual void* data() IPL_NOEXCEPT
    {
        // be careful with this add (adds sizeof ptr-type!)
        return ((uint8_t*)this) - m_capacity;
    }

    /**
     * \brief
     *     Resize the buffer to a capacity of at least size bytes

     *     The buffer size reported to the client will be size
     *     regardless of the actual buffer capacity.
     * \see
     *     Buffer::resize()
     * \note
     *     To actually resize the current object DefaultBuffer
     *     would have to completely reallocate itself (including
     *     "this"). This would be erroneous due to SharedPtr usage.
     *     SharedPtr doesn't know its managed object suddenly isn't
     *     valid any more.
     *
     *     Therefore the implementation of resize instead allocates
     *     a new object capable of holding size bytes. The old
     *     object will not be explicitly deallocated but only  when
     *     the last SharedPtr holding the old object goes away.
     *
     *     This is not necessarily more expensive in terms of
     *     runtime but of course the memory usage may remain higher
     *     for a longer time than expected. It may also be that
     *     resize() isn't reallocating anything in case capacity is
     *     already high enough. In that case nothing is done.
     *
     *     These actions are transparent to the client, however.
     *     resize() should only be called on Writable buffers which
     *     should only have one client at the same time anyway.
     *     This one client should only have one SharedPtr to the
     *     buffer.  This SharedPtr is to be assigned the BufferPtr
     *     returned here and will be assigned the newly sized
     *     buffer. Thus in the common case the behaviour is the
     *     expected one:
     *
     *     The new Buffer gets allocated, the old BufferPtr gets
     *     assigned the new Buffer and thereby the old Buffer will
     *     be deleted.
     **/
    virtual BufferPtr resize(const size_t size, BufferPtr p_old_ptr) IPL_NOEXCEPT;

    virtual BufferPtr duplicate() const IPL_NOEXCEPT;

    IPL_DEPRECATED("makeUnique is prone to race conditions and should not be used",
    virtual void makeUnique(BufferPtr &old_ptr) const IPL_NOEXCEPT)
    {
        if( old_ptr.use_count() == 1 )
        {
            old_ptr = old_ptr->duplicate();
        }
    }
    

    /**
     * \brief
     *     Adjusted deallocation strategy for DefaultBuffer

     *     As DefaultBuffer is specially allocated we can't simply
     *     allow a standard delete on it. Deletion of DefaultBuffer
     *     is done by SharedPtr, however which doesn't know about
     *     our allocation policy. Thus we overload deletion
     *     operator to call custom code in that case.
     **/
    void operator delete(void *o) IPL_NOEXCEPT;

protected: // members

    //! \brief
    //!    (user visible) size of the current buffer in bytes
    //! \note
    //!    buffer data starts at "this + sizeof(DefaultBuffer)"
    size_t m_size;

    //! \brief
    //!    Actual capacity of the current buffer in bytes
    size_t m_capacity;
private: // methods
    /**
     * \brief
     *     Construct a new DefaultBuffer able to hold size bytes

     *     Will only be called via static create(...)
     *
     *     As the object ("this") and the buffer storage are
     *     allocated in one go the constructor doesn't have to do
     *     any additional allocation.
     * \note
     *     declared private, because deriving from this class is
     *     pretty dangerous with all the nasty stuff that goes on
     *     here.
     **/
    DefaultBuffer(const size_t size, const size_t cap) :
        m_size(size),
        m_capacity(cap)
    {}

}; // class DefaultBuffer

} // end namespace transport
} // end namespace util

#endif
