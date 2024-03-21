/*
    Copyright e.solutions GmbH
    All rights reserved
    Authors:
        Matthias Gerstner
    $Id: $
*/

#include "WinPath.hxx"

namespace osal {

    inline void SharedObj::load(const char * const p_library_path)
    {
        WinPath wp(p_library_path);

        return this->load((osal::UnicodeString)wp);
    }

}  // end of namespace osal
