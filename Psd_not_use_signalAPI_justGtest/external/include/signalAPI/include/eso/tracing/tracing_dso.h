/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef TRACING_DSO_H
#define TRACING_DSO_H

/*!
    \file
    \brief Export/import macros for the tracing shared library
*/

#include <ipl_config.h>
#include <iplbase/dso_macros.h>

#if defined(tracing_EXPORTS) || defined(tracing_static_util_EXPORTS)
    #define TRACINGIMPL_EXPORT IPL_EXPORT_MARKER
#elif defined(IPL_STATIC_LIBS)
    #define TRACINGIMPL_EXPORT IPL_STATICLINK_MARKER
#else
    #define TRACINGIMPL_EXPORT IPL_IMPORT_MARKER
#endif

#endif
