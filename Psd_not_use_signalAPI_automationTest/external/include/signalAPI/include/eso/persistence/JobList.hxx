/*****************************************************************************/
/*
    Copyright esolutions GmbH
    All rights reserved
    Authors:
        Stefan Meinlschmidt
        Martin Stein
*/
/*****************************************************************************/
#ifndef PERSISTENCE_JOBLIST_HXX_
#define PERSISTENCE_JOBLIST_HXX_
/*****************************************************************************/

#include <ipl_config.h>

#include <common/types/list.hxx>
#include <osal/Mutex.hxx>
#include <util/SharedPtr.hxx>

/*****************************************************************************/

namespace persistence {

    class Core;
    class Job;
    class Event;

}

/*****************************************************************************/

namespace persistence {

/*****************************************************************************/

    class JobList {

    public:
        JobList(int32_t warn_level, int32_t error_level) IPL_NOEXCEPT;

        /*!
            \brief Add a new job to the job list

            \b Warning: Unsynchronized, only call from Core thread

            \param[in] job
                the job instance to add to the list
            \return false on success, true on error
            \errorindicator
                    return value
            \errors none
            
            \note
                calling this method the m_mutex has to be locked by the caller
        */
        bool add(const util::SharedPtr<Job> &job) IPL_NOEXCEPT;

        /*!
            \brief Call the process method of the event for all jobs in the list,
            remove jobs that ask for it and pull the emergency brake if requested

            \b Warning: Unsynchronized, only call from Core thread

            \param[in] ev
                event to be processed
        */
        void processEvent(const util::SharedPtr<Event> &ev) IPL_NOEXCEPT;

        size_t size() const IPL_NOEXCEPT { return m_jobs.size(); }

        //! \brief Abort and remove all transient jobs
        void reset() IPL_NOEXCEPT;
        //! \brief Dump status information to the tracechannel FW_PERSISTENCE_STATUS
        //!
        //! \b Warning: Unsynchronized, only call from Core thread
        void traceStatus() IPL_NOEXCEPT;
        
        //! \brief Retrieve Job currently being fed with events
        //!
        //! \b Warning: Unsynchronized, only call from Core thread
        Job *currentJob() const IPL_NOEXCEPT { return m_current_job.retrieve(); }

    private:

        // Just needed for unit tests:
        int32_t getSizeWarn() { return SIZE_WARN; }
        int32_t getSizeErr() { return SIZE_ERR; }
        bool isWarned() { return m_warned; }

        const int32_t SIZE_WARN;
        const int32_t SIZE_ERR;
        bool m_warned;

        // the running jobqueue is locked by a blocking job
        typedef ipl::list<util::SharedPtr<Job> > Jobs;
        Jobs m_jobs;

        //! \brief Used internally by processEvent()
        //!
        //! This is a member so that currentJob() can determine the Job
        //! currently fed with events and ultimately
        //! Core::getBlame() can output it.
        //! Do not even think of writing to this variable!
        // Not object state but method-internal processing state,
        // hence mutable is OK
        mutable util::SharedPtr<Job> m_current_job;

        /* record some statistics */
        int m_max_size;

        JobList(const JobList&);
        JobList& operator=(const JobList&);
    };

/*****************************************************************************/

}  // end of namespace persistence

/*****************************************************************************/
#endif
