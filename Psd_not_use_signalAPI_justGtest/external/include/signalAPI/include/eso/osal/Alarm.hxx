/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

/*****************************************************************************/
#ifndef OSAL_ALARM_HXX
#define OSAL_ALARM_HXX
/*****************************************************************************/

#include <ipl_config.h>

#if defined(IPL_OS_POSIX)
#if defined(IPL_OS_QNX)
#include "AlarmImpl-qnx.hxx"
#else
#include "AlarmImpl-posix.hxx"
#endif
#elif defined(IPL_OS_WIN32)
#include "AlarmImpl-win32.hxx"
#elif defined(IPL_OS_INTEGRITY)
#include "AlarmImpl-integrity.hxx"
#else
#error Unsupported OS
#endif

#include <osal/osal_dso.h>
#include <osal/signals.h>
#include <osal/Message.hxx>
#include <common/Shared.hxx>
#include <iplbase/time.hxx>
#include <iplbase/exceptions.hxx>

#include <map>

/*****************************************************************************/

namespace osal {

/*****************************************************************************/

    /*!
        \brief Rings later

        This is a timer that can be set to call some callback
        \cond NOT_YET
        (or schedule to some queue to call it)
        \endcond
        after some delay.
        All Alarms share a Timer object that does the real work of
        multiplexing a single OS timer.
        Several Timers can be used for different priorities or similar.

        Note that this is one-shot -- if you need some periodic alarm,
        call set() from your callback.
    */
    class OSAL_EXPORT Alarm: public AlarmImpl {

    public:

        class OSAL_EXPORT Timer: public TimerImpl {

        public:
#ifdef IPL_OS_WIN32
            //! \brief <b>Don't use, ever!</b>
            //!
            //! This is just a workaround for the Microsoft compiler's
            //! broken template instantiation. Ignore.
            Timer() {}
#endif
            Timer(int posix_signal, const char *threadname="Timer",
                  const osal::Thread::Priority &threadprio=0) IPL_NOEXCEPT;
            ~Timer() IPL_NOEXCEPT;

            void add(Alarm *alarm, const iplbase::Duration &delay) IPL_NOEXCEPT;
            void remove(Alarm *alarm) IPL_NOEXCEPT;

        protected:
            static void ring(void *context);

            threadsafe::Mutex mutex;
            typedef std::map<Alarm *, iplbase::TimePoint> Deadlines;
            Deadlines deadlines;
            iplbase::TimePoint next_deadline;
        };
        friend class Timer;

        typedef Message::Callback::Procedure Procedure;  // void (*Procedure)(void *context);

        //! \brief Set up Alarm to call \a procedure with argument \a context upon ring
        Alarm(Procedure procedure, void *context) IPL_NOEXCEPT:
            timer(DEFAULT_TIMER), queue(nullptr), procedure(procedure),
            context(context) {}
        //! \brief Set up Alarm to insert a call to \a procedure with argument
        //! \a context into \a queue upon ring
        Alarm(Message::UnlimitedSink &queue, Procedure procedure, void *context) IPL_NOEXCEPT:
            timer(DEFAULT_TIMER), queue(&queue), procedure(procedure),
            context(context) {}
        //! \brief Set up Alarm to call \a procedure with argument \a context upon ring
        //! and to use the underlying \a timer
        Alarm(Timer &timer, Procedure procedure, void *context) IPL_NOEXCEPT:
            timer(&timer), queue(nullptr), procedure(procedure),
            context(context) {}
        //! \brief Set up Alarm to insert a call to \a procedure with argument
        //! \a context into \a queue upon ring and to use the underlying \a timer
        Alarm(Timer &timer, Message::UnlimitedSink &queue, Procedure procedure,
              void *context) IPL_NOEXCEPT:
            timer(&timer), queue(&queue), procedure(procedure),
            context(context) {}
        //! \brief Set up Alarm to call \a procedure with argument \a context upon ring
        //! and to use the underlying \a timer
        Alarm(const ipl::Shared<Timer>::Ptr &timer, Procedure procedure,
              void *context) IPL_NOEXCEPT:
            timer(timer), queue(nullptr), procedure(procedure),
            context(context) {}
        //! \brief Set up Alarm to insert a call to \a procedure with argument
        //! \a context into \a queue upon ring and to use the underlying \a timer
        Alarm(const ipl::Shared<Timer>::Ptr &timer,
              Message::UnlimitedSink &queue,
              Procedure procedure, void *context) IPL_NOEXCEPT:
            timer(timer), queue(&queue), procedure(procedure),
            context(context) {}
        ~Alarm() IPL_NOEXCEPT { cancel(); }

        //! \brief Start or reset timer
        void set(const iplbase::Duration &delay) IPL_NOEXCEPT {
            timer->add(this, delay);
        }
        //! \brief Stop timer, it is guaranteed not to ring after this returns
        //! \b except when called from a timer callback
        void cancel() IPL_NOEXCEPT { timer->remove(this); }

        class DefaultTimer: public Timer {
        public:
            DefaultTimer(): Timer(IPL_TIMER_POSIX_SIGNAL_DEFAULT) {}
        };

        //! \brief The Timer used when you don't specify one explicitly
        static ipl::Shared<DefaultTimer> DEFAULT_TIMER;

    protected:
        ipl::Shared<Timer>::Ptr timer;
        Message::UnlimitedSink *queue;
        Procedure procedure;
        void *context;
    };

/*****************************************************************************/

}  // end of namespace osal

/*****************************************************************************/
#endif
