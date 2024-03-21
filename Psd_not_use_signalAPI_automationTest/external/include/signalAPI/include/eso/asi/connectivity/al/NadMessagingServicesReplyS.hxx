/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceReplyS_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_NADMESSAGINGSERVICES_REPLYS_HXX
#define ASI_CONNECTIVITY_AL_NADMESSAGINGSERVICES_REPLYS_HXX
#include <ipl_config.h>
#include <comm/commidltypes.hxx>
#include <asi/connectivity/al/StructTimestamp.hxx>
#include <asi/connectivity/al/Definitions.hxx>
namespace asi
{
namespace connectivity
{
namespace al
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
        virtual bool onMessage (
            const asi::connectivity::al::SmsType type,
            const uint32_t pduSize,
            const CIPtr< CIString >& pdu
        ) IPL_NOEXCEPT = 0;

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
        virtual bool onCBSMessage (
            const asi::connectivity::al::SmsCbmReportType msgType,
            const int32_t msgId,
            const int32_t serialNumber,
            const int32_t warningType,
            const int32_t dataCoding,
            const CIPtr< asi::connectivity::al::Timestamp >& time,
            const CIPtr< CIString >& content
        ) IPL_NOEXCEPT = 0;

            /**
            sendMessageResponse Method ID: 3
            **/
        virtual bool sendMessageResponse (
            const uint32_t msgId,
            const asi::connectivity::al::ResultType result
        ) IPL_NOEXCEPT = 0;

        virtual ~NadMessagingServicesReplyS() {}
    };

}// namespace asi
}// namespace connectivity
}// namespace al


#endif// ASI_CONNECTIVITY_AL_NADMESSAGINGSERVICES_REPLYS_HXX
