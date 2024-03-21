/*
    Copyright e.solutions GmbH
    All rights reserved
    Authors:
        Matthias Gerstner
    $Id: $
*/

#include "WinPath.hxx"

namespace osal {
    
    inline bool SemaphoreClient::attach(const char *p)
    {
        WinPath p2(p);
        return this->attach( static_cast<osal::UnicodeString>(p2) );
    }

}  // end of namespace osal
