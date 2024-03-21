/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_HEAPINFO_HXX
#define OSAL_HEAPINFO_HXX

#include <ipl_config.h>
#include <osal/osal_dso.h>

#if defined IPL_OS_POSIX
#    include "posix/HeapInfoDefs.hxx"
#elif defined IPL_OS_WINPC
#    include "win32/HeapInfoDefs.hxx"
#elif defined IPL_OS_INTEGRITY
#    include "integrity/HeapInfoDefs.hxx"
#else
#    error "error undefined IPL_OS_ variant"
#endif

namespace osal
{

/**
 * \brief
 *     Provide information about the process's heap

 *     The given datums are rather rough. For example on WIN32 data
 *     allocated for internal purposes and by the c library isn't
 *     included in usedSize(). Also calculation of overhead data is
 *     hard to achieve in a portable way.
 *
 *     Still these values should provide some idea what the impact of
 *     application memory usage is.
 *
 **/
class /*OSAL_EXPORT*/ HeapInfo
{
public: // functions
    //! default ctor.; doesn't get a current snaphosrt!
    HeapInfo() { }

    //! get a new snapshot of heap information
    inline void update();

    //! get the overall size of the heap, in bytes
    inline size_t heapSize() const;

    //! get the size of the heap, in bytes, that is actually used
    inline size_t usedSize() const;

    //! get the size of the heap, in bytes, that is free for use
    inline size_t freeSize() const;
private: // data
    HeapInfoHandle m_handle;
};

} // end namespace

#if defined IPL_OS_POSIX
#    include "posix/HeapInfo.inl"
#elif defined IPL_OS_WINPC
#    include "win32/HeapInfo.inl"
#elif defined IPL_OS_INTEGRITY
#    include "integrity/HeapInfo.inl"
#else
#    error "error undefined IPL_OS_ variant"
#endif

#endif // OSAL_HEAPINFO_HXX
