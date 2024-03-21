/*
    Copyright esolutions GmbH
    All rights reserved
    Authors:
        Matthias Gerstner
        Jörg Kupietz
*/

#ifndef OSAL_INTEGRITY_PATHDEFS_HXX
#define OSAL_INTEGRITY_PATHDEFS_HXX

#include <sys/types.h>
#include <osal/osal_dso.h>

#include <limits.h>

#include <unistd.h>

#define OSAL_USE_PATH  // hack used in TreeWalker.cxx

namespace osal {

    template <typename CHAR_TYPE>
    struct OSAL_EXPORT path_traits
    {
        static const CHAR_TYPE SEPARATOR = static_cast<CHAR_TYPE>('/');
        static const size_t MAX_PATH_LEN = MAXPATHLEN;
        static const size_t MAX_COMPONENT_LEN = NAME_MAX;
    };

}  // end of namespace osal

#endif
