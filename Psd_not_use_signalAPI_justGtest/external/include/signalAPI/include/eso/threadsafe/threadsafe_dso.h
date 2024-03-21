/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

/****************************************************************************/
#ifndef THREADSAFE_DSO_H
#define THREADSAFE_DSO_H
/****************************************************************************/

#include <ipl_config.h>
#include <iplbase/dso_macros.h>

/****************************************************************************/

#if defined(threadsafe_EXPORTS)
    #define THREADSAFE_EXPORT IPL_EXPORT_MARKER
#elif defined(IPL_STATIC_LIBS) || defined(IPL_STATIC_THREADSAFE_LIB)
    #define THREADSAFE_EXPORT IPL_STATICLINK_MARKER
#else
    #define THREADSAFE_EXPORT IPL_IMPORT_MARKER
#endif

/****************************************************************************/

/*!
    \def THREADSAFE_EXPORT
    \internal
    \brief Export marker
    
    For every object that should be exported from the threadsafe library,
    prefix its declaration with THREADSAFE_EXPORT.
    This macro will expand to the appropriate “export me” attribute
    depending on OS, compiler and need.
    
    \code
        class THREADSAFE_EXPORT ClassName: public SomeClass {
            // class definition
        };
        
        THREADSAFE_EXPORT returnType Function1(arg list);
    \endcode
*/

/****************************************************************************/
#endif
