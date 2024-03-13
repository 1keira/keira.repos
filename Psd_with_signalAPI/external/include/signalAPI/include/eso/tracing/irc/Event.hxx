/*
    Copyright 2020, 2023 e.solutions GmbH
    All rights reserved
*/

#ifndef TRACING_IRCBACKEND_EVENT_HXX
#define TRACING_IRCBACKEND_EVENT_HXX

#include <ipl_config.h>

#include <cstddef>
#include <string>
#include <iplbase/dso_macros.h>
#include <tracing/irc/TriggerType.hxx>


#if defined(IRCBackend_EXPORTS) || defined(tracing_EXPORTS) && defined(BUILTIN_IRCBACKEND)
#   define IRC_LIB_EXPORT IPL_EXPORT_MARKER
#elif defined(IPL_STATIC_LIBS)
#   define IRC_LIB_EXPORT IPL_STATICLINK_MARKER
#else
#   define IRC_LIB_EXPORT IPL_IMPORT_MARKER
#endif

namespace tracing
{

class IEventConsumer;

/*!
 *    \brief
 *        This class defines an abstract event, triggering some IRC functionality.
 */
class IRC_LIB_EXPORT Event
{
public:

    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //  NOTE: When Change this enum also the array
    //  EVENT_NAMES in Event.cxx has to be adapted
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //! \brief Enumeration for IRC input events
    enum class EventType
    {
        UNDEFINED_EVENT = 0,
        SHUTDOWN_EVENT,
        ASILOGTRANSFER_EVENT,
        RECONNECTPROXY_EVENT,
        CONNECTION_STATE_CHANGED_EVENT,
        TRACE_CONNECT_EVENT,
        TRIGGER_EVENT,
        INFOTAINMENTREC_LOG_EVENT,
        SE_SHUTDOWN_REQUESTED_EVENT,
        SE_SHUTDOWN_CANCELLED_EVENT,
        DIAGNOSIS_DATA_EVENT,
        IRCCONTROL_EVENT,
        IRCCONTROL_LOG_EVENT,
        IRCPRIVACY_EVENT,
        LAST_EVENT_NUMBER
    };

    //! \brief Default constructor.
    Event() :
        m_type(EventType::UNDEFINED_EVENT),
        m_consumer(nullptr)
    { /* nop */ }

    /*!
     *    \brief
     *        Constructor.
     *
     *    \param
     *        type The event type.
     *    \param
     *        consumer The consumer of the event.
     */
    Event(EventType type, IEventConsumer * consumer = nullptr) :
        m_type(type),
        m_consumer(consumer)
    { /* nop */ }

    //! \brief Virtual destructor.
    virtual ~Event() { /* nop */ }

    //! \brief Move Constructor, disabled.
    Event(Event&& other)=delete;
    //! \brief Move assignment operator, disabled.
    Event& operator=(Event&& other)=delete;

    /*!
     *    \brief
     *        Check for matching \sa EventType.
     *
     *    \param
     *        is EventType to check.
     *    \return
     *        true when matching, otherwise false.
     */
    bool is(EventType is) const
    {
        return (m_type == is);
    }

    //! \brief Get the \sa EventType.
    EventType is() const
    {
        return m_type;
    }

    //! \brief Default event handling.
    virtual void process() const { /* nop */ }

    //! \brief Get the default event type.
    virtual int32_t type() const { return 0; }

    //! \brief Get the \sa IEventConsumer.
    IEventConsumer * consumer() const { return m_consumer; }

    //! \brief Get the event name.
    virtual std::string toString() const;

protected:
    EventType m_type;
    IEventConsumer * m_consumer;
};

} // end of namespace tracing

#endif /* TRACING_IRCBACKEND_EVENT_HXX */
