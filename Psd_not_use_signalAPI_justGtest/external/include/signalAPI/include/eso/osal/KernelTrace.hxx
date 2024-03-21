/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_KERNEL_TRACE_HXX
#define OSAL_KERNEL_TRACE_HXX

#include <ipl_config.h>
namespace osal
{

namespace kernel
{

/**
 * \file
 * \brief
 *     QNX kernel trace facility

 *     The free functions in this header only actually do something on
 *     the QNX operating system.
 *
 *     They allow to trace data in the context of the QNX kernel
 *     instrumentation. Thus it only works if you're running an
 *     instrumented QNX kernel.
 *
 *     Each of the functions takes an event ID that is chosen by the
 *     caller but needs to be within the range defined by
 *     [OSAL_KERNEL_TRACE_EVENT_BEGIN, OSAL_KERNEL_TRACE_EVENT_END]
 **/

/**
 * \brief
 *     Traces the given null-terminated string \a string using the
 *     given event id \a event_id
 **/
inline void TraceEventString(const int event_id, const char* string);

/**
 * \brief
 *     Traces the given pair of integers (?) using the given event id
 *     \a event_id

 *     QNX documentation doesn't clearly state what \a data0 nad
 *     \a data1 are used for. I can only assume it's two integers that
 *     will be traced.
 **/
inline void TraceEventInt(const int event_id, const int data0, const int data1);

/**
 * \brief
 *     Traces the given raw data in \a buf of \a len bytes length using
 *     the given event id \a event_id
 **/
inline void TraceEventBuffer(const int event_id, unsigned * buf, unsigned len);

} // end ns kernel

} // end ns osal

#if defined (IPL_OS_QNX)
#    include "qnx/KernelTrace.inl"
#elif defined (IPL_OS_WINPC)
#    include "win32/KernelTrace.inl"
#else
#    include "linux/KernelTrace.inl"  // empty implementation
#endif

#endif /* KERNEL_TRACE_HXX */
