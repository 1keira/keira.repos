/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceS_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_CALLHANDLINGSERVICESS_HXX
#define ASI_CONNECTIVITY_AL_CALLHANDLINGSERVICESS_HXX

#include <common/Macros.hxx>

#include <comm/commtypes.hxx>
#include <comm/commidltypes.hxx>
#include <comm/CallEvent.hxx>
#include <asi/connectivity/al/CallHandlingServicesServiceRegistration.hxx>
#include <asi/connectivity/al/StructCallStatus.hxx>

#include <asi/connectivity/al/Definitions.hxx>

#include <asi/connectivity/al/CallHandlingServicesProxyReply.hxx>
#include <asi/connectivity/al/CallHandlingServicesReplyS.hxx>

namespace asi
{
namespace connectivity
{
namespace al
{

    /**
    \brief  The al::CallHandlingServices interface on tthe service side.
    \details
            A service instance needs to implement this interface.
    **/
    class CallHandlingServicesS
    {
    public:
        CallHandlingServicesS () {}
    // List of request methods
        /**
            sendDtmf Method ID: 18
        **/
        virtual void sendDtmf(
            const int32_t tone
            ,CallHandlingServicesProxyReply& reply
        ) = 0;
        /**
            acceptCall Method ID: 2
        **/
        virtual void acceptCall(
            const asi::connectivity::al::DeviceType device
            ,CallHandlingServicesProxyReply& reply
        ) = 0;
        /**
            acceptAndHoldCall Method ID: 0
        **/
        virtual void acceptAndHoldCall(
            const asi::connectivity::al::DeviceType device,
            const int32_t callId
            ,CallHandlingServicesProxyReply& reply
        ) = 0;
        /**
            switchCalls Method ID: 22
        **/
        virtual void switchCalls(
            const asi::connectivity::al::DeviceType device
            ,CallHandlingServicesProxyReply& reply
        ) = 0;
        /**
            dialNumber Method ID: 6
        **/
        virtual void dialNumber(
            const asi::connectivity::al::DeviceType device,
            const CIPtr< CIString >& number,
            const bool isEmergencyNumber
            ,CallHandlingServicesProxyReply& reply
        ) = 0;
        /**
            hangupCall Method ID: 10
        **/
        virtual void hangupCall(
            const asi::connectivity::al::DeviceType device,
            const int32_t callID
            ,CallHandlingServicesProxyReply& reply
        ) = 0;
        /**
            joinCalls Method ID: 14
        **/
        virtual void joinCalls(
            const asi::connectivity::al::DeviceType device
            ,CallHandlingServicesProxyReply& reply
        ) = 0;
        /**
            splitCall Method ID: 20
        **/
        virtual void splitCall(
            const asi::connectivity::al::DeviceType device,
            const int32_t callID
            ,CallHandlingServicesProxyReply& reply
        ) = 0;
        /**
            holdActiveCalls Method ID: 12
        **/
        virtual void holdActiveCalls(
            const asi::connectivity::al::DeviceType device
            ,CallHandlingServicesProxyReply& reply
        ) = 0;
        /**
            resumeHeldCalls Method ID: 16
        **/
        virtual void resumeHeldCalls(
            const asi::connectivity::al::DeviceType device
            ,CallHandlingServicesProxyReply& reply
        ) = 0;
        /**
            *
         * Execute a USSD (unstructured supplementary service code). The response may take up to
         * 30s.
         * @param serviceCode the service code to execute
         
            executeUSSD Method ID: 8
        **/
        virtual void executeUSSD(
            const CIPtr< CIString >& serviceCode
            ,CallHandlingServicesProxyReply& reply
        ) = 0;
        /**
            *
         * Cancel any ongoing USSD session
         
            cancelUSSD Method ID: 4
        **/
        virtual void cancelUSSD(
            
            CallHandlingServicesProxyReply& reply
        ) = 0;

        /*!
        \brief Informs the service about a connected client
        \param count The number of connected clients
        \param reply A proxy that can be used to reply to the connected client. If the client did
        not register its reply interface, calling valid() or isAlive() on reply will return false.
        In this case calling any other methods of the proxy will yield in undefined behaviour.
        */
        virtual void clientConnected(uint32_t count
            ,CallHandlingServicesProxyReply& reply
        ) {}

        /*!
        \brief Informs the service that a client disconnected
        \param count the number of connected clients
        \param reply The proxy to the disconnected client. It is not alive any more, but can be used for comparison
        if it ever was valid.
        */
        virtual void clientDisconnected(uint32_t count
            ,CallHandlingServicesProxyReply& reply
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
                CallHandlingServicesServiceRegistration(comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_AL_CALLHANDLINGSERVICES_REQUEST), instance_no), static_cast<CallHandlingServicesS*>(this), l, factory );
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
                CallHandlingServicesServiceRegistration(comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_AL_CALLHANDLINGSERVICES_REQUEST), instance_no), static_cast<CallHandlingServicesS*>(this), l );
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
            m_registration = CallHandlingServicesServiceRegistration();
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
            CallHandlingServicesServiceRegistration tmp{m_registration};
            // let go of the reference the member holds
            m_registration = CallHandlingServicesServiceRegistration();
            // call unregisterAndNotify
            return tmp.unregisterAndNotify(callback, ctx);
        }

        virtual ~CallHandlingServicesS()
        {
            // unregister in case it wasn't done by the caller.
            unregisterSelf();
        }

        // call ids
        void
        sendDtmfCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<CallHandlingServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 18;
            ce.assign(inst, mid);
        }
        void
        acceptCallCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<CallHandlingServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 2;
            ce.assign(inst, mid);
        }
        void
        acceptAndHoldCallCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<CallHandlingServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 0;
            ce.assign(inst, mid);
        }
        void
        switchCallsCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<CallHandlingServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 22;
            ce.assign(inst, mid);
        }
        void
        dialNumberCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<CallHandlingServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 6;
            ce.assign(inst, mid);
        }
        void
        hangupCallCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<CallHandlingServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 10;
            ce.assign(inst, mid);
        }
        void
        joinCallsCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<CallHandlingServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 14;
            ce.assign(inst, mid);
        }
        void
        splitCallCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<CallHandlingServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 20;
            ce.assign(inst, mid);
        }
        void
        holdActiveCallsCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<CallHandlingServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 12;
            ce.assign(inst, mid);
        }
        void
        resumeHeldCallsCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<CallHandlingServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 16;
            ce.assign(inst, mid);
        }
        void
        executeUSSDCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<CallHandlingServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 8;
            ce.assign(inst, mid);
        }
        void
        cancelUSSDCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<CallHandlingServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 4;
            ce.assign(inst, mid);
        }

    protected:
        CallHandlingServicesServiceRegistration m_registration;
    };

} //namespace asi
} //namespace connectivity
} //namespace al
#endif// ASI_CONNECTIVITY_AL_CALLHANDLINGSERVICESS_HXX
