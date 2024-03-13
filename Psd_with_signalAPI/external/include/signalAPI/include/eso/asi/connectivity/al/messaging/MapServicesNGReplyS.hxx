/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceReplyS_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_MESSAGING_MAPSERVICESNG_REPLYS_HXX
#define ASI_CONNECTIVITY_AL_MESSAGING_MAPSERVICESNG_REPLYS_HXX
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
    \brief  Interface declaration, which is implemented by the proxy, and used/called by any user of this interface
    **/
    class MapServicesNGReplyS
    {
    public:
        // List of reply methods
            /**
            *
       * @param addr BT address of active device (-1 if none connected)
       * @param accounts List of accounts
       
            updActiveDevice Method ID: 21
            **/
        virtual bool updActiveDevice (
            const int64_t addr,
            const CIPtr< CIPtrArray< asi::connectivity::al::messaging::MapAccount > >& accounts
        ) IPL_NOEXCEPT = 0;

            /**
            *
       * Response to get a folder.
       *
       * @param accountId Account Identifier.
       * @param folder path of parent folder
       * @param subFolder name of subfolder in folder
       * @param unreadCount Number of unread messages in subfolder
       * @param total_messages Total number of messages in subfolder
       
            getFolders Method ID: 2
            **/
        virtual bool getFolders (
            const int32_t accountId,
            const CIPtr< CIString >& folder,
            const CIPtr< CIString >& subFolder,
            const int32_t total_messages,
            const int32_t unread_messages
        ) IPL_NOEXCEPT = 0;

            /**
            *
       * Response of the getMessageCount request
       *
       * @param accountId Account Identifier.
       * @param folder Path of folder
       * @param msgCount Count of messages.
       
            getMessageCount Method ID: 4
            **/
        virtual bool getMessageCount (
            const int32_t accountId,
            const CIPtr< CIString >& folder,
            const uint32_t msgCount
        ) IPL_NOEXCEPT = 0;

            /**
            getMessageHeaders Method ID: 5
            **/
        virtual bool getMessageHeaders (
            const int32_t accountId,
            const CIPtr< CIString >& folder,
            const int32_t offset,
            const CIPtr< CIPtrArray< asi::connectivity::al::messaging::MapHeaderEntry > >& entry
        ) IPL_NOEXCEPT = 0;

            /**
            pushMessage Method ID: 17
            **/
        virtual bool pushMessage (
            const int32_t accountId,
            const CIPtr< CIString >& messageId
        ) IPL_NOEXCEPT = 0;

            /**
            messageContentHeaders Method ID: 8
            **/
        virtual bool messageContentHeaders (
            const int32_t accountId,
            const CIPtr< CIString >& messageId,
            const asi::connectivity::al::messaging::MapMessageType type,
            const CIPtr< CIString >& folder,
            const CIPtr< asi::connectivity::al::messaging::MapEnvelopeVcard >& sender,
            const CIPtr< CIPtrArray< asi::connectivity::al::messaging::MapEnvelopeVcard > >& final_recipients,
            const bool isRead,
            const int32_t partno,
            const CIPtr< CIString >& char_set
        ) IPL_NOEXCEPT = 0;

            /**
            messageContentPart Method ID: 9
            **/
        virtual bool messageContentPart (
            const int32_t accountId,
            const CIPtr< CIString >& messageId,
            const CIPtr< CIString >& local_path,
            const CIPtr< CIString >& content_type,
            const int32_t original_length,
            const bool truncated,
            const int32_t multipart_nesting_level
        ) IPL_NOEXCEPT = 0;

            /**
            =======================================================================*\
       * MAP notifications
      \*=======================================================================
            onNewMessage Method ID: 16
            **/
        virtual bool onNewMessage (
            const int32_t accountId,
            const CIPtr< CIString >& folder,
            const CIPtr< CIString >& messageId,
            const asi::connectivity::al::messaging::MapMessageType msg_type
        ) IPL_NOEXCEPT = 0;

            /**
            onMessageDeleted Method ID: 12
            **/
        virtual bool onMessageDeleted (
            const int32_t accountId,
            const CIPtr< CIString >& folder,
            const CIPtr< CIString >& messageId
        ) IPL_NOEXCEPT = 0;

            /**
            onMessageSentStatusChanged Method ID: 15
            **/
        virtual bool onMessageSentStatusChanged (
            const int32_t accountId,
            const CIPtr< CIString >& messageId,
            const asi::connectivity::al::messaging::MapSentStatus status
        ) IPL_NOEXCEPT = 0;

            /**
            onMessageReadStatusChanged Method ID: 14
            **/
        virtual bool onMessageReadStatusChanged (
            const int32_t accountId,
            const CIPtr< CIString >& messageId,
            const CIPtr< CIString >& folder
        ) IPL_NOEXCEPT = 0;

            /**
            onMessageMoved Method ID: 13
            **/
        virtual bool onMessageMoved (
            const int32_t accountId,
            const CIPtr< CIString >& messageId,
            const CIPtr< CIString >& old_folder,
            const CIPtr< CIString >& new_folder
        ) IPL_NOEXCEPT = 0;

            /**
            onMemoryStatusChanged Method ID: 11
            **/
        virtual bool onMemoryStatusChanged (
            const int32_t accountId,
            const bool memory_full
        ) IPL_NOEXCEPT = 0;

            /**
            *
       * Called to terminate any MAP request.
       * @param errorCode Error Code.
       
            onMapJobTerminated Method ID: 10
            **/
        virtual bool onMapJobTerminated (
            const int32_t accountId,
            const uint32_t errorCode
        ) IPL_NOEXCEPT = 0;

        virtual ~MapServicesNGReplyS() {}
    };

}// namespace asi
}// namespace connectivity
}// namespace al
}// namespace messaging


#endif// ASI_CONNECTIVITY_AL_MESSAGING_MAPSERVICESNG_REPLYS_HXX
