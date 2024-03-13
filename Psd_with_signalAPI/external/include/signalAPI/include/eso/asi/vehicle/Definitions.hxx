/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template ModuleDefinitions_hxx.tmpl
*/
#ifndef ASI_VEHICLE_DEFINITIONS_HXX
#define ASI_VEHICLE_DEFINITIONS_HXX

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

namespace asi { namespace vehicle { 
    /**
        Enum definition ZASKl15Enum
    */
    const uint64_t eZASKl15_Aus = 0ULL;
    const uint64_t eZASKl15_Ein = 1ULL;
    /**
        Enum definition PdustateEnum
    */
    const uint64_t ePdustate_NotExisting = 0ULL;
    const uint64_t ePdustate_Valid = 1ULL;
    const uint64_t ePdustate_TempNotValid = 2ULL;
    const uint64_t ePdustate_TimeoutNotValidNotFiltered = 3ULL;
    const uint64_t ePdustate_NeverReceived = 4ULL;
    const uint64_t ePdustate_TimeoutNotValidFiltered = 5ULL;
    const uint64_t ePdustate_Invalid = 15ULL;
    /**
        instance ID for the ASI interface
    */
    const uint32_t TEST_INSTANCE_ID = 1UL;
    /**
        minimum update time (ms) for the attributes
    */
    const uint32_t TEST_KLEMMEN_STATUS_01_PERIOD = 0UL;

// Module Version
#define ASI_VEHICLE_VERSION ipl::string("1.0.0")
#define ASI_VEHICLE_VERSION_MAJOR 1
#define ASI_VEHICLE_VERSION_MINOR 0
#define ASI_VEHICLE_VERSION_PATCHLEVEL 0

// Module without version
#define ASI_VEHICLE_VERSION_FREE_NAMESPACE ipl::string("asi.vehicle")

// Interface Version
#define ASI_VEHICLE_TEST_VERSION_MAJOR 1
#define ASI_VEHICLE_TEST_VERSION_MINOR 0
#define ASI_VEHICLE_TEST_VERSION_PATCHLEVEL 0

// Interface UUID as string
// NOTE: Using this UUID representation needs more performance, use the binary representation
#define STRING_UUID_ASI_VEHICLE_TEST_REQUEST ipl::string("606beb48-725e-5e98-b456-048fb6b6d129")
// Interface UUID as binary
#define BINARY_UUID_ASI_VEHICLE_TEST_REQUEST ipl::UUID(0x606beb48, 0x725e, 0x5e98, 0xb456, 0x04, 0x8f, 0xb6, 0xb6, 0xd1, 0x29)
// semver encoded as a UUID (non standard version 6)
#define BINARY_IFC_KEY_ASI_VEHICLE_TEST_REQUEST comm::InterfaceKey(0x00010000, 0x0000, 0x6000, 0x0000, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00)
#define STRING_IFC_KEY_ASI_VEHICLE_TEST_REQUEST ipl::string("00010000-0000-6000-0000-000100000000")

// Interface UUID as string
// NOTE: Using this UUID representation needs more performance, use the binary representation
#define STRING_UUID_ASI_VEHICLE_TEST_REPLY ipl::string("c10ac01f-3f55-5440-b401-d4074d8602be")
// Interface UUID as binary
#define BINARY_UUID_ASI_VEHICLE_TEST_REPLY ipl::UUID(0xc10ac01f, 0x3f55, 0x5440, 0xb401, 0xd4, 0x07, 0x4d, 0x86, 0x02, 0xbe)
// semver encoded as a UUID (non standard version 6)
#define BINARY_IFC_KEY_ASI_VEHICLE_TEST_REPLY comm::InterfaceKey(0x00010000, 0x0000, 0x6000, 0x0000, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00)
#define STRING_IFC_KEY_ASI_VEHICLE_TEST_REPLY ipl::string("00010000-0000-6000-0000-000100000000")

// IDSs for the attributes
#define ASI_VEHICLE_TEST_KLEMMEN_STATUS_01 7
} }  // end of module namespace(s)

// Serialization and Deserialization of all enums
namespace util { namespace serializer {
} } // namespace util::serializer

namespace asi
{
namespace vehicle
{
}// namespace asi
}// namespace vehicle

#endif  // ASI_VEHICLE_DEFINITIONS_HXX
