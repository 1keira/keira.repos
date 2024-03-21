/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef TRACING_UTILITY_HXX
#define TRACING_UTILITY_HXX

#include <ipl_config.h>
#include <common/Macros.hxx>
#include <common/stdint.h>
#include <common/types/string.hxx>
#include <common/streams/sstream.hxx>
#include <common/streams/ostream.hxx>
#include <common/streams/iomanip.hxx>

namespace tracing
{
//! \brief Provides formatted string of a timestamp with milliseconds resolution as '+/-hh:mm:ss:xxx'
inline ipl::string formatTimestampMS(int64_t time_stamp_ms) IPL_NOEXCEPT
{
    ipl::ostringstream o;
    if (time_stamp_ms < 0)
    {
        o << "-";
        time_stamp_ms *= -1;
    }

    int32_t millis = (int32_t)(time_stamp_ms % 1000LL); time_stamp_ms /= 1000LL;
    int32_t seconds = (int32_t)(time_stamp_ms % 60LL); time_stamp_ms /= 60LL;
    int32_t minutes = (int32_t)(time_stamp_ms % 60LL); time_stamp_ms /= 60LL;
    int32_t hours = (int32_t)(time_stamp_ms % 24LL);

    o << ipl::setfill('0');
    o << ipl::setw(2);
    o << hours << ":";
    o << ipl::setw(2);
    o << minutes << ":";
    o << ipl::setw(2);
    o << seconds << ".";
    o << ipl::setw(3);
    o << millis;

    return o.str();
}

//! \brief Provides formatted string of a timestamp with nanoseconds resolution as '+/-hh:mm:ss:nnnnnnnnn'
inline ipl::string formatTimestampNS(int64_t time_stamp_ns) IPL_NOEXCEPT
{
    ipl::ostringstream o;
    if (time_stamp_ns < 0)
    {
        o << "-";
        time_stamp_ns *= -1;
    }

    int32_t nanos = (int32_t)(time_stamp_ns % 1'000'000'000LL);
    time_stamp_ns /= 1'000'000'000LL;
    int32_t seconds = (int32_t)(time_stamp_ns % 60LL); time_stamp_ns /= 60LL;
    int32_t minutes = (int32_t)(time_stamp_ns % 60LL); time_stamp_ns /= 60LL;
    int32_t hours = (int32_t)(time_stamp_ns % 24LL);

    o << ipl::setfill('0');
    o << ipl::setw(2);
    o << hours << ":";
    o << ipl::setw(2);
    o << minutes << ":";
    o << ipl::setw(2);
    o << seconds << ".";
    o << ipl::setw(9);
    o << nanos;

    return o.str();
}

IPL_DEPRECATED("use explicit formatTimestampMS or formatTimestampNS function instead",
inline ipl::string formatTimestamp(int64_t time_stamp_ms) IPL_NOEXCEPT
);

//! \brief Provides formatted string of a timestamp with milliseconds resolution as '+/-hh:mm:ss:xxx'
inline ipl::string formatTimestamp(int64_t time_stamp_ms) IPL_NOEXCEPT
{
    return formatTimestampMS(time_stamp_ms);
}

} // end of namespace tracing

#endif /* TRACING_UTILITY_HXX */

