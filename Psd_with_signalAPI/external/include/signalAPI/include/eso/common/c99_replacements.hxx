/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef IPL_C99_REPLACEMENTS_HXX
#define IPL_C99_REPLACEMENTS_HXX

/*
 * this header pulls in some replacements for C99 c library functions
 * that are missing on Win32/MSVC systems as they don't implement that
 * standard fully.
 */

#include <ipl_config.h>
#include <wchar.h>
#include <common/iplcommon_dso.h>

#if defined(_MSC_VER) && defined(WIN32) && _MSC_VER<1900
/*
 * \brief
 *     Provides C99 conformant snprintf function
 * \warning
 *     The _snprintf function provided by up to MS VS 2010 does *not*
 *     conform to C99. It differs in the handling of the return value
 *     as it returns -1 if the data didn't fit. Also it doesn't
 *     terminate \c str if the data didn't fit.
 */
int IPLCOMMON_EXPORT snprintf(char *str, size_t size,
    const char *format, ...);
#endif

#ifndef HAVE_LLABS
// maps the C99 llabs() for 64 bit integers to the Win32 proprietary
// _abs64
#define llabs(LL) _abs64(LL)
#endif

#ifndef HAVE_SWPRINTF
// explanation for this can be found in replacements.hxx where the same
// is done for mingw
#define swprintf _snwprintf
#endif

#endif
