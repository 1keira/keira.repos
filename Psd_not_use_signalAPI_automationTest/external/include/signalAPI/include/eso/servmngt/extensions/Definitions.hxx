/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template ModuleDefinitions_hxx.tmpl
*/
#ifndef SERVMNGT_EXTENSIONS_DEFINITIONS_HXX
#define SERVMNGT_EXTENSIONS_DEFINITIONS_HXX

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

namespace servmngt { namespace extensions { 
    const uint32_t DEFAULT_WD_PERIOD = 5000UL;
    // servmngt::extensions
    enum SuspendRequest {

        /*
        start suspend prepare
        */
        SUSPEND_PREPARE = 0,
        /*
        suspend is cancelled
        */
        SUSPEND_CANCEL = 1,
        /*
        continue after suspend
        */
        SUSPEND_RESUME = 2
    };
    // servmngt::extensions
    enum ServiceManagerEventType {

        SMET_WATCHDOG_MISSED = 0
    };

// Module Version
#define SERVMNGT_EXTENSIONS_VERSION ipl::string("3.0.1")
#define SERVMNGT_EXTENSIONS_VERSION_MAJOR 3
#define SERVMNGT_EXTENSIONS_VERSION_MINOR 0
#define SERVMNGT_EXTENSIONS_VERSION_PATCHLEVEL 1

// Module without version
#define SERVMNGT_EXTENSIONS_VERSION_FREE_NAMESPACE ipl::string("servmngt.extensions")

// Interface Version
#define SERVMNGT_EXTENSIONS_WATCHDOG_VERSION_MAJOR 1
#define SERVMNGT_EXTENSIONS_WATCHDOG_VERSION_MINOR 0
#define SERVMNGT_EXTENSIONS_WATCHDOG_VERSION_PATCHLEVEL 0
#define SERVMNGT_EXTENSIONS_SYSTEMEVENTS_VERSION_MAJOR 2
#define SERVMNGT_EXTENSIONS_SYSTEMEVENTS_VERSION_MINOR 0
#define SERVMNGT_EXTENSIONS_SYSTEMEVENTS_VERSION_PATCHLEVEL 0
#define SERVMNGT_EXTENSIONS_SERVICEMANAGEREVENTS_VERSION_MAJOR 1
#define SERVMNGT_EXTENSIONS_SERVICEMANAGEREVENTS_VERSION_MINOR 0
#define SERVMNGT_EXTENSIONS_SERVICEMANAGEREVENTS_VERSION_PATCHLEVEL 0

// Interface UUID as string
// NOTE: Using this UUID representation needs more performance, use the binary representation
#define STRING_UUID_SERVMNGT_EXTENSIONS_WATCHDOG_REQUEST ipl::string("11eaa58a-7811-47de-9981-4f8914ce7c1e")
// Interface UUID as binary
#define BINARY_UUID_SERVMNGT_EXTENSIONS_WATCHDOG_REQUEST ipl::UUID(0x11eaa58a, 0x7811, 0x47de, 0x9981, 0x4f, 0x89, 0x14, 0xce, 0x7c, 0x1e)
// semver encoded as a UUID (non standard version 6)
#define BINARY_IFC_KEY_SERVMNGT_EXTENSIONS_WATCHDOG_REQUEST comm::InterfaceKey(0x00030000, 0x0001, 0x6000, 0x0000, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00)
#define STRING_IFC_KEY_SERVMNGT_EXTENSIONS_WATCHDOG_REQUEST ipl::string("00030000-0001-6000-0000-000100000000")

// Interface UUID as string
// NOTE: Using this UUID representation needs more performance, use the binary representation
#define STRING_UUID_SERVMNGT_EXTENSIONS_WATCHDOG_REPLY ipl::string("3fafdfd0-c4f8-4433-b358-8d2cbc45f9e2")
// Interface UUID as binary
#define BINARY_UUID_SERVMNGT_EXTENSIONS_WATCHDOG_REPLY ipl::UUID(0x3fafdfd0, 0xc4f8, 0x4433, 0xb358, 0x8d, 0x2c, 0xbc, 0x45, 0xf9, 0xe2)
// semver encoded as a UUID (non standard version 6)
#define BINARY_IFC_KEY_SERVMNGT_EXTENSIONS_WATCHDOG_REPLY comm::InterfaceKey(0x00030000, 0x0001, 0x6000, 0x0000, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00)
#define STRING_IFC_KEY_SERVMNGT_EXTENSIONS_WATCHDOG_REPLY ipl::string("00030000-0001-6000-0000-000100000000")

// Interface UUID as string
// NOTE: Using this UUID representation needs more performance, use the binary representation
#define STRING_UUID_SERVMNGT_EXTENSIONS_SYSTEMEVENTS_REQUEST ipl::string("51749ceb-66b7-46ea-9862-0230f186a8e7")
// Interface UUID as binary
#define BINARY_UUID_SERVMNGT_EXTENSIONS_SYSTEMEVENTS_REQUEST ipl::UUID(0x51749ceb, 0x66b7, 0x46ea, 0x9862, 0x02, 0x30, 0xf1, 0x86, 0xa8, 0xe7)
// semver encoded as a UUID (non standard version 6)
#define BINARY_IFC_KEY_SERVMNGT_EXTENSIONS_SYSTEMEVENTS_REQUEST comm::InterfaceKey(0x00030000, 0x0001, 0x6000, 0x0000, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00)
#define STRING_IFC_KEY_SERVMNGT_EXTENSIONS_SYSTEMEVENTS_REQUEST ipl::string("00030000-0001-6000-0000-000200000000")

// Interface UUID as string
// NOTE: Using this UUID representation needs more performance, use the binary representation
#define STRING_UUID_SERVMNGT_EXTENSIONS_SYSTEMEVENTS_REPLY ipl::string("df50787c-06eb-4f9e-aed0-ad7551efc2f0")
// Interface UUID as binary
#define BINARY_UUID_SERVMNGT_EXTENSIONS_SYSTEMEVENTS_REPLY ipl::UUID(0xdf50787c, 0x06eb, 0x4f9e, 0xaed0, 0xad, 0x75, 0x51, 0xef, 0xc2, 0xf0)
// semver encoded as a UUID (non standard version 6)
#define BINARY_IFC_KEY_SERVMNGT_EXTENSIONS_SYSTEMEVENTS_REPLY comm::InterfaceKey(0x00030000, 0x0001, 0x6000, 0x0000, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00)
#define STRING_IFC_KEY_SERVMNGT_EXTENSIONS_SYSTEMEVENTS_REPLY ipl::string("00030000-0001-6000-0000-000200000000")

// Interface UUID as string
// NOTE: Using this UUID representation needs more performance, use the binary representation
#define STRING_UUID_SERVMNGT_EXTENSIONS_SERVICEMANAGEREVENTS_REQUEST ipl::string("adc5f968-ca05-4ac9-b559-2e3ebd4c8ff5")
// Interface UUID as binary
#define BINARY_UUID_SERVMNGT_EXTENSIONS_SERVICEMANAGEREVENTS_REQUEST ipl::UUID(0xadc5f968, 0xca05, 0x4ac9, 0xb559, 0x2e, 0x3e, 0xbd, 0x4c, 0x8f, 0xf5)
// semver encoded as a UUID (non standard version 6)
#define BINARY_IFC_KEY_SERVMNGT_EXTENSIONS_SERVICEMANAGEREVENTS_REQUEST comm::InterfaceKey(0x00030000, 0x0001, 0x6000, 0x0000, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00)
#define STRING_IFC_KEY_SERVMNGT_EXTENSIONS_SERVICEMANAGEREVENTS_REQUEST ipl::string("00030000-0001-6000-0000-000100000000")

// Interface UUID as string
// NOTE: Using this UUID representation needs more performance, use the binary representation
#define STRING_UUID_SERVMNGT_EXTENSIONS_SERVICEMANAGEREVENTS_REPLY ipl::string("dc663330-ba61-4861-bc40-17f5e253d13f")
// Interface UUID as binary
#define BINARY_UUID_SERVMNGT_EXTENSIONS_SERVICEMANAGEREVENTS_REPLY ipl::UUID(0xdc663330, 0xba61, 0x4861, 0xbc40, 0x17, 0xf5, 0xe2, 0x53, 0xd1, 0x3f)
// semver encoded as a UUID (non standard version 6)
#define BINARY_IFC_KEY_SERVMNGT_EXTENSIONS_SERVICEMANAGEREVENTS_REPLY comm::InterfaceKey(0x00030000, 0x0001, 0x6000, 0x0000, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00)
#define STRING_IFC_KEY_SERVMNGT_EXTENSIONS_SERVICEMANAGEREVENTS_REPLY ipl::string("00030000-0001-6000-0000-000100000000")

} }  // end of module namespace(s)

// Serialization and Deserialization of all enums
namespace util { namespace serializer {
            inline bool serialize(IStructuredSerializer& s, const servmngt::extensions::SuspendRequest  e)
            {
                int32_t value = int32_t(e);

                if ((value < 0) ||
                    (value > 2))
                {
                    // illegal value
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "SuspendRequest");
                    return true;
                }
                return s.putEnum(value, 32);
            }

            inline bool deserialize(IStructuredPullDeserializer& s, servmngt::extensions::SuspendRequest & e)
            {
                int32_t value;
                bool error = s.getEnum(value, 32, false /*unsigned */);
                if (!error) {
                    if ((value < 0) ||
                        (value > 2))
                    {
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "SuspendRequest");
                        return true;
                    }
                    e = (servmngt::extensions::SuspendRequest) value;
                }
                return error;
            }
            inline bool serialize(IStructuredSerializer& s, const servmngt::extensions::ServiceManagerEventType  e)
            {
                int32_t value = int32_t(e);

                if ((value < 0) ||
                    (value > 0))
                {
                    // illegal value
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "ServiceManagerEventType");
                    return true;
                }
                return s.putEnum(value, 32);
            }

            inline bool deserialize(IStructuredPullDeserializer& s, servmngt::extensions::ServiceManagerEventType & e)
            {
                int32_t value;
                bool error = s.getEnum(value, 32, false /*unsigned */);
                if (!error) {
                    if ((value < 0) ||
                        (value > 0))
                    {
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "ServiceManagerEventType");
                        return true;
                    }
                    e = (servmngt::extensions::ServiceManagerEventType) value;
                }
                return error;
            }
} } // namespace util::serializer

namespace servmngt
{
namespace extensions
{
    // enum array factory for servmngt::extensions::ServiceManagerEventType
    typedef CIFactory< servmngt::extensions::ServiceManagerEventType > CIServiceManagerEventTypeArrayFactory;
}// namespace servmngt
}// namespace extensions

#endif  // SERVMNGT_EXTENSIONS_DEFINITIONS_HXX
