/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template ModuleDefinitions_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_MESSAGING_DEFINITIONS_HXX
#define ASI_CONNECTIVITY_AL_MESSAGING_DEFINITIONS_HXX

#include <ipl_config.h>
#include <common/types/string.hxx>
#include <common/UUID.hxx>
#include <tracing/tracing.hxx>
#include <util/UnicodeString.hxx>
#include <comm/commidltypes.hxx>
#include <util/serializer/IStructuredSerializer.hxx>
#include <util/serializer/IStructuredPullDeserializer.hxx>
#include <util/serializer/SerializerErrors.hxx>
#ifdef IPL_OS_WIN32
#undef ERROR_SUCCESS
#undef ERROR_NOT_SUPPORTED
#undef ERROR_INVALID_PARAMETER
#undef ERROR_CONNECTION_REFUSED
#undef SHUTDOWN_RESTART
#endif

namespace asi { namespace connectivity { namespace al { namespace messaging { 
    // asi::connectivity::al::messaging
    enum MessagingErrorCode {

        /*
        * SUCCEEDED.
        */
        ERROR_SUCCESS = 0,
        /*
        * The action needs another parameters.
        */
        ERROR_OTHER_PARAM = 101,
        /*
        * One or several parameters are wrong.
        */
        ERROR_WRONG_PARAMETER = 102,
        /*
        * The request is invalid because Letter of device is not expected.
        */
        ERROR_INVALID_DEVICE = 111,
        /*
        * No action associated,
        */
        ERROR_NO_ACTION_ASSOCIATED = 702,
        /*
        * Miscellaneous error
        */
        ERROR_MISCELLANEOUS = 806
    };
    /**
        *
    * Describes the message priority.
    
    */
    // asi::connectivity::al::messaging
    enum MapMessagePriority {

        /*
        * Normal priority.
        */
        MSG_PRIORITY_NORMAL = 0,
        /*
        * High priority.
        */
        MSG_PRIORITY_HIGH = 1,
        /*
        * Low priority.
        */
        MSG_PRIORITY_LOW = 2
    };
    /**
        *
    * Describes the message text type.
    
    */
    // asi::connectivity::al::messaging
    enum MapMessageType {

        /*
        * EMail
        */
        MSG_TYPE_EMAIL = 0,
        /*
        * SMS GSM
        */
        MSG_TYPE_SMS_GSM = 1,
        /*
        * SMS CDMA
        */
        MSG_TYPE_SMS_CDMA = 2,
        /*
        * MMS
        */
        MSG_TYPE_MMS = 3,
        /*
        * Unknown message type
        */
        MSG_TYPE_INVALID = 255
    };
    /**
        *
    * Describes, what a account provides.
    
    */
    // asi::connectivity::al::messaging
    enum MapAccountFeature {

        /*
        * The account doesn't support a provided feature.
        */
        ACCOUNT_FEATURE_NOTHING = 0,
        /*
        * The account supports email.
        */
        ACCOUNT_FEATURE_EMAIL = 1,
        /*
        * The account supports gsm messages.
        */
        ACCOUNT_FEATURE_SMS_GSM = 2,
        /*
        * The account supports cdma messages.
        */
        ACCOUNT_FEATURE_SMS_CDMA = 4,
        /*
        * The account supports multi media messages.
        */
        ACCOUNT_FEATURE_MMS = 8
    };
    // asi::connectivity::al::messaging
    enum MapModifyText {

        MODIFY_TEXT_REPLACE = 0,
        MODIFY_TEXT_PREPEND = 1
    };
    // asi::connectivity::al::messaging
    enum MapSentStatus {

        MAP_SENT_STATUS_NETWORK = 0,
        MAP_SENT_STATUS_NETWORK_FAILED = 1,
        MAP_SENT_STATUS_DELIVERED = 2,
        MAP_SENT_STATUS_DELIVERY_FAILED = 3
    };
    // asi::connectivity::al::messaging
    enum NumberingScheme {

        /*
        * National numbering scheme.
        */
        NS_NATIONAL = 129,
        /*
        * International numbering scheme (contains the character +).
        */
        NS_INTERNATIONAL = 145
    };
    // asi::connectivity::al::messaging
    enum SmsStorage {

        /*
        * ME storage.
        */
        SS_ME_Storage = 0,
        /*
        * SIM storage.
        */
        SS_SIM_Storage = 1,
        /*
        * SR storage.
        */
        SS_SR_Storage = 2
    };
    /**
        *
    * Status of a nad message.
    
    */
    // asi::connectivity::al::messaging
    enum NadMessageStatus {

        /*
        * New/Unread text sms.
        */
        NadStatusNew = 0,
        /*
        * (Read) Text sms.
        */
        NadStatusRead = 1,
        /*
        * Stored text sms, not yet sent.
        */
        NadStatusStoredNotSent = 2,
        /*
        * Stored text sms, already sent.
        */
        NadStatusStoredSent = 3,
        /*
        * All sms's.
        */
        NadStatusAll = 4,
        /*
        * New/Unread delivery confirm sms.
        */
        NadStatusNewDeliveryConfirm = 5,
        /*
        * Delivery confirm sms, already readed.
        */
        NadStatusDeliveryConfirm = 6,
        /*
        * New/Unread binary sms.
        */
        NadStatusNewBinary = 7,
        /*
        * Binary sms, already readed.
        */
        NadStatusBinary = 8,
        /*
        * Binary sms, stored but not yet sent.
        */
        NadStatusBinaryStoredNotSent = 9,
        /*
        * Binary sms, stored already sent.
        */
        NadStatusBinaryStoredSent = 10
    };
    /**
        *
    * Multiple message deletion flag.
    
    */
    // asi::connectivity::al::messaging
    enum NadDeleteFlag {

        DeleteSpecifiedMessage = 0
    };
    // asi::connectivity::al::messaging
    enum SendWriteAction {

        /*
        * Clean up the send/write buffer.
        */
        SW_ACTION_CLEAR = 0,
        /*
        * Concatenate message text.
        */
        SW_ACTION_CONCATENATE = 1,
        /*
        * Send message.
        */
        SW_ACTION_SEND = 2,
        /*
        * Write message.
        */
        SW_ACTION_WRITE = 3
    };
    // asi::connectivity::al::messaging
    enum SimType {

        /*
        Unknown SIM type
        */
        ST_UNKNOWN = 0,
        /*
        Local/SAP costumer SIM available
        */
        ST_CUSTOMER = 1,
        /*
        Only embedded SIM available
        */
        ST_EMBEDDED = 2
    };
    // asi::connectivity::al::messaging
    enum SimMode {

        /*
        unknown SIM operational mode
        */
        SM_UNKNOWN = -1,
        /*
        Current SIM is used for voice, sms and data services
        */
        SM_VOICE_AND_DATA = 0,
        /*
        Current SIM is used only for data services (will also be sent for eSIM, in which case sms functionality is limited)
        */
        SM_DATA_ONLY = 1
    };
    // asi::connectivity::al::messaging
    enum SimReady {

        /*
        sent when the sim becomes unavailable or when a sim that is locked is available
        */
        SIM_NOT_FUNCTIONAL = -1,
        /*
        sent when the available sim has been unlocked and is ready for use
        */
        SIM_FUNCTIONAL = 0
    };

// Module Version
#define ASI_CONNECTIVITY_AL_MESSAGING_VERSION ipl::string("2.0.1")
#define ASI_CONNECTIVITY_AL_MESSAGING_VERSION_MAJOR 2
#define ASI_CONNECTIVITY_AL_MESSAGING_VERSION_MINOR 0
#define ASI_CONNECTIVITY_AL_MESSAGING_VERSION_PATCHLEVEL 1

// Module without version
#define ASI_CONNECTIVITY_AL_MESSAGING_VERSION_FREE_NAMESPACE ipl::string("asi.connectivity.al.messaging")

// Interface Version
#define ASI_CONNECTIVITY_AL_MESSAGING_MAPSERVICESNG_VERSION_MAJOR 1
#define ASI_CONNECTIVITY_AL_MESSAGING_MAPSERVICESNG_VERSION_MINOR 0
#define ASI_CONNECTIVITY_AL_MESSAGING_MAPSERVICESNG_VERSION_PATCHLEVEL 2
#define ASI_CONNECTIVITY_AL_MESSAGING_MAPSETUP_VERSION_MAJOR 1
#define ASI_CONNECTIVITY_AL_MESSAGING_MAPSETUP_VERSION_MINOR 1
#define ASI_CONNECTIVITY_AL_MESSAGING_MAPSETUP_VERSION_PATCHLEVEL 0
#define ASI_CONNECTIVITY_AL_MESSAGING_NADMESSAGINGSERVICES_VERSION_MAJOR 1
#define ASI_CONNECTIVITY_AL_MESSAGING_NADMESSAGINGSERVICES_VERSION_MINOR 0
#define ASI_CONNECTIVITY_AL_MESSAGING_NADMESSAGINGSERVICES_VERSION_PATCHLEVEL 0

// Interface UUID as string
// NOTE: Using this UUID representation needs more performance, use the binary representation
#define STRING_UUID_ASI_CONNECTIVITY_AL_MESSAGING_MAPSERVICESNG_REQUEST ipl::string("7d12eb42-d72d-4c8b-a720-05c31eed7641")
// Interface UUID as binary
#define BINARY_UUID_ASI_CONNECTIVITY_AL_MESSAGING_MAPSERVICESNG_REQUEST ipl::UUID(0x7d12eb42, 0xd72d, 0x4c8b, 0xa720, 0x05, 0xc3, 0x1e, 0xed, 0x76, 0x41)
// semver encoded as a UUID (non standard version 6)
#define BINARY_IFC_KEY_ASI_CONNECTIVITY_AL_MESSAGING_MAPSERVICESNG_REQUEST comm::InterfaceKey(0x00020000, 0x0001, 0x6000, 0x0000, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02)
#define STRING_IFC_KEY_ASI_CONNECTIVITY_AL_MESSAGING_MAPSERVICESNG_REQUEST ipl::string("00020000-0001-6000-0000-000100000002")

// Interface UUID as string
// NOTE: Using this UUID representation needs more performance, use the binary representation
#define STRING_UUID_ASI_CONNECTIVITY_AL_MESSAGING_MAPSERVICESNG_REPLY ipl::string("675e86c9-f93e-42d9-bac5-8503f3f08d11")
// Interface UUID as binary
#define BINARY_UUID_ASI_CONNECTIVITY_AL_MESSAGING_MAPSERVICESNG_REPLY ipl::UUID(0x675e86c9, 0xf93e, 0x42d9, 0xbac5, 0x85, 0x03, 0xf3, 0xf0, 0x8d, 0x11)
// semver encoded as a UUID (non standard version 6)
#define BINARY_IFC_KEY_ASI_CONNECTIVITY_AL_MESSAGING_MAPSERVICESNG_REPLY comm::InterfaceKey(0x00020000, 0x0001, 0x6000, 0x0000, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02)
#define STRING_IFC_KEY_ASI_CONNECTIVITY_AL_MESSAGING_MAPSERVICESNG_REPLY ipl::string("00020000-0001-6000-0000-000100000002")

// Interface UUID as string
// NOTE: Using this UUID representation needs more performance, use the binary representation
#define STRING_UUID_ASI_CONNECTIVITY_AL_MESSAGING_MAPSETUP_REQUEST ipl::string("9de75f72-b34c-4b6c-88b0-d1f8ce76c8c0")
// Interface UUID as binary
#define BINARY_UUID_ASI_CONNECTIVITY_AL_MESSAGING_MAPSETUP_REQUEST ipl::UUID(0x9de75f72, 0xb34c, 0x4b6c, 0x88b0, 0xd1, 0xf8, 0xce, 0x76, 0xc8, 0xc0)
// semver encoded as a UUID (non standard version 6)
#define BINARY_IFC_KEY_ASI_CONNECTIVITY_AL_MESSAGING_MAPSETUP_REQUEST comm::InterfaceKey(0x00020000, 0x0001, 0x6000, 0x0000, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00)
#define STRING_IFC_KEY_ASI_CONNECTIVITY_AL_MESSAGING_MAPSETUP_REQUEST ipl::string("00020000-0001-6000-0000-000100010000")


// Interface UUID as string
// NOTE: Using this UUID representation needs more performance, use the binary representation
#define STRING_UUID_ASI_CONNECTIVITY_AL_MESSAGING_NADMESSAGINGSERVICES_REQUEST ipl::string("117fdea4-1e03-45f3-9c7b-c95f82aa6e57")
// Interface UUID as binary
#define BINARY_UUID_ASI_CONNECTIVITY_AL_MESSAGING_NADMESSAGINGSERVICES_REQUEST ipl::UUID(0x117fdea4, 0x1e03, 0x45f3, 0x9c7b, 0xc9, 0x5f, 0x82, 0xaa, 0x6e, 0x57)
// semver encoded as a UUID (non standard version 6)
#define BINARY_IFC_KEY_ASI_CONNECTIVITY_AL_MESSAGING_NADMESSAGINGSERVICES_REQUEST comm::InterfaceKey(0x00020000, 0x0001, 0x6000, 0x0000, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00)
#define STRING_IFC_KEY_ASI_CONNECTIVITY_AL_MESSAGING_NADMESSAGINGSERVICES_REQUEST ipl::string("00020000-0001-6000-0000-000100000000")

// Interface UUID as string
// NOTE: Using this UUID representation needs more performance, use the binary representation
#define STRING_UUID_ASI_CONNECTIVITY_AL_MESSAGING_NADMESSAGINGSERVICES_REPLY ipl::string("2273d73d-db18-4d07-95e0-2ef7133bca0d")
// Interface UUID as binary
#define BINARY_UUID_ASI_CONNECTIVITY_AL_MESSAGING_NADMESSAGINGSERVICES_REPLY ipl::UUID(0x2273d73d, 0xdb18, 0x4d07, 0x95e0, 0x2e, 0xf7, 0x13, 0x3b, 0xca, 0x0d)
// semver encoded as a UUID (non standard version 6)
#define BINARY_IFC_KEY_ASI_CONNECTIVITY_AL_MESSAGING_NADMESSAGINGSERVICES_REPLY comm::InterfaceKey(0x00020000, 0x0001, 0x6000, 0x0000, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00)
#define STRING_IFC_KEY_ASI_CONNECTIVITY_AL_MESSAGING_NADMESSAGINGSERVICES_REPLY ipl::string("00020000-0001-6000-0000-000100000000")

} } } }  // end of module namespace(s)

// Serialization and Deserialization of all enums
namespace util { namespace serializer {
            inline bool serialize(IStructuredSerializer& s, const asi::connectivity::al::messaging::MessagingErrorCode  e)
            {
                int32_t value = int32_t(e);

                switch (value)
                {
                    case 0:
                    case 101:
                    case 102:
                    case 111:
                    case 702:
                    case 806:
                        break;
                    default:
                        // illegal value
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "MessagingErrorCode");
                        return true;
                }
                return s.putEnum(value, 32);
            }

            inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::al::messaging::MessagingErrorCode & e)
            {
                int32_t value;
                bool error = s.getEnum(value, 32, false /*unsigned */);
                if (!error) {
                    switch (value)
                    {
                        case 0:
                        case 101:
                        case 102:
                        case 111:
                        case 702:
                        case 806:
                            break;
                        default:
                            ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "MessagingErrorCode");
                            return true;
                    }
                    e = (asi::connectivity::al::messaging::MessagingErrorCode) value;
                }
                return error;
            }
            inline bool serialize(IStructuredSerializer& s, const asi::connectivity::al::messaging::MapMessagePriority  e)
            {
                int32_t value = int32_t(e);

                if ((value < 0) ||
                    (value > 2))
                {
                    // illegal value
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "MapMessagePriority");
                    return true;
                }
                return s.putEnum(value, 32);
            }

            inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::al::messaging::MapMessagePriority & e)
            {
                int32_t value;
                bool error = s.getEnum(value, 32, false /*unsigned */);
                if (!error) {
                    if ((value < 0) ||
                        (value > 2))
                    {
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "MapMessagePriority");
                        return true;
                    }
                    e = (asi::connectivity::al::messaging::MapMessagePriority) value;
                }
                return error;
            }
            inline bool serialize(IStructuredSerializer& s, const asi::connectivity::al::messaging::MapMessageType  e)
            {
                int32_t value = int32_t(e);

                switch (value)
                {
                    case 0:
                    case 1:
                    case 2:
                    case 3:
                    case 255:
                        break;
                    default:
                        // illegal value
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "MapMessageType");
                        return true;
                }
                return s.putEnum(value, 32);
            }

            inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::al::messaging::MapMessageType & e)
            {
                int32_t value;
                bool error = s.getEnum(value, 32, false /*unsigned */);
                if (!error) {
                    switch (value)
                    {
                        case 0:
                        case 1:
                        case 2:
                        case 3:
                        case 255:
                            break;
                        default:
                            ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "MapMessageType");
                            return true;
                    }
                    e = (asi::connectivity::al::messaging::MapMessageType) value;
                }
                return error;
            }
            inline bool serialize(IStructuredSerializer& s, const asi::connectivity::al::messaging::MapAccountFeature  e)
            {
                int32_t value = int32_t(e);

                switch (value)
                {
                    case 0:
                    case 1:
                    case 2:
                    case 4:
                    case 8:
                        break;
                    default:
                        // illegal value
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "MapAccountFeature");
                        return true;
                }
                return s.putEnum(value, 32);
            }

            inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::al::messaging::MapAccountFeature & e)
            {
                int32_t value;
                bool error = s.getEnum(value, 32, false /*unsigned */);
                if (!error) {
                    switch (value)
                    {
                        case 0:
                        case 1:
                        case 2:
                        case 4:
                        case 8:
                            break;
                        default:
                            ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "MapAccountFeature");
                            return true;
                    }
                    e = (asi::connectivity::al::messaging::MapAccountFeature) value;
                }
                return error;
            }
            inline bool serialize(IStructuredSerializer& s, const asi::connectivity::al::messaging::MapModifyText  e)
            {
                int32_t value = int32_t(e);

                if ((value < 0) ||
                    (value > 1))
                {
                    // illegal value
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "MapModifyText");
                    return true;
                }
                return s.putEnum(value, 32);
            }

            inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::al::messaging::MapModifyText & e)
            {
                int32_t value;
                bool error = s.getEnum(value, 32, false /*unsigned */);
                if (!error) {
                    if ((value < 0) ||
                        (value > 1))
                    {
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "MapModifyText");
                        return true;
                    }
                    e = (asi::connectivity::al::messaging::MapModifyText) value;
                }
                return error;
            }
            inline bool serialize(IStructuredSerializer& s, const asi::connectivity::al::messaging::MapSentStatus  e)
            {
                int32_t value = int32_t(e);

                if ((value < 0) ||
                    (value > 3))
                {
                    // illegal value
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "MapSentStatus");
                    return true;
                }
                return s.putEnum(value, 32);
            }

            inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::al::messaging::MapSentStatus & e)
            {
                int32_t value;
                bool error = s.getEnum(value, 32, false /*unsigned */);
                if (!error) {
                    if ((value < 0) ||
                        (value > 3))
                    {
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "MapSentStatus");
                        return true;
                    }
                    e = (asi::connectivity::al::messaging::MapSentStatus) value;
                }
                return error;
            }
            inline bool serialize(IStructuredSerializer& s, const asi::connectivity::al::messaging::NumberingScheme  e)
            {
                int32_t value = int32_t(e);

                switch (value)
                {
                    case 129:
                    case 145:
                        break;
                    default:
                        // illegal value
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "NumberingScheme");
                        return true;
                }
                return s.putEnum(value, 32);
            }

            inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::al::messaging::NumberingScheme & e)
            {
                int32_t value;
                bool error = s.getEnum(value, 32, false /*unsigned */);
                if (!error) {
                    switch (value)
                    {
                        case 129:
                        case 145:
                            break;
                        default:
                            ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "NumberingScheme");
                            return true;
                    }
                    e = (asi::connectivity::al::messaging::NumberingScheme) value;
                }
                return error;
            }
            inline bool serialize(IStructuredSerializer& s, const asi::connectivity::al::messaging::SmsStorage  e)
            {
                int32_t value = int32_t(e);

                if ((value < 0) ||
                    (value > 2))
                {
                    // illegal value
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "SmsStorage");
                    return true;
                }
                return s.putEnum(value, 32);
            }

            inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::al::messaging::SmsStorage & e)
            {
                int32_t value;
                bool error = s.getEnum(value, 32, false /*unsigned */);
                if (!error) {
                    if ((value < 0) ||
                        (value > 2))
                    {
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "SmsStorage");
                        return true;
                    }
                    e = (asi::connectivity::al::messaging::SmsStorage) value;
                }
                return error;
            }
            inline bool serialize(IStructuredSerializer& s, const asi::connectivity::al::messaging::NadMessageStatus  e)
            {
                int32_t value = int32_t(e);

                if ((value < 0) ||
                    (value > 10))
                {
                    // illegal value
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "NadMessageStatus");
                    return true;
                }
                return s.putEnum(value, 32);
            }

            inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::al::messaging::NadMessageStatus & e)
            {
                int32_t value;
                bool error = s.getEnum(value, 32, false /*unsigned */);
                if (!error) {
                    if ((value < 0) ||
                        (value > 10))
                    {
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "NadMessageStatus");
                        return true;
                    }
                    e = (asi::connectivity::al::messaging::NadMessageStatus) value;
                }
                return error;
            }
            inline bool serialize(IStructuredSerializer& s, const asi::connectivity::al::messaging::NadDeleteFlag  e)
            {
                int32_t value = int32_t(e);

                if ((value < 0) ||
                    (value > 0))
                {
                    // illegal value
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "NadDeleteFlag");
                    return true;
                }
                return s.putEnum(value, 32);
            }

            inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::al::messaging::NadDeleteFlag & e)
            {
                int32_t value;
                bool error = s.getEnum(value, 32, false /*unsigned */);
                if (!error) {
                    if ((value < 0) ||
                        (value > 0))
                    {
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "NadDeleteFlag");
                        return true;
                    }
                    e = (asi::connectivity::al::messaging::NadDeleteFlag) value;
                }
                return error;
            }
            inline bool serialize(IStructuredSerializer& s, const asi::connectivity::al::messaging::SendWriteAction  e)
            {
                int32_t value = int32_t(e);

                if ((value < 0) ||
                    (value > 3))
                {
                    // illegal value
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "SendWriteAction");
                    return true;
                }
                return s.putEnum(value, 32);
            }

            inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::al::messaging::SendWriteAction & e)
            {
                int32_t value;
                bool error = s.getEnum(value, 32, false /*unsigned */);
                if (!error) {
                    if ((value < 0) ||
                        (value > 3))
                    {
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "SendWriteAction");
                        return true;
                    }
                    e = (asi::connectivity::al::messaging::SendWriteAction) value;
                }
                return error;
            }
            inline bool serialize(IStructuredSerializer& s, const asi::connectivity::al::messaging::SimType  e)
            {
                int32_t value = int32_t(e);

                if ((value < 0) ||
                    (value > 2))
                {
                    // illegal value
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "SimType");
                    return true;
                }
                return s.putEnum(value, 32);
            }

            inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::al::messaging::SimType & e)
            {
                int32_t value;
                bool error = s.getEnum(value, 32, false /*unsigned */);
                if (!error) {
                    if ((value < 0) ||
                        (value > 2))
                    {
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "SimType");
                        return true;
                    }
                    e = (asi::connectivity::al::messaging::SimType) value;
                }
                return error;
            }
            inline bool serialize(IStructuredSerializer& s, const asi::connectivity::al::messaging::SimMode  e)
            {
                int32_t value = int32_t(e);

                if ((value < -1) ||
                    (value > 1))
                {
                    // illegal value
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "SimMode");
                    return true;
                }
                return s.putEnum(value, 32);
            }

            inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::al::messaging::SimMode & e)
            {
                int32_t value;
                bool error = s.getEnum(value, 32, true /* signed */);
                if (!error) {
                    if ((value < -1) ||
                        (value > 1))
                    {
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "SimMode");
                        return true;
                    }
                    e = (asi::connectivity::al::messaging::SimMode) value;
                }
                return error;
            }
            inline bool serialize(IStructuredSerializer& s, const asi::connectivity::al::messaging::SimReady  e)
            {
                int32_t value = int32_t(e);

                if ((value < -1) ||
                    (value > 0))
                {
                    // illegal value
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "SimReady");
                    return true;
                }
                return s.putEnum(value, 32);
            }

            inline bool deserialize(IStructuredPullDeserializer& s, asi::connectivity::al::messaging::SimReady & e)
            {
                int32_t value;
                bool error = s.getEnum(value, 32, true /* signed */);
                if (!error) {
                    if ((value < -1) ||
                        (value > 0))
                    {
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "SimReady");
                        return true;
                    }
                    e = (asi::connectivity::al::messaging::SimReady) value;
                }
                return error;
            }
} } // namespace util::serializer

namespace asi
{
namespace connectivity
{
namespace al
{
namespace messaging
{
}// namespace asi
}// namespace connectivity
}// namespace al
}// namespace messaging

#endif  // ASI_CONNECTIVITY_AL_MESSAGING_DEFINITIONS_HXX
