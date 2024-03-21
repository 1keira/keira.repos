/*
    Copyright e.solutions GmbH
    All rights reserved
    Authors:
        Matthias Gerstner
    $Id: $
*/

#include "WinPath.hxx"

namespace osal {
    
    inline bool BinFileBase::open(const char *p,
                                  const OpenFlags &flags,
                                  const FileAccess &access)
    {
        WinPath p2(p);

        // call the UCS variant
        return BinFileBase::open(p2, flags, access);
    }

}  // end of namespace osal
