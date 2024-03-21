#ifndef OSAL_WIN32_THREADDEFS_HXX
#define OSAL_WIN32_THREADDEFS_HXX

#include <ipl_config.h>

#ifdef IPL_OS_WINPC
#include <osal/AtomicCounter.hxx>
#endif

namespace osal
{

//! datatype for thread IDs
typedef DWORD OSThreadId;

//! datatype for thread api references
typedef struct ThreadHandle_
{
    HANDLE handle;
    //! \brief
    //!    this is needed as the HANDLE of the thread is somehow not fully compatible with
    //!    the DWORD that's returned as ThreadId
    DWORD thread_id;
    
#ifdef IPL_OS_WINPC
    //! if zero then no RT initialization has been done yet
    static osal::AtomicCounter m_rt_init;
#endif
} ThreadHandle;

} // end ns osal

#endif // inc. guard
