/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_COMMON_ATOMICCOUNTERDEFS_HXX
#define OSAL_COMMON_ATOMICCOUNTERDEFS_HXX

/*
 *    for the common OSAL impl. of AtomicCounter we simply use a normal integer accompanied by a
 *    Mutex
 */

#include <osal/Mutex.hxx>

namespace osal
{

typedef int_fast32_t AtomicCounterType;

struct AtomicCounterHandle
{
    // volatile seems to be a good idea here. Some OSs use it in their function signatures as
    // well.
    volatile AtomicCounterType counter;
    osal::Mutex counter_lock;
};

} // end ns osal

#endif
