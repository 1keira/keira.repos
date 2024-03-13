/*
    Copyright e.solutions GmbH
    All rights reserved
    Authors:
        Horst Hadler
        Matthias Gerstner
    $Id: $
*/

/*
    AtomicCounter Win32 implementation.

    On WinXP we have the full feature set of atomic operations
    (which isn't so hard as XP is a x86-only OS). On WinCE only
    decrement, increment and exchange exist. It's enough to provide
    a common Win32 implementation.
*/

namespace osal {

    inline AtomicCounterType AtomicCounter::increment()
    {
        const AtomicCounterType newval =
            InterlockedIncrement((AtomicCounterType*)&m_handle.counter);

        return newval - 1;
    }

    inline AtomicCounterType AtomicCounter::decrement()
    {
        const AtomicCounterType newval =
            InterlockedDecrement((AtomicCounterType*)&m_handle.counter);

        return newval + 1;
    }

    inline AtomicCounterType AtomicCounter::exchange(
        const AtomicCounterType &newval)
    {
        return InterlockedExchange((AtomicCounterType*)&m_handle.counter,
            newval);
    }

    inline AtomicCounterType AtomicCounter::exchangeIf(
        const AtomicCounterType &newval,
        const AtomicCounterType &compval)
    {
        return InterlockedCompareExchange(
            (AtomicCounterType*)&m_handle.counter,
            newval,
            compval);

    }

} // end namespace
