/*
   Copyright 2023 e.solutions GmbH
   All rights reserved
*/

#ifndef TRACING_IRCBACKEND_IIRCBACKEND_HXX
#define TRACING_IRCBACKEND_IIRCBACKEND_HXX

#include <string>
#include <map>
#include <tracing/message/Message.hxx>
#include <tracing/irc/TriggerType.hxx>

namespace tracing
{

class Frontend;
class Event;
class ITriggerListener;

//! Interfaces required by plugins loaded by the IRC backend.
class IIRCBackend
{
public:
    virtual ~IIRCBackend() = default;

    //! Get the trace core frontend instance.
    virtual Frontend & getFrontend() const = 0;

    //! The trace core name of the current process (i.e. the parameter supplied to the Util constructor).
    virtual const std::string & getCoreName() const = 0;

    using Channels = std::map<std::string, uint32_t>;

    //! Get IRC channels and their maximum message length.
    virtual Channels getChannelList() const = 0;

    //! Register a listener for the specified trigger, \sa TriggerType.
    virtual void registerTriggerListener(ITriggerListener * listener, TriggerType trigger) = 0;

    //! Unregister a listener for the specified trigger.
    virtual void deregisterTriggerListener(ITriggerListener * listener, TriggerType trigger) = 0;

    //! Trigger exporting the IRC log data.
    virtual void exportLog() = 0;
    //! Trigger deletion of the IRC log data.
    virtual void deleteLog() = 0;

    //! Whether IRC logging is enabled via Diagnosis coding.
    virtual void diagnosisEnabled(bool enabled) = 0;

    //! Whether IRC logging is enabled via privacy settings.
    virtual void privacyEnabled(bool enabled) = 0;

    //! Start IRC logging via control interface
    virtual void startIRC() = 0;

    /*!
     *  \brief
     *      Stop the IRC via control interfaces.
     *
     *  \param
     *      context An opaque pointer that will be supplied to the plugin
     *      via sendStopDone() when the IRCBackend stopped recording.
     */
    virtual void stopIRC(const void * context) = 0;

    /*!
     *  \brief
     *      Flush IRC data to persistent storage.
     *
     *  \param
     *      context An opaque pointer that will be supplied to the plugin
     *      via sendSyncDone() when the IRCBackend finished writing its data.
     */
    virtual void syncIRC(const void * context) = 0;

    /*!
     *  \brief
     *      Log an IRC message.
     *
     *  \param
     *      domain The IRC domain the message will be associated with.
     *  \param
     *      channel The IRC channel the message will be associated with.
     *  \param
     *      message The IRC message that will be stored.
     */
    virtual void logIRCMessage(const std::string & domain, const std::string & channel, const MessagePtr & message) = 0;

    //! Add an event to the IRC backend's internal event queue.
    virtual void addEvent(const Event * event) = 0;
};

} // end of namespace tracing

#endif /* TRACING_IRCBACKEND_IIRCBACKEND_HXX */

