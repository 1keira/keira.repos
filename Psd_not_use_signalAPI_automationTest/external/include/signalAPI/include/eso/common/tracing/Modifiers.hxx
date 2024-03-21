/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef TRACING_MODIFIERS_HXX
#define TRACING_MODIFIERS_HXX

#include <common/iplcommon_dso.h>
#include <common/stdint.h>

namespace tracing
{

//! \brief Currently specified modifiers.
struct IPLCOMMON_EXPORT Modifiers
{
    static const int16_t NONE;           /* = 0; */       //! Default value for trace message modifiers.
    static const int16_t EXPAND_NOW;     /* = 1 << 0; */  //! Reserved.
    static const int16_t SAFE_TRANSPORT; /* = 1 << 1; */  //! Indicates a message that must not get lost.
    static const int16_t OBFUSCATE;      /* = 1 << 2; */  //! Obfuscate regions marked by @...@
    static const int16_t GEN_TAGS_LIST;  /* = 1 << 11; */ //! Protocol extension for tags list
    static const int16_t OBJECT_NODE;    /* = 1 << 12; */ //! Protocol extension for object node
    static const int16_t TIMESTAMP_NS;   /* = 1 << 13; */ //! Protocol extension for high res timestampNS
    static const int16_t PRIVACY_FLAGS;  /* = 1 << 14; */ //! Protocol extension for privacy flags
    static const int16_t EXTEND_MODIFIER;/* = 1 << 15; */ //! Reserved. Presence of follow up modifier
    static const char * NAMES[16];
};

}

#endif /* TRACING_MODIFIERS_HXX */
