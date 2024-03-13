/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef THREADSAFE_CONDITIONIMPL_WIN32_HXX
#define THREADSAFE_CONDITIONIMPL_WIN32_HXX

#ifndef IPL_OS_WIN32
#error Only valid on Win32
#endif
/*****************************************************************************/

#include "threadsafe_dso.h"
#include "MutexImpl-win32.hxx"

#include <iplbase/time.hxx>
#include <iplbase/win32.h>

/*****************************************************************************/

namespace threadsafe {

/*****************************************************************************/

    /*!
        \internal
        \brief Posix implementation of Condition functionality
    */
    class THREADSAFE_EXPORT ConditionImpl {

    public:

        ConditionImpl(MutexImpl &mutex_impl) IPL_NOEXCEPT;
        ~ConditionImpl() IPL_NOEXCEPT;

        const char *wait() IPL_NOEXCEPT;
        const char *wait_timeout(const iplbase::TimePoint &end_time) IPL_NOEXCEPT;
        const char *signal_one() IPL_NOEXCEPT;
        const char *signal_all() IPL_NOEXCEPT;

    protected:

        struct Pending;  // defined in .cxx
        Pending * volatile pending;
        CRITICAL_SECTION internal_mutex;
        MutexImpl &mutex;
    };

/*****************************************************************************/

}  // end of namespace threadsafe

/*****************************************************************************/
#endif
