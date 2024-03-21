/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/
#ifndef TRACEME_HXX
#define TRACEME_HXX

#include <tracing/tracing_dso.h>
#include <common/tracing/tracing.hxx>
#include <osal/StreamFmtFileW.hxx>
#include <osal/Mutex.hxx>

namespace tracing
{

/*!
 *    \brief
 *        Debugging help for tracing itself.
 *    \note
 *        If you intend to create your own plugins for the tracing module
 *        you may use the macros defined in this header for tracing internal
 *        debugging purposes.
 *        First a TraceMe channel needs to be declared via
 *        IPL_TRACEME_DECLARE_CHANNEL(<channelname>) - with default WARNING level
 *        or via
 *        IPL_TRACEME_DECLARE_CHANNEL_WITH_LEVEL(<channelname>, <level>) - with an explicit level.
 *        Then the scope setting is required, either locally via
 *        IPL_TRACEME_SET_SCOPE(<channelname>)
 *        or - in class context in constructor -
 *        IPL_TRACEME_INIT_SCOPE(<channelname>).
 *        Now tracing via TraceMe is possible via IPL_TRACEME_<level> macros.
 *        Note that in class context the scope has also to be declared via
 *        IPL_TRACEME_DECLARE_SCOPE(<channelname>).
 *
 *        The default trace level is WARNING and TraceMe messages are
 *        written to std::cerr by default.
 *        The common trace level can be set via environment variable
 *        "IPL_TRACEME_FILTER" (e.g. IPL_TRACEME_FILTER=info).
 *        A channel specific trace level can also be set via environment
 *        variables "IPL_TRACEME_FILTER_<channelname>"
 *        (e.g. IPL_TRACEME_FILTER_my_channel=trace).
 *        TraceMe messages can also be routed to a file when the related
 *        full file path is set via environment variable
 *        "IPL_TRACEME_FILE" (e.g. IPL_TRACEME_FILE=/data/eso/traceMe_log).
 */
class TRACINGIMPL_EXPORT TraceMe
{
public:
    static const uint8_t MAX_MSG_LEN = 150;

    //! \brief Constructor with channel name and default trace level.
    TraceMe(const std::string & channel_name, const uint16_t level = Levels::LevelWARN);
    //! \brief Virtual destructor
    virtual ~TraceMe();

    //! \brief Default Constructor, disabled.
    TraceMe()=delete;
    //! \brief Copy Constructor, disabled.
    TraceMe(const TraceMe& other)=delete;
    //! \brief Move Constructor, disabled.
    TraceMe(const TraceMe&& other)=delete;
    //! \brief Assignment operator, disabled.
    TraceMe& operator=(const TraceMe& other)=delete;
    //! \brief Move assignment operator, disabled.
    TraceMe& operator=(const TraceMe&& other)=delete;

    //! \brief Write a traceMe message without variable arguments
    void msg( const uint16_t level, int line, const char *msg);
    //! \brief Write a traceMe message without variable arguments
    void msg( const uint16_t level, int line, const std::ostringstream & os)
    {
        msg(level, line, os.str().c_str());
    }
    //! \brief Write a traceMe message without variable arguments
    void msg( const uint16_t level, int line, const std::string & str)
    {
        msg(level, line, str.c_str());
    }

    //! \brief Write a traceMe message with variable arguments
    void msgCV( const uint16_t level, int line, const char *format, ... ) IPL_NOEXCEPT IPL_PRINTF_LIKE_FUNCTION(4,5);

    //! \brief Trace level check
    bool isEnabled(uint16_t level);
    //! \brief Set the trace level
    void setLevel(uint16_t level);
    //! \brief Set the traceMe file which is initially set via environment variable
    static bool setTraceMeFile(const std::string & file_name);

private:
    //! \brief Read filter level from environment for given channel
    void readEnvFilterLevel();
    //! \brief Read filter level from environment for given channel and environment variable
    bool readEnvSubFilterLevel(const std::string & env_variable);
    //! \brief Transform string to lowercase
    std::string toLower(const std::string & str);

    //! \brief the optional trace file for any traceMe messages
    static osal::StreamFmtFileW* s_file;
    //! \brief flag to track initialization of TraceMe instance with channel "TraceMe"
    static bool s_traceme_initialized;

    //! The active filter level
    uint16_t m_filter_level;
    //! The channel name
    std::string m_channel_name;
    //! \brief Lock to guard writing to log (keep on heap to prevent inconsistencies during shutdown)
    static osal::Mutex *s_mutex;
};
} // end namespace tracing


/* TraceMe macros for channel registration */

//! \brief Declares TraceMe channel within a given scope and WARNING level
#define IPL_TRACEME_DECLARE_CHANNEL(channelname) \
    ::tracing::TraceMe __traceme__channel_ ## channelname( TOSTRING(channelname) )

//! \brief Declares TraceMe channel within a given scope and explicit default level
#define IPL_TRACEME_DECLARE_CHANNEL_WITH_LEVEL(channelname, level) \
    ::tracing::TraceMe __traceme__channel_ ## channelname( TOSTRING(channelname), (level) )

//! \brief Declares a traceMe channel scope reference
#define IPL_TRACEME_DECLARE_SCOPE(channelname) \
    ::tracing::TraceMe * __traceme__scope

//! \brief Sets the scope of a TraceMe channel (use at the beginning of a block)
#define IPL_TRACEME_SET_SCOPE(channelname) \
    ::tracing::TraceMe * __traceme__scope = &__traceme__channel_ ## channelname

//! \brief Sets the scope of a TraceMe channel (use at ctor initialization)
#define IPL_TRACEME_INIT_SCOPE(channelname) \
    __traceme__scope( &__traceme__channel_ ## channelname )

//! \brief Informs if certain trace level is enabled
#define IPL_TRACEME_IS_ENABLED(level) \
    __traceme__scope->isEnabled(level)

//! \brief Sets the trace level
#define IPL_TRACEME_SET_LEVEL(level) \
    __traceme__scope->setLevel(level)

/* TraceMe macros WITHOUT variable arguments */

//! \brief Create a traceMe message without args after level evaluation
#define IPL_TRACEME_LVL(level, arg) \
    do { \
        if (IPL_TRACEME_IS_ENABLED(level)) \
        { \
            __traceme__scope->msg( (level), __LINE__, (arg)); \
        }\
    } while (false)

//! \brief Create a traceMe message with level "Trace"
#define IPL_TRACEME_TRACE(msg) IPL_TRACEME_LVL(::tracing::Levels::LevelTRACE, (msg))

//! \brief Create a traceMe message with level "Debug"
#define IPL_TRACEME_DEBUG(msg) IPL_TRACEME_LVL(::tracing::Levels::LevelDEBUG, (msg))

//! \brief Create a traceMe message with level "Info"
#define IPL_TRACEME_INFO(msg)  IPL_TRACEME_LVL(::tracing::Levels::LevelINFO, (msg))

//! \brief Create a traceMe message with level "Warning"
#define IPL_TRACEME_WARN(msg)  IPL_TRACEME_LVL(::tracing::Levels::LevelWARN, (msg))

//! \brief Create a traceMe message with level "Error"
#define IPL_TRACEME_ERR(msg)   IPL_TRACEME_LVL(::tracing::Levels::LevelERROR, (msg))

//! \brief Create a traceMe message with level "Fatal"
#define IPL_TRACEME_FATAL(msg) IPL_TRACEME_LVL(::tracing::Levels::LevelFATAL, (msg))


/* TraceMe macros WITH variable arguments */

//! \brief Create a traceMe message with args after level evaluation
#define IPL_TRACEME_LVL_CV(level, format, ...) \
    do { \
        if (IPL_TRACEME_IS_ENABLED(level)) \
        { \
            __traceme__scope->msgCV( (level), __LINE__, (format), __VA_ARGS__); \
        }\
    } while (false)

//! \brief Create a traceMe message with args and level "Trace"
#define IPL_TRACEME_TRACE_CV(msg, ...) IPL_TRACEME_LVL_CV(::tracing::Levels::LevelTRACE, (msg), __VA_ARGS__)

//! \brief Create a traceMe message with args and level "Debug"
#define IPL_TRACEME_DEBUG_CV(msg, ...) IPL_TRACEME_LVL_CV(::tracing::Levels::LevelDEBUG, (msg), __VA_ARGS__)

//! \brief Create a traceMe message with args and level "Info"
#define IPL_TRACEME_INFO_CV(msg, ...)  IPL_TRACEME_LVL_CV(::tracing::Levels::LevelINFO, (msg), __VA_ARGS__)

//! \brief Create a traceMe message with args and level "Warning"
#define IPL_TRACEME_WARN_CV(msg, ...)  IPL_TRACEME_LVL_CV(::tracing::Levels::LevelWARN, (msg), __VA_ARGS__)

//! \brief Create a traceMe message with args and level "Error"
#define IPL_TRACEME_ERR_CV(msg, ...)   IPL_TRACEME_LVL_CV(::tracing::Levels::LevelERROR, (msg), __VA_ARGS__)

//! \brief Create a traceMe message with args and level "Fatal"
#define IPL_TRACEME_FATAL_CV(msg, ...) IPL_TRACEME_LVL_CV(::tracing::Levels::LevelFATAL, (msg), __VA_ARGS__)

#endif /* TRACEME_HXX */
