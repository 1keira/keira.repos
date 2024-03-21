/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template ModuleDefinitions_hxx.tmpl
*/
#ifndef ASI_DIAG_COMMON_DEFINITIONS_HXX
#define ASI_DIAG_COMMON_DEFINITIONS_HXX

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

namespace asi { namespace diag { namespace common { 
    /**
        * Clients have to connect to the following diag node instance IDs to use the ASIs of respective node
     *
     * 0x8125 - Compute Node1
     * 0x813f - Sound
     * 0x0017 - Instrument Cluster
     * 0x8153 - Android
    */
    const uint32_t diag_id_cn1 = 33061UL;
    const uint32_t diag_id_sound = 33087UL;
    const uint32_t diag_id_cluster = 23UL;
    const uint32_t diag_id_android = 33107UL;
    /**
        * Identifier to receive p-mode status via storage ASI for Compute Node1 (8125) 
     * This id should be used instead of original adaption value for p-mode (id 0x04FE).
     * Reason: more conditions needs to be checked to decide, if p-mode is active. Diagnosis node cn1
     * is checking these conditions and the result can be retrieved by this id.
     * Payload structure is identical to 0x04FE (see specification).
    */
    const uint16_t pmode_id_storage_cn1 = 42240;

// Module Version
#define ASI_DIAG_COMMON_VERSION ipl::string("1.0.1")
#define ASI_DIAG_COMMON_VERSION_MAJOR 1
#define ASI_DIAG_COMMON_VERSION_MINOR 0
#define ASI_DIAG_COMMON_VERSION_PATCHLEVEL 1

// Module without version
#define ASI_DIAG_COMMON_VERSION_FREE_NAMESPACE ipl::string("asi.diag.common")

// Interface Version

} } }  // end of module namespace(s)

// Serialization and Deserialization of all enums
namespace util { namespace serializer {
} } // namespace util::serializer

namespace asi
{
namespace diag
{
namespace common
{
}// namespace asi
}// namespace diag
}// namespace common

#endif  // ASI_DIAG_COMMON_DEFINITIONS_HXX
