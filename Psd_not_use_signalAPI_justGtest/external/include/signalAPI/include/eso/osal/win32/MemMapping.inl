#include <iplbase/win32.h>

namespace osal {

    inline bool MemMapping::isValid() const
    {
        return m_handle.addr != NULL;
    }

    inline void* MemMapping::addr()
    {
        return m_handle.addr;
    }

    inline const void* MemMapping::constAddr() const
    {
        return m_handle.addr;
    }

    inline size_t MemMapping::getAlignment()
    {
        // this is the normal pagesize
        return osal::Osal::getSystemInfo().getPagesize();
    }

    inline size_t MemMapping::getStartAddrAlignment()
    {
        return osal::Osal::getSystemInfo().getHandle().dwAllocationGranularity;
    }

} // end ns osal
