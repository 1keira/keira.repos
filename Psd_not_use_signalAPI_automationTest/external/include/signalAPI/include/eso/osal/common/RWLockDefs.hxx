/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_COMMON_RWLOCKDEFS_HXX
#define OSAL_COMMON_RWLOCKDEFS_HXX

/*
 *    For the common OSAL impl. of RWLock we simply rely on osal Mutex
 *    and Condition primitives.
 *
 *    This way the RWLock can easily be implemented, providing all
 *    features.
 */

#include <osal/osal_dso.h>
#include <osal/Condition.hxx>
#include <osal/Mutex.hxx>

namespace osal
{

template <class MUTEX, class CONDITION>
/**
 * \brief
 *     Generic implementation of an RWLock based on Condition variables
 *     and a Mutex

 *     This is a template to allow use for RWLock *and* ShmRWLock.
 *
 *     CONDITION may be osal::Condition or osal::ShmCondition
 *     MUTEX may be osal::Mutex or osal::ShmMutex
 *
 *     m_state may reside on the stack, on the heap or in a shared
 *     memory area.
 **/
struct OSAL_EXPORT RWLockBase
{
public: // types

    //! collected state variables for the RWLock implementation
    struct OSAL_EXPORT State
    {
        State() :
            readers_active(0),
            writers_active(0),
            readers_waiting(0),
            writers_waiting(0)
        { }

        uint_fast32_t readers_active;
        uint_fast32_t writers_active;
        uint_fast32_t readers_waiting;
        uint_fast32_t writers_waiting;
    };

public: // members
    //! a condition for writers to wait on to get the write lock
    mutable CONDITION m_writers;
    //! a condition for readers to wait on to get the read lock
    mutable CONDITION m_readers;
    //! \brief
    //! a lock to use with m_writers, m_readers and for safe access
    //! to m_state
    mutable MUTEX m_lock;

protected: // members
    //! the current counters associated with RWLock state
    State *m_state;

protected: // functions
    RWLockBase(State *state) :
        m_state(state)
    { }

    ~RWLockBase()
    {
    #ifdef IPL_DEBUG
        IPL_ASSERT(!m_state || !m_state->readers_active);
        IPL_ASSERT(!m_state || !m_state->writers_active);
        IPL_ASSERT(!m_state || !m_state->readers_waiting);
        IPL_ASSERT(!m_state || !m_state->writers_waiting);
    #endif
    }

public:
    bool isValid() const
    {
        return m_state && m_writers.isValid() &&
            m_readers.isValid() && m_lock.isValid();
    }

    int_fast8_t readLock(const uint_fast32_t *timeout) const;

    int_fast8_t writeLock(const uint_fast32_t *timeout) const;

    bool unlock() const;
};

struct OSAL_EXPORT RWLockHandle :
    public RWLockBase<osal::Mutex, osal::Condition>
{
private: // members
    RWLockBase<osal::Mutex, osal::Condition>::State state;

public: // functions
    RWLockHandle() :
        RWLockBase<osal::Mutex, osal::Condition>(&state)
    { }
};

} // end ns osal

#endif
