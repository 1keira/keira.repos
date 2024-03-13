/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceS_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_MESSAGING_MAPSERVICESNGS_HXX
#define ASI_CONNECTIVITY_AL_MESSAGING_MAPSERVICESNGS_HXX

#include <common/Macros.hxx>

#include <comm/commtypes.hxx>
#include <comm/commidltypes.hxx>
#include <comm/CallEvent.hxx>
#include <asi/connectivity/al/messaging/MapServicesNGServiceRegistration.hxx>
#include <asi/connectivity/al/messaging/StructMapAccount.hxx>
#include <asi/connectivity/al/messaging/StructMapAttachments.hxx>
#include <asi/connectivity/al/messaging/StructMapEnvelopeVcard.hxx>
#include <asi/connectivity/al/messaging/StructMapHeaderEntry.hxx>

#include <asi/connectivity/al/messaging/Definitions.hxx>

#include <asi/connectivity/al/messaging/MapServicesNGProxyReply.hxx>
#include <asi/connectivity/al/messaging/MapServicesNGReplyS.hxx>

namespace asi
{
namespace connectivity
{
namespace al
{
namespace messaging
{

    /**
    \brief  The messaging::MapServicesNG interface on tthe service side.
    \details
            A service instance needs to implement this interface.
    **/
    class MapServicesNGS
    {
    public:
        MapServicesNGS () {}
    // List of request methods
        /**
            *
       * Get subfolders of given folder
       *
       * @startuml
       * Client -> Server: getFolders(account, "telecom/msg")
       * alt SUCCESS
       * Server -> Client: getFolders(account, "telecom/msg", "inbox", 100, 5)
       * Server -> Client: getFolders(account, "telecom/msg", "outbox", 0, 0)
       * Server -> Client: getFolders(account, "telecom/msg", "sent", 10, 0)
       * Server -> Client: getFolders(account, "telecom/msg", "deleted", 0, 0)
       * Server -> Client: getFolders(account, "telecom/msg", "draft", 0, 0)
       * Server -> Client: onMapJobTerminated(ERROR_SUCCESS)
       * else FAILED
       * Server -> Client: onMapJobTerminated(ERROR_FAILED)
       * end
       * @enduml
       *
       * @param accountId Account Identifier.
       * @param folder path to folder (e.g. telecom/msg/inbox), may be empty to access root
       
            getFolders Method ID: 1
        **/
        virtual void getFolders(
            const int32_t accoundId,
            const CIPtr< CIString >& folder
            ,MapServicesNGProxyReply& reply
        ) = 0;
        /**
            *
       * Requests the numbers of messages in the given folder.
       *
       * @startuml
       * Client -> Server: getMessageCount(account, "telecom/msg/inbox", true)
       * alt SUCCESS
       * Server -> Client: getMessageCount(account, "telecom/msg/inbox", 5)
       * Server -> Client: onMapJobTerminated(ERROR_SUCCESS)
       * else FAILED
       * Server -> Client: onMapJobTerminated(ERROR_FAILED)
       * end
       * @enduml
       *
       * @param accountId Account Identifier.
       * @param folder Path of folder
       * @param unread_only If set, only the count of unread messages in given folder is returned (if supported by the device).
       
            getMessageCount Method ID: 3
        **/
        virtual void getMessageCount(
            const int32_t accountId,
            const CIPtr< CIString >& folder,
            const bool unread_only
            ,MapServicesNGProxyReply& reply
        ) = 0;
        /**
            *
       * Requests the message headers.
       *
       * @startuml
       * Client -> Server: getMessageHeaders(account, "telecom/msg/inbox", 10, 2)
       * alt SUCCESS
       * Server -> Client: getMessageHeaders(account, "telecom/msg/inbox", 10, [ {from@me.com, Subject1, ...}, {from@me.com, Subject2, ...}])
       * Server -> Client: onMapJobTerminated(ERROR_SUCCESS)
       * else FAILED
       * Server -> Client: onMapJobTerminated(ERROR_FAILED)
       * end
       * @enduml
       *
       * @param accountId Account Identifier.
       * @param folderId Folder Identifier.
       * @param offset Index of the first requested message header.
       * @param count Number of requested message headers.
       
            getMessageHeaders Method ID: 6
        **/
        virtual void getMessageHeaders(
            const int32_t accountId,
            const CIPtr< CIString >& folder,
            const int32_t offset,
            const int32_t count
            ,MapServicesNGProxyReply& reply
        ) = 0;
        /**
            *
       * Push message into given folder
       *
       * @startuml
       * Client -> Server: pushMessage(account, "telecom/msg/outbox", EMAIL, "test@me.com", "/tmp/msg_to_send")
       * alt SUCCESS
       * Server -> Client: pushMessage(account, MSG_HANDLE)
       * Server -> Client: onMapJobTerminated(ERROR_SUCCESS)
       * else FAILED
       * Server -> Client: onMapJobTerminated(ERROR_FAILED)
       * end
       * @enduml
       *
       * @param accountId Account identifier
       * @param folder destination folder
       * @param type message type
       * @param recipients list of recipients
       * @param path_to_message file on local filesystem which should be pushed to folder
       
            pushMessage Method ID: 18
        **/
        virtual void pushMessage(
            const int32_t accountId,
            const CIPtr< CIString >& folder,
            const asi::connectivity::al::messaging::MapMessageType type,
            const CIPtr< CIPtrArray< asi::connectivity::al::messaging::MapEnvelopeVcard > >& recipients,
            const CIPtr< CIString >& path_to_message,
            const CIPtr< CIString >& messageId,
            const bool withAttachments,
            const asi::connectivity::al::messaging::MapModifyText modifyText
            ,MapServicesNGProxyReply& reply
        ) = 0;
        /**
            *
       * Push message to given folder
       * @note pushMessage seems to be broken, thus pushMessageEx is introduced to handled recipient and attachments
       *       correctly and memory efficient (provide attachments and encoded attachments on the fly).
       *
       * @startuml
       * Client -> Server: pushMessageEx(account, "telecom/msg/outbox", EMAIL, from@me.com, [test1@eso.de, test2@eso.de], "Test subject", "This is a plain text body", [{/tmp/part1, vcard, test.vcf, FALSE}, ...)
       * alt SUCCESS
       * Server -> Client: pushMessage(account, MSG_HANDLE)
       * Server -> Client: onMapJobTerminated(ERROR_SUCCESS)
       * else FAILED
       * Server -> Client: onMapJobTerminated(ERROR_FAILED)
       * end
       * @enduml
       *
       * @param accountId Account identifier
       * @param folder destination folder
       * @param type message type
       * @param originator message originator (optional)
       * @param to list of recipients
       * @param cc list of carbon copies
       * @param bcc list of blind carbon copies
       * @param text_body plain text body to be send
       * @param attachments list of attachments to append
       
            pushMessageEx Method ID: 19
        **/
        virtual void pushMessageEx(
            const int32_t accountId,
            const CIPtr< CIString >& folder,
            const asi::connectivity::al::messaging::MapMessageType type,
            const CIPtr< asi::connectivity::al::messaging::MapEnvelopeVcard >& originator,
            const CIPtr< CIPtrArray< asi::connectivity::al::messaging::MapEnvelopeVcard > >& to,
            const CIPtr< CIPtrArray< asi::connectivity::al::messaging::MapEnvelopeVcard > >& cc,
            const CIPtr< CIPtrArray< asi::connectivity::al::messaging::MapEnvelopeVcard > >& bcc,
            const CIPtr< CIString >& subject,
            const CIPtr< CIString >& text_body,
            const CIPtr< CIPtrArray< asi::connectivity::al::messaging::MapAttachments > >& attachments
            ,MapServicesNGProxyReply& reply
        ) = 0;
        /**
            *
       * Change read status of given message
       *
       * @startuml
       * Client -> Server: setMessageReadStatus(account, "telecom/msg/inbox", "123456789", true)
       * alt SUCCESS
       * Server -> Client: onMapJobTerminated(ERROR_SUCCESS)
       * else FAILED
       * Server -> Client: onMapJobTerminated(ERROR_FAILED)
       * end
       * @enduml
       *
       * @param accountId Account identifier
       * @param folder folder where messageId is located
       * @param messageId message id
       * @param read true to mark message as read, false to mark as unread
       
            setMessageReadStatus Method ID: 20
        **/
        virtual void setMessageReadStatus(
            const int32_t accountId,
            const CIPtr< CIString >& folder,
            const CIPtr< CIString >& messageId,
            const bool read
            ,MapServicesNGProxyReply& reply
        ) = 0;
        /**
            *
       * Request ME to update inbox
       *
       * @startuml
       * Client -> Server: updateInbox(account)
       * alt SUCCESS
       * Server -> Client: onMapJobTerminated(ERROR_SUCCESS)
       * else FAILED
       * Server -> Client: onMapJobTerminated(ERROR_FAILED)
       * end
       * @enduml
       *
       * @param accountId Account identifier
       
            updateInbox Method ID: 22
        **/
        virtual void updateInbox(
            const int32_t accountId
            ,MapServicesNGProxyReply& reply
        ) = 0;
        /**
            *
       * Delete message
       *
       * @startuml
       * Client -> Server: deleteMessage(account, "telecom/msg/inbox", "123456789")
       * alt SUCCESS
       * Server -> Client: onMapJobTerminated(ERROR_SUCCESS)
       * else FAILED
       * Server -> Client: onMapJobTerminated(ERROR_FAILED)
       * end
       * @enduml
       *
       * @param accountId Account identifier
       * @param folder folder where messageId is located
       * @param messageId message id
       
            deleteMessage Method ID: 0
        **/
        virtual void deleteMessage(
            const int32_t accountId,
            const CIPtr< CIString >& folder,
            const CIPtr< CIString >& messageId
            ,MapServicesNGProxyReply& reply
        ) = 0;
        /**
            *
       * Retrieve message from given MAP account
       *
       * @startuml
       * Client -> Server: messageContent(account, "123456789", true)
       * alt SUCCESS
       * Server -> Client: messageContentHeaders(account, "123456789", sender: Telekom Service, recipients: {YourNumber})
       * Server -> Client: messageContentPart(account, "123456789", "/tmp/message_123456789/part_0)
       * Server -> Client: messageContentPart(account, "123456789", "/tmp/message_123456789/part_1)
       * Server -> Client: messageContentPart(account, "123456789", "/tmp/message_123456789/part_2)
       * Server -> Client: onMapJobTerminated(ERROR_SUCCESS)
       * else FAILED
       * Server -> Client: onMapJobTerminated(ERROR_FAILED)
       * end
       * @enduml
       
            messageContent Method ID: 7
        **/
        virtual void messageContent(
            const int32_t accountId,
            const CIPtr< CIString >& messageId,
            const CIPtr< CIString >& folderPath,
            const bool with_attachments
            ,MapServicesNGProxyReply& reply
        ) = 0;

        /*!
        \brief Informs the service about a connected client
        \param count The number of connected clients
        \param reply A proxy that can be used to reply to the connected client. If the client did
        not register its reply interface, calling valid() or isAlive() on reply will return false.
        In this case calling any other methods of the proxy will yield in undefined behaviour.
        */
        virtual void clientConnected(uint32_t count
            ,MapServicesNGProxyReply& reply
        ) {}

        /*!
        \brief Informs the service that a client disconnected
        \param count the number of connected clients
        \param reply The proxy to the disconnected client. It is not alive any more, but can be used for comparison
        if it ever was valid.
        */
        virtual void clientDisconnected(uint32_t count
            ,MapServicesNGProxyReply& reply
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
                MapServicesNGServiceRegistration(comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_AL_MESSAGING_MAPSERVICESNG_REQUEST), instance_no), static_cast<MapServicesNGS*>(this), l, factory );
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
                MapServicesNGServiceRegistration(comm::InstanceID (comm::InterfaceID(BINARY_UUID_ASI_CONNECTIVITY_AL_MESSAGING_MAPSERVICESNG_REQUEST), instance_no), static_cast<MapServicesNGS*>(this), l );
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
            m_registration = MapServicesNGServiceRegistration();
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
            MapServicesNGServiceRegistration tmp{m_registration};
            // let go of the reference the member holds
            m_registration = MapServicesNGServiceRegistration();
            // call unregisterAndNotify
            return tmp.unregisterAndNotify(callback, ctx);
        }

        virtual ~MapServicesNGS()
        {
            // unregister in case it wasn't done by the caller.
            unregisterSelf();
        }

        // call ids
        void
        getFolders_I32_SCallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<MapServicesNGS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 1;
            ce.assign(inst, mid);
        }
        void
        getMessageCount_I32_S_BCallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<MapServicesNGS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 3;
            ce.assign(inst, mid);
        }
        void
        getMessageHeaders_I32_S_I32_I32CallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<MapServicesNGS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 6;
            ce.assign(inst, mid);
        }
        void
        pushMessage_I32_S_MapMessageType_aMapEnvelopeVcard_S_S_B_MapModifyTextCallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<MapServicesNGS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 18;
            ce.assign(inst, mid);
        }
        void
        pushMessageExCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<MapServicesNGS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 19;
            ce.assign(inst, mid);
        }
        void
        setMessageReadStatusCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<MapServicesNGS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 20;
            ce.assign(inst, mid);
        }
        void
        updateInboxCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<MapServicesNGS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 22;
            ce.assign(inst, mid);
        }
        void
        deleteMessageCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<MapServicesNGS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 0;
            ce.assign(inst, mid);
        }
        void
        messageContentCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<MapServicesNGS*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 7;
            ce.assign(inst, mid);
        }

    protected:
        MapServicesNGServiceRegistration m_registration;
    };

} //namespace asi
} //namespace connectivity
} //namespace al
} //namespace messaging
#endif// ASI_CONNECTIVITY_AL_MESSAGING_MAPSERVICESNGS_HXX
