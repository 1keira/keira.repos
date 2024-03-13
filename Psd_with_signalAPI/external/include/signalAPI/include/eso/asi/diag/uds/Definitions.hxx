/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template ModuleDefinitions_hxx.tmpl
*/
#ifndef ASI_DIAG_UDS_DEFINITIONS_HXX
#define ASI_DIAG_UDS_DEFINITIONS_HXX

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

namespace asi { namespace diag { namespace uds { 
    const uint32_t dfcc_no_dtc = 4294967295UL;
    /**
         Service Errors 
    */
    // asi::diag::uds
    enum eServiceOpError {

        /*
        * Please see the respective Services for information about which ErrorCodes (= NRCs) have to be sent on different use cases
                *
        */
        service_subFunction_unsupported = 18,
        service_incorrect_message_length_format = 19,
        service_condition_incorrect = 34,
        service_sequence_error = 36,
        service_failure_prevents_execution = 38,
        service_request_out_of_range = 49,
        service_general_programming_failure = 114
    };

// Module Version
#define ASI_DIAG_UDS_VERSION ipl::string("1.2.0")
#define ASI_DIAG_UDS_VERSION_MAJOR 1
#define ASI_DIAG_UDS_VERSION_MINOR 2
#define ASI_DIAG_UDS_VERSION_PATCHLEVEL 0

// Module without version
#define ASI_DIAG_UDS_VERSION_FREE_NAMESPACE ipl::string("asi.diag.uds")

// Interface Version
#define ASI_DIAG_UDS_READDATABYIDENT_VERSION_MAJOR 1
#define ASI_DIAG_UDS_READDATABYIDENT_VERSION_MINOR 1
#define ASI_DIAG_UDS_READDATABYIDENT_VERSION_PATCHLEVEL 0

// Interface UUID as string
// NOTE: Using this UUID representation needs more performance, use the binary representation
#define STRING_UUID_ASI_DIAG_UDS_READDATABYIDENT_REQUEST ipl::string("cc69cdb2-3226-11ea-a1c0-ef404598535f")
// Interface UUID as binary
#define BINARY_UUID_ASI_DIAG_UDS_READDATABYIDENT_REQUEST ipl::UUID(0xcc69cdb2, 0x3226, 0x11ea, 0xa1c0, 0xef, 0x40, 0x45, 0x98, 0x53, 0x5f)
// semver encoded as a UUID (non standard version 6)
#define BINARY_IFC_KEY_ASI_DIAG_UDS_READDATABYIDENT_REQUEST comm::InterfaceKey(0x00010002, 0x0000, 0x6000, 0x0000, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00)
#define STRING_IFC_KEY_ASI_DIAG_UDS_READDATABYIDENT_REQUEST ipl::string("00010002-0000-6000-0000-000100010000")

// Interface UUID as string
// NOTE: Using this UUID representation needs more performance, use the binary representation
#define STRING_UUID_ASI_DIAG_UDS_READDATABYIDENT_REPLY ipl::string("d5b8a906-3226-11ea-be09-530048856a4e")
// Interface UUID as binary
#define BINARY_UUID_ASI_DIAG_UDS_READDATABYIDENT_REPLY ipl::UUID(0xd5b8a906, 0x3226, 0x11ea, 0xbe09, 0x53, 0x00, 0x48, 0x85, 0x6a, 0x4e)
// semver encoded as a UUID (non standard version 6)
#define BINARY_IFC_KEY_ASI_DIAG_UDS_READDATABYIDENT_REPLY comm::InterfaceKey(0x00010002, 0x0000, 0x6000, 0x0000, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00)
#define STRING_IFC_KEY_ASI_DIAG_UDS_READDATABYIDENT_REPLY ipl::string("00010002-0000-6000-0000-000100010000")

} } }  // end of module namespace(s)

// Serialization and Deserialization of all enums
namespace util { namespace serializer {
            inline bool serialize(IStructuredSerializer& s, const asi::diag::uds::eServiceOpError  e)
            {
                int32_t value = int32_t(e);

                switch (value)
                {
                    case 18:
                    case 19:
                    case 34:
                    case 36:
                    case 38:
                    case 49:
                    case 114:
                        break;
                    default:
                        // illegal value
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "eServiceOpError");
                        return true;
                }
                return s.putEnum(value, 32);
            }

            inline bool deserialize(IStructuredPullDeserializer& s, asi::diag::uds::eServiceOpError & e)
            {
                int32_t value;
                bool error = s.getEnum(value, 32, false /*unsigned */);
                if (!error) {
                    switch (value)
                    {
                        case 18:
                        case 19:
                        case 34:
                        case 36:
                        case 38:
                        case 49:
                        case 114:
                            break;
                        default:
                            ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "eServiceOpError");
                            return true;
                    }
                    e = (asi::diag::uds::eServiceOpError) value;
                }
                return error;
            }
} } // namespace util::serializer

namespace asi
{
namespace diag
{
namespace uds
{
}// namespace asi
}// namespace diag
}// namespace uds

#endif  // ASI_DIAG_UDS_DEFINITIONS_HXX
