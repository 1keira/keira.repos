/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

/*****************************************************************************/
#ifndef THREADSAFE_ATOMICCOUNTERIMPL_INTEGRITY_HXX
#define THREADSAFE_ATOMICCOUNTERIMPL_INTEGRITY_HXX
/*****************************************************************************/

#include <ipl_config.h>

// #include "threadsafe_dso.h"

#ifndef IPL_OS_INTEGRITY
#error Only valid on Integrity
#endif

#include <INTEGRITY.h>

/*****************************************************************************/

//! \brief threadsafe::AtomicCounter is \b guaranteed to be efficient
#define THREADSAFE_ATOMICCOUNTER_IS_EFFICIENT

/*****************************************************************************/

namespace threadsafe {

/*****************************************************************************/

    /*!
        \internal
        \brief Integrity implementation of AtomicCounter functionality
    */
    class /* THREADSAFE_EXPORT not allowed, inline-only */ AtomicCounterImpl {

    public:
        typedef Address value_type;

        AtomicCounterImpl(value_type initial) IPL_NOEXCEPT: counter(initial) {}

        value_type exchange(value_type set_to) IPL_NOEXCEPT {
            value_type old_val;
            AtomicModify (&counter, &old_val, (Address) -1, set_to);
            return old_val;
        }

        value_type exchange_if(value_type set_to, value_type if_equals) IPL_NOEXCEPT {
            value_type old_val;
            // as INTEGRITY's atomic operations I/F does not satisfy our SW needs, the following
            // construct is chosen to deliver the old_val in a reasonable manner
            while (1)
            {
                old_val = counter;
                if (old_val == if_equals) {
                    if (TestAndSet (&counter, if_equals, set_to) == Success)
                        return old_val;
                } else
                    return old_val;
            }
        }

        value_type inc() IPL_NOEXCEPT {
            value_type old_val;
            AtomicModify (&counter, &old_val, 0, 1);
            return old_val;
        }

        value_type dec() IPL_NOEXCEPT {
            value_type old_val;
            AtomicModify (&counter, &old_val, 0, (value_type) -1);
            return old_val;
        }

        value_type get() const  IPL_NOEXCEPT{ return counter; }

    protected:
        volatile value_type counter;
    };

/*****************************************************************************/

}  // end of namespace threadsafe

/*****************************************************************************/
#endif
