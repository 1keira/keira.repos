/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_CONDITION_HXX
#define OSAL_CONDITION_HXX

#include <ipl_config.h>

#include <common/NonCopyable.hxx>
#include <common/error/Error.hxx>
#include <common/align.hxx>

#ifdef USE_THREADSAFE_IN_OSAL
#include <threadsafe/Condition.hxx>
#endif

#ifdef IPL_OS_POSIX
#    include "posix/ConditionDefs.hxx"
#elif defined (IPL_OS_WINPC)
#    include "win32/ConditionDefs.hxx"
#elif defined (IPL_OS_INTEGRITY)
#else
#    error "error undefined IPL_OS_ variant"
#endif

#include <osal/osal.hxx>
#include <osal/osal_dso.h>
#include <osal/Mutex.hxx>
#include <osal/SysError.hxx>
#include <osal/Time.hxx>

namespace osal
{

/**
 * \brief
 *     A Condition object

 *     A Condition object provides a special kind of synchronization
 *     between threads.  While an osal::Mutex simply protects a shared
 *     ressource an Condition does more. It addresses the
 *     consumer/producer paradigm. If a producing thread provides some
 *     data to be handled by a consuming thread then the consuming
 *     thread should have a facility to efficiently wait for new data
 *     provided by the producing thread and then safely access that
 *     data.
 *
 *     To achieve the safety part an osal::Mutex is coupled with the
 *     Condition. The procedure is the following: The consuming thread
 *     acquires an osal::Mutex that is shared by both threads. This
 *     mutex protects some state flag.  Thus when the consuming thread
 *     has got the mutex it checks the flag that indicates wheter new
 *     data is available. If this is the case then the data is
 *     extracted, the mutex released and the data can be worked on.
 *
 *     If no data is available, however, then the consuming thread
 *     waits on an Condition for an event. The Condition takes the
 *     already locked osal::Mutex, unlocks it and waits for an event or
 *     "condition" to be in effect. This condition is signaled by the
 *     producing thread. When the producing thread has produced new
 *     data then it acquires the mutex, sets the state flag and signals
 *     the condition. When this is done then the consuming thread
 *     returns from its Condition wait call with the osal::Mutex locked
 *     again. Thus the state flag can be checked and if new data is
 *     available (which is most times the case but must not be even if
 *     the condition has been signaled!) the work can be done.
 * \code
 *     // A Condition should be bound to a predicate and is dependent
 *     // on a mutex.
 *
 *     Condition g_Condition;
 *     osal::Mutex g_protection_mutex;
 *     // Predicate to mark "Data available"
 *     bool g_data_avail_flag = false;
 *
 *     // ==================================================
 *     // Assume thread A as a Consumer (Receiver) for some
 *     // data.
 *     // ==================================================
 *     // thread A:
 *
 *     void waitForData()
 *     {
 *         g_protection_mutex.lock();
 *
 *         // Wait until "Data available"
 *         while (g_data_avail_flag == false)
 *         {
 *             // attention: this call unlocks the mutex
 *             // automatically!
 *             g_Condition.wait(g_protection_mutex);
 *         }
 *
 *         // fetch data
 *
 *         g_data_avail_flag = false; // Resume "Data available"
 *
 *         // release the mutex
 *         g_protection_mutex.unlock();
 *
 *         // perform work on data
 *     }
 *
 *     // ==================================================
 *     // Assume osal::Thread B as a Sender (notifier for osal::Thread
 *     // A) for some data.
 *     // ==================================================
 *     // osal::Thread B:
 *
 *     void signalReceiver()
 *     {
 *         // produce data
 *
 *         // signal consumer thread
 *         g_protection_mutex.lock();
 *         g_data_avail_flag = true; // Mark "Data available"
 *         g_Condition.signal();
 *         g_protection_mutex.unlock();
 *     }
 * \endcode
**/
class OSAL_EXPORT Condition :
    // a condition should never be copied
    public ipl::NonCopyable
{
public: // types

    //! specific condition error IDs
    enum ConditionErrors
    {
        CREATE_FAILED = 0,
        // WAIT_FAILED is already set on win32
        WAIT_FAIL,
        SIGNAL_FAILED
    };

    //! Condition specific error type
    static ipl::ErrorType Error;

    //! return code from waitTimeout() on signal
    static const int_fast8_t WAIT_SIGNALED = 0;
    //! return code from waitTimeout() on timeout
    static const int_fast8_t WAIT_TIMEDOUT = 1;
    //! return code from waitTimeout() on error
    static const int_fast8_t WAIT_ERROR = -1;

public: // functions
    /**
      * \brief
      *     Create a Condition ready for use
      * \errorindicator
      *     via isValid()
      * \errors
      *     Condition::Error with ID CREATE_FAILED attached with a
      *     SysError with IDs:
      *
      *     - SYSTEM_RESSOURCES_EXHAUSTED on lack of ressources
      *     other than memory
      *     - OUT_OF_MEMORY on lack of memory
      *     - INTEGRITY_ERROR on severe errors
    **/
    inline Condition();

    /**
     * \brief
     *     Destructor for a Condition Variable

     *     On errors destroying the condition IPL_WARN will be
     *     triggered.
     * \warning
     *     No more threads should be waiting on the condition
     *     object at destruction time. Otherwise undefined
     *     behaviour results.
     * \note
     *     This is kept non-virtual to avoid increase of object
     *     size. It is improbable that anybody will inherit from
     *     Condition.
    **/
    inline /*virtual*/ ~Condition();

    /**
     *  \brief
     *     Wait until the Condition will be signaled

     *     The wait() function is used to block on a Condition
     *     variable. It has to be called with the passed mutex
     *     locked by the calling thread or undefined behaviour will
     *     result.
     *
     *     The function call will then block until another thread
     *     calls the signal or signalAll function. In this case the
     *     blocking call returns for at least one waiting thread
     *     and the thread competes to acquire the passed mutex
     *     again.  When the function call returns successfully then
     *     the mutex is owned by the calling thread again.
     *  \note
     *     Multiple thread may issues a wait call, all using the
     *     same mutex and condition variable. Upon one signal()
     *     call is issued then at least one of the waiting threads
     *     is released. Upon signalAll() is issued all of the
     *     currently waiting threads are released.
     *  \param
     *     p_lock The mutex associated with the Condition variable.
     *     This mutex must have the osal::Mutex::BINARY MutexType.
     *  \warning
     *     Using different osal::Mutex objects with the same
     *     Condition instance will end up in undefined behaviour.
     *     The condition object is bound to the mutex object that
     *     it is first used with.
     *  \warning
     *     The wait call may also return if nothing of interest
     *     happened at all (e.g.  due to spurious interrupts). Thus
     *     a boolean state flag or something alike is usually used
     *     to check wheter something actually happened. The return
     *     of the wait call alone doesn't indicate anything.
     *  \warning
     *     Beware of threads with different priority that call
     *     wait() on the same condition variable. A deadlock may
     *     occur as the thread that should wake might never be
     *     scheduled by the OS.
     *  \return
     *     true on error, false on success.
     *  \see
     *     waitTimeout()
     *  \errors
     *     Condition::Error with ID WAIT_FAIL is raised if
     *
     *     - \c p_lock isn't currently owned by the calling thread
     *     - if a different \c p_lock has been used with this
     *     condition before.
     *     - Condition of \c p_lock are invalid
     *     - \c p_lock is of the wrong type (i.e. not BINARY)
     *
     *     attached will be a SysError, if apropriate
     *  \errorindicator
     *     via return code
    **/
    inline bool wait(osal::Mutex &p_lock);

    /**
     *  \brief
     *     Wait until either the Condition will be signaled or
     *     until \c end_time is reached

     *     The semantic of this function is the same as the one of
     *     wait(). The only difference is that if until \c end_time
     *     the condition object wasn't signaled by another thread
     *     then the call returns.
     *     <br>
     *     This is indicated by means of a return value > 0. Even
     *     if the timeout occurs the mutex shall still be owned by
     *     the calling thread after returning from the waitTimeout()
     *     function.
     *     <br>
     *     The clock used for this timeout calculation is a
     *     monotonic clock i.e. it won't jump.
     *  \param[in,out]
     *     lock The mutex associated with the Condition variable.
     *  \param[in]
     *     end_time The absolute time until the blocking call
     *     should last when no signal occurs. If end_time is less
     *     or equal the current time then no wait will be done but
     *     only the current state will be checked and acted
     *     accordingly. This type can be obtained from
     *     osal::Time::getTime(const osal::TimeT&).
     *  \note
     *     Even if the call returns with a negative indication i.e.
     *     the timeout was triggered the condition may still have
     *     changed due to race conditions. Thus a check of the
     *     corresponding flag is still something that should be
     *     done after returning from this call.
     *     <br>
     *     As the case with the plain wait() function it may happen
     *     that this function returns returning positive indication
     *     but still there hasn't happened anything at all. In this
     *     case you can continue the timeout-wait by simply turning
     *     in the same \c end_time again.
     *  \return
     *     zero if the call has been unblocked by a signal() or
     *     signalAll() invocation.  > 0 if the call returned,
     *     because \c end_time has been reached. < 0 if an error
     *     occured.
     *  \see
     *     wait()
     *  \errors
     *     \see wait()
     *  \errorindicator
     *     if < 0 is returned then an error occured.
     **/
    inline int_fast8_t waitTimeout(osal::Mutex &lock,
        const osal::AbsTimeT &end_time);

    /**
     *  \brief
     *     Signal a thread waiting on a condition variable

     *     The call to this function causes a thread that is
     *     currently blocked by calling wait() or waitTimeout() at
     *     the condition variable to be unblocked and contend for
     *     gaining the mutex.
     *     <br>
     *     If multiple threads are waiting on the condition
     *     variable then the thread that is selected to be
     *     unblocked is determined by the scheduling policy of the
     *     OS. It may also happen that more than only one thread is
     *     unblocked in this case. Each thread that is unblocked
     *     shall contend for gaining the mutex as if each had
     *     called osal::Mutex::lock().
     *  \note
     *     Note that you do not need to have the corresponding
     *     mutex locked when calling signal. If you do have locked
     *     the mutex during the call to signal, however, then you
     *     should release the mutex afterwards to allow the
     *     signaled threads to acquire the mutex and start running.
     *     <br>
     *     Locking the mutex before calling signal may result in a
     *     more predictable wakeup order of multiple waiting
     *     threads. On the other hand it imposes a possible
     *     performance penalty, because threads may be scheduled
     *     for wakeup immediatly but they can't do anything as the
     *         thread calling signal() still holds the mutex.
     *  \return
     *     true on error, false on success.
     *  \errors
     *     Condition::Error with ID SIGNAL_FAILED is raised if
     *
     *     - Condition variable is invalid
     *  \errorindicator
     *     if true is returned an error occured.
     *  \see
     *     signalAll()
     **/
    inline bool signal();

    /**
     * \brief
     *     Signal all threads currently waiting on a condition
     *     variable

     *     The call to signalAll causes at least all currently
     *     waiting threads to be signaled. All threads that wake up
     *     due to this call contend for gaining the mutex as if
     *     they called osal::Mutex::lock(). It can happen that some
     *     threads that subsequently call wait() or waitTimeout()
     *     during or immediatly after a call to signalAll() also
     *     get signaled.
     *     <br>
     *     Sadly it also may happen that instead on of one (or
     *     more) of the currently waiting threads one (or more) of
     *     subsequently waiting threads get signaled.  This
     *     particularly applies to the WIN32 implementation.
     *
     *     The semantic of signalAll is equal to the signal()
     *     function otherwise.
     * \return
     *     true on error, false on success.
     * \errors
     *     see signal()
     * \errorindicator
     *     if true is returned an error occured.
     * \see
     *     signal()
     **/
    inline bool signalAll();

    //! returns true if the construction succeeded, false otherwise
    bool isValid() const
#ifdef USE_THREADSAFE_IN_OSAL
        { return true; }
#else
    { return m_handle.isValid(); }
#endif
private:
#ifdef USE_THREADSAFE_IN_OSAL

    class UglyHack: public iplbase::TimePoint {
    public:
        explicit UglyHack(TimeT absolute_ticks) {
            set_ms((Ticks)absolute_ticks);
        }
    };

    threadsafe::Mutex internal_mutex;
    Mutex *mutex;
#ifdef HAVE_ALIGNAS  // __alignas_is_defined is buggy in the supplied headers
    alignas(threadsafe::Condition) unsigned char condition_buf[sizeof(threadsafe::Condition)];
#else  // else just hope for the best...
    union {
        long long alignment_dummy;
        unsigned char condition_buf[sizeof(threadsafe::Condition)];
    };
#endif
#else
    //! handle for native condition object
    ConditionHandle m_handle;
#endif
}; // class Condition

} // end namespace

#ifdef USE_THREADSAFE_IN_OSAL

osal::Condition::Condition():
    mutex(NULL)
{
    /* NOP */
}

osal::Condition::~Condition()
{
    threadsafe::Mutex::Guard lock(internal_mutex);
    threadsafe::Condition *condition=
        ipl::cast_without_warning<threadsafe::Condition *>(&condition_buf);
    if(mutex)
        condition->~Condition();
}

bool osal::Condition::wait(osal::Mutex &lock)
{
    internal_mutex.lock();
    if(mutex) {
        if(mutex!=&lock) {
            ipl_raise(SysError, INTEGRITY_ERROR, "Using Condition with different Mutexes");
            internal_mutex.unlock();
            return true; //WAIT_ERROR;
        }
    } else {
        mutex=&lock;
        new(condition_buf) threadsafe::Condition(mutex->mutex);
    }
    internal_mutex.unlock();

    threadsafe::Condition *condition=
        ipl::cast_without_warning<threadsafe::Condition *>(&condition_buf);
    if(const char *res=condition->wait()) { // BRANCH_COVERAGE_UNTESTABLE
        ipl_raise(SysError, INTEGRITY_ERROR, res);
        return true; //WAIT_ERROR;
    }

    return false; //WAIT_SIGNALED;
}

int_fast8_t osal::Condition::waitTimeout(osal::Mutex &lock,
                                         const osal::AbsTimeT &end_time)
{
    internal_mutex.lock();
    if(mutex) {
        if(mutex!=&lock) {
            ipl_raise(SysError, INTEGRITY_ERROR, "Using Condition with different Mutexes");
            internal_mutex.unlock();
            return WAIT_ERROR;
        }
    } else {
        mutex=&lock;
        new(condition_buf) threadsafe::Condition(mutex->mutex);
    }
    internal_mutex.unlock();

    threadsafe::Condition *condition=
        ipl::cast_without_warning<threadsafe::Condition *>(&condition_buf);
    if(const char *res=condition->wait_timeout(UglyHack(end_time.t))) {
        if(res==threadsafe::Condition::TIMEOUT) { // BRANCH_COVERAGE_UNTESTABLE
            return WAIT_TIMEDOUT;
        } else {
            ipl_raise(SysError, INTEGRITY_ERROR, res);
            return WAIT_ERROR;
        }
    }

    return WAIT_SIGNALED;
}

bool osal::Condition::signalAll()
{
    threadsafe::Mutex::Guard lock(internal_mutex);
    if(!mutex)
        return false;

    threadsafe::Condition *condition=
        ipl::cast_without_warning<threadsafe::Condition *>(&condition_buf);
    if(const char *res=condition->signal_all()) { // BRANCH_COVERAGE_UNTESTABLE
        ipl_raise(SysError,
                  res==threadsafe::Condition::ERROR_INCONSISTENCY? INTEGRITY_ERROR : UNKNOWN_ERROR, // BRANCH_COVERAGE_UNTESTABLE
                  res);
        return true;
    }

    return false;
}

bool osal::Condition::signal()
{
    threadsafe::Mutex::Guard lock(internal_mutex);
    if(!mutex)
        return false;

    threadsafe::Condition *condition=
        ipl::cast_without_warning<threadsafe::Condition *>(&condition_buf);
    if(const char *res=condition->signal_one()) { // BRANCH_COVERAGE_UNTESTABLE
        ipl_raise(SysError,
                  res==threadsafe::Condition::ERROR_INCONSISTENCY? INTEGRITY_ERROR : UNKNOWN_ERROR, // BRANCH_COVERAGE_UNTESTABLE
                  res);
        return true;
    }

    return false;
}

#else

#ifdef IPL_OS_POSIX
#    include "posix/Condition.inl"
#elif defined (IPL_OS_WINPC)
#    include "win32/Condition.inl"
#else
#    error "error undefined IPL_OS_ variant"
#endif

#endif

//! \brief
//! a macro that waits on a condition/mutex pair and on error aborts the
//! program
#define IPL_CONDITION_WAIT_OR_ABORT(C, M) if( C.wait(M) ) \
    { IPL_ABORT("error waiting on condition"); }

#define IPL_CONDITION_SIGNAL_OR_ABORT(C) if( C.signal() ) \
    { IPL_ABORT("error signaling condition"); }

#define IPL_CONDITION_SIGNALALL_OR_ABORT(C) if( C.signalAll() ) \
    { IPL_ABORT("error signaling condition"); }

#endif
