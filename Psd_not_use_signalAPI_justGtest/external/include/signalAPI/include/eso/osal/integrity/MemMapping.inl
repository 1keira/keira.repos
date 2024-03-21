#include "SharedMemoryDefs.hxx"
#include "SharedMemoryArea.h"

namespace osal {

    inline bool MemMapping::isValid() const
    {
         return m_handle != MAP_FAILED;
    }

    inline void* MemMapping::addr()
    {
         return m_handle;
    }

    inline const void* MemMapping::constAddr() const
    {
         return m_handle;
    }

    inline size_t MemMapping::getAlignment()
    {
         return osal::Osal::getSystemInfo().getPagesize();
    }

    inline size_t MemMapping::getStartAddrAlignment()
    {
         // the very same on POSIX
         return getAlignment();
    }

    inline MemMapping::MemMapping(const SharedMemoryHandle &shm,
        const MemAccessFlags& flags, const size_t length,
        const size_t off, void *suggested_addr,
        const bool get_ringbuffer
        )
    {
         // the very same on POSIX
         new(this) MemMapping(shm.fd, flags, length, off,
             suggested_addr, get_ringbuffer);
    }

} // end ns osal
