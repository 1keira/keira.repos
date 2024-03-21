/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

/****************************************************************************/
/****************************************************************************/
#ifndef OSAL_DSO_H
#define OSAL_DSO_H
/****************************************************************************/

#include <ipl_config.h>
#include <iplbase/dso_macros.h>

/****************************************************************************/

#if defined(osal_EXPORTS) || defined(IPL_STATIC_LIBS)
    //! \brief EVIL STUFF – DO NOT USE
    #define OSAL_EXPORT_CONTEXT
#endif

/****************************************************************************/

#if defined(osal_EXPORTS)
    #define OSAL_EXPORT IPL_EXPORT_MARKER
#elif defined(IPL_STATIC_LIBS)
    #define OSAL_EXPORT IPL_STATICLINK_MARKER
#else
    #define OSAL_EXPORT IPL_IMPORT_MARKER
#endif

/****************************************************************************/

/*!
    \def OSAL_EXPORT
    \internal
    \brief Export marker
    
    For every object that should be exported from the osal library,
    prefix its declaration with OSAL_EXPORT.
    This macro will expand to the appropriate “export me” attribute
    depending on OS, compiler and need.
    
    \code
        class OSAL_EXPORT ClassName: public SomeClass {
            // class definition
        };
        
        OSAL_EXPORT returnType Function1(arg list);
    \endcode
*/

/****************************************************************************/
#endif
