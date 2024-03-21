/*****************************************************************************/
/*
    Copyright esolutions GmbH
    All rights reserved
    Authors:
        Stefan Meinlschmidt
        Martin Stein
*/
/*****************************************************************************/
#ifndef PERSISTENCE_CORE_HXX_
#define PERSISTENCE_CORE_HXX_
/*****************************************************************************/

#include <ipl_config.h>

#include <osal/Time.hxx>
#include <osal/AtomicCounter.hxx>
#include <util/Thread.hxx>
#include <util/config/Values.hxx>
#include <comm/SingleThreadedActiveObjectFactory.hxx>
#include <persistence/EventQueue.hxx>
#include <persistence/Job.hxx>
#include <persistence/JobList.hxx>

/*****************************************************************************/

IPL_TRACE_DECLARE_CHANNEL_EXTERN(FW_PERSISTENCE_CORE);

/*****************************************************************************/

class TestJobAndEventQueue;  // for unit-test purpose

/*****************************************************************************/

namespace persistence {

/*****************************************************************************/

    class Core: public util::Thread, public util::IRunnable {

    public:

        //! \brief Sequence number for asynchronous requests
        typedef uint32_t Seqnum;
        struct Config;
        enum ConnectionLogEntryEvent {
            CONNECTION_ESTABLISHED = 0,
            CONNECTION_CLOSED
        };

        Core(const Config &config) IPL_NOEXCEPT;
        ~Core() IPL_NOEXCEPT;

        /*!
            \brief Start the thread and do everythin to get the core running
            \errorindicator
                return code
            \return    true on error, false on success
        */
        bool startup() IPL_NOEXCEPT;

        /*!
            \brief Shutdown everything and stop the core thread

            \b Warning: Do not call from Core thread!
            
            \errorindicator
                return code
            \return    true on error, false on success
        */
        bool shutdown() IPL_NOEXCEPT;

        /*!
            \brief Worker thread main loop
        */
        virtual void threadLoop(const Thread* const thread);

        //! \brief Testing only
        void addJob(util::SharedPtr<Job>& job) IPL_NOEXCEPT {
            m_job_list.add(job);
        }

        void enqueue(const util::SharedPtr<Event> &event) IPL_NOEXCEPT;
        Seqnum seqnum() IPL_NOEXCEPT { return m_seqnum++; }

        //! \brief Tracing callback to traceout the status of some core information
        void traceStatus(int32_t cbid, void * const data, size_t len) IPL_NOEXCEPT;

        //! \brief Retrieve reason for whatever \e currently happens in order to
        //! add to a trace message
        //!
        //! \b Warning: Call from core thread only,
        //! explicitly copy into other threads!
        ipl::string getBlame() const IPL_NOEXCEPT;

        //! brief    add a connection event
        void connectionEvent (const ipl::string& client, ConnectionLogEntryEvent event) IPL_NOEXCEPT;

        size_t getMaxDataChunkSize() IPL_NOEXCEPT { return (size_t)m_max_datachunk_size; }

        const int32_t max_jobs;    //!< \brief Max. number of jobs in list
        const int32_t max_events;  //!< \brief Max. number of events in queue

        class Job;
        friend class Job;

        static constexpr auto DEFAULT_JOBS_WARN_LEVEL   {100};
        static constexpr auto DEFAULT_JOBS_ERROR_LEVEL  {150};
        static constexpr auto DEFAULT_EVENTS_WARN_LEVEL {200};
        static constexpr auto DEFAULT_EVENTS_ERROR_LEVEL{250};
        
        static constexpr auto UNLIMITED_DATACHUNK_SIZE    {0};
        
    private:

        struct ConnectionLogEntry {
            ipl::string             m_client;
            osal::TimeT             m_timestamp;
            ConnectionLogEntryEvent m_event;
        };

        JobList             m_job_list;
        EventQueue          m_event_queue;
        //! \brief Flag requesting the core thread to empty the event queue and
        //! abort all transient jobs to recover from overflow situations
        osal::AtomicCounter m_emergency_brake;
        
        //! \brief Used internally by the threadLoop()
        //!
        //! This is a member so that getBlame() can determine the Event
        //! currently processed.
        //! Do not even think of writing to this variable!
        util::SharedPtr<Event> m_current_event;

        //! \brief for unit-test purpose
        friend class ::TestJobAndEventQueue;

        Seqnum m_seqnum;

        typedef ipl::vector<ConnectionLogEntry> ConnectionLog;
        ConnectionLog m_connection_log;

        size_t m_max_datachunk_size;
    };

/*****************************************************************************/

    /*!
        \brief Handling events in lieu of the Core
    */
    class Core::Job: public persistence::Job {

    public:

        class EventShutdown;

        Job(Core &core) IPL_NOEXCEPT: persistence::Job(core, "Core::Job") {}

        static JobType TYPE;

        virtual bool abort() IPL_NOEXCEPT;
        virtual void *cast(const JobType& type) IPL_NOEXCEPT;
        virtual void start() IPL_NOEXCEPT;

        //! \brief Shut down core
        virtual void shutdown() const IPL_NOEXCEPT;
        //! \brief Add \a job to core's job list and start it
        virtual void addAndStart(const util::SharedPtr<persistence::Job> &job) const IPL_NOEXCEPT;
    };

/*****************************************************************************/

    class Core::Job::EventShutdown: public Event {

    public:
        virtual ipl::string toString() const IPL_NOEXCEPT;
        virtual bool abort() IPL_NOEXCEPT;
        virtual void process(const util::SharedPtr<persistence::Job> &job) const IPL_NOEXCEPT;
    };

/*****************************************************************************/

    struct Core::Config {

        // part of the interface, hence without m_
        int32_t jobs_warn_level;
        int32_t jobs_error_level;
        int32_t events_warn_level;
        int32_t events_error_level;
        size_t max_datachunk_size;

        Config(int32_t jobs_warn_level, int32_t jobs_error_level,
               int32_t events_warn_level, int32_t events_error_level,
               size_t max_datachunk_size) IPL_NOEXCEPT:
            jobs_warn_level(jobs_warn_level), jobs_error_level(jobs_error_level),
            events_warn_level(events_warn_level), events_error_level(events_error_level),
            max_datachunk_size(max_datachunk_size) {}
        Config(const util::config::Value &config) IPL_NOEXCEPT:
            jobs_warn_level(DEFAULT_JOBS_WARN_LEVEL),
            jobs_error_level(DEFAULT_JOBS_ERROR_LEVEL),
            events_warn_level(DEFAULT_EVENTS_WARN_LEVEL),
            events_error_level(DEFAULT_EVENTS_ERROR_LEVEL),
            max_datachunk_size((size_t)UNLIMITED_DATACHUNK_SIZE)
        {
            load(config);
        }

        void load(const util::config::Value &config_root) IPL_NOEXCEPT;
    };

/*****************************************************************************/

}  // end of namespace persistence

/*****************************************************************************/

#endif
