/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef IPL_REPLACEMENTS_HXX
#define IPL_REPLACEMENTS_HXX

/*
 *    This header is a new central place for transparently providing
 *    functions that are missing from certain operating systems (the
 *    functions of interest here are ANSI C functions and other
 *    standard functions that one might expect to be there everywhere)
 */

#ifdef _MSC_VER
#    ifdef WINCE
#        include <common/wince_replacements.hxx>
#    endif // WINCE
#    include <common/c99_replacements.hxx>
#endif // _MSC_VER

#ifdef __MINGW32__
    /*
     * here we have some obscurity. the c library does only provide a
     * version of swprintf that doesn't take a size_t. In c++ the function
     * is overloaded, however, such that using it works as expected.
     *
     * The pure c library however is not enough. An mingw uses the pure
     * library. So we need to do that define (MSDN even suggests it) to get
     * what we want. We override the default swprintf by the right one.
     */
#include <wchar.h> // needs to be included before overriding the function
#    define swprintf _snwprintf
#endif

#endif
