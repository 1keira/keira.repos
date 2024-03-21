/*
    Copyright esolutions GmbH
    All rights reserved
    Author:
        Andre Grabinski
*/

#include <sys/trace.h>

#define OSAL_KERNEL_TRACE_EVENT_BEGIN _NTO_TRACE_USERFIRST
#define OSAL_KERNEL_TRACE_EVENT_END _NTO_TRACE_USERLAST

namespace osal {
    namespace kernel {

        inline void TraceEventString(const int event_id, const char* string)
        {
            TraceEvent(_NTO_TRACE_INSERTUSRSTREVENT, event_id, string);
        }

        inline void TraceEventInt(const int event_id, const int data0, const int data1)
        {
            TraceEvent(_NTO_TRACE_INSERTSUSEREVENT, event_id, data0, data1);
        }

        inline void TraceEventBuffer(const int event_id, unsigned * buf, unsigned len)
        {
            TraceEvent(_NTO_TRACE_INSERTCUSEREVENT, event_id, buf, len);
        }

    } // end namespace
} // end namespace
