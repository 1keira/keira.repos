/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

/****************************************************************************/
#ifndef IPLBASE_DSO_H
#define IPLBASE_DSO_H
/****************************************************************************/

#include <ipl_config.h>
#include "dso_macros.h"

/****************************************************************************/

#if defined(iplbase_EXPORTS)
    #define IPLBASE_EXPORT IPL_EXPORT_MARKER
#elif defined(IPL_STATIC_LIBS) || defined(IPL_STATIC_IPLBASE_LIB)
    #define IPLBASE_EXPORT IPL_STATICLINK_MARKER
#else
    #define IPLBASE_EXPORT IPL_IMPORT_MARKER
#endif

/****************************************************************************/

/*!
    \def IPLBASE_EXPORT
    \internal
    \brief Export marker
    
    For every object that should be exported from the iplbase library,
    prefix its declaration with IPLBASE_EXPORT.
    This macro will expand to the appropriate “export me” attribute
    depending on OS, compiler and need.
    
    \code
        class IPLBASE_EXPORT ClassName: public SomeClass {
            // class definition
        };
        
        IPLBASE_EXPORT returnType Function1(arg list);
    \endcode
*/

/****************************************************************************/
#endif
