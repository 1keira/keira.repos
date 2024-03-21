/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceS_hxx.tmpl
*/
#ifndef ASI_DIAG_UDS_READDATABYIDENTS_HXX
#define ASI_DIAG_UDS_READDATABYIDENTS_HXX

#include <common/Macros.hxx>

#include <comm/commtypes.hxx>
#include <comm/commidltypes.hxx>
#include <comm/CallEvent.hxx>
#include <asi/diag/uds/ReadDataByIdentServiceRegistration.hxx>

#include <asi/diag/uds/Definitions.hxx>

#include <asi/diag/uds/ReadDataByIdentProxyReply.hxx>
#include <asi/diag/uds/ReadDataByIdentReplyS.hxx>

namespace asi
{
namespace diag
{
namespace uds
{

    /**
    \brief  The uds::ReadDataByIdent interface on tthe service side.
    \details
            A service instance needs to implement this interface.
        * Diagnosis service interface for read by identifier in uds service (0x22, e.g. measurement).
     * Client sends data to the Service as a response 
     * based on request specified by the Identifier.
     * For example this is used to Read the values of Coding or
     * or HW version or SW Version requested by Service. 
     * And these Coding or HW Version or SW Version will be identified by 2-Byte Identifier
     * Detailed list of use cases can be found in the specifications for the corresponding node,    
     * e.g. measurements for 0x8125: "HCP3_0x8125_Messwerte_Bs42.0_03 - Austausch (EXERPT) - HCP3.reqifz"
     *
     * Every diagnosis node on system and android partition registers its own service instance of this interface.   
     * Every instance ID handles exactly the identifiers which are defined for that node.
     * The instance IDs of all nodes are defined in diag_common.idl.
    **/
    class ReadDataByIdentS
    {
    public:
        ReadDataByIdentS () {}
    // List of request methods
        /**
            
         * Register a read data by identifier handler
         * The Client should register the identifier/identifiers for which it is responsible for.
         * 
         * @param identifier identifier of a Read data by ident that this application handles
         
            registerHandler Method ID: 4
        **/
        virtual void registerHandler(
            const uint16_t identifier
            ,ReadDataByIdentProxyReply& reply
        ) = 0;
        /**
            
         * Register multiple read by identifier handlers
         * With this method Client can register for multiple Identifiers with a single call.
         * 
         * @param identifiers identifiers of Read data by idents that this application handles
         
            registerHandler Method ID: 3
        **/
        virtual void registerHandler(
            const CIPtr< CIUInt16Array >& identifiers
            ,ReadDataByIdentProxyReply& reply
        ) = 0;
        /**
            
         * The Client responds to the readValue Request from the 
         * service along with data values. 
         *
         * @param requestIdentifier identifier of the tester request, which was passed by readValue
         * @param identifier identifier of this value
         * @param value Read value for identifier
         
            readValueReply Method ID: 2
        **/
        virtual void readValueReply(
            const uint32_t requestIdentifier,
            const uint16_t identifier,
            const CIPtr< CIUInt8Array >& value
            ,ReadDataByIdentProxyReply& reply
        ) = 0;
        /**
            
         * If Client can not process the readValue request then ErrorResponse to be sent
         * Only Following eServiceOpError codes can be sent.
         * service_condition_incorrect(0x22)
         *   - This error must be sent if the condition for identifier does not apply
         * service_failure_prevents_execution(0x26)
             - This error must be sent if e.g. a hardware error prevents processing the request
         * service_request_out_of_range(0x31)
         *   - This error must be sent if requested Identifier is not supported currently or
         *     Identifier is not supported in the current  configuration (e.g. coding or parameter set does not apply).
         *
         * @param requestIdentifier identifier of the tester request, which was passed by readValue
         * @param identifier  Requested identifier
         * @param eServiceOpError Reason for failure
         
            readValueErrorReply Method ID: 1
        **/
        virtual void readValueErrorReply(
            const uint32_t requestIdentifier,
            const uint16_t identifier,
            const asi::diag::uds::eServiceOpError error
            ,ReadDataByIdentProxyReply& reply
        ) = 0;

        /*!
        \brief Informs the service about a connected client
        \param count The number of connected clients
        \param reply A proxy that can be used to reply to the connected client. If the client did
        not register its reply interface, calling valid() or isAlive() on reply will return false.
        In this case calling any other methods of the proxy will yield in undefined behaviour.
        */
        virtual void clientConnected(uint32_t count
            ,ReadDataByIdentProxyReply& reply
        ) {}

        /*!
        \brief Informs the service that a client disconnected
        \param count the number of connected clients
        \param reply The proxy to the disconnected client. It is not alive any more, but can be used for comparison
        if it ever was valid.
        */
        virtual void clientDisconnected(uint32_t count
            ,ReadDataByIdentProxyReply& reply
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
                ReadDataByIdentServiceRegistration(comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_DIAG_UDS_READDATABYIDENT_REQUEST), instance_no), static_cast<ReadDataByIdentS*>(this), l, factory );
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
                ReadDataByIdentServiceRegistration(comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_DIAG_UDS_READDATABYIDENT_REQUEST), instance_no), static_cast<ReadDataByIdentS*>(this), l );
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
            m_registration = ReadDataByIdentServiceRegistration();
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
            ReadDataByIdentServiceRegistration tmp{m_registration};
            // let go of the reference the member holds
            m_registration = ReadDataByIdentServiceRegistration();
            // call unregisterAndNotify
            return tmp.unregisterAndNotify(callback, ctx);
        }

        virtual ~ReadDataByIdentS()
        {
            // unregister in case it wasn't done by the caller.
            unregisterSelf();
        }

        // call ids
        void
        registerHandler_U16CallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<ReadDataByIdentS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 4;
            ce.assign(inst, mid);
        }
        void
        registerHandler_aU16CallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<ReadDataByIdentS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 3;
            ce.assign(inst, mid);
        }
        void
        readValueReplyCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<ReadDataByIdentS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 2;
            ce.assign(inst, mid);
        }
        void
        readValueErrorReplyCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<ReadDataByIdentS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 1;
            ce.assign(inst, mid);
        }

    protected:
        ReadDataByIdentServiceRegistration m_registration;
    };

} //namespace asi
} //namespace diag
} //namespace uds
#endif// ASI_DIAG_UDS_READDATABYIDENTS_HXX
