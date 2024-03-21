/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

namespace osal
{

    inline bool SemaphoreClient::attach(const osal::UnicodeString &name)
    {
        return attach(name.nativeData());
    }

}  // end of namespace osal
