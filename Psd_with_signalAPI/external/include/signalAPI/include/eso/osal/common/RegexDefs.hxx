/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_COMMON_REGEXDEFS_HXX
#define OSAL_COMMON_REGEXDEFS_HXX

#    ifdef OSAL_USE_SPENCER

#include <osal/osal_dso.h>
#include <osal/common/SpencerRegexp.hxx>

namespace osal
{

struct RegMatchHandle
{
    size_t start_index;
    size_t length;
};

struct OSAL_EXPORT RegexHandle
{
    mutable oc::Regexp regexp;

    RegexHandle() :
        regexp()
    { }

    bool isValid() const
    {
        return regexp.HasCompiledOK();
    }
};

} // end ns osal

#    endif // OSAL_USE_SPENCER

#endif
