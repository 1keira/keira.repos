/*****************************************************************************/
/*
    Copyright esolutions GmbH
    All rights reserved
    Authors:
        Stefan Meinlschmidt
        Martin Stein
*/
/*****************************************************************************/
#ifndef PERSISTENCE_TNG_WORKERTHREAD_HXX
#define PERSISTENCE_TNG_WORKERTHREAD_HXX
/*****************************************************************************/

#include <ipl_config.h>

#include <persistence/Job.hxx>

#include <osal/Mutex.hxx>
#include <osal/Condition.hxx>
#include <util/Thread.hxx>
#include <util/IRunnable.hxx>
#include <util/SharedPtr.hxx>
#include <common/types/list.hxx>

/*****************************************************************************/

namespace persistence {

/*****************************************************************************/

    /*!
        \brief A Thread performing single jobs on behalf of someone else
    */
    class WorkerThread: public util::Thread, public util::IRunnable {

    public:

        class Job;
        class Observer;

        WorkerThread(const char *name, Observer *observer=NULL) IPL_NOEXCEPT:
            util::Thread(this, name),
               m_mutex(osal::Mutex::RECURSIVE), m_observer(observer) {}
        ~WorkerThread() IPL_NOEXCEPT;

        void schedule(const util::SharedPtr<Job> &job) IPL_NOEXCEPT;

    protected:
        virtual void threadLoop(const Thread* const thread);

        ipl::string     m_name;
        typedef ipl::list<util::SharedPtr<Job> > Jobs;
        Jobs            m_jobs;
        osal::Mutex     m_mutex;
        osal::Condition m_condition;
        Observer       *m_observer;
    };

/*****************************************************************************/

    //! \brief Base for jobs that are delegated to a WorkerThread
    class WorkerThread::Job {

    public:
        Job(const char *description) IPL_NOEXCEPT: m_description(description) {}
        virtual ~Job() IPL_NOEXCEPT {}

        ipl::string toString() const IPL_NOEXCEPT { return m_description; }

        //! \brief Perform the job, synchronously
        virtual void doIt() IPL_NOEXCEPT=0;

    protected:
        ipl::string m_description;
    };

/*****************************************************************************/

    //! \brief Interface for observing WorkerThread progress (e.g. watchdog)
    class WorkerThread::Observer {

    public:
        virtual ~Observer() IPL_NOEXCEPT;  //!< \brief Just to make the compiler happy...
        virtual void currentJob(void *thread, void *job) IPL_NOEXCEPT=0;
    };

/*****************************************************************************/

}  // end of namespace persistence

/*****************************************************************************/
#endif
