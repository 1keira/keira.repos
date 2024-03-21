/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

/*****************************************************************************/
#ifndef THREADSAFE_ATOMICCOUNTERIMPL_WIN32_HXX
#define THREADSAFE_ATOMICCOUNTERIMPL_WIN32_HXX
/*****************************************************************************/

#include <ipl_config.h>

// #include "threadsafe_dso.h"

#ifndef IPL_OS_WIN32
#error Only valid on Win32
#endif

#include <iplbase/win32.h>

/*****************************************************************************/

// Do not define: threadsafe::AtomicCounter is not guaranteed to be efficient!
// #define THREADSAFE_ATOMICCOUNTER_IS_EFFICIENT

/*****************************************************************************/

namespace threadsafe {

/*****************************************************************************/

    /*!
        \internal
        \brief Windows implementation of AtomicCounter functionality
    */
    class /* THREADSAFE_EXPORT not allowed, inline-only */ AtomicCounterImpl {

    public:

        typedef LONG value_type;

        AtomicCounterImpl(value_type initial) IPL_NOEXCEPT: counter(initial) {}

        value_type exchange(value_type set_to) IPL_NOEXCEPT {
            return InterlockedExchange(&counter, set_to);
        }
        value_type exchange_if(value_type set_to, value_type if_equals) IPL_NOEXCEPT {
            return InterlockedCompareExchange(&counter, set_to, if_equals);
        }
        value_type inc() IPL_NOEXCEPT { return InterlockedIncrement(&counter)-1; }
        value_type dec() IPL_NOEXCEPT { return InterlockedDecrement(&counter)+1; }
        // "Simple reads and writes to properly-aligned 32-bit variables are
        // atomic operations."
        // https://msdn.microsoft.com/de-de/library/windows/desktop/ms684122(v=vs.85).aspx
        value_type get() const IPL_NOEXCEPT { return counter; }

    protected:
        volatile value_type counter;
    };

/*****************************************************************************/

}  // end of namespace threadsafe

/*****************************************************************************/
#endif
