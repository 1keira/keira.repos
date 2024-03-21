/*
    Copyright 2020, 2023 e.solutions GmbH
    All rights reserved
*/

#ifndef TRACING_ICLOCKSOURCE_HXX
#define TRACING_ICLOCKSOURCE_HXX

#include <common/stdint.h>
#include <stdlib.h>
#include <string>
#include <vector>

namespace tracing {

/*!
 * \brief
 *      The resolution of a clocksource
 */
enum ClockResolution {
    RESOLUTION_S = 0,           /* Seconds */
    RESOLUTION_MS = 1,          /* Milliseconds */
    RESOLUTION_US = 2,          /* Microseconds */
    RESOLUTION_NS = 3           /* Nanoseconds */
};

const int64_t INVALID_TIME = 0xffffffffffffffffLL;

class IClockSourceCallback;

/*!
 *  \brief
 *      Interface class for a clocksource.
 */
class IClockSource
{
public:
    //! ClockSource provides system-wide clock that measures time
    static const uint32_t FLAGS_WALL_CLOCK = 1 << 0;
    //! ClockSource is suspend-aware, including any time where the system was suspended
    static const uint32_t FLAGS_SUSPEND_AWARE = 1 << 1;
    //! ClockSource indicates that time can be affected by discontinuous jumps in the system time
    static const uint32_t FLAGS_AFFECTED_BY_DISC_JUMPS= 1 << 2;
    //! ClockSource indicates that time can be affected by incremental adjustments
    static const uint32_t FLAGS_AFFECTED_BY_ADJTIME = 1 << 3;
    //! ClockSource provices the time offset between a suspend-aware and non-suspend
    //! aware clock
    static const uint32_t FLAGS_SUSPEND_OFFSET_AWARE = 1 << 4;
    //! ClockSource can provide the actual time only asynchronously via getTimeAsync()
    //! with related callback \sa IClockSourceCallback.
    static const uint32_t FLAGS_ASYNC_CLOCK = 1 << 5;
    //! ClockSource only provides an offset to the core reference time.
    static const uint32_t FLAGS_CLOCK_OFFSET_ONLY = 1 << 6;

public:
    //! \brief Default constructor.
    IClockSource() = default;
    //! \brief Virtual default destructor.
    virtual ~IClockSource() = default;

    /*!
     *  \brief
     *      Creates a new clock source
     *
     *      When implementing your own ClockSource you are expected to implement this
     *      function in a way, such that calling it will create a new clock source of
     *      the type you declared (and which derives itself from this interface
     *      class) and return a pointer to an object of your clock source class or NULL
     *      if construction failed.
     *
     *  \return
     *      A pointer to the newly created clock source.
     */
    static IClockSource * create() {return nullptr;}

    /*!
    *  \brief
    *      Destroys a clock source again.
    *
    *      This is the counter-part to create(). You can implement this just like
    *      shown here, but possibly you want to do some other cleanup work in your
    *      clock source first.
    *      The pointer provided as parameter is the one received from create().
    *
    *  \param
    *      source A pointer to a clock source object.
    */
    static void destroy(IClockSource * source) { delete source; }

    /*!
     *  \brief
     *      Returns a C string containing the name of the ClockSource.
     *
     *      If you derive from this interface and implement your own clock source you
     *      are expected to return a C string containing a unique name for your
     *      clock source. This string will be compared with entries found in the config
     *      file, to decide which clock source to instantiate.
     *
     *  \return
     *      C-style string with clock source's name.
     */
    static const char * getClockSourceName() { return nullptr; }

    /*************** Start of ClockSource interface *********************************/

    /*!
     *  \brief
     *      Get flags indicating supported clock source capabilities.
     */
    virtual uint32_t getFlags() const
    {
        return 0;
    }

    /*!
     *  \brief
     *      Get time in nanoseconds
     *
     *      Asynchronous clocksources (flag FLAGS_ASYNC_CLOCK) provide here the last
     *      time which was requested via \sa getTimeAsync().
     */
    virtual uint64_t getTime() = 0;

    /*!
     *  \brief
     *      Asynchronous get time request.
     *
     *      This is the API to provide the actual clocksource time asynchronously,
     *      i.e. when the capability flag FLAGS_ASYNC_CLOCK is set.
     *
     *  \param
     *      caller The initiator of this request who expects callback response
     *             via \sa IClockSourceCallback::updateTimeAsync().
     *  \param
     *      user_data Caller's user data which shall be mirrored back in the callback
     *             via \sa IClockSourceCallback::updateTimeAsync().
     */
    virtual bool getTimeAsync(IClockSourceCallback* caller, int32_t user_data)
    {
        return false;
    }

    //! \brief Get clocksource resolution \sa IClockSource::ClockResolution.
    virtual ClockResolution getResolution() = 0;

    /*!
     *  \brief
     *      Get precision
     *
     *      Precision indicates the duration of a clock tick measured in nanoseconds.
     *      E.g. value 1 means nanoseconds precision, 1 tick per nanosecond.
     *      E.g. value 1.000.000 relates to a clock ticking each 1 millisecond.
     *
     *  \return
     *      The duration of a clock tick measured in nanoseconds.
     */
    virtual uint64_t getPrecision() = 0;

    //! \brief Get the clock source name.
    virtual const std::string & getName()
    {
        return m_name;
    }

    /*!
     *  \brief
     *      Initialize suspend monitor with threshold for jitter compensation.
     *
     *      Only relevant if FLAGS_SUSPEND_OFFSET_AWARE is supported.
     *  \param
     *      thres_ms The threshold in [ms].
     *  \param
     *      update_statistics Flag to indicate if core statistics shall be reported.
     */
    virtual void initSuspendMonitor(uint32_t thres_ms, bool update_statistics)
    {
        /* nop */
    }

    /*!
     *  \brief
     *      Get suspend offset towards a secondary non-suspend aware clocksource.
     *
     *      Only relevant if FLAGS_SUSPEND_OFFSET_AWARE is supported.
     *  \return
     *      boolean flag, only when true the offset is valid.
     */
    virtual bool getSuspendOffset(int64_t& offset)
    {
        return false;
    }

protected:
    std::string m_name;
};

/*!
 *  \brief
 *      Interface class for a handler of callbacks from a clocksource.
 */
class IClockSourceCallback
{
public:
    //! \brief Virtual default destructor.
    virtual ~IClockSourceCallback() = default;

    /*!
    *  \brief
    *      Callback from a clocksource with asynchronous time reporting.
    *
    *      This is the response to a preceding getTimeAsync() request \sa IClockSource.
    *
    *  \param
    *      flags The caller's clocksource flags.
    *  \param
    *      user_data The mirrored user data from the request.
    *  \param
    *      time The reported clocksource time in nanoseconds.
    */
    virtual void updateTimeAsync(uint32_t flags, int32_t user_data, int64_t time) = 0;
};

} //namespace tracing

#endif //TRACING_ICLOCKSOURCE_HXX
