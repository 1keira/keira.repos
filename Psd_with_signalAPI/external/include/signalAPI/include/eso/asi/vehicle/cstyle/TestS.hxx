/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleInterfaceS_hxx.tmpl
*/
#ifndef ASI_VEHICLE_TESTS_CSTYLE_HXX
#define ASI_VEHICLE_TESTS_CSTYLE_HXX

#include <common/Macros.hxx>

#include <comm/commtypes.hxx>
#include <comm/commidltypes.hxx>
#include <comm/CallEvent.hxx>
#include <asi/vehicle/cstyle/TestServiceRegistration.hxx>
#include <asi/vehicle/cstyle/StructKlemmenStatus01Struct.hxx>
#include <asi/vehicle/cstyle/Definitions.hxx>
#include <asi/vehicle/cstyle/TestProxyReply.hxx>
#include <asi/vehicle/cstyle/TestReplyS.hxx>

namespace asi
{
namespace vehicle
{
namespace cstyle
{

    /**
    \brief  The vehicle::cstyle::Test interface on tthe service side.
    \details
            A service instance needs to implement this interface.
    **/
    class TestS
    {
    public:
        TestS () {}
    // List of request methods
        /**
            \brief
            getter for the attribute Klemmen_Status_01
            \details
            ***
         * Note: Please inform eso.IN-Car@esolutions.de if you are using this interface.
         * You will then be involved on changes in this interface.
         * ZAS_Kl_15:
         *   * E3_1_1_UNECE: Klemmen_Status_01.ZAS_Kl_15
         * > KlemmenStatus01Struct.ZAS_Kl_15 [uint64]:
         *   Based on:
         *     * ZAS_Kl_15: Klemme 15: Zuendung (SW-Kl.15)
         *   Used Constants:
         *     0: eZASKl15_Aus
         *     1: eZASKl15_Ein
         * > KlemmenStatus01Struct.pdustate [uint64]:
         *   Based on:
         *     ZAS_Kl_15 SignalState
         *   Used Constants:
         *     0: ePdustate_NotExisting
         *     1: ePdustate_Valid
         *     2: ePdustate_TempNotValid
         *     3: ePdustate_TimeoutNotValidNotFiltered
         *     4: ePdustate_NeverReceived
         *     5: ePdustate_TimeoutNotValidFiltered
         *     15: ePdustate_Invalid
         ***
            getKlemmen_Status_01 Method ID: 3
        **/
        virtual void getKlemmen_Status_01(
            
            TestProxyReply& reply
        ) = 0;
        /**
            \brief
            setNotification for all notifiable attributes
            setNotification Method ID: 32767
        **/
        virtual void setNotification(
            
            TestProxyReply& reply
        ) = 0;
        /**
            \brief
            setNotification for one specific attribute
            setNotification Method ID: 32765
        **/
        virtual void setNotification(
            const uint32_t attributeId
            ,TestProxyReply& reply
        ) = 0;
        /**
            \brief
            setNotification for a list of attributes
            setNotification Method ID: 32766
        **/
        virtual void setNotification(
            const ipl::vector<uint32_t>* attributeId
            ,TestProxyReply& reply
        ) = 0;
        /**
            \brief
            clearNotification for all notifiable attributes
            clearNotification Method ID: 32764
        **/
        virtual void clearNotification(
            
            TestProxyReply& reply
        ) = 0;
        /**
            \brief
            clearNotification for one specific attribute
            clearNotification Method ID: 32762
        **/
        virtual void clearNotification(
            const uint32_t attributeId
            ,TestProxyReply& reply
        ) = 0;
        /**
            \brief
            clearNotification for a list of attributes
            clearNotification Method ID: 32763
        **/
        virtual void clearNotification(
            const ipl::vector<uint32_t>* attributeId
            ,TestProxyReply& reply
        ) = 0;

        /*!
        \brief Informs the service about a connected client
        \param count The number of connected clients
        \param reply A proxy that can be used to reply to the connected client. If the client did
        not register its reply interface, calling valid() or isAlive() on reply will return false.
        In this case calling any other methods of the proxy will yield in undefined behaviour.
        */
        virtual void clientConnected(uint32_t count
            ,TestProxyReply& reply
        ) {}

        /*!
        \brief Informs the service that a client disconnected
        \param count the number of connected clients
        \param reply The proxy to the disconnected client. It is not alive any more, but can be used for comparison
        if it ever was valid.
        */
        virtual void clientDisconnected(uint32_t count
            ,TestProxyReply& reply
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
                TestServiceRegistration(comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_VEHICLE_TEST_REQUEST), instance_no), static_cast<TestS*>(this), l, factory );
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
                TestServiceRegistration(comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_VEHICLE_TEST_REQUEST), instance_no), static_cast<TestS*>(this), l );
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
            m_registration = TestServiceRegistration();
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
            m_registration = TestServiceRegistration();
            return false;
        }

        virtual ~TestS()
        {
            // unregister in case it wasn't done by the caller.
            unregisterSelf();
        }

        // call ids
        void
        getKlemmen_Status_01CallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<TestS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 3;
            ce.assign(inst, mid);
        }
        void
        setNotification_CallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<TestS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 32767;
            ce.assign(inst, mid);
        }
        void
        setNotification_U32CallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<TestS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 32765;
            ce.assign(inst, mid);
        }
        void
        setNotification_aU32CallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<TestS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 32766;
            ce.assign(inst, mid);
        }
        void
        clearNotification_CallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<TestS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 32764;
            ce.assign(inst, mid);
        }
        void
        clearNotification_U32CallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<TestS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 32762;
            ce.assign(inst, mid);
        }
        void
        clearNotification_aU32CallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<TestS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 32763;
            ce.assign(inst, mid);
        }

    protected:
        TestServiceRegistration m_registration;
    };

} // namespace cstyle
} //namespace asi
} //namespace vehicle
#endif// ASI_VEHICLE_TESTS_CSTYLE_HXX
