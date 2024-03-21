#ifndef OSAL_WIN32_HEAPINFORMATIONDEFS_HXX
#define OSAL_WIN32_HEAPINFORMATIONDEFS_HXX

#include <ipl_config.h>

#ifdef HAVE_MALLINFO
#    warning "You'd also have a mallinfo() available"
#endif

#include <iplbase/win32.h>

// on wince and with mingw we don't have CrtMemState stuff
//
// mingw also has no mallinfo
#if defined(IPL_OS_WINCE) || defined(__MINGW32__)
#    define    OSAL_NO_HEAP_INFO
#endif

#ifdef OSAL_NO_HEAP_INFO
#    define _CrtMemState int
#else
#    include <crtdbg.h>
#endif

#include <string.h>

namespace osal
{


struct HeapInfoHandle
{
    HeapInfoHandle()
    {
        reset();
    }

    void reset()
    {
        ::memset(&m_crt_state, 0, sizeof(_CrtMemState));
    }

    _CrtMemState m_crt_state;
};

} // end ns osal

#endif
