/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceS_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_MESSAGING_MAPSETUPS_HXX
#define ASI_CONNECTIVITY_AL_MESSAGING_MAPSETUPS_HXX

#include <common/Macros.hxx>

#include <comm/commtypes.hxx>
#include <comm/commidltypes.hxx>
#include <comm/CallEvent.hxx>
#include <asi/connectivity/al/messaging/MapSetupServiceRegistration.hxx>

#include <asi/connectivity/al/messaging/Definitions.hxx>


namespace asi
{
namespace connectivity
{
namespace al
{
namespace messaging
{

    /**
    \brief  The messaging::MapSetup interface on tthe service side.
    \details
            A service instance needs to implement this interface.
        *
    * Interface to setup map, because the Bluetooth application does the service startup/teardown.
    **/
    class MapSetupS
    {
    public:
        MapSetupS () {}
    // List of request methods
        /**
            *
       * @brief Informs Messaging of connected/disconnected devices for MAP.
       *
       * @param friendlyName Friendly name of connected device (if connected)
       * @param address MAC address of the device.
       * @param isMapConnected Is MAP connected for the device?
       * @param isSapConnected Is the device connected via SAP?
       * @param isHfpConnected Is the device connected via HFP?
       * @param slotNumber Slot number that device is currently assigned to
       
            updateDeviceStatus Method ID: 0
        **/
        virtual void updateDeviceStatus(
            const CIPtr< CIString >& friendlyName,
            const int64_t address,
            const bool isMapConnected,
            const bool isSapConnected,
            const bool isHfpConnected,
            const bool isPbapConnected,
            const bool isPimDevice
        ) = 0;

        /*!
        \brief Informs the service about a connected client
        \param count The number of connected clients
        */
        virtual void clientConnected(uint32_t count
        ) {}

        /*!
        \brief Informs the service that a client disconnected
        \param count the number of connected clients
        */
        virtual void clientDisconnected(uint32_t count
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
                MapSetupServiceRegistration(comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_AL_MESSAGING_MAPSETUP_REQUEST), instance_no), static_cast<MapSetupS*>(this), l, factory );
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
                MapSetupServiceRegistration(comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_AL_MESSAGING_MAPSETUP_REQUEST), instance_no), static_cast<MapSetupS*>(this), l );
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
            m_registration = MapSetupServiceRegistration();
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
            MapSetupServiceRegistration tmp{m_registration};
            // let go of the reference the member holds
            m_registration = MapSetupServiceRegistration();
            // call unregisterAndNotify
            return tmp.unregisterAndNotify(callback, ctx);
        }

        virtual ~MapSetupS()
        {
            // unregister in case it wasn't done by the caller.
            unregisterSelf();
        }

        // call ids
        void
        updateDeviceStatusCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<MapSetupS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 0;
            ce.assign(inst, mid);
        }

    protected:
        MapSetupServiceRegistration m_registration;
    };

} //namespace asi
} //namespace connectivity
} //namespace al
} //namespace messaging
#endif// ASI_CONNECTIVITY_AL_MESSAGING_MAPSETUPS_HXX
