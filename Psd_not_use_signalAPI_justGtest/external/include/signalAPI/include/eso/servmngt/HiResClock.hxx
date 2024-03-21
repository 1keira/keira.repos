#ifndef SERVMNGT_HIRESCLOCK_HXX_
#define SERVMNGT_HIRESCLOCK_HXX_

/*
    Copyright esolutions GmbH
    All rights reserved
    Authors:
        Martin Ruff
    $Id: HiResClock.hxx 12434 2010-03-12 13:03:18Z andre.grabinski $
*/

#include <ipl_config.h>

#include <assert.h>
#include <osal/Time.hxx>
#include <servmngt/servmngt_dso.h>

#include <time.h>

#ifdef IPL_OS_QNX
#include <sys/neutrino.h>
#endif

//-----------------------------------------------------------------------------

namespace servmngt {

typedef uint64_t HiResTick;

/*!
\brief    Access to a high resolution clock. The resolution of the clock
        depends on the OS osal implementation.
*/
class SERVMNGT_EXPORT HiResClock {
public:
    HiResClock();
    
    //! get the current clock tick
    static inline HiResTick getTick();
    //! get the current clock tick
    static inline void getTick(HiResTick& tick);
    //! get the difference between a given clock tick and the current clock tick
    static HiResTick getDiffToTick(const HiResTick& old) { return getTick() - old; }

    //! convert a given clock tick value into a microsecond value
    static osal::TimeT ticksToUs (const HiResTick& ticks);

    //! calculate the difference of two clock tick values and return the result in milliseconds
    static osal::TimeT calcDiffMs(const HiResTick& first, const HiResTick& second);

    //! convert a given clock tick value into milliseconds
    static osal::TimeT calcDiffMs(const HiResTick& delta);

    //! calculate the difference of two clock tick values and return the result in microseconds
    static osal::TimeT calcDiffUs(const HiResTick& first, const HiResTick& second);

    //! convert a given clock tick value into microseconds
    static osal::TimeT calcDiffUs(const HiResTick& delta);

    //! calculate the difference of two clock tick values and return the result clock ticks
    static float calcDiffFloat(const HiResTick& first, const HiResTick& second);

    //! convert a given clock tick value into clock ticks
    static float calcDiffFloat(const HiResTick& delta);

    //! retrieve the resolution of the high resolution clock in nanoseconds
    static osal::TimeT getResNs();

    //! start the timer
    void start() { getTick(m_start); }

    //! stop the timer
    void stop()  { getTick(m_end); }

    //! retrieve the time between last start() and stop() sequence in milliseconds
    osal::TimeT getDiffMs();

    //! retrieve the time between last start() and stop() sequence in microseconds
    osal::TimeT getDiffUs();

    //! retrieve the time between last start() and stop() in clock ticks
    float getDiffFloat();

private:
    HiResTick m_start;
    HiResTick m_end;
};

#ifdef IPL_OS_LINUX

HiResTick SERVMNGT_EXPORT timespec2nsec(struct timespec& ts);

#endif

}


//-----------------------------------------------------------------------------
// inline definitions

#ifdef IPL_OS_QNX

servmngt::HiResTick servmngt::HiResClock::getTick() {
    return ClockCycles();
}

void servmngt::HiResClock::getTick(servmngt::HiResTick& tick) {
    tick = ClockCycles();
}

#elif defined IPL_OS_WIN32

servmngt::HiResTick servmngt::HiResClock::getTick() {
    LARGE_INTEGER t;
    bool ok = QueryPerformanceCounter(&t);
    assert(ok);
    return t.QuadPart;
}

void servmngt::HiResClock::getTick(servmngt::HiResTick& tick) {
    LARGE_INTEGER t;
    bool ok = QueryPerformanceCounter(&t);
    assert(ok);
    tick = t.QuadPart;
}

#elif defined IPL_OS_LINUX

servmngt::HiResTick servmngt::HiResClock::getTick() {
    struct timespec t;
    if(clock_gettime(CLOCK_REALTIME, &t)) { // BRANCH_COVERAGE_UNTESTABLE
        return 0ULL;
    }
    return timespec2nsec(t);
}

void servmngt::HiResClock::getTick(servmngt::HiResTick& tick) {
    struct timespec t;
    if(clock_gettime(CLOCK_REALTIME, &t)) { // BRANCH_COVERAGE_UNTESTABLE
        tick = 0ULL;
    }
    else {
        tick = timespec2nsec(t);
    }
}

#endif

#endif
