/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceS_hxx.tmpl
*/
#ifndef ASI_DIAG_DTC_DTCS_HXX
#define ASI_DIAG_DTC_DTCS_HXX

#include <common/Macros.hxx>

#include <comm/commtypes.hxx>
#include <comm/commidltypes.hxx>
#include <comm/CallEvent.hxx>
#include <asi/diag/dtc/DtcServiceRegistration.hxx>

#include <asi/diag/dtc/Definitions.hxx>

#include <asi/diag/dtc/DtcProxyReply.hxx>
#include <asi/diag/dtc/DtcReplyS.hxx>

namespace asi
{
namespace diag
{
namespace dtc
{

    /**
    \brief  The dtc::Dtc interface on tthe service side.
    \details
            A service instance needs to implement this interface.
        * Diagnosis service interface to test and report DTCs based on 3 Byte Diagnostic Fault Check Codes (DFCC).
     *
     * Every diagnosis node on system and android partition registers its own service instance of this interface.   
     * Every instance ID handles exactly the DTCs which are defined for that node.
     * The instance IDs of all nodes are defined in diag_common.idl.
    **/
    class DtcS
    {
    public:
        DtcS () {}
    // List of request methods
        /**
            
         * report a single test result. service side handled the debouncing.
         * should only report a changed test result ((pre)failed -> (pre)passed and vice versa) except after the following events
         * - asi reconnect (due to disconnect from service and/or client side)
         * debouncing is then restarted on service side
         *
         * @param dfcc       The tested dtc
         * @param result     Test result of the test.
         
            reportTestResult Method ID: 2
        **/
        virtual void reportTestResult(
            const uint32_t dfcc,
            const asi::diag::dtc::eDtcTestResult result
            ,DtcProxyReply& reply
        ) = 0;
        /**
            
         * signalize if enableConditions are fulfilled (see "Randbedingungen" in dtc specification).
         * Must be sent in case of any status change. enableConditions == false until true value is initially sent by client.
         * TestResults from client are ignored if enabledConditions == false. Must be set to true prior to reportTestResult.
         * 
         * @param dfcc Diagnostic Fault Check Code that this application handles
         * @param fulfilled if enableConditions are fulfilled. If true, a dtc detection is possible on client side.   
         
            enableConditionsFulfilled Method ID: 0
        **/
        virtual void enableConditionsFulfilled(
            const uint32_t dfcc,
            const bool fulfilled
            ,DtcProxyReply& reply
        ) = 0;

        /*!
        \brief Informs the service about a connected client
        \param count The number of connected clients
        \param reply A proxy that can be used to reply to the connected client. If the client did
        not register its reply interface, calling valid() or isAlive() on reply will return false.
        In this case calling any other methods of the proxy will yield in undefined behaviour.
        */
        virtual void clientConnected(uint32_t count
            ,DtcProxyReply& reply
        ) {}

        /*!
        \brief Informs the service that a client disconnected
        \param count the number of connected clients
        \param reply The proxy to the disconnected client. It is not alive any more, but can be used for comparison
        if it ever was valid.
        */
        virtual void clientDisconnected(uint32_t count
            ,DtcProxyReply& reply
        ) {}

        /*!
        \brief  Registers this service instance.
        \param  instance_no is the instance number for the service.
        \param  p a user provided ActiveObject factory. This gives control over the threads that call the service.
        \return false on success, true on error
        \errorindicator
                return code
        \errors
                any possible error generated from COMM
        */
        bool registerSelf(uint32_t instance_no, const comm::ActiveObjectFactoryPtr& factory, comm::LifecycleListener* l=nullptr)
        {
            if (m_registration.isAlive()) {
                ipl_raise(comm::Error, comm::error::SELF_ALREADY_REGISTERED
                            ,((ipl::string)m_registration.getInstanceID()).c_str());
                return true;
            }

            m_registration =
                DtcServiceRegistration(comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_DIAG_DTC_DTC_REQUEST), instance_no), static_cast<DtcS*>(this), l, factory );
            if (!m_registration.valid()) {
                comm::error::fatal( "can't create ServiceRegistration, OOM ", COMM_HERE);
                return true;
            }
            return m_registration.registerService();
        }

        /*!
        \brief  Registers this service instance.
        \param  instance_no is the instance number for the service interface.
        \param  l is the lifecycle listern instance
        \return false on success, true on error
        \errorindicator
                return code
        \errors
                any possible error generated from COMM
        */
        bool registerSelf(uint32_t instance_no, comm::LifecycleListener* l=nullptr)
        {
            if (m_registration.isAlive()) {
                ipl_raise(comm::Error, comm::error::SELF_ALREADY_REGISTERED
                            ,((ipl::string)m_registration.getInstanceID()).c_str());
                return true;
            }

            m_registration =
                DtcServiceRegistration(comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_DIAG_DTC_DTC_REQUEST), instance_no), static_cast<DtcS*>(this), l );
            if (!m_registration.valid()) {
                comm::error::fatal( "can't create ServiceRegistration, OOM ", COMM_HERE);
                return true;
            }
            return m_registration.registerService();
        }

        /*!
        \brief  Registers this service instance.
        \param  instance_no is the instance number for the service interface
        \param  l is the lifecycle listern instance
        \return false on success, true on error
        \errorindicator
                return code
        \errors
                any possible error generated from COMM
        */
        bool registerSelf(uint32_t instance_no, comm::LifecycleListener& l)
        {
            return registerSelf (instance_no, &l);
        }

        /*!
        \brief  Unregisters this service instance.
        \return false on success, true on error
        \errorindicator
                return code
        \errors
                none
        */
        bool unregisterSelf()
        {
            if (!m_registration.isAlive()) {
                // not registered -> nothing to do.
                return false;
            }
            m_registration.unregisterService();
            // must not be alive after unregistration
            IPL_ASSERT(!m_registration.isAlive());
            // let go of the reference
            m_registration = DtcServiceRegistration();
            return false;
        }

        /*!
        \brief  Unregisters this service instance and calls a callback.
        \return false if the service is being unregistered, true on error
                The callback is called only if false is returned.
                Errors are:
                <ul>
                <li>the service registration is not valid
                <li>an unregisterSelf() or ServiceRegistration::unregisterService() or
                    or ServiceRegistration::unregisterAndNotify had already been called.
                <li>the callback is NULL.
                </ul>
        \errorindicator
                return code
        \errors
                \see comm::ServiceRegistration::unregisterAndNotify
        */
        bool unregisterSelf(comm::ServiceReleasedFct callback, void* ctx) // NOSONAR - must not be changed because of API compatibility
        {
            // to not race with the callback. we can't touch m_registration after
            // calling unregisterAndNotify
            // make a temporary copy
            DtcServiceRegistration tmp{m_registration};
            // let go of the reference the member holds
            m_registration = DtcServiceRegistration();
            // call unregisterAndNotify
            return tmp.unregisterAndNotify(callback, ctx);
        }

        virtual ~DtcS()
        {
            // unregister in case it wasn't done by the caller.
            unregisterSelf();
        }

        // call ids
        void
        reportTestResultCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<DtcS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 2;
            ce.assign(inst, mid);
        }
        void
        enableConditionsFulfilledCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<DtcS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 0;
            ce.assign(inst, mid);
        }

    protected:
        DtcServiceRegistration m_registration;
    };

} //namespace asi
} //namespace diag
} //namespace dtc
#endif// ASI_DIAG_DTC_DTCS_HXX
