/*
    Copyright e.solutions GmbH
    All rights reserved
    Authors:
        Matthias Gerstner
    $Id: $
*/

/*
    AtomicCounter QNX implementation.

    On QNX we have a clean API provided by the system that allows us
    to do quite everything we want.

    -> with the exception of exchange and exchangeIf which suddenly
    needs to be done via some per-CPU-header and not via the
    atomic_* API. Well at least there is something there.
*/

#include <atomic.h>
// I took this strange macro over from a foundry post
#include _NTO_CPU_HDR_(smpxchg.h)

namespace osal {

    inline AtomicCounterType AtomicCounter::increment()
    {
        return atomic_add_value(&m_handle.counter, 1);
    }

    inline AtomicCounterType AtomicCounter::decrement()
    {
        return atomic_sub_value(&m_handle.counter, 1);
    }

    inline AtomicCounterType AtomicCounter::exchange(
        const AtomicCounterType &newval)
    {
        return _smp_xchg(&m_handle.counter, newval);
    }

    inline AtomicCounterType AtomicCounter::exchangeIf(
        const AtomicCounterType &newval,
        const AtomicCounterType &compval)
    {
        return _smp_cmpxchg(&m_handle.counter, compval, newval);
    }

} // end namespace
