/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_POSIX_MEMFILEDEFS_HXX
#define OSAL_POSIX_MEMFILEDEFS_HXX

#include <osal/MemMapping.hxx>

namespace osal {

    struct MemFileHandle {
        //! \brief Any registered memory mappings
        ipl::map< const void*, MemMapping > mappings;
    };

}  // end of namespace osal

#endif
