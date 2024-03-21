/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleInterfaceS_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICVOICEMEASUREMENTSS_CSTYLE_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICVOICEMEASUREMENTSS_CSTYLE_HXX

#include <common/Macros.hxx>

#include <comm/commtypes.hxx>
#include <comm/commidltypes.hxx>
#include <comm/CallEvent.hxx>
#include <asi/connectivity/diagnostic/cstyle/DiagnosticVoiceMeasurementsServiceRegistration.hxx>
#include <asi/connectivity/diagnostic/cstyle/StructEcallOperationStatus.hxx>
#include <asi/connectivity/diagnostic/cstyle/Definitions.hxx>
#include <asi/connectivity/diagnostic/cstyle/DiagnosticVoiceMeasurementsProxyReply.hxx>
#include <asi/connectivity/diagnostic/cstyle/DiagnosticVoiceMeasurementsReplyS.hxx>

namespace asi
{
namespace connectivity
{
namespace diagnostic
{
namespace cstyle
{

    /**
    \brief  The diagnostic::cstyle::DiagnosticVoiceMeasurements interface on tthe service side.
    \details
            A service instance needs to implement this interface.
    **/
    class DiagnosticVoiceMeasurementsS
    {
    public:
        DiagnosticVoiceMeasurementsS () {}
    // List of request methods
        /**
            getAerialSwitchStatus Method ID: 0
        **/
        virtual void getAerialSwitchStatus(
            
            DiagnosticVoiceMeasurementsProxyReply& reply
        ) = 0;
        /**
            getECallActivationState Method ID: 2
        **/
        virtual void getECallActivationState(
            
            DiagnosticVoiceMeasurementsProxyReply& reply
        ) = 0;
        /**
            getECallCallState Method ID: 4
        **/
        virtual void getECallCallState(
            
            DiagnosticVoiceMeasurementsProxyReply& reply
        ) = 0;
        /**
            getEcallOperationStatus Method ID: 14
        **/
        virtual void getEcallOperationStatus(
            
            DiagnosticVoiceMeasurementsProxyReply& reply
        ) = 0;
        /**
            getRecentCallList Method ID: 16
        **/
        virtual void getRecentCallList(
            
            DiagnosticVoiceMeasurementsProxyReply& reply
        ) = 0;
        /**
            getECallSetOfData Method ID: 12
        **/
        virtual void getECallSetOfData(
            
            DiagnosticVoiceMeasurementsProxyReply& reply
        ) = 0;
        /**
            getECallEraProfileActivationStatus Method ID: 8
        **/
        virtual void getECallEraProfileActivationStatus(
            
            DiagnosticVoiceMeasurementsProxyReply& reply
        ) = 0;
        /**
            getECallEraProfileAvailabilityStatus Method ID: 10
        **/
        virtual void getECallEraProfileAvailabilityStatus(
            
            DiagnosticVoiceMeasurementsProxyReply& reply
        ) = 0;
        /**
            getECallEraIccid Method ID: 6
        **/
        virtual void getECallEraIccid(
            
            DiagnosticVoiceMeasurementsProxyReply& reply
        ) = 0;

        /*!
        \brief Informs the service about a connected client
        \param count The number of connected clients
        \param reply A proxy that can be used to reply to the connected client. If the client did
        not register its reply interface, calling valid() or isAlive() on reply will return false.
        In this case calling any other methods of the proxy will yield in undefined behaviour.
        */
        virtual void clientConnected(uint32_t count
            ,DiagnosticVoiceMeasurementsProxyReply& reply
        ) {}

        /*!
        \brief Informs the service that a client disconnected
        \param count the number of connected clients
        \param reply The proxy to the disconnected client. It is not alive any more, but can be used for comparison
        if it ever was valid.
        */
        virtual void clientDisconnected(uint32_t count
            ,DiagnosticVoiceMeasurementsProxyReply& reply
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
                DiagnosticVoiceMeasurementsServiceRegistration(comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICVOICEMEASUREMENTS_REQUEST), instance_no), static_cast<DiagnosticVoiceMeasurementsS*>(this), l, factory );
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
                DiagnosticVoiceMeasurementsServiceRegistration(comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICVOICEMEASUREMENTS_REQUEST), instance_no), static_cast<DiagnosticVoiceMeasurementsS*>(this), l );
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
            m_registration = DiagnosticVoiceMeasurementsServiceRegistration();
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
        bool unregisterSelf(comm::ServiceReleasedFct callback, void* ctx)
        {
            if ( m_registration.unregisterAndNotify(callback, ctx) ) {
                return true;
            }
            // let go of the reference
            m_registration = DiagnosticVoiceMeasurementsServiceRegistration();
            return false;
        }

        virtual ~DiagnosticVoiceMeasurementsS()
        {
            // unregister in case it wasn't done by the caller.
            unregisterSelf();
        }

        // call ids
        void
        getAerialSwitchStatus_CallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<DiagnosticVoiceMeasurementsS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 0;
            ce.assign(inst, mid);
        }
        void
        getECallActivationState_CallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<DiagnosticVoiceMeasurementsS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 2;
            ce.assign(inst, mid);
        }
        void
        getECallCallState_CallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<DiagnosticVoiceMeasurementsS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 4;
            ce.assign(inst, mid);
        }
        void
        getEcallOperationStatus_CallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<DiagnosticVoiceMeasurementsS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 14;
            ce.assign(inst, mid);
        }
        void
        getRecentCallList_CallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<DiagnosticVoiceMeasurementsS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 16;
            ce.assign(inst, mid);
        }
        void
        getECallSetOfData_CallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<DiagnosticVoiceMeasurementsS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 12;
            ce.assign(inst, mid);
        }
        void
        getECallEraProfileActivationStatus_CallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<DiagnosticVoiceMeasurementsS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 8;
            ce.assign(inst, mid);
        }
        void
        getECallEraProfileAvailabilityStatus_CallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<DiagnosticVoiceMeasurementsS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 10;
            ce.assign(inst, mid);
        }
        void
        getECallEraIccid_CallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<DiagnosticVoiceMeasurementsS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 6;
            ce.assign(inst, mid);
        }

    protected:
        DiagnosticVoiceMeasurementsServiceRegistration m_registration;
    };

} // namespace cstyle
} //namespace asi
} //namespace connectivity
} //namespace diagnostic
#endif// ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICVOICEMEASUREMENTSS_CSTYLE_HXX
