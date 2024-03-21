/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_BUFFER_HXX
#define UTIL_BUFFER_HXX

#include <ipl_config.h>
#include <util/util_dso.h>
#include <common/Macros.hxx>
#include <memory>

namespace util
{
namespace transport
{

/**
 * \brief
 *    Base interface class for (transport) buffers

 *    Buffers are the data chunks that are passed to and fro the
 *    transport layer. They deal with quite some additional logic to
 *    allow for efficient buffer sharing between different software
 *    parts. This avoids buffer copying and hopefully increases
 *    usability (buzzword: zero copy).
 *
 *    This is merely the base interface for Buffers. A default
 *    implementation DefaultBuffer is shipped along.
 * \warning
 *    Buffer and/or transport clients should not access the Buffer
 *    interface directly.  Instead there are two frontends for clients
 *    Readable and Writeable which allow corresponding access to a
 *    buffer.
 *
 *    The Buffer interface itself can be considered low-level and
 *    potentially dangerous to the unaware user.
**/
class UTIL_EXPORT Buffer
{
public: // types

    /**
     * \brief
     *     A suitable pointer to a buffer

     *    We use SharedPtr's to touch buffers and nothing else.
     *    Does the reference counting for us.
     **/
    using BufferPtr = std::shared_ptr<Buffer>;

    // them need access to EmptyBuffer stuff
    friend class Readable;
    friend class Writeable;

public: // methods

    //! \brief
    //! virtual destructor to make sure derived class dtor gets
    //! always called
    virtual ~Buffer() IPL_NOEXCEPT { };

    /**
     * \brief
     *    Create a pristine buffer

     *    An implementor of FooBuffer is expected to implement
     *    this pure virtual function by means of calling its own
     *
     *    static FooBuffer* create(size_t size);
     *
     *    function. This allows for implementation defined buffer
     *    creation.
     *
     *    New buffers may only be obtained via build or create
     *    functions and not via constructors or copy-constructors.
     *    This is due to the zero-copy approach using reference
     *    counting.
     **/
    virtual BufferPtr build(const size_t size) const IPL_NOEXCEPT = 0;

    /**
     * \brief
     *     Current size of buffer in bytes
     * \note
     *     This gives only the capacity of the buffer in bytes but
     *     not the actual amount of useful data in the buffer.
     *     Keeping track of data content is the clients job.
     **/
    virtual size_t size() const IPL_NOEXCEPT = 0;

    /**
     * \brief
     *     Retrieve non-const pointer to the buffer data
     **/
    virtual void* data() IPL_NOEXCEPT = 0;

    /**
     * \brief
     *     Retrieve const pointer to the buffer data
     **/
    virtual const void* data() const IPL_NOEXCEPT = 0;

    /**
     * \brief
     *     Resize the buffer to \c size bytes

     *     This might influence the actual capacity of the buffer.
     *     If this is the case and how this is done depends on the
     *     actual implementation. The client of the buffer will see
     *     a buffer size of \c size after return of the function.
     * \warning
     *     This operation might require reallocation of the current
     *     data. References to pointers to the buffer or any
     *     pointers to the old Buffer object have to be considered
     *     undefined after return of this function.
     *
     *     The only valid remaining reference to the buffer will be
     *     the one returned from this function.
     * \param[in]
     *     old_ptr The old BufferPtr associated with this buffer.
     **/
    virtual BufferPtr resize(const size_t size, BufferPtr old_ptr) IPL_NOEXCEPT = 0;

    /**
     * \brief
     *     Retrieve a duplicate of the current buffer

     *     A deep copy of the current Buffer object will be
     *     performed and returned.  This is an expensive operation.
     *     The resulting buffer will not be shared any more.
     * \note
     *     As the Buffer doesn't keep track of actual useful data
     *     in the Buffer at duplicate() time the complete buffer
     *     capacity will be copied. Clients are thus advised to
     *     take care of not doing unnecessary copy operations via
     *     duplicate().
     * \return
     *     Pointer to duplicate of the current buffer.
     **/
    virtual BufferPtr duplicate() const IPL_NOEXCEPT = 0;

    /**
     * \brief
     *     Return a BufferPtr that is not shared

     *     If old_ptr is currently shared then a copy of the buffer
     *     will be made and a pointer to that buffer that is no
     *     longer shared is returned. If old_ptr is not shared than
     *     old_ptr will be returned.
     *
     *     The restrictions described at duplicate() apply to this
     *     function as well in case a copy needed to be made.
     * \param[in]
     *     old_ptr The current pointer to the buffer. This needs to
     *     be a reference (otherwise we always have at least two
     *     users of old_ptr).
     * \return
     *     A pointer to the buffer that is no longer shared.
     **/
    IPL_DEPRECATED("makeUnique is prone to race conditions and should not be used",
        virtual void makeUnique(BufferPtr& old_ptr) const IPL_NOEXCEPT) = 0;

protected: // methods
    /**
     * \brief
     *     Non-public constructor

     *     Buffers should only be obtained via BufferPtr
     *     build(const size_t) or create(...) and not via the
     *     constructor.
     *
     *     This is because creation of Buffers via constructors
     *     would circumvent reference counting scheme or any
     *     implementation details regarding creation.
     **/
    Buffer() IPL_NOEXCEPT { };

    /**
     * \brief
     *     Non-public copy-constructor

     *    Buffers should only be copied via duplicate().
     *
     *     Creation of Buffers via constructors would circumvent
     *     reference counting scheme and implementation details.
     **/
    Buffer(const Buffer &other) IPL_NOEXCEPT { };

protected: // inner classes and members

    //! Special buffer class for empty buffers
    class EmptyBuffer;
    //! \brief
    //! Optimization for empty buffers: Single object that's used
    //! for all empty buffers
    static EmptyBuffer EMPTY;
private:
}; // class


} // end namespace transport
} // end namespace util

#endif
