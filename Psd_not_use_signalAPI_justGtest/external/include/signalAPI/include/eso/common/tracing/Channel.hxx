/*
    Copyright 2020 e.solutions GmbH
        All rights reserved
*/
#ifndef TRACING_CHANNEL_HXX
#define TRACING_CHANNEL_HXX

#include <ipl_config.h>

#include <common/tracing/Levels.hxx>
#include <common/iplcommon_dso.h>
#include <common/stdint.h>
#include <common/types/string.hxx>
#include <common/types/list.hxx>
#include <common/Macros.hxx>

#include <stdarg.h>
#include <common/tracing/MessageAttributes.hxx>

namespace tracing
{

class Config;
class IClient;

/*!
 *    \brief
 *        Trace channels are the high-level representation of channel entities.

 *        When creating trace messages one usually wants to associate a context
 *        with them, e.g. some name where they originate from. Furthermore, it
 *        should be possible to filter messages by some kind of priority.
 *        The Channel class provides this feature. It is used to declare trace
 *        entities of type 'channel' within the trace core, it must be given a
 *        unique name and it always holds a filter level. When creating a new
 *        trace message you always reference a specific channel object thus
 *        providing the context where your message comes from.
 *    \note
 *        Maybe you want to use the macros provided in tracing.hxx. This would
 *        allow compiling away all references to a channel and their associated
 *        trace messages for production builds.
 */
class IPLCOMMON_EXPORT Channel
{
public:
    // flags for channel
    //! internal nodes created dynamically in the core to fill the tree
    static const uint32_t FLAG_INTERNAL  = (1 << 0);
    //! automatically register the channel at the channel list
    static const uint32_t FLAG_REGISTER  = (1 << 1);
    static const uint32_t FLAG_NO_REGISTER = 0;
    //! channel was registered during client runtime and not on setup
    static const uint32_t FLAG_RUNTIME   = (1 << 2);
    static const uint32_t FLAG_DEFAULT_CHANNEL = FLAG_REGISTER;

    // maximum message length for c-style messages
    static const size_t MAX_MSG_LEN = 511;

    /*!
     *    \brief
     *        Creates a new channel object.
     *    \param
     *        name_or_path The unique name of the channel.
     *    \param
     *        level The initial level of this channel object. Note that this may
     *        be overridden during runtime either by user interaction or through
     *        entries in the configuration file.
     *    \param
     *        flags Any specific channel flags
     */
    Channel(const ipl::string & name_or_path, int16_t level = Levels::LevelNONE,
            uint32_t flags = FLAG_DEFAULT_CHANNEL) IPL_NOEXCEPT;

    //! \brief Virtual destructor.
    ~Channel() IPL_NOEXCEPT;

    //! \brief Get the client instance.
    IClient * getClient() const IPL_NOEXCEPT
    {
        return m_client;
    }

    //! \brief Set the client instance.
    void setClient(IClient *client) IPL_NOEXCEPT
    {
        m_client = client;
    }

    //! \brief Get the channel's parent.
    const Channel * getParent() const IPL_NOEXCEPT
    {
        return m_parent;
    }

    //! \brief Get the channel's parent.
    Channel * getParent() IPL_NOEXCEPT
    {
        return m_parent;
    }

    //! \brief Set the channel's parent.
    void setParent(Channel *parent) IPL_NOEXCEPT
    {
        m_parent = parent;
    }

    //! \brief Get the channel's flags.
    uint32_t getFlags() const IPL_NOEXCEPT
    {
        return m_flags;
    }

    //! \brief Checks if channel has exactly matching flags.
    bool hasFlags(uint32_t f) const IPL_NOEXCEPT
    {
        return (m_flags & f) == f;
    }

    //! \brief Add channel flags.
    void addFlags(uint32_t f) IPL_NOEXCEPT
    {
        m_flags |= f;
    }

    /*!
     *    \brief
     *        Check if a channel has child channels.
     *    \return
     *        true if children exist.
     */
    bool hasChildren() const IPL_NOEXCEPT
    {
        return !m_children.empty();
    }

    /*!
     *    \brief
     *        Determine the number of children.
     */
    size_t getNumChildren() const IPL_NOEXCEPT
    {
        return m_children.size();
    }

    //! \brief Get a list of all children.
    const ipl::list<Channel *> &getAllChildren() const IPL_NOEXCEPT
    {
        return m_children;
    }

    /*!
     *    \brief
     *        Adds a new child to a channel.
     *    \param
     *        c The child to add.
     */
    void addChild(Channel * c) IPL_NOEXCEPT
    {
        m_children.push_back(c);
    }

    //! \brief Removes a child channel.
    void removeChild(Channel * c) IPL_NOEXCEPT
    {
        m_children.remove(c);
    }

    /*!
     *    \brief
     *        Find the child of a channel.
     *    \param
     *        name The name of the child to search for.
     *    \return
     *        The child channel if found, NULL otherwise.
     */
    Channel * findChild(const ipl::string & name) const IPL_NOEXCEPT;

    /*!
     *    \brief
     *        Find a channel by its channel ID.
     *    \param
     *        cid The channel ID.
     *    \return
     *        A channel object if the ID was found, NULL otherwise.
     */
    Channel * findByChannelId(int32_t cid) IPL_NOEXCEPT;

    /*!
     *    \brief
     *        Get the channel's complete path name.
     *    \return
     *        A string with the channel's name, prefixed by parent's path name,
     *        separated by the underscore character.
     */
    void determinePathString() IPL_NOEXCEPT;

    /*!
     *    \brief
     *        Sets unique channel id.
     */
    void setChannelId(int32_t cid) IPL_NOEXCEPT
    {
        m_cid = cid;
    }

    /*!
     *    \brief
     *        Returns the unique channel id.
     */
    int32_t getChannelId() const IPL_NOEXCEPT
    {
        return m_cid;
    }

    /*!
     *    \brief
     *        Set the default and the initial filter level of a channel.

     *        The actual filter level may be changed afterwards, e.g. if
     *        the configuration file specifies a different level.
     *    \param
     *        level The filter level, see Levels.hxx.
     */
    bool changeFilterLevel(int16_t level) IPL_NOEXCEPT;

    /*!
     *    \brief
     *        Get the current channel filter level, see Levels.hxx.
     */
    int16_t getFilterLevel() const IPL_NOEXCEPT
    {
        return m_filter_level;
    }

    /*!
     *  \brief
     *      Check filter level at the core.

     *      This method is used to check if a specific message level
     *      on this channel with its thread context would be filtered away.
     *  \param
     *      msg_level The message level to be checked.
     *  \return
     *      true if both channel and related thread have a lower or equal filter level
     *      setting than the message level.
     */
    bool isLevelEnabled(const int16_t msg_level) const IPL_NOEXCEPT;

    /*!
     *    \brief
     *        Get the channel's unique name.
     */
    const ipl::string & getName() const IPL_NOEXCEPT
    {
        return m_name;
    }

    //! \brief Get the channel path.
    const ipl::string & getPath() const IPL_NOEXCEPT
    {
        return m_path;
    }

    //! \brief Set the channel path.
    void setPath(const ipl::string &path) IPL_NOEXCEPT { m_path = path; }

    //! \brief Set the channel name
    void setName(const ipl::string &name) IPL_NOEXCEPT { m_name = name; }

    /*!
     *    \brief
     *        Determines the filter level based on parent channels if no
     *        filter level is set for a channel, see Levels.hxx.
     */
    int16_t getValidFilterLevelAlongPath() const IPL_NOEXCEPT;

    /*!
     *    \brief
     *        Enable this channel.
     */
    bool enable() IPL_NOEXCEPT;

    /*!
     *    \brief
     *        Disable this channel.
     */
    bool disable() IPL_NOEXCEPT;

    /*!
     *    \brief
     *        Creates a trace message.

     *        This creates a new trace message containing a user-supplied
     *        message string with the filter level specified IF the channel
     *        is enabled and its filter level is not greater than the level
     *        provided as argument.
     *        The message is then forwarded to the trace core for further
     *        processing.
     *    \param
     *        level The filter level of the trace message, see Levels.hxx.
     *    \param
     *        message The actual message to be logged.
     */
    void log(int16_t level, const ipl::string & message) IPL_NOEXCEPT;

    /*!
     *    \brief
     *        Same as before but with an additional parameter \c modifiers.
     *    \param
     *        level The filter level of the trace message, see Levels.hxx.
     *    \param
     *        modifiers See Modifiers.hxx.
     *    \param
     *        message The actual message to be logged.
     */
    void log(int16_t level, int16_t modifiers, const ipl::string & message) IPL_NOEXCEPT;

    /*!
     * \brief
     *         Support for constant string message

     *         This creates a new trace message containing a user-supplied
     *      string in printf notation.
     */
    void logC(int16_t level, const char *message) IPL_NOEXCEPT;

     /*!
     * \brief
     *         Support for constant string message with Message Attributes (Tags or/and Nodes)

     *         This creates a new trace message containing a user-supplied string and
     *         message attributes coming with this message
     */
    void logCA(int16_t level, const char *message, MessageAttributes&& attr) IPL_NOEXCEPT;

    /*!
     * \brief
     *         Support for variable length message with Message Attributes (Tags or/and Nodes)
     *         This creates a new trace message containing a user-supplied string and
     *         message attributes coming with this message
     */
    void logCVA(int16_t level, MessageAttributes&& attr, const char *format, ...) IPL_NOEXCEPT;

     /*!
     * \brief
     *         Support for variable length message with Message Attributes (Tags or/and Nodes)
     *         This creates a new trace message containing a user-supplied string and
     *         message attributes coming with this message
     */
    void vlogCA(int16_t level, MessageAttributes&& attr, const char *format, va_list vargs) IPL_NOEXCEPT;

    /*!
     * \brief
     *         Support for constant string message

     *         This creates a new trace message containing a user-supplied
     *      string in printf notation.
     */
    void logC(int16_t level, int16_t modifiers, const char *message) IPL_NOEXCEPT;

    /*!
     * \brief
     *         Support for printf-style traces with vargs

     *         This creates a new trace message containing a user-supplied
     *      string in printf notation.
     * \note
     *        The resulting message is truncated to 511 bytes \sa MAX_MSG_LEN.
     */
    void logCV(int16_t level, const char *format, ...) IPL_NOEXCEPT IPL_PRINTF_LIKE_FUNCTION(3,4);

    /*!
     * \brief
     *         Support for printf-style traces with vargs

     *         This creates a new trace message containing a user-supplied
     *      string in printf notation.
     * \note
     *        The resulting message is truncated to 511 bytes \sa MAX_MSG_LEN.
     */
    void logCV(int16_t level, int16_t modifiers, const char *format, ...) IPL_NOEXCEPT IPL_PRINTF_LIKE_FUNCTION(4,5);

    /*!
     * \brief
     *         Support for printf-style traces with vargs

     * \details
     *         This creates a new trace message containing a user-supplied
     *      string in printf notation.
     * \note
     *        The resulting message is truncated to 511 bytes \sa MAX_MSG_LEN.
     */
    void logCV(int16_t level, int16_t modifiers, int64_t ts, const char *format, ...) IPL_NOEXCEPT IPL_PRINTF_LIKE_FUNCTION(5,6);

    /*!
     * \brief
     *         Support for printf-style traces with vargs
     * \details
     *         This creates a new trace message containing a user-supplied
     *      string in printf notation.
     * \note
     *        The resulting message is not truncated. Instead the buffer used for
     *        creating the message is heap-allocated which might reduce performance.
     */
    void logCVN(int16_t level, size_t size, const char *format, ...) IPL_NOEXCEPT IPL_PRINTF_LIKE_FUNCTION(4,5);

    /*!
     * \brief
     *         Support for printf-style traces with vargs

     * \details
     *         This creates a new trace message containing a user-supplied
     *      string in printf notation.
     * \note
     *        The resulting message is not truncated. Instead the buffer used for
     *        creating the message is heap-allocated which might reduce performance.
     */
    void logCVN(int16_t level, int16_t modifiers, size_t size, const char *format, ...) IPL_NOEXCEPT IPL_PRINTF_LIKE_FUNCTION(5,6);

    /*!
     * \brief
     *         Support for printf-style traces with vargs
     * \details
     *         This creates a new trace message containing a user-supplied
     *      string in printf notation.
     * \note
     *        The resulting message is not truncated. Instead the buffer used for
     *        creating the message is heap-allocated which might reduce performance.
     */
    void logCVN(int16_t level, int16_t modifiers, int64_t ts, size_t size, const char *format, ...) IPL_NOEXCEPT IPL_PRINTF_LIKE_FUNCTION(6,7);

    /*!
     * \brief
     *         Support for printf-style traces with vargs

     *         This creates a new trace message containing a user-supplied
     *      string in printf notation.
     * \note
     *        The resulting message is truncated to 511 bytes \sa MAX_MSG_LEN.
     */
    void vlogCV(int16_t level, const char *format, va_list vaargs) IPL_NOEXCEPT;

    /*!
     * \brief
     *         Support for printf-style traces with vargs

     *         This creates a new trace message containing a user-supplied
     *      string in printf notation.
     * \note
     *        The resulting message is truncated to 511 bytes \sa MAX_MSG_LEN.
     */
    void vlogCV(int16_t level, int16_t modifiers, const char *format, va_list vaargs) IPL_NOEXCEPT;

    /*!
     * \brief
     *         Support for printf-style traces with vargs

     * \details
     *         This creates a new trace message containing a user-supplied
     *      string in printf notation.
     * \note
     *        The resulting message is truncated to 511 bytes \sa MAX_MSG_LEN.
     */
    void vlogCV(int16_t level, int16_t modifiers, int64_t ts, const char *format, va_list vaargs) IPL_NOEXCEPT;

    /*!
     * \brief
     *         Support for printf-style traces with vargs
     * \details
     *         This creates a new trace message containing a user-supplied
     *      string in printf notation.
     * \note
     *        The resulting message is not truncated. Instead the buffer used for
     *        creating the message is heap-allocated which might reduce performance.
     */
    void vlogCVN(int16_t level, size_t size, const char *format, va_list vaargs) IPL_NOEXCEPT;

    /*!
     * \brief
     *         Support for printf-style traces with vargs

     * \details
     *         This creates a new trace message containing a user-supplied
     *      string in printf notation.
     * \note
     *        The resulting message is not truncated. Instead the buffer used for
     *        creating the message is heap-allocated which might reduce performance.
     */
    void vlogCVN(int16_t level, int16_t modifiers, size_t size, const char *format, va_list vaargs) IPL_NOEXCEPT;

    /*!
     * \brief
     *         Support for printf-style traces with vargs
     * \details
     *         This creates a new trace message containing a user-supplied
     *      string in printf notation.
     * \note
     *        The resulting message is not truncated. Instead the buffer used for
     *        creating the message is heap-allocated which might reduce performance.
     */
    void vlogCVN(int16_t level, int16_t modifiers, int64_t ts, size_t size, const char *format, va_list vaargs) IPL_NOEXCEPT;

    /*!
     * \brief
     *         Submit a raw trace message with multiple buffers

     *         This creates a new trace message from the given buffer
     *         The buffers are given as tuples: ptr and size in the variadic
     *         argument list. Maximum total message length is MAX_MSG_LEN.
     */
    IPL_DEPRECATED("Use vlogCV or logRawV instead")
    void vlogRawV(int16_t level, int16_t modifiers, int16_t type, va_list vaargs) IPL_NOEXCEPT;

    /*!
     * \brief
     *         Submit a raw trace message with multiple buffers

     *         This creates a new trace message from the given buffer
     *         The buffers are given as tuples: ptr and size in the variadic
     *         argument list. Maximum total message length is MAX_MSG_LEN.
     */
    IPL_DEPRECATED("Use vlogCV or logRawV instead")
    void vlogRawV(int16_t level, int16_t type, va_list vaargs) IPL_NOEXCEPT;

    /*!
     * \brief
     *         Submit a raw trace message

     *         This creates a new trace message from the given buffer
     */
    void logRaw(int16_t level, int16_t modifiers, int16_t type, const void *buffer, size_t len) IPL_NOEXCEPT;

    /*!
     * \brief
     *         Submit a raw trace message

     *         This creates a new trace message from the given buffer
     */
    void logRaw(int16_t level, int16_t type, const void *buffer, size_t len) IPL_NOEXCEPT;

    /*!
     * \brief
     *         Submit a raw trace message with multiple buffers

     *         This creates a new trace message from the given buffer
     *         The buffers are given as tuples: ptr and size in the variadic
     *         argument list.
     */
    void logRawV(int16_t level, int16_t modifiers, int32_t type, ...) IPL_NOEXCEPT;

    /*!
     * \brief
     *         Submit a raw trace message with multiple buffers

     *         This creates a new trace message from the given buffer
     *         The buffers are given as tuples: ptr and size in the variadic
     *         argument list.
     */
    void logRawV(int16_t level, int32_t type, va_list args) IPL_NOEXCEPT;

    /*!
     *     \brief
     *         remove parent and child links
     */
    void detach() IPL_NOEXCEPT;

protected:
    //! The client instance this channel was created with.
    IClient * m_client;
    //! The parent channel, which may be NULL for the root channel only.
    Channel * m_parent;
    //! All known child channels of this channel.
    ipl::list<Channel *> m_children;
    //! The channel's name which consists of the substring following the
    //! last underscore character in the string supplied to the ctor.
    ipl::string m_name;
    //! The path name of the channel
    ipl::string m_path;
    //! The channel's current filter level.
    int16_t m_filter_level;
    //! The filter level this channel was created with.
    int16_t m_create_level;
    //! The unique channel ID as reported from the trace frontend.
    int32_t m_cid;
    //! Flag that the instance is statically created
    uint32_t m_flags;

    friend class Client;
    //! \brief Sets the filter level
    void setFilterLevel(int16_t level) IPL_NOEXCEPT;
    //! \brief Utility function to get a channel's path name.
    void fillPathString(ipl::string & buffer) const IPL_NOEXCEPT;
    //! \brief Reports a message to the frontend if it is not filtered away, used by public log() function.
    void logMessage(int16_t level, const ipl::string & message) IPL_NOEXCEPT;
    //! \brief Reports a message to the frontend if it is not filtered away, used by public log() function.
    void logMessage(int16_t level, int16_t modifiers, const ipl::string & message) IPL_NOEXCEPT;
};

/*!
 * \brief
 *        This helper submits a printf-like log message with many tags.
 *        Tags are provided in braced-init-list style .
 */
template<typename T>
void tracing_helper_logCVA(::tracing::Channel * __tracing__scope,
        int16_t level,
        std::initializer_list<LogTag<T>> list,
        const char *format, ...)
{
    va_list args;
    va_start(args, format);

    tracing::TagsList tags;
    for (auto it = list.begin(); it != list.end(); ++it)
    {
        tags.emplace_back(std::unique_ptr<LogTagBase>((LogTagBase*)(*it).clone()));;
    }

    MessageAttributes attributes;
    attributes.forwardTags(tags);

    __tracing__scope->vlogCA(level, std::move(attributes), format, args);

    va_end(args);
}

/*!
 * \brief
 *        This helper submits a printf-like log message with many tags.
 *        Tags are provided in braced-init-list style .
 */
template<typename T>
void tracing_helper_logCVA(::tracing::Channel * __tracing__scope,
            int16_t level,
            std::initializer_list<LogTag<T>> list,
            ObjectNodePtr &&object,
            const char *format, ...)
{
    va_list args;
    va_start(args, format);

    tracing::TagsList tags;
    for (auto it = list.begin(); it != list.end(); ++it)
    {
        tags.emplace_back(std::unique_ptr<LogTagBase>((LogTagBase*)(*it).clone()));;
    }

    MessageAttributes attributes;
    attributes.forwardTags(tags);
    attributes.forwardObject(std::move(object));

    __tracing__scope->vlogCA(level, std::move(attributes), format, args);

    va_end(args);
}


/*!
 * \brief
 *        This helper submits a printf-like log message with one tag
 */
void IPLCOMMON_EXPORT tracing_helper_logCVA(::tracing::Channel * __tracing__scope, int16_t level, const LogTagBase &tag, const char *format, ...);

/*!
 * \brief
 *        This helper submits a printf-like log message with one tag and one object
 */
void IPLCOMMON_EXPORT tracing_helper_logCVA(::tracing::Channel * __tracing__scope, int16_t level, const LogTagBase &tag, ObjectNodePtr &&object, const char *format, ...);

/*!
 * \brief
 *        This helper submits a printf-like log message with one object
 */
void IPLCOMMON_EXPORT tracing_helper_logCVA(::tracing::Channel * __tracing__scope, int16_t level, ObjectNodePtr &&object, const char *format, ...);

/*!
 * \brief
 *        This helper submits a log message many tags and one object. Tags are provided in braced-init-list style .
 */
template<typename T>
void tracing_helper_logCA(::tracing::Channel * __tracing__scope,
                    int16_t level,
                    std::initializer_list<LogTag<T>> list,
                    ObjectNodePtr &&object,
                    const char *msg)
{
    MessageAttributes attributes;

    tracing::TagsList tags;
    for (auto it = list.begin(); it != list.end(); ++it)
    {
        tags.emplace_back(std::unique_ptr<LogTagBase>((LogTagBase*)(*it).clone()));;
    }

    attributes.forwardTags(tags);
    attributes.forwardObject(std::move(object));

    __tracing__scope->logCA(level, msg, std::move(attributes));
}

/*!
 * \brief
 *        This helper submits a log message many tags. Tags are provided in braced-init-list style .
 */
template<typename T>
void tracing_helper_logCA(::tracing::Channel * __tracing__scope,
                    int16_t level,
                    std::initializer_list<LogTag<T>> list,
                    const char *msg)
{
    MessageAttributes attributes;

    tracing::TagsList tags;
    for (auto it = list.begin(); it != list.end(); ++it)
    {
        tags.emplace_back(std::unique_ptr<LogTagBase>((LogTagBase*)(*it).clone()));;
    }

    attributes.forwardTags(tags);

    __tracing__scope->logCA(level, msg, std::move(attributes));
}

/*!
 * \brief
 *        This helper submits a log message with one tag
 */
void IPLCOMMON_EXPORT tracing_helper_logCA(::tracing::Channel * __tracing__scope, int16_t level, const LogTagBase &tag, const char *msg);

/*!
 * \brief
 *        This helper submits a log message with one object
 */
void IPLCOMMON_EXPORT tracing_helper_logCA(::tracing::Channel * __tracing__scope, int16_t level, ObjectNodePtr &&object, const char *msg);

/*!
 * \brief
 *        This helper submits a log message with one object and one tag
 */
void IPLCOMMON_EXPORT tracing_helper_logCA(::tracing::Channel * __tracing__scope, int16_t level,  const LogTagBase &tag, ObjectNodePtr &&object, const char *msg);

} //namespace tracing

#endif /* TRACING_CHANNEL_HXX */

