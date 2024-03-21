/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

/*****************************************************************************/
#ifndef COMMON_TAG_HXX
#define COMMON_TAG_HXX
/*****************************************************************************/

#include <ipl_config.h>
#include <iplbase/NonCopyable.hxx>
#include "ipl_namespace.hxx"

/*****************************************************************************/

namespace IPL_NAMESPACE {

/*****************************************************************************/

    /*!
        \brief Thing that compares equal to itself and unequal to everything else

        This is a means to identify ...things without the need to manage
        numeric IDs in some central manner.
        It is mainly meant for poor-man's RTTI.
        For every class (or whatever) that you want to recognize,
        create a Tag object somewhere as an ID.
        When you refer to a specific class, pass this information as
        \em reference to the Tag object.

        For example the \ref persistence::Job "Persistence Service event handlers"
        do something like this:
        \code
        class EventHandler {
        public:
            // return NULL for non-matching type, mimicking dynamic_cast:
            virtual void *cast(const Tag &type)=0;
        };

        class FooHandler: public EventHandler {
        public:
            static Tag TYPE;
            virtual void *cast(const Tag &type) { return type==TYPE? this : NULL; }

            // some unique interface:
            void foo(int i);
        };

        Tag FooHandler::TYPE;  // This represents the FooHandler type

        class BarHandler: public EventHandler {
        public:
            static Tag TYPE;
            virtual void *cast(const Tag &type) { return type==TYPE? this : NULL; }

            // some unique interface:
            void bar();
            void baz(bool imeanit);
        };

        Tag BarHandler::TYPE;  // This represents the BarHandler type

        class Event {
        public:
            // have the handler do the right thing or not, depending on type
            virtual void process(EventHandler &handler)=0;
        };

        class FooEvent: public Event {
        public:
            virtual void process(EventHandler &handler) {
                // only a FooHandler has the method foo
                void *p=handler.cast(FooHandler::TYPE);
                // now p points to an EventHandler or is NULL
                if(p) ((FooHandler *)p)->foo(whatever);
            }
        };

        class BarEvent: public Event {
        public:
            virtual void process(EventHandler &handler) {
                // only a BarHandler has the method bar
                void *p=handler.cast(BarHandler::TYPE);
                // now p points to an EventHandler or is NULL
                if(p) ((BarHandler *)p)->bar();
            }
        };

        class BazEvent: public Event {
        public:
            virtual void process(EventHandler &handler) {
                // only a BarHandler has the method baz
                void *p=handler.cast(BarHandler::TYPE);
                // now p points to an EventHandler or is NULL
                if(p) ((BarHandler *)p)->baz(true);
            }
        };

        void handle(Event &event)
        {
            // passes the event to all handlers that can handle it,
            // having called the individual method fitting the event:
            for(Handlers::iterator i=handler.begin(); i!=handlers.end(); i++)
                event->process(handler);
        }
        \endcode
    */
    class Tag: public iplbase::NonCopyable {
    public:
        bool operator==(const Tag& other) const IPL_NOEXCEPT {
            return this == &other;
        }
        bool operator!=(const Tag& other) const IPL_NOEXCEPT {
            return this != &other;
        }
    };

/*****************************************************************************/

}  // end of namespace IPL_NAMESPACE

/*****************************************************************************/
#endif
