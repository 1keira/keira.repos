/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

/*****************************************************************************/
#ifndef THREADSAFE_TLSIMPL_POSIX_HXX
#define THREADSAFE_TLSIMPL_POSIX_HXX

#ifndef IPL_OS_POSIX
#error Only valid on Posix
#endif
/*****************************************************************************/

#include "threadsafe_dso.h"

#include <pthread.h>

/*****************************************************************************/

namespace threadsafe {

/*****************************************************************************/

    /*!
        \internal
        \brief Posix implementation of Tls functionality
    */
    class THREADSAFE_EXPORT TlsImpl {

    public:
        TlsImpl() IPL_NOEXCEPT;
        ~TlsImpl() IPL_NOEXCEPT;

        const char *set(void *p) IPL_NOEXCEPT;
        void *get() const IPL_NOEXCEPT;

    protected:
        pthread_key_t key;
    };

/*****************************************************************************/

}  // end of namespace threadsafe

/*****************************************************************************/
#endif
