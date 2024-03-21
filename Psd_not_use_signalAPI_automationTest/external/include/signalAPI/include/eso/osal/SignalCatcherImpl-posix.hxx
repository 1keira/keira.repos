/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

/****************************************************************************/
#ifndef OSAL_SIGNALCATCHERIMPL_POSIX_HXX
#define OSAL_SIGNALCATCHERIMPL_POSIX_HXX
/****************************************************************************/

#include <ipl_config.h>

#ifndef IPL_OS_POSIX
#error Only valid on Posix
#endif

#include <threadsafe/AtomicCounter.hxx>
#include <common/Macros.hxx>
#include "SignalCatcherBase.hxx"
#include "SignalQueue.hxx"

#include <unistd.h>
#include <signal.h>

/****************************************************************************/

namespace osal {

/****************************************************************************/

    /*!
        \internal
        \brief System dependent part of SignalCatcher, Posix incarnation
    */
    class OSAL_EXPORT SignalCatcherImpl: public SignalCatcherBase {

    public:
        SignalCatcherImpl(int signal,
                          const ipl::Shared<SignalDispatcher>::Ptr &signaldispatcher,
                          SignalQueue &queue,
                          SignalQueue::Callback callback, void *context):
            SignalCatcherBase(signal, signaldispatcher)
        {
            IPL_ASSERT(0<=signal);
            IPL_ASSERT(signal<IPL_NSIGNALS);
            queue.sign_on(signal, callback, context);
            info[signal].spin_lock();
            info[signal].queue=&queue;
            info[signal].unlock();

            struct sigaction action;
            memset(&action, 0, sizeof(action));
            action.sa_handler=enqueue_signal;
// nope, would switch to sa_sigaction            action.sa_flags=SA_SIGINFO;  // make queued, needed on QNX
            sigfillset(&action.sa_mask);
// Somewhat heavy handed workaround for QNX not supporting it:
#ifdef SA_RESTART
            action.sa_flags|=SA_RESTART;  // avoid EINTR where possible
#endif
            installed=sigaction(signal, &action, &old_action)==0;
            IPL_ASSERT((old_action.sa_flags & SA_SIGINFO) || old_action.sa_handler==SIG_DFL || old_action.sa_handler==SIG_IGN);
            IPL_ASSERT(!(old_action.sa_flags & SA_SIGINFO) || old_action.sa_sigaction==(void (*) (int, siginfo_t *, void *))SIG_DFL || old_action.sa_sigaction==(void (*) (int, siginfo_t *, void *))SIG_IGN);
        }

        ~SignalCatcherImpl() {
            if(installed) {
                struct sigaction action;
                memset(&action, 0, sizeof(action));
                if(sigaction(signal, &old_action, &action)) // BRANCH_COVERAGE_UNTESTABLE
                    IPL_ASSERT(true && "resetting signal failed");
                else
                    IPL_ASSERT(action.sa_handler==enqueue_signal);
            }
            info[signal].spin_lock();
            SignalQueue *queue=info[signal].queue;
            info[signal].queue=NULL;
//             info[signal].enabled=false;
            info[signal].unlock();
            queue->sign_off(signal);
        }

        static void enqueue_signal(int signal);

    protected:

        struct Info {
            threadsafe::AtomicCounter locked;
            SignalQueue *queue;

            Info(): locked(0), queue(NULL)/*, enabled(false)*/ {}
            //! \brief Needed because osal::SpinLock is not async-safe
            void spin_lock() { while(locked.exchange_if(1, 0)); } // BRANCH_COVERAGE_UNTESTABLE
            //! \brief Needed because osal::SpinLock is not async-safe
            void unlock()    { locked.exchange(0); }
        };
        static Info info[];

        struct sigaction old_action;
        bool installed;
    };

/****************************************************************************/

}  // end of namespace osal

/****************************************************************************/
#endif
