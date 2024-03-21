/*
    Copyright esolutions GmbH
    All rights reserved
    Authors:
        Matthias Gerstner
    $Id: $
*/

namespace osal
{

    inline bool SemaphoreClient::attach(const osal::UnicodeString &name)
    {
        return attach(name.nativeData());
    }

}  // end of namespace osal
