/*
    Copyright esolutions GmbH
    All rights reserved
    Authors:
        Matthias Gerstner
    $Id: $
*/

#ifndef OSAL_WIN32_MSGQUEUEDEFS_HXX
#define OSAL_WIN32_MSGQUEUEDEFS_HXX

#include <iplbase/win32.h>
// for some reason we need to include that header or otherwise the Mq header
// borks (tm) pretty badly.
#include <ole2.h>
#include <Mq.h>

namespace osal {

    static const size_t MSG_QUEUE_MAX_ID_LEN = 256;
    typedef unsigned QueuePriority;

    //! OS handle to reference a posix message queue
    struct OSAL_EXPORT MsgQueueHandle
    {
        /*
        * MSMQ queues can only be opened for receiving or sending, not both
        *
        * thus we're using two, to have it easier matching the POSIX queue
        * API.
        */
        QUEUEHANDLE rx_queue;
        QUEUEHANDLE tx_queue;

        MsgQueueHandle()
        {
            invalidate();
        }

        bool isValid() const
        {
            return rx_queue != NULL && tx_queue != NULL;
        }

        void invalidate()
        {
            rx_queue = NULL;
            tx_queue = NULL;
        }

        /*
        * returns a queue name for the label *name*. If *for_open* is set to
        * *true* then the returned name is only valid for opening the queue.
        * Otherwise it is only valid for creating the queue.
        */
        static ipl::wstring getQueueName(
            const char *name, const bool for_open);
    };

    struct MsgQueueServerHandle
    {
        wchar_t m_identifier[MSG_QUEUE_MAX_ID_LEN + 1];
        const bool destroy_on_close;

        MsgQueueServerHandle(const bool doc) :
            destroy_on_close(doc)
        { }

        bool isValid() const
        {
            return m_identifier[0] != '\0';
        }

        void invalidate()
        {
            m_identifier[0] = '\0';
        }

        wchar_t* identifier()
        {
            return &m_identifier[0];
        }
    };

}  // end of namespace osal

#endif
