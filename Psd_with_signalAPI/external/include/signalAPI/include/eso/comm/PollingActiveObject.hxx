/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/


#ifndef COMM_POLLING_ACTIVE_OBJECT_HXX
#define COMM_POLLING_ACTIVE_OBJECT_HXX

#include <ipl_config.h>

#include <common/types/deque.hxx>
#include <osal/Mutex.hxx>
#include <osal/Condition.hxx>
#include <comm/commtypes.hxx>
#include <comm/ActiveObject.hxx>
#include <comm/ActiveObjectEvent.hxx>
#include <comm/comm_dso.h>

namespace comm {

    class COMM_EXPORT PollingActiveObject : public comm::ActiveObject {
        public:
            explicit PollingActiveObject( uint_fast16_t p_priority ) IPL_NOEXCEPT
            : ActiveObject(p_priority)
            {}
            explicit PollingActiveObject( const char* name ) IPL_NOEXCEPT
            : ActiveObject(name)
            {}
            PollingActiveObject( const char* name, uint_fast16_t p_priority) IPL_NOEXCEPT
            : ActiveObject(name, p_priority)
            {}
            ~PollingActiveObject() IPL_NOEXCEPT override {}

            //! check is an event in within the queue
            bool hasEvent() const IPL_NOEXCEPT;

            /*!
             * fetch the first event from the queue, remove it from the
             * queue and then process it.
             *
             * In case of the queue is empty nothing is done (wait_until=false)
             * or the call blocks until an event is available (wait_until=true)
             *
             * \param wait_until
             * defines whether the call shall wait on an event if the queue is
             * empty
             *
             * \return
             * false in case of nothing done
             * true in case of an event was processed
            */
            bool processEvent(bool wait_until) IPL_NOEXCEPT;

        protected:
            /*! overwrite the dispatch event in order to
             * - collect and store method calls
             * - perform all other internal events
           */
            bool dispatchEvent ( const comm::ActiveObjectEventPtr& event ) override;


        private:
            PollingActiveObject();
            ipl::deque<comm::ActiveObjectEventPtr>  m_calls;
            osal::Mutex                             m_mtx;
            osal::Condition                         m_cond;
    };

} // namespace comm

#endif // COMM_POLLING_ACTIVE_OBJECT_HXX

