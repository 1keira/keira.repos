/*
    Copyright 2023 e.solutions GmbH
    All rights reserved
*/
#ifndef TRACING_CLOCKSOURCE_BOOTTIME_HXX
#define TRACING_CLOCKSOURCE_BOOTTIME_HXX

#include <tracing/tracing_dso.h>
#include <tracing/clocksource/IClockSource.hxx>

namespace tracing {

/*!
 *    \brief
 *        This clocksource implements a CLOCK_BOOTTIME clock from Linux.
 *
 *      Identical to CLOCK_MONOTONIC, except it also includes any time that the system is suspended.
 *      This allows applications to get a suspend-aware monotonic clock without having to deal with
 *      the complications of CLOCK_REAL‐TIME, which may have discontinuities if the time is changed
 *      using settimeofday(2).
 *
 *      See clock_gettime()
 */
class TRACINGIMPL_EXPORT ClockBoottime : public IClockSource
{
public:
    //! \brief Returns a C string containing the name of the ClockSource.
    static const char * getClockSourceName() { return "ClockBoottime"; }

    //! \brief Default constructor.
    ClockBoottime()
    {
        m_name = getClockSourceName();
    }
    //! \brief Virtual default destructor.
    ~ClockBoottime() override = default;

    //! \brief Creates a new ClockBoottime clock source.
    static IClockSource * create() { return new ClockBoottime();}
    //! \brief Destroys a clock source.
    static void destroy(IClockSource * source) { delete source; }

    /* Overrides */
    //! \brief Get flags indicating supported clock source capabilities \sa IClockSource.
    uint32_t getFlags() const override
    {
        return IClockSource::FLAGS_AFFECTED_BY_ADJTIME |
               IClockSource::FLAGS_SUSPEND_AWARE;
    }

    //! \brief Get the clock source time in nanoseconds.
    uint64_t getTime() override;

    //! \brief Get clocksource resolution \sa IClockSource::ClockResolution.
    ClockResolution getResolution() override
    {
        return RESOLUTION_NS;    //resolution is nanoseconds
    }

    //! \brief Get the clock source precision \sa IClockSource::getPrecision.
    uint64_t getPrecision() override
    {
        return 1;    //nanoseconds
    }

    //! \brief Get the clock source name.
    const std::string & getName() override
    {
        return m_name;
    }
};

} //namespace tracing

#endif // CLOCKBOOTTIME_HXX
