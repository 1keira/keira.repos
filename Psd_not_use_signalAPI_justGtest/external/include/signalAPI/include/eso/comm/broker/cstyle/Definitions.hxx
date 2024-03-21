/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleModuleDefinitions_hxx.tmpl
*/
#ifndef COMM_BROKER_DEFINITIONS_CSTYLE_HXX
#define COMM_BROKER_DEFINITIONS_CSTYLE_HXX

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

namespace comm { namespace broker { namespace cstyle {
    enum ServiceReason {

        NORMAL_OPERATION = 0,
        DUPLICATE_INSTANCEID = 1,
        INVALID_INSTANCEID = 2,
        CONNECTION_LOST = 3,
        INTERFACE_KEY_MISMATCH = 4,
        OOM = 5,
        SERVICE_NOT_AVAILABLE = 6,
        FACTORY_NOT_FOUND = 7,
        ID_POOL_EXHAUSTED = 8,
        OBJECT_IS_DEAD = 9,
        PROXY_IS_INVALID = 10,
        INVALID_AGENT_ID = 11,
        AGENT_IN_SHUTDOWN = 12,
        INTERNAL_ERROR = 13
    };
    enum ServiceAction {

        SERVICE_REGISTERED = 0,
        SERVICE_UNREGISTERED = 1,
        SERVICE_NOT_REGISTERED = 2
    };

// Module Version
#define COMM_BROKER_VERSION ipl::string("4.0.1")
#define COMM_BROKER_VERSION_MAJOR 4
#define COMM_BROKER_VERSION_MINOR 0
#define COMM_BROKER_VERSION_PATCHLEVEL 1

// Module without version
#define COMM_BROKER_VERSION_FREE_NAMESPACE ipl::string("comm.broker")

// Interface Version
#define COMM_BROKER_BROKER_VERSION_MAJOR 3
#define COMM_BROKER_BROKER_VERSION_MINOR 0
#define COMM_BROKER_BROKER_VERSION_PATCHLEVEL 0
#define COMM_BROKER_AGENT_VERSION_MAJOR 4
#define COMM_BROKER_AGENT_VERSION_MINOR 0
#define COMM_BROKER_AGENT_VERSION_PATCHLEVEL 0

// Interface UUID as string
// NOTE: Using this UUID representation needs more performance, use the binary representation
#define STRING_UUID_COMM_BROKER_BROKER_REQUEST ipl::string("8d4f7cec-be0c-49b7-b1b6-1e3e4c26b847")
// Interface UUID as binary
#define BINARY_UUID_COMM_BROKER_BROKER_REQUEST ipl::UUID(0x8d4f7cec, 0xbe0c, 0x49b7, 0xb1b6, 0x1e, 0x3e, 0x4c, 0x26, 0xb8, 0x47)

// Interface UUID as string
// NOTE: Using this UUID representation needs more performance, use the binary representation
#define STRING_UUID_COMM_BROKER_AGENT_REQUEST ipl::string("78a07e56-255a-4309-8bde-b1e1c73bc71c")
// Interface UUID as binary
#define BINARY_UUID_COMM_BROKER_AGENT_REQUEST ipl::UUID(0x78a07e56, 0x255a, 0x4309, 0x8bde, 0xb1, 0xe1, 0xc7, 0x3b, 0xc7, 0x1c)

} //  end of namespace cstyle
} }  // end of module namespace(s)

// Streaming operators for all enums arrays
namespace util { namespace serializer {
// Streaming operators for all enum arrays

        inline bool serialize(IStructuredSerializer& s, const comm::broker::cstyle::ServiceReason  e)
        {
            int32_t value = int32_t(e);

            if ((value < 0) ||
                (value > 13))
            {
                ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "ServiceReason");
                return true;
            }
            return s.putEnum(value, 32);
        }

        inline bool deserialize(IStructuredPullDeserializer& s, comm::broker::cstyle::ServiceReason & e)
        {
            int32_t value;
            bool error = s.getEnum(value, 32, false /*unsigned */);
            if (!error) {
                if ((value < 0) ||
                    (value > 13))
                {
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "ServiceReason");
                    return true;
                }
                e = (comm::broker::cstyle::ServiceReason) value;
            }
            return error;
        }


        inline bool serialize(IStructuredSerializer& s, const comm::broker::cstyle::ServiceAction  e)
        {
            int32_t value = int32_t(e);

            if ((value < 0) ||
                (value > 2))
            {
                ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "ServiceAction");
                return true;
            }
            return s.putEnum(value, 32);
        }

        inline bool deserialize(IStructuredPullDeserializer& s, comm::broker::cstyle::ServiceAction & e)
        {
            int32_t value;
            bool error = s.getEnum(value, 32, false /*unsigned */);
            if (!error) {
                if ((value < 0) ||
                    (value > 2))
                {
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "ServiceAction");
                    return true;
                }
                e = (comm::broker::cstyle::ServiceAction) value;
            }
            return error;
        }


} } // namespace util::serializer

#endif  // COMM_BROKER_DEFINITIONS_CSTYLE_HXX
