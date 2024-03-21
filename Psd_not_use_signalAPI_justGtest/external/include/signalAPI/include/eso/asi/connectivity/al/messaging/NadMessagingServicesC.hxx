/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceC_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_MESSAGING_NADMESSAGINGSERVICESC_HXX
#define ASI_CONNECTIVITY_AL_MESSAGING_NADMESSAGINGSERVICESC_HXX

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
    \brief The messaging::NadMessagingServices interface on the client side.
    \details
            A proxy implements this interface.
    **/
    class NadMessagingServicesC
    {
    public:
        // List of request methods
        /**
            *
        * Selects the sms storage.
        *
        * @param readStorage Read sms memory storage.
        * @param writeStorage Write sms memory storage.
        * @param receiveStorage Received memory storage.
        
            selectSmsStorage Method ID: 14
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool selectSmsStorage(
            const uint32_t deviceId,
            const asi::connectivity::al::messaging::SmsStorage readStorage,
            const asi::connectivity::al::messaging::SmsStorage writeStorage,
            const asi::connectivity::al::messaging::SmsStorage receiveStorage
        ) const IPL_NOEXCEPT = 0;

        /**
            *
       * Request to get the service center.
       * 
       * @param deviceId Device Identifier.
       
            getSMSC Method ID: 2
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool getSMSC(
            const uint32_t deviceId
        ) const IPL_NOEXCEPT = 0;

        /**
            *
       * Request to get the service center.
       *
       * @param deviceId Device Identifier.
       
            setSMSC Method ID: 20
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool setSMSC(
            const uint32_t deviceId,
            const CIPtr< CIString >& number,
            const asi::connectivity::al::messaging::NumberingScheme numberType
        ) const IPL_NOEXCEPT = 0;

        /**
            *
       * Request to Enable/Disable automatic SMS status update after reading a sms.
       * 
       * @param enable true Status will be automatically set to read.
       * 	false The status won't be changed.
       
            setStatusUpdateMode Method ID: 22
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool setStatusUpdateMode(
            const uint32_t deviceId,
            const bool enable
        ) const IPL_NOEXCEPT = 0;

        /**
            *
       * Request to set the sms text mode parameters.
       * 
       * @param deviceId DeviceIdentifier.
       * @param firstOctet FirstOctet (TP-MTI, TP-RD, TP-VDF, TP-SRR, TP-UDHI, TP-RP).
       * @param validityPeriod Validity period.
       * @param dataCodingScheme Data coding scheme.
       
            setSmsModeParameters Method ID: 21
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool setSmsModeParameters(
            const uint32_t deviceId,
            const uint32_t firstOctet,
            const uint32_t validityPeriod,
            const uint32_t dataCodingScheme
        ) const IPL_NOEXCEPT = 0;

        /**
            *
       * Deletes the specified Messages.
       
            deleteMessages Method ID: 0
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool deleteMessages(
            const uint32_t deviceId,
            const asi::connectivity::al::messaging::NadDeleteFlag deleteFlag,
            const uint32_t index
        ) const IPL_NOEXCEPT = 0;

        /**
            *
       * Request to get a list of messages.
       
            listMessages Method ID: 4
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool listMessages(
            const uint32_t deviceId,
            const asi::connectivity::al::messaging::NadMessageStatus status
        ) const IPL_NOEXCEPT = 0;

        /**
            *
       * Requests the pdu of a specified message.
       *
       * @param deviceId Device Identifier.
       * @param index Index of the message. 
       
            readRawMessage Method ID: 13
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool readRawMessage(
            const uint32_t deviceId,
            const uint32_t index
        ) const IPL_NOEXCEPT = 0;

        /**
            *
       * Sends a message in pdu format.
       *
       * @param deviceId Device Identifier.
       * @param pduSize Length of the pdu to send.
       * @param pdu Sms pdu data to be sent.
       
            sendRawMessage Method ID: 19
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool sendRawMessage(
            const uint32_t deviceId,
            const uint32_t pduSize,
            const CIPtr< CIString >& pdu
        ) const IPL_NOEXCEPT = 0;

        /**
            *
       * Sends a specified message from the storage.
       * 
       * @param deviceId Device Identifier.
       * @param index Index of the new message.
       
            sendMessageFromStorage Method ID: 16
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool sendMessageFromStorage(
            const uint32_t deviceId,
            const uint32_t index
        ) const IPL_NOEXCEPT = 0;

        /**
            *
       * Writes a message in pdu format.
       *
       * @param deviceId Device Identifier.
       * @param pduSize Length of the pdu to send.
       * @param pdu Sms pdu data to be sent.
       
            writeRawMessage Method ID: 24
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool writeRawMessage(
            const uint32_t deviceId,
            const uint32_t pduSize,
            const CIPtr< CIString >& pdu
        ) const IPL_NOEXCEPT = 0;

        NadMessagingServicesC()  {}
        virtual ~NadMessagingServicesC() {}
    protected:
        friend class NadMessagingServicesProxy;
    };

}//namespace asi
}//namespace connectivity
}//namespace al
}//namespace messaging
#endif// ASI_CONNECTIVITY_AL_MESSAGING_NADMESSAGINGSERVICESC_HXX
