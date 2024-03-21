#ifndef TRACING_PROTOCOL_DSO_H
#define TRACING_PROTOCOL_DSO_H

#include <ipl_config.h>
#include <iplbase/dso_macros.h>

/*!
    \brief Export/import macros for the tracing protocol shared library
*/

#if defined (TracingProtocol_EXPORTS)
    #define TRACING_PROTOCOL_EXPORT IPL_EXPORT_MARKER
#elif defined(IPL_STATIC_LIBS) || defined(Protocol_STATIC)
    #define TRACING_PROTOCOL_EXPORT IPL_STATICLINK_MARKER
#else
    #define TRACING_PROTOCOL_EXPORT IPL_IMPORT_MARKER
#endif

#endif
