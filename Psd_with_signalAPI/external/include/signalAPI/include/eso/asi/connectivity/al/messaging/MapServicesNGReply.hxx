/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceReply_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_MESSAGING_MAPSERVICESNGREPLY_HXX
#define ASI_CONNECTIVITY_AL_MESSAGING_MAPSERVICESNGREPLY_HXX

#include <comm/commtypes.hxx>
#include <comm/commidltypes.hxx>
#include <comm/CallEvent.hxx>
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
    \brief  Declaration of the reply interface, which must be implemented by any user of this interface
    **/
    class MapServicesNGReply {

    public:
    // List of reply methods
            /**
            *
       * @param addr BT address of active device (-1 if none connected)
       * @param accounts List of accounts
       
            updActiveDevice Method ID: 21
            **/
        virtual void updActiveDevice(
            const int64_t addr,
            const CIPtr< CIPtrArray< asi::connectivity::al::messaging::MapAccount > >& accounts
        ) = 0;
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
        virtual void getFolders(
            const int32_t accountId,
            const CIPtr< CIString >& folder,
            const CIPtr< CIString >& subFolder,
            const int32_t total_messages,
            const int32_t unread_messages
        ) = 0;
            /**
            *
       * Response of the getMessageCount request
       *
       * @param accountId Account Identifier.
       * @param folder Path of folder
       * @param msgCount Count of messages.
       
            getMessageCount Method ID: 4
            **/
        virtual void getMessageCount(
            const int32_t accountId,
            const CIPtr< CIString >& folder,
            const uint32_t msgCount
        ) = 0;
            /**
            getMessageHeaders Method ID: 5
            **/
        virtual void getMessageHeaders(
            const int32_t accountId,
            const CIPtr< CIString >& folder,
            const int32_t offset,
            const CIPtr< CIPtrArray< asi::connectivity::al::messaging::MapHeaderEntry > >& entry
        ) = 0;
            /**
            pushMessage Method ID: 17
            **/
        virtual void pushMessage(
            const int32_t accountId,
            const CIPtr< CIString >& messageId
        ) = 0;
            /**
            messageContentHeaders Method ID: 8
            **/
        virtual void messageContentHeaders(
            const int32_t accountId,
            const CIPtr< CIString >& messageId,
            const asi::connectivity::al::messaging::MapMessageType type,
            const CIPtr< CIString >& folder,
            const CIPtr< asi::connectivity::al::messaging::MapEnvelopeVcard >& sender,
            const CIPtr< CIPtrArray< asi::connectivity::al::messaging::MapEnvelopeVcard > >& final_recipients,
            const bool isRead,
            const int32_t partno,
            const CIPtr< CIString >& char_set
        ) = 0;
            /**
            messageContentPart Method ID: 9
            **/
        virtual void messageContentPart(
            const int32_t accountId,
            const CIPtr< CIString >& messageId,
            const CIPtr< CIString >& local_path,
            const CIPtr< CIString >& content_type,
            const int32_t original_length,
            const bool truncated,
            const int32_t multipart_nesting_level
        ) = 0;
            /**
            =======================================================================*\
       * MAP notifications
      \*=======================================================================
            onNewMessage Method ID: 16
            **/
        virtual void onNewMessage(
            const int32_t accountId,
            const CIPtr< CIString >& folder,
            const CIPtr< CIString >& messageId,
            const asi::connectivity::al::messaging::MapMessageType msg_type
        ) = 0;
            /**
            onMessageDeleted Method ID: 12
            **/
        virtual void onMessageDeleted(
            const int32_t accountId,
            const CIPtr< CIString >& folder,
            const CIPtr< CIString >& messageId
        ) = 0;
            /**
            onMessageSentStatusChanged Method ID: 15
            **/
        virtual void onMessageSentStatusChanged(
            const int32_t accountId,
            const CIPtr< CIString >& messageId,
            const asi::connectivity::al::messaging::MapSentStatus status
        ) = 0;
            /**
            onMessageReadStatusChanged Method ID: 14
            **/
        virtual void onMessageReadStatusChanged(
            const int32_t accountId,
            const CIPtr< CIString >& messageId,
            const CIPtr< CIString >& folder
        ) = 0;
            /**
            onMessageMoved Method ID: 13
            **/
        virtual void onMessageMoved(
            const int32_t accountId,
            const CIPtr< CIString >& messageId,
            const CIPtr< CIString >& old_folder,
            const CIPtr< CIString >& new_folder
        ) = 0;
            /**
            onMemoryStatusChanged Method ID: 11
            **/
        virtual void onMemoryStatusChanged(
            const int32_t accountId,
            const bool memory_full
        ) = 0;
            /**
            *
       * Called to terminate any MAP request.
       * @param errorCode Error Code.
       
            onMapJobTerminated Method ID: 10
            **/
        virtual void onMapJobTerminated(
            const int32_t accountId,
            const uint32_t errorCode
        ) = 0;

        /*!
        \brief Informs the service about a connected client
        \param count The number of connected clients
        */
        virtual void clientConnected(uint32_t count) {}

        /*!
        \brief Informs the service that a client disconnected
        \param count the number of connected clients
        */
        virtual void clientDisconnected(uint32_t count) {}

        // call ids
        void
        updActiveDeviceCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<MapServicesNGReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 21;
            ce.assign(inst, mid);
        }

        void
        getFolders_I32_S_S_I32_I32CallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<MapServicesNGReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 2;
            ce.assign(inst, mid);
        }

        void
        getMessageCount_I32_S_U32CallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<MapServicesNGReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 4;
            ce.assign(inst, mid);
        }

        void
        getMessageHeaders_I32_S_I32_aMapHeaderEntryCallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<MapServicesNGReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 5;
            ce.assign(inst, mid);
        }

        void
        pushMessage_I32_SCallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<MapServicesNGReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 17;
            ce.assign(inst, mid);
        }

        void
        messageContentHeadersCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<MapServicesNGReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 8;
            ce.assign(inst, mid);
        }

        void
        messageContentPartCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<MapServicesNGReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 9;
            ce.assign(inst, mid);
        }

        void
        onNewMessageCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<MapServicesNGReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 16;
            ce.assign(inst, mid);
        }

        void
        onMessageDeletedCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<MapServicesNGReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 12;
            ce.assign(inst, mid);
        }

        void
        onMessageSentStatusChangedCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<MapServicesNGReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 15;
            ce.assign(inst, mid);
        }

        void
        onMessageReadStatusChangedCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<MapServicesNGReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 14;
            ce.assign(inst, mid);
        }

        void
        onMessageMovedCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<MapServicesNGReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 13;
            ce.assign(inst, mid);
        }

        void
        onMemoryStatusChangedCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<MapServicesNGReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 11;
            ce.assign(inst, mid);
        }

        void
        onMapJobTerminatedCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<MapServicesNGReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 10;
            ce.assign(inst, mid);
        }


        virtual ~MapServicesNGReply() {}
    };

}//namespace asi
}//namespace connectivity
}//namespace al
}//namespace messaging

#endif// ASI_CONNECTIVITY_AL_MESSAGING_MAPSERVICESNGREPLY_HXX
