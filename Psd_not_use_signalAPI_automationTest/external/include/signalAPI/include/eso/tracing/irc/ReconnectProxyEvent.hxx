/*
    Copyright 2023 e.solutions GmbH

    All rights reserved
*/

#ifndef TRACING_RECONNECTPROXYEVENT_HXX
#define TRACING_RECONNECTPROXYEVENT_HXX

#include <tracing/irc/Event.hxx>
#include <tracing/irc/IEventConsumer.hxx>

namespace tracing
{

class ReconnectProxyEvent : public Event
{
public:
    ReconnectProxyEvent(IEventConsumer * consumer) :
        Event(EventType::RECONNECTPROXY_EVENT, consumer)
    {
        /* nop */
    }

    void process() const override
    {
        if (m_consumer)
            m_consumer->handleEvent(this);
    }
};


} // end of namespace tracing

#endif /* TRACING_RECONNECTPROXYEVENT_HXX */ 
