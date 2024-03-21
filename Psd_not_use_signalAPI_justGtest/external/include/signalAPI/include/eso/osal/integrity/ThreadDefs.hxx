#ifndef OSAL_INTEGRITY_THREADDEFS_HXX
#define OSAL_INTEGRITY_THREADDEFS_HXX

#include <string.h>

namespace osal
{

//! OS handle to reference a posix thread
struct ThreadHandle
{
    //! this is the actual thread id type
    Task thread;
    ThreadHandle()
    {
        ::memset( &thread, 0, sizeof(Task) );
    }
};

//! definition of a thread ID, remember this could be any type
typedef Task OSThreadId;

} // end ns osal

#endif // inc. guard
