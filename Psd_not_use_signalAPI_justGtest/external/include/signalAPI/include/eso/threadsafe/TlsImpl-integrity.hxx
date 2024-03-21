/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

/*****************************************************************************/
#ifndef THREADSAFE_TLSIMPL_INTEGRITY_HXX
#define THREADSAFE_TLSIMPL_INTEGRITY_HXX

#ifndef IPL_OS_INTEGRITY
#error Only valid on Integrity
#endif
/*****************************************************************************/

#include "threadsafe_dso.h"

#include <INTEGRITY.h>

/*****************************************************************************/

namespace threadsafe {

/*****************************************************************************/

    /*!
        \internal
        \brief Integrity implementation of Tls functionality
    */
    class THREADSAFE_EXPORT TlsImpl {

    public:
        TlsImpl() IPL_NOEXCEPT;
        ~TlsImpl() IPL_NOEXCEPT;

        const char *set(void *p) IPL_NOEXCEPT;
        void *get() const IPL_NOEXCEPT;

    protected:
        TaskKey *key;
    };

/*****************************************************************************/

}  // end of namespace threadsafe

/*****************************************************************************/
#endif
