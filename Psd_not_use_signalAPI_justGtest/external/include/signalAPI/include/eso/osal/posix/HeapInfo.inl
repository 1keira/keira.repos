/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

namespace osal {

    inline void HeapInfo::update()
    {
        m_handle.info =
#if defined(HAVE_MALLINFO2)
            ::mallinfo2();
#else // using either real mallinfo() or the dummy implementation
            ::mallinfo();
#endif
    }

    inline size_t HeapInfo::heapSize() const
    {
        return m_handle.info.arena + m_handle.info.hblkhd;
    }

    inline size_t HeapInfo::usedSize() const
    {
        return m_handle.info.uordblks;
    }

    inline size_t HeapInfo::freeSize() const
    {
        return m_handle.info.fordblks;
    }

} // end ns osal
