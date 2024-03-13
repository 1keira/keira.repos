/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

/*****************************************************************************/
#ifndef OSAL_ALARMIMPL_WIN32_HXX
#define OSAL_ALARMIMPL_WIN32_HXX
/*****************************************************************************/

#include <ipl_config.h>

#ifndef IPL_OS_WIN32
#error Only valid on Win32
#endif

#include <iplbase/win32.h>
#include <iplbase/time.hxx>
#include <osal/Dispatcher.hxx>
#include <osal/SignalQueue.hxx>
#include <osal/SignalCatcher.hxx>
#include <osal/Thread.hxx>

/*****************************************************************************/

namespace osal {

/*****************************************************************************/

    /*!
        \internal
        \brief System dependent part of Alarm and Alarm::Timer, Windows incarnation
        (callback function based)
    */
    class AlarmImpl {

    public:

        class TimerImpl {

        public:
            //! \brief <b>Don't use, ever!</b>
            //!
            //! This is just a workaround for the Microsoft compiler's
            //! broken template instantiation. Ignore.
            TimerImpl() {}
            TimerImpl(int posix_signal,
                      const osal::Thread::Priority &threadprio,
                      const char *threadname,
                      void (* callback)(void *), void *context);
            ~TimerImpl();

            void next_ring(const iplbase::Duration &delay);

        protected:
            void stop();
            static void CALLBACK timeCallback(UINT timer_id,
                                              UINT msg, DWORD_PTR context,
                                              DWORD_PTR, DWORD_PTR);

            void (* callback)(void *);
            void *context;
            UINT timer_id;
        };
    };

/*****************************************************************************/

}  // end of namespace osal

/*****************************************************************************/
#endif
