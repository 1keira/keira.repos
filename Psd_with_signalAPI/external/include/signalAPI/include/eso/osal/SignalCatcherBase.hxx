/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

/****************************************************************************/
#ifndef OSAL_SIGNALCATCHERBASE_HXX
#define OSAL_SIGNALCATCHERBASE_HXX
/****************************************************************************/

#include <common/Shared.hxx>
#include <osal/SignalDispatcher.hxx>

/****************************************************************************/

namespace osal {

/****************************************************************************/

    /*!
        \internal
        \brief Common base for the various SignalCatcherImpl variants
    */
    class OSAL_EXPORT SignalCatcherBase {

    public:
        SignalCatcherBase(int signal,
                          const ipl::Shared<SignalDispatcher>::Ptr &signaldispatcher):
            signal(signal), signaldispatcher(signaldispatcher) {}

    protected:
        int signal;

        // Hold the reference to the possibly dynamically allocated dispatcher
        const ipl::Shared<SignalDispatcher>::Ptr signaldispatcher;
    };

/****************************************************************************/

}  // end of namespace osal

/****************************************************************************/
#endif
