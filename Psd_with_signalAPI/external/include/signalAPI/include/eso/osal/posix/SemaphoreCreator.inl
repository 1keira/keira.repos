/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

namespace osal {

    inline bool SemaphoreCreator::create(const osal::UnicodeString &name,
                                         const size_t initial_count,
                                         const CreationStrategy strategy)
    {
        return create(name.nativeData(), initial_count, strategy);
    }

    inline bool SemaphoreCreator::deleteName(const osal::UnicodeString &name)
    {
        return SemaphoreCreator::deleteName(name.nativeData());
    }

}  // end of namespace osal
