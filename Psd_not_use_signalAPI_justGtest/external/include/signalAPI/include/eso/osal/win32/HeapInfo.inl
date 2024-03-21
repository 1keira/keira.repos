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
#ifndef OSAL_NO_HEAP_INFO
        _CrtMemCheckpoint(&m_handle.m_crt_state);
#endif
    }

    inline size_t HeapInfo::heapSize() const
    {
#ifndef OSAL_NO_HEAP_INFO
        return m_handle.m_crt_state.lTotalCount;
#else
        return 0;
#endif
    }

    inline size_t HeapInfo::usedSize() const
    {
#ifndef OSAL_NO_HEAP_INFO
        // this leaves us wich allocations for the CRT itself and maybe
        // some special allocation types from other libraries
        return m_handle.m_crt_state.lSizes[_NORMAL_BLOCK];
#else
        return 0;
#endif
    }

    inline size_t HeapInfo::freeSize() const
    {
#ifndef OSAL_NO_HEAP_INFO
        return m_handle.m_crt_state.lSizes[_FREE_BLOCK];
#else
        return 0;
#endif
    }

} // end ns osal
