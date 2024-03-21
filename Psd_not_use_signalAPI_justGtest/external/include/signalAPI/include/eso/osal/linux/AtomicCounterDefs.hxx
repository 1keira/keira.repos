/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_LINUX_ATOMICCOUNTERDEFS_HXX
#define OSAL_LINUX_ATOMICCOUNTERDEFS_HXX

namespace osal
{

typedef unsigned int AtomicCounterType;

struct AtomicCounterHandle
{
    // volatile seems to be a good idea here. Some OSs use it in their function signatures as
    // well.
    volatile AtomicCounterType counter;
};

} // end ns osal

#endif
