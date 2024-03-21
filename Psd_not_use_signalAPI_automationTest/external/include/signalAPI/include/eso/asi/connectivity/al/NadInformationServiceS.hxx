/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceS_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_NADINFORMATIONSERVICES_HXX
#define ASI_CONNECTIVITY_AL_NADINFORMATIONSERVICES_HXX

#include <common/Macros.hxx>

#include <comm/commtypes.hxx>
#include <comm/commidltypes.hxx>
#include <comm/CallEvent.hxx>
#include <asi/connectivity/al/NadInformationServiceServiceRegistration.hxx>
#include <asi/connectivity/al/StructAntennaInfo.hxx>
#include <asi/connectivity/al/StructDataConnectionInfo.hxx>
#include <asi/connectivity/al/StructDataConnectionStartResult.hxx>
#include <asi/connectivity/al/StructNadDeviceInformation.hxx>
#include <asi/connectivity/al/StructNetworkInfo.hxx>
#include <asi/connectivity/al/StructNetworkRejectInformation.hxx>
#include <asi/connectivity/al/StructSimDataConfig.hxx>
#include <asi/connectivity/al/StructSimDataInfo.hxx>
#include <asi/connectivity/al/StructTemperatureInfo.hxx>

#include <asi/connectivity/al/Definitions.hxx>

#include <asi/connectivity/al/NadInformationServiceProxyReply.hxx>
#include <asi/connectivity/al/NadInformationServiceReplyS.hxx>

namespace asi
{
namespace connectivity
{
namespace al
{

    /**
    \brief  The al::NadInformationService interface on tthe service side.
    \details
            A service instance needs to implement this interface.
        *
    * Clients, which are registered with the NadInformationService,
    * will receive updates of NAD related information.
    * All information will be cached and is read-only from a client perspective.
    **/
    class NadInformationServiceS
    {
    public:
        NadInformationServiceS () {}
    // List of request methods
        /**
            \brief
            getter for the attribute AntennaInfo
            getAntennaInfo Method ID: 4
        **/
        virtual void getAntennaInfo(
            
            NadInformationServiceProxyReply& reply
        ) = 0;
        /**
            \brief
            getter for the attribute DataConnectionInfo
            getDataConnectionInfo Method ID: 5
        **/
        virtual void getDataConnectionInfo(
            
            NadInformationServiceProxyReply& reply
        ) = 0;
        /**
            \brief
            getter for the attribute SimDataConfig
            getSimDataConfig Method ID: 13
        **/
        virtual void getSimDataConfig(
            
            NadInformationServiceProxyReply& reply
        ) = 0;
        /**
            \brief
            getter for the attribute DataConnectionStartResult
            getDataConnectionStartResult Method ID: 6
        **/
        virtual void getDataConnectionStartResult(
            
            NadInformationServiceProxyReply& reply
        ) = 0;
        /**
            \brief
            getter for the attribute NadDeviceInformation
            getNadDeviceInformation Method ID: 9
        **/
        virtual void getNadDeviceInformation(
            
            NadInformationServiceProxyReply& reply
        ) = 0;
        /**
            \brief
            getter for the attribute NetworkRejectInformation
            getNetworkRejectInformation Method ID: 12
        **/
        virtual void getNetworkRejectInformation(
            
            NadInformationServiceProxyReply& reply
        ) = 0;
        /**
            \brief
            getter for the attribute SimDataInfo
            getSimDataInfo Method ID: 14
        **/
        virtual void getSimDataInfo(
            
            NadInformationServiceProxyReply& reply
        ) = 0;
        /**
            \brief
            getter for the attribute TemperatureInfo
            getTemperatureInfo Method ID: 15
        **/
        virtual void getTemperatureInfo(
            
            NadInformationServiceProxyReply& reply
        ) = 0;
        /**
            \brief
            getter for the attribute NetworkInfo
            getNetworkInfo Method ID: 11
        **/
        virtual void getNetworkInfo(
            
            NadInformationServiceProxyReply& reply
        ) = 0;
        /**
            \brief
            getter for the attribute AirplaneMode
            getAirplaneMode Method ID: 3
        **/
        virtual void getAirplaneMode(
            
            NadInformationServiceProxyReply& reply
        ) = 0;
        /**
            \brief
            getter for the attribute NadState
            getNadState Method ID: 10
        **/
        virtual void getNadState(
            
            NadInformationServiceProxyReply& reply
        ) = 0;
        /**
            \brief
            getter for the attribute JammingState
            getJammingState Method ID: 8
        **/
        virtual void getJammingState(
            
            NadInformationServiceProxyReply& reply
        ) = 0;
        /**
            \brief
            getter for the attribute DormantMode
            getDormantMode Method ID: 7
        **/
        virtual void getDormantMode(
            
            NadInformationServiceProxyReply& reply
        ) = 0;
        /**
            \brief
            setNotification for all notifiable attributes
            setNotification Method ID: 32767
        **/
        virtual void setNotification(
            
            NadInformationServiceProxyReply& reply
        ) = 0;
        /**
            \brief
            setNotification for one specific attribute
            setNotification Method ID: 32765
        **/
        virtual void setNotification(
            const uint32_t attributeId
            ,NadInformationServiceProxyReply& reply
        ) = 0;
        /**
            \brief
            setNotification for a list of attributes
            setNotification Method ID: 32766
        **/
        virtual void setNotification(
            const CIPtr< CIUInt32Array >& attributeId
            ,NadInformationServiceProxyReply& reply
        ) = 0;
        /**
            \brief
            clearNotification for all notifiable attributes
            clearNotification Method ID: 32764
        **/
        virtual void clearNotification(
            
            NadInformationServiceProxyReply& reply
        ) = 0;
        /**
            \brief
            clearNotification for one specific attribute
            clearNotification Method ID: 32762
        **/
        virtual void clearNotification(
            const uint32_t attributeId
            ,NadInformationServiceProxyReply& reply
        ) = 0;
        /**
            \brief
            clearNotification for a list of attributes
            clearNotification Method ID: 32763
        **/
        virtual void clearNotification(
            const CIPtr< CIUInt32Array >& attributeId
            ,NadInformationServiceProxyReply& reply
        ) = 0;

        /*!
        \brief Informs the service about a connected client
        \param count The number of connected clients
        \param reply A proxy that can be used to reply to the connected client. If the client did
        not register its reply interface, calling valid() or isAlive() on reply will return false.
        In this case calling any other methods of the proxy will yield in undefined behaviour.
        */
        virtual void clientConnected(uint32_t count
            ,NadInformationServiceProxyReply& reply
        ) {}

        /*!
        \brief Informs the service that a client disconnected
        \param count the number of connected clients
        \param reply The proxy to the disconnected client. It is not alive any more, but can be used for comparison
        if it ever was valid.
        */
        virtual void clientDisconnected(uint32_t count
            ,NadInformationServiceProxyReply& reply
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
                NadInformationServiceServiceRegistration(comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_AL_NADINFORMATIONSERVICE_REQUEST), instance_no), static_cast<NadInformationServiceS*>(this), l, factory );
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
                NadInformationServiceServiceRegistration(comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_AL_NADINFORMATIONSERVICE_REQUEST), instance_no), static_cast<NadInformationServiceS*>(this), l );
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
            m_registration = NadInformationServiceServiceRegistration();
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
            NadInformationServiceServiceRegistration tmp{m_registration};
            // let go of the reference the member holds
            m_registration = NadInformationServiceServiceRegistration();
            // call unregisterAndNotify
            return tmp.unregisterAndNotify(callback, ctx);
        }

        virtual ~NadInformationServiceS()
        {
            // unregister in case it wasn't done by the caller.
            unregisterSelf();
        }

        // call ids
        void
        getAntennaInfoCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NadInformationServiceS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 4;
            ce.assign(inst, mid);
        }
        void
        getDataConnectionInfoCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NadInformationServiceS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 5;
            ce.assign(inst, mid);
        }
        void
        getSimDataConfigCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NadInformationServiceS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 13;
            ce.assign(inst, mid);
        }
        void
        getDataConnectionStartResultCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NadInformationServiceS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 6;
            ce.assign(inst, mid);
        }
        void
        getNadDeviceInformationCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NadInformationServiceS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 9;
            ce.assign(inst, mid);
        }
        void
        getNetworkRejectInformationCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NadInformationServiceS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 12;
            ce.assign(inst, mid);
        }
        void
        getSimDataInfoCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NadInformationServiceS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 14;
            ce.assign(inst, mid);
        }
        void
        getTemperatureInfoCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NadInformationServiceS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 15;
            ce.assign(inst, mid);
        }
        void
        getNetworkInfoCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NadInformationServiceS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 11;
            ce.assign(inst, mid);
        }
        void
        getAirplaneModeCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NadInformationServiceS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 3;
            ce.assign(inst, mid);
        }
        void
        getNadStateCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NadInformationServiceS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 10;
            ce.assign(inst, mid);
        }
        void
        getJammingStateCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NadInformationServiceS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 8;
            ce.assign(inst, mid);
        }
        void
        getDormantModeCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NadInformationServiceS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 7;
            ce.assign(inst, mid);
        }
        void
        setNotification_CallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<NadInformationServiceS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 32767;
            ce.assign(inst, mid);
        }
        void
        setNotification_U32CallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<NadInformationServiceS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 32765;
            ce.assign(inst, mid);
        }
        void
        setNotification_aU32CallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<NadInformationServiceS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 32766;
            ce.assign(inst, mid);
        }
        void
        clearNotification_CallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<NadInformationServiceS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 32764;
            ce.assign(inst, mid);
        }
        void
        clearNotification_U32CallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<NadInformationServiceS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 32762;
            ce.assign(inst, mid);
        }
        void
        clearNotification_aU32CallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<NadInformationServiceS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 32763;
            ce.assign(inst, mid);
        }

    protected:
        NadInformationServiceServiceRegistration m_registration;
    };

} //namespace asi
} //namespace connectivity
} //namespace al
#endif// ASI_CONNECTIVITY_AL_NADINFORMATIONSERVICES_HXX
