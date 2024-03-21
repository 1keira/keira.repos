/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

/*****************************************************************************/
#ifndef THREADSAFE_ATOMICCOUNTERIMPL_QNX_HXX
#define THREADSAFE_ATOMICCOUNTERIMPL_QNX_HXX
/*****************************************************************************/

#include <ipl_config.h>

// #include "threadsafe_dso.h"

#ifndef HAVE_ATOMIC_SYNC
#error Only valid when __sync_* intrinsics are available
#endif

/*****************************************************************************/

//! \brief ipl::AtomicCounter is \b guaranteed to be efficient
#define THREADSAFE_ATOMICCOUNTER_IS_EFFICIENT

/*****************************************************************************/
/*
    See http://gcc.gnu.org/onlinedocs/gcc-4.1.2/gcc/Atomic-Builtins.html
    for docu about the intrinsics
*/
/*****************************************************************************/

namespace threadsafe {

/*****************************************************************************/

    /*!
        \internal
        \brief GCC/ICC intrinsics implementation of AtomicCounter functionality
    */
    class /* THREASDAFE_EXPORT nope, inline-only */ AtomicCounterImpl {

    public:

        // "GCC will allow any integral scalar or pointer type that is
        // 1, 2, 4 or 8 bytes in length."
        // "If a particular operation cannot be implemented on the target
        // processor, a warning will be generated and a call an external
        // function will be generated."
        // https://gcc.gnu.org/onlinedocs/gcc-4.4.3/gcc/Atomic-Builtins.html
        typedef unsigned value_type;

        AtomicCounterImpl(value_type initial) IPL_NOEXCEPT: counter(initial) {}

        value_type exchange(value_type set_to) IPL_NOEXCEPT {
            return __sync_lock_test_and_set(&counter, set_to);
        }
        value_type exchange_if(value_type set_to, value_type if_equals) IPL_NOEXCEPT {
            return __sync_val_compare_and_swap(&counter, if_equals, set_to);
        }
        value_type inc() IPL_NOEXCEPT { return __sync_fetch_and_add(&counter, 1); }
        value_type dec() IPL_NOEXCEPT { return __sync_fetch_and_sub(&counter, 1); }
        value_type get() const IPL_NOEXCEPT {
            return __sync_fetch_and_add(const_cast<value_type *>(&counter), 0);
        }

    protected:
        value_type counter;
    };

/*****************************************************************************/

}  // end of namespace threadsafe

/*****************************************************************************/
#endif
