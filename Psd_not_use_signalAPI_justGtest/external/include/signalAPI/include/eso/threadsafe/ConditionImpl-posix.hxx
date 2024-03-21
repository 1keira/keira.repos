/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

/*****************************************************************************/
#ifndef THREADSAFE_CONDITIONIMPL_POSIX_HXX
#define THREADSAFE_CONDITIONIMPL_POSIX_HXX

#ifndef IPL_OS_POSIX
#error Only valid on Posix
#endif
/*****************************************************************************/

#include "threadsafe_dso.h"
#include "MutexImpl-posix.hxx"

#include <iplbase/time.hxx>

#include <pthread.h>

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
        pthread_cond_t  condition;
        pthread_mutex_t &mutex;
    };

/*****************************************************************************/

}  // end of namespace threadsafe

/*****************************************************************************/
#endif
