/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/


/*
    AtomicCounter Linux implementation.

    On Linux the atomic operations are a somewhat difficult matter. There's no dedicated
    user space API for atomic operations. In kernel space there exist macros or
    functions that can't be used, of course, in user space.

    Since gcc 4.1.x there exist some gcc-internal functions for doing atomic operations,
    though. As this is a fairly new compiler it might happen that OSAL is built with an
    older compiler and the according functions aren't available. Also it can happen that
    the functions aren't available on a certain hardware architecture. In the latter
    case gcc calls an undefined function of the same name. This function can then be
    provided by OSAL.
*/

#ifndef HAVE_ATOMIC_COUNTER
#    error "included AtomicCounter native header but HAVE_ATOMIC_COUNTER is not set"
#endif

#if defined(__GNUC__) && (__GNUC__ < 4)
    #warning "It's very probable that the atomic counter won't work for you, because your compiler is too old."
        " Add CMake flag -DHAVE_ATOMIC_COUNTER=0 or C preprocessor flag -DHAVE_ATOMIC_COUNTER=0 to the build process"
#endif

#ifndef __GNUC__
    #warning "Unknown compiler detected. Problems might occur (not only with the AtomicCounter)"
#endif

namespace osal
{

inline AtomicCounterType AtomicCounter::increment()
{
    return __sync_fetch_and_add(&m_handle.counter, 1);
}

inline AtomicCounterType AtomicCounter::decrement()
{
    return __sync_fetch_and_sub(&m_handle.counter, 1);
}

inline AtomicCounterType AtomicCounter::exchange(
    const AtomicCounterType &newval)
{
    return __sync_lock_test_and_set(&m_handle.counter, newval);
}

inline AtomicCounterType AtomicCounter::exchangeIf(
    const AtomicCounterType &newval,
    const AtomicCounterType &compval)
{
    return __sync_val_compare_and_swap(&m_handle.counter, compval, newval);
}

} // end namespace
