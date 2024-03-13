/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template ModuleDefinitions_hxx.tmpl
*/
#ifndef PERSISTENCE_DEFINITIONS_HXX
#define PERSISTENCE_DEFINITIONS_HXX

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

namespace persistence { 
    /**
        Importance classification, results in a "reasonable" timeout
    */
    const int32_t ESSENTIAL_VALUE = -1L;
    /**
        Importance classification, results in a "eternal" timeout
    */
    const int32_t DISPENSABLE_VALUE = -2L;
    // persistence
    enum RequestStatus {

        /*
        No error, guaranteed to evaluate false
        */
        PERS_STATUS_OK = 0,
        /*
        The system underlying the persistence service is not initialized
        */
        PERS_STATUS_NO_ENGINE = 1,
        /*
        Partition versions don't match
        */
        PERS_STATUS_VERSION_MISMATCH = 2,
        /*
        Data types don't match
        */
        PERS_STATUS_TYPE_MISMATCH = 3,
        /*
        The partition handle is not currently open
        */
        PERS_STATUS_INVALID_HANDLE = 4,
        /*
        The partition number/name, partition profile or key is invalid
        */
        PERS_STATUS_INVALID_NAME = 5,
        /*
        The partition or key does not exist
        */
        PERS_STATUS_DOES_NOT_EXIST = 6,
        /*
        Cannot purge/convert/copy, the partition is still open
        */
        PERS_STATUS_IN_USE = 7,
        /*
        Cannot write, there is no transaction pending
        */
        PERS_STATUS_NO_TRANSACTION = 8,
        /*
        Some underlying mechanisms have failed,
                   check the services' traces for debugging info
        */
        PERS_STATUS_FAILED = 9,
        /*
        We're not subscribed for the element
        */
        PERS_STATUS_NOT_SUBSCRIBED = 10,
        /*
        The timeout value is neither a time nor a valid importance
        */
        PERS_STATUS_INVALID_TIMEOUT = 11,
        /*
        Request couldn't be completed before some timeout
        */
        PERS_STATUS_TIMEOUT = 12,
        /*
        Multiple identical requests issued, only one will be performed
        */
        PERS_STATUS_REDUNDANT_REQUEST_REJECTED = 13,
        /*
        Service ressources depleted, request rejected
        */
        PERS_STATUS_OVERLOAD = 14,
        /*
        There is already a transaction pending on this partition
        */
        PERS_STATUS_TRANSACTION_PENDING = 15,
        /*
        The value exeeded some configured limit
        */
        PERS_STATUS_VALUE_TOO_BIG = 16,
        /*
        Some parameter is NULL, illegaly
        */
        PERS_STATUS_NULL_ARGUMENT = 17
    };

// Module Version
#define PERSISTENCE_VERSION ipl::string("1.4.0")
#define PERSISTENCE_VERSION_MAJOR 1
#define PERSISTENCE_VERSION_MINOR 4
#define PERSISTENCE_VERSION_PATCHLEVEL 0

// Module without version
#define PERSISTENCE_VERSION_FREE_NAMESPACE ipl::string("persistence")

// Interface Version
#define PERSISTENCE_IPERSISTENCEA_VERSION_MAJOR 1
#define PERSISTENCE_IPERSISTENCEA_VERSION_MINOR 4
#define PERSISTENCE_IPERSISTENCEA_VERSION_PATCHLEVEL 0
#define PERSISTENCE_IPERSISTENCEB_VERSION_MAJOR 1
#define PERSISTENCE_IPERSISTENCEB_VERSION_MINOR 1
#define PERSISTENCE_IPERSISTENCEB_VERSION_PATCHLEVEL 0

// Interface UUID as string
// NOTE: Using this UUID representation needs more performance, use the binary representation
#define STRING_UUID_PERSISTENCE_IPERSISTENCEA_REQUEST ipl::string("03171582-f255-4991-b8ae-83f90521c08b")
// Interface UUID as binary
#define BINARY_UUID_PERSISTENCE_IPERSISTENCEA_REQUEST ipl::UUID(0x03171582, 0xf255, 0x4991, 0xb8ae, 0x83, 0xf9, 0x05, 0x21, 0xc0, 0x8b)
// semver encoded as a UUID (non standard version 6)
#define BINARY_IFC_KEY_PERSISTENCE_IPERSISTENCEA_REQUEST comm::InterfaceKey(0x00010004, 0x0000, 0x6000, 0x0000, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00)
#define STRING_IFC_KEY_PERSISTENCE_IPERSISTENCEA_REQUEST ipl::string("00010004-0000-6000-0000-000100040000")

// Interface UUID as string
// NOTE: Using this UUID representation needs more performance, use the binary representation
#define STRING_UUID_PERSISTENCE_IPERSISTENCEA_REPLY ipl::string("f4ac6df9-a35a-4f1c-a334-9c2890a41c09")
// Interface UUID as binary
#define BINARY_UUID_PERSISTENCE_IPERSISTENCEA_REPLY ipl::UUID(0xf4ac6df9, 0xa35a, 0x4f1c, 0xa334, 0x9c, 0x28, 0x90, 0xa4, 0x1c, 0x09)
// semver encoded as a UUID (non standard version 6)
#define BINARY_IFC_KEY_PERSISTENCE_IPERSISTENCEA_REPLY comm::InterfaceKey(0x00010004, 0x0000, 0x6000, 0x0000, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00)
#define STRING_IFC_KEY_PERSISTENCE_IPERSISTENCEA_REPLY ipl::string("00010004-0000-6000-0000-000100040000")

// Interface UUID as string
// NOTE: Using this UUID representation needs more performance, use the binary representation
#define STRING_UUID_PERSISTENCE_IPERSISTENCEB_REQUEST ipl::string("08914f70-1547-4921-989c-2d6ff58d5654")
// Interface UUID as binary
#define BINARY_UUID_PERSISTENCE_IPERSISTENCEB_REQUEST ipl::UUID(0x08914f70, 0x1547, 0x4921, 0x989c, 0x2d, 0x6f, 0xf5, 0x8d, 0x56, 0x54)
// semver encoded as a UUID (non standard version 6)
#define BINARY_IFC_KEY_PERSISTENCE_IPERSISTENCEB_REQUEST comm::InterfaceKey(0x00010004, 0x0000, 0x6000, 0x0000, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00)
#define STRING_IFC_KEY_PERSISTENCE_IPERSISTENCEB_REQUEST ipl::string("00010004-0000-6000-0000-000100010000")

// Interface UUID as string
// NOTE: Using this UUID representation needs more performance, use the binary representation
#define STRING_UUID_PERSISTENCE_IPERSISTENCEB_REPLY ipl::string("6bb15b15-db1e-486d-8120-6367064b279a")
// Interface UUID as binary
#define BINARY_UUID_PERSISTENCE_IPERSISTENCEB_REPLY ipl::UUID(0x6bb15b15, 0xdb1e, 0x486d, 0x8120, 0x63, 0x67, 0x06, 0x4b, 0x27, 0x9a)
// semver encoded as a UUID (non standard version 6)
#define BINARY_IFC_KEY_PERSISTENCE_IPERSISTENCEB_REPLY comm::InterfaceKey(0x00010004, 0x0000, 0x6000, 0x0000, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00)
#define STRING_IFC_KEY_PERSISTENCE_IPERSISTENCEB_REPLY ipl::string("00010004-0000-6000-0000-000100010000")

}  // end of module namespace(s)

// Serialization and Deserialization of all enums
namespace util { namespace serializer {
            inline bool serialize(IStructuredSerializer& s, const persistence::RequestStatus  e)
            {
                int32_t value = int32_t(e);

                if ((value < 0) ||
                    (value > 17))
                {
                    // illegal value
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "RequestStatus");
                    return true;
                }
                return s.putEnum(value, 32);
            }

            inline bool deserialize(IStructuredPullDeserializer& s, persistence::RequestStatus & e)
            {
                int32_t value;
                bool error = s.getEnum(value, 32, false /*unsigned */);
                if (!error) {
                    if ((value < 0) ||
                        (value > 17))
                    {
                        ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "RequestStatus");
                        return true;
                    }
                    e = (persistence::RequestStatus) value;
                }
                return error;
            }
} } // namespace util::serializer

namespace persistence
{
    // enum array factory for persistence::RequestStatus
    typedef CIFactory< persistence::RequestStatus > CIRequestStatusArrayFactory;
}// namespace persistence

#endif  // PERSISTENCE_DEFINITIONS_HXX
