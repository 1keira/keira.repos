/*****************************************************************************/
/*
    Copyright esolutions GmbH
    All rights reserved
    Authors:
        Stefan Meinlschmidt
        Martin Stein
*/
/*****************************************************************************/
#ifndef PERSISTENCE_EVENTQUEUE_HXX_
#define PERSISTENCE_EVENTQUEUE_HXX_
/*****************************************************************************/

#include <ipl_config.h>

#include <common/types/list.hxx>
#include <osal/Condition.hxx>
#include <osal/Mutex.hxx>
#include <util/SharedPtr.hxx>
#include <persistence/Event.hxx>

/*****************************************************************************/

namespace persistence {

/*****************************************************************************/

    class EventQueue  {

    public:
        EventQueue(int32_t warn_level, int32_t error_level) IPL_NOEXCEPT;
        ~EventQueue() IPL_NOEXCEPT;

        /**
            \brief Push a event into the input queue.
            \param[in] ev
                The event
            \return true on success, false on error
            \errorindicator
                    return code
            \errors    none
        **/
        bool push(const util::SharedPtr<Event> &ev) IPL_NOEXCEPT;

        /**
            \brief Get an event or NULL from the input queue.

            If the queue is empty, the method will block until a event is
                put into the queue by another thread
                or the queue is forcefully woken up.
                In this case it will return NULL.
            \return
                the event from the queue or NULL in case of wakeup
        **/
        util::SharedPtr<Event> pop() IPL_NOEXCEPT;

        //! \brief Wake a waiting pop() and make it return NULL
        void wakeup() IPL_NOEXCEPT;

        /**
            \brief Get the current size of the queue.
            \return The size of the queue.
        **/
        size_t size() IPL_NOEXCEPT { return m_queue.size(); }

        //! \brief Abort all events, empty queue
        void reset() IPL_NOEXCEPT;

        //! \brief Dump status information to the tracechannel FW_PERSISTENCE_STATUS
        void traceStatus() IPL_NOEXCEPT;

    private:

        bool isWarned() { return m_warned; }

        // TODO: make queue unsynchronized, move mutex into Core
        osal::Mutex m_mutex;
        osal::Condition m_cond;
        bool m_wakeup;
        
        const int32_t SIZE_WARN;
        const int32_t SIZE_ERR;
        bool m_warned;
        typedef ipl::list<util::SharedPtr<Event> > Queue;
        Queue m_queue;

        uint32_t m_num_evts;
        uint16_t m_max_size;

        EventQueue(const EventQueue&);
        EventQueue& operator=(const EventQueue&);

    };

/*****************************************************************************/

}  // end of namespace persistence

/*****************************************************************************/
#endif
