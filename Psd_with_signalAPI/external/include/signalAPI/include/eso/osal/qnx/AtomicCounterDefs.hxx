#ifndef OSAL_QNX_ATOMICCOUNTERDEFS_HXX
#define OSAL_QNX_ATOMICCOUNTERDEFS_HXX

namespace osal
{

typedef unsigned AtomicCounterType;

struct AtomicCounterHandle
{
    // volatile seems to be a good idea here. Some OSs use it in their function signatures as
    // well.
    volatile AtomicCounterType counter;
};

} // end ns osal

#endif
