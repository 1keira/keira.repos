/*
    Copyright 2021 e.solutions GmbH
    All rights reserved
*/
#ifndef TRACING_CLOCKSOURCE_CPU_HXX
#define TRACING_CLOCKSOURCE_CPU_HXX

#include <tracing/tracing_dso.h>
#include <tracing/clocksource/IClockSource.hxx>

namespace tracing {

/*!
 *    \brief
 *        Clocksource implements a pure HW based and suspend-aware clock.
 */
class TRACINGIMPL_EXPORT ClockCpu : public IClockSource
{
public:
    //! \brief Returns a C string containing the name of the ClockSource.
    static const char * getClockSourceName() { return "ClockCpu"; }

    //! \brief Creates a new ClockCpu clock source.
    static IClockSource * create() { return new ClockCpu();}
    //! \brief Destroys a clock source.
    static void destroy(IClockSource * source) { delete source; }

    //! \brief Default constructor.
    ClockCpu();
    //! \brief Virtual default destructor.
    ~ClockCpu() override = default;

    /* Overrides */
    //! \brief Get flags indicating supported clock source capabilities \sa IClockSource.
    uint32_t getFlags() const override
    {
        return IClockSource::FLAGS_SUSPEND_AWARE;
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

protected:
    //! \brief Read the clock ticks from HW.
    static inline uint64_t getTicks();
    //! \brief Read the clock frequency from HW.
    static inline uint64_t getFreq();

    uint32_t m_ticks_per_ns;
};

} //namespace tracing

#endif // TRACING_CLOCKSOURCE_CPU_HXX
