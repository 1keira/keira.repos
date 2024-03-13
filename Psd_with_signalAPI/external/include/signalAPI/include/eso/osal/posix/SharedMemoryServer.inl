/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

namespace osal {

    inline bool SharedMemoryServer::create(const osal::UnicodeString &name,
                                           const size_t size,
                                           const CreationStrategy &strategy)
    {
        return this->create(name.nativeData(), size, strategy);
    }

    inline bool SharedMemoryServer::deleteName(const osal::UnicodeString &name)
    {
        return SharedMemoryServer::deleteName(name.nativeData());
    }

}  // end of namespace osal
