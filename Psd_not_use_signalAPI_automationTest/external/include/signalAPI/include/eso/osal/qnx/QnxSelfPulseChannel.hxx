/****************************************************************************/
/*
    Copyright esolutions GmbH
    All rights reserved
    Authors:
        Stefan Meinlschmidt
*/
/****************************************************************************/
#ifndef OSAL_QNX_QNXSELFPULSECHANNEL_HXX
#define OSAL_QNX_QNXSELFPULSECHANNEL_HXX
/****************************************************************************/

#include <ipl_config.h>

#ifndef IPL_OS_QNX
#error Only valid on QNX
#endif

#include <osal/osal_dso.h>

#include <threadsafe/Mutex.hxx>
#include <common/Shared.hxx>
#include <common/types/vector.hxx>
#include <osal/Thread.hxx>

/****************************************************************************/

namespace osal {

/****************************************************************************/

    /*!
        \brief QNX only: Thread receiving pulses on a private channel and
        calling registered callbacks accordingly
        
        Timers, signal handlers an possibly others need a means of sending
        pulses from one thread to another within the same process.
        This is those means, including a thread that dispatches the received
        pulses to callbacks.
        
        The idea is that several clients can share one QnxSelfPulseChannel
        by getting assigned different pulse codes for their different callbacks.
        This minimizes the number of channels and threads involved but also
        introduced possibly unwanted interaction.
    */
    class OSAL_EXPORT QnxSelfPulseChannel {
        
    public:
        
        typedef void (*Callback)(void *);
        
        QnxSelfPulseChannel();
        ~QnxSelfPulseChannel();

        //! \brief Register callback, returns pulse code you can send to invoke callback
        int sign_on(Callback callback, void *context);
        //! \brief Unregister callback by associated pulse code
        void sign_off(int code);
        
        //! \brief Send pulse with \a code to channel, invoking the associated callback in worker thread
        void send(int code);

        //! \brief Canonical instance for all to share that have no special needs
        static ipl::Shared<QnxSelfPulseChannel> DEFAULT;
        
    protected:
        static void main(void *context);
        
        struct Info {
            Callback callback;
            void *context;
        };
        
        typedef ipl::vector<Info> Callbacks;
        Callbacks callbacks;
        threadsafe::Mutex mutex;
        int channel;
        
    public:
        //! \brief The actual channel's id in case you cannot use send()
        const int coid;

    protected:
        static const int STOP_CODE=_PULSE_CODE_MINAVAIL;
        static const int PULSE_CODE_OFFSET=STOP_CODE+1;
        osal::Thread thread;
        volatile bool running;
    };

/****************************************************************************/

}  // end of namespace osal

/****************************************************************************/
#endif
