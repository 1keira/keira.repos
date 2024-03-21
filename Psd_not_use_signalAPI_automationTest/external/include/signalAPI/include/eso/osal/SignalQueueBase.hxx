/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

/****************************************************************************/
#ifndef OSAL_SIGNALQUEUEBASE_HXX
#define OSAL_SIGNALQUEUEBASE_HXX
/****************************************************************************/

#include <ipl_config.h>

#include <osal/osal_dso.h>

#include "Message.hxx"
#include "Dispatcher.hxx"

/****************************************************************************/

namespace osal {

/****************************************************************************/

    //! \internal
    class OSAL_EXPORT SignalQueueBase {

    public:

        typedef void (* Callback)(int signal, void *context);

    protected:

        class Message;
    };

/****************************************************************************/

    /*!
        \internal
        \brief Specialized Message for signal handling callbacks
    */
    class SignalQueueBase::Message: public osal::Message {

    public:
        Message(int signal, SignalQueueBase::Callback callback, void *context):
            signal(signal), callback(callback), context(context) {}

        virtual void invoke();

    protected:
        int signal;
        SignalQueueBase::Callback callback;
        void *context;
    };

/****************************************************************************/

}  // end of namespace osal

/****************************************************************************/
#endif
