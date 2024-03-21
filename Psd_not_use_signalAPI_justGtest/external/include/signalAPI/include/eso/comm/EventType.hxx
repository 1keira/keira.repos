/*
    Copyright e.solutions GmbH
    All rights reserved
    Authors:
        Stefan Bittner
*/

#ifndef COMM_EVENT_TYPE_HXX
#define COMM_EVENT_TYPE_HXX

#include <comm/comm_dso.h>

namespace comm {

    /**
     * \brief Event type.
     * Used to compare events and cast down from the event base type.
     * Derived event classes need a static EventType member.
    */
    class COMM_EXPORT EventType {
        public:
            EventType() {}
            ~EventType() {}
            bool operator==(const EventType& other) const {
                return (this==&other);
            }
            bool operator!=(const EventType& other) const {
                return !operator==(other);
            }
        private:
            // not copy-assignable
            EventType(const EventType& other);
            EventType& operator=(const EventType& other);
    };
}

#endif // COMM_EVENT_TYPE_HXX

