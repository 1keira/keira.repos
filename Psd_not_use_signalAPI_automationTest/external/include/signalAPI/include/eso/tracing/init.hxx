/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef TRACING_INIT_HXX
#define TRACING_INIT_HXX

#include <tracing/tracing_dso.h>

/*
 * Initialization and shutdown functions for tracing library which is
 * statically linked against util.
 *
 * Note: Do not call these functions if using the regular tracing library
 * which is dynamically linked against util. It will cause linker errors
 * because their implementation is only contained in the util-static tracing
 * lib.
 * The util library has its own initialization mechanism which will setup
 * tracing automatically when constructing a util::Util object.
 */

/*!
    \brief
        Initialize tracing.
    \param
        process_name The name of your process, as specified in framework.json
    \param
        read_config Specifies whether tracing.json should be parsed.
    \return
        True on error.
 */
extern "C" TRACINGIMPL_EXPORT bool initStaticTracingLib(
        const char * const process_name, bool read_config);

/*!
    \brief
        Shut down tracing.
 */
extern "C" TRACINGIMPL_EXPORT void exitStaticTracingLib();

/*!
    \brief
        Initialize tracing.
    \param
        process_name The name of your process, as specified in framework.json
    \param
        read_config Specifies whether tracing.json should be parsed.
    \return
        True on error.
 */
extern "C" TRACINGIMPL_EXPORT bool initTraceCore(
        const char * const process_name, bool read_config);

/*!
    \brief
        Shut down tracing.
 */
extern "C" TRACINGIMPL_EXPORT void exitTraceCore();

/*!
    \brief DEPRECATED!
        Do not use this function. This is only introduced as workaround for
        the current implementation of the traceserver when loading plugins
        that call initTraceCore(). This function only increases/decreases
        the reference count but performs no actual initialization.
    \deprecated
 */
extern "C" TRACINGIMPL_EXPORT void traceCoreInitialized(bool initialize);

namespace tracing {
/*!
    \brief
        Return the number of trace core users.
    \return
        0 if no one uses the trace core or the number of users.
 */
int getTraceCoreUseCount();
} // namespace tracing

#endif /* TRACING_INIT_HXX */

