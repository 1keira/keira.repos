/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

/****************************************************************************/
#ifndef OSAL_SIGNALQUEUE_HXX
#define OSAL_SIGNALQUEUE_HXX
/****************************************************************************/

#include <ipl_config.h>

#if defined IPL_OS_POSIX
#if defined IPL_OS_QNX
#include "SignalQueueImpl-qnx.hxx"
#else
#include "SignalQueueImpl-posix.hxx"
#endif
#elif defined IPL_OS_WIN32
#include "SignalQueueImpl-win32.hxx"
#elif defined IPL_OS_INTEGRITY
#include "SignalQueueImpl-integrity.hxx"
#else
#error Unsupported OS
#endif

#include <osal/osal_dso.h>

#include "Message.hxx"
#include "Dispatcher.hxx"

#include <common/Macros.hxx>
#include <common/const_assert.hxx>

/****************************************************************************/

namespace osal {

/****************************************************************************/

    /*!
        \brief Special Message::Source to be used from a signal handler
    */
    class OSAL_EXPORT SignalQueue: public SignalQueueImpl {

    public:

        class Notifier: public SignalQueueImpl::NotifierImpl {};

        SignalQueue(Notifier &notifier): SignalQueueImpl(notifier) {}
    };

/****************************************************************************/

}  // end of namespace osal

/****************************************************************************/
#endif
