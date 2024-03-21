/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template ModuleDefinitions_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_OOC_DEFINITIONS_HXX
#define ASI_CONNECTIVITY_OOC_DEFINITIONS_HXX

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

namespace asi { namespace connectivity { namespace ooc { 

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
// semver encoded as a UUID (non standard version 6)
#define BINARY_IFC_KEY_ASI_CONNECTIVITY_OOC_POWERMANAGEMENTSERVICE_REQUEST comm::InterfaceKey(0x00010000, 0x0001, 0x6000, 0x0000, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01)
#define STRING_IFC_KEY_ASI_CONNECTIVITY_OOC_POWERMANAGEMENTSERVICE_REQUEST ipl::string("00010000-0001-6000-0000-000100000001")

// Interface UUID as string
// NOTE: Using this UUID representation needs more performance, use the binary representation
#define STRING_UUID_ASI_CONNECTIVITY_OOC_POWERMANAGEMENTSERVICE_REPLY ipl::string("ddb92f08-74d0-499a-b139-8deff371cdba")
// Interface UUID as binary
#define BINARY_UUID_ASI_CONNECTIVITY_OOC_POWERMANAGEMENTSERVICE_REPLY ipl::UUID(0xddb92f08, 0x74d0, 0x499a, 0xb139, 0x8d, 0xef, 0xf3, 0x71, 0xcd, 0xba)
// semver encoded as a UUID (non standard version 6)
#define BINARY_IFC_KEY_ASI_CONNECTIVITY_OOC_POWERMANAGEMENTSERVICE_REPLY comm::InterfaceKey(0x00010000, 0x0001, 0x6000, 0x0000, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01)
#define STRING_IFC_KEY_ASI_CONNECTIVITY_OOC_POWERMANAGEMENTSERVICE_REPLY ipl::string("00010000-0001-6000-0000-000100000001")

} } }  // end of module namespace(s)

// Serialization and Deserialization of all enums
namespace util { namespace serializer {
} } // namespace util::serializer

namespace asi
{
namespace connectivity
{
namespace ooc
{
}// namespace asi
}// namespace connectivity
}// namespace ooc

#endif  // ASI_CONNECTIVITY_OOC_DEFINITIONS_HXX
