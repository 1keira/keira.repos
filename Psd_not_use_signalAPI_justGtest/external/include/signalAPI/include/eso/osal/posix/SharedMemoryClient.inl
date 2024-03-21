/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

namespace osal
{

    inline bool SharedMemoryClient::attach(const osal::UnicodeString &name,
                                           const osal::MemMapping::MemAccessFlags &access)
    {
        return this->attach(name.nativeData(), access);
    }

}  // end of namespace osal
