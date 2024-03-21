/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_POSIX_HEAPINFORMATIONDEFS_HXX
#define OSAL_POSIX_HEAPINFORMATIONDEFS_HXX

#include <ipl_config.h>

#if !defined(HAVE_MALLINFO2) && !defined(HAVE_MALLINFO)
    // mallinfo-like replacement so that we can compile HeapInfo.
    // doesn't have any usable data.
#ifdef __cplusplus
extern "C" {
#endif
    struct mallinfo {
        int arena;
        int hblkhd;
        int uordblks;
        int fordblks;
    };

    static inline struct mallinfo mallinfo(void) {
        struct mallinfo info = {0,0,0,0};
        return info;
    }
#ifdef __cplusplus
}
#endif
#endif

// what we need is in here
#include <malloc.h>
#include <string.h>

namespace osal
{

struct HeapInfoHandle
{
#ifdef HAVE_MALLINFO2
    typedef struct mallinfo2 ipl_mallinfo_t;
#else
    typedef struct mallinfo ipl_mallinfo_t;
#endif

    ipl_mallinfo_t info;

    HeapInfoHandle()
    {
        ::memset(&info, 0, sizeof(ipl_mallinfo_t));
    }
};

} // end ns osal

#endif
