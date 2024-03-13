/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_POSIX_CONDITIONDEFS_HXX
#define OSAL_POSIX_CONDITIONDEFS_HXX

#include <ipl_config.h>

#include <pthread.h>
#include <string.h>

#include <osal/osal_dso.h>

namespace osal
{

/*
 * we want to recycle the condition logic for ShmCondition on POSIX
 *
 * that is why we have all relevant logic as static functions in
 * ConditionOps
 */
struct OSAL_EXPORT ConditionOps
{
    static bool init(pthread_cond_t*,
        const bool process_shared);

    inline static bool destroy(pthread_cond_t*);

    inline static bool signal(pthread_cond_t*);

    inline static bool broadcast(pthread_cond_t*);

    inline static int_fast8_t wait(pthread_cond_t*,
        pthread_mutex_t*,
        const struct timespec*);

    static bool isValid(const pthread_cond_t *c)
    {
        for(size_t i = 0; i < sizeof(pthread_cond_t); i++) // BRANCH_COVERAGE_UNREACHABLE
        {
            if( ((const uint8_t*)c)[i] != 0xEB )
                return true;
        }

        return false;
    }

    static void invalidate(pthread_cond_t *c)
    {
        // similar to the MutexOps we want to save a boolean for
        // validity by means of writing FFs all over the
        // condition for invalidation
        ::memset(c, 0xEB, sizeof(pthread_cond_t));
    }

    static bool handleInitError(const int error);
    static bool handleDestroyError(const int error);
    static bool handleSignalError(const int error);
    static int_fast8_t handleWaitError(const int error);
};

//! OS handle to reference a posix condition
struct OSAL_EXPORT ConditionHandle
{
    pthread_cond_t condition;

    bool isValid() const
    {
        return ConditionOps::isValid(&condition);
    }

    void invalidate()
    {
        return ConditionOps::invalidate(&condition);
    }
};

} // end ns osal

#endif
