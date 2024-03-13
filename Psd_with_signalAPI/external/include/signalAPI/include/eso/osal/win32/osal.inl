/*
    Copyright e.solutions GmbH
    All rights reserved
    Authors:
        Matthias Gerstner
    $Id: $
*/

namespace osal {

    inline size_t Osal::SystemInfo::getPagesize() const
    {
        return m_handle.dwPageSize;
    }

    inline size_t Osal::SystemInfo::getNumCPUs() const
    {
        return m_handle.dwNumberOfProcessors;
    }

}  // end of namespace osal

#include <osal/common/osal.inl>
