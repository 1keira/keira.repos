#ifndef TRACING_CLOCKSOURCE_MONOTONIC_HXX
#define TRACING_CLOCKSOURCE_MONOTONIC_HXX
/*
    Copyright 2021 e.solutions GmbH
    All rights reserved
*/

#include <tracing/tracing_dso.h>
#include <tracing/clocksource/IClockSource.hxx>

namespace tracing {

/*!
 *    \brief
 *        This clocksource implements a CLOCK_MONOTONIC clock from Linux.
 *
 *      Clock that cannot be set and represents monotonic time since some unspecified starting
 *      point. This clock is not affected by discontinuous jumps in the system time (e.g., if
 *      the system administrator manually changes the clock), but is affected by the incremental
 *      adjustments performed by adjtime(3) and NTP.
 *
 *      See clock_gettime()
 */
class TRACINGIMPL_EXPORT ClockMonotonic : public IClockSource
{
public:
    //! \brief Returns a C string containing the name of the ClockSource.
    static const char * getClockSourceName() { return "ClockMonotonic"; }

    //! \brief Default constructor.
    ClockMonotonic()
    {
        m_name = getClockSourceName();
    }
    //! \brief Virtual default destructor.
    ~ClockMonotonic() override = default;

    //! \brief Creates a new ClockMonotonic clock source.
    static IClockSource * create() { return new ClockMonotonic();}
    //! \brief Destroys a clock source.
    static void destroy(IClockSource * source) { delete source; }

    /* Overrides */
    //! \brief Get flags indicating supported clock source capabilities \sa IClockSource.
    uint32_t getFlags() const override
    {
        return IClockSource::FLAGS_AFFECTED_BY_ADJTIME;
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

#endif // CLOCKMONOTONIC_HXX
