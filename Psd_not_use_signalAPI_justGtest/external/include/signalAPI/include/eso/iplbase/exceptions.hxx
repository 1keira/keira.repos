/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

/*****************************************************************************/
#ifndef IPLBASE_EXCEPTIONS_HXX
#define IPLBASE_EXCEPTIONS_HXX
/*****************************************************************************/

#include <ipl_config.h>
#include <common/types/exception.hxx>
#include "abort.hxx"

/*****************************************************************************/
/*
    Note on macros that take code as parameter
    
    A macro in the style of
    #define FOO(code) do_something(); code; do_more();
    fails miserably if code contains commas that are not between (),
    as those get parsed by the preprocessor. The solution is to define FOO
    as a variadic macro and pass the code solely as ... aka. __VA_ARGS__.
*/
/*****************************************************************************/
/*!
    \def IPL_NOEXCEPT
    
    Defined in ipl_config.h and ultimatly in the toolchain file this expands to
    <code>noexcept</code>, <code>throw()</code> or nothing, depending on the
    actual compiler.
*/
/*****************************************************************************/

/*!
    \def IPLBASE_TRY
    
    Takes C++ code as parameter and expands to this code surrounded either
    by curly braces <code>{ }</code> or a try block <code>try { }</code>,
    depending in whether IPL_HAVE_EXCEPTIONS is defined.
*/

/*!
    \def IPLBASE_CATCH
    
    Takes a catch-like exception declaration and C++ code as parameters and
    expands either an empty pair of curly braces or a catch block with this
    exception declaration and this code,
    depending in whether IPL_HAVE_EXCEPTIONS is defined.
*/

#ifdef IPL_HAVE_EXCEPTIONS

    #define IPLBASE_TRY(...) try { __VA_ARGS__ }
    #define IPLBASE_CATCH(EXCEPTION, ...) catch(EXCEPTION) { __VA_ARGS__ }
    
#else

    #define IPLBASE_TRY(...) { __VA_ARGS__ }
    #define IPLBASE_CATCH(EXCEPTION, ...) {}
    
#endif

/*!
    \def IPLBASE_ABORT_ON_EXCEPTION
    
    Takes C++ code as parameter and expands either to this code surrounded by
    curly braces <code>{ }</code> or a try-catch-block containing the code and
    aborting the program on any exception,
    depending in whether IPL_HAVE_EXCEPTIONS is defined.
*/
#if defined __has_builtin /* Clang and new GCC only */
#if __has_builtin(__builtin_unreachable)
// special version suppressing spurious warnings
#define IPLBASE_ABORT_ON_EXCEPTION(...) { IPLBASE_TRY(__VA_ARGS__) \
    IPLBASE_CATCH(const std::exception& e, ::iplbase::abort(__FILE__, __LINE__, __FUNCTION__, "%s", e.what()); __builtin_unreachable();)\
    IPLBASE_CATCH(..., ::iplbase::abort(__FILE__, __LINE__, __FUNCTION__, "Exception caught"); __builtin_unreachable();)\
    }
#endif
#endif
#ifndef IPLBASE_ABORT_ON_EXCEPTION
// normal version suppressing the same warnings the hard way
#define IPLBASE_ABORT_ON_EXCEPTION(...) { IPLBASE_TRY(__VA_ARGS__) \
    IPLBASE_CATCH(const std::exception& e, ::iplbase::abort(__FILE__, __LINE__, __FUNCTION__, "%s", e.what());\
    /* this is never reached but convinces the compiler that we will never return: */ \
    ::abort();)\
    IPLBASE_CATCH(..., ::iplbase::abort(__FILE__, __LINE__, __FUNCTION__, "Exception caught");\
    /* this is never reached but convinces the compiler that we will never return: */ \
    ::abort();)\
    }
#endif

/*****************************************************************************/
#endif
