/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_THREADPOOL_HXX
#define UTIL_THREADPOOL_HXX

#include <ipl_config.h>

#include <util/util_dso.h>

#include <common/types/list.hxx>
#include <common/types/string.hxx>
#include <common/types/deque.hxx>

#include <util/Thread.hxx>
#include <osal/Mutex.hxx>
#include <osal/AtomicCounter.hxx>

namespace util
{

/**
 * \brief
 *     The interface for dynamic thread pool functionality

 *     A ThreadPool is a group of threads that are created and kept
 *     ready for any work that might come up. An util::IRunnable
 *     interface can be passed to the pool to execute an arbitrary job
 *     in a separate thread. The advantage of this approach is that
 *     threads aren't created dynamically during runtime but are setup
 *     in the first place and the execution of thread jobs is then done
 *     faster when it comes to.
 *
 *     The ThreadPool class allows more fine grained tuning. For
 *     example it is possible to specify a static amount of threads
 *     that are always kept alive. Additionally a dynamic thread amount
 *     can be specified that allows the pool to create additional
 *     thread in case that a high amount of work is running and no more
 *     threads are available. These dynamically created threads may be
 *     removed again when the workload drops later on.
 *
 *     Features/Requirements:
 *     -# FW_UTIL_TP_STATIC_POOL
 *     -# FW_UTIL_TP_SHOULD_DYNAMIC_EXTEND
 *     -# FW_UTIL_TP_QUEUE queuing of new tasks when pool full
 *     -# FW_UTIL_TP_QUEUE_PRIO priorities for queued tasks (not)
 *     -# FW_UTIL_TP_SHOULD_TIMEOUT if pool is unused cancel idle tasks
 *     or kill active (only interface)
 *     -# FW_UTIL_TP_QUIT_OPTION offer strong 'kill' option for tasks
 *     of the ThreadPool is reduced again.
 **/
class UTIL_EXPORT ThreadPool
{
public: // types
    /**
     * \brief
     *    Type offering available task quitting options
    **/
    enum TaskQuitPolicy
    {
        /**
         * \brief
         *     Always kill running threads without wait for
         *     exit or join (dangerous! best not use it)
         **/
        TASK_KILL,
        //! Always wait for tasks to quit and join (cooperative).
        TASK_JOIN
    };

    /**
     * \brief
     *    Type offering available queueing options
    **/
    enum QueueType
    {
        //! \brief
        //! Before creating a new thread, wake an idle one from
        //! the pool
        QU_FIRST_WAKE,
        //! \brief
        //!    Always create a new thread if possible first
        //! \warning
        //!    This variant is not yet implemented
        QU_FIRST_CREATE
    };

public: // static data

    //! Maximum allowed items in queue
    static const uint16_t MAX_ITEM_SIZE = UINT16_MAX;
    //! default pattern for the pool's thread names
    static const char* POOL_THREAD_NAME;
public: // functions
    /**
     * \brief
     *     The only constructor. Offers detailed settings but also
     *     sensible default values
     * \param[in] staticsize
     *     The fixed amount of threads in the pool. Zero is allowed
     *     -> results in an all dynamic thread pool. Zero is only
     *     valid if maxsize is non-zero.
     * \param[in] maxsize
     *    The total amount of threads that can be created (i.e.
     *    the maximum size consisting of the static amount of
     *    threads plus a number of dynamically creatable threads.
     *    Has to be greater or equal to staticsize. Default is
     *    zero which means no dynamic threads are created.
     * \param[in] kill_timeout
     *    A time in milliseconds that is granted to threads before
     *    they are killed if quitpolicy is TASK_KILL
     * \param[in] qtype
     *    Queuing behaviour of threads in the pool.
     * \param[in] quitpolicy
     *    Quit behaviour for threads in the pool.
     * \errorindicator
     *    via isValid()
     * \errors
     *    ipl::CommonError with IDs:
     *
     *    - OUT_OF_MEMORY if a thread could not be allocated
     *
     *    util::Thread::Error with IDs:
     *
     *    - CREATE_FAILED if one of the pool threads could not be
     *    created
     *    - START_FAILED if one of the pool threads could not be
     *    started
    **/
    ThreadPool(const uint16_t staticsize,
        const uint16_t maxsize = 0,
        const uint32_t kill_timeout = 0,
        const QueueType qtype = QU_FIRST_WAKE,
        const TaskQuitPolicy quitpolicy = TASK_JOIN) IPL_NOEXCEPT;

    /**
     * \brief
     *     The only constructor. Offers detailed settings but also
     *     sensible default values
     * \param[in] thread_name
     *    A pattern for the pool thread names. The pool will add
     *    a number when it names a thread.
     * \param[in] staticsize
     *     The fixed amount of threads in the pool. Zero is allowed
     *     -> results in an all dynamic thread pool. Zero is only
     *     valid if maxsize is non-zero.
     * \param[in] maxsize
     *    The total amount of threads that can be created (i.e.
     *    the maximum size consisting of the static amount of
     *    threads plus a number of dynamically creatable threads.
     *    Has to be greater or equal to staticsize. Default is
     *    zero which means no dynamic threads are created.
     * \param[in] kill_timeout
     *    A time in milliseconds that is granted to threads before
     *    they are killed if quitpolicy is TASK_KILL
     * \param[in] qtype
     *    Queuing behaviour of threads in the pool.
     * \param[in] quitpolicy
     *    Quit behaviour for threads in the pool.
     * \errorindicator
     *    via isValid()
     * \errors
     *    ipl::CommonError with IDs:
     *
     *    - OUT_OF_MEMORY if a thread could not be allocated
     *
     *    util::Thread::Error with IDs:
     *
     *    - CREATE_FAILED if one of the pool threads could not be
     *    created
     *    - START_FAILED if one of the pool threads could not be
     *    started
    **/
    ThreadPool(
        const ipl::string& thread_name,
        const uint16_t staticsize,
        const uint16_t maxsize = 0,
        const uint32_t kill_timeout = 0,
        const QueueType qtype = QU_FIRST_WAKE,
        const TaskQuitPolicy quitpolicy = TASK_JOIN) IPL_NOEXCEPT;

    /**
     * \brief
     *    Virtual destructor to satisfy gcc and C++ gurus

     *    Ensures that destructor of base class gets always called
     **/
    virtual ~ThreadPool() IPL_NOEXCEPT;

    /**
     * \brief
     *    Queue an IRunnable for execution

     *    Note that the oject pointer passed to the pool must
     *    exist. NULL pointers are not allowed here.
     * \param[in] task
     *    The external task to be run.
     * \return
     *    true on error, false otherwise
     * \errorindicator
     *    via return code
     * \errors
     *    ipl::CommonError with IDs:
     *
     *    - ITEM_OVERFLOW if the maximum number of pool tasks has
     *    been reached
    **/
    bool execute(IRunnable* const task) IPL_NOEXCEPT;

    /**
     * \brief
     *    Remove a previously issued item from the thread pool
     * \note
     *    This is only useful if the task has not yet been
     *    executed. If it has been or is currently being executed
     *    than this function will return false.
     * \warning
     *    If you have issued the same task multiple times then the
     *    only one of the issued tasks will be removed.
     * \param[in] task
     *    The already issued task not to be executed any more.
     * \return
     *    true if removing was sucessful
    **/
    bool remove(IRunnable* task) IPL_NOEXCEPT;

    /**
     * \brief
     *    Returns the amount of tasks that have not yet been
     *    worked on by the ThreadPool
     * \return
     *    Number of tasks not worked on yet.
     **/
    uint_fast16_t getRemainingTasks() IPL_NOEXCEPT;

    /**
     * \brief
     *    Return the type of queue currently set
     * \return
     *    The queue type.
    **/
    QueueType getQueueType() const IPL_NOEXCEPT
    {
        return m_qtype;
    }

    /**
     * \brief
     *    Return the active amount of threads currently executing
     *    tasks
     * \return
     *    The amount of active threads.
     * \note
     *    Can't be const because mutex->lock is needed
     **/
    uint16_t getActiveCount() IPL_NOEXCEPT;

    /**
     * \brief
     *    Get the static (fixed) size of the pool
     * \return
     *    The amount of fixed threads used in the pool.
    **/
    uint16_t getStaticSize() const IPL_NOEXCEPT
    {
        return m_staticsize;
    }

    /**
     * \brief
     *    Return the total size of the pool, including dynamically
     *    created threads
     * \return
     *    The current amount of threads existing.
     * \note
     *    Can't be const as of mutex->lock
    **/
    uint16_t getCurrentSize() IPL_NOEXCEPT;

    /**
     * \brief
     *    Get the maximum size of the pool (static and dynamic)
     * \return
     *    The maximum size of threads allowed.
    **/
    uint16_t getMaxSize() const IPL_NOEXCEPT
    {
        return m_maxsize;
    }

    /**
     * \brief
     *    Return the grant time before a thread is kill if quit
     *    policy is TASK_KILL
     * \return
     *    The maximum allowed time granted a thread before it
     *    joins the ThreadPool
    **/
    uint32_t getKillTimeout() const IPL_NOEXCEPT
    {
        return m_kill_timeout;
    }

    /**
     * \brief
     *    Wait until all tasks of the pool have become idle and no
     *    more tasks are pending for execution

     *    To make sure no tasks are outstanding in the pool a call
     *    to this function can be used. It blocks until the last
     *    task has been executed.
     *
     *    Beware that if tasks are added to the pool dynamically
     *    then a call to joinPool may never return in case the
     *    tasks never reach a zero level. Thus it is best if no
     *    tasks at all are added to the pool while you are
     *    performing a call to joinPool.
     *
     *    This function can be used to safely determine when
     *    destruction of a ThreadPool is safe as the destruction
     *    may leave some tasks behind unfinished.
     **/
    void joinPool() IPL_NOEXCEPT;

    bool isValid() const IPL_NOEXCEPT
    { return m_valid; }

protected: // functions
    /**
     * \brief
     *    virtual function to be used for advanced execution
     *    control

     *    The function gets called just before a tasks gets
     *    executed by a thread.
     * \param[in] task
     *    The task that is going to be executed.
    **/
    virtual void beforeExecute(IRunnable* const task) {};

    /**
     * \brief
     *    Virtual function to be used for advanced execution
     *    control. The function gets called just after a tasks
     *    gets executed by a thread.
     * \warning
     *    if the executed task throws an exception, this function
     *    will not be called.  See 'afterExecutionFailed'
     *    function.
     * \param[in] task
     *    The task that was executed.
    **/
    virtual void afterExecute(IRunnable* const task) { };

private: // types
    /**
     * \brief
     *    Class derived from util::Thread to hold external tasks
     *    runtime information

     *    This is a private class to hold the status and task
     *    information for each internal thread-task tuple.
     **/
    class ProxyThread :
        public util::Thread,
        // for every thread in the thread pool we need our own
        // runnable to control thread execution
        public util::IRunnable
    {
    public:
        /**
         * \brief
         *    Creates a named pool thread.

         *    IplException handling is not done, since an
         *    errornous pointer would mean the whole thread
         *    pool being broken.
         * \param[in] homepool
         *    The pointer to the controlling thread pool.
         * \param[in] name
         *    Thread name.
        **/
        ProxyThread(util::ThreadPool* const homepool, const ipl::string& name) IPL_NOEXCEPT;

        /**
         *  \brief
         *    The thread entry function for our thread control
         *    logic inside the ThreadPool

         *    Tasks are encapsulated into a protective block
         *    to ensure an exception does never kill the
         *    thread.
         **/
        void threadLoop(const util::Thread* const);

        /**
         * \brief
         *    Set the external task to be executed by this
         *    thread

         *    This value should either be NULL if currently
         *    unset or represent a valid pointer.
         * \param[in] task
           *    The task to be executed.
        **/
        void setRunnable(IRunnable* const task) IPL_NOEXCEPT
        {
            m_task = task;
        }

    private:
        //! \brief
        //! The task that was externally set and will actually
        //! be executed.
        IRunnable* m_task;
        //! A reference to the daddy-pool.
        util::ThreadPool* const m_ppool;
    }; // end class

    //! Internal state type for task protection at shutdown
    enum PoolState
    {
        RUNNING = 0,
        SHUTDOWN
    };

private: // functions

    /*
     * \brief
     *    Common init function for construction of the object
    */
    void init();


    //! Reschedule tasks after "change events"
    void reschedule();

    //! Set threads to be used again after finishing tasks
    void announceFree(ProxyThread* freethread);

private: // members

    //! The main queue for new and running tasks.
    ipl::deque<util::IRunnable*> m_tqueue;
    //! The actual container for all idle threads.
    ipl::deque<util::ThreadPool::ProxyThread*> m_idlepool;
    //! The actual container for all active threads.
    ipl::list<util::ThreadPool::ProxyThread*> m_activepool;
    //! joinable threads
    ipl::list<util::ThreadPool::ProxyThread*> m_joinable;

    //! The policy for quitting/exiting/killing threads.
    const TaskQuitPolicy m_quitpolicy;

    //! The sole fixed size of the thread pool.
    const uint16_t m_staticsize;
    //! \brief
    //! The time in ms. that is granted a to be stopped thread if
    //! quit policy is TASK_KILL
    const uint32_t m_kill_timeout;
    //! \brief
    //! Maximum size of the pool including static and dynamic
    //! threads
    const uint16_t m_maxsize;

    //! The queueing policy for the thread handling
    const QueueType m_qtype;

    //! \brief
    //! Protect complex data structures from cross access of
    //! internal proxy-threads
    osal::Mutex m_data_lock;
    //! Protect the shutdown process from list access
    osal::Mutex m_state_lock;

    //! internal state of thread pool
    volatile PoolState m_state;

    //! \brief
    //! a condition used to indicate when all tasks in the pool have
    //! finished
    osal::Condition m_join_event;

    //! validity of the object
    bool m_valid;

    osal::AtomicCounter m_join_token;
    void joinJoinable();
    void quickJoin();
    bool getJoinToken();
    void putJoinToken();

    // thread naming helpers
    // thread pool instabce counter for unnamed threads
    static osal::AtomicCounter    m_inst_counter;
    // counter for this pool's thread
    unsigned                     m_thread_counter;
    ipl::string                    m_thread_name;

}; // end class thread pool

} // namespace

#endif // UTIL_THREADPOOL_HXX
