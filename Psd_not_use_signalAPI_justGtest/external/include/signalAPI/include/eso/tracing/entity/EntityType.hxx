/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef TRACING_ENTITYTYPE_HXX
#define TRACING_ENTITYTYPE_HXX

#include <ipl_config.h>
#include <common/stdint.h>
#include <tracing/tracing_dso.h>
#ifdef IPL_OS_WIN32
// pull in windows headers to avoid conflict with CALLBACK identifier
#include <iplbase/win32.h>
#endif

namespace tracing
{

//! \brief Entity type constant definitions.
struct TRACINGIMPL_EXPORT EntityType
{
    static const int16_t TARGET_ENTITY;    //! Defines a target-type entity.
    static const int16_t PROCESS_ENTITY;   //! Defines a process-type entity.
    static const int16_t THREAD_ENTITY;    //! Defines a thread-type entity.
    static const int16_t CHANNEL_ENTITY;   //! Defines a channel-type entity.
    static const int16_t CALLBACK_ENTITY;  //! Defines a callback-type entity.
    static const int16_t PROBE_ENTITY;     //! Defines a probe-type entity.
    static const int16_t LAST_ENTITY = 6;  //! Placeholder to determine number of entity types.

    static const char * NAMES[LAST_ENTITY]; //! Contains printable names of entity types.
};

}

#endif /* TRACING_ENTITYTYPE_HXX */

