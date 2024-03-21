/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

namespace osal {

    inline size_t Osal::SystemInfo::getPagesize() const
    {
        return m_handle.pagesize;
    }

    inline size_t Osal::SystemInfo::getNumCPUs() const
    {
        return m_handle.cpu_count;
    }

}  // end of namespace osal

#include <osal/common/osal.inl>
