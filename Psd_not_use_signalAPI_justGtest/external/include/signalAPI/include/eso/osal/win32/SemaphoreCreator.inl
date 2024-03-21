/*
    Copyright e.solutions GmbH
    All rights reserved
    Authors:
        Matthias Gerstner
    $Id: $
*/

#include "WinPath.hxx"

namespace osal {
    
    inline bool SemaphoreCreator::create(const char *name, const size_t initial_count,
                                         const CreationStrategy strategy)
    {
        WinPath p2(name);

        return this->create( static_cast<osal::UnicodeString>(name),
            initial_count, strategy );
    }

    inline bool SemaphoreCreator::deleteName(const osal::UnicodeString &name)
    {
        // no-op on windows
        return false;
    }

}  // end of namespace osal
