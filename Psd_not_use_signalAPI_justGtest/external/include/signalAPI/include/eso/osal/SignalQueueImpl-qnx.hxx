/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

/****************************************************************************/
#ifndef OSAL_SIGNALQUEUEIMPL_QNX_HXX
#define OSAL_SIGNALQUEUEIMPL_QNX_HXX
/****************************************************************************/

#include <ipl_config.h>

#ifndef IPL_OS_QNX
#error Only valid on QNX
#endif

#include <osal/osal_dso.h>

#include "SignalQueuePosixBase.hxx"

#include <threadsafe/Mutex.hxx>
#include <threadsafe/Condition.hxx>
#include <common/types/vector.hxx>
#include <osal/Thread.hxx>
#include <osal/qnx/QnxSelfPulseChannel.hxx>

/****************************************************************************/

namespace osal {

/****************************************************************************/

    /*!
        \internal
        \brief System dependent part of SignalQueue, QNX incarnation
    */
    class OSAL_EXPORT SignalQueueImpl: public SignalQueuePosixBase {

    public:

        /*!
            \internal
            \brief System dependent part of SignalQueue::Notifier, ONX incarnation
            (pulse based)
        */
        class NotifierImpl: public Dispatcher::Notifier {

        public:
            NotifierImpl();
            ~NotifierImpl();

            void wait() IPL_NOEXCEPT override;
            void signal() IPL_NOEXCEPT override;

        protected:
            static void callback(void *context);
            ipl::Shared<QnxSelfPulseChannel>::Ptr channel;
            int code;
            threadsafe::Mutex mutex;
            threadsafe::Condition condition;
            volatile bool signalled;
        };

        SignalQueueImpl(NotifierImpl &notifier): SignalQueuePosixBase(notifier) {}
    };

/****************************************************************************/

}  // end of namespace osal

/****************************************************************************/
#endif
