/*
    Copyright 2023 e.solutions GmbH

    All rights reserved
*/

#ifndef TRACING_CONNECTIONSTATECHANGEDEVENT_HXX
#define TRACING_CONNECTIONSTATECHANGEDEVENT_HXX

#include <tracing/irc/Event.hxx>
#include <tracing/irc/IEventConsumer.hxx>

namespace tracing
{

class ConnectionStateChangedEvent : public Event
{
public:
    ConnectionStateChangedEvent(bool is_connected, IEventConsumer * consumer) :
        Event(EventType::CONNECTION_STATE_CHANGED_EVENT, consumer),
        m_connected(is_connected)
    {
        /* nop */
    }

    void process() const override
    {
        if (m_consumer)
            m_consumer->handleEvent(this);
    }

    bool isConnected() const
    {
        return m_connected;
    }

protected:
    bool m_connected{false};
};

} // end of namespace tracing

#endif /* TRACING_CONNECTIONSTATECHANGEDEVENT_HXX */ 
