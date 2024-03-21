/*
    Copyright esolutions GmbH
    All rights reserved
    Authors:
        Matthias Gerstner
    $Id: $
*/

#ifndef OSAL_ANDROID_MSGQUEUEDEFS_HXX
#define OSAL_ANDROID_MSGQUEUEDEFS_HXX

namespace osal {

    typedef unsigned QueuePriority;

    struct MsgQueueHandle
    {
        bool isValid() const {
            // this is an empty implementation that just satisfies the interface,
            // but doesn't do anything useful
            return false;
        }
    };

    struct MsgQueueServerHandle
    {
        MsgQueueServerHandle(const bool&) {}
    };

}  // end of namespace osal

#endif
