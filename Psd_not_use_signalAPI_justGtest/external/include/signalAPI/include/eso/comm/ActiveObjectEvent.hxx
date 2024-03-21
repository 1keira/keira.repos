/*
    Copyright e.solutions GmbH
    All rights reserved
    Authors:
        Stefan Bittner
*/

#ifndef COMM_AO_EVENT_HXX
#define COMM_AO_EVENT_HXX

#include <util/SharedPtr.hxx>
#include <comm/EventType.hxx>
#include <comm/comm_dso.h>

namespace comm {

    /**
        \brief Interface for events handled in active objects
    */
    class COMM_EXPORT ActiveObjectEvent {
        public:
            ActiveObjectEvent() {}
            virtual ~ActiveObjectEvent() {}

            /** \brief Processes the event.
                \returns true, if an error occurred, false otherwise. If true is returned an error
                was raised.
            */
            virtual bool process() = 0;

            /** \brief Tests if this event is of a certain type. */
            virtual bool isA (const EventType&) const = 0;

    };

    typedef util::SharedPtr<ActiveObjectEvent> ActiveObjectEventPtr;

} // namespace comm

#endif // COMM_AO_EVENT_HXX

