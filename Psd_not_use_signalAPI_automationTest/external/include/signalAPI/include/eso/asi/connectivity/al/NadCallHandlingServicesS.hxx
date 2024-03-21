/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceS_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_NADCALLHANDLINGSERVICESS_HXX
#define ASI_CONNECTIVITY_AL_NADCALLHANDLINGSERVICESS_HXX

#include <common/Macros.hxx>

#include <comm/commtypes.hxx>
#include <comm/commidltypes.hxx>
#include <comm/CallEvent.hxx>
#include <asi/connectivity/al/NadCallHandlingServicesServiceRegistration.hxx>
#include <asi/connectivity/al/StructCallStatus.hxx>

#include <asi/connectivity/al/Definitions.hxx>

#include <asi/connectivity/al/NadCallHandlingServicesProxyReply.hxx>
#include <asi/connectivity/al/NadCallHandlingServicesReplyS.hxx>

namespace asi
{
namespace connectivity
{
namespace al
{

    /**
    \brief  The al::NadCallHandlingServices interface on tthe service side.
    \details
            A service instance needs to implement this interface.
    **/
    class NadCallHandlingServicesS
    {
    public:
        NadCallHandlingServicesS () {}
    // List of request methods
        /**
            acceptCall Method ID: 0
        **/
        virtual void acceptCall(
            
            NadCallHandlingServicesProxyReply& reply
        ) = 0;
        /**
            dialNumber Method ID: 2
        **/
        virtual void dialNumber(
            const CIPtr< CIString >& number
            ,NadCallHandlingServicesProxyReply& reply
        ) = 0;
        /**
            hangupCall Method ID: 4
        **/
        virtual void hangupCall(
            const int32_t callID
            ,NadCallHandlingServicesProxyReply& reply
        ) = 0;
        /**
            sendDtmf Method ID: 6
        **/
        virtual void sendDtmf(
            const int32_t value
            ,NadCallHandlingServicesProxyReply& reply
        ) = 0;

        /*!
        \brief Informs the service about a connected client
        \param count The number of connected clients
        \param reply A proxy that can be used to reply to the connected client. If the client did
        not register its reply interface, calling valid() or isAlive() on reply will return false.
        In this case calling any other methods of the proxy will yield in undefined behaviour.
        */
        virtual void clientConnected(uint32_t count
            ,NadCallHandlingServicesProxyReply& reply
        ) {}

        /*!
        \brief Informs the service that a client disconnected
        \param count the number of connected clients
        \param reply The proxy to the disconnected client. It is not alive any more, but can be used for comparison
        if it ever was valid.
        */
        virtual void clientDisconnected(uint32_t count
            ,NadCallHandlingServicesProxyReply& reply
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
                NadCallHandlingServicesServiceRegistration(comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_AL_NADCALLHANDLINGSERVICES_REQUEST), instance_no), static_cast<NadCallHandlingServicesS*>(this), l, factory );
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
                NadCallHandlingServicesServiceRegistration(comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_AL_NADCALLHANDLINGSERVICES_REQUEST), instance_no), static_cast<NadCallHandlingServicesS*>(this), l );
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
            m_registration = NadCallHandlingServicesServiceRegistration();
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
            NadCallHandlingServicesServiceRegistration tmp{m_registration};
            // let go of the reference the member holds
            m_registration = NadCallHandlingServicesServiceRegistration();
            // call unregisterAndNotify
            return tmp.unregisterAndNotify(callback, ctx);
        }

        virtual ~NadCallHandlingServicesS()
        {
            // unregister in case it wasn't done by the caller.
            unregisterSelf();
        }

        // call ids
        void
        acceptCallCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NadCallHandlingServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 0;
            ce.assign(inst, mid);
        }
        void
        dialNumberCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NadCallHandlingServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 2;
            ce.assign(inst, mid);
        }
        void
        hangupCallCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NadCallHandlingServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 4;
            ce.assign(inst, mid);
        }
        void
        sendDtmfCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NadCallHandlingServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 6;
            ce.assign(inst, mid);
        }

    protected:
        NadCallHandlingServicesServiceRegistration m_registration;
    };

} //namespace asi
} //namespace connectivity
} //namespace al
#endif// ASI_CONNECTIVITY_AL_NADCALLHANDLINGSERVICESS_HXX
