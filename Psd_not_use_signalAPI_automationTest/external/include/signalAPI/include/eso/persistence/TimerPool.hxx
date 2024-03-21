/*****************************************************************************/
/*
    Copyright esolutions GmbH
    All rights reserved
    Authors:
        Stefan Meinlschmidt
        Martin Stein
*/
/*****************************************************************************/
#ifndef PERSISTENCE_TIMERPOOL_HXX_
#define PERSISTENCE_TIMERPOOL_HXX_
/*****************************************************************************/

#include <ipl_config.h>

#include <osal/Mutex.hxx>
#include <osal/Timer.hxx>
#include <persistence/Core.hxx>

/*****************************************************************************/

namespace persistence {

/*****************************************************************************/

    class TimerPool {
    public:

        class Job;
        class Event;

        typedef size_t Handle;

        TimerPool(Core &core, int max_size) IPL_NOEXCEPT;
        ~TimerPool() IPL_NOEXCEPT;

        bool isValid() IPL_NOEXCEPT { return m_valid; }

        void remove(Handle timer) IPL_NOEXCEPT;
        void removeAll() IPL_NOEXCEPT;

        /*!
            \return    true on success, false on error
            \errorindicator
                return code
            \errors
                none
        */
        Handle start(osal::TimeT interval_ms) IPL_NOEXCEPT;

        void stop(Handle timer) IPL_NOEXCEPT;
        void stopAll() IPL_NOEXCEPT;

        // the osal timer callback
        static void timerCallback(osal::Timer* const which) IPL_NOEXCEPT;

        static const Handle INVALID_TIMER_ID = (Handle)-1;

    private:

        struct Info;

        Handle add();
        Handle findNextFree();

        Core       &m_core;
        typedef ipl::vector<Info> Timers;
        Timers      m_timers;
        Handle      m_next_free;
        size_t         m_max_size;
        osal::Mutex m_mutex;
        bool        m_valid;
    };

/*****************************************************************************/

    /*!
        \brief Mixin for a Job that has a timer
    */
    class TimerPool::Job {
    public:
        static JobType TYPE;

        Job(TimerPool &timerpool, osal::TimeT timeout_ms) IPL_NOEXCEPT;
        virtual ~Job() IPL_NOEXCEPT;

        void *cast(const JobType &type) IPL_NOEXCEPT { return type==TYPE? this : NULL; }

        virtual void timerRings(Handle handle) IPL_NOEXCEPT;

    protected:

        //! \brief Our timer has rung
        virtual void timeout()=0;

        /*!
            \brief Schedule timeout() to be called in m_timeout_ms
            \return    false on success, true on error
        */
        bool startTimer();
        void stopTimer();

        TimerPool        &m_timerpool;
        Handle            m_timer_handle;
        const osal::TimeT m_timeout_ms;
    };

/*****************************************************************************/

    class TimerPool::Event: public persistence::Event {

    public:
        Event(Handle handle) IPL_NOEXCEPT: m_handle(handle) {}

        virtual ipl::string toString() const IPL_NOEXCEPT;
        virtual bool abort() IPL_NOEXCEPT;
        virtual void process(const util::SharedPtr<persistence::Job> &job) const IPL_NOEXCEPT;

    private:
        Handle m_handle;
    };

/*****************************************************************************/

}  // end of namespace persistence

/*****************************************************************************/
#endif
