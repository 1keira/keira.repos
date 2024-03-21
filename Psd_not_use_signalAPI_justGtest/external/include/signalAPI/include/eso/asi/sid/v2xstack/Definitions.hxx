/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template ModuleDefinitions_hxx.tmpl
*/
#ifndef ASI_SID_V2XSTACK_DEFINITIONS_HXX
#define ASI_SID_V2XSTACK_DEFINITIONS_HXX

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

namespace asi { namespace sid { namespace v2xstack { 
    /**
        Enum definition SignalStateEnum
    */
    const uint64_t eSignalState_Valid = 0ULL;
    const uint64_t eSignalState_Init = 1ULL;
    const uint64_t eSignalState_Error = 2ULL;
    const uint64_t eSignalState_NotInstalled = 3ULL;
    const uint64_t eSignalState_Undefined = 4ULL;
    const uint64_t eSignalState_NotStandardized = 5ULL;
    const uint64_t eSignalState_RelativeDate = 6ULL;
    const uint64_t eSignalState_EcuKnockOutDeaktivated = 7ULL;
    const uint64_t eSignalState_BusKnockOutDeaktivated = 8ULL;
    const uint64_t eSignalState_NoObject = 9ULL;
    const uint64_t eSignalState_Saturation = 10ULL;
    const uint64_t eSignalState_NotAvailable = 11ULL;
    const uint64_t eSignalState_Deactivated = 12ULL;
    const uint64_t eSignalState_PowertrainDisconnected = 13ULL;
    const uint64_t eSignalState_NotPresent = 14ULL;
    const uint64_t eSignalState_Off = 15ULL;
    const uint64_t eSignalState_Reserved = 16ULL;
    const uint64_t eSignalState_NoDisplay = 17ULL;
    const uint64_t eSignalState_FlashingDisplay = 18ULL;
    const uint64_t eSignalState_NoManualShift = 19ULL;
    const uint64_t eSignalState_ZeroRoundsPerMinute = 20ULL;
    const uint64_t eSignalState_RequiredSensorNotInstalled = 21ULL;
    const uint64_t eSignalState_NoLine = 22ULL;
    const uint64_t eSignalState_Between248mAnd400m = 23ULL;
    const uint64_t eSignalState_MoreThan400m = 24ULL;
    const uint64_t eSignalState_Invalid = 25ULL;
    const uint64_t eSignalState_Undervoltage = 26ULL;
    const uint64_t eSignalState_NoFunctionAvailable = 27ULL;
    const uint64_t eSignalState_Mute = 28ULL;
    const uint64_t eSignalState_MoreThan61 = 29ULL;
    const uint64_t eSignalState_MoreThan126 = 30ULL;
    const uint64_t eSignalState_LessThanMinus250 = 31ULL;
    const uint64_t eSignalState_GreaterThan250 = 32ULL;
    const uint64_t eSignalState_GreaterThanMax = 33ULL;
    /**
        Enum definition PduStateEnum
    */
    const uint64_t ePduState_NotExisting = 0ULL;
    const uint64_t ePduState_Valid = 1ULL;
    const uint64_t ePduState_TempNotValid = 2ULL;
    const uint64_t ePduState_TimeoutNotValidNotFiltered = 3ULL;
    const uint64_t ePduState_NeverReceived = 4ULL;
    const uint64_t ePduState_TimeoutNotValidFiltered = 5ULL;
    const uint64_t ePduState_Invalid = 15ULL;
    /**
        instance ID for the ASI interface
    */
    const uint32_t INTV2XSTACK_INSTANCE_ID = 1UL;
    /**
        minimum update time (ms) for the attributes
    */
    const uint32_t INTV2XSTACK_ESC50_PERIOD = 0UL;
    const uint32_t INTV2XSTACK_EBKV03AUTH_PERIOD = 0UL;
    const uint32_t INTV2XSTACK_ESC51AUTH_PERIOD = 0UL;
    const uint32_t INTV2XSTACK_ESP21_PERIOD = 0UL;
    const uint32_t INTV2XSTACK_LICHTANF01_PERIOD = 0UL;
    const uint32_t INTV2XSTACK_LICHTVORNE01_PERIOD = 0UL;
    const uint32_t INTV2XSTACK_BLINKMODI02_PERIOD = 0UL;
    const uint32_t INTV2XSTACK_VMM02AUTH_PERIOD = 0UL;
    const uint32_t INTV2XSTACK_ESP24_PERIOD = 0UL;
    const uint32_t INTV2XSTACK_MOTOR14_PERIOD = 0UL;
    const uint32_t INTV2XSTACK_LWI01_PERIOD = 0UL;
    const uint32_t INTV2XSTACK_GETRIEBE11_PERIOD = 0UL;
    const uint32_t INTV2XSTACK_KLEMMENSTATUS01_PERIOD = 0UL;
    const uint32_t INTV2XSTACK_PERSONALISIERUNG01_PERIOD = 0UL;

// Module Version
#define ASI_SID_V2XSTACK_VERSION ipl::string("1.0.0")
#define ASI_SID_V2XSTACK_VERSION_MAJOR 1
#define ASI_SID_V2XSTACK_VERSION_MINOR 0
#define ASI_SID_V2XSTACK_VERSION_PATCHLEVEL 0

// Module without version
#define ASI_SID_V2XSTACK_VERSION_FREE_NAMESPACE ipl::string("asi.sid")

// Interface Version
#define ASI_SID_V2XSTACK_INTV2XSTACK_VERSION_MAJOR 1
#define ASI_SID_V2XSTACK_INTV2XSTACK_VERSION_MINOR 0
#define ASI_SID_V2XSTACK_INTV2XSTACK_VERSION_PATCHLEVEL 0

// Interface UUID as string
// NOTE: Using this UUID representation needs more performance, use the binary representation
#define STRING_UUID_ASI_SID_V2XSTACK_INTV2XSTACK_REQUEST ipl::string("7849fb46-ec45-5d13-b16d-ec2179252966")
// Interface UUID as binary
#define BINARY_UUID_ASI_SID_V2XSTACK_INTV2XSTACK_REQUEST ipl::UUID(0x7849fb46, 0xec45, 0x5d13, 0xb16d, 0xec, 0x21, 0x79, 0x25, 0x29, 0x66)
// semver encoded as a UUID (non standard version 6)
#define BINARY_IFC_KEY_ASI_SID_V2XSTACK_INTV2XSTACK_REQUEST comm::InterfaceKey(0x00010000, 0x0000, 0x6000, 0x0000, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00)
#define STRING_IFC_KEY_ASI_SID_V2XSTACK_INTV2XSTACK_REQUEST ipl::string("00010000-0000-6000-0000-000100000000")

// Interface UUID as string
// NOTE: Using this UUID representation needs more performance, use the binary representation
#define STRING_UUID_ASI_SID_V2XSTACK_INTV2XSTACK_REPLY ipl::string("14b60cbe-515f-5af6-b6aa-493677f07dd9")
// Interface UUID as binary
#define BINARY_UUID_ASI_SID_V2XSTACK_INTV2XSTACK_REPLY ipl::UUID(0x14b60cbe, 0x515f, 0x5af6, 0xb6aa, 0x49, 0x36, 0x77, 0xf0, 0x7d, 0xd9)
// semver encoded as a UUID (non standard version 6)
#define BINARY_IFC_KEY_ASI_SID_V2XSTACK_INTV2XSTACK_REPLY comm::InterfaceKey(0x00010000, 0x0000, 0x6000, 0x0000, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00)
#define STRING_IFC_KEY_ASI_SID_V2XSTACK_INTV2XSTACK_REPLY ipl::string("00010000-0000-6000-0000-000100000000")

// IDSs for the attributes
#define ASI_SID_V2XSTACK_INTV2XSTACK_ESC50 22
#define ASI_SID_V2XSTACK_INTV2XSTACK_EBKV03AUTH 21
#define ASI_SID_V2XSTACK_INTV2XSTACK_ESC51AUTH 23
#define ASI_SID_V2XSTACK_INTV2XSTACK_ESP21 24
#define ASI_SID_V2XSTACK_INTV2XSTACK_LICHTANF01 29
#define ASI_SID_V2XSTACK_INTV2XSTACK_LICHTVORNE01 30
#define ASI_SID_V2XSTACK_INTV2XSTACK_BLINKMODI02 20
#define ASI_SID_V2XSTACK_INTV2XSTACK_VMM02AUTH 33
#define ASI_SID_V2XSTACK_INTV2XSTACK_ESP24 25
#define ASI_SID_V2XSTACK_INTV2XSTACK_MOTOR14 31
#define ASI_SID_V2XSTACK_INTV2XSTACK_LWI01 28
#define ASI_SID_V2XSTACK_INTV2XSTACK_GETRIEBE11 26
#define ASI_SID_V2XSTACK_INTV2XSTACK_KLEMMENSTATUS01 27
#define ASI_SID_V2XSTACK_INTV2XSTACK_PERSONALISIERUNG01 32
} } }  // end of module namespace(s)

// Serialization and Deserialization of all enums
namespace util { namespace serializer {
} } // namespace util::serializer

namespace asi
{
namespace sid
{
namespace v2xstack
{
}// namespace asi
}// namespace sid
}// namespace v2xstack

#endif  // ASI_SID_V2XSTACK_DEFINITIONS_HXX
