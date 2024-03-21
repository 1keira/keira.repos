/*
    Copyright 2021 e.solutions GmbH
    All rights reserved
*/

#ifndef TRACING_HXX
#define TRACING_HXX


//! \brief Create a string of the parameter
#define STRINGIFY(x) #x
//! \brief Helper macro to create strings of tokens which must be evaluated by the preprocessor
#define TOSTRING(x) STRINGIFY(x)

//! \brief Variable name used for trace channels referenced via IPL_TRACE_USE_CHANNEL
#define IPL_TRACE_CHANNEL_VARIABLE_NAME __tracing__scope

#include <ipl_config.h>

#ifndef NTRACE

#ifndef IPL_TRACE_DISABLE_STREAMS
#include <common/streams/sstream.hxx>
#include <common/streams/ios.hxx>
#endif

#include <utility>

#include <common/iplcommon_dso.h>

#include <common/tracing/Channel.hxx>
#include <common/tracing/SharedChannelPtr.hxx>
#include <common/tracing/IClient.hxx>
#include <common/tracing/IClientHelper.hxx>
#include <common/tracing/CallbackDispatcher.hxx>
#include <common/tracing/Modifiers.hxx>
#include <common/tracing/TraceBuffer.hxx>

// libfmt support
#if defined(TRACING_WITH_LIBFMT)
#   include <fmt/format.h>
#   include <common/tracing/formatter.hxx>
#endif

// define valid modifiers
#define IPL_TRACE_OBFUSCATE        ::tracing::Modifiers::OBFUSCATE

//! \brief Initializes tracing subsystem
#define IPL_TRACE_INIT_NAME(clientname) \
    ::tracing::client_helper->init(clientname)

//! \brief Initializes tracing subsystem
#define IPL_TRACE_INIT_NAME_READ_CONFIG(clientname, read_config) \
    ::tracing::client_helper->init((clientname), "client", (read_config))

//! \brief Deinitializes tracing subsystem
#define IPL_TRACE_EXIT() \
    ::tracing::client_helper->exit()

//! \brief Creates a trace channel object
#define IPL_TRACE_DECLARE_CHANNEL(channelname) \
    ::tracing::Channel __tracing__channel_ ## channelname( TOSTRING(channelname) );

//! \brief References a trace channel object declared in another source file
#define IPL_TRACE_DECLARE_CHANNEL_EXTERN(channelname) \
    extern ::tracing::Channel __tracing__channel_ ## channelname

//! \brief Declares a channel for use in a shared library which can be referenced by executables.
#define IPL_TRACE_DECLARE_CHANNEL_EXPORT(export_macro, channelname) \
    export_macro ::tracing::Channel __tracing__channel_ ## channelname( TOSTRING(channelname) );

//! \brief References a trace channel object declared in another libary.
#define IPL_TRACE_DECLARE_CHANNEL_IMPORT(export_macro, channelname) \
    extern export_macro ::tracing::Channel __tracing__channel_ ## channelname;

//! \brief Create a channel that could be shared
#define IPL_TRACE_DECLARE_SHARED_CHANNEL(channelname) \
    ::tracing::SharedChannelPtr __tracing__shared_channel_ptr_ ## channelname( TOSTRING(channelname) );

//! \brief References a shared trace channel object declared in another source file
#define IPL_TRACE_DECLARE_SHARED_CHANNEL_EXTERN(channelname) \
    extern ::tracing::SharedChannelPtr __tracing__shared_channel_ptr_ ## channelname

//! \brief Declare the scope of a shared channel
#define IPL_TRACE_USE_SHARED_CHANNEL(channelname) \
    ::tracing::Channel * __tracing__scope = __tracing__shared_channel_ptr_ ## channelname.getChannel()

//! \brief Defines the scope of a trace channel (use at the beginning of a block)
#define IPL_TRACE_USE_CHANNEL(channelname) \
    ::tracing::Channel * __tracing__scope = &__tracing__channel_ ## channelname

//! \brief Get the channel object referred by its name.
#define IPL_TRACE_GET_CHANNEL_OBJECT(channelname) \
    &__tracing__channel_ ## channelname

//! \brief Register a thread in the trace core; i.e. set a name for the caller thread.
#define IPL_TRACE_REGISTER_THREAD(threadname) \
    do { \
        if (::tracing::client_helper->getClient()) \
            ::tracing::client_helper->getClient()->registerThread(threadname); \
    } while (false)

//! \brief Unregister the thread in the trace core; i.e. disables the thread entity in the core.
#define IPL_TRACE_UNREGISTER_THREAD() \
    do { \
        if (::tracing::client_helper->getClient()) \
            ::tracing::client_helper->getClient()->unregisterThread(); \
    } while (false)

//! \brief Register a time zone with name and the time zone's resolution.
#define IPL_TRACE_REGISTER_TIMEZONE(name, resolution) \
    (::tracing::client_helper->getClient() ? ::tracing::client_helper->getClient()->registerTimeZone((name), (resolution)) : -1)

//! \brief Update a time zone's current time.
#define IPL_TRACE_UPDATE_TIMEZONE(id, current_time) \
    do { \
        if (::tracing::client_helper->getClient()) \
            ::tracing::client_helper->getClient()->updateTimeZone((id), (current_time)); \
    } while (false)

//! \brief Check if a channel's level setting would allow creation of trace messages with the specified level
#define IPL_TRACE_HAS_LEVEL(channelname, level) \
    ( __tracing__channel_ ## channelname .getFilterLevel() <= (level) )

//! \brief Set the trace level of a channel
#define IPL_TRACE_SET_LEVEL(channelname, level) \
    __tracing__channel_ ## channelname .changeFilterLevel(level)

//! \brief Get the trace level of a channel
#define IPL_TRACE_GET_LEVEL(channelname) \
    __tracing__channel_ ## channelname .getFilterLevel()

//! \brief check level macros are similar to HAS_LEVEL but they use the current scope
#define IPL_TRACE_CHECK_LEVEL(level) \
    (__tracing__scope->getFilterLevel() <= (level))
#define IPL_TRACE_CHECK_TRACE_LEVEL \
    (__tracing__scope->getFilterLevel() <= ::tracing::Levels::LevelTRACE)
#define IPL_TRACE_CHECK_DEBUG_LEVEL \
    (__tracing__scope->getFilterLevel() <= ::tracing::Levels::LevelDEBUG)
#define IPL_TRACE_CHECK_INFO_LEVEL \
    (__tracing__scope->getFilterLevel() <= ::tracing::Levels::LevelINFO)
#define IPL_TRACE_CHECK_WARN_LEVEL \
    (__tracing__scope->getFilterLevel() <= ::tracing::Levels::LevelWARN)
#define IPL_TRACE_CHECK_ERR_LEVEL \
    (__tracing__scope->getFilterLevel() <= ::tracing::Levels::LevelERROR)
#define IPL_TRACE_CHECK_FATAL_LEVEL \
    (__tracing__scope->getFilterLevel() <= ::tracing::Levels::LevelFATAL)


//! optionally disable stream based trace macros
#ifndef IPL_TRACE_DISABLE_STREAMS

#ifndef COMMON_TRACING_BY_FUNCTIONS

//! \brief Create a trace message (don't call directly, use IPL_TRACE_INFO etc. instead)
#define IPL_TRACE_LVL(level, msg) \
    do { \
        if (__tracing__scope->getFilterLevel() <= (level)) \
        { \
            ::ipl::ostringstream __tracing__out; \
            __tracing__out << msg; \
            __tracing__scope->log((level), __tracing__out.str()); \
        }\
    } while (false)

//! \brief Create a trace message with modifiers
//!        (don't call directly, use IPL_TRACE_INFO_M etc. instead)
#define IPL_TRACE_LVL_M(level, mod, msg) \
    do { \
        if (__tracing__scope->getFilterLevel() <= (level)) \
        { \
            ::ipl::ostringstream __tracing__out; \
            __tracing__out << msg; \
            __tracing__scope->log((level), (mod), __tracing__out.str()); \
        }\
    } while (false)
#endif  //  COMMON_TRACING_BY_FUNCTIONS

//! \brief Create a trace message with level "Trace"
#define IPL_TRACE_TRACE(...)    IPL_TRACE_LVL(::tracing::Levels::LevelTRACE, __VA_ARGS__)

//! \brief Create a trace message with level "Debug"
#define IPL_TRACE_DEBUG(...)    IPL_TRACE_LVL(::tracing::Levels::LevelDEBUG, __VA_ARGS__)

//! \brief Create a trace message with level "Info"
#define IPL_TRACE_INFO(...)        IPL_TRACE_LVL(::tracing::Levels::LevelINFO, __VA_ARGS__)

//! \brief Create a trace message with level "Warning"
#define IPL_TRACE_WARN(...)        IPL_TRACE_LVL(::tracing::Levels::LevelWARN, __VA_ARGS__)

//! \brief Create a trace message with level "Error"
#define IPL_TRACE_ERR(...)        IPL_TRACE_LVL(::tracing::Levels::LevelERROR, __VA_ARGS__)

//! \brief Create a trace message with level "Fatal"
#define IPL_TRACE_FATAL(...)    IPL_TRACE_LVL(::tracing::Levels::LevelFATAL, __VA_ARGS__)

// set of macros that allow to set a modifier
//! \brief Create a trace message with level "Trace"
#define IPL_TRACE_TRACE_M(mod, ...)    IPL_TRACE_LVL_M(::tracing::Levels::LevelTRACE, (mod), __VA_ARGS__)

//! \brief Create a trace message with level "Debug"
#define IPL_TRACE_DEBUG_M(mod, ...)    IPL_TRACE_LVL_M(::tracing::Levels::LevelDEBUG, (mod), __VA_ARGS__)

//! \brief Create a trace message with level "Info"
#define IPL_TRACE_INFO_M(mod, ...)    IPL_TRACE_LVL_M(::tracing::Levels::LevelINFO, (mod), __VA_ARGS__)

//! \brief Create a trace message with level "Warning"
#define IPL_TRACE_WARN_M(mod, ...)    IPL_TRACE_LVL_M(::tracing::Levels::LevelWARN, (mod), __VA_ARGS__)

//! \brief Create a trace message with level "Error"
#define IPL_TRACE_ERR_M(mod, ...)    IPL_TRACE_LVL_M(::tracing::Levels::LevelERROR, (mod), __VA_ARGS__)

//! \brief Create a trace message with level "Fatal"
#define IPL_TRACE_FATAL_M(mod, ...)    IPL_TRACE_LVL_M(::tracing::Levels::LevelFATAL, (mod), __VA_ARGS__)

#endif // IPL_TRACE_DISABLE_STREAMS


#ifdef COMMON_TRACING_BY_FUNCTIONS
// This option replaces the trace makros by trace functions (except for the stream-based makros)

namespace tracing
{

// single-instance functions allow to replace makros containing branches by simple non-branching function-calls:

//! \brief Create a trace message, parameters C (classic c-string) and V (variadic argument list)
IPLCOMMON_EXPORT void IPL_TRACE_LVL_CV_single(int16_t level, ::tracing::Channel *out_ch, const char *msg, ... ) IPL_NOEXCEPT IPL_PRINTF_LIKE_FUNCTION(3,4);

//! \brief Create a trace message, parameters C (classic c-string) and V (variadic argument list) and T (custom timestamp in nanoseconds)
IPLCOMMON_EXPORT void IPL_TRACE_LVL_CVT_single(int16_t level, ::tracing::Channel *out_ch, int64_t timestamp_ns, const char *msg, ... ) IPL_NOEXCEPT IPL_PRINTF_LIKE_FUNCTION(4,5);

//! \brief Create a trace message, parameters C (classic c-string) and V (variadic argument list) and M (modifiers like SAFE_TRANSPORT)
IPLCOMMON_EXPORT void IPL_TRACE_LVL_CVM_single(int16_t level, ::tracing::Channel *out_ch, int16_t mod, const char *msg, ... ) IPL_NOEXCEPT IPL_PRINTF_LIKE_FUNCTION(4,5);

//! \brief Create a trace message, parameters C (classic c-string) and V (variadic argument list) and M (modifiers like OBFUSCATE) and T (custom timestamp in nanoseconds)
IPLCOMMON_EXPORT void IPL_TRACE_LVL_CVMT_single(int16_t level, ::tracing::Channel *out_ch, int16_t mod, int64_t timestamp_ns, const char *msg, ... ) IPL_NOEXCEPT IPL_PRINTF_LIKE_FUNCTION(5,6);;

//! \brief Create a trace message, parameters C (classic c-string) and V (variadic argument list) and N (size)
IPLCOMMON_EXPORT void IPL_TRACE_LVL_CVN_single(int16_t level, ::tracing::Channel *out_ch, size_t size, const char *msg, ... ) IPL_NOEXCEPT IPL_PRINTF_LIKE_FUNCTION(4,5);

//! \brief Create a trace message, parameters C (classic c-string) and V (variadic argument list) and M (modifiers like SAFE_TRANSPORT) and N (size)
IPLCOMMON_EXPORT void IPL_TRACE_LVL_CVMN_single(int16_t level, ::tracing::Channel *out_ch, int16_t mod, size_t size, const char *msg, ... ) IPL_NOEXCEPT IPL_PRINTF_LIKE_FUNCTION(5,6);

//! \brief Create a trace message, parameters C (classic c-string) and V (variadic argument list) and M (modifiers like OBFUSCATE) and N (size) and T (custom timestamp in nanoseconds)
IPLCOMMON_EXPORT void IPL_TRACE_LVL_CVMNT_single(int16_t level, ::tracing::Channel *out_ch, int16_t mod, int64_t timestamp_ns, size_t size, const char *msg, ... ) IPL_NOEXCEPT IPL_PRINTF_LIKE_FUNCTION(6,7);

//! \brief Create a trace message, parameters C (classic c-string)
IPLCOMMON_EXPORT void IPL_TRACE_LVL_C_single(int16_t level, ::tracing::Channel *out_ch, const char *msg) IPL_NOEXCEPT;

//! \brief Create a trace message, parameters C (classic c-string) and M (modifiers like SAFE_TRANSPORT)
IPLCOMMON_EXPORT void IPL_TRACE_LVL_CM_single(int16_t level, ::tracing::Channel *out_ch, int16_t mod, const char *msg) IPL_NOEXCEPT;

//! \brief Create a trace message from raw data
IPLCOMMON_EXPORT void IPL_TRACE_LVL_RAW_single(int16_t level, ::tracing::Channel *out_ch, int16_t type_, const void *msg, size_t len) IPL_NOEXCEPT;

//! \brief Create a trace message from raw data, V (variadic argument list)
IPLCOMMON_EXPORT void IPL_TRACE_LVL_RAW_V_single(int16_t level, ::tracing::Channel *out_ch, int32_t type_, ... ) IPL_NOEXCEPT;

//! \brief Generic trace with variable message arguments and with Message Attributes (Tags or/and Nodes).
template<typename... Args> IPLCOMMON_EXPORT void IPL_TRACE_LVL_CVA_single(int16_t level, ::tracing::Channel *out_ch, Args... args) IPL_NOEXCEPT
{
    ::tracing::Channel *__tracing__scope = out_ch;
    /* COPY OF MACRO: ---------------------------- */
    if (__tracing__scope->getFilterLevel() <= level) {
        tracing_helper_logCVA(__tracing__scope, level, std::forward<Args>(args)...);
    }
    /* ------------------------------------------- */
}

//! \brief Generic trace with variable message arguments and PrivacyFlags.
template<typename... Args> IPLCOMMON_EXPORT void IPL_TRACE_LVL_CVP_single(int16_t level, ::tracing::Channel *out_ch, uint32_t priv_flag, Args... args) IPL_NOEXCEPT
{
    ::tracing::Channel *__tracing__scope = out_ch;
    /* COPY OF MACRO: ---------------------------- */
    if (__tracing__scope->getFilterLevel() <= level) {
        tracing_helper_logCVA(__tracing__scope, level, tracing::LogTagTLRPrivacyFlag(priv_flag), std::forward<Args>(args)...);
    }
    /* ------------------------------------------- */
}

//! \brief Generic trace with message and PrivacyFlags.
template<typename... Args> IPLCOMMON_EXPORT void IPL_TRACE_LVL_CP_single(int16_t level, ::tracing::Channel *out_ch, uint32_t priv_flag, const char *msg) IPL_NOEXCEPT
{
    ::tracing::Channel *__tracing__scope = out_ch;
    /* COPY OF MACRO: ---------------------------- */
    if (__tracing__scope->getFilterLevel() <= level) {
        tracing_helper_logCA(__tracing__scope, level, tracing::LogTagTLRPrivacyFlag(priv_flag), msg);
    }
    /* ------------------------------------------- */
}

//! \brief Generic trace with message string and with Message Attributes (Tags or/and Nodes).
template<typename... Args> IPLCOMMON_EXPORT void IPL_TRACE_LVL_CA_single(int16_t level, ::tracing::Channel *out_ch, Args... args) IPL_NOEXCEPT
{
    ::tracing::Channel *__tracing__scope = out_ch;
    /* COPY OF MACRO: ---------------------------- */
    if (__tracing__scope->getFilterLevel() <= level) {
        tracing_helper_logCA(__tracing__scope, level, std::forward<Args>(args)...);
    }
    /* ------------------------------------------- */
}

//! \brief Create a trace message (don't call directly, use IPL_TRACE_INFO etc. instead)
template<typename T> IPLCOMMON_EXPORT void IPL_TRACE_LVL_single(int16_t level, ::tracing::Channel *out_ch, T msg) IPL_NOEXCEPT
{
    ::tracing::Channel *__tracing__scope = out_ch;
    /* COPY OF MACRO: ---------------------------- */
    if (__tracing__scope->getFilterLevel() <= level)
    {
        ::ipl::ostringstream __tracing__out;
        __tracing__out << msg;
        __tracing__scope->log(level, __tracing__out.str());
    }
    /* ------------------------------------------- */
}

//! \brief Create a trace message with modifiers
//!        (don't call directly, use IPL_TRACE_INFO_M etc. instead)
template<typename T> IPLCOMMON_EXPORT void IPL_TRACE_LVL_M_single(int16_t level, ::tracing::Channel *out_ch, int16_t mod, T msg) IPL_NOEXCEPT
{
    ::tracing::Channel *__tracing__scope = out_ch;
    /* COPY OF MACRO: ---------------------------- */
    if (__tracing__scope->getFilterLevel() <= level)
    {
        ::ipl::ostringstream __tracing__out;
        __tracing__out << msg;
        __tracing__scope->log(level, mod, __tracing__out.str());
    }
    /* ------------------------------------------- */
}

}

#define IPL_TRACE_LVL_CV(level, msg, ... ) ::tracing::IPL_TRACE_LVL_CV_single((level), __tracing__scope, (msg), __VA_ARGS__)

#define IPL_TRACE_LVL_CVT(level, ts, msg, ... ) ::tracing::IPL_TRACE_LVL_CVT_single((level), __tracing__scope, (ts), (msg), __VA_ARGS__)

#define IPL_TRACE_LVL_CVM(level, mod, msg, ... ) ::tracing::IPL_TRACE_LVL_CVM_single((level), __tracing__scope, (mod), (msg), __VA_ARGS__)

#define IPL_TRACE_LVL_CVMT(level, mod, ts, msg, ... ) ::tracing::IPL_TRACE_LVL_CVMT_single((level), __tracing__scope, (mod), (ts), (msg), __VA_ARGS__)

#define IPL_TRACE_LVL_CVN(level, size, msg, ... ) ::tracing::IPL_TRACE_LVL_CVN_single((level), __tracing__scope, (size), (msg), __VA_ARGS__)

#define IPL_TRACE_LVL_CVMN(level, mod, size, msg, ... ) ::tracing::IPL_TRACE_LVL_CVMN_single((level), __tracing__scope, (mod), (size), (msg), __VA_ARGS__)

#define IPL_TRACE_LVL_CVMNT(level, mod, ts, size, msg, ... ) ::tracing::IPL_TRACE_LVL_CVMNT_single((level), __tracing__scope, (mod), (ts), (size), (msg), __VA_ARGS__)

#define IPL_TRACE_LVL_C(level, msg) ::tracing::IPL_TRACE_LVL_C_single((level), __tracing__scope, (msg))

#define IPL_TRACE_LVL_CM(level, mod, msg) ::tracing::IPL_TRACE_LVL_CM_single((level), __tracing__scope, (mod), (msg))

#define IPL_TRACE_LVL_RAW(level, type_, msg, len) ::tracing::IPL_TRACE_LVL_RAW_single((level), __tracing__scope, (type_), (msg), (len))

#define IPL_TRACE_LVL_RAW_V(level, type_, ... ) ::tracing::IPL_TRACE_LVL_RAW_V_single((level), __tracing__scope, (type_), __VA_ARGS__)

#define IPL_TRACE_LVL_CVA(level, ...) ::tracing::IPL_TRACE_LVL_CVA_single((level), __tracing__scope, __VA_ARGS__)

#define IPL_TRACE_LVL_CVP(level, priv_flag, ...) ::tracing::IPL_TRACE_LVL_CVP_single((level), __tracing__scope, (priv_flag), __VA_ARGS__)

#define IPL_TRACE_LVL_CP(level, priv_flag, msg) ::tracing::IPL_TRACE_LVL_CP_single((level), __tracing__scope, (priv_flag), (msg))

#define IPL_TRACE_LVL_CA(level, ...) ::tracing::IPL_TRACE_LVL_CA_single((level), __tracing__scope, __VA_ARGS__)

#define IPL_TRACE_LVL(level, msg) ::tracing::IPL_TRACE_LVL_single((level), __tracing__scope, (msg))

#define IPL_TRACE_LVL_M(level, mod, msg) ::tracing::IPL_TRACE_LVL_M_single((level), __tracing__scope, (mod), (msg))

#endif  //  COMMON_TRACING_BY_FUNCTIONS


//! \brief Create an emergency log entry (consisting of a single string only).
#define IPL_EMERGENCY_LOG(msg)    ::tracing::client_helper->getClient()->emergencyLog(msg)

//! \brief Issue an emergency break, \sa Frontend::emergencyBreak().
#define IPL_EMERGENCY_BREAK() ::tracing::client_helper->getClient()->emergencyBreak()

//! \brief Triggers trace core to flush all pending messages.
#define IPL_TRACE_FLUSH() ::tracing::client_helper->getClient()->flushMessages(true)
#define IPL_TRACE_FLUSH_TIMEOUT(timeout_ms) ::tracing::client_helper->getClient()->flushMessages(true, (timeout_ms))

//! \brief Creates a trace callback dispatcher.
#define IPL_TRACE_DECLARE_CALLBACK(type_name) \
    namespace \
    { \
        ::tracing::CallbackDispatcher<type_name> callback_dispatcher; \
    }

//! \brief Register a function as callback.
#define IPL_TRACE_REGISTER_CALLBACK_FUNCTION(callback_name, function_name) \
    ::tracing::client_helper->getClient() ? ::tracing::client_helper->getClient()->registerCallback((callback_name), (function_name)) : -1

//! \brief Register a callback object.
#define IPL_TRACE_REGISTER_CALLBACK_OBJECT(callback_name, object_addr) \
    ::tracing::client_helper->getClient() ? ::tracing::client_helper->getClient()->registerCallback((callback_name), (object_addr)) : -1

//! \brief Register a callback with class instance and member function pointer.
#define IPL_TRACE_REGISTER_CALLBACK(callback_name, object_addr, method_addr) \
    callback_dispatcher.registerCallback((callback_name), (object_addr), (method_addr))

//! \brief Unregister a function as callback.
#define IPL_TRACE_UNREGISTER_CALLBACK_FUNCTION(id) \
    ::tracing::client_helper->getClient() ? ::tracing::client_helper->getClient()->unregisterCallback(id) : true

//! \brief Unregister a callback object.
#define IPL_TRACE_UNREGISTER_CALLBACK_OBJECT(id) \
    ::tracing::client_helper->getClient() ? ::tracing::client_helper->getClient()->unregisterCallback(id) : true

//! \brief Unregister a callback with class instance and member function pointer.
#define IPL_TRACE_UNREGISTER_CALLBACK(callback_name, object_addr) \
    callback_dispatcher.unregisterCallback((callback_name), (object_addr))


/* C-Style Trace Macros */

#ifndef COMMON_TRACING_BY_FUNCTIONS

//! \brief Generic variadic printf style trace macro.
#define IPL_TRACE_LVL_CV(level, msg, ...) \
    do { \
        if (__tracing__scope->getFilterLevel() <= (level)) \
        { \
            __tracing__scope->logCV((level), (msg), __VA_ARGS__); \
        }\
    } while (false)

//! \brief Generic variadic printf style trace macro with custom timestamp in nanoseconds.
#define IPL_TRACE_LVL_CVT(level, timestamp_ns, msg, ...) \
    do { \
        if (__tracing__scope->getFilterLevel() <= (level)) \
        { \
            __tracing__scope->logCV((level), ::tracing::Modifiers::NONE, (timestamp_ns), (msg), __VA_ARGS__); \
        }\
    } while (false)

//! \brief Generic variadic printf style trace macro with message modifier.
#define IPL_TRACE_LVL_CVM(level, mod, msg, ...) \
    do { \
        if (__tracing__scope->getFilterLevel() <= (level)) \
        { \
            __tracing__scope->logCV((level), (mod), (msg), __VA_ARGS__); \
        }\
    } while (false)

//! \brief Generic variadic printf style trace macro with message modifier and custom timestamp in nanoseconds.
#define IPL_TRACE_LVL_CVMT(level, mod, timestamp_ns, msg, ...) \
    do { \
        if (__tracing__scope->getFilterLevel() <= (level)) \
        { \
            __tracing__scope->logCV((level), (mod), (timestamp_ns), (msg), __VA_ARGS__); \
        }\
    } while (false)

//! \brief Generic variadic printf style trace macro with size parameter.
#define IPL_TRACE_LVL_CVN(level, size, msg, ...) \
    do { \
        if (__tracing__scope->getFilterLevel() <= (level)) \
        { \
            __tracing__scope->logCVN((level), (size), (msg), __VA_ARGS__); \
        }\
    } while (false)

//! \brief Generic variadic printf style trace macro with message modifier and size parameter.
#define IPL_TRACE_LVL_CVMN(level, mod, size, msg, ...) \
    do { \
        if (__tracing__scope->getFilterLevel() <= (level)) \
        { \
            __tracing__scope->logCVN((level), (mod), (size), (msg), __VA_ARGS__); \
        }\
    } while (false)

//! \brief Generic variadic printf style trace macro with message modifier and size parameter and custom timestamp in nanoseconds.
#define IPL_TRACE_LVL_CVMNT(level, mod, timestamp_ns, size, msg, ...) \
    do { \
        if (__tracing__scope->getFilterLevel() <= (level)) \
        { \
            __tracing__scope->logCVN((level), (mod), (timestamp_ns), (size), (msg), __VA_ARGS__); \
        }\
    } while (false)
#endif  //  COMMON_TRACING_BY_FUNCTIONS

//! \brief Create a trace message with level "Trace"
#define IPL_TRACE_TRACE_CV(msg,...)        IPL_TRACE_LVL_CV(::tracing::Levels::LevelTRACE, (msg), __VA_ARGS__)

//! \brief Create a trace message with level "Debug"
#define IPL_TRACE_DEBUG_CV(msg,...)        IPL_TRACE_LVL_CV(::tracing::Levels::LevelDEBUG, (msg), __VA_ARGS__)

//! \brief Create a trace message with level "Info"
#define IPL_TRACE_INFO_CV(msg,...)        IPL_TRACE_LVL_CV(::tracing::Levels::LevelINFO, (msg), __VA_ARGS__)

//! \brief Create a trace message with level "Warning"
#define IPL_TRACE_WARN_CV(msg,...)        IPL_TRACE_LVL_CV(::tracing::Levels::LevelWARN, (msg), __VA_ARGS__)

//! \brief Create a trace message with level "Error"
#define IPL_TRACE_ERR_CV(msg,...)        IPL_TRACE_LVL_CV(::tracing::Levels::LevelERROR, (msg), __VA_ARGS__)

//! \brief Create a trace message with level "Fatal"
#define IPL_TRACE_FATAL_CV(msg,...)        IPL_TRACE_LVL_CV(::tracing::Levels::LevelFATAL, (msg), __VA_ARGS__)

//! \brief Create a trace message with level "Trace" and custom timestamp in nanoseconds
#define IPL_TRACE_TRACE_CVT(timestamp_ns, msg,...)        IPL_TRACE_LVL_CVT(::tracing::Levels::LevelTRACE, (timestamp_ns), (msg), __VA_ARGS__)

//! \brief Create a trace message with level "Debug" and custom timestamp in nanoseconds
#define IPL_TRACE_DEBUG_CVT(timestamp_ns, msg,...)        IPL_TRACE_LVL_CVT(::tracing::Levels::LevelDEBUG, (timestamp_ns), (msg), __VA_ARGS__)

//! \brief Create a trace message with level "Info" and custom timestamp in nanoseconds
#define IPL_TRACE_INFO_CVT(timestamp_ns, msg,...)        IPL_TRACE_LVL_CVT(::tracing::Levels::LevelINFO, (timestamp_ns), (msg), __VA_ARGS__)

//! \brief Create a trace message with level "Warning" and custom timestamp in nanoseconds
#define IPL_TRACE_WARN_CVT(timestamp_ns, msg,...)        IPL_TRACE_LVL_CVT(::tracing::Levels::LevelWARN, (timestamp_ns), (msg), __VA_ARGS__)

//! \brief Create a trace message with level "Error" and custom timestamp in nanoseconds
#define IPL_TRACE_ERR_CVT(timestamp_ns, msg,...)        IPL_TRACE_LVL_CVT(::tracing::Levels::LevelERROR, (timestamp_ns), (msg), __VA_ARGS__)

//! \brief Create a trace message with level "Fatal" and custom timestamp in nanoseconds
#define IPL_TRACE_FATAL_CVT(timestamp_ns, msg,...)        IPL_TRACE_LVL_CVT(::tracing::Levels::LevelFATAL, (timestamp_ns), (msg), __VA_ARGS__)

//! \brief Create a trace message with level "Trace"
#define IPL_TRACE_TRACE_CVN(size, msg, ...)        IPL_TRACE_LVL_CVN(::tracing::Levels::LevelTRACE, (size), (msg), __VA_ARGS__)

//! \brief Create a trace message with level "Debug"
#define IPL_TRACE_DEBUG_CVN(size, msg, ...)        IPL_TRACE_LVL_CVN(::tracing::Levels::LevelDEBUG, (size), (msg), __VA_ARGS__)

//! \brief Create a trace message with level "Info"
#define IPL_TRACE_INFO_CVN(size, msg, ...)        IPL_TRACE_LVL_CVN(::tracing::Levels::LevelINFO, (size), (msg), __VA_ARGS__)

//! \brief Create a trace message with level "Warning"
#define IPL_TRACE_WARN_CVN(size, msg, ...)        IPL_TRACE_LVL_CVN(::tracing::Levels::LevelWARN, (size), (msg), __VA_ARGS__)

//! \brief Create a trace message with level "Error"
#define IPL_TRACE_ERR_CVN(size, msg, ...)        IPL_TRACE_LVL_CVN(::tracing::Levels::LevelERROR, (size), (msg), __VA_ARGS__)

//! \brief Create a trace message with level "Fatal"
#define IPL_TRACE_FATAL_CVN(size, msg, ...)        IPL_TRACE_LVL_CVN(::tracing::Levels::LevelFATAL, (size), (msg), __VA_ARGS__)

//! \brief Create a trace message with level "Trace"
#define IPL_TRACE_TRACE_CVM(mod,msg,...)    IPL_TRACE_LVL_CVM(::tracing::Levels::LevelTRACE, (mod), (msg), __VA_ARGS__)

//! \brief Create a trace message with level "Debug"
#define IPL_TRACE_DEBUG_CVM(mod,msg,...)    IPL_TRACE_LVL_CVM(::tracing::Levels::LevelDEBUG, (mod), (msg), __VA_ARGS__)

//! \brief Create a trace message with level "Info"
#define IPL_TRACE_INFO_CVM(mod,msg,...)        IPL_TRACE_LVL_CVM(::tracing::Levels::LevelINFO, (mod), (msg), __VA_ARGS__)

//! \brief Create a trace message with level "Warning"
#define IPL_TRACE_WARN_CVM(mod,msg,...)        IPL_TRACE_LVL_CVM(::tracing::Levels::LevelWARN, (mod), (msg), __VA_ARGS__)

//! \brief Create a trace message with level "Error"
#define IPL_TRACE_ERR_CVM(mod,msg,...)        IPL_TRACE_LVL_CVM(::tracing::Levels::LevelERROR, (mod), (msg), __VA_ARGS__)

//! \brief Create a trace message with level "Fatal"
#define IPL_TRACE_FATAL_CVM(mod,msg,...)    IPL_TRACE_LVL_CVM(::tracing::Levels::LevelFATAL, (mod), (msg), __VA_ARGS__)

//! \brief Create a trace message with level "Trace" and custom timestamp in nanoseconds
#define IPL_TRACE_TRACE_CVMT(mod, timestamp_ns, msg,...)    IPL_TRACE_LVL_CVMT(::tracing::Levels::LevelTRACE, (mod), (timestamp_ns), (msg), __VA_ARGS__)

//! \brief Create a trace message with level "Debug" and custom timestamp in nanoseconds
#define IPL_TRACE_DEBUG_CVMT(mod, timestamp_ns, msg,...)    IPL_TRACE_LVL_CVMT(::tracing::Levels::LevelDEBUG, (mod), (timestamp_ns), (msg), __VA_ARGS__)

//! \brief Create a trace message with level "Info" and custom timestamp in nanoseconds
#define IPL_TRACE_INFO_CVMT(mod, timestamp_ns, msg,...)        IPL_TRACE_LVL_CVMT(::tracing::Levels::LevelINFO, (mod), (timestamp_ns), (msg), __VA_ARGS__)

//! \brief Create a trace message with level "Warning" and custom timestamp in nanoseconds
#define IPL_TRACE_WARN_CVMT(mod, timestamp_ns, msg,...)        IPL_TRACE_LVL_CVMT(::tracing::Levels::LevelWARN, (mod), (timestamp_ns), (msg), __VA_ARGS__)

//! \brief Create a trace message with level "Error" and custom timestamp in nanoseconds
#define IPL_TRACE_ERR_CVMT(mod, timestamp_ns, msg,...)        IPL_TRACE_LVL_CVMT(::tracing::Levels::LevelERROR, (mod), (timestamp_ns), (msg), __VA_ARGS__)

//! \brief Create a trace message with level "Fatal" and custom timestamp in nanoseconds
#define IPL_TRACE_FATAL_CVMT(mod, timestamp_ns, msg,...)    IPL_TRACE_LVL_CVMT(::tracing::Levels::LevelFATAL, (mod), (timestamp_ns), (msg), __VA_ARGS__)

//! \brief Create a trace message with level "Trace"
#define IPL_TRACE_TRACE_CVMN(mod, size, msg, ...)    IPL_TRACE_LVL_CVMN(::tracing::Levels::LevelTRACE, (mod), (size), (msg), __VA_ARGS__)

//! \brief Create a trace message with level "Debug"
#define IPL_TRACE_DEBUG_CVMN(mod, size, msg, ...)    IPL_TRACE_LVL_CVMN(::tracing::Levels::LevelDEBUG, (mod), (size), (msg), __VA_ARGS__)

//! \brief Create a trace message with level "Info"
#define IPL_TRACE_INFO_CVMN(mod, size, msg, ...)    IPL_TRACE_LVL_CVMN(::tracing::Levels::LevelINFO, (mod), (size), (msg), __VA_ARGS__)

//! \brief Create a trace message with level "Warning"
#define IPL_TRACE_WARN_CVMN(mod, size, msg, ...)    IPL_TRACE_LVL_CVMN(::tracing::Levels::LevelWARN, (mod), (size), (msg), __VA_ARGS__)

//! \brief Create a trace message with level "Error"
#define IPL_TRACE_ERR_CVMN(mod, size, msg, ...)    IPL_TRACE_LVL_CVMN(::tracing::Levels::LevelERROR, (mod), (size), (msg), __VA_ARGS__)

//! \brief Create a trace message with level "Fatal"
#define IPL_TRACE_FATAL_CVMN(mod, size, msg, ...)    IPL_TRACE_LVL_CVMN(::tracing::Levels::LevelFATAL, (mod), (size), (msg), __VA_ARGS__)

//! \brief Create a trace message with level "Trace" and custom timestamp in nanoseconds
#define IPL_TRACE_TRACE_CVMNT(mod, timestamp_ns, size, msg, ...)    IPL_TRACE_LVL_CVMNT(::tracing::Levels::LevelTRACE, (mod), (timestamp_ns), (size), (msg), __VA_ARGS__)

//! \brief Create a trace message with level "Debug" and custom timestamp in nanoseconds
#define IPL_TRACE_DEBUG_CVMNT(mod, timestamp_ns, size, msg, ...)    IPL_TRACE_LVL_CVMNT(::tracing::Levels::LevelDEBUG, (mod), (timestamp_ns), (size), (msg), __VA_ARGS__)

//! \brief Create a trace message with level "Info" and custom timestamp in nanoseconds
#define IPL_TRACE_INFO_CVMNT(mod, timestamp_ns, size, msg, ...)    IPL_TRACE_LVL_CVMNT(::tracing::Levels::LevelINFO, (mod), (timestamp_ns), (size), (msg), __VA_ARGS__)

//! \brief Create a trace message with level "Warning" and custom timestamp in nanoseconds
#define IPL_TRACE_WARN_CVMNT(mod, timestamp_ns, size, msg, ...)    IPL_TRACE_LVL_CVMNT(::tracing::Levels::LevelWARN, (mod), (timestamp_ns), (size), (msg), __VA_ARGS__)

//! \brief Create a trace message with level "Error" and custom timestamp in nanoseconds
#define IPL_TRACE_ERR_CVMNT(mod, timestamp_ns, size, msg, ...)    IPL_TRACE_LVL_CVMNT(::tracing::Levels::LevelERROR, (mod), (timestamp_ns), (size), (msg), __VA_ARGS__)

//! \brief Create a trace message with level "Fatal" and custom timestamp in nanoseconds
#define IPL_TRACE_FATAL_CVMNT(mod, timestamp_ns, size, msg, ...)    IPL_TRACE_LVL_CVMNT(::tracing::Levels::LevelFATAL, (mod), (timestamp_ns), (size), (msg), __VA_ARGS__)

#ifndef COMMON_TRACING_BY_FUNCTIONS

//! \brief Generic constant string trace.
#define IPL_TRACE_LVL_C(level, msg) \
    do { \
        if (__tracing__scope->getFilterLevel() <= (level)) \
        { \
            __tracing__scope->logC((level), (msg)); \
        }\
    } while (false)

//! \brief Generic constant string trace with message modifier.
#define IPL_TRACE_LVL_CM(level, mod, msg) \
    do { \
        if (__tracing__scope->getFilterLevel() <= (level)) \
        { \
            __tracing__scope->logC((level), (mod), (msg)); \
        }\
    } while (false)

//! \brief Generic trace with variable message arguments and with Message Attributes (Tags or/and Nodes).
#define IPL_TRACE_LVL_CVA(level, ...) \
    do { \
        if (__tracing__scope->getFilterLevel() <= (level)) { \
            ::tracing::tracing_helper_logCVA(__tracing__scope, (level), __VA_ARGS__); \
        } \
    } while (false)

//! \brief Generic trace with variable message arguments and PrivacyFlags.
#define IPL_TRACE_LVL_CVP(level, priv_flag, ...) \
    do { \
        if (__tracing__scope->getFilterLevel() <= (level)) { \
            ::tracing::tracing_helper_logCVA(__tracing__scope, (level), tracing::LogTagTLRPrivacyFlag(priv_flag), __VA_ARGS__); \
        } \
    } while (false)

//! \brief Generic trace with message and PrivacyFlags.
#define IPL_TRACE_LVL_CP(level, priv_flag, msg) \
    do { \
        if (__tracing__scope->getFilterLevel() <= (level)) { \
            ::tracing::tracing_helper_logCA(__tracing__scope, (level), tracing::LogTagTLRPrivacyFlag(priv_flag), (msg)); \
        } \
    } while (false)

//! \brief Generic trace with message string and with Message Attributes (Tags or/and Nodes).
#define IPL_TRACE_LVL_CA(level, ...) \
    do { \
        if (__tracing__scope->getFilterLevel() <= (level)) { \
            ::tracing::tracing_helper_logCA(__tracing__scope, (level), __VA_ARGS__); \
        } \
    } while (false)

#endif  //  COMMON_TRACING_BY_FUNCTIONS

#define IPL_TRACE_TRACE_CVA(msg, ...)        IPL_TRACE_LVL_CVA(::tracing::Levels::LevelTRACE, msg, __VA_ARGS__)
#define IPL_TRACE_DEBUG_CVA(msg, ...)        IPL_TRACE_LVL_CVA(::tracing::Levels::LevelDEBUG, msg, __VA_ARGS__)
#define IPL_TRACE_INFO_CVA(msg, ...)         IPL_TRACE_LVL_CVA(::tracing::Levels::LevelINFO, msg, __VA_ARGS__)
#define IPL_TRACE_WARN_CVA(msg, ...)         IPL_TRACE_LVL_CVA(::tracing::Levels::LevelWARN, msg, __VA_ARGS__)
#define IPL_TRACE_ERR_CVA(msg, ...)          IPL_TRACE_LVL_CVA(::tracing::Levels::LevelERROR, msg, __VA_ARGS__)
#define IPL_TRACE_FATAL_CVA(msg, ...)        IPL_TRACE_LVL_CVA(::tracing::Levels::LevelFATAL, msg, __VA_ARGS__)

#define IPL_TRACE_TRACE_CVP(priv_flag, msg, ...)        IPL_TRACE_LVL_CVP(::tracing::Levels::LevelTRACE, (priv_flag), msg, __VA_ARGS__)
#define IPL_TRACE_DEBUG_CVP(priv_flag, msg, ...)        IPL_TRACE_LVL_CVP(::tracing::Levels::LevelDEBUG, (priv_flag), msg, __VA_ARGS__)
#define IPL_TRACE_INFO_CVP(priv_flag, msg, ...)         IPL_TRACE_LVL_CVP(::tracing::Levels::LevelINFO, (priv_flag), msg, __VA_ARGS__)
#define IPL_TRACE_WARN_CVP(priv_flag, msg, ...)         IPL_TRACE_LVL_CVP(::tracing::Levels::LevelWARN, (priv_flag), msg, __VA_ARGS__)
#define IPL_TRACE_ERR_CVP(priv_flag, msg, ...)          IPL_TRACE_LVL_CVP(::tracing::Levels::LevelERROR, (priv_flag), msg, __VA_ARGS__)
#define IPL_TRACE_FATAL_CVP(priv_flag, msg, ...)        IPL_TRACE_LVL_CVP(::tracing::Levels::LevelFATAL, (priv_flag), msg, __VA_ARGS__)

#define IPL_TRACE_TRACE_CA(...)        IPL_TRACE_LVL_CA(::tracing::Levels::LevelTRACE,  __VA_ARGS__)
#define IPL_TRACE_DEBUG_CA(...)        IPL_TRACE_LVL_CA(::tracing::Levels::LevelDEBUG,  __VA_ARGS__)
#define IPL_TRACE_INFO_CA(...)         IPL_TRACE_LVL_CA(::tracing::Levels::LevelINFO,  __VA_ARGS__)
#define IPL_TRACE_WARN_CA(...)         IPL_TRACE_LVL_CA(::tracing::Levels::LevelWARN,  __VA_ARGS__)
#define IPL_TRACE_ERR_CA(...)          IPL_TRACE_LVL_CA(::tracing::Levels::LevelERROR,  __VA_ARGS__)
#define IPL_TRACE_FATAL_CA(...)        IPL_TRACE_LVL_CA(::tracing::Levels::LevelFATAL,  __VA_ARGS__)

#define IPL_TRACE_TRACE_CP(priv_flag, msg)        IPL_TRACE_LVL_CP(::tracing::Levels::LevelTRACE, (priv_flag), (msg))
#define IPL_TRACE_DEBUG_CP(priv_flag, msg)        IPL_TRACE_LVL_CP(::tracing::Levels::LevelDEBUG, (priv_flag), (msg))
#define IPL_TRACE_INFO_CP(priv_flag, msg)         IPL_TRACE_LVL_CP(::tracing::Levels::LevelINFO, (priv_flag), (msg))
#define IPL_TRACE_WARN_CP(priv_flag, msg)         IPL_TRACE_LVL_CP(::tracing::Levels::LevelWARN, (priv_flag), (msg))
#define IPL_TRACE_ERR_CP(priv_flag, msg)          IPL_TRACE_LVL_CP(::tracing::Levels::LevelERROR, (priv_flag), (msg))
#define IPL_TRACE_FATAL_CP(priv_flag, msg)        IPL_TRACE_LVL_CP(::tracing::Levels::LevelFATAL, (priv_flag), (msg))



//! \brief Create a trace message with level "Trace"
#define IPL_TRACE_TRACE_C(msg)        IPL_TRACE_LVL_C(::tracing::Levels::LevelTRACE, (msg))

//! \brief Create a trace message with level "Debug"
#define IPL_TRACE_DEBUG_C(msg)        IPL_TRACE_LVL_C(::tracing::Levels::LevelDEBUG, (msg))

//! \brief Create a trace message with level "Info"
#define IPL_TRACE_INFO_C(msg)        IPL_TRACE_LVL_C(::tracing::Levels::LevelINFO, (msg))

//! \brief Create a trace message with level "Warning"
#define IPL_TRACE_WARN_C(msg)        IPL_TRACE_LVL_C(::tracing::Levels::LevelWARN, (msg))

//! \brief Create a trace message with level "Error"
#define IPL_TRACE_ERR_C(msg)        IPL_TRACE_LVL_C(::tracing::Levels::LevelERROR, (msg))

//! \brief Create a trace message with level "Fatal"
#define IPL_TRACE_FATAL_C(msg)        IPL_TRACE_LVL_C(::tracing::Levels::LevelFATAL, (msg))

//! \brief Create a trace message with level "Trace"
#define IPL_TRACE_TRACE_CM(mod,msg)        IPL_TRACE_LVL_CM(::tracing::Levels::LevelTRACE, (mod), (msg))

//! \brief Create a trace message with level "Debug"
#define IPL_TRACE_DEBUG_CM(mod,msg)        IPL_TRACE_LVL_CM(::tracing::Levels::LevelDEBUG, (mod), (msg))

//! \brief Create a trace message with level "Info"
#define IPL_TRACE_INFO_CM(mod,msg)        IPL_TRACE_LVL_CM(::tracing::Levels::LevelINFO, (mod), (msg))

//! \brief Create a trace message with level "Warning"
#define IPL_TRACE_WARN_CM(mod,msg)        IPL_TRACE_LVL_CM(::tracing::Levels::LevelWARN, (mod), (msg))

//! \brief Create a trace message with level "Error"
#define IPL_TRACE_ERR_CM(mod,msg)        IPL_TRACE_LVL_CM(::tracing::Levels::LevelERROR, (mod), (msg))

//! \brief Create a trace message with level "Fatal"
#define IPL_TRACE_FATAL_CM(mod,msg)        IPL_TRACE_LVL_CM(::tracing::Levels::LevelFATAL, (mod), (msg))


#ifndef COMMON_TRACING_BY_FUNCTIONS

//! \brief Generic raw data trace.
#define IPL_TRACE_LVL_RAW(level, type, msg, len) \
    do { \
        if (__tracing__scope->getFilterLevel() <= (level)) \
        { \
            __tracing__scope->logRaw((level), (type), (msg), (len)); \
        }\
    } while (false)
#endif  //  COMMON_TRACING_BY_FUNCTIONS

//! \brief Create a trace message with level "Trace"
#define IPL_TRACE_TRACE_RAW(type,msg,len)        IPL_TRACE_LVL_RAW(::tracing::Levels::LevelTRACE, (type),(msg),(len))

//! \brief Create a trace message with level "Debug"
#define IPL_TRACE_DEBUG_RAW(type,msg,len)        IPL_TRACE_LVL_RAW(::tracing::Levels::LevelDEBUG, (type),(msg),(len))

//! \brief Create a trace message with level "Info"
#define IPL_TRACE_INFO_RAW(type,msg,len)        IPL_TRACE_LVL_RAW(::tracing::Levels::LevelINFO, (type),(msg),(len))

//! \brief Create a trace message with level "Warning"
#define IPL_TRACE_WARN_RAW(type,msg,len)        IPL_TRACE_LVL_RAW(::tracing::Levels::LevelWARN, (type),(msg),(len))

//! \brief Create a trace message with level "Error"
#define IPL_TRACE_ERR_RAW(type,msg,len)            IPL_TRACE_LVL_RAW(::tracing::Levels::LevelERROR, (type),(msg),(len))

//! \brief Create a trace message with level "Fatal"
#define IPL_TRACE_FATAL_RAW(type,msg,len)        IPL_TRACE_LVL_RAW(::tracing::Levels::LevelFATAL, (type),(msg),(len))

#ifndef COMMON_TRACING_BY_FUNCTIONS

/*! \brief Generic variadic raw data trace.
 *
 *  Usage (level, type, ptr1, len1, ptr2, len2, ..., ptrN, lenN, NULL)
 */
#define IPL_TRACE_LVL_RAW_V(level, type, ...) \
    do { \
        if (__tracing__scope->getFilterLevel() <= (level)) \
        { \
            __tracing__scope->logRawV((level), tracing::Modifiers::NONE, (type), __VA_ARGS__); \
        }\
    } while (false)
#endif  //  COMMON_TRACING_BY_FUNCTIONS

//! \brief Create a trace message with level "Trace"
#define IPL_TRACE_TRACE_RAW_V(type, ...)        IPL_TRACE_LVL_RAW_V(::tracing::Levels::LevelTRACE, (type), __VA_ARGS__)

//! \brief Create a trace message with level "Debug"
#define IPL_TRACE_DEBUG_RAW_V(type, ...)        IPL_TRACE_LVL_RAW_V(::tracing::Levels::LevelDEBUG, (type), __VA_ARGS__)

//! \brief Create a trace message with level "Info"
#define IPL_TRACE_INFO_RAW_V(type, ...)            IPL_TRACE_LVL_RAW_V(::tracing::Levels::LevelINFO, (type), __VA_ARGS__)

//! \brief Create a trace message with level "Warning"
#define IPL_TRACE_WARN_RAW_V(type, ...)            IPL_TRACE_LVL_RAW_V(::tracing::Levels::LevelWARN, (type), __VA_ARGS__)

//! \brief Create a trace message with level "Error"
#define IPL_TRACE_ERR_RAW_V(type, ...)            IPL_TRACE_LVL_RAW_V(::tracing::Levels::LevelERROR, (type), __VA_ARGS__)

//! \brief Create a trace message with level "Fatal"
#define IPL_TRACE_FATAL_RAW_V(type, ...)        IPL_TRACE_LVL_RAW_V(::tracing::Levels::LevelFATAL, (type), __VA_ARGS__)

//! \brief Conditionally execute statements based on the current channel's filter level.
#define IPL_TRACE_EXECUTE_LVL(level, statements) \
    do { \
        if (__tracing__scope->getFilterLevel() <= (level)) \
        { \
            statements; \
        } \
    } while (false)

//! \brief Executes statement if current channel is set to level "Trace"
#define IPL_TRACE_EXECUTE_TRACE(statements)        IPL_TRACE_EXECUTE_LVL(::tracing::Levels::LevelTRACE, statements);

//! \brief Executes statement if current channel is set to level "Debug"
#define IPL_TRACE_EXECUTE_DEBUG(statements)        IPL_TRACE_EXECUTE_LVL(::tracing::Levels::LevelDEBUG, statements);

//! \brief Executes statement if current channel is set to level "Info"
#define IPL_TRACE_EXECUTE_INFO(statements)        IPL_TRACE_EXECUTE_LVL(::tracing::Levels::LevelINFO, statements);

//! \brief Executes statement if current channel is set to level "Warning"
#define IPL_TRACE_EXECUTE_WARN(statements)        IPL_TRACE_EXECUTE_LVL(::tracing::Levels::LevelWARN, statements);

//! \brief Executes statement if current channel is set to level "Error"
#define IPL_TRACE_EXECUTE_ERR(statements)        IPL_TRACE_EXECUTE_LVL(::tracing::Levels::LevelERROR, statements);

//! \brief Executes statement if current channel is set to level "Fatal"
#define IPL_TRACE_EXECUTE_FATAL(statements)        IPL_TRACE_EXECUTE_LVL(::tracing::Levels::LevelFATAL, statements);

//! \brief Instantiates a trace buffer for given channel
#define IPL_TRACE_BUFFER(channelname) \
    ::tracing::TraceBuffer __trace__buffer( &__tracing__channel_ ## channelname)

//! \brief Assigns tags to the traceBuffer. After assignment, messageTags will be cleared.
#define IPL_TRACE_BUFFER_FORWARD_TAGS(tags) __trace__buffer.forwardTags(tags)

//! \brief Assigns and forwards ownership of object node to the traceBuffer.
#define IPL_TRACE_BUFFER_FORWARD_OBJECT(obj) __trace__buffer.forwardObject(obj)

//! \brief Prints the buffered content
#define IPL_TRACE_BUFFER_PRINT() __trace__buffer.print()

//! \brief Clears the buffered content
#define IPL_TRACE_BUFFER_RESET() __trace__buffer.reset()

//! \brief Set the message text if given level is enabled by the trace channel.
#define IPL_TRACE_BUFFER_SETC(level, message) __trace__buffer.set((level), (message))

//! \brief Set the message text with variable arguments if given level is enabled by the trace channel.
#define IPL_TRACE_BUFFER_SETCV(level, format, ...) \
    __trace__buffer.setf((level), (format), __VA_ARGS__)

//! \brief Appends the message text.
#define IPL_TRACE_BUFFER_C(message) __trace__buffer.append(message)

//! \brief Appends the message text with variable arguments.
#define IPL_TRACE_BUFFER_CV(format, ...) __trace__buffer.appendf((format), __VA_ARGS__)

//! \brief Appends the message text if given level is enabled by the trace channel.
#define IPL_TRACE_BUFFER_LVL_C(level, message) \
    __trace__buffer.append((level), (message))
//! \brief Appends the message text if TRACE level is enabled by the trace channel.
#define IPL_TRACE_BUFFER_TRACE_C(message) \
    __trace__buffer.append(::tracing::Levels::LevelTRACE, (message))
//! \brief Appends the message text if DEBUG level is enabled by the trace channel.
#define IPL_TRACE_BUFFER_DEBUG_C(message) \
    __trace__buffer.append(::tracing::Levels::LevelDEBUG, (message))
//! \brief Appends the message text if INFO level is enabled by the trace channel.
#define IPL_TRACE_BUFFER_INFO_C(message) \
    __trace__buffer.append(::tracing::Levels::LevelINFO, (message))
//! \brief Appends the message text if WARN level is enabled by the trace channel.
#define IPL_TRACE_BUFFER_WARN_C(message) \
    __trace__buffer.append(::tracing::Levels::LevelWARN, (message))
//! \brief Appends the message text if ERROR level is enabled by the trace channel.
#define IPL_TRACE_BUFFER_ERR_C(message) \
    __trace__buffer.append(::tracing::Levels::LevelERROR, (message))
//! \brief Appends the message text if FATAL level is enabled by the trace channel.
#define IPL_TRACE_BUFFER_FATAL_C(message) \
    __trace__buffer.append(::tracing::Levels::LevelFATAL, (message))

//! \brief Appends the message with variable arguments if given level is enabled by the trace channel.
#define IPL_TRACE_BUFFER_LVL_CV(level, format, ...) \
    __trace__buffer.appendf((level), (format), __VA_ARGS__)
//! \brief Appends the message with variable arguments if TRACE level is enabled by the trace channel.
#define IPL_TRACE_BUFFER_TRACE_CV(format, ...) \
    __trace__buffer.appendf(::tracing::Levels::LevelTRACE, (format), __VA_ARGS__)
//! \brief Appends the message with variable arguments if DEBUG level is enabled by the trace channel.
#define IPL_TRACE_BUFFER_DEBUG_CV(format, ...) \
    __trace__buffer.appendf(::tracing::Levels::LevelDEBUG, (format), __VA_ARGS__)
//! \brief Appends the message with variable arguments if INFO level is enabled by the trace channel.
#define IPL_TRACE_BUFFER_INFO_CV(format, ...) \
    __trace__buffer.appendf(::tracing::Levels::LevelINFO, (format), __VA_ARGS__)
//! \brief Appends the message with variable arguments if WARN level is enabled by the trace channel.
#define IPL_TRACE_BUFFER_WARN_CV(format, ...) \
    __trace__buffer.appendf(::tracing::Levels::LevelWARN, (format), __VA_ARGS__)
//! \brief Appends the message with variable arguments if ERROR level is enabled by the trace channel.
#define IPL_TRACE_BUFFER_ERR_CV(format, ...) \
    __trace__buffer.appendf(::tracing::Levels::LevelERROR, (format), __VA_ARGS__)
//! \brief Appends the message with variable arguments if FATAL level is enabled by the trace channel.
#define IPL_TRACE_BUFFER_FATAL_CV(format, ...) \
    __trace__buffer.appendf(::tracing::Levels::LevelFATAL, (format), __VA_ARGS__)

//! \brief Provides the size of the stored message.
#define IPL_TRACE_BUFFER_SIZE() __trace__buffer.size()
//! \brief Informs if the stored message is empty.
#define IPL_TRACE_BUFFER_EMPTY() __trace__buffer.empty()

//! \brief Provides the client "ID", i.e. the name provided to the Util constructor
#define IPL_TRACE_CLIENT_ID() ::tracing::client_helper->getClient()->getClientId()

// libfmt support
#if defined(TRACING_WITH_LIBFMT)

//! \brief Traces a message in libfmt format if given level is enabled by the trace channel.
#define IPL_TRACE_LVL_FMT(level, msg, ...) \
    do { \
        if (__tracing__scope->getFilterLevel() <= (level)) \
        { \
            const auto text = ::fmt::format(FMT_STRING(msg), __VA_ARGS__);  \
            __tracing__scope->log((level), text); \
        } \
    } while (false)

//! \brief Traces a message in libfmt format if TRACE level is enabled by the trace channel.
#define IPL_TRACE_TRACE_FMT(msg, ...) IPL_TRACE_LVL_FMT(::tracing::Levels::LevelTRACE, (msg), __VA_ARGS__)
//! \brief Traces a message in libfmt format if DEBUG level is enabled by the trace channel.
#define IPL_TRACE_DEBUG_FMT(msg, ...) IPL_TRACE_LVL_FMT(::tracing::Levels::LevelDEBUG, (msg), __VA_ARGS__)
//! \brief Traces a message in libfmt format if INFO level is enabled by the trace channel.
#define IPL_TRACE_INFO_FMT(msg, ...)  IPL_TRACE_LVL_FMT(::tracing::Levels::LevelINFO,  (msg), __VA_ARGS__)
//! \brief Traces a message in libfmt format if WARN level is enabled by the trace channel.
#define IPL_TRACE_WARN_FMT(msg, ...)  IPL_TRACE_LVL_FMT(::tracing::Levels::LevelWARN,  (msg), __VA_ARGS__)
//! \brief Traces a message in libfmt format if ERROR level is enabled by the trace channel.
#define IPL_TRACE_ERR_FMT(msg, ...)   IPL_TRACE_LVL_FMT(::tracing::Levels::LevelERROR, (msg), __VA_ARGS__)
//! \brief Traces a message in libfmt format if FATAL level is enabled by the trace channel.
#define IPL_TRACE_FATAL_FMT(msg, ...) IPL_TRACE_LVL_FMT(::tracing::Levels::LevelFATAL, (msg), __VA_ARGS__)


//! \brief Traces a message in libfmt format with level and PrivacyFlags.
#define IPL_TRACE_LVL_FMT_P(level, priv_flag, msg, ...) \
    do { \
        if (__tracing__scope->getFilterLevel() <= (level)) \
        { \
            const std::string text = ::fmt::format(FMT_STRING(msg), __VA_ARGS__);  \
            ::tracing::tracing_helper_logCA(__tracing__scope, (level), tracing::LogTagTLRPrivacyFlag(priv_flag), text.c_str()); \
        } \
    } while (false)

//! \brief Traces a message in libfmt with PrivacyFlags format if TRACE level is enabled.
#define IPL_TRACE_TRACE_FMT_P(priv_flag, msg, ...) IPL_TRACE_LVL_FMT_P(::tracing::Levels::LevelTRACE, (priv_flag), (msg), __VA_ARGS__)
//! \brief Traces a message in libfmt format with PrivacyFlags if DEBUG level is enabled.
#define IPL_TRACE_DEBUG_FMT_P(priv_flag, msg, ...) IPL_TRACE_LVL_FMT_P(::tracing::Levels::LevelDEBUG, (priv_flag), (msg), __VA_ARGS__)
//! \brief Traces a message in libfmt format with PrivacyFlags if INFO level is enabled.
#define IPL_TRACE_INFO_FMT_P(priv_flag, msg, ...)  IPL_TRACE_LVL_FMT_P(::tracing::Levels::LevelINFO,  (priv_flag), (msg), __VA_ARGS__)
//! \brief Traces a message in libfmt format with PrivacyFlags if WARN level is enabled.
#define IPL_TRACE_WARN_FMT_P(priv_flag, msg, ...)  IPL_TRACE_LVL_FMT_P(::tracing::Levels::LevelWARN,  (priv_flag), (msg), __VA_ARGS__)
//! \brief Traces a message in libfmt format with PrivacyFlags if ERROR level is enabled.
#define IPL_TRACE_ERR_FMT_P(priv_flag, msg, ...)   IPL_TRACE_LVL_FMT_P(::tracing::Levels::LevelERROR, (priv_flag), (msg), __VA_ARGS__)
//! \brief Traces a message in libfmt format with PrivacyFlags if FATAL level is enabled.
#define IPL_TRACE_FATAL_FMT_P(priv_flag, msg, ...) IPL_TRACE_LVL_FMT_P(::tracing::Levels::LevelFATAL, (priv_flag), (msg), __VA_ARGS__)

#else /* TRACING_WITH_LIBFMT */

#define IPL_TRACE_LVL_FMT(level, ...) do { /* NOP */ } while (false)
#define IPL_TRACE_TRACE_FMT(...) do { /* NOP */ } while (false)
#define IPL_TRACE_DEBUG_FMT(...) do { /* NOP */ } while (false)
#define IPL_TRACE_INFO_FMT(...)  do { /* NOP */ } while (false)
#define IPL_TRACE_WARN_FMT(...)  do { /* NOP */ } while (false)
#define IPL_TRACE_ERR_FMT(...)   do { /* NOP */ } while (false)
#define IPL_TRACE_FATAL_FMT(...) do { /* NOP */ } while (false)

#define IPL_TRACE_LVL_FMT_P(level, ...) do { /* NOP */ } while (false)
#define IPL_TRACE_TRACE_FMT_P(...) do { /* NOP */ } while (false)
#define IPL_TRACE_DEBUG_FMT_P(...) do { /* NOP */ } while (false)
#define IPL_TRACE_INFO_FMT_P(...)  do { /* NOP */ } while (false)
#define IPL_TRACE_WARN_FMT_P(...)  do { /* NOP */ } while (false)
#define IPL_TRACE_ERR_FMT_P(...)   do { /* NOP */ } while (false)
#define IPL_TRACE_FATAL_FMT_P(...) do { /* NOP */ } while (false)

#endif /* TRACING_WITH_LIBFMT */

#else /* NTRACE */

inline int __tracing__dummy() { return -1; }

#define IPL_TRACE_INIT() do { /* NOP */ } while (false)
#define IPL_TRACE_EXIT() do { /* NOP */ } while (false)
#define IPL_TRACE_INIT_NAME(clientname) do { /* NOP */ } while (false)
#define IPL_TRACE_INIT_NAME_READ_CONFIG(clientname, read_config) do { /* NOP */ } while (false)

#define IPL_TRACE_DECLARE_CHANNEL(channelname) /* empty */
#define IPL_TRACE_DECLARE_CHANNEL_EXTERN(channelname) /* empty */
#define IPL_TRACE_DECLARE_CHANNEL_EXPORT(export_macro, channelname) /* empty */
#define IPL_TRACE_DECLARE_CHANNEL_IMPORT(export_macro, channelname) /* empty */
#define IPL_TRACE_DECLARE_SHARED_CHANNEL(channelname) /* empty */
#define IPL_TRACE_DECLARE_SHARED_CHANNEL_EXTERN(channelname) /* empty */
#define IPL_TRACE_USE_SHARED_CHANNEL(channelname) do { /* NOP */ } while (false)
#define IPL_TRACE_USE_CHANNEL(channelname) do { /* NOP */ } while (false)
#define IPL_TRACE_GET_CHANNEL_OBJECT(channelname) NULL
#define IPL_TRACE_REGISTER_THREAD(threadname) do { /* NOP */ } while (false)
#define IPL_TRACE_UNREGISTER_THREAD() do { /* NOP */ } while (false)
#define IPL_TRACE_REGISTER_TIMEZONE(name, resolution) __tracing__dummy()
#define IPL_TRACE_UPDATE_TIMEZONE(id, current_time) do { /* NOP */ } while (false)
#define IPL_TRACE_HAS_LEVEL(channelname, level) false
#define IPL_TRACE_SET_LEVEL(channelname, level) do { /* NOP */ } while (false)
#define IPL_TRACE_GET_LEVEL(channelname) 8 /* = ::tracing::Levels::LevelDISABLED */

#define IPL_TRACE_CHECK_LEVEL(level) false
#define IPL_TRACE_CHECK_TRACE_LEVEL  false
#define IPL_TRACE_CHECK_DEBUG_LEVEL  false
#define IPL_TRACE_CHECK_INFO_LEVEL   false
#define IPL_TRACE_CHECK_WARN_LEVEL   false
#define IPL_TRACE_CHECK_ERR_LEVEL       false
#define IPL_TRACE_CHECK_FATAL_LEVEL  false

#define IPL_TRACE_LVL(level, msg) do { /* NOP */ } while (false)
#define IPL_TRACE_TRACE(msg) do { /* NOP */ } while (false)
#define IPL_TRACE_DEBUG(msg) do { /* NOP */ } while (false)
#define IPL_TRACE_INFO(msg) do { /* NOP */ } while (false)
#define IPL_TRACE_WARN(msg) do { /* NOP */ } while (false)
#define IPL_TRACE_ERR(msg) do { /* NOP */ } while (false)
#define IPL_TRACE_FATAL(msg) do { /* NOP */ } while (false)

#define IPL_TRACE_LVL_M(level, mod, msg) do { /* NOP */ } while (false)
#define IPL_TRACE_TRACE_M(mod, msg) do { /* NOP */ } while (false)
#define IPL_TRACE_DEBUG_M(mod, msg) do { /* NOP */ } while (false)
#define IPL_TRACE_INFO_M(mod, msg) do { /* NOP */ } while (false)
#define IPL_TRACE_WARN_M(mod, msg) do { /* NOP */ } while (false)
#define IPL_TRACE_ERR_M(mod, msg) do { /* NOP */ } while (false)
#define IPL_TRACE_FATAL_M(mod, msg) do { /* NOP */ } while (false)

#define IPL_TRACE_LVL_CV(level, msg, ...) do { /* NOP */ } while (false)
#define IPL_TRACE_TRACE_CV(msg, ...) do { /* NOP */ } while (false)
#define IPL_TRACE_DEBUG_CV(msg, ...) do { /* NOP */ } while (false)
#define IPL_TRACE_INFO_CV(msg, ...) do { /* NOP */ } while (false)
#define IPL_TRACE_WARN_CV(msg, ...) do { /* NOP */ } while (false)
#define IPL_TRACE_ERR_CV(msg, ...) do { /* NOP */ } while (false)
#define IPL_TRACE_FATAL_CV(msg, ...) do { /* NOP */ } while (false)

#define IPL_TRACE_LVL_CVA(level, msg, ...) do { /* NOP */ } while (false)
#define IPL_TRACE_LVL_CVP(level, priv_flag, msg, ...) do { /* NOP */ } while (false)
#define IPL_TRACE_LVL_CA(level, ...) do { /* NOP */ } while (false)
#define IPL_TRACE_LVL_CP(level, priv_flag, msg)  do { /* NOP */ } while (false)

#define IPL_TRACE_TRACE_CVA(msg, ...) do { /* NOP */ } while (false)
#define IPL_TRACE_DEBUG_CVA(msg, ...) do { /* NOP */ } while (false)
#define IPL_TRACE_INFO_CVA(msg, ...) do { /* NOP */ } while (false)
#define IPL_TRACE_WARN_CVA(msg, ...) do { /* NOP */ } while (false)
#define IPL_TRACE_ERR_CVA(msg, ...) do { /* NOP */ } while (false)
#define IPL_TRACE_FATAL_CVA(msg, ...) do { /* NOP */ } while (false)

#define IPL_TRACE_TRACE_CVP(priv_flag, msg, ...) do { /* NOP */ } while (false)
#define IPL_TRACE_DEBUG_CVP(priv_flag, msg, ...) do { /* NOP */ } while (false)
#define IPL_TRACE_INFO_CVP(priv_flag, msg, ...) do { /* NOP */ } while (false)
#define IPL_TRACE_WARN_CVP(priv_flag, msg, ...) do { /* NOP */ } while (false)
#define IPL_TRACE_ERR_CVP(priv_flag, msg, ...) do { /* NOP */ } while (false)
#define IPL_TRACE_FATAL_CVP(priv_flag, msg, ...) do { /* NOP */ } while (false)

#define IPL_TRACE_TRACE_CA(...)        do { /* NOP */ } while (false)
#define IPL_TRACE_DEBUG_CA(...)        do { /* NOP */ } while (false)
#define IPL_TRACE_INFO_CA(...)         do { /* NOP */ } while (false)
#define IPL_TRACE_WARN_CA(...)         do { /* NOP */ } while (false)
#define IPL_TRACE_ERR_CA(...)          do { /* NOP */ } while (false)
#define IPL_TRACE_FATAL_CA(...)        do { /* NOP */ } while (false)

#define IPL_TRACE_TRACE_CP(priv_flag, msg) do { /* NOP */ } while (false)
#define IPL_TRACE_DEBUG_CP(priv_flag, msg) do { /* NOP */ } while (false)
#define IPL_TRACE_INFO_CP(priv_flag, msg) do { /* NOP */ } while (false)
#define IPL_TRACE_WARN_CP(priv_flag, msg) do { /* NOP */ } while (false)
#define IPL_TRACE_ERR_CP(priv_flag, msg) do { /* NOP */ } while (false)
#define IPL_TRACE_FATAL_CP(priv_flag, msg) do { /* NOP */ } while (false)

#define IPL_TRACE_LVL_CVT(level, ts, msg, ...) do { /* NOP */ } while (false)
#define IPL_TRACE_TRACE_CVT(ts, msg, ...) do { /* NOP */ } while (false)
#define IPL_TRACE_DEBUG_CVT(ts, msg, ...) do { /* NOP */ } while (false)
#define IPL_TRACE_INFO_CVT(ts, msg, ...) do { /* NOP */ } while (false)
#define IPL_TRACE_WARN_CVT(ts, msg, ...) do { /* NOP */ } while (false)
#define IPL_TRACE_ERR_CVT(ts, msg, ...) do { /* NOP */ } while (false)
#define IPL_TRACE_FATAL_CVT(ts, msg, ...) do { /* NOP */ } while (false)

#define IPL_TRACE_LVL_CVMT(level, mod, ts, msg, ...) do { /* NOP */ } while (false)
#define IPL_TRACE_TRACE_CVMT(mod, ts, msg, ...) do { /* NOP */ } while (false)
#define IPL_TRACE_DEBUG_CVMT(mod, ts, msg, ...) do { /* NOP */ } while (false)
#define IPL_TRACE_INFO_CVMT(mod, ts, msg, ...) do { /* NOP */ } while (false)
#define IPL_TRACE_WARN_CVMT(mod, ts, msg, ...) do { /* NOP */ } while (false)
#define IPL_TRACE_ERR_CVMT(mod, ts, msg, ...) do { /* NOP */ } while (false)
#define IPL_TRACE_FATAL_CVMT(mod, ts, msg, ...) do { /* NOP */ } while (false)

#define IPL_TRACE_LVL_CVMNT(level, mod, ts, size, msg, ...) do { /* NOP */ } while (false)
#define IPL_TRACE_TRACE_CVMNT(mod, ts, size, msg, ...) do { /* NOP */ } while (false)
#define IPL_TRACE_DEBUG_CVMNT(mod, ts, size, msg, ...) do { /* NOP */ } while (false)
#define IPL_TRACE_INFO_CVMNT(mod, ts, size, msg, ...) do { /* NOP */ } while (false)
#define IPL_TRACE_WARN_CVMNT(mod, ts, size, msg, ...) do { /* NOP */ } while (false)
#define IPL_TRACE_ERR_CVMNT(mod, ts, size, msg, ...) do { /* NOP */ } while (false)
#define IPL_TRACE_FATAL_CVMNT(mod, ts, size, msg, ...) do { /* NOP */ } while (false)

#define IPL_TRACE_LVL_CVN(level, size, msg, ...) do { /* NOP */ } while (false)
#define IPL_TRACE_TRACE_CVN(size, msg, ...) do { /* NOP */ } while (false)
#define IPL_TRACE_DEBUG_CVN(size, msg, ...) do { /* NOP */ } while (false)
#define IPL_TRACE_INFO_CVN(size, msg, ...) do { /* NOP */ } while (false)
#define IPL_TRACE_WARN_CVN(size, msg, ...) do { /* NOP */ } while (false)
#define IPL_TRACE_ERR_CVN(size, msg, ...) do { /* NOP */ } while (false)
#define IPL_TRACE_FATAL_CVN(size, msg, ...) do { /* NOP */ } while (false)

#define IPL_TRACE_LVL_CVM(level, mod, msg, ...) do { /* NOP */ } while (false)
#define IPL_TRACE_TRACE_CVM(mod, msg, ...) do { /* NOP */ } while (false)
#define IPL_TRACE_DEBUG_CVM(mod, msg, ...) do { /* NOP */ } while (false)
#define IPL_TRACE_INFO_CVM(mod, msg, ...) do { /* NOP */ } while (false)
#define IPL_TRACE_WARN_CVM(mod, msg, ...) do { /* NOP */ } while (false)
#define IPL_TRACE_ERR_CVM(mod, msg, ...) do { /* NOP */ } while (false)
#define IPL_TRACE_FATAL_CVM(mod, msg, ...) do { /* NOP */ } while (false)

#define IPL_TRACE_LVL_CVMN(level, mod, size, msg, ...) do { /* NOP */ } while (false)
#define IPL_TRACE_TRACE_CVMN(mod, size, msg, ...) do { /* NOP */ } while (false)
#define IPL_TRACE_DEBUG_CVMN(mod, size, msg, ...) do { /* NOP */ } while (false)
#define IPL_TRACE_INFO_CVMN(mod, size, msg, ...) do { /* NOP */ } while (false)
#define IPL_TRACE_WARN_CVMN(mod, size, msg, ...) do { /* NOP */ } while (false)
#define IPL_TRACE_ERR_CVMN(mod, size, msg, ...) do { /* NOP */ } while (false)
#define IPL_TRACE_FATAL_CVMN(mod, size, msg, ...) do { /* NOP */ } while (false)

#define IPL_TRACE_LVL_C(level, msg) do { /* NOP */ } while (false)
#define IPL_TRACE_TRACE_C(msg) do { /* NOP */ } while (false)
#define IPL_TRACE_DEBUG_C(msg) do { /* NOP */ } while (false)
#define IPL_TRACE_INFO_C(msg) do { /* NOP */ } while (false)
#define IPL_TRACE_WARN_C(msg) do { /* NOP */ } while (false)
#define IPL_TRACE_ERR_C(msg) do { /* NOP */ } while (false)
#define IPL_TRACE_FATAL_C(msg) do { /* NOP */ } while (false)

#define IPL_TRACE_LVL_CM(level, mod, msg) do { /* NOP */ } while (false)
#define IPL_TRACE_TRACE_CM(mod, msg) do { /* NOP */ } while (false)
#define IPL_TRACE_DEBUG_CM(mod, msg) do { /* NOP */ } while (false)
#define IPL_TRACE_INFO_CM(mod, msg) do { /* NOP */ } while (false)
#define IPL_TRACE_WARN_CM(mod, msg) do { /* NOP */ } while (false)
#define IPL_TRACE_ERR_CM(mod, msg) do { /* NOP */ } while (false)
#define IPL_TRACE_FATAL_CM(mod, msg) do { /* NOP */ } while (false)

#define IPL_TRACE_LVL_RAW(level, type, msg, len) do { /* NOP */ } while (false)
#define IPL_TRACE_TRACE_RAW(type, msg, len) do { /* NOP */ } while (false)
#define IPL_TRACE_DEBUG_RAW(type, msg, len) do { /* NOP */ } while (false)
#define IPL_TRACE_INFO_RAW(type, msg, len) do { /* NOP */ } while (false)
#define IPL_TRACE_WARN_RAW(type, msg, len) do { /* NOP */ } while (false)
#define IPL_TRACE_ERR_RAW(type, msg, len) do { /* NOP */ } while (false)
#define IPL_TRACE_FATAL_RAW(type, msg, len) do { /* NOP */ } while (false)

#define IPL_TRACE_LVL_RAW_V(level, ...) do { /* NOP */ } while (false)
#define IPL_TRACE_TRACE_RAW_V(type, ...) do { /* NOP */ } while (false)
#define IPL_TRACE_DEBUG_RAW_V(type, ...) do { /* NOP */ } while (false)
#define IPL_TRACE_INFO_RAW_V(type, ...) do { /* NOP */ } while (false)
#define IPL_TRACE_WARN_RAW_V(type, ...) do { /* NOP */ } while (false)
#define IPL_TRACE_ERR_RAW_V(type, ...) do { /* NOP */ } while (false)
#define IPL_TRACE_FATAL_RAW_V(type, ...) do { /* NOP */ } while (false)

#define IPL_EMERGENCY_LOG(msg)    ::ipl::cerr << msg << ::ipl::endl
#define IPL_EMERGENCY_BREAK() do { /* NOP */ } while (false)
#define IPL_TRACE_FLUSH() do { /* NOP */ } while (false)

#define IPL_TRACE_DECLARE_CALLBACK(type_name) /* empty */
#define IPL_TRACE_REGISTER_CALLBACK_FUNCTION(callback_name, function_name) __tracing__dummy()
#define IPL_TRACE_REGISTER_CALLBACK_OBJECT(callback_name, object_addr) __tracing__dummy()
#define IPL_TRACE_REGISTER_CALLBACK(callback_name, object_addr, method_addr) __tracing__dummy()
#define IPL_TRACE_UNREGISTER_CALLBACK_FUNCTION(id) do { /* NOP */ } while (false)
#define IPL_TRACE_UNREGISTER_CALLBACK_OBJECT(id) do { /* NOP */ } while (false)
#define IPL_TRACE_UNREGISTER_CALLBACK(callback_name, object_addr) do { /* NOP */ } while (false)

#define IPL_TRACE_EXECUTE_LVL(level, statements) do { /* NOP */ } while (false)
#define IPL_TRACE_EXECUTE_TRACE(statements) do { /* NOP */ } while (false)
#define IPL_TRACE_EXECUTE_DEBUG(statements) do { /* NOP */ } while (false)
#define IPL_TRACE_EXECUTE_INFO(statements) do { /* NOP */ } while (false)
#define IPL_TRACE_EXECUTE_WARN(statements) do { /* NOP */ } while (false)
#define IPL_TRACE_EXECUTE_ERR(statements) do { /* NOP */ } while (false)
#define IPL_TRACE_EXECUTE_FATAL(statements) do { /* NOP */ } while (false)

#define IPL_TRACE_BUFFER_FORWARD_TAGS(tags) do { /* NOP */ } while (false)
#define IPL_TRACE_BUFFER_FORWARD_OBJECT(obj) do { /* NOP */ } while (false)

#define IPL_TRACE_BUFFER(channelname) do { /* NOP */ } while (false)
#define IPL_TRACE_BUFFER_PRINT() do { /* NOP */ } while (false)
#define IPL_TRACE_BUFFER_RESET() do { /* NOP */ } while (false)
#define IPL_TRACE_BUFFER_SETC(level, message) do { /* NOP */ } while (false)
#define IPL_TRACE_BUFFER_SETCV(level, format, ...) do { /* NOP */ } while (false)
#define IPL_TRACE_BUFFER_C(message) do { /* NOP */ } while (false)
#define IPL_TRACE_BUFFER_CV(format, ...) do { /* NOP */ } while (false)
#define IPL_TRACE_BUFFER_LVL_C(level, message) do { /* NOP */ } while (false)
#define IPL_TRACE_BUFFER_TRACE_C(message) do { /* NOP */ } while (false)
#define IPL_TRACE_BUFFER_DEBUG_C(message) do { /* NOP */ } while (false)
#define IPL_TRACE_BUFFER_INFO_C(message) do { /* NOP */ } while (false)
#define IPL_TRACE_BUFFER_WARN_C(message) do { /* NOP */ } while (false)
#define IPL_TRACE_BUFFER_ERR_C(message) do { /* NOP */ } while (false)
#define IPL_TRACE_BUFFER_FATAL_C(message) do { /* NOP */ } while (false)
#define IPL_TRACE_BUFFER_LVL_CV(level, format, ...) do { /* NOP */ } while (false)
#define IPL_TRACE_BUFFER_TRACE_CV(format, ...) do { /* NOP */ } while (false)
#define IPL_TRACE_BUFFER_DEBUG_CV(format, ...) do { /* NOP */ } while (false)
#define IPL_TRACE_BUFFER_INFO_CV(format, ...) do { /* NOP */ } while (false)
#define IPL_TRACE_BUFFER_WARN_CV(format, ...) do { /* NOP */ } while (false)
#define IPL_TRACE_BUFFER_ERR_CV(format, ...) do { /* NOP */ } while (false)
#define IPL_TRACE_BUFFER_FATAL_CV(format, ...) do { /* NOP */ } while (false)
#define IPL_TRACE_BUFFER_SIZE() 0
#define IPL_TRACE_BUFFER_EMPTY() true
#define IPL_TRACE_CLIENT_ID() ""

#define IPL_TRACE_LVL_FMT(level, ...) do { /* NOP */ } while (false)
#define IPL_TRACE_TRACE_FMT(...) do { /* NOP */ } while (false)
#define IPL_TRACE_DEBUG_FMT(...) do { /* NOP */ } while (false)
#define IPL_TRACE_INFO_FMT(...)  do { /* NOP */ } while (false)
#define IPL_TRACE_WARN_FMT(...)  do { /* NOP */ } while (false)
#define IPL_TRACE_ERR_FMT(...)   do { /* NOP */ } while (false)
#define IPL_TRACE_FATAL_FMT(...) do { /* NOP */ } while (false)

#define IPL_TRACE_LVL_FMT_P(level, ...) do { /* NOP */ } while (false)
#define IPL_TRACE_TRACE_FMT_P(...) do { /* NOP */ } while (false)
#define IPL_TRACE_DEBUG_FMT_P(...) do { /* NOP */ } while (false)
#define IPL_TRACE_INFO_FMT_P(...)  do { /* NOP */ } while (false)
#define IPL_TRACE_WARN_FMT_P(...)  do { /* NOP */ } while (false)
#define IPL_TRACE_ERR_FMT_P(...)   do { /* NOP */ } while (false)
#define IPL_TRACE_FATAL_FMT_P(...) do { /* NOP */ } while (false)

#endif /* NTRACE */

#endif /* TRACING_HXX */

