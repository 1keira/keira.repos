#ifndef OSAL_POSIX_HEAPINFORMATIONDEFS_HXX
#define OSAL_POSIX_HEAPINFORMATIONDEFS_HXX

#include <ipl_config.h>

// #ifndef HAVE_MALLINFO
// #    error "There's no mallinfo available in your configuration"
// #endif
// 
// // what we need is in here
// #include <malloc.h>
// #include <string.h>

namespace osal
{

struct HeapInfoHandle
{
//     struct mallinfo info;
// 
//     HeapInfoHandle()
//     {
//         ::memset(&info, 0, sizeof(struct mallinfo));
//     }
};

} // end ns osal

#endif
