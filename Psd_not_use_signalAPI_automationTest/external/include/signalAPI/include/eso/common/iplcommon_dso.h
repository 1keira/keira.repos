/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef IPLCOMMON_DSO_H
#define IPLCOMMON_DSO_H
/****************************************************************************/

#include <ipl_config.h>
#include <iplbase/dso_macros.h>

/****************************************************************************/

#if defined(iplcommon_EXPORTS) || defined(IPL_STATIC_LIBS)
    //! \brief EVIL STUFF – DO NOT USE
    #define IPLCOMMON_EXPORT_CONTEXT
#endif

/****************************************************************************/

// the iplcommon code may be compiled into different libraries as of now iplcommon hence the
// expansion of the IPLCOMMON_EXPORT needs to be triggered by either of them
#if defined(iplcommon_EXPORTS)
    #define IPLCOMMON_EXPORT IPL_EXPORT_MARKER
#elif defined(IPL_STATIC_LIBS)
    #define IPLCOMMON_EXPORT IPL_STATICLINK_MARKER
#else
    #define IPLCOMMON_EXPORT IPL_IMPORT_MARKER
#endif


/****************************************************************************/

/*!
    \def IPLCOMMON_EXPORT
    \internal
    \brief Export marker
    
    For every object that should be exported from the iplcommon library
    (whichever that may be), prefix its declaration with IPLCOMMON_EXPORT.
    This macro will expand to the appropriate “export me” attribute
    depending on OS, compiler and need.
    
    \code
        class IPLCOMMON_EXPORT ClassName: public SomeClass {
            // class definition
        };
        
        IPLCOMMON_EXPORT returnType Function1(arg list);
    \endcode
*/

/*!
    \def IPLCOMMON_EXPORT_ELF
    \brief Executable format aware export marker
    
    Like \ref IPLCOMMON_EXPORT, but expanding to nothing on Windows
    or other non-ELF architectures.
*/

/*!
    \def IPLCOMMON_EXPORT_WIN32
    \brief Executable format aware export marker
    
    Like \ref IPLCOMMON_EXPORT, but only on Windows,
    expanding to nothing on other architectures.
*/

/****************************************************************************/
#endif
