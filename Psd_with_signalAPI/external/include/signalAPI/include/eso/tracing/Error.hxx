/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef TRACING_ERROR_HXX
#define TRACING_ERROR_HXX

#include <common/error/Error.hxx>
#include <tracing/tracing_dso.h>

namespace tracing
{

/*!
 *  \brief
 *      Defines errors created by the trace module.
 */
enum TraceErrors
{
    //! The file selected for printing trace messages could not be opened.
    CANT_OPEN_TRACE_FILE = 0,
    //! Opening the emergency log file failed.
    EMERGENCY_OPEN_FAILED = 1,
    //! Writing to the emergency log file failed.
    EMERGENCY_LOG_FAILED = 2,
    //! Failed to load a plugin specified in tracing configuration.
    PLUGIN_LOADING_FAILED = 3
};

TRACINGIMPL_EXPORT extern ipl::ErrorType Error;

}

#endif /* TRACING_ERROR_HXX */

