/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_POSIX_MSGQUEUEDEFS_HXX
#define OSAL_POSIX_MSGQUEUEDEFS_HXX

#include <mqueue.h>
#include <limits.h>

namespace osal {

    typedef unsigned QueuePriority;

    //! OS handle to reference a posix message queue
    struct MsgQueueHandle
    {
        mqd_t queue;

        MsgQueueHandle()
        {
            invalidate();
        }

        bool isValid() const
        {
            return queue != (mqd_t)-1;
        }

        void invalidate()
        {
            queue = (mqd_t)-1;
        }
    };

    struct MsgQueueServerHandle
    {
        char m_identifier[NAME_MAX + 1];
        const bool del_on_close;

        MsgQueueServerHandle(const bool doc) :
            del_on_close(doc)
        {
            invalidate();
        }

        bool isValid() const
        {
            return m_identifier[0] != '\0';
        }

        void invalidate()
        {
            m_identifier[0] = '\0';
        }

        char* identifier()
        {
            return &m_identifier[0];
        }
    };

}  // end of namespace osal

#endif
