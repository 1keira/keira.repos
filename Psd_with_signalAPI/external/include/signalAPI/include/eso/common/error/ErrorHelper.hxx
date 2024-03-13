/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/
#ifndef IPL_ERRORHELPER_HXX
#define IPL_ERRORHELPER_HXX

#include <ipl_config.h>
#include <common/ipl_namespace.hxx>

#include <stdlib.h>

#include <common/iplcommon_dso.h>
#include <common/types/new.hxx>
#include <common/CommonError.hxx>


namespace IPL_NAMESPACE
{

class raise_error_t
{ };

IPLCOMMON_EXPORT extern const raise_error_t raise_error;

/**
 * \brief
 *     Return a source location path relative to the src or include
 *     directory

 *     This function is intended for printing out the __FILE__
 *     preprocessor string. This path is an absolute path when building
 *     with CMake and thus the paths get very long and clutter e. g.
 *     error output with useless information.
 *
 *     Thus this function tries to find the "src" or "include"
 *     directory part in \c path and returns a pointer into the string
 *     that is starting just past that part of the path.
 *
 *     If no decision can be made then the original path is returned.
 **/
const char* getShortenedSourceLocation(const char *path) IPL_NOEXCEPT;


} // namespace ipl

/**
 * \brief
 *    Array variant of void* operator new[](size_t, const
 *    ipl::raise_error_t&)
 **/
inline void* operator new(size_t s, const ipl::raise_error_t &re) IPL_NOEXCEPT
{
    void *ret = operator new(s, ipl::nothrow);

    if( ! ret )// BRANCH_COVERAGE_UNTESTABLE
    {
        ipl_raise( ipl::CommonError, ipl::OUT_OF_MEMORY );
    }

    return ret;
}

/**
 * \brief
 *    Allocate \c s bytes and raise an error on failure

 *    If memory allocation failes then an ipl::CommonError with reason
 *    ipl::OUT_OF_MEMORY will be raised.
 **/
inline void* operator new[](size_t s, const ipl::raise_error_t &re) IPL_NOEXCEPT
{
    void *ret = operator new[] (s, ipl::nothrow);

    if ( !ret )// BRANCH_COVERAGE_UNTESTABLE
    {
        ipl_raise( ipl::CommonError, ipl::OUT_OF_MEMORY );
    }

    return ret;
}

#endif // IPL_ERRORHELPER_HXX
