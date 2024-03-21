/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef TRACING_TRACEBUFFER_HXX
#define TRACING_TRACEBUFFER_HXX

#include <ipl_config.h>
#include <common/iplcommon_dso.h>
#include <common/Macros.hxx>
#include <common/types/string.hxx>

#include <common/tracing/MessageAttributes.hxx>

namespace tracing
{

class Channel;

/*!
 *  \brief
 *      This class composes a trace Core Message.
 *
 *      The text content of the eso trace Core Message is accumulated until the
 *      print() function is called.
 *      Non-text information (Objects or Tags) can be added as well
 *      using forwardTags() or forwardObjects() functions.
 */
class IPLCOMMON_EXPORT TraceBuffer
{
public:
    //! Maximum supported message length for printf-like methods.
    static const size_t MAX_FMT_MSG_LEN;

protected:
    friend class CoreConfig;
    //! \brief Set the maximum total message length for all TraceBuffers, but at least MAX_FMT_MSG_LEN.
    static void setMaxMsgLen(size_t max_size) IPL_NOEXCEPT;

    //! Configurable maximum total message length, but at least MAX_FMT_MSG_LEN.
    static size_t s_max_msg_len;

public:
    //! \brief Constructor.
    TraceBuffer(Channel * channel) IPL_NOEXCEPT;
    //! \brief Destructor.
    ~TraceBuffer() IPL_NOEXCEPT;

    //! \brief Set the message text if given level is enabled by the trace channel.
    void set(int16_t level, const char * msg) IPL_NOEXCEPT;
    //! \brief Set the message text with variable arguments if given level is enabled by the trace channel.
    void setf(int16_t level, const char * fmt, ...) IPL_NOEXCEPT IPL_PRINTF_LIKE_FUNCTION(3, 4);
    //! \brief Set the message text if given level is enabled by the trace channel.
    void set(int16_t level, const ipl::string & msg) IPL_NOEXCEPT
    {
        set(level, msg.c_str());
    }

    //! \brief Appends the message text.
    void append(const char * msg) IPL_NOEXCEPT;
    //! \brief Appends the message text with variable arguments.
    void appendf(const char * fmt, ...) IPL_NOEXCEPT IPL_PRINTF_LIKE_FUNCTION(2, 3);
    //! \brief Appends the message text.
    void append(const ipl::string & msg) IPL_NOEXCEPT
    {
        append(msg.c_str());
    }
    //! \brief Appends the message text if given level is enabled by the trace channel.
    void append(int16_t level, const char * msg) IPL_NOEXCEPT;
    //! \brief Appends the message with variable arguments if given level is enabled by the trace channel.
    void appendf(int16_t level, const char * fmt, ...) IPL_NOEXCEPT IPL_PRINTF_LIKE_FUNCTION(3, 4);
    //! \brief Appends the message text if given level is enabled by the trace channel.
    void append(int16_t level, const ipl::string & msg) IPL_NOEXCEPT
    {
        append(level, msg.c_str());
    }

    //! \brief Prints m_msg if not empty.
    void print() IPL_NOEXCEPT;
    //! \brief Clears m_msg, and sets m_level to Levels::LevelTRACE.
    void reset() IPL_NOEXCEPT;

    //! \brief Get the size of the stored message.
    size_t size() const IPL_NOEXCEPT
    {
        return m_msg.size();
    }
    //! \brief Check if stored message is empty.
    bool empty() const IPL_NOEXCEPT
    {
        return m_msg.empty();
    }

    //! \brief Check if filter level is enabled at the core.
    bool isLevelEnabled(const int16_t level) const IPL_NOEXCEPT;

    //! \brief Assign tags to the traceBuffer. After assign, messageTags will be cleared
    void forwardTags(std::vector<std::unique_ptr<LogTagBase>> & messageTags)
    {
        m_messageAttributes.forwardTags(messageTags);
    }

    //! \brief Assign and forward ownership of object node to the traceBuffer
    void forwardObject(BaseNodePtr &&object)
    {
        m_messageAttributes.forwardObject(std::move(object));
    }
protected:
    Channel * m_channel;
    ipl::string m_msg;
    int16_t m_level;
    MessageAttributes m_messageAttributes;
};


} // end of namespace tracing

#endif /* TRACING_TRACEBUFFER_HXX */

