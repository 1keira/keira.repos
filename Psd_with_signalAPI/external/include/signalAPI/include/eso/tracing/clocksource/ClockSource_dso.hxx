/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

/****************************************************************************/
#ifndef CLOCKSOURCE_DSO_H
#define CLOCKSOURCE_DSO_H
/****************************************************************************/

#include <ipl_config.h>
#include <iplbase/dso_macros.h>
#include "IClockSource.hxx"

/****************************************************************************/

#if defined(CLOCKSOURCE_EXPORTS)
    #define CLOCKSOURCE_EXPORT IPL_EXPORT_MARKER
#elif defined(IPL_STATIC_LIBS)
    #define CLOCKSOURCE_EXPORT IPL_STATICLINK_MARKER
#else
    #define CLOCKSOURCE_EXPORT IPL_IMPORT_MARKER
#endif

/*!
 *   \brief Every plugin shall expose getClockSourceFactory that returns ClockSourceFactory.
 *   E.g.
 *   extern "C" CLOCKSOURCE_EXPORT struct tracing::ClockSourceFactory * getClockSourceFactory()
 */
namespace tracing {
    typedef const char *    (*ClockSourceName)();
    typedef IClockSource *  (*ClockSourceCreate)();
    typedef void            (*ClockSourceDestroy)(IClockSource *);

    struct ClockSourceFactory
    {
        ClockSourceName clocksource_name;
        ClockSourceCreate clocksource_create;
        ClockSourceDestroy clocksource_destroy;
    };
}// end of namespace tracing

#endif
