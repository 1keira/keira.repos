/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

/*****************************************************************************/
#ifndef THREADSAFE_TLSIMPL_WIN32_HXX
#define THREADSAFE_TLSIMPL_WIN32_HXX

#ifndef IPL_OS_WIN32
#error Only valid on Win32
#endif
/*****************************************************************************/

#include "threadsafe_dso.h"

#include <iplbase/win32.h>

/*****************************************************************************/

namespace threadsafe {

/*****************************************************************************/

    /*!
        \internal
        \brief Win32 implementation of Tls functionality
    */
    class THREADSAFE_EXPORT TlsImpl {

    public:
        TlsImpl() IPL_NOEXCEPT;
        ~TlsImpl() IPL_NOEXCEPT;

        const char *set(void *p) IPL_NOEXCEPT;
        void *get() const IPL_NOEXCEPT;

    protected:
        DWORD key;
    };

/*****************************************************************************/

}  // end of namespace threadsafe

/*****************************************************************************/
#endif
