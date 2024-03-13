/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleModuleDefinitions_hxx.tmpl
*/
#ifndef ASI_DIAG_UDS_DEFINITIONS_CSTYLE_HXX
#define ASI_DIAG_UDS_DEFINITIONS_CSTYLE_HXX

#include <ipl_config.h>
#include <common/types/string.hxx>
#include <common/UUID.hxx>
#include <common/tracing/tracing.hxx>
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

namespace asi { namespace diag { namespace uds { namespace cstyle {
    const uint32_t dfcc_no_dtc = 4294967295UL;
    /**
         Service Errors 
    */
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
// Interface UUID as string
// NOTE: Using this UUID representation needs more performance, use the binary representation
#define STRING_UUID_ASI_DIAG_UDS_READDATABYIDENT_REPLY ipl::string("d5b8a906-3226-11ea-be09-530048856a4e")
// Interface UUID as binary
#define BINARY_UUID_ASI_DIAG_UDS_READDATABYIDENT_REPLY ipl::UUID(0xd5b8a906, 0x3226, 0x11ea, 0xbe09, 0x53, 0x00, 0x48, 0x85, 0x6a, 0x4e)

} //  end of namespace cstyle
} } }  // end of module namespace(s)

// Streaming operators for all enums arrays
namespace util { namespace serializer {
// Streaming operators for all enum arrays

        inline bool serialize(IStructuredSerializer& s, const asi::diag::uds::cstyle::eServiceOpError  e)
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
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "eServiceOpError");
                    return true;
            }
            return s.putEnum(value, 32);
        }

        inline bool deserialize(IStructuredPullDeserializer& s, asi::diag::uds::cstyle::eServiceOpError & e)
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
                e = (asi::diag::uds::cstyle::eServiceOpError) value;
            }
            return error;
        }


} } // namespace util::serializer

#endif  // ASI_DIAG_UDS_DEFINITIONS_CSTYLE_HXX
