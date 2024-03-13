/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef TRACING_IEVENTLISTENER_HXX
#define TRACING_IEVENTLISTENER_HXX

#include <string>

namespace tracing
{

/*!
 *    \brief
 *        Interface class for an event listener listening to generic trace core events.
 *
 *        After registration via \sa registerEventListener at frontend or backend for
 *        certain event(s) it will be notified via \sa event method.
 */
class IEventListener
{
public:
    //! \brief Virtual destructor.
    virtual ~IEventListener() {/* nop */}

    /*!
     *    \brief
     *        Notification about an event.
     *    \param
     *        name The event name.
     */
    virtual void event(const std::string & name) = 0;
};

} // end of namespace tracing

#endif /* TRACING_IEVENTLISTENER_HXX */

