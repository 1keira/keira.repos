/*
    Copyright 2020, 2023 e.solutions GmbH
    All rights reserved
*/

#ifndef TRACING_IRCBACKEND_EVENTCONSUMER_HXX
#define TRACING_IRCBACKEND_EVENTCONSUMER_HXX

namespace tracing
{

class Event;

/*!
 *    \brief
 *        Interface class that must be implemented by a project-specific software
 *        component. Implementations can be called by specific events for processing.
 */
class IEventConsumer
{
public:
    //! \brief Virtual destructor.
    virtual ~IEventConsumer() = default;
    //! \brief Interface to be implemented by derived consumers.
    virtual void handleEvent(const Event * event) = 0;
};

}

#endif // TRACING_IRCBACKEND_EVENTCONSUMER_HXX
