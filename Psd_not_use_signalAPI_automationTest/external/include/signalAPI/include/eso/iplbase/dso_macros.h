/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

/****************************************************************************/
#ifndef DSO_MACROS_H
#define DSO_MACROS_H
/****************************************************************************/

#include <ipl_config.h>

/*!
    \def IPL_EXPORT_MARKER
    \internal
    \brief Export marker

    Correctly sets export marker for symbols depending on
    the operating system. It can be used like this

    \code
        class IPL_EXPORT_MARKER SomeClass {
            // class definition
        };

        IPL_EXPORT_MARKER void function();
        
    \endcode

    \warning Do not use it in shared public headers as Windows
    requires different markers depending on whether the
    symbol needs to be exported or imported.
 **/
#if defined(IPL_OS_WIN32)
    #define IPL_EXPORT_MARKER __declspec(dllexport)
#elif defined IPL_OS_INTEGRITY
    #define IPL_EXPORT_MARKER
#else
    #if __GNUC__ >= 4 
        #define IPL_EXPORT_MARKER __attribute__ ((visibility("default")))
    #else
        #define IPL_EXPORT_MARKER
    #endif
#endif

/*!
    \def IPL_IMPORT_MARKER
    \internal
    \brief Import marker

    Correctly sets import marker for symbols depending on
    the operating system. This is mostly relevant for Windows
    as otherwise the export marker and import marker are the same.

    This macro is not meant to be used directly but as an indirection
    for other macros that decide whether to use an export, import or
    static lib marker in a shared public header.

    Could be used similarly to the export marker in code.
 **/
#if defined(IPL_OS_WIN32)
    #define IPL_IMPORT_MARKER __declspec(dllimport)
#elif defined IPL_OS_INTEGRITY
    #define IPL_IMPORT_MARKER
#else
    #if __GNUC__ >= 4 
        #define IPL_IMPORT_MARKER __attribute__ ((visibility("default")))
    #else
        #define IPL_IMPORT_MARKER
    #endif
#endif

/*!
    \def IPL_STATICLINK_MARKER
    \internal
    \brief Static Library export/import marker

    Correctly sets marker for statically linked symbols depending on
    the operating system. This is mostly relevant for Windows
    as otherwise the export marker is used.

    This macro is not meant to be used directly but as an indirection
    for other macros that decide whether to use an export, import or
    static lib marker in a public header.

    Could be used similarly to the export marker in code.
 **/
#if defined(IPL_OS_WIN32)
    #define IPL_STATICLINK_MARKER
#elif defined IPL_OS_INTEGRITY
    #define IPL_STATICLINK_MARKER
#else
    #if __GNUC__ >= 4 
        #define IPL_STATICLINK_MARKER __attribute__ ((visibility("default")))
    #else
        #define IPL_STATICLINK_MARKER
    #endif
#endif

/****************************************************************************/
#endif
