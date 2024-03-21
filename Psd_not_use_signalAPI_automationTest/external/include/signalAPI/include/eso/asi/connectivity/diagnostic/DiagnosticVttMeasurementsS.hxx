/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceS_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICVTTMEASUREMENTSS_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICVTTMEASUREMENTSS_HXX

#include <common/Macros.hxx>

#include <comm/commtypes.hxx>
#include <comm/commidltypes.hxx>
#include <comm/CallEvent.hxx>
#include <asi/connectivity/diagnostic/DiagnosticVttMeasurementsServiceRegistration.hxx>
#include <asi/connectivity/diagnostic/StructVttStatus.hxx>

#include <asi/connectivity/diagnostic/Definitions.hxx>

#include <asi/connectivity/diagnostic/DiagnosticVttMeasurementsProxyReply.hxx>
#include <asi/connectivity/diagnostic/DiagnosticVttMeasurementsReplyS.hxx>

namespace asi
{
namespace connectivity
{
namespace diagnostic
{

    /**
    \brief  The diagnostic::DiagnosticVttMeasurements interface on tthe service side.
    \details
            A service instance needs to implement this interface.
    **/
    class DiagnosticVttMeasurementsS
    {
    public:
        DiagnosticVttMeasurementsS () {}
    // List of request methods
        /**
            getSmsPdus Method ID: 0
        **/
        virtual void getSmsPdus(
            
            DiagnosticVttMeasurementsProxyReply& reply
        ) = 0;
        /**
            getVttStatus Method ID: 2
        **/
        virtual void getVttStatus(
            
            DiagnosticVttMeasurementsProxyReply& reply
        ) = 0;

        /*!
        \brief Informs the service about a connected client
        \param count The number of connected clients
        \param reply A proxy that can be used to reply to the connected client. If the client did
        not register its reply interface, calling valid() or isAlive() on reply will return false.
        In this case calling any other methods of the proxy will yield in undefined behaviour.
        */
        virtual void clientConnected(uint32_t count
            ,DiagnosticVttMeasurementsProxyReply& reply
        ) {}

        /*!
        \brief Informs the service that a client disconnected
        \param count the number of connected clients
        \param reply The proxy to the disconnected client. It is not alive any more, but can be used for comparison
        if it ever was valid.
        */
        virtual void clientDisconnected(uint32_t count
            ,DiagnosticVttMeasurementsProxyReply& reply
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
                DiagnosticVttMeasurementsServiceRegistration(comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICVTTMEASUREMENTS_REQUEST), instance_no), static_cast<DiagnosticVttMeasurementsS*>(this), l, factory );
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
                DiagnosticVttMeasurementsServiceRegistration(comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICVTTMEASUREMENTS_REQUEST), instance_no), static_cast<DiagnosticVttMeasurementsS*>(this), l );
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
            m_registration = DiagnosticVttMeasurementsServiceRegistration();
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
            DiagnosticVttMeasurementsServiceRegistration tmp{m_registration};
            // let go of the reference the member holds
            m_registration = DiagnosticVttMeasurementsServiceRegistration();
            // call unregisterAndNotify
            return tmp.unregisterAndNotify(callback, ctx);
        }

        virtual ~DiagnosticVttMeasurementsS()
        {
            // unregister in case it wasn't done by the caller.
            unregisterSelf();
        }

        // call ids
        void
        getSmsPdus_CallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<DiagnosticVttMeasurementsS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 0;
            ce.assign(inst, mid);
        }
        void
        getVttStatus_CallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<DiagnosticVttMeasurementsS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 2;
            ce.assign(inst, mid);
        }

    protected:
        DiagnosticVttMeasurementsServiceRegistration m_registration;
    };

} //namespace asi
} //namespace connectivity
} //namespace diagnostic
#endif// ASI_CONNECTIVITY_DIAGNOSTIC_DIAGNOSTICVTTMEASUREMENTSS_HXX
