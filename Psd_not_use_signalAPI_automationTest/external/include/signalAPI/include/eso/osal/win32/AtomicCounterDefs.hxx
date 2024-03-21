#ifndef OSAL_WIN32_ATOMICCOUNTERDEFS_HXX
#define OSAL_WIN32_ATOMICCOUNTERDEFS_HXX

#include <iplbase/win32.h>

namespace osal
{

typedef LONG AtomicCounterType;


struct AtomicCounterHandle
{
    // volatile seems to be a good idea here. Some OSs use it in their function signatures as
    // well.
    volatile AtomicCounterType counter;
};

} // end ns osal

#endif
