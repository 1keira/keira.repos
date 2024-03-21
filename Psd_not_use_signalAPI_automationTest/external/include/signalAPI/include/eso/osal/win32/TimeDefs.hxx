#ifndef OSAL_WIN32_TIMEDEFS_HXX
#define OSAL_WIN32_TIMEDEFS_HXX

#include <osal/osal.hxx>

namespace osal
{

// this is the difference between the UNIX epoch and the WIN32 epoch
// (FileTime) WIN32 epoch is longer than the UNIX epoch (somewhen about
// 16xy they think it started)
#define OSAL_DELTA_EPOCH_IN_MSEC  11644473600000ULL

inline osal::TimeT convertFileTimeToOsalTime(const FILETIME &ft)
{
    osal::TimeT ret;
    // don't actually ask what I'm doing here. I borrowed this code
    // from the net and it works. Thanks god.
    ret = static_cast<TimeT>(ft.dwHighDateTime) << 32;

    ret |= ft.dwLowDateTime;

    // from 100 nano-sec periods to msec
    ret = ret / 10 / 1000;

    // from WIN32 epoch to UNIX epoch
    ret -= OSAL_DELTA_EPOCH_IN_MSEC;

    return ret;
}

inline FILETIME convertOsalTimeToFileTime(const osal::TimeT &ot)
{
    osal::TimeT tmp = ot;
    // from UNIX epoch to WIN32 epoch
    tmp += OSAL_DELTA_EPOCH_IN_MSEC;

    // from msec to 100 nano-sec periods
    tmp = tmp * 10 * 1000;

    FILETIME ret;

    ret.dwLowDateTime = (DWORD)tmp;
    ret.dwHighDateTime = (DWORD)(tmp >> 32);

    return ret;
}

} // end ns osal

#endif // inc. guard
