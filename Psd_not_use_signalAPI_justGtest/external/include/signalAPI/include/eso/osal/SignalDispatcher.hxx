/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

/****************************************************************************/
#ifndef OSAL_SIGNALDISPATCHER_HXX
#define OSAL_SIGNALDISPATCHER_HXX
/****************************************************************************/

#include <common/Shared.hxx>
#include <osal/osal_dso.h>
#include <osal/Dispatcher.hxx>
#include <osal/SignalQueue.hxx>
#include <osal/Thread.hxx>

/****************************************************************************/

namespace osal {

/****************************************************************************/

    /*!
        \brief Convenient package of a Dispatcher, a Thread servicing it,
        a SignalQueue and a SignalNotifier
    */
    class OSAL_EXPORT SignalDispatcher {

    public:

        SignalDispatcher(const char *threadname="osal::SignalDispatcher",
                         Thread::Priority prio=0):
            queue(notifier), stopped(false), dispatcher(notifier),
            thread(dispatcher.main, &dispatcher, threadname, prio, prio) {
            dispatcher.add_high_prio(queue);
            thread.start();
        }
        ~SignalDispatcher() { stop(); }

        //! \brief Stop and join internal thread, idempotently
        //!
        //! You can call this as often as you want, but only the first call
        //! is guaranteed not to return before the thread is actually joined.
        void stop() {
            if(stopped)
                return;
            stopped=true;
            dispatcher.stop();
            thread.join();
        }

        //! \brief Add a message queue so that it is handled before any other already added
        void add_high_prio(Message::Source &queue) { dispatcher.add_high_prio(queue); }
        //! \brief Add a message queue so that it is handled after any other already added
        void add_low_prio(Message::Source &queue) { dispatcher.add_low_prio(queue); }
        //! \brief Add message handler
        void add(Message::Handler *handler) { dispatcher.add(handler); }
        //! \brief Add message handler
        void add(Message::Handler &handler) { dispatcher.add(handler); }
        //! \brief Remove message handler
        void remove(Message::Handler *handler) { dispatcher.remove(handler); }
        //! \brief Remove message handler
        void remove(Message::Handler &handler) { dispatcher.remove(handler); }

        //! \brief Default instance to be used by normal signal handling,
        //! normal-priority timers and everybody who wants to share it
        static ipl::Shared<SignalDispatcher> &DEFAULT;

        SignalQueue::Notifier notifier;
        SignalQueue queue;

    protected:
        bool stopped;
        Dispatcher dispatcher;
        Thread thread;
    };

/****************************************************************************/

}  // end of namespace osal

/****************************************************************************/
#endif
