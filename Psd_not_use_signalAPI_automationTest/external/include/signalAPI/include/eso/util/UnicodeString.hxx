/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_UNICODESTRING_HXX
#define UTIL_UNICODESTRING_HXX

#include <ipl_config.h>
#include <util/util_dso.h>
#include <osal/osal.hxx>
#include <osal/Environment.hxx>

/*
If the functions
    char const* char_str() const
    wchar_t const* wchar_str() const
are called directly at the UnicodeString, no zero-termination of the data is
guaranteed. The proper way to get a raw string pointer is to get a DataBuffer
object through a call to utf8(), utf16(), ascii() or whatever encoding it should
be in and then call the functions above on that object. This way, a
zero-termination of the data is provided.
*/

#ifndef STRING_BASE_ENCODING
//use the system's native base encoding as our base encoding
#if defined(IPL_OS_WIN32)
#define STRING_BASE_ENCODING 16
#else
#define STRING_BASE_ENCODING 8
#endif
#endif

namespace util{
class UnicodeString16;
class UnicodeString8;

#if STRING_BASE_ENCODING==16
typedef UnicodeString16 UnicodeString;
#elif STRING_BASE_ENCODING==8
typedef UnicodeString8 UnicodeString;
#else
#error STRING_BASE_ENCODING has to be set to 8 or 16 for utf8 or utf16!
#endif

}

#include <util/UnicodeString8.hxx>
#include <util/UnicodeString16.hxx>

namespace util {
// functions to call the placement delete
UTIL_EXPORT void placementDelete(util::UnicodeString8* val) IPL_NOEXCEPT ;
UTIL_EXPORT void placementDelete(util::UnicodeString16* val) IPL_NOEXCEPT ;

}
#endif // UTIL_UNICODESTRING_HXX
