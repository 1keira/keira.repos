/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceReplyS_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_MESSAGING_NADMESSAGINGSERVICES_REPLYS_HXX
#define ASI_CONNECTIVITY_AL_MESSAGING_NADMESSAGINGSERVICES_REPLYS_HXX
#include <ipl_config.h>
#include <comm/commidltypes.hxx>
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
    \brief  Interface declaration, which is implemented by the proxy, and used/called by any user of this interface
    **/
    class NadMessagingServicesReplyS
    {
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
        virtual bool selectSmsStorage (
            const uint32_t deviceId,
            const uint32_t readUsed,
            const uint32_t readTotal,
            const uint32_t writeUsed,
            const uint32_t writeTotal,
            const uint32_t revUsed,
            const uint32_t revTotal
        ) IPL_NOEXCEPT = 0;

            /**
            *
       * Response for the getSMS request.
       * 
       * @param number Number of the service center.
       * @param numberType Type of the sercie center number (inter-/national).
       
            getSMSC Method ID: 3
            **/
        virtual bool getSMSC (
            const uint32_t deviceId,
            const CIPtr< CIString >& number,
            const uint32_t numberType
        ) IPL_NOEXCEPT = 0;

            /**
            *
       * Returns the result of the delete call.
       * 
       * @param deviceId Device Identifier.
       
            deleteMessages Method ID: 1
            **/
        virtual bool deleteMessages (
            const uint32_t deviceId,
            const uint32_t flag,
            const uint32_t index
        ) IPL_NOEXCEPT = 0;

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
        virtual bool listMessages (
            const uint32_t deviceId,
            const uint32_t index,
            const asi::connectivity::al::messaging::NadMessageStatus status,
            const uint32_t pduSize,
            const CIPtr< CIString >& pdu
        ) IPL_NOEXCEPT = 0;

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
        virtual bool readRawMessage (
            const uint32_t deviceId,
            const asi::connectivity::al::messaging::NadMessageStatus status,
            const uint32_t pduSize,
            const CIPtr< CIString >& pdu
        ) IPL_NOEXCEPT = 0;

            /**
            *
       * Returns the result of the send call.
       *
       * @param deviceId Device Identifier.
       * @param refNumber Reference number of the sended message.
       
            sendRawMessage Method ID: 18
            **/
        virtual bool sendRawMessage (
            const uint32_t deviceId,
            const uint32_t refNumber
        ) IPL_NOEXCEPT = 0;

            /**
            *
       * Returns the result of the send call.
       * 
       * @param deviceId Device Identifier.
       * @param index Index of the sended message.
       * @param refNumber Reference number of the sended message.
       
            sendMessageFromStorage Method ID: 17
            **/
        virtual bool sendMessageFromStorage (
            const uint32_t deviceId,
            const uint32_t index,
            const uint32_t refNumber
        ) IPL_NOEXCEPT = 0;

            /**
            *
       * Returns the result of the write call.
       *
       * @param deviceId Device Identifier.
       * @param index Index of the new message.
       
            writeRawMessage Method ID: 23
            **/
        virtual bool writeRawMessage (
            const uint32_t deviceId,
            const uint32_t index
        ) IPL_NOEXCEPT = 0;

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
        virtual bool onMessage (
            const uint32_t deviceId,
            const uint32_t type,
            const uint32_t storage,
            const uint32_t index,
            const uint32_t pduSize,
            const CIPtr< CIString >& pdu
        ) IPL_NOEXCEPT = 0;

            /**
            onSimStatus Method ID: 9
            **/
        virtual bool onSimStatus (
            const uint32_t deviceId,
            const uint32_t simMode,
            const uint32_t simStatus
        ) IPL_NOEXCEPT = 0;

            /**
            onTelModuleEvent Method ID: 11
            **/
        virtual bool onTelModuleEvent (
            const uint32_t deviceId,
            const uint32_t event,
            const uint32_t eventExt,
            const uint32_t info
        ) IPL_NOEXCEPT = 0;

            /**
            *
      * Send this update for any sim related information changes
      *  @param simInfo     (simType : unknown/costumer/embedded, 
      *                      iccid   : should be a valid string if simREady is FUNCTIONAL
      *                      simReady: for an unlocked available sim 
      *                      simMode : will be specifying when sim is in data/voice+data mode
      
            onSimInfo Method ID: 8
            **/
        virtual bool onSimInfo (
            const CIPtr< asi::connectivity::al::messaging::SimInfo >& info
        ) IPL_NOEXCEPT = 0;

            /**
             Sent whenever the sms storage for current sim changes to 'full' 
            onSmsStorage Method ID: 10
            **/
        virtual bool onSmsStorage (
            const bool full
        ) IPL_NOEXCEPT = 0;

            /**
            *
       * Called to terminate any nad request.
       *  
       * @param errorCode Error Code.
       
            onNadJobTerminated Method ID: 7
            **/
        virtual bool onNadJobTerminated (
            const uint32_t errorCode
        ) IPL_NOEXCEPT = 0;

        virtual ~NadMessagingServicesReplyS() {}
    };

}// namespace asi
}// namespace connectivity
}// namespace al
}// namespace messaging


#endif// ASI_CONNECTIVITY_AL_MESSAGING_NADMESSAGINGSERVICES_REPLYS_HXX
