/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceReply_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_MESSAGING_NADMESSAGINGSERVICESREPLY_HXX
#define ASI_CONNECTIVITY_AL_MESSAGING_NADMESSAGINGSERVICESREPLY_HXX

#include <comm/commtypes.hxx>
#include <comm/commidltypes.hxx>
#include <comm/CallEvent.hxx>
#include <asi/connectivity/al/messaging/StructSimInfo.hxx>
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
    class NadMessagingServicesReply {

    public:
    // List of reply methods
            /**
            *
        * Response for selecting the sms storage.
        *
        * @param readUsed Used read memory.
        * @param readTotal Total read memory.
        * @param writeUsed Used write memory.
        * @param writeTotal Total write memory.
        * @param revUsed Used receive memory.
        * @param revTotal Total receive memory.
        
            selectSmsStorage Method ID: 15
            **/
        virtual void selectSmsStorage(
            const uint32_t deviceId,
            const uint32_t readUsed,
            const uint32_t readTotal,
            const uint32_t writeUsed,
            const uint32_t writeTotal,
            const uint32_t revUsed,
            const uint32_t revTotal
        ) = 0;
            /**
            *
       * Response for the getSMS request.
       * 
       * @param number Number of the service center.
       * @param numberType Type of the sercie center number (inter-/national).
       
            getSMSC Method ID: 3
            **/
        virtual void getSMSC(
            const uint32_t deviceId,
            const CIPtr< CIString >& number,
            const uint32_t numberType
        ) = 0;
            /**
            *
       * Returns the result of the delete call.
       * 
       * @param deviceId Device Identifier.
       
            deleteMessages Method ID: 1
            **/
        virtual void deleteMessages(
            const uint32_t deviceId,
            const uint32_t flag,
            const uint32_t index
        ) = 0;
            /**
            *
       * Returns a list entry.
       * 
       * @param deviceId Device Identifier.
       * @param index Index of the message.
       * @param status SMS status (new, read, ...).
       * @param pduSize Length of the pdu in bytes.
       * @param pdu Pdu data.
       
            listMessages Method ID: 5
            **/
        virtual void listMessages(
            const uint32_t deviceId,
            const uint32_t index,
            const asi::connectivity::al::messaging::NadMessageStatus status,
            const uint32_t pduSize,
            const CIPtr< CIString >& pdu
        ) = 0;
            /**
            *
       * Returns the content of the requested message.
       *
       * @param deviceId Device Identifier.
       * @param status Message status (new, read, ...).
       * @param pduSize Length of the pdu in bytes.
       * @param pdu Pdu data.
       
            readRawMessage Method ID: 12
            **/
        virtual void readRawMessage(
            const uint32_t deviceId,
            const asi::connectivity::al::messaging::NadMessageStatus status,
            const uint32_t pduSize,
            const CIPtr< CIString >& pdu
        ) = 0;
            /**
            *
       * Returns the result of the send call.
       *
       * @param deviceId Device Identifier.
       * @param refNumber Reference number of the sended message.
       
            sendRawMessage Method ID: 18
            **/
        virtual void sendRawMessage(
            const uint32_t deviceId,
            const uint32_t refNumber
        ) = 0;
            /**
            *
       * Returns the result of the send call.
       * 
       * @param deviceId Device Identifier.
       * @param index Index of the sended message.
       * @param refNumber Reference number of the sended message.
       
            sendMessageFromStorage Method ID: 17
            **/
        virtual void sendMessageFromStorage(
            const uint32_t deviceId,
            const uint32_t index,
            const uint32_t refNumber
        ) = 0;
            /**
            *
       * Returns the result of the write call.
       *
       * @param deviceId Device Identifier.
       * @param index Index of the new message.
       
            writeRawMessage Method ID: 23
            **/
        virtual void writeRawMessage(
            const uint32_t deviceId,
            const uint32_t index
        ) = 0;
            /**
            *
       * Message Indication (if a new message received.)
       *
       * @param deviceId Device identifier.
       * @param type  0 - Deliver
       *              1 - Cell Broadcast
       *              2 - Status Report
       * @param storage 0 - phone module
       *                1 - sim card
       *                3 - status report
       * @param index Index of the received message.
       * @param pduSize Length of the recieved pdu.
       * @param pdu Pdu of the received message.
       
            onMessage Method ID: 6
            **/
        virtual void onMessage(
            const uint32_t deviceId,
            const uint32_t type,
            const uint32_t storage,
            const uint32_t index,
            const uint32_t pduSize,
            const CIPtr< CIString >& pdu
        ) = 0;
            /**
            onSimStatus Method ID: 9
            **/
        virtual void onSimStatus(
            const uint32_t deviceId,
            const uint32_t simMode,
            const uint32_t simStatus
        ) = 0;
            /**
            onTelModuleEvent Method ID: 11
            **/
        virtual void onTelModuleEvent(
            const uint32_t deviceId,
            const uint32_t event,
            const uint32_t eventExt,
            const uint32_t info
        ) = 0;
            /**
            *
      * Send this update for any sim related information changes
      *  @param simInfo     (simType : unknown/costumer/embedded, 
      *                      iccid   : should be a valid string if simREady is FUNCTIONAL
      *                      simReady: for an unlocked available sim 
      *                      simMode : will be specifying when sim is in data/voice+data mode
      
            onSimInfo Method ID: 8
            **/
        virtual void onSimInfo(
            const CIPtr< asi::connectivity::al::messaging::SimInfo >& info
        ) = 0;
            /**
             Sent whenever the sms storage for current sim changes to 'full' 
            onSmsStorage Method ID: 10
            **/
        virtual void onSmsStorage(
            const bool full
        ) = 0;
            /**
            *
       * Called to terminate any nad request.
       *  
       * @param errorCode Error Code.
       
            onNadJobTerminated Method ID: 7
            **/
        virtual void onNadJobTerminated(
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
        selectSmsStorage_U32_U32_U32_U32_U32_U32_U32CallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<NadMessagingServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 15;
            ce.assign(inst, mid);
        }

        void
        getSMSC_U32_S_U32CallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<NadMessagingServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 3;
            ce.assign(inst, mid);
        }

        void
        deleteMessages_U32_U32_U32CallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<NadMessagingServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 1;
            ce.assign(inst, mid);
        }

        void
        listMessages_U32_U32_NadMessageStatus_U32_SCallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<NadMessagingServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 5;
            ce.assign(inst, mid);
        }

        void
        readRawMessage_U32_NadMessageStatus_U32_SCallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<NadMessagingServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 12;
            ce.assign(inst, mid);
        }

        void
        sendRawMessage_U32_U32CallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<NadMessagingServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 18;
            ce.assign(inst, mid);
        }

        void
        sendMessageFromStorage_U32_U32_U32CallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<NadMessagingServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 17;
            ce.assign(inst, mid);
        }

        void
        writeRawMessage_U32_U32CallID(comm::CallEvent::CallID& ce)
        {
            void* inst=static_cast<NadMessagingServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 23;
            ce.assign(inst, mid);
        }

        void
        onMessageCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NadMessagingServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 6;
            ce.assign(inst, mid);
        }

        void
        onSimStatusCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NadMessagingServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 9;
            ce.assign(inst, mid);
        }

        void
        onTelModuleEventCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NadMessagingServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 11;
            ce.assign(inst, mid);
        }

        void
        onSimInfoCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NadMessagingServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 8;
            ce.assign(inst, mid);
        }

        void
        onSmsStorageCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NadMessagingServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 10;
            ce.assign(inst, mid);
        }

        void
        onNadJobTerminatedCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NadMessagingServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 7;
            ce.assign(inst, mid);
        }


        virtual ~NadMessagingServicesReply() {}
    };

}//namespace asi
}//namespace connectivity
}//namespace al
}//namespace messaging

#endif// ASI_CONNECTIVITY_AL_MESSAGING_NADMESSAGINGSERVICESREPLY_HXX
