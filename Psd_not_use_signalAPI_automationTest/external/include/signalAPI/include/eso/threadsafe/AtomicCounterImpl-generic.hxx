/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

/*****************************************************************************/
#ifndef THREADSAFE_ATOMICCOUNTERIMPL_GENERIC_HXX
#define THREADSAFE_ATOMICCOUNTERIMPL_GENERIC_HXX
/*****************************************************************************/

#include "threadsafe_dso.h"
#include "Mutex.hxx"

/*****************************************************************************/

// Do not define: threadsafe::AtomicCounter is not efficient!
// #define THREADSAFE_ATOMICCOUNTER_IS_EFFICIENT

/*****************************************************************************/

namespace threadsafe {

/*****************************************************************************/

    /*!
        \internal
        \brief Generic fallback implementation of AtomicCounter functionality

        This is only intended for systems without native atomic functionality
        as it is not as efficient as you normally would expect from
        an atomic counter.
    */
    class THREADSAFE_EXPORT AtomicCounterImpl {

    public:

        typedef unsigned value_type;

        AtomicCounterImpl(value_type initial) IPL_NOEXCEPT: counter(initial) {}

        value_type exchange(value_type set_to) IPL_NOEXCEPT;
        value_type exchange_if(value_type set_to, value_type if_equals) IPL_NOEXCEPT;
        value_type inc() IPL_NOEXCEPT;
        value_type dec() IPL_NOEXCEPT;
        value_type get() const IPL_NOEXCEPT;

    protected:
        Mutex mutex;
        value_type counter;
    };

/*****************************************************************************/

}  // end of namespace threadsafe

/*****************************************************************************/
#endif
