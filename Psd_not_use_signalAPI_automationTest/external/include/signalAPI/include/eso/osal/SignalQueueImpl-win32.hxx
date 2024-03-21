/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

/****************************************************************************/
#ifndef OSAL_SIGNALQUEUEIMPL_WIN32_HXX
#define OSAL_SIGNALQUEUEIMPL_WIN32_HXX
/****************************************************************************/

#include <ipl_config.h>

#ifndef IPL_OS_WIN32
#error Only valid on Win32
#endif

#include <osal/osal_dso.h>

#include "SignalQueueBase.hxx"
#include "Message.hxx"
#include "Dispatcher.hxx"

#include <iplbase/win32.h>
// #include <common/Macros.hxx>
// #include <common/const_assert.hxx>
//
// #include <common/types/list.hxx>

/****************************************************************************/

namespace osal {

/****************************************************************************/

    /*!
        \internal
        \brief System dependent part of SignalQueue, Windows incarnation
    */
    class OSAL_EXPORT SignalQueueImpl:
        public SignalQueueBase, public Dispatcher::VanillaQueue {

    public:

        typedef Dispatcher::VanillaNotifier NotifierImpl;

        SignalQueueImpl(NotifierImpl &notifier): VanillaQueue(notifier) {}

        using VanillaQueue::push;
        void push(int signal, Callback callback, void *context);
    };

/****************************************************************************/


/****************************************************************************/

}  // end of namespace osal

/****************************************************************************/
#endif
