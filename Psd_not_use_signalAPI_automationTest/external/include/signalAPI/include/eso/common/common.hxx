/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef IPL_COMMON_HXX
#define IPL_COMMON_HXX

#ifdef _MSC_VER
#pragma message(__FILE__)
#pragma message("THIS FILE IS DEPRECATED. EXPLICITLY INCLUDE WHAT YOU NEED INSTEAD.")
#else
#warning THIS FILE IS DEPRECATED. EXPLICITLY INCLUDE WHAT YOU NEED INSTEAD.
#endif

// for C++ this makes stdint.h also define constant macros and limits
// for 64 bit types note: You should best enable these definitions from
// within your build system to prevent trouble regarding strange include
// orders (if other standard headers are included then stdint.h may be
// included before this header has the chance to define them)
#ifdef __cplusplus
    #ifndef __STDC_LIMIT_MACROS
        #ifdef __GNUC__
            #warning "You should define __STDC_LIMIT_MACROS from within your build system"
        #endif
        #ifdef __MSC_VER__
            #pragma message ( "You should define __STDC_LIMIT_MACROS from within your build system" )
        #endif
        #define __STDC_LIMIT_MACROS
    #endif
    #ifndef __STDC_CONSTANT_MACROS
        #ifdef __GNUC__
            #warning "You should define __STDC_CONSTANT_MACROS from within your build system"
        #endif
        #ifdef __MSC_VER__
            #pragma message ( "You should define __STDC_CONSTANT_MACROS from within your build system" )
        #endif
        #define __STDC_CONSTANT_MACROS
    #endif
#endif

// our handling of C99 types and fallbacks when the headers are missing
#include <ipl_config.h> // HAVE_... defines

// #ifdef HAVE_INTTYPES_H
// // try inttypes.h first, it includes stdint.h
// /*
//  C99 says that C++ should define the macros from inttypes.h only when
//  __STDC_FORMAT_MACROS is defined before inttypes.h is included.
//  The C++ standard defines them always when cinttypes is included.
//  We include inttypes.h so we define it.
// */
// #define __STDC_FORMAT_MACROS
// #include <inttypes.h>
// #else
//
// // try stdint.h
// #ifdef HAVE_STDINT_H
// #include <stdint.h>
// #else
// // use fallback
// // include from the directory where this file (common.hxx) resides
// #define __STDC_FORMAT_MACROS
// #include "inttypes.h"
// #endif
#include <common/inttypes.h>
//
// #endif

// nothing should be included before stdint.h
#include <limits.h>

// not used at all
#ifdef __cplusplus
#define INLINE_CPP inline
#else
#define INLINE_CPP
#endif

// platform specific replacements
#include <common/replacements.hxx>

#ifdef _MSC_VER
    /*
     *    all right ... I've finally looked deeper into the
     *    strncpy vs. strncpy_s stuff on VS2005 and it turns out
     *    that the strncpy_s variant (which is non standard!)
     *    takes another pretty much redundant parameter telling
     *    not only "the number of characters" to copy but the size
     *    of the source *and* the target buffer.
     *
     *    I consider this harassment and define this thing now to
     *    make the compiler shut up on such stuff in the future
     */
// not needed here, already in iplcompiler.h
#    pragma warning(disable:4996)
#endif

#endif
