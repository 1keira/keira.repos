/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

/*****************************************************************************/
#ifndef THREADSAFE_MUTEXIMPL_POSIX_HXX
#define THREADSAFE_MUTEXIMPL_POSIX_HXX

#ifndef IPL_OS_POSIX
#error Only valid on Posix
#endif
/*****************************************************************************/

#include "threadsafe_dso.h"
#include <iplbase/time.hxx>

#include <pthread.h>

/*****************************************************************************/

namespace threadsafe {

/*****************************************************************************/

    /*!
        \internal
        \brief Posix implementation of Mutex functionality
    */
    class THREADSAFE_EXPORT MutexImpl {

    public:
        MutexImpl(bool recursive) IPL_NOEXCEPT;
        ~MutexImpl() IPL_NOEXCEPT;

        const char *lock() IPL_NOEXCEPT;
        const char *unlock() IPL_NOEXCEPT;
        const char *try_lock() IPL_NOEXCEPT;
        const char *try_lock(const iplbase::Duration &timeout) IPL_NOEXCEPT;

    protected:
        pthread_mutex_t mutex;
        friend class ConditionImpl;  // may access mutex
    };

/*****************************************************************************/

}  // end of namespace threadsafe

/*****************************************************************************/
#endif
