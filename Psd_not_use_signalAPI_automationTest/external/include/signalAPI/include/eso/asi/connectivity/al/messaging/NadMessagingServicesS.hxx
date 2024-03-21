/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceS_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_MESSAGING_NADMESSAGINGSERVICESS_HXX
#define ASI_CONNECTIVITY_AL_MESSAGING_NADMESSAGINGSERVICESS_HXX

#include <common/Macros.hxx>

#include <comm/commtypes.hxx>
#include <comm/commidltypes.hxx>
#include <comm/CallEvent.hxx>
#include <asi/connectivity/al/messaging/NadMessagingServicesServiceRegistration.hxx>
#include <asi/connectivity/al/messaging/StructSimInfo.hxx>

#include <asi/connectivity/al/messaging/Definitions.hxx>

#include <asi/connectivity/al/messaging/NadMessagingServicesProxyReply.hxx>
#include <asi/connectivity/al/messaging/NadMessagingServicesReplyS.hxx>

namespace asi
{
namespace connectivity
{
namespace al
{
namespace messaging
{

    /**
    \brief  The messaging::NadMessagingServices interface on tthe service side.
    \details
            A service instance needs to implement this interface.
    **/
    class NadMessagingServicesS
    {
    public:
        NadMessagingServicesS () {}
    // List of request methods
        /**
            *
        * Selects the sms storage.
        *
        * @param readStorage Read sms memory storage.
        * @param writeStorage Write sms memory storage.
        * @param receiveStorage Received memory storage.
        
            selectSmsStorage Method ID: 14
        **/
        virtual void selectSmsStorage(
            const uint32_t deviceId,
            const asi::connectivity::al::messaging::SmsStorage readStorage,
            const asi::connectivity::al::messaging::SmsStorage writeStorage,
            const asi::connectivity::al::messaging::SmsStorage receiveStorage
            ,NadMessagingServicesProxyReply& reply
        ) = 0;
        /**
            *
       * Request to get the service center.
       * 
       * @param deviceId Device Identifier.
       
            getSMSC Method ID: 2
        **/
        virtual void getSMSC(
            const uint32_t deviceId
            ,NadMessagingServicesProxyReply& reply
        ) = 0;
        /**
            *
       * Request to get the service center.
       *
       * @param deviceId Device Identifier.
       
            setSMSC Method ID: 20
        **/
        virtual void setSMSC(
            const uint32_t deviceId,
            const CIPtr< CIString >& number,
            const asi::connectivity::al::messaging::NumberingScheme numberType
            ,NadMessagingServicesProxyReply& reply
        ) = 0;
        /**
            *
       * Request to Enable/Disable automatic SMS status update after reading a sms.
       * 
       * @param enable true Status will be automatically set to read.
       * 	false The status won't be changed.
       
            setStatusUpdateMode Method ID: 22
        **/
        virtual void setStatusUpdateMode(
            const uint32_t deviceId,
            const bool enable
            ,NadMessagingServicesProxyReply& reply
        ) = 0;
        /**
            *
       * Request to set the sms text mode parameters.
       * 
       * @param deviceId DeviceIdentifier.
       * @param firstOctet FirstOctet (TP-MTI, TP-RD, TP-VDF, TP-SRR, TP-UDHI, TP-RP).
       * @param validityPeriod Validity period.
       * @param dataCodingScheme Data coding scheme.
       
            setSmsModeParameters Method ID: 21
        **/
        virtual void setSmsModeParameters(
            const uint32_t deviceId,
            const uint32_t firstOctet,
            const uint32_t validityPeriod,
            const uint32_t dataCodingScheme
            ,NadMessagingServicesProxyReply& reply
        ) = 0;
        /**
            *
       * Deletes the specified Messages.
       
            deleteMessages Method ID: 0
        **/
        virtual void deleteMessages(
            const uint32_t deviceId,
            const asi::connectivity::al::messaging::NadDeleteFlag deleteFlag,
            const uint32_t index
            ,NadMessagingServicesProxyReply& reply
        ) = 0;
        /**
            *
       * Request to get a list of messages.
       
            listMessages Method ID: 4
        **/
        virtual void listMessages(
            const uint32_t deviceId,
            const asi::connectivity::al::messaging::NadMessageStatus status
            ,NadMessagingServicesProxyReply& reply
        ) = 0;
        /**
            *
       * Requests the pdu of a specified message.
       *
       * @param deviceId Device Identifier.
       * @param index Index of the message. 
       
            readRawMessage Method ID: 13
        **/
        virtual void readRawMessage(
            const uint32_t deviceId,
            const uint32_t index
            ,NadMessagingServicesProxyReply& reply
        ) = 0;
        /**
            *
       * Sends a message in pdu format.
       *
       * @param deviceId Device Identifier.
       * @param pduSize Length of the pdu to send.
       * @param pdu Sms pdu data to be sent.
       
            sendRawMessage Method ID: 19
        **/
        virtual void sendRawMessage(
            const uint32_t deviceId,
            const uint32_t pduSize,
            const CIPtr< CIString >& pdu
            ,NadMessagingServicesProxyReply& reply
        ) = 0;
        /**
            *
       * Sends a specified message from the storage.
       * 
       * @param deviceId Device Identifier.
       * @param index Index of the new message.
       
            sendMessageFromStorage Method ID: 16
        **/
        virtual void sendMessageFromStorage(
            const uint32_t deviceId,
            const uint32_t index
            ,NadMessagingServicesProxyReply& reply
        ) = 0;
        /**
            *
       * Writes a message in pdu format.
       *
       * @param deviceId Device Identifier.
       * @param pduSize Length of the pdu to send.
       * @param pdu Sms pdu data to be sent.
       
            writeRawMessage Method ID: 24
        **/
        virtual void writeRawMessage(
            const uint32_t deviceId,
            const uint32_t pduSize,
            const CIPtr< CIString >& pdu
            ,NadMessagingServicesProxyReply& reply
        ) = 0;

        /*!
        \brief Informs the service about a connected client
        \param count The number of connected clients
        \param reply A proxy that can be used to reply to the connected client. If the client did
        not register its reply interface, calling valid() or isAlive() on reply will return false.
        In this case calling any other methods of the proxy will yield in undefined behaviour.
        */
        virtual void clientConnected(uint32_t count
            ,NadMessagingServicesProxyReply& reply
        ) {}

        /*!
        \brief Informs the service that a client disconnected
        \param count the number of connected clients
        \param reply The proxy to the disconnected client. It is not alive any more, but can be used for comparison
        if it ever was valid.
        */
        virtual void clientDisconnected(uint32_t count
            ,NadMessagingServicesProxyReply& reply
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
                NadMessagingServicesServiceRegistration(comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_AL_MESSAGING_NADMESSAGINGSERVICES_REQUEST), instance_no), static_cast<NadMessagingServicesS*>(this), l, factory );
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
                NadMessagingServicesServiceRegistration(comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_AL_MESSAGING_NADMESSAGINGSERVICES_REQUEST), instance_no), static_cast<NadMessagingServicesS*>(this), l );
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
            m_registration = NadMessagingServicesServiceRegistration();
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
            NadMessagingServicesServiceRegistration tmp{m_registration};
            // let go of the reference the member holds
            m_registration = NadMessagingServicesServiceRegistration();
            // call unregisterAndNotify
            return tmp.unregisterAndNotify(callback, ctx);
        }

        virtual ~NadMessagingServicesS()
        {
            // unregister in case it wasn't done by the caller.
            unregisterSelf();
        }

        // call ids
        void
        selectSmsStorage_U32_SmsStorage_SmsStorage_SmsStorageCallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<NadMessagingServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 14;
            ce.assign(inst, mid);
        }
        void
        getSMSC_U32CallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<NadMessagingServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 2;
            ce.assign(inst, mid);
        }
        void
        setSMSCCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NadMessagingServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 20;
            ce.assign(inst, mid);
        }
        void
        setStatusUpdateModeCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NadMessagingServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 22;
            ce.assign(inst, mid);
        }
        void
        setSmsModeParametersCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NadMessagingServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 21;
            ce.assign(inst, mid);
        }
        void
        deleteMessages_U32_NadDeleteFlag_U32CallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<NadMessagingServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 0;
            ce.assign(inst, mid);
        }
        void
        listMessages_U32_NadMessageStatusCallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<NadMessagingServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 4;
            ce.assign(inst, mid);
        }
        void
        readRawMessage_U32_U32CallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<NadMessagingServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 13;
            ce.assign(inst, mid);
        }
        void
        sendRawMessage_U32_U32_SCallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<NadMessagingServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 19;
            ce.assign(inst, mid);
        }
        void
        sendMessageFromStorage_U32_U32CallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<NadMessagingServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 16;
            ce.assign(inst, mid);
        }
        void
        writeRawMessage_U32_U32_SCallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<NadMessagingServicesS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 24;
            ce.assign(inst, mid);
        }

    protected:
        NadMessagingServicesServiceRegistration m_registration;
    };

} //namespace asi
} //namespace connectivity
} //namespace al
} //namespace messaging
#endif// ASI_CONNECTIVITY_AL_MESSAGING_NADMESSAGINGSERVICESS_HXX
