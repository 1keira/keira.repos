/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/


#ifndef TRACING_MESSAGE_HXX
#define TRACING_MESSAGE_HXX

#include <common/tracing/MessageTypes.hxx>
#include <common/types/string.hxx>
#include <common/tracing/MessageAttributes.hxx>
#include <tracing/tracing_dso.h>
#include <util/SharedPtr.hxx>

namespace tracing
{

class Core;
class MessageBuffer;
class Frontend;
class FileFrontend;

namespace protocol
{
class ConnectionFrontendHandler;
class LogDataMessage;
class BulkLogDataMessage;
} // end of namespace protocol

/*!
 *  \brief
 *      Creates a trace message.
 *  \note
 *      Most probably you don't want to use this class for creating trace
 *      messages directly. Instead you should use trace macros or
 *      Frontend::log() functions.
 */
class Message
{
public:
    /*!
     *  \brief
     *      Constructor
     *
     *  \param
     *      timestamp The timestamp in nanoseconds when this message was created.
     *      \sa osal::Time::getTimestampNS()
     *  \param
     *      channel_id The channel's entity ID this message is associated with.
     *  \param
     *      thread_id The thread's entity ID this message is associated with.
     *  \param
     *      level The filter level this message has, if the thread or the
     *      channel have a higher filter level the message will be discarded.
     *  \param
     *      modifiers \sa Modifiers.
     *  \param
     *      type Message type, \sa MessageTypes.
     *  \param
     *      data Pointer to some arbitrary data.
     *  \param
     *      len Number of bytes to contain in the message, starting from data.
     */
    TRACINGIMPL_EXPORT Message(int64_t timestamp, int32_t channel_id,
            int32_t thread_id, int16_t level, int16_t modifiers, int16_t type,
            const void * data, size_t len);

    /*!
     *  \brief
     *      Constructor
     *
     *  \param
     *      timestamp The timestamp in nanoseconds when this message was created
     *      \sa osal::Time::getTimestampNS()
     *  \param
     *      channel_id The channel's entity ID this message is associated with.
     *  \param
     *      thread_id The thread's entity ID this message is associated with.
     *  \param
     *      level The filter level this message has, if the thread or the
     *      channel have a higher filter level the message will be discarded.
     *  \param
     *      modifiers \sa Modifiers.
     *  \param
     *      type Message type, \sa MessageTypes.
     *  \param
     *      string UTF-8 encoded string message.
     */
    TRACINGIMPL_EXPORT Message(int64_t timestamp, int32_t channel_id,
            int32_t thread_id, int16_t level, int16_t modifiers, int16_t type,
            const ipl::string & string);

    //! \brief Destructor.
    ~Message()
    {
        delete[] m_data;
    }
    
    Message(const Message &)=delete;
    Message &operator = (const Message &)=delete;

    //! \brief Get the timestamp in nanoseconds when the message was created.
    int64_t getTimeStampNS() const
    {
        return m_timestamp;
    }

    //! \brief Get the trace level associated with the message \sa Levels.
    int16_t getLevel() const
    {
        return m_level;
    }

    //! \brief Get the modifiers associated with the message \sa Modifiers.
    int16_t getModifiers() const
    {
        return m_modifiers;
    }

    //! \brief Get the entity ID of the associated trace channel.
    int32_t getChannelID() const
    {
        return m_channel_id;
    }

    //! \brief Get the entity ID of the associated thread.
    int32_t getThreadID() const
    {
        return m_thread_id;
    }

    //! \brief Get the trace message type \sa MessageTypes.
    int16_t getMessageType() const
    {
        return m_message_type;
    }

    //! \brief Get a string representation of the contained payload data.
    ipl::string getMessageString() const
    {
        return ipl::string((const char *)m_data, m_data_size);
    }

    //! \brief Get the raw payload data.
    const void * getMessageData() const
    {
        return m_data;
    }

    //! \brief Get the size of the payload data.
    size_t getMessageSize() const
    {
        return m_data_size;
    }

    //! \brief Get the trace core epoch the message was created in.
    int32_t getEpoch() const
    {
        return m_epoch;
    }

    //! \brief Get the sequence number of the message.
    int32_t getSeqNum() const
    {
        return m_seq_num;
    }

    //! \brief Assign message attributes to the message using move semantic
    void forwardAttributes(MessageAttributes&& attr) {
        m_attr = std::move(attr);
    }

    //! \brief Returns assigned message attributes
    MessageAttributes& getAttributes(){
        return m_attr;
    }

protected:
    // Friend declarations for protected setter methods.
    friend class Core;
    friend class MessageBuffer;
    friend class Frontend;
    friend class FileFrontend;
    friend class tracing::protocol::ConnectionFrontendHandler;
    // Friend declaration for protected constructor.
    friend class tracing::protocol::LogDataMessage;
    friend class tracing::protocol::BulkLogDataMessage;

    /*!
     *  \brief
     *      Constructor for LogDataMessage in remote connections, which avoids
     *      copying data to often.
     *
     *  \param
     *      timestamp The timestamp in nanoseconds when this message was created.
     *      \sa osal::Time::getTimestampNS()
     *  \param
     *      channel_id The channel's entity ID this message is associated with.
     *  \param
     *      thread_id The thread's entity ID this message is associated with.
     *  \param
     *      level The filter level this message has, if the thread or the
     *      channel have a higher filter level the message will be discarded.
     *  \param
     *      modifiers \sa Modifiers.
     *  \param
     *      type Message type, \sa MessageTypes.
     *  \param
     *      data Pointer to some arbitrary data.
     *  \param
     *      len Number of bytes to contain in the message, starting from data.
     *  \param
     *      dummy Not being used.
     */
    TRACINGIMPL_EXPORT Message(int64_t timestamp, int32_t channel_id,
            int32_t thread_id, int16_t level, int16_t modifiers, int16_t type,
            void * data, size_t len, bool dummy);

    //! \brief Adjust the trace core epoch the message was created in.
    void setEpoch(int32_t epoch)
    {
        m_epoch = epoch;
    }

    //! \brief Sets the sequence number of the message.
    void setSeqNum(int32_t seq_num)
    {
        m_seq_num = seq_num;
    }

    //! \brief Sets the entity ID of the associated trace channel.
    void setChannelID(int32_t cid)
    {
        m_channel_id = cid;
    }

    //! \brief Sets the entity ID of the associated thread.
    void setThreadID(int32_t tid)
    {
        m_thread_id = tid;
    }

    //! \brief Set the timestamp in nanoseconds when this message was created.
    void setTimeStampNS(int64_t ts)
    {
        m_timestamp = ts;
    }

    /*!
     *    \brief
     *        Obfuscate the message data by replacing contents between pairs
     *        of a delimiter character with a checksum.
     *
     *        This delimiter is configurable via key 'obfuscationDelimiter' and has
     *        the value '@' by default.
     */
    void obfuscate();

protected:
    uint32_t m_marker;      //! magic marker byte sequence for post-mortem recovery
    int32_t m_seq_num;      //! Message sequence number.

    int64_t m_timestamp;    //! The timestamp the message was created at.

    int32_t m_channel_id;   //! The channel's entity ID this message is associated with.
    int32_t m_thread_id;    //! The thread's entity ID this message is associated with.
    int32_t m_epoch;        //! Trace core epoch this message was created in.

    uint8_t * m_data;       //! Pointer to the arbitrary payload data.
    size_t m_data_size;     //! Size of the payload data.

    int16_t m_level;        //! The filter level of the message.
    int16_t m_modifiers;    //! Reserved.
    int16_t m_message_type; //! The message type. This is MessageTypes::RAW in this case.


    MessageAttributes m_attr; //! A list of message attributes associated with message

    static char s_obfuscation_delimiter;
};

//! \brief Convenience typedef for shared pointers containing a raw message pointer.
typedef util::SharedPtr<Message> MessagePtr;

}

#endif /* TRACING_MESSAGE_HXX */

