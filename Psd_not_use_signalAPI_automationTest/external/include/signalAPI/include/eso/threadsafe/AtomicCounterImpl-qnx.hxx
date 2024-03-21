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

#ifndef IPL_OS_QNX
#error Only valid on QNX
#endif

#include <atomic.h>
#include _NTO_CPU_HDR_(smpxchg.h)

/*****************************************************************************/

//! \brief threadsafe::AtomicCounter is \b guaranteed to be efficient
#define THREADSAFE_ATOMICCOUNTER_IS_EFFICIENT

/*****************************************************************************/
/*
    The various magic incantations used here are inspired by
    http://community.qnx.com/sf/discussion/do/listPosts/projects.core_os/discussion.newcode.topc17261
*/
/*****************************************************************************/

namespace threadsafe {

/*****************************************************************************/

    /*!
        \internal
        \brief QNX implementation of AtomicCounter functionality
    */
    class /* THREADSAFE_EXPORT not allowed, inline-only */ AtomicCounterImpl {

    public:

        typedef unsigned value_type;

        AtomicCounterImpl(value_type initial) IPL_NOEXCEPT: counter(initial) {}

        value_type exchange(value_type set_to) IPL_NOEXCEPT {
            return _smp_xchg(&counter, set_to);
        }
        value_type exchange_if(value_type set_to, value_type if_equals) IPL_NOEXCEPT {
            return _smp_cmpxchg(&counter, if_equals, set_to);
        }
        value_type inc() IPL_NOEXCEPT { return atomic_add_value(&counter, 1); }
        value_type dec() IPL_NOEXCEPT { return atomic_sub_value(&counter, 1); }
        value_type get() const IPL_NOEXCEPT {
            return atomic_add_value(const_cast<value_type *>(&counter), 0);
        }

    protected:
        volatile value_type counter;
    };

/*****************************************************************************/

}  // end of namespace threadsafe

/*****************************************************************************/
#endif
