/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template ModuleDefinitions_hxx.tmpl
*/
#ifndef ASI_DIAG_DTC_DEFINITIONS_HXX
#define ASI_DIAG_DTC_DEFINITIONS_HXX

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

namespace asi { namespace diag { namespace dtc { 
    // asi::diag::dtc
    enum eDtcTestResult {

        dtc_test_result_pre_failed = 0,
        dtc_test_result_failed = 1,
        dtc_test_result_pre_passed = 2,
        dtc_test_result_passed = 3
    };
    // asi::diag::dtc
    enum eDtcEvent {

        dtc_event_storage_cleared = 0
    };

// Module Version
#define ASI_DIAG_DTC_VERSION ipl::string("0.5.0")
#define ASI_DIAG_DTC_VERSION_MAJOR 0
#define ASI_DIAG_DTC_VERSION_MINOR 5
#define ASI_DIAG_DTC_VERSION_PATCHLEVEL 0

// Module without version
#define ASI_DIAG_DTC_VERSION_FREE_NAMESPACE ipl::string("asi.diag.dtc")

// Interface Version
#define ASI_DIAG_DTC_DTC_VERSION_MAJOR 0
#define ASI_DIAG_DTC_DTC_VERSION_MINOR 3
#define ASI_DIAG_DTC_DTC_VERSION_PATCHLEVEL 0

// Interface UUID as string
// NOTE: Using this UUID representation needs more performance, use the binary representation
#define STRING_UUID_ASI_DIAG_DTC_DTC_REQUEST ipl::string("cb8d87a8-3c35-11ea-9df0-53ed12a0bde7")
// Interface UUID as binary
#define BINARY_UUID_ASI_DIAG_DTC_DTC_REQUEST ipl::UUID(0xcb8d87a8, 0x3c35, 0x11ea, 0x9df0, 0x53, 0xed, 0x12, 0xa0, 0xbd, 0xe7)
// semver encoded as a UUID (non standard version 6)
#define BINARY_IFC_KEY_ASI_DIAG_DTC_DTC_REQUEST comm::InterfaceKey(0x00000005, 0x0000, 0x6000, 0x0000, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00)
#define STRING_IFC_KEY_ASI_DIAG_DTC_DTC_REQUEST ipl::string("00000005-0000-6000-0000-000000030000")

// Interface UUID as string
// NOTE: Using this UUID representation needs more performance, use the binary representation
#define STRING_UUID_ASI_DIAG_DTC_DTC_REPLY ipl::string("d0cf53f4-3c35-11ea-a1f5-93aec4819508")
// Interface UUID as binary
#define BINARY_UUID_ASI_DIAG_DTC_DTC_REPLY ipl::UUID(0xd0cf53f4, 0x3c35, 0x11ea, 0xa1f5, 0x93, 0xae, 0xc4, 0x81, 0x95, 0x08)
// semver encoded as a UUID (non standard version 6)
#define BINARY_IFC_KEY_ASI_DIAG_DTC_DTC_REPLY comm::InterfaceKey(0x00000005, 0x0000, 0x6000, 0x0000, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00)
#define STRING_IFC_KEY_ASI_DIAG_DTC_DTC_REPLY ipl::string("00000005-0000-6000-0000-000000030000")

} } }  // end of module namespace(s)

// Serialization and Deserialization of all enums
namespace util { namespace serializer {
            inline bool serialize(IStructuredSerializer& s, const asi::diag::dtc::eDtcTestResult  e)
            {
                int32_t value = int32_t(e);

                if ((value < 0) ||
                    (value > 3))
                {
                    // illegal value
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "eDtcTestResult");
                    return true;
                }
                return s.putEnum(value, 32);
            }

            inline bool deserialize(IStructuredPullDeserializer& s, asi::diag::dtc::eDtcTestResult & e)
            {
                int32_t value;
                bool error = s.getEnum(value, 32, false /*unsigned */);
                if (!error) {
                    if ((value < 0) ||
                        (value > 3))
                    {
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "eDtcTestResult");
                        return true;
                    }
                    e = (asi::diag::dtc::eDtcTestResult) value;
                }
                return error;
            }
            inline bool serialize(IStructuredSerializer& s, const asi::diag::dtc::eDtcEvent  e)
            {
                int32_t value = int32_t(e);

                if ((value < 0) ||
                    (value > 0))
                {
                    // illegal value
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "eDtcEvent");
                    return true;
                }
                return s.putEnum(value, 32);
            }

            inline bool deserialize(IStructuredPullDeserializer& s, asi::diag::dtc::eDtcEvent & e)
            {
                int32_t value;
                bool error = s.getEnum(value, 32, false /*unsigned */);
                if (!error) {
                    if ((value < 0) ||
                        (value > 0))
                    {
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "eDtcEvent");
                        return true;
                    }
                    e = (asi::diag::dtc::eDtcEvent) value;
                }
                return error;
            }
} } // namespace util::serializer

namespace asi
{
namespace diag
{
namespace dtc
{
}// namespace asi
}// namespace diag
}// namespace dtc

#endif  // ASI_DIAG_DTC_DEFINITIONS_HXX
