/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

namespace osal {

    inline bool SharedMemoryBase::init(const bool lazy)
    {
        (void)lazy;
        return false;
    }

    inline void SharedMemoryBase::exit()
    {
        /* NOP */
    }

}  // end of namespace osal
