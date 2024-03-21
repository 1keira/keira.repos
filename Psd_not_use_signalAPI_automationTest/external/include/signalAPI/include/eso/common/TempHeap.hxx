/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef COMMON_TEMPHEAP_HXX
#define COMMON_TEMPHEAP_HXX

#include <ipl_config.h>
#include <common/ipl_namespace.hxx>
#include <common/types/new.hxx>
#include <common/align.hxx>
#include <common/Macros.hxx>
#include <common/stdint.h>

namespace IPL_NAMESPACE
{

/**
 * \brief
 *     A heap implemented in a stack-like manner for temporary
 *     allocations

 *     This is a very simple heap implementation. The heap simply
 *     allocates one large block of memory as determined at
 *     construction time. On this memory block a stack data structure
 *     is maintained. Allocation requests will be satisfied from the
 *     top of the stack. Deallocations will only be marked as free at
 *     appropriate positions in the stack.
 *
 *     Memory will only really become available again if memory at the
 *     top of the stack is freed. Thus the memory efficiency is rather
 *     low and this heap is not general-purpose.
 *
 *     Instead this heap is designed to be suitable for temporary
 *     memory requirements in containers and algorithms. The
 *     accompanying TempAllocator type can be used as an allocator
 *     template-parameter to STL containers and alike.
 * \warning
 *     This is currently not thread safe
 **/
class TempHeap
{
public:
    //! create a temporary heap of \c bytes bytes size
    TempHeap(const size_t bytes) IPL_NOEXCEPT :
        m_stack_size(bytes),
        m_stack_top(0)
    {
        m_stack = NULL;

        while( !m_stack )
        {
            m_stack = new(ipl::nothrow) uint8_t[m_stack_size];

            if( ! m_stack ) // BRANCH_COVERAGE_UNTESTABLE
            {
                IPL_OOM("cannot allocate stack for "
                    "TempHeap");
            }
        }
    }

    //! \brief
    //! Destroy the heap, check that all memory has been freed by
    //! clients
    ~TempHeap() IPL_NOEXCEPT
    {
        IPL_ASSERT( m_stack );
        IPL_ASSERT( ! m_stack_top );
        delete[] m_stack;
        m_stack = NULL;
    }

    //! \brief
    //! Allocate \c bytes bytes from the heap and return a ptr to it
    //! or NULL if depleted.
    void* alloc(const size_t bytes) IPL_NOEXCEPT
    {
        // we allocate blocks acc. to the following scheme:
        //
        /////////////////////////////////////////////////////////////////////////////////////////////////
        // user-data (bytes bytes) // padding bytes ( 0 .. (ALIGNMENT - 1) bytes ) // EXTRA_DATA bytes //
        /////////////////////////////////////////////////////////////////////////////////////////////////

        // we need piggyback data for a size_t containing the
        // size of the block allocated and one byte for a free
        // marker.
        size_t real_bytes = bytes + EXTRA_DATA;

        // add any padding bytes needed for alignment
        real_bytes = this->alignBlock(real_bytes);

        // cannot satisfy request
        if( m_stack_top + real_bytes > m_stack_size )
            return NULL;

        // this will be the user-data ptr.
        void* ret = &m_stack[m_stack_top];

        // this will be the start index of the next allocation block - correctly aligned
        m_stack_top += real_bytes;

        // store the size of the complete block to be able to
        // free data later on correctly ( at the end of the
        // block store the size to prevent alignment trouble)
        *cast_without_warning<size_t*>(m_stack + m_stack_top  - SIZE_OFFSET) = real_bytes;
        // set the byte before that to mark this block as
        // occupied
        m_stack[m_stack_top  - MARK_OFFSET] = BLOCK_IN_USE;

        return ret;
    }

    //! \brief
    //! deallocate \c ptr of size \c bytes as previously obtained
    //! from allocate()
    void dealloc( void *ptr, const size_t bytes ) IPL_NOEXCEPT
    {
        // make sure this really is a ptr. from here
        IPL_ASSERT( ptr >= m_stack && ptr < m_stack + m_stack_size );

        const size_t block_start_index = (uint8_t*)ptr - m_stack;
        size_t real_bytes = bytes + EXTRA_DATA;
        real_bytes = this->alignBlock(real_bytes);
        const size_t mark_index = block_start_index + real_bytes - MARK_OFFSET;

        // make sure this block is marked as used, otherwise
        // something is wrong
        IPL_ASSERT( m_stack[mark_index] == BLOCK_IN_USE );
        // mark as unused now
        m_stack[mark_index] = BLOCK_FREE;

        // check whether we can actually make some memory
        // available from the top of the stack
        this->cleanupStack();
    }

    //! \brief
    //!    returns the bytes left for allocation - only a rough
    //!    estimate due to extra data needed per allocation
    size_t bytesLeft() const IPL_NOEXCEPT
    {
        return m_stack_size - m_stack_top;
    }

protected: // functions
    //! \brief
    //! make sure that the given block size is correctly padded for
    //! alignment
    static size_t alignBlock(size_t bytes) IPL_NOEXCEPT
    {
        size_t pad = bytes % ALIGNMENT;

        if( pad )
        {
            pad = ALIGNMENT - pad;
        }

        return bytes + pad;
    }

    //! \brief
    //!    called upon deallocation to theck if we can actually
    //!    free some space from the top of the stack
    void cleanupStack() IPL_NOEXCEPT
    {
        // check the top block until we reach a still allocated
        // block
        while( m_stack_top &&
            m_stack[m_stack_top - MARK_OFFSET] == BLOCK_FREE
            )
        {
            // get the size of the current top block
            // (including any padding and extra bytes)
            const size_t block_size = *cast_without_warning<size_t*>(m_stack + m_stack_top - SIZE_OFFSET);

            IPL_ASSERT( block_size <= m_stack_top );

            // okay, top-block is freed now
            m_stack_top -= block_size;
        }
    }

protected: // members
    //! size of the stack as given to constructor
    const size_t m_stack_size;

    //! the actual stack memory block
    uint8_t *m_stack;

    //! \brief
    //!    current top position of the stack (correctly aligned to
    //!    return memory from that position)
    size_t m_stack_top;

    // right now we ensure 4-byte alignment, maybe 8-byte alignment is better for
    // doubles and stuff ... we'll see
    static const size_t ALIGNMENT = 4;
    // various offsets for piggyback-data
    static const size_t MARK_OFFSET = sizeof(size_t) + sizeof(uint8_t);
    static const size_t SIZE_OFFSET = sizeof(size_t);
    static const size_t EXTRA_DATA = sizeof(size_t) + sizeof(uint8_t);
    // constants to mark block usage
    static const uint8_t BLOCK_IN_USE = 1;
    static const uint8_t BLOCK_FREE = 0;
private:
};

/**
 * \brief
 *     An allocator that follows the STL allocator pattern
 * \see
 *     ipl::allocator

 *     This allocator can be used in conjunction with a TempHeap and
 *     STL containers. It is intended for STL containers that exist
 *     only temporarily. In such cases heap-allocation can be
 *     expensive. Thus a TempHeap can be used to reduce runtime
 *     penalties and increase memory penalties instead.
 **/
template <typename T>
class TempAllocator
{
    template <typename O>
    friend class TempAllocator;
public:
    // upcoming the usual template type defines
    typedef T value_type;
    typedef T* pointer;
    typedef T& reference;
    typedef T* const_pointer;
    typedef const T& const_reference;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;

public:
    //! \brief
    //! see stroustrup about what this does (getting the template
    //! type for a different template parameter)
    template <class O>
    struct rebind
    {
        typedef TempAllocator<O> other;
    };
public:
    TempAllocator(TempHeap &heap) IPL_NOEXCEPT :
        m_heap(heap)
    { }

    TempAllocator(const TempAllocator &other) IPL_NOEXCEPT :
        m_heap(other.m_heap)
    { }

    template <typename O>
    TempAllocator(const TempAllocator<O> &other) IPL_NOEXCEPT :
        m_heap(other.m_heap)
    { }

    ~TempAllocator() IPL_NOEXCEPT
    { }

    pointer address(reference x) const IPL_NOEXCEPT
    { return &x; }

    const_pointer address(const_reference x) const IPL_NOEXCEPT
    { return &x; }

    pointer allocate(size_type n, void* hint = 0) IPL_NOEXCEPT
    {
        return (pointer)m_heap.alloc( n * sizeof(value_type) );
    }

    void deallocate(pointer p, size_type n) IPL_NOEXCEPT
    {
        return m_heap.dealloc(p, n * sizeof(value_type) );
    }

    size_type max_size() const IPL_NOEXCEPT
    { return m_heap.bytesLeft(); }

    void construct(pointer p, const_reference val) IPL_NOEXCEPT
    {
        ::new( static_cast<void*>(p) ) value_type(val);
    }

    void destroy(pointer p) IPL_NOEXCEPT
    {
        p->~T();
    }
private:
    TempHeap &m_heap;
};

} // end namespace ipl

#endif // include guard
