/*
    Copyright 2021 e.solutions GmbH
    All rights reserved
*/
#ifndef TRACING_CLOCKSOURCE_MONOCPU_HXX
#define TRACING_CLOCKSOURCE_MONOCPU_HXX

#include <string>
#include <tracing/clocksource/ClockCpu.hxx>
#include <tracing/clocksource/ClockMonotonic.hxx>
#include <tracing/core/clock/SuspendMonitor.hxx>

namespace tracing {

/*!
 *    \brief
 *        This clocksource basically uses monotonic clock but also monitors
 *        the HW based ARM clock for suspend-time offset provisioning.
 */
class ClockMonoCpu final : public ClockMonotonic
{
public:
    //! \brief Returns a C string containing the name of the ClockSource.
    static const char * getClockSourceName() { return "ClockMonoCpu"; }

    //! \brief Creates a new ClockMonoCpu clock source.
    static IClockSource * create() { return new ClockMonoCpu();}

    //! \brief Destroys a clock source.
    static void destroy(IClockSource * source) { delete source; }

    //! \brief Default constructor.
    ClockMonoCpu();
    //! \brief Virtual default destructor.
    ~ClockMonoCpu() override = default;

    /* Overrides */
    //! \brief Get flags indicating supported clock source capabilities \sa IClockSource.
    uint32_t getFlags() const override
    {
        return IClockSource::FLAGS_AFFECTED_BY_ADJTIME |
               IClockSource::FLAGS_SUSPEND_AWARE |
               IClockSource::FLAGS_SUSPEND_OFFSET_AWARE;
    }

    //! \brief Get the clock source time in nanoseconds.
    uint64_t getTime() override;

    //! \sa IClockSource::getSuspendOffset()
    bool getSuspendOffset(int64_t &offset) override;

    //! \sa IClockSource::initSuspendMonitor()
    void initSuspendMonitor(uint32_t thres_ms, bool update_statistics) override
    {
        m_suspend_monitor.init(thres_ms, update_statistics);
    }

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

private:
    //! the latest monotonic timestamp without offset
    uint64_t m_ts_mono;
    //! cpu clock for suspend time offset
    ClockCpu m_clock_cpu;
    //! suspend time monitor
    SuspendMonitor  m_suspend_monitor;
};

} //namespace tracing

#endif // TRACING_CLOCKSOURCE_MONOCPU_HXX
