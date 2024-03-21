#ifndef OSAL_WIN32_CONDITIONBASE_HXX
#define OSAL_WIN32_CONDITIONBASE_HXX

// to prevent annoying warnings on WIN32
#include <iplcompiler.h>

#include <common/types/queue.hxx>
#include <osal/Mutex.hxx>
#include <osal/Time.hxx>

namespace osal
{

/*
 * \brief
 *     A win32 Event object which offers a subset of what a condition
 *     needs to do
 */
class /*OSAL_EXPORT*/ Event
{
public:
    Event() :
        m_event(0)
    {
        this->create(NULL);
    }

    Event(const wchar_t *name) :
        m_event(0)
    {
        if(name)
        {
            this->create(name);
        }
    }

    ~Event()
    {
        close();
    }

    bool close()
    {
        if( isValid() && !CloseHandle(m_event) )
        {
            m_event = 0;
            return true;
        }

        m_event = 0;

        return false;
    }

    int_fast8_t wait(const DWORD dur)
    {
        DWORD wait_res = ::WaitForSingleObject( m_event, dur );

        if( wait_res == WAIT_FAILED )
            return -1;
        else if( wait_res == WAIT_TIMEOUT )
            return 1;
        else if( wait_res == WAIT_OBJECT_0 )
            return 0;

        // should that ever happen?
        return 2;
    }

    bool reset()
    {
        return !::ResetEvent(m_event);
    }

    bool set()
    {
        return !::SetEvent(m_event);
    }

    bool isValid() const
    {
        return m_event != 0;
    }

private:
    void create(const wchar_t *name)
    {
        m_event = ::CreateEventW( NULL, TRUE, FALSE, name );
#if 0
        if( this->isValid() && GetLastError() == ERROR_ALREADY_EXISTS )
        {
            // already existed i.e. we opened an existing
            // one
        }
#endif
    }

    HANDLE m_event;
};

template <class MUTEX>
/**
 * \brief
 *     Generic implementation of a condition based on a win32 event
 *     object and a mutex

 *     This is a template to allow use for Condition *and* ShmCondition
 **/
class OSAL_EXPORT ConditionBase
{
public: // types
    //! collected state variables for the condition implementation
    struct OSAL_EXPORT State
    {
        State() :
            // initially no one should be woken up
            current_wakeup_count(0),
            // initially no one is waiting
            current_waiter_count(0),
            // we start the generation ids at one
            next_generation_id(1),
            // the maximum generation ID allowed to wakeup
            // (zero for the start i.e. no one may wake up)
            max_wakeup_generation_id(0)
        {}

        /**
         * \brief
         *    this gives the number of threads that should
         *    currently wakeup due to signal[All] calls (this
         *    information is needed to know when to reset the
         *    condition signal)
         **/
        volatile uint32_t current_wakeup_count;
        /**
         * \brief
         *    this gives the number of threads that are
         *    currently waiting for something on the cond.
         **/
        volatile uint32_t current_waiter_count;
        // XXX overflow of this variable is not yet handled !
        /**
         * \brief
         *    this gives the next generation ID to be used for
         *    new waiters
         **/
        volatile uint32_t next_generation_id;
        /**
         * \brief
         *    this gives the highest generation ID that is
         *    currently allowed to wakeup
         **/
        volatile uint32_t max_wakeup_generation_id;
        /**
         * \brief
         *    this contains a number of generation_ids that
         *    are to be skipped regarding wakeup (generations
         *    that are skipped are the ones that exit the
         *    waitTimeout due to timeout)
         **/
        ipl::queue<uint32_t> skip_generations;
    };

public: // members
    //! \brief
    //!    A simple event object that allows for wait/signal
    //!    semantics
    Event m_event;
    //! A lock protecting all the counters and IDs
    MUTEX m_counter_lock;
    //! The current state of the condition
    State* m_state;

protected: // functions
    ConditionBase(State *state) :
        m_state(state)
    { }

public:
    bool isValid() const
    {
        return m_state && m_event.isValid() &&
            m_counter_lock.isValid();
    }

    int_fast8_t wait(MUTEX &lock, const osal::AbsTimeT *end_time);

    bool signal(const bool broadcast);
};

#ifndef OSAL_EXPORT_CONTEXT
extern template class ConditionBase<osal::Mutex>;
#endif

} // end ns osal

#endif // include guard
