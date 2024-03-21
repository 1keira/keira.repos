/*
    Copyright e.solutions GmbH
    All rights reserved
    Authors:
        Matthias Gerstner
    $Id: $
*/

namespace osal {

    inline void HeapInfo::update()
    {
//         m_handle.info = ::mallinfo();
    }

    inline size_t HeapInfo::heapSize() const
    {
        return 0;
//         return m_handle.info.arena + m_handle.info.hblkhd;
    }

    inline size_t HeapInfo::usedSize() const
    {
        return 0;
//         return m_handle.info.uordblks;
    }

    inline size_t HeapInfo::freeSize() const
    {
        return 0;
//         return m_handle.info.fordblks;
    }

} // end ns osal
