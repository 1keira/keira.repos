/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/
        
/****************************************************************************/
#ifndef UTIL_DSO_H
#define UTIL_DSO_H
/****************************************************************************/

#include <ipl_config.h>
#include <iplbase/dso_macros.h>

/****************************************************************************/

#if defined(util_EXPORTS) || defined(IPL_STATIC_LIBS)
    #define UTIL_EXPORT_CONTEXT
#endif

/****************************************************************************/

#if defined(util_EXPORTS)
    #define UTIL_EXPORT IPL_EXPORT_MARKER
#elif defined(IPL_STATIC_LIBS) || defined(IPL_STATIC_UTIL_LIB)
    #define UTIL_EXPORT IPL_STATICLINK_MARKER
#else
    #define UTIL_EXPORT IPL_IMPORT_MARKER
#endif

/****************************************************************************/

/*!
    \def UTIL_EXPORT
    \internal
    \brief Export marker
    
    For every object that should be exported from the util library,
    prefix its declaration with UTIL_EXPORT.
    This macro will expand to the appropriate “export me” attribute
    depending on OS, compiler and need.
    
    \code
        class UTIL_EXPORT ClassName: public SomeClass {
            // class definition
        };
        
        UTIL_EXPORT returnType Function1(arg list);
    \endcode
*/

/****************************************************************************/
#endif
