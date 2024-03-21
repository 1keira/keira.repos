/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_POSIX_SYSTEMINFODEFS_HXX
#define OSAL_POSIX_SYSTEMINFODEFS_HXX

#include <stddef.h>

namespace osal
{

//! this is for additional, platform-dependent system information
struct SystemInfoHandle
{
    //! the page size of the machine we're running on
    size_t pagesize;
    //! the number of CPUs present in the system
    size_t cpu_count;

    SystemInfoHandle() :
        pagesize(),
        cpu_count()
    { }
};

} // end namespace

#endif // OSAL_POSIX_SYSTEMINFODEFS_HXX
