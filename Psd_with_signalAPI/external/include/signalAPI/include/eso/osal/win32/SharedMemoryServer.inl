/*
    Copyright esolutions GmbH
    All rights reserved
    Authors:
        Matthias Gerstner
    $Id: $
*/

#include "WinPath.hxx"

namespace osal {

    inline bool SharedMemoryServer::create(const char *name, const size_t size,
                                           const CreationStrategy &strategy)
    {
        return this->create( UnicodeString(WinPath(name).getPath()), size, strategy);
    }

    inline bool SharedMemoryServer::deleteName(const osal::UnicodeString &name)
    {
        // no-op on windows
        return false;
    }

}  // end of namespace osal
