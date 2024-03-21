/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

/*
    AtomicCounter fallback implementation.

    If all else fails and we can't provide userspace atomic counters
    then we have to fallback to a counter protected by a standard
    mutex. For the mutex an abstract osal::Mutex is used such that
    this AtomicCounter is actually platform-independent.
*/

#include <ipl_config.h>
#include <common/Macros.hxx>
#include <osal/AtomicCounter.hxx>

namespace osal
{

inline uint_fast32_t AtomicCounter::increment()
{
    bool err = m_handle.counter_lock.lock();
    IPL_ASSERT( ! err );

    const AtomicCounterType ret = m_handle.counter;
    m_handle.counter++;

    err = m_handle.counter_lock.unlock();
    IPL_ASSERT( ! err );

    return ret;
}

inline uint_fast32_t AtomicCounter::decrement()
{
    bool err = m_counter_lock.lock();
    IPL_ASSERT( ! err );

    const AtomicCounterType ret = m_handle.counter;
    m_handle.counter--;

    err = m_counter_lock.unlock();
    IPL_ASSERT( ! err );

    return ret;
}

inline AtomicCounterType AtomicCounter::exchange(
    const AtomicCounterType &newval)
{
    bool err = m_counter_lock.lock();
    IPL_ASSERT( ! err );

    AtomicCounterType ret = m_handle.counter;
    m_handle.counter = newval;
    
    err = m_counter_lock.unlock();
    IPL_ASSERT( ! err );

    return ret;
}

inline AtomicCounterType AtomicCounter::exchangeIf(
    const AtomicCounterType &newval,
    const AtomicCounterType &compval)
{
    bool err = m_counter_lock.lock();
    IPL_ASSERT( ! err );

    AtomicCounterType ret = m_handle.counter;

    if( ret == compval )
        m_handle.counter = newval;

    err = m_counter_lock.unlock();
    IPL_ASSERT( ! err );

    return ret;
}

} // end namespace
