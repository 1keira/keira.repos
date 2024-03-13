/*
    Copyright 2020, 2022 e.solutions GmbH
    All rights reserved
*/

#ifndef TRACING_COMMON_HXX
#define TRACING_COMMON_HXX

#include <iomanip>
#include <sstream>
#include <ipl_config.h>
#include <common/Macros.hxx>
#include <common/types/string.hxx>
#include <common/types/vector.hxx>
#include <common/streams/sstream.hxx>
#include <osal/Time.hxx>
#include <tracing/tracing_dso.h>
#include <tracing/clocksource/IClockSource.hxx>

/*!
 *  \brief
 *      Utility functions for tracing module.
 *
 *  \note
 *      These functions are not intended to be used outside of the framework's
 *      tracing module implementation.  They may be deprecated and disappear
 *      without further notice!
 */

namespace tracing
{

//! \brief Replace non-printable and non-ASCII characters of a string with percentage representation.
TRACINGIMPL_EXPORT ipl::string escapeString(const ipl::string & str);

//! \brief Get numeric representation of a trace level string.
TRACINGIMPL_EXPORT int16_t getLevelValue(const ipl::string & str, bool allow_default = false);

//! \brief Get string representation of a numerical trace level, empty string for invalid levels.
TRACINGIMPL_EXPORT const char * getLevelString(int16_t level);

//! \brief Get a vector of substrings from str, splitted at c, returning str if c is not found at all.
TRACINGIMPL_EXPORT ipl::vector<ipl::string> tokenize(const ipl::string & str, const char c = ' ');

//! \brief Same as before, but splitting will be performed at each of the characters in sep.
TRACINGIMPL_EXPORT ipl::vector<ipl::string> tokenize(const ipl::string & str, const ipl::string & sep);

//! \brief Obfuscate a string by replacing contents between pairs of '@' with a checksum.
TRACINGIMPL_EXPORT ipl::string obfuscate(const ipl::string & str, const char sep = '@');

//! \brief Check if string contains digits only
TRACINGIMPL_EXPORT bool hasDigitsOnly(const std::string & str);

//! \brief Concatenates strings pointed at by begin and end separated by separator.
template <typename ForwardIterator>
ipl::string join(
        const ForwardIterator & begin,
        const ForwardIterator & end,
        const ipl::string & separator = ipl::string("")
)
{
    ipl::string result;

    for (ForwardIterator it = begin; it != end; ++it)
    {
        if (!result.empty())
        {
            result.append(separator);
        }
        // Note: this obviously works only if begin and end point to
        // basic string-like stuff, i.e. ipl::string and const char *.
        result.append(*it);
    }

    return result;
}

IPL_DEPRECATED("use tracing::Frontend::getTimestamp() instead", osal::TimeT getTimestamp());
inline osal::TimeT getTimestamp()
{
    bool err;
    osal::TimeT ts = 0;
#if defined(TRACING_USE_CLOCK_MONOTONIC)
    err = osal::Time::getTime(ts);
#elif defined(TRACING_USE_CLOCK_BOOTTIME)
    struct timespec t;
    err = (::clock_gettime(CLOCK_BOOTTIME, &t) != 0);
    ts = static_cast<osal::TimeT>(t.tv_sec) * 1000 + ((t.tv_nsec + 500000) / 1000000);
#else /* TRACING_USE_CLOCK_MONOTONIC */
    err = osal::Time::getTimestamp(ts);
#endif /* TRACING_USE_CLOCK_MONOTONIC */

    if(err)
        ts = INVALID_TIME;

    return ts;
}

IPL_DEPRECATED("use tracing::Frontend::getTimestampNS() instead", osal::TimeT getTimestampNS());
inline osal::TimeT getTimestampNS()
{
    bool err;
    osal::TimeT ts = 0;
#if defined(TRACING_USE_CLOCK_MONOTONIC)
    err = osal::Time::getTime(ts);
    ts *= 1000000;
#elif defined(TRACING_USE_CLOCK_BOOTTIME)
    struct timespec t;
    err = (::clock_gettime(CLOCK_BOOTTIME, &t) != 0);
    ts = static_cast<osal::TimeT>(t.tv_sec) * 1000000000UL + t.tv_nsec;
#else /* TRACING_USE_CLOCK_MONOTONIC */
    err = osal::Time::getTimestampNS(ts);
#endif /* TRACING_USE_CLOCK_MONOTONIC */

    if(err)
        ts = INVALID_TIME;

    return ts;
}

} // end of namespace tracing

#endif /* TRACING_COMMON_HXX */

