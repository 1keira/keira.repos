/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

/*****************************************************************************/
#ifndef OSAL_ALARMIMPL_INTEGRITY_HXX
#define OSAL_ALARMIMPL_INTEGRITY_HXX
/*****************************************************************************/

#include <ipl_config.h>

#ifndef IPL_OS_INTEGRITY
#error Only valid on Integrity
#endif

#include <iplbase/time.hxx>
#include <osal/Thread.hxx>

#include <INTEGRITY.h>

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
            static void* timerFct (void* context);

        protected:
            void stop();
            static void timer_signal(int signal, void *context);

            void (* callback)(void *);
            void *context;

        private:
            Task         timer_task;
            Clock        clock;
            Activity     actvity;
        };
    };

/*****************************************************************************/

}  // end of namespace osal

/*****************************************************************************/
#endif
