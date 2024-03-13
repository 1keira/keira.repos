/*
    Copyright esolutions GmbH
    All rights reserved
    Author:
        Andre Grabinski
*/

#define OSAL_KERNEL_TRACE_EVENT_BEGIN 0
#define OSAL_KERNEL_TRACE_EVENT_END 0

namespace osal {
    namespace kernel {

        inline void TraceEventString(const int event_id, const char* string)
        {
        }

        inline void TraceEventInt(const int event_id, const int data0, const int data1)
        {
        }

        inline void TraceEventBuffer(const int event_id, unsigned * buf, unsigned len)
        {
        }

    } // end namespace
} // end namespace

