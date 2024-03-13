/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

/*****************************************************************************/
#ifndef THREADSAFE_CONDITIONIMPL_INTEGRITY_HXX
#define THREADSAFE_CONDITIONIMPL_INTEGRITY_HXX

#ifndef IPL_OS_INTEGRITY
#error Only valid on Integrity
#endif
/*****************************************************************************/

#include "threadsafe_dso.h"
#include "MutexImpl-integrity.hxx"

#include <iplbase/time.hxx>

#include <INTEGRITY.h>

/*****************************************************************************/

namespace threadsafe {

/*****************************************************************************/

    /*!
        \internal
        \brief Integrity implementation of Condition functionality
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
        Condition  condition;
        Semaphore &mutex;
    };

/*****************************************************************************/

}  // end of namespace threadsafe

/*****************************************************************************/
#endif
