/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_POSIX_CONDITION_INL
#define OSAL_POSIX_CONDITION_INL

namespace osal
{

inline bool ConditionOps::destroy(pthread_cond_t *c)
{
    int res;

    // we might issue a signalAll() here but it is
    // questionable wheter this is a good idea at all - if the user
    // of the condition variable didn't care about shutting down
    // correctly then letting all waiting threads do one spin around
    // will most probably not be of much use as well.

    if( isValid(c) && (res = ::pthread_cond_destroy(c)) ) // BRANCH_COVERAGE_UNTESTABLE
    {
        return handleDestroyError(res);
    }

    return false;
}

// timed wait on a condition with absolute time
static inline int osal_pthread_cond_timedwait_abs(pthread_cond_t* condvar
                                                ,pthread_mutex_t* mutex
                                                ,const struct timespec* abstime)
{
    return
#ifdef HAVE_PTHREAD_COND_TIMEDWAIT_MONOTONIC_NP
    // Android's timed wait with absolute time using CLOCK_MONOTONIC
    ::pthread_cond_timedwait_monotonic_np(condvar, mutex, abstime);
#else
    ::pthread_cond_timedwait(condvar, mutex, abstime);
#endif
}

inline int_fast8_t ConditionOps::wait(
    pthread_cond_t *c,
    pthread_mutex_t *m,
    const struct timespec *t)
{
    int res;

    if( !t && (res = ::pthread_cond_wait(c, m)) ) // BRANCH_COVERAGE_UNTESTABLE
    {
        return handleWaitError(res);
    }
    else if ( t && (res = osal_pthread_cond_timedwait_abs(c, m, t) )) // BRANCH_COVERAGE_UNTESTABLE
    {
        return handleWaitError(res);
    }

    return Condition::WAIT_SIGNALED;
}

#ifdef USE_THREADSAFE_IN_OSAL
/* already defined where it belongs */
#else
inline int_fast8_t Condition::waitTimeout(osal::Mutex& lock,
    const osal::AbsTimeT &end_time)
{
    /* Since pthread_cond_timedwait() waits for an *absolute* time
     * since epoch (see man time) we'll need to construct a native
     * time struct from end_time
     */

    // note: this is no stupidity of the API developers. It is safer
    // to implement relative wait on top of absolute wait instead of
    // vice versa. Also some callers might want to wait for an
    // absolute time and if waitTimeout returns by spurious
    // interrupts then the caller has to recalculate its relative
    // time anew to reach that point in time.
    //
    // OSAL now does the same.

    /*
     *    the end_time is required to be acquired from
     *    Time::getTime() which uses the CLOCK_MONOTONIC.
     */

    struct timespec end_time_posix;
    end_time_posix.tv_sec = end_time.t / 1000;
    end_time_posix.tv_nsec = (end_time.t - (end_time_posix.tv_sec *
        1000)) * 1000 * 1000;

    return ConditionOps::wait(&m_handle.condition,
        &lock.m_handle.mutex, &end_time_posix);
}
#endif

inline bool ConditionOps::signal(pthread_cond_t *c)
{
    int res;

    if ( (res = ::pthread_cond_signal(c)) ) // BRANCH_COVERAGE_UNTESTABLE
    {
        return handleSignalError(res);

    }

    return false;
}

inline bool ConditionOps::broadcast(pthread_cond_t *c)
{
    int res;

    if ( (res = ::pthread_cond_broadcast(c)) ) // BRANCH_COVERAGE_UNTESTABLE
    {
        return handleSignalError(res);
    }

    return false;
}
    
#ifdef USE_THREADSAFE_IN_OSAL
/* already defined where it belongs */
#else
inline bool Condition::signal()
{
    return ConditionOps::signal( &m_handle.condition );
}
#endif

#ifdef USE_THREADSAFE_IN_OSAL
/* already defined where it belongs */
#else
inline bool Condition::signalAll()
{
    return ConditionOps::broadcast( &m_handle.condition );
}
#endif

#ifdef USE_THREADSAFE_IN_OSAL
/* already defined where it belongs */
#else
inline Condition::Condition() :
    // default initialisation
    m_handle()
{
    ConditionOps::init(&m_handle.condition, false);
}
#endif

#ifdef USE_THREADSAFE_IN_OSAL
/* already defined where it belongs */
#else
inline Condition::~Condition()
{
    if( ConditionOps::destroy( &m_handle.condition ) )
    {
        IPL_WARN("error destroying condition variable");
    }
}
#endif

#ifdef USE_THREADSAFE_IN_OSAL
/* already defined where it belongs */
#else
inline bool Condition::wait(osal::Mutex &p_lock)
{
    return ConditionOps::wait(&m_handle.condition,
        &p_lock.m_handle.mutex, NULL )
        != WAIT_SIGNALED;
}
#endif

} // end ns osal

#endif
