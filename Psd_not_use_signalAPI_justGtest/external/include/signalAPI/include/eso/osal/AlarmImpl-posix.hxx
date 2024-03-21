/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

/*****************************************************************************/
#ifndef OSAL_ALARMIMPL_POSIX_HXX
#define OSAL_ALARMIMPL_POSIX_HXX
/*****************************************************************************/

#include <ipl_config.h>

#ifndef IPL_OS_POSIX
#error Only valid on Posix
#endif

#include <iplbase/time.hxx>
#include <osal/Dispatcher.hxx>
#include <osal/SignalQueue.hxx>
#include <osal/SignalCatcher.hxx>
#include <osal/Thread.hxx>

#include <time.h>

/*****************************************************************************/

namespace osal {

/*****************************************************************************/

    /*!
        \internal
        \brief System dependent part of Alarm and Alarm::Timer, Posix incarnation
        (i.e. signal based)
    */
    class AlarmImpl {

    public:

        class TimerImpl {

        public:
            TimerImpl(int posix_signal,
                      const osal::Thread::Priority &threadprio,
                      const char *threadname,
                      void (* callback)(void *), void *context);
            ~TimerImpl();

            void next_ring(const iplbase::Duration &delay);

        protected:
            void stop();
            static void timer_signal(int signal, void *context);

            SignalDispatcher dispatcher;
            SignalCatcher signalcatcher;
            void (* callback)(void *);
            void *context;

            timer_t timer_id;
        };
    };

/*****************************************************************************/

}  // end of namespace osal

/*****************************************************************************/
#endif
