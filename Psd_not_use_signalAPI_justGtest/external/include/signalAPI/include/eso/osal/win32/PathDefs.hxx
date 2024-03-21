/*
    Copyright esolutions GmbH
    All rights reserved
    Authors:
        Matthias Gerstner
    $Id: $
*/

#ifndef OSAL_WIN32_PATHDEFS_HXX
#define OSAL_WIN32_PATHDEFS_HXX

#include <iplbase/win32.h>
#include <common/types/string.hxx>

#define OSAL_USE_WIDEPATH  // hack used in TreeWalker.cxx

namespace osal {

    template <typename CHAR_TYPE>
    struct path_traits
    {
        static const CHAR_TYPE SEPARATOR = static_cast<CHAR_TYPE>('\\');
        static const size_t MAX_PATH_LEN = MAX_PATH * sizeof(CHAR_TYPE);
        static const size_t MAX_COMPONENT_LEN = MAX_PATH * sizeof(CHAR_TYPE);
    };

}  // end of namespace osal

#endif
