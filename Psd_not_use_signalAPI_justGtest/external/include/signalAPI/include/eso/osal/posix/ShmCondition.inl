/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_POSIX_SHMCONDITION_INL
#define OSAL_POSIX_SHMCONDITION_INL

namespace osal {

    inline bool ShmCondition::attach(
        void *shm_addr,
        const bool initialize,
        const bool auto_destroy)
    {
        if( this->close() ) // BRANCH_COVERAGE_UNTESTABLE
        {
            IPL_WARN("error closing shm condition");
        }

        m_handle = ShmConditionHandle(shm_addr, auto_destroy);

        if( initialize &&  // BRANCH_COVERAGE_UNTESTABLE
            ConditionOps::init( m_handle.shm_cond, true ) )
        {
            m_handle.invalidate();
        }
        else if( ! initialize && !this->isValid() )
        {
            ipl_raise( Error, Condition::CREATE_FAILED,
                "there seems to be no valid ShmCondition at the given location" );
        }

        return !this->isValid();
    }

    inline bool ShmCondition::close()
    {
        bool ret = false;

        if( m_handle.isValid() && m_handle.autoDestroy() )
        {
            if( destroy( m_handle.shm_cond ) ) // BRANCH_COVERAGE_UNTESTABLE
            {
                ret = true;
            }
        }

        m_handle.invalidate();

        return ret;
    }

    inline bool ShmCondition::destroy( void *shm_addr )
    {
        const bool ret = ConditionOps::destroy(
            (pthread_cond_t*)shm_addr );

        ConditionOps::invalidate( (pthread_cond_t*)shm_addr );

        return ret;
    }

    inline bool ShmCondition::wait(osal::ShmMutex &p_lock)
    {
        return ConditionOps::wait(
            m_handle.shm_cond,
            p_lock.m_handle.shm_mutex, NULL ) != WAIT_SIGNALED;
    }

    inline int_fast8_t ShmCondition::waitTimeout(osal::ShmMutex &p_lock,
        const osal::AbsTimeT &end_time)
    {
        struct timespec end_time_posix;
        end_time_posix.tv_sec = end_time.t / 1000;
        end_time_posix.tv_nsec = (end_time.t - (end_time_posix.tv_sec *
            1000)) * 1000 * 1000;

        return ConditionOps::wait(
            m_handle.shm_cond,
            p_lock.m_handle.shm_mutex,
            &end_time_posix );
    }

    inline bool ShmCondition::signal()
    {
        return ConditionOps::signal( m_handle.shm_cond );
    }

    inline bool ShmCondition::signalAll()
    {
        return ConditionOps::broadcast( m_handle.shm_cond );
    }

} // end ns osal

#endif
