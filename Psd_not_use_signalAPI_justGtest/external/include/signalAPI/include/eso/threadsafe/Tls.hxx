/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

/*****************************************************************************/
#ifndef THREADSAFE_TLS_HXX
#define THREADSAFE_TLS_HXX
/*****************************************************************************/

#include <ipl_config.h>

#if defined(THREADSAFE_USE_GENERIC_TLS)
#include "TlsImpl-generic.hxx"
#elif defined(IPL_OS_POSIX)
#include "TlsImpl-posix.hxx"
#elif defined(IPL_OS_WIN32)
#include "TlsImpl-win32.hxx"
#elif defined(IPL_OS_INTEGRITY)
#include "TlsImpl-integrity.hxx"
#else
#error Unsupported OS
#endif

#include "TlsBase.hxx"

/*****************************************************************************/

namespace threadsafe {

/*****************************************************************************/

    /*!
        \brief Thread-local storage for one pointer.

        This class implements vital functionality not provided by C++ thread_local: dynamically allocates key on TLS.

        \link2req{satisfies,req~FW_THREADSAFE_TLS~1}
    */
    class /* THREADSAFE_EXPORT nope, inline-only */
    Tls: public TlsBase {

    public:

        Tls() IPL_NOEXCEPT {}

        const char *set(void *p) IPL_NOEXCEPT { return impl.set(p); }
        void *get() const IPL_NOEXCEPT        { return impl.get();  }

    protected:
        TlsImpl impl;
    };

/*****************************************************************************/

}  // end of namespace threadsafe

/*****************************************************************************/
#endif
