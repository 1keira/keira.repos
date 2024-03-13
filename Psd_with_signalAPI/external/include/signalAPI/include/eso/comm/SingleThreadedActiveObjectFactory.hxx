/*
    Copyright e.solutions GmbH
    All rights reserved
    Authors:
        Stefan Bittner
*/

#ifndef COMM_SINGLETHREADED_ACTIVE_OBJ_FACTORY_HXX
#define COMM_SINGLETHREADED_ACTIVE_OBJ_FACTORY_HXX

#include <common/types/map.hxx>
#include <osal/sched.hxx>
#include <util/SharedPtr.hxx>

#include <comm/commtypes.hxx>
#include <comm/Error.hxx>
#include <comm/util.hxx>
#include <comm/ActiveObject.hxx>
#include <comm/ActiveObjectEvent.hxx>
#include <comm/IActiveObjectFactory.hxx>

#include <comm/comm_dso.h>

namespace comm {
    /**
        \brief  This factory for Active Objects always returns the same single ActiveObject instance to all
                its users.
     **/
    template <typename T = comm::ActiveObject, typename P = void>
    // can't export this class as it is completely inline. VC++ chokes on it.
    class /*COMM_EXPORT*/ SingleThreadedActiveObjectFactory : public IActiveObjectFactory {
        private:
            ActiveObjectPtr m_ao;
        public:
            /** \brief Default constructor. */
            SingleThreadedActiveObjectFactory();

            /** \brief Constructor with thread name. */
            explicit SingleThreadedActiveObjectFactory(const char* name);

            /** \brief Constructor with priority.
             * \note
             * Deprecated. There is no way to set the scheduling policy, use
             * SingleThreadedActiveObjectFactory(const osal::sched::Attr& )
             * instead.
             */
            explicit SingleThreadedActiveObjectFactory(uint_fast16_t priority);

            /** \brief Constructor with thread name and priority.
             * \note
             * Deprecated. There is no way to set the scheduling policy, use
             * SingleThreadedActiveObjectFactory(const char*, const osal::sched::Attr& )
             * instead.
             */
            SingleThreadedActiveObjectFactory(const char* name, uint_fast16_t priority);

            /** \brief Consructor with thread name and scheduling attributes.
             */
            SingleThreadedActiveObjectFactory(const char* name, const osal::sched::Attr& sched_attr);

            /** \briefConstructor with an argument for the to be created ActiveObject.
             */
            explicit SingleThreadedActiveObjectFactory(P* p);

            ~SingleThreadedActiveObjectFactory() override {}

            ActiveObjectPtr getActiveObject(const InstanceID&) override { return m_ao; }
            ActiveObjectPtr hasActiveObject(const InstanceID&) override { return m_ao; }
            ActiveObjectPtr getActiveObject(const ServiceRegistration&) override { return m_ao; }
            // convenience: since there is only one
            void enque (const ActiveObjectEventPtr& event) { m_ao->enque(event); }

            void enque(const ActiveObjectEventPtr& event, bool oob) { m_ao->enque(event,oob); }
            osal::Thread::ThreadId getThreadId() const { return m_ao->getThreadId(); }

        private:
            // not copy-assignable
            SingleThreadedActiveObjectFactory(const SingleThreadedActiveObjectFactory&);
            SingleThreadedActiveObjectFactory& operator=(const SingleThreadedActiveObjectFactory&);

            void stop() override {
                m_ao->stop();
            }

            /** check construction with priority and fallback if it failed */
            void check_fallback(const char* name, const osal::sched::Attr& sched_attr);
    };

    // syntactic sugar to avoid having to write SingleThreadedActiveObjectFactory<...> for the default case
    typedef SingleThreadedActiveObjectFactory<> DefaultSingleThreadedActiveObjectFactory;


    // implementations
    template <typename T, typename P>
    SingleThreadedActiveObjectFactory<T, P>::SingleThreadedActiveObjectFactory() {
        m_ao = new (ipl::nothrow) T();
        if (!m_ao.valid()) { // BRANCH_COVERAGE_UNTESTABLE
            error::fatal("comm::SingleThreadedActiveObjectFactory: can't create ActiveObject", COMM_HERE);
        }
    }

    template <typename T, typename P>
    SingleThreadedActiveObjectFactory<T, P>::SingleThreadedActiveObjectFactory(const char* name) {
        m_ao = new (ipl::nothrow) T(name);
        if (!m_ao.valid()) { // BRANCH_COVERAGE_UNTESTABLE
            error::fatal("comm::SingleThreadedActiveObjectFactory: can't create ActiveObject", COMM_HERE);
        }
    }

    template <typename T, typename P>
    SingleThreadedActiveObjectFactory<T, P>::SingleThreadedActiveObjectFactory(P* p) {
        m_ao = new (ipl::nothrow) T(p);
        if (!m_ao.valid()) { // BRANCH_COVERAGE_UNTESTABLE
            error::fatal("comm::SingleThreadedActiveObjectFactory: can't create ActiveObject"
                    ,COMM_HERE);
        }
    }

    template <typename T, typename P>
    SingleThreadedActiveObjectFactory<T, P>::SingleThreadedActiveObjectFactory(uint_fast16_t priority) {
        osal::sched::Attr sched_attr;
        if ( osal::Thread::getCallerSchedAttrs(sched_attr) ) {
            ipl_error.ack();
            m_ao = new (ipl::nothrow) T();
        } else {
            // interpret priority based on policy
            sched_attr = osal::sched::Attr(sched_attr.policy, priority);
            m_ao = new (ipl::nothrow) T(sched_attr);
            check_fallback(0, sched_attr);
        }
    }

    template <typename T, typename P>
    SingleThreadedActiveObjectFactory<T, P>::SingleThreadedActiveObjectFactory(const char* name,
                                                                                uint_fast16_t priority) {
        osal::sched::Attr sched_attr;
        if ( osal::Thread::getCallerSchedAttrs(sched_attr) ) {
            ipl_error.ack();
            m_ao = new (ipl::nothrow) T(name);
        } else {
            // interpret priority based on policy
            sched_attr = osal::sched::Attr(sched_attr.policy, priority);
            m_ao = new (ipl::nothrow) T(name, sched_attr);
            check_fallback(name, sched_attr);
        }
    }

    template <typename T, typename P>
    SingleThreadedActiveObjectFactory<T, P>::SingleThreadedActiveObjectFactory(const char* name
                                                                ,const osal::sched::Attr& sched_attr) {
        m_ao = new (ipl::nothrow) T(name, sched_attr);
        check_fallback(name, sched_attr);
    }

    template <typename T, typename P>
    void SingleThreadedActiveObjectFactory<T, P>::check_fallback(const char* name
                                                                ,const osal::sched::Attr& sched_attr) {
        bool first=true;
        while(true) {
            if (!m_ao.valid()) { // BRANCH_COVERAGE_UNTESTABLE
                // new failed, abort
                error::fatal("comm::SingleThreadedActiveObjectFactory: can't create ActiveObject"
                            ,COMM_HERE);
                break;
            }
            if ( m_ao->hasError() ) {
                if ( first ) {
                    comm::error::priority_warn2("comm::SingleThreadedActiveObjectFactory: couldn't "
                            "create ActiveObject with these sched attrs, falling back to unprioritized "
                            ,sched_attr);
                    ipl_error.ack();
                    // fall back to AO without priority
                    if ( !name ) {
                        m_ao = new (ipl::nothrow) T();
                    } else {
                        m_ao = new (ipl::nothrow) T(name);
                    }
                    first = false;
                    // recheck errors
                    continue;
                }
                m_ao = ActiveObjectPtr();
                comm::error::priority_error("comm::SingleThreadedActiveObjectFactory: couldn't create "
                        "fallback unprioritized ActiveObject");
                break;
            } else {
                // all good
                break;
            }
        }
    }

} // namespace comm

#endif // COMM_SINGLETHREADED_ACTIVE_OBJ_FACTORY_HXX

