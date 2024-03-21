/*
    Copyright 2020, 2023 e.solutions GmbH
    All rights reserved
*/

#ifndef TRACING_IRCBACKEND_ITRIGGERLISTENER_HXX
#define TRACING_IRCBACKEND_ITRIGGERLISTENER_HXX

#include <stddef.h>
#include <tracing/irc/TriggerType.hxx>

namespace tracing
{
/*!
 *    \brief
 *        Interface class for an IRC trigger listener.

 *        IRC components interested in IRC events need to implement this interface.
 */
class ITriggerListener
{
public:
    //! \brief Virtual destructor.
    virtual ~ITriggerListener() = default;

    /*!
     *    \brief
     *        An IRC event has been received and listeners are notified.
     *
     *    \param
     *        trigger The trigger type.
     *    \param
     *        data Optional data provided with the event.
     *    \param
     *        datalen The length of data provided with the event.
     */
    virtual void triggerOccured(TriggerType trigger, const void * data, size_t datalen) = 0;
};

} // end of namespace tracing

#endif /* TRACING_IRCBACKEND_ITRIGGERLISTENER_HXX */
