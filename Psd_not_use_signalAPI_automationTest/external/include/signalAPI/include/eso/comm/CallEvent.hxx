/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/


#ifndef COMM_CALL_EVENT_HXX
#define COMM_CALL_EVENT_HXX

#include <comm/comm_dso.h>
#include <comm/commtypes.hxx>
#include <comm/ActiveObjectEvent.hxx>
#include <comm/Connection.hxx>

namespace comm {


    /** \brief An event for method calls. */
    class COMM_EXPORT CallEvent : public ActiveObjectEvent {
        public:

            /** \brief An abstract identifier for a method in a comm interface. */
            class COMM_EXPORT CallID {
                public:
                    CallID() : m_instance{nullptr}, m_method(0) {}
                    ~CallID() {}
                    bool operator==(const CallID& other) const;
                    void assign(void* inst, const comm::OpaqueMethodID& m);
                private:
                    void*                   m_instance;
                    comm::OpaqueMethodID    m_method;
            };


            CallEvent() {}
            ~CallEvent() override {}

            bool isA(const EventType& other) const override { return m_type==other; }

            virtual bool calls(const CallID&) const {return false;}

            virtual const ConnectionPtr& getConnection() const {
                static ConnectionPtr invalid_connection;
                return invalid_connection;
            }

            static const EventType& getType() { return m_type; }
        private:
            static const EventType  m_type;
    };

    typedef util::SharedPtr<CallEvent> CallEventPtr;
}
#endif // COMM_CALL_EVENT_HXX

