/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceC_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_MESSAGING_MAPSERVICESNGC_HXX
#define ASI_CONNECTIVITY_AL_MESSAGING_MAPSERVICESNGC_HXX

#include <ipl_config.h>
#include <comm/commidltypes.hxx>
#include <asi/connectivity/al/messaging/StructMapAccount.hxx>
#include <asi/connectivity/al/messaging/StructMapAttachments.hxx>
#include <asi/connectivity/al/messaging/StructMapEnvelopeVcard.hxx>
#include <asi/connectivity/al/messaging/StructMapHeaderEntry.hxx>
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
    \brief The messaging::MapServicesNG interface on the client side.
    \details
            A proxy implements this interface.
    **/
    class MapServicesNGC
    {
    public:
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
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool getFolders(
            const int32_t accoundId,
            const CIPtr< CIString >& folder
        ) const IPL_NOEXCEPT = 0;

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
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool getMessageCount(
            const int32_t accountId,
            const CIPtr< CIString >& folder,
            const bool unread_only
        ) const IPL_NOEXCEPT = 0;

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
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool getMessageHeaders(
            const int32_t accountId,
            const CIPtr< CIString >& folder,
            const int32_t offset,
            const int32_t count
        ) const IPL_NOEXCEPT = 0;

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
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool pushMessage(
            const int32_t accountId,
            const CIPtr< CIString >& folder,
            const asi::connectivity::al::messaging::MapMessageType type,
            const CIPtr< CIPtrArray< asi::connectivity::al::messaging::MapEnvelopeVcard > >& recipients,
            const CIPtr< CIString >& path_to_message,
            const CIPtr< CIString >& messageId,
            const bool withAttachments,
            const asi::connectivity::al::messaging::MapModifyText modifyText
        ) const IPL_NOEXCEPT = 0;

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
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool pushMessageEx(
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
        ) const IPL_NOEXCEPT = 0;

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
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool setMessageReadStatus(
            const int32_t accountId,
            const CIPtr< CIString >& folder,
            const CIPtr< CIString >& messageId,
            const bool read
        ) const IPL_NOEXCEPT = 0;

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
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool updateInbox(
            const int32_t accountId
        ) const IPL_NOEXCEPT = 0;

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
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool deleteMessage(
            const int32_t accountId,
            const CIPtr< CIString >& folder,
            const CIPtr< CIString >& messageId
        ) const IPL_NOEXCEPT = 0;

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
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool messageContent(
            const int32_t accountId,
            const CIPtr< CIString >& messageId,
            const CIPtr< CIString >& folderPath,
            const bool with_attachments
        ) const IPL_NOEXCEPT = 0;

        MapServicesNGC()  {}
        virtual ~MapServicesNGC() {}
    protected:
        friend class MapServicesNGProxy;
    };

}//namespace asi
}//namespace connectivity
}//namespace al
}//namespace messaging
#endif// ASI_CONNECTIVITY_AL_MESSAGING_MAPSERVICESNGC_HXX
