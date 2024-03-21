/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

/****************************************************************************/
#ifndef OSAL_SIGNALCATCHERIMPL_INTEGRITY_HXX
#define OSAL_SIGNALCATCHERIMPL_INTEGRITY_HXX
/****************************************************************************/

#include <ipl_config.h>

#ifndef IPL_OS_INTEGRITY
#error Only valid on IntegrityOS
#endif

#include <common/Shared.hxx>
#include <common/types/vector.hxx>
#include "SignalCatcherBase.hxx"
#include "SignalQueue.hxx"
#include "SignalDispatcher.hxx"

/****************************************************************************/

namespace osal {

/****************************************************************************/

    /*!
        \internal
        \brief System dependent part of SignalCatcher, Integrity incarnation
    */
    class SignalCatcherImpl: public SignalCatcherBase {

    public:
        SignalCatcherImpl(int signal,
                          const ipl::Shared<SignalDispatcher>::Ptr &signaldispatcher,
                          SignalQueue &queue,
                          SignalQueue::Callback callback, void *context);
        ~SignalCatcherImpl();

    protected:
        static Mutex mutex;
        static ipl::vector<SignalCatcherImpl *> handlers;

        SignalQueue &queue;
        SignalQueue::Callback callback;
        void *context;
    };

/****************************************************************************/

}  // end of namespace osal

/****************************************************************************/
#endif
