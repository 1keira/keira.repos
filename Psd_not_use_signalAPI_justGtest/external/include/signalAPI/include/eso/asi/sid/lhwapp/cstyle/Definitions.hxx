/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleModuleDefinitions_hxx.tmpl
*/
#ifndef ASI_SID_LHWAPP_DEFINITIONS_CSTYLE_HXX
#define ASI_SID_LHWAPP_DEFINITIONS_CSTYLE_HXX

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

namespace asi { namespace sid { namespace lhwapp { namespace cstyle {
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
        instance ID for the ASI interface
    */
    const uint32_t INTLHWAPP_INSTANCE_ID = 1UL;
    /**
        minimum update time (ms) for the attributes
    */
    const uint32_t INTLHWAPP_AIRBAG01_PERIOD = 0UL;
    const uint32_t INTLHWAPP_BLINKMODI02_PERIOD = 0UL;
    const uint32_t INTLHWAPP_DAEMPFER01_PERIOD = 0UL;
    const uint32_t INTLHWAPP_ESC50_PERIOD = 0UL;
    const uint32_t INTLHWAPP_ESP21_PERIOD = 0UL;
    const uint32_t INTLHWAPP_ESP24_PERIOD = 0UL;
    const uint32_t INTLHWAPP_ESP30_PERIOD = 0UL;
    const uint32_t INTLHWAPP_HVK01_PERIOD = 0UL;
    const uint32_t INTLHWAPP_MOTOR18_PERIOD = 0UL;
    const uint32_t INTLHWAPP_MOTOR_41_PERIOD = 0UL;
    const uint32_t INTLHWAPP_POSGNSSDR01_PERIOD = 0UL;
    const uint32_t INTLHWAPP_PSD04_PERIOD = 0UL;
    const uint32_t INTLHWAPP_PSD05_PERIOD = 0UL;
    const uint32_t INTLHWAPP_PSD06_PERIOD = 0UL;
    const uint32_t INTLHWAPP_RKA01_PERIOD = 0UL;

// Module Version
#define ASI_SID_LHWAPP_VERSION ipl::string("1.0.0")
#define ASI_SID_LHWAPP_VERSION_MAJOR 1
#define ASI_SID_LHWAPP_VERSION_MINOR 0
#define ASI_SID_LHWAPP_VERSION_PATCHLEVEL 0

// Module without version
#define ASI_SID_LHWAPP_VERSION_FREE_NAMESPACE ipl::string("asi.sid.lhwapp")

// Interface Version
#define ASI_SID_LHWAPP_INTLHWAPP_VERSION_MAJOR 1
#define ASI_SID_LHWAPP_INTLHWAPP_VERSION_MINOR 0
#define ASI_SID_LHWAPP_INTLHWAPP_VERSION_PATCHLEVEL 0

// Interface UUID as string
// NOTE: Using this UUID representation needs more performance, use the binary representation
#define STRING_UUID_ASI_SID_LHWAPP_INTLHWAPP_REQUEST ipl::string("e7ad5a94-c7bd-59e9-ad52-ddaef46b9591")
// Interface UUID as binary
#define BINARY_UUID_ASI_SID_LHWAPP_INTLHWAPP_REQUEST ipl::UUID(0xe7ad5a94, 0xc7bd, 0x59e9, 0xad52, 0xdd, 0xae, 0xf4, 0x6b, 0x95, 0x91)
// Interface UUID as string
// NOTE: Using this UUID representation needs more performance, use the binary representation
#define STRING_UUID_ASI_SID_LHWAPP_INTLHWAPP_REPLY ipl::string("f1260d67-98aa-563a-8d3b-1805e1f9d226")
// Interface UUID as binary
#define BINARY_UUID_ASI_SID_LHWAPP_INTLHWAPP_REPLY ipl::UUID(0xf1260d67, 0x98aa, 0x563a, 0x8d3b, 0x18, 0x05, 0xe1, 0xf9, 0xd2, 0x26)

// IDSs for the attributes
#define ASI_SID_LHWAPP_INTLHWAPP_AIRBAG01 21
#define ASI_SID_LHWAPP_INTLHWAPP_BLINKMODI02 22
#define ASI_SID_LHWAPP_INTLHWAPP_DAEMPFER01 23
#define ASI_SID_LHWAPP_INTLHWAPP_ESC50 24
#define ASI_SID_LHWAPP_INTLHWAPP_ESP21 25
#define ASI_SID_LHWAPP_INTLHWAPP_ESP24 26
#define ASI_SID_LHWAPP_INTLHWAPP_ESP30 27
#define ASI_SID_LHWAPP_INTLHWAPP_HVK01 28
#define ASI_SID_LHWAPP_INTLHWAPP_MOTOR18 29
#define ASI_SID_LHWAPP_INTLHWAPP_MOTOR_41 30
#define ASI_SID_LHWAPP_INTLHWAPP_POSGNSSDR01 31
#define ASI_SID_LHWAPP_INTLHWAPP_PSD04 32
#define ASI_SID_LHWAPP_INTLHWAPP_PSD05 33
#define ASI_SID_LHWAPP_INTLHWAPP_PSD06 34
#define ASI_SID_LHWAPP_INTLHWAPP_RKA01 35
} //  end of namespace cstyle
} } }  // end of module namespace(s)

// Streaming operators for all enums arrays
namespace util { namespace serializer {
// Streaming operators for all enum arrays

} } // namespace util::serializer

#endif  // ASI_SID_LHWAPP_DEFINITIONS_CSTYLE_HXX
