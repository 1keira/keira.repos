/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_ATOMICCOUNTER_HXX
#define OSAL_ATOMICCOUNTER_HXX

#include <osal/osal_dso.h>

#ifdef USE_THREADSAFE_IN_OSAL

#include <threadsafe/AtomicCounter.hxx>

namespace osal {

    typedef threadsafe::AtomicCounter::value_type AtomicCounterType;

    //! \brief Deprecated legacy wrapper around threadsafe::AtomicCounter
    class AtomicCounter: private threadsafe::AtomicCounter {

    public:
        AtomicCounter(const AtomicCounterType initial=1):
            threadsafe::AtomicCounter(initial) {}

        AtomicCounterType increment() { return inc(); }
        AtomicCounterType decrement() { return dec(); }
        using threadsafe::AtomicCounter::exchange;
        AtomicCounterType exchangeIf(AtomicCounterType set_to,
                                     AtomicCounterType if_equals) {
            return exchange_if(set_to, if_equals);
        }
        AtomicCounterType getCurrentCount() const { return get(); }
        using threadsafe::AtomicCounter::operator ++;
        using threadsafe::AtomicCounter::operator --;
        using threadsafe::AtomicCounter::operator =;

        AtomicCounter &operator = (const AtomicCounter &other) {
            operator = ((const threadsafe::AtomicCounter &)other);
            return *this;
        }

        AtomicCounter(const AtomicCounter& other) = default;

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4522)  // "multiple assignment operators specified"
#endif
    };
#ifdef _MSC_VER
#pragma warning(pop)
#endif

}  // end of namespace osal

#else

#include <ipl_config.h>

#ifdef HAVE_ATOMIC_COUNTER
//#    if defined (IPL_OS_ANDROID) || defined (IPL_OS_LINUX)
#ifdef IPL_OS_POSIX
#        include "linux/AtomicCounterDefs.hxx"
#    elif defined (IPL_OS_QNX)
#        include "qnx/AtomicCounterDefs.hxx"
#    elif defined (IPL_OS_WINPC)
#        include "win32/AtomicCounterDefs.hxx"
#    else
#        error "error undefined IPL_OS_ variant"
#    endif
#else
#    include "common/AtomicCounterDefs.hxx"
#endif

namespace osal
{

/**
 * \brief
 *    The AtomicCounter class implements efficient, thread-safe
 *    operations on native integer values

 *    This class's operations are realised using efficient atomic
 *    operations instead of the usual mutex locking operations that
 *    might involve system calls in case of contention.
 *
 *    These atomic operations might not be available on every
 *    platform. Thus as a fallback implementation involving
 *    traditional mutexes or apropriate system calls will be used to
 *    realise this functionality, if required.
 *
 *    The atomic operations allow to safely:
 *
 *    * increment the integer by one, retrieving the old/new value
 *    * decrement the integer by one, retrieving the old/new value
 *    * exchanging the integer by a new value, retrieving the old
 *    value
 *    * exchanging the integer by a new value, if the current value
 *    matches a given value, returning the old value
 *
 *    Note that you cannot provide a userspace-only locking facility
 *    using these operations. Locking between threads cannot be
 *    achieved in userspace alone. In case of contention there's
 *    a system call needed to resolve the situation without polling.
 *
 *    This counter class is particularly valuable for implementing
 *    reference counting mechanisms.
 * \note
 *    The underlying POD data type for this counter varies between
 *    platforms. Usually it is a native word of the target CPU i.e. a
 *    4 byte integer on 32 bit systems. On some compiler/os
 *    combinations it's int, long etc. and some make it signed or
 *    unsigned. But usually it's unsigned.
 *
 *    That's why OSAL provide the AtomicCounterType type that maps to
 *    the correct underlying type. It should be considered to be an
 *    unsigned, efficient integer for the target platform.
**/
class AtomicCounter
{
public:
    /**
     * \brief
     *    Construct the atomic counter assigning an initial value

     *     The default initial value is one.
     **/
    AtomicCounter(const AtomicCounterType p_initval = 1)
    {
        // this operation is still safe as we're the
        // first to know about this object.
        m_handle.counter = p_initval;
    }

    /**
     * \brief
     *    Increments the counter by one
     * \return
     *    The value of the counter before the increment operation
     *    took place is returned.
     **/
    inline AtomicCounterType increment();

    /**
     * \brief
     *    Decrements the counter by one
     * \note
     *    Be aware that OSAL suggest that the atomic counter is
     *    always unsigned even if on some OSs it is actually
     *    signed (i.e. Win32). Using negative counter values thus
     *    results in undefined behaviour. If a count of zero is
     *    reached no decrement should be called any more. OSAL
     *    doesn't check that as it would increase the cost of this
     *    operation unnecessarily.
     * \return
     *    The value of the counter before the decrement operation
     *    took place is returned.
     **/
    inline AtomicCounterType decrement();

    /**
     * \brief
     *     Sets the counter to \c newval, returning the previous
     *     value
     **/
    inline AtomicCounterType exchange(const AtomicCounterType &newval);

    /**
     * \brief
     *     Sets the counter to \c newval if the current value
     *     equals \c compval

     *     This exchange operation only takes place if the current
     *     counter value matches \c compval. The returned value
     *     will be the value that was encountered when attempting
     *     the operation. This means if \c compval is returned then
     *     the exchange operation will have taken place. Otherwise
     *     no modification was done.
     **/
    inline AtomicCounterType exchangeIf(const AtomicCounterType &newval,
        const AtomicCounterType &compval);

    /**
     * \brief
     *    Returns the current counter value
     **/
    AtomicCounterType getCurrentCount() const
    {
        // reading a word usually can't be interrupted so no
        // special precautions should be necessary
        return m_handle.counter;
    }

    /**
     * \brief
     *    Shortcut operator for increment, prefix variant
     * \return
     *     The value after the increment operation took place
     **/
    AtomicCounterType operator++()
    {
        return increment() + 1;
    }

    /**
     * \brief
     *    Shortcut operator for decrement, prefix variant
     * \return
     *     The value after the decrement operation took place
     **/
    AtomicCounterType operator--()
    {
        return decrement() - 1;
    }

    /**
     * \brief
     *    Shortcut operator for increment, postfix variant
     * \return
     *     The value before the increment operation took place
     **/
    AtomicCounterType operator++(int)
    {
        return increment();
    }

    /**
     * \brief
     *    Shortcut operator for decrement, postfix variant
     * \return
     *     The value before the decrement operation took place
     **/
    AtomicCounterType operator--(int)
    {
        return decrement();
    }

    /**
     * \brief
     *     Atomically changes the current value of the counter to
     *     \c val
     **/
    AtomicCounter& operator=(const AtomicCounterType &val)
    {
        this->exchange(val);

        return *this;
    }
private:
    //! \brief
    //!    this is the actual variable containing the current
    //!    counter value.
    AtomicCounterHandle m_handle;
};

} // end namespace

#ifdef HAVE_ATOMIC_COUNTER
#    if defined (IPL_OS_ANDROID) || defined (IPL_OS_LINUX)
#        include "linux/AtomicCounter.inl"
#    elif defined (IPL_OS_QNX)
#        include "qnx/AtomicCounter.inl"
#    elif defined (IPL_OS_WINPC)
#        include "win32/AtomicCounter.inl"
#    else
#        error "error undefined IPL_OS_ variant"
#    endif
#else
#    include "common/AtomicCounter.inl"
#endif

#endif  // def USE_THREADSAFE_IN_OSAL

#endif // OSAL_ATOMICCOUNTER_HXX
