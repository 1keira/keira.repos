/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/


#ifndef COMM_ACTIVEOBJECT_HXX
#define COMM_ACTIVEOBJECT_HXX

#include <ipl_config.h>

#include <iplbase/exceptions.hxx>
#include <common/types/list.hxx>
#include <common/types/map.hxx>
#include <osal/sched.hxx>
#include <util/SharedPtr.hxx>
#include <util/Thread.hxx>
#include <osal/Mutex.hxx>
#include <osal/Condition.hxx>
#include <osal/AtomicCounter.hxx>

#include <comm/comm_dso.h>
#include <comm/ActiveObjectEvent.hxx>

/** \brief The comm namespace contains the comminication layer, including marshalling/unmarshalling,
            dervice discovery and lifecycle tracking
*/
namespace comm {
    /** \brief the comm core and model implementation
        \internal
    */
    class Core;
    class ServiceInfo;

    /**
      \brief A thread with a queue.

      ActiveObjects provide the threads that execute method calls.

    */
    class COMM_EXPORT ActiveObject : public util::IRunnable {
        public:
            /**
            \brief Default constructor. The thread associated with this ActveObject will run with
            the default priority.
            */
            ActiveObject() IPL_NOEXCEPT;

            /**
            \brief Constructor with a priority.
            \note
                \a Deprecated. Don't use this constructor. There is no way to specify the
                scheduling policy to be used.
            */
            explicit ActiveObject( uint_fast16_t p_priority ) IPL_NOEXCEPT;

            /**
            \brief Constructor with scheduling attributes.
            */
            explicit ActiveObject( const osal::sched::Attr& attr ) IPL_NOEXCEPT;

            /**
            \brief Constructor with a thread name.
            */
            explicit ActiveObject( const char* name ) IPL_NOEXCEPT;

            /**
            \brief Constructor with thread name and priority
            \note
                \a Deprecated. Don't use this constructor. There is no way to specify the
                scheduling policy to be used.
            */
            ActiveObject( const char* name, uint_fast16_t prio ) IPL_NOEXCEPT;

            /**
            \brief Constructor with name and scheduling attributes.
            */
            explicit ActiveObject( const char* name, const osal::sched::Attr& attr ) IPL_NOEXCEPT;
            /**
            \brief    thread-execution method. It blocks on the internal osal::Condition, until events
                    are in the queue.
            **/
            void threadLoop(const util::Thread* const) override;

            /**
            \brief Puts an event into the queue and signals the osal::Condition
            The event is added to the end of the queue.
            This call is equivalent to callinge enque(const ActiveObjectEventPtr& msg, bool oob)
            with the second parameter set to false.
            **/
            void enque(const ActiveObjectEventPtr& msg) IPL_NOEXCEPT;


            /**
            \brief    destructor
            **/
            ~ActiveObject() IPL_NOEXCEPT override;


            /**
            \brief    signal the thread loop to terminate
            **/
            void stop(void) IPL_NOEXCEPT;

            /**
            \brief answers if a constructor had an error.
            If this method returns true, the object must not be used. Call it after the constructor and destroy
            the object if it returns true
            */
            bool hasError() IPL_NOEXCEPT;

            /**
            \brief Returns the ThreadID of the ActiveObject's thread.
            **/
            osal::Thread::ThreadId getThreadId() const IPL_NOEXCEPT;

            /**
            \brief Puts an event into the queue and signals the osal::Condition

                Puts an event into the queue and signals the condition. If the parameter oob ist
                    true, the event is handled out-of-band. This puts the event in front of
                    other events in the queue that are not internal.
                    Internal events are used for house keeping.
                \param oob if true the event is handles out-of-band

            **/
            void enque(const ActiveObjectEventPtr& msg, bool oob) IPL_NOEXCEPT;


        protected:
            /**
                \brief Processes one event

                Processes one event. The implementation must reais an error with ipl_error
                        if it returns true.
                \param event the event
                \return true, if an error occured, false otherwise.
            */
            virtual bool dispatchEvent ( const ActiveObjectEventPtr& event ) {
                IPLBASE_ABORT_ON_EXCEPTION(
                return event->process();
                );
                return true;    // never reached, but needed to satisfy no-warning and CLANG-Build
            }
        private:
            void enqueFront(const ActiveObjectEventPtr& msg);

            /**
            \brief    return the status of the active object
            **/
            bool isClosed() const    { return m_closed.getCurrentCount()!=0; }

            /**
            \brief    Marks the object as closed
            **/
            void markClosed()        { m_closed.increment(); }

            /** Flag indicating successful construction */
            bool                m_valid;

            /** The thread object */
            util::Thread        m_threadctrl;

            /**
            \brief mutex for the message input queues
            **/
            osal::Mutex         m_mutex;

            /**
            \brief    osal::Condition to block on, when both queues are empty. The osal::Condition
                    is signaled, when a new message is enqueued.
            **/
            osal::Condition     m_cond;

            /**
            \brief message queue for ActiveObjectEvents
            **/
            typedef ipl::list<ActiveObjectEventPtr> AOEvents;
            AOEvents m_events;

            /**
            \brief    status of the active object (false: thread is active running, true: thread is finalized
            **/
            osal::AtomicCounter            m_closed;

            /**
            \brief   common initialization code for all constructors
            */
            void init();

            friend class Core;
            friend class ServiceInfo;
    };

    typedef util::SharedPtr<ActiveObject> ActiveObjectPtr;

} // namespace comm

#endif // COMM_ACTIVEOBJECT_HXX

