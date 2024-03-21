/*
    Copyright esolutions GmbH
    All rights reserved
    Authors:
        Matthias Gerstner
    $Id: $
*/

#include "WinPath.hxx"

namespace osal {

    inline bool SharedMemoryClient::attach(
        const char *name, const MemMapping::MemAccessFlags &access)
    {
        return this->attach( UnicodeString(WinPath(name).getPath()), access);
    }

}  // end of namespace osal
