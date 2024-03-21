#ifndef SERVMNGT_DSO_H
#define SERVMNGT_DSO_H

/*
    Copyright esolutions GmbH
    All rights reserved
*/

#include <ipl_config.h>
#include <iplbase/dso_macros.h>

#if defined(servmngt_EXPORTS)
    #define SERVMNGT_EXPORT IPL_EXPORT_MARKER
#elif defined(IPL_STATIC_LIBS)
    #define SERVMNGT_EXPORT IPL_STATICLINK_MARKER
#else
    #define SERVMNGT_EXPORT IPL_IMPORT_MARKER
#endif

#endif
