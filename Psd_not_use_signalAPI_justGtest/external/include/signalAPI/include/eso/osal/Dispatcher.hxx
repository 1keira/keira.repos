/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

/****************************************************************************/
#ifndef OSAL_DISPATCHER_HXX
#define OSAL_DISPATCHER_HXX
/****************************************************************************/

#include <osal/osal_dso.h>
#include <osal/Message.hxx>
#include <osal/Mutex.hxx>
#include <osal/Condition.hxx>
#include <common/Macros.hxx>
#include <common/Tag.hxx>
#include <iplbase/exceptions.hxx>

#include <list>
#include <deque>

/****************************************************************************/

namespace osal {

/****************************************************************************/

    /*!
        \brief Manage a set of message queues and a set of message handlers
        and get messages from the former to the latter
    */
    class OSAL_EXPORT Dispatcher {

    public:

        class Notifier;

        class VanillaQueue;
        class VanillaNotifier;

        //! Note: \p notifier must be the same as handed to all queues
        explicit Dispatcher(Notifier &notifier) IPL_NOEXCEPT:
            running(true), notifier(notifier) {}

        /*!
            \brief Add a message queue so that it is handled
            before any other already added

            Don't call this during run()!
        */
        void add_high_prio(Message::Source &queue) IPL_NOEXCEPT {
            queues.push_front(&queue);
        }
        /*!
            \brief Add a message queue so that it is handled
            after any other already added

            Don't call this during run()!
        */
        void add_low_prio(Message::Source &queue) IPL_NOEXCEPT {
            queues.push_back(&queue);
        }
        /*!
            \brief Add message handler

            Must not be called during any Message::get_handled_by().
            Preferrably call this from the handler's constructor.
        */
        void add(Message::Handler *handler) IPL_NOEXCEPT {
            IPL_MUTEX_LOCK_OR_ABORT(mutex);
            handlers.push_back(handler);
            IPL_MUTEX_UNLOCK_OR_ABORT(mutex);
        }
        /*!
            \brief Add message handler

            Must not be called during any Message::get_handled_by().
            Preferrably call this from the handler's constructor.
        */
        void add(Message::Handler &handler) IPL_NOEXCEPT { add(&handler); }
        /*!
            \brief Remove message handler

            Must not be called during any Message::get_handled_by().
            Preferrably call this from the handler's constructor.
        */
        void remove(Message::Handler *handler) IPL_NOEXCEPT {
            IPL_MUTEX_LOCK_OR_ABORT(mutex);
            handlers.remove(handler);
            IPL_MUTEX_UNLOCK_OR_ABORT(mutex);
        }
        /*!
            \brief Remove message handler

            Must not be called during any Message::get_handled_by().
            Preferrably call this from the handler's constructor.
        */
        void remove(Message::Handler &handler) IPL_NOEXCEPT { remove(&handler); }
        /*!
            \brief The Dispatcher's main loop

            The machinery only works while this is executed.
            
            This is not threadsafe, i.e. run it only once a time.
        */
        void run() IPL_NOEXCEPT;
        /*!
            \brief Signal the main loop to exit
        */
        void stop() IPL_NOEXCEPT;
        /*!
            \brief Direct entry point for osal::Thread

            Pass this Dispatcher as \a context.
            Note that the Thread's shutdown system won't work,
            call stop() on the Dispatcher instead.
            
            Calls run() under the hood.
        */
        static void main(void *context) IPL_NOEXCEPT;

    protected:
        //! \brief Fully handle and dispose of a single \a message
        void dispatch(Message *message);

        osal::Mutex mutex;
        volatile bool running;
        Notifier &notifier;
        typedef std::list<Message::Source *> Queues;
        Queues queues;
        typedef std::list<Message::Handler *> Handlers;
        Handlers handlers;
    };

/****************************************************************************/

    /*!
        \brief Interface that can notify you of whatever

        You may be tempted to ignore this for a condition variable, a mutex,
        a flag and a loop, but a Notifier need not be built that way.
        Instead it \e can even be usable from a signal handler.
    */
    class OSAL_EXPORT Dispatcher::Notifier {

    public:
        virtual ~Notifier()=default;  // Just keeping the compiler happy...
        //! \brief Block until someone has called signal()
        virtual void wait() IPL_NOEXCEPT=0;
        //! \brief Unblock pending or next call to wait()
        virtual void signal() IPL_NOEXCEPT=0;
    };

/****************************************************************************/

    /*!
        \brief Simple, deque based implementation of a Queue
    */
    class OSAL_EXPORT Dispatcher::VanillaQueue:
        public Message::Source, public Message::UnlimitedSink{

    public:
        //! Note: \p notifier must be the same object as handed to the
        //! corresponding Dispatcher. It is used to communicate that
        //! something has been pushed and can now be popped.
        explicit VanillaQueue(Dispatcher::Notifier &notifier) IPL_NOEXCEPT:
            notifier(notifier) {}
        Message *pop_nonblock () IPL_NOEXCEPT override;
        using UnlimitedSink::push;
        void push(Message *message) IPL_NOEXCEPT override;
        void forget(Message::Pusher *pusher) IPL_NOEXCEPT override;

    protected:
        Dispatcher::Notifier &notifier;
        Mutex mutex;
        std::deque<Message *> buffer;
    };

/****************************************************************************/

    /*!
        \brief Simple, condition based implementation of a Notifier
    */
    class OSAL_EXPORT Dispatcher::VanillaNotifier: public Dispatcher::Notifier {

    public:
        VanillaNotifier() IPL_NOEXCEPT: signalled(false) {}

        void wait() IPL_NOEXCEPT override;
        void signal() IPL_NOEXCEPT override;

    protected:
        Mutex mutex;
        Condition condition;
        bool signalled;
    };

/****************************************************************************/

}  // end of namespace osal

/****************************************************************************/
#endif
