/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef COMMON_HEAPPROFILER_HXX
#define COMMON_HEAPPROFILER_HXX

#include <ipl_config.h>
#include <common/ipl_namespace.hxx>

#include <stdio.h>

#include <common/Macros.hxx>
#include <common/NonCopyable.hxx>
#include <common/types/new.hxx>
#include <common/types/algorithm.hxx>

namespace IPL_NAMESPACE
{
    class HeapProfiler;
}

void* operator new( size_t s, ipl::HeapProfiler &hp ) IPL_NOEXCEPT;
void operator delete( void *p, ipl::HeapProfiler &hp ) IPL_NOEXCEPT;

namespace IPL_NAMESPACE
{

/*
 *     problem: multi-threading support is only possible from OSAL upwards
 *
 *     problem: evaluating low-level information is nearly impossible platform-independently. This
 *     counts e.g. for call stack information or heap-fragmentation (the latter would require full
 *     control of the heap)
 *
 *     feature: __FILE__, __LINE__, __FUNCTION__ information can be recorded, too. But this
 *     requires apropriate calls like "new(HeapObject, SRC_LOCATION) SomeObj;"
 *
 *     feature: snapshots could be stored, triggered via timer or memory consumption (also needs
 *     OSAL partly)
 *
 *     feature: evaluate thread ID to make it possible to do statements about thread-memory-usage
 *
 *     feature: make it possible to have scopes that are profiled e.g. a TLS object that's put up
 *     that makes it possible to easily express the wish to profile a certain section of code.
 *
 *     feature: along with profiling also heap-debugging can be performed.
 *
 *     feature: profiling information can be kept in memory and be evaluated upon active request
 *     from the application or at exit of the process / destruction of the object. (can require
 *     quite an amount of memory depending on what we're profiling)
 *
 *     feature: profiling information can be written to file or network and be evaluated with a
 *     separate program.
 *
 *     feature: on UTIL level upwards memory profiling information could be integrated into
 *     tracing.
 */

/**
 *    \brief
 *        Collects heap-allocation data when put into overloaded new operators
 **/
class HeapProfiler
{
public:
    /**
     *    \param[in]
     *        module A label for the module that is profiled via this instance. Must be a
     *        statically allocated string
     **/
    HeapProfiler(const char *module) IPL_NOEXCEPT :
        m_module(module)
    {
        IPL_ASSERT(module);
        ::memset( &m_state, 0, sizeof(HeapState) );
    }

    void printReport() IPL_NOEXCEPT
    {
        printf("Heap report for module \"%s\"\n", m_module);
        printf("Total number of allocations: %lu\n", (unsigned long)m_state.all_allocs);
        printf("Total number of de-allocations: %lu\n", (unsigned long)m_state.all_deallocs);
        printf("Maximum number of allocations at the same time: %lu\n", (unsigned long)m_state.max_allocs);
        printf("Current number of allocations: %lu\n", (unsigned long)m_state.cur_allocs);
        printf("Total number of bytes allocated: %lu\n", (unsigned long)m_state.all_bytes);
        printf("Maximum number of bytes allocated at the same time: %lu\n", (unsigned long)m_state.max_bytes);
        printf("Current number of bytes allocated: %lu\n", (unsigned long)m_state.cur_bytes);
    }

protected:
    //! number of extra bytes needed for accounting information per heap-allocation
    static size_t neededExtraBytes() IPL_NOEXCEPT
    {
        // beware of alignment issues!
        return sizeof(size_t);
    }

    //! bytes is the actually requested size, not including the profiling data overhead
    //! p is the actually allocated pointer (i.e. it points to the management data)
    void addAlloc(size_t bytes, void *p) IPL_NOEXCEPT
    {
        *((size_t*)p) = bytes;

        m_state.cur_bytes += bytes;
        m_state.all_bytes += bytes;
        m_state.max_bytes = ipl::max( m_state.max_bytes, m_state.cur_bytes );
        m_state.cur_allocs++;
        m_state.all_allocs++;
        m_state.max_allocs = ipl::max( m_state.max_allocs, m_state.cur_allocs );
    }

    //! p points to the originally allocated pointer (i.e. it points to the management data)
    void delAlloc(void *p) IPL_NOEXCEPT
    {
        size_t alloc_size = *((size_t*)p);

        m_state.cur_bytes -= alloc_size;
        m_state.cur_allocs--;
        m_state.all_deallocs++;
    }

private:
    typedef size_t counter_t;

    //! a state representation of the heap managed by this profiler
    struct HeapState
    {
        //! accumulated number of allocations
        counter_t all_allocs;

        //! accumulated number of deallocations
        counter_t all_deallocs;

        //! current number of allocations
        counter_t cur_allocs;

        //! maximum number of allocations at the same time
        counter_t max_allocs;

        //! accumulated number of bytes allocated
        counter_t all_bytes;

        //! current number of bytes allocated
        counter_t cur_bytes;

        //! maximum number of bytes allocated at the same time
        counter_t max_bytes;
    };

    //! the current state of the heap
    HeapState m_state;

    //! name of the module that is profiled
    const char *m_module;

    friend void* ::operator new(size_t, ipl::HeapProfiler& ) IPL_NOEXCEPT;
    friend void ::operator delete(void*, ipl::HeapProfiler& ) IPL_NOEXCEPT;
};

} // end ns ipl

inline void* operator new( size_t s, ipl::HeapProfiler &hp ) IPL_NOEXCEPT
{
    uint8_t *ret = new(ipl::nothrow) uint8_t[s + hp.neededExtraBytes()];

    if( ret )
    {
        hp.addAlloc(s, ret);
    }

    return ret + hp.neededExtraBytes();
}

inline void* operator new[]( size_t s, ipl::HeapProfiler &hp ) IPL_NOEXCEPT
{
    return operator new(s, hp);
}

inline void operator delete( void *p, ipl::HeapProfiler &hp ) IPL_NOEXCEPT
{
    uint8_t *delp = ((uint8_t*)p) - hp.neededExtraBytes();

    hp.delAlloc(delp);

    return delete[] delp;
}

inline void operator delete[]( void *p, ipl::HeapProfiler &hp ) IPL_NOEXCEPT
{
    return operator delete(p, hp);
}

#endif // include guard
