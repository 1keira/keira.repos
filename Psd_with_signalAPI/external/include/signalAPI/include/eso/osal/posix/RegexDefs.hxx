/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_POSIX_REGEXDEFS_HXX
#define OSAL_POSIX_REGEXDEFS_HXX

#ifdef OSAL_USE_POSIXREGEX
#    include <regex.h>

#    include <osal/osal_dso.h>
#include <cstring>

namespace osal
{

typedef regmatch_t RegMatchHandle;

struct OSAL_EXPORT RegexHandle
{
    RegexHandle() :
        valid(false),
        submatches(false)
    {
        memset(&regex, 0, sizeof(regex));
    }

    bool isValid() const
    { return valid; }

    int_fast8_t handleMatchError(const int err,
        const bool submatch = false) const;

    regex_t regex;
    bool valid;
    bool submatches;
};

} // end ns osal

#else
#    include <osal/common/RegexDefs.hxx>
#endif // OSAL_USE_POSIXREGEX

#endif // include guard
