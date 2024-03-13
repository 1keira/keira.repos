/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/
        
#ifndef TRACING_IRC_HXX
#define TRACING_IRC_HXX

#include <common/tracing/tracing.hxx>

#ifndef NTRACE

//! \brief Create an IRC trace channel object.
#define IRC_DECLARE_ENTRY(DOMAIN, ENTRY) \
    ::tracing::Channel __irc__channel_ ## DOMAIN ## _ ## ENTRY( "IRC_" TOSTRING(DOMAIN) "_" TOSTRING(ENTRY) )

//! \brief Create an IRC info level trace message.
#define IRC_LOG_USAGE_C(DOMAIN, ENTRY, message) \
    do { \
        __irc__channel_ ## DOMAIN ## _ ## ENTRY .logC(::tracing::Levels::LevelINFO, message); \
    } while (0)

//! \brief Create an IRC info level trace message with arguments.
#define IRC_LOG_USAGE_CV(DOMAIN, ENTRY, message, ...) \
    do { \
        __irc__channel_ ## DOMAIN ## _ ## ENTRY .logCV(::tracing::Levels::LevelINFO, message, __VA_ARGS__); \
    } while (0)

//! \brief Create an IRC system error level trace message.
#define IRC_LOG_SYS_C(DOMAIN, ENTRY, message) \
    do { \
        __irc__channel_ ## DOMAIN ## _ ## ENTRY .logC(::tracing::Levels::LevelERROR, message); \
    } while (0)

//! \brief Create an IRC system error level trace message with arguments.
#define IRC_LOG_SYS_CV(DOMAIN, ENTRY, message, ...) \
    do { \
        __irc__channel_ ## DOMAIN ## _ ## ENTRY .logCV(::tracing::Levels::LevelERROR, message, __VA_ARGS__); \
    } while (0)

#else /* NTRACE */

#define IRC_DECLARE_ENTRY(DOMAIN, ENTRY)
#define IRC_LOG_USAGE_C(DOMAIN, ENTRY, message) do { /* NOP */ } while (0)
#define IRC_LOG_USAGE_CV(DOMAIN, ENTRY, message, ...) do { /* NOP */ } while (0)
#define IRC_LOG_SYS_C(DOMAIN, ENTRY, message) do { /* NOP */ } while (0)
#define IRC_LOG_SYS_CV(DOMAIN, ENTRY, message, ...) do { /* NOP */ } while (0)

#endif /* NTRACE */

#endif /* TRACING_IRC_HXX */

