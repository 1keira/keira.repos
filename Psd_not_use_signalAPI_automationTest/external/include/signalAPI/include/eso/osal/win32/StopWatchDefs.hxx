#ifndef OSAL_WIN32_STOPWATCHDEFS_HXX
#define OSAL_WIN32_STOPWATCHDEFS_HXX

#include <ipl_config.h>

#include <iplbase/win32.h>
#include <common/Macros.hxx>
#include <common/stdint.h>
#include <osal/Time.hxx>

namespace osal
{

typedef struct StopWatchHandle_
{
    enum ClockType
    {
        TICK_COUNT,
        HW_COUNT,
        PROCESS,
        THREAD
    };

    LARGE_INTEGER start_time;
    LARGE_INTEGER elapsed_time;
    ClockType clock;

    void translateTimeToUnitDirect(LARGE_INTEGER &time,
        const bool micro) const
    {
        if( clock == HW_COUNT )
        {
            if( !micro )
            {
                time.QuadPart /= (g_osal_win32_hwcounter_reffreq/1000);
            }
            // us.
            else
            {
                time.QuadPart /= (g_osal_win32_hwcounter_reffreq/1000);
                time.QuadPart *= 1000;
            }
        }
        else if( clock == TICK_COUNT )
        {
            if( !micro )
            {
                // already in the right unit
            }
            // us.
            else
            {
                // we need to extrapolate
                time.QuadPart *= 1000;
            }
        }
        else if( clock == THREAD || clock == PROCESS )
        {
            // here we have 100-nanosecond time unit
            if( !micro )
            {
                // down to msec.
                time.QuadPart = time.QuadPart / 10 / 1000;
            }
            else
            {
                // down to usec.
                time.QuadPart = time.QuadPart / 10;
            }
        }
    
    }

    LARGE_INTEGER translateTimeToUnitRet(const LARGE_INTEGER &time, const bool micro) const
    {
        LARGE_INTEGER ret = time;
        translateTimeToUnitDirect(ret, micro);
        return ret;
    }

    // global function to calculate time differences
    // for high performance counters
    LARGE_INTEGER calcDiffTime(const LARGE_INTEGER &start, const LARGE_INTEGER &end) const
    {
        if( clock != TICK_COUNT )
        {
            LARGE_INTEGER diff_time;

            IPL_ASSERT( end.QuadPart >= start.QuadPart );

            diff_time.QuadPart = (end.QuadPart - start.QuadPart);

            return diff_time;
        }
        else
        {
            // here we have to check for overflow of the GetTickCount(). It flows over every 50 days or
            // something. This also means that we can't assume an error if end is less then start.
            const DWORD end_dw = static_cast<DWORD>(end.QuadPart);
            const DWORD start_dw = static_cast<DWORD>(start.QuadPart);
    
            LARGE_INTEGER ret;
    
            if( end_dw < start_dw )
            {
                ret.QuadPart = 0;
                // get the part of start until the overflow occured
                ret.QuadPart += (UINT16_MAX - start_dw);
                ret.QuadPart += end_dw;

            }
            else
            {
                ret.QuadPart = end_dw - start_dw;
            }

            return ret;
        }
    }

    bool queryClock(LARGE_INTEGER &val) const
    {
        if( clock == HW_COUNT )
        {
            // get current performance counter value
            if(0 == QueryPerformanceCounter( &val ) )
            {
                return true;
            }
        }
        else if( clock == TICK_COUNT )
        {
            // we simply store the 32-bit tick count in the 64-bit member of LARGE_INTEGER
            val.QuadPart = GetTickCount();
        }
        else if( clock == THREAD )
        {
            FILETIME kernel, user, dummy_start, dummy_exit;
            const BOOL success = ::GetThreadTimes(
                ::GetCurrentThread(),
                &dummy_start,
                &dummy_exit,
                &kernel,
                &user);

            val.LowPart = kernel.dwLowDateTime + user.dwLowDateTime;
            val.HighPart = kernel.dwHighDateTime + user.dwHighDateTime;

            return !success;

        }
        else if( clock == PROCESS )
        {
/* pedu2501: WinCE 6.0 does not support GetProcessTimes().
 *
 * What is possible is to get a snapshot of all threads in the current
 * process via "CreateToolhelp32Snapshot()" and "Thread32First(),
 * Thread32Next()" and then use "OpenThread()" on the retrieved
 * ThreadIDs to get a ThreadHandle and use that ThreadHandles to call
 * ThreadTimes().
 */
#if defined(IPL_OS_WINCE)
            return true; // pedu2501: Return with failure
#else
            FILETIME kernel, user, dummy_start, dummy_exit;
            const BOOL success = ::GetProcessTimes(
                ::GetCurrentProcess(),
                &dummy_start,
                &dummy_exit,
                &kernel,
                &user);
    
            val.LowPart = kernel.dwLowDateTime + user.dwLowDateTime;
            val.HighPart = kernel.dwHighDateTime + user.dwHighDateTime;

            return !success;
#endif
        }

        return false;
    }
} StopWatchHandle;

} // end ns osal

#endif // inc. guard
