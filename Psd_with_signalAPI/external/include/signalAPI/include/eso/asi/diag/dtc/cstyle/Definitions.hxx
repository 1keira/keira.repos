/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleModuleDefinitions_hxx.tmpl
*/
#ifndef ASI_DIAG_DTC_DEFINITIONS_CSTYLE_HXX
#define ASI_DIAG_DTC_DEFINITIONS_CSTYLE_HXX

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

namespace asi { namespace diag { namespace dtc { namespace cstyle {
    enum eDtcTestResult {

        dtc_test_result_pre_failed = 0,
        dtc_test_result_failed = 1,
        dtc_test_result_pre_passed = 2,
        dtc_test_result_passed = 3
    };
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
// Interface UUID as string
// NOTE: Using this UUID representation needs more performance, use the binary representation
#define STRING_UUID_ASI_DIAG_DTC_DTC_REPLY ipl::string("d0cf53f4-3c35-11ea-a1f5-93aec4819508")
// Interface UUID as binary
#define BINARY_UUID_ASI_DIAG_DTC_DTC_REPLY ipl::UUID(0xd0cf53f4, 0x3c35, 0x11ea, 0xa1f5, 0x93, 0xae, 0xc4, 0x81, 0x95, 0x08)

} //  end of namespace cstyle
} } }  // end of module namespace(s)

// Streaming operators for all enums arrays
namespace util { namespace serializer {
// Streaming operators for all enum arrays

        inline bool serialize(IStructuredSerializer& s, const asi::diag::dtc::cstyle::eDtcTestResult  e)
        {
            int32_t value = int32_t(e);

            if ((value < 0) ||
                (value > 3))
            {
                ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "eDtcTestResult");
                return true;
            }
            return s.putEnum(value, 32);
        }

        inline bool deserialize(IStructuredPullDeserializer& s, asi::diag::dtc::cstyle::eDtcTestResult & e)
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
                e = (asi::diag::dtc::cstyle::eDtcTestResult) value;
            }
            return error;
        }


        inline bool serialize(IStructuredSerializer& s, const asi::diag::dtc::cstyle::eDtcEvent  e)
        {
            int32_t value = int32_t(e);

            if ((value < 0) ||
                (value > 0))
            {
                ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "eDtcEvent");
                return true;
            }
            return s.putEnum(value, 32);
        }

        inline bool deserialize(IStructuredPullDeserializer& s, asi::diag::dtc::cstyle::eDtcEvent & e)
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
                e = (asi::diag::dtc::cstyle::eDtcEvent) value;
            }
            return error;
        }


} } // namespace util::serializer

#endif  // ASI_DIAG_DTC_DEFINITIONS_CSTYLE_HXX
