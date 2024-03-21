/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

/****************************************************************************/
#ifndef OSAL_SIGNALQUEUEPOSIXBASE_HXX
#define OSAL_SIGNALQUEUEPOSIXBASE_HXX
/****************************************************************************/

#include <ipl_config.h>

#ifndef IPL_OS_POSIX
#error Only valid on Posix
#endif

#include <osal/osal_dso.h>

#include "SignalQueueBase.hxx"

#include <threadsafe/AtomicCounter.hxx>
#include <threadsafe/Mutex.hxx>

/****************************************************************************/

namespace osal {

/****************************************************************************/

    /*!
        \internal
        \brief Semi system dependent part of SignalQueue, common to Posix and QNX
    */
    class OSAL_EXPORT SignalQueuePosixBase:
        public SignalQueueBase, public Message::Source {

    public:

        SignalQueuePosixBase(Dispatcher::Notifier &notifier): notifier(notifier) {
            for(int i=0; i<IPL_NSIGNALS; i++)
                signals[i].callback=NULL;
        }

        //! \brief Register signal callback
        void sign_on(int signal, Callback callback, void *context);
        //! \brief Unregister signal callback
        void sign_off(int signal);
        //! \brief Put signal in queue
        void push(int signal);
        osal::Message *pop_nonblock() IPL_NOEXCEPT override;

    protected:

        threadsafe::Mutex mutex;
        /*!
            \brief Signal callback registration info

            Registered signals are maintained as array of Info structures.
            If \a callback is non-NULL, a callback is registered for this signal.
            push() doesn't actually enqueue anything, instead it increments
            the signal's \a counter.
            Similar, pop_nonblock() just scans for the first non-zero \a counter
            with a non-null \a callback pointer.
            Hence the whole queue behaves more like a priority queue.
        */
        struct Info {
            Callback callback;  //!< \brief \c NULL means info is invalid
            void *context;
            threadsafe::AtomicCounter counter;
        } signals[IPL_NSIGNALS];

        Dispatcher::Notifier &notifier;
    };

/****************************************************************************/

}  // end of namespace osal

/****************************************************************************/
#endif
