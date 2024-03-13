/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleModuleDefinitions_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_OOC_DEFINITIONS_CSTYLE_HXX
#define ASI_CONNECTIVITY_OOC_DEFINITIONS_CSTYLE_HXX

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

namespace asi { namespace connectivity { namespace ooc { namespace cstyle {

// Module Version
#define ASI_CONNECTIVITY_OOC_VERSION ipl::string("1.0.1")
#define ASI_CONNECTIVITY_OOC_VERSION_MAJOR 1
#define ASI_CONNECTIVITY_OOC_VERSION_MINOR 0
#define ASI_CONNECTIVITY_OOC_VERSION_PATCHLEVEL 1

// Module without version
#define ASI_CONNECTIVITY_OOC_VERSION_FREE_NAMESPACE ipl::string("asi.connectivity.ooc")

// Interface Version
#define ASI_CONNECTIVITY_OOC_POWERMANAGEMENTSERVICE_VERSION_MAJOR 1
#define ASI_CONNECTIVITY_OOC_POWERMANAGEMENTSERVICE_VERSION_MINOR 0
#define ASI_CONNECTIVITY_OOC_POWERMANAGEMENTSERVICE_VERSION_PATCHLEVEL 1

// Interface UUID as string
// NOTE: Using this UUID representation needs more performance, use the binary representation
#define STRING_UUID_ASI_CONNECTIVITY_OOC_POWERMANAGEMENTSERVICE_REQUEST ipl::string("ce2cbc2b-e64f-4c7a-a4a3-efcda12a0b09")
// Interface UUID as binary
#define BINARY_UUID_ASI_CONNECTIVITY_OOC_POWERMANAGEMENTSERVICE_REQUEST ipl::UUID(0xce2cbc2b, 0xe64f, 0x4c7a, 0xa4a3, 0xef, 0xcd, 0xa1, 0x2a, 0x0b, 0x09)
// Interface UUID as string
// NOTE: Using this UUID representation needs more performance, use the binary representation
#define STRING_UUID_ASI_CONNECTIVITY_OOC_POWERMANAGEMENTSERVICE_REPLY ipl::string("ddb92f08-74d0-499a-b139-8deff371cdba")
// Interface UUID as binary
#define BINARY_UUID_ASI_CONNECTIVITY_OOC_POWERMANAGEMENTSERVICE_REPLY ipl::UUID(0xddb92f08, 0x74d0, 0x499a, 0xb139, 0x8d, 0xef, 0xf3, 0x71, 0xcd, 0xba)

} //  end of namespace cstyle
} } }  // end of module namespace(s)

// Streaming operators for all enums arrays
namespace util { namespace serializer {
// Streaming operators for all enum arrays

} } // namespace util::serializer

#endif  // ASI_CONNECTIVITY_OOC_DEFINITIONS_CSTYLE_HXX
