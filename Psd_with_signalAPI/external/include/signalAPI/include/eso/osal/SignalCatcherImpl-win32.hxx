/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

/****************************************************************************/
#ifndef OSAL_SIGNALCATCHERIMPL_WIN32_HXX
#define OSAL_SIGNALCATCHERIMPL_WIN32_HXX
/****************************************************************************/

#include <ipl_config.h>

#ifndef IPL_OS_WIN32
#error Only valid on Win32
#endif

#include <common/Shared.hxx>
#include <common/types/vector.hxx>
#include "SignalCatcherBase.hxx"
#include "SignalQueue.hxx"
#include "SignalDispatcher.hxx"

/****************************************************************************/

namespace osal {

/****************************************************************************/

// http://stackoverflow.com/questions/16826097/equivalent-to-sigint-posix-signal-for-catching-ctrlc-under-windows-mingw

    /*!
        \internal
        \brief System dependent part of SignalCatcher, Windows incarnation
    */
    class SignalCatcherImpl: public SignalCatcherBase {

    public:
        SignalCatcherImpl(int signal,
                          const ipl::Shared<SignalDispatcher>::Ptr &signaldispatcher,
                          SignalQueue &queue,
                          SignalQueue::Callback callback, void *context);
        ~SignalCatcherImpl();

    protected:
        static BOOL console_ctrl_handler(DWORD event);

        static Mutex mutex;
        static unsigned refs;
        static ipl::vector<SignalCatcherImpl *> handlers;

        SignalQueue &queue;
        SignalQueue::Callback callback;
        void *context;
    };

/****************************************************************************/

}  // end of namespace osal

/****************************************************************************/
#endif
