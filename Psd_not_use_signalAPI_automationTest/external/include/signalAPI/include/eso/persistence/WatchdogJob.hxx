/*****************************************************************************/
/*
    Copyright esolutions GmbH
    All rights reserved
    Authors:
        Stefan Meinlschmidt
        Martin Stein
*/
/*****************************************************************************/
#ifndef WATCHDOG_JOB_HXX
#define WATCHDOG_JOB_HXX
/*****************************************************************************/

#include <ipl_config.h>

#include <persistence/Job.hxx>

/*****************************************************************************/

namespace persistence {
    class Core;
}

/*****************************************************************************/

namespace persistence {

/*****************************************************************************/

    /*!
        \brief Feed the (<b>one!</b>) watchdog

        The watchdog asks by running a EventWatchdogAliveRequest through the
        event queue.
        The job only answeres when all stuff running in the background
        has either reported idle or has reported working since the watchdog
        asked last by throwing an EventWorking or EventWorking, respectively.
    */
    class WatchdogJob: public Job {

    public:

        class Client;

        class EventWatchdogAliveRequest;
        class EventWorking;
        class EventIdle;

        WatchdogJob(Core &core, Client &client) IPL_NOEXCEPT:
            Job(core, "WatchdogJob"), m_client(client) {}

        static JobType TYPE;

        virtual void *cast(const JobType& type) IPL_NOEXCEPT;
        virtual bool abort() IPL_NOEXCEPT;
        virtual void start() IPL_NOEXCEPT;

        //! \brief Some watchdog requests a reaction
        virtual void watchdogAliveRequest() IPL_NOEXCEPT;
        //! \brief Some thing is to be considered "working and alive" by the watchdog
        virtual void working(void *who) IPL_NOEXCEPT;
        //! \brief Some thing is not to be considered by the watchdog anymore
        virtual void idle(void *who) IPL_NOEXCEPT;

    protected:
        Client &m_client;
        typedef ipl::map<void *, bool> Alive;
        Alive m_alive;
    };

/*****************************************************************************/

    /*!
        \brief Interface for callbacks from the WatchdogJob
    */
    class WatchdogJob::Client {

    public:
        //! \brief Just to make the compiler happy...
        virtual ~Client() IPL_NOEXCEPT;
        
        //! \brief The system thinks it is alive
        virtual void watchdogAlive() IPL_NOEXCEPT = 0;
    };

/*****************************************************************************/

    class WatchdogJob::EventWatchdogAliveRequest: public Event {

    public:
        virtual ipl::string toString() const IPL_NOEXCEPT;
        virtual bool abort() IPL_NOEXCEPT;
        virtual void process(const util::SharedPtr<persistence::Job> &job) const IPL_NOEXCEPT;
    };

/*****************************************************************************/

    class WatchdogJob::EventWorking: public Event {

    public:
        EventWorking(void *who) IPL_NOEXCEPT: m_who(who) {}

        virtual ipl::string toString() const IPL_NOEXCEPT;
        virtual bool abort() IPL_NOEXCEPT;
        virtual void process(const util::SharedPtr<persistence::Job> &job) const IPL_NOEXCEPT;

    protected:
        void *m_who;
    };

/*****************************************************************************/

    class WatchdogJob::EventIdle: public Event {

    public:
        EventIdle(void *who) IPL_NOEXCEPT: m_who(who) {}

        virtual ipl::string toString() const IPL_NOEXCEPT;
        virtual bool abort() IPL_NOEXCEPT;
        virtual void process(const util::SharedPtr<persistence::Job> &job) const IPL_NOEXCEPT;

    protected:
        void *m_who;
    };

/*****************************************************************************/

}  // end of namespace persistence

/*****************************************************************************/
#endif
