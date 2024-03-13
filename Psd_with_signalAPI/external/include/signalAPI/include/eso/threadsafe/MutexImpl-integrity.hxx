/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

/*****************************************************************************/
#ifndef THREADSAFE_MUTEXIMPL_INTEGRITY_HXX
#define THREADSAFE_MUTEXIMPL_INTEGRITY_HXX

#ifndef IPL_OS_INTEGRITY
#error Only valid on Integrity
#endif
/*****************************************************************************/

#include "threadsafe_dso.h"
#include <iplbase/time.hxx>

#include <INTEGRITY.h>

/*****************************************************************************/

namespace threadsafe {

/*****************************************************************************/

    /*!
        \internal
        \brief Integrity implementation of Mutex functionality
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
        Semaphore  mutex;
        friend class ConditionImpl;  // may access mutex

    private:
        bool recursive;
    };

/*****************************************************************************/

}  // end of namespace threadsafe

/*****************************************************************************/
#endif
