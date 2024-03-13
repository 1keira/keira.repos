/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

/*****************************************************************************/
#ifndef THREADSAFE_ATOMICCOUNTER_HXX
#define THREADSAFE_ATOMICCOUNTER_HXX
/*****************************************************************************/

#include <ipl_config.h>

#if defined(HAVE_ATOMIC_SYNC)
#include "AtomicCounterImpl-gcc4.hxx"
#elif defined(HAVE_ATOMIC_SMP)
#include "AtomicCounterImpl-qnx.hxx"
#elif defined(IPL_OS_WIN32)
#include "AtomicCounterImpl-win32.hxx"
#elif defined(IPL_OS_INTEGRITY)
#include "AtomicCounterImpl-integrity.hxx"
#else
#include "AtomicCounterImpl-generic.hxx"
#endif

/*****************************************************************************/

namespace threadsafe {

/*****************************************************************************/

    /*!
        \brief Thread safe value, probably efficient

        \link2req{satisfies,req~FW_THREADSAFE_ATOMIC_COUNTER~1}
    */
    class /* THREADSAFE_EXPORT nope, inline-only */ AtomicCounter {

    public:

        typedef AtomicCounterImpl::value_type value_type;

        AtomicCounter(value_type initial=0) IPL_NOEXCEPT: impl(initial) {}

        //! \brief Set counter to \a set_to, return old value
        value_type exchange(value_type set_to) IPL_NOEXCEPT { return impl.exchange(set_to); }
        //! \brief Set counter to \a set_to if counter equals \a if_equals, return old/current value
        value_type exchange_if(value_type set_to, value_type if_equals) IPL_NOEXCEPT {
            return impl.exchange_if(set_to, if_equals);
        }
        //! \brief Increment counter, return old value
        value_type inc() IPL_NOEXCEPT { return impl.inc(); }
        //! \brief Decrement counter, return old value
        value_type dec() IPL_NOEXCEPT { return impl.dec(); }
        //! \brief Return current value
        value_type get() const IPL_NOEXCEPT { return impl.get(); }

        AtomicCounter &operator = (value_type val) IPL_NOEXCEPT {
            exchange(val);
            return *this;
        }
        operator value_type () const IPL_NOEXCEPT   { return get(); }
        value_type operator ++ (int) IPL_NOEXCEPT /* suffix */ { return inc(); }
        value_type operator -- (int) IPL_NOEXCEPT /* suffix */ { return dec(); }
        value_type operator ++ () IPL_NOEXCEPT    /* prefix */ { return inc()+1; }
        value_type operator -- () IPL_NOEXCEPT    /* prefix */ { return dec()-1; }

    protected:
        AtomicCounterImpl impl;
    };

/*****************************************************************************/

}  // end of namespace threadsafe

/*****************************************************************************/
#endif
