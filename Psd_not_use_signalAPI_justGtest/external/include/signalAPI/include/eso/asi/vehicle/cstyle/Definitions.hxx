/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleModuleDefinitions_hxx.tmpl
*/
#ifndef ASI_VEHICLE_DEFINITIONS_CSTYLE_HXX
#define ASI_VEHICLE_DEFINITIONS_CSTYLE_HXX

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

namespace asi { namespace vehicle { namespace cstyle {
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
// Interface UUID as string
// NOTE: Using this UUID representation needs more performance, use the binary representation
#define STRING_UUID_ASI_VEHICLE_TEST_REPLY ipl::string("c10ac01f-3f55-5440-b401-d4074d8602be")
// Interface UUID as binary
#define BINARY_UUID_ASI_VEHICLE_TEST_REPLY ipl::UUID(0xc10ac01f, 0x3f55, 0x5440, 0xb401, 0xd4, 0x07, 0x4d, 0x86, 0x02, 0xbe)

// IDSs for the attributes
#define ASI_VEHICLE_TEST_KLEMMEN_STATUS_01 7
} //  end of namespace cstyle
} }  // end of module namespace(s)

// Streaming operators for all enums arrays
namespace util { namespace serializer {
// Streaming operators for all enum arrays

} } // namespace util::serializer

#endif  // ASI_VEHICLE_DEFINITIONS_CSTYLE_HXX
