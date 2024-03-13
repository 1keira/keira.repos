/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceReply_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_NADMESSAGINGSERVICESREPLY_HXX
#define ASI_CONNECTIVITY_AL_NADMESSAGINGSERVICESREPLY_HXX

#include <comm/commtypes.hxx>
#include <comm/commidltypes.hxx>
#include <comm/CallEvent.hxx>
#include <asi/connectivity/al/StructTimestamp.hxx>
#include <asi/connectivity/al/Definitions.hxx>

namespace asi
{
namespace connectivity
{
namespace al
{

    /**
    \brief  Declaration of the reply interface, which must be implemented by any user of this interface
    **/
    class NadMessagingServicesReply {

    public:
    // List of reply methods
            /**
            *
        * Message Indication (if a new message received.)
        *
        * @param type
        * NAD_SMS_REPORT_UNKNOWN = -1, // -1: this is internal default value
        * NAD_SMS_NORMAL_NEW_MSG = 0,  // 0: normal new SMS
        * NAD_SMS_STATUS_REPORT = 1,  // 1: SMS center receives SMS
        * NAD_SMS_SUBMIT_REPORT = 2,  // 2: SMS center does not receive SMS
        * @param pduSize Length of the recieved pdu.
        * @param pdu Pdu of the received message.
        
            onMessage Method ID: 1
            **/
        virtual void onMessage(
            const asi::connectivity::al::SmsType type,
            const uint32_t pduSize,
            const CIPtr< CIString >& pdu
        ) = 0;
            /**
            *
         * Cell Broadcast Message Indication
         *
         * @param msgType : SMS_CBS_CMAS_MSG  (0: Commercial Mobile Alert System) or SMS_CBS_ETWS_MSG  (1: Earthquake and Tsunami Warning System)
         * @param serialNumber : This parameter identifies a particular CBS message from the source and type indicated by the Message Identifier and
         *                       is altered every time the CBS message with a given Message Identifier is changed.
         *                       Content: a 2-bit Geographical Scope (GS) indicator, a 10-bit Message Code and a 4-bit Update Number.
         * @param msgId : This parameter identifies the source and type of the CBS message.
         *                For example, "Automotive Association" (= source), "Traffic Reports" (= type) could correspond to one value.
         *                A number of CBS messages may originate from the same source and/or be of the same type.
         *                These will be distinguished by the Serial Number. The Message Identifier is coded in binary.
         *                Range of Ids: 4370 – 4379, 4383 – 4392 (optional language)
         * @param warningType :  The warning type value field indicates the following 5 warning types as its values:
         *                       earthquake, tsunami, earthquake and tsunami, test, and other
         *                       Also, other warning types can be defined in the future if it is required.
         * @param dataCoding : Member 'data_coding' indicates cell broadcast service message data coding scheme.
         * @param content : This parameter contains the content of the warning message -it has a maximum length of 1024 bytes

         
            onCBSMessage Method ID: 0
            **/
        virtual void onCBSMessage(
            const asi::connectivity::al::SmsCbmReportType msgType,
            const int32_t msgId,
            const int32_t serialNumber,
            const int32_t warningType,
            const int32_t dataCoding,
            const CIPtr< asi::connectivity::al::Timestamp >& time,
            const CIPtr< CIString >& content
        ) = 0;
            /**
            sendMessageResponse Method ID: 3
            **/
        virtual void sendMessageResponse(
            const uint32_t msgId,
            const asi::connectivity::al::ResultType result
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
        onMessageCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NadMessagingServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 1;
            ce.assign(inst, mid);
        }

        void
        onCBSMessageCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NadMessagingServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 0;
            ce.assign(inst, mid);
        }

        void
        sendMessageResponseCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NadMessagingServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 3;
            ce.assign(inst, mid);
        }


        virtual ~NadMessagingServicesReply() {}
    };

}//namespace asi
}//namespace connectivity
}//namespace al

#endif// ASI_CONNECTIVITY_AL_NADMESSAGINGSERVICESREPLY_HXX
