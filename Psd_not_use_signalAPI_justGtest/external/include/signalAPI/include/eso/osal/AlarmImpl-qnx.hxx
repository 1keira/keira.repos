/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

/*****************************************************************************/
#ifndef OSAL_ALARMIMPL_QNX_HXX
#define OSAL_ALARMIMPL_QNX_HXX
/*****************************************************************************/

#include <ipl_config.h>

#ifndef IPL_OS_QNX
#error Only valid on QNX
#endif

#include <iplbase/time.hxx>
#include <common/Shared.hxx>
#include <osal/Thread.hxx>
#include <osal/qnx/QnxSelfPulseChannel.hxx>

#include <time.h>

/*****************************************************************************/

namespace osal {

/*****************************************************************************/

    /*!
        \internal
        \brief System dependent part of Alarm and Alarm::Timer, ONX incarnation
        (i.e. pulse based)
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

            timer_t timer_id;
            ipl::Shared<QnxSelfPulseChannel>::Ptr channel;
            int code;
        };
    };

/*****************************************************************************/

}  // end of namespace osal

/*****************************************************************************/
#endif
