/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleModuleDefinitions_hxx.tmpl
*/
#ifndef SERVMNGT_DEFINITIONS_CSTYLE_HXX
#define SERVMNGT_DEFINITIONS_CSTYLE_HXX

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

namespace servmngt { namespace cstyle {
    const uint32_t DEFAULT_TIMEOUT_PERIOD = 5000UL;
    const uint32_t WD_MIN_PERIOD = 1000UL;
    const uint32_t WD_MAX_PERIOD = 60000UL;
    /**
        
    \brief    system-runmode for an application. It's requested by
            the service-manager and has to be acknowledged
            
    
    */
    enum SystemRunMode {

        SYS_RM_NORMAL = 0,
        SYS_RM_DOWNLOAD = 1,
        SYS_RM_DIAGNOSIS = 2
    };
    enum PersistenceAccessMode {

        PS_ACC_NONE = 0,
        PS_ACC_READ = 1,
        PS_ACC_READ_WRITE = 2,
        PS_ACC_UNCHANGED = 3
    };
    /**
        
    \brief
        result for a requestUserCommand() call, which is reported
        via userCommandDone()
    
    */
    enum UserCommandResult {

        /*
        !
                The user command was successfully performed
        */
        USER_COMMAND_OK = 0,
        /*
        !
                The user command was not found in the servicemgr_usercommands.json file,
                or it's no array of commands or the file itself was not found
        */
        USER_COMMAND_NOT_FOUND = 1,
        /*
        !
                One or more of the jobs in the command-list failed
        */
        USER_COMMAND_JOB_FAILED = 2
    };
    /**
        
    \brief    system events which can be sent to applications
    
    */
    enum SystemEvent {

        /*
        \brief    a low-memory situation was detected in the system
        */
        SYS_EVENT_LOWMEM = 0,
        /*
        \brief    the system startup is completed
        */
        SYS_EVENT_STARTUP_COMPLETE = 1
    };
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
    /**
        
    The application states.
    See the framework user guide for a detailed description of these states.
   
    */
    enum AppState {

        AS_UNDEFINED = 0,
        AS_INITIALIZING = 1,
        AS_INITIALIZED = 2,
        AS_RUNNING = 3,
        AS_STOPPING = 4,
        AS_STOPPED = 5,
        AS_LOADING = 6,
        AS_FAILED = 7,
        AS_DIED = 8
    };
    enum LoaderResult {

        LR_OK = 0,
        LR_ERR_BUNDLE_NOT_LOADABLE = 1,
        LR_ERR_APP_INIT_FAILED = 2
    };

// Module Version
#define SERVMNGT_VERSION ipl::string("3.3.0")
#define SERVMNGT_VERSION_MAJOR 3
#define SERVMNGT_VERSION_MINOR 3
#define SERVMNGT_VERSION_PATCHLEVEL 0

// Module without version
#define SERVMNGT_VERSION_FREE_NAMESPACE ipl::string("servmngt")

// Interface Version
#define SERVMNGT_ISERVICEMANAGER_VERSION_MAJOR 1
#define SERVMNGT_ISERVICEMANAGER_VERSION_MINOR 1
#define SERVMNGT_ISERVICEMANAGER_VERSION_PATCHLEVEL 0

// Interface UUID as string
// NOTE: Using this UUID representation needs more performance, use the binary representation
#define STRING_UUID_SERVMNGT_ISERVICEMANAGER_REQUEST ipl::string("63bb63cc-9f4c-450e-95f2-55c4f5de53a2")
// Interface UUID as binary
#define BINARY_UUID_SERVMNGT_ISERVICEMANAGER_REQUEST ipl::UUID(0x63bb63cc, 0x9f4c, 0x450e, 0x95f2, 0x55, 0xc4, 0xf5, 0xde, 0x53, 0xa2)
// Interface UUID as string
// NOTE: Using this UUID representation needs more performance, use the binary representation
#define STRING_UUID_SERVMNGT_ISERVICEMANAGER_REPLY ipl::string("4fa1af1b-ecb1-4603-85e0-c82cf4d98108")
// Interface UUID as binary
#define BINARY_UUID_SERVMNGT_ISERVICEMANAGER_REPLY ipl::UUID(0x4fa1af1b, 0xecb1, 0x4603, 0x85e0, 0xc8, 0x2c, 0xf4, 0xd9, 0x81, 0x08)

} //  end of namespace cstyle
}  // end of module namespace(s)

// Streaming operators for all enums arrays
namespace util { namespace serializer {
// Streaming operators for all enum arrays

        inline bool serialize(IStructuredSerializer& s, const servmngt::cstyle::SystemRunMode  e)
        {
            int32_t value = int32_t(e);

            if ((value < 0) ||
                (value > 2))
            {
                ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "SystemRunMode");
                return true;
            }
            return s.putEnum(value, 32);
        }

        inline bool deserialize(IStructuredPullDeserializer& s, servmngt::cstyle::SystemRunMode & e)
        {
            int32_t value;
            bool error = s.getEnum(value, 32, false /*unsigned */);
            if (!error) {
                if ((value < 0) ||
                    (value > 2))
                {
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "SystemRunMode");
                    return true;
                }
                e = (servmngt::cstyle::SystemRunMode) value;
            }
            return error;
        }


        inline bool serialize(IStructuredSerializer& s, const servmngt::cstyle::PersistenceAccessMode  e)
        {
            int32_t value = int32_t(e);

            if ((value < 0) ||
                (value > 3))
            {
                ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "PersistenceAccessMode");
                return true;
            }
            return s.putEnum(value, 32);
        }

        inline bool deserialize(IStructuredPullDeserializer& s, servmngt::cstyle::PersistenceAccessMode & e)
        {
            int32_t value;
            bool error = s.getEnum(value, 32, false /*unsigned */);
            if (!error) {
                if ((value < 0) ||
                    (value > 3))
                {
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "PersistenceAccessMode");
                    return true;
                }
                e = (servmngt::cstyle::PersistenceAccessMode) value;
            }
            return error;
        }


        inline bool serialize(IStructuredSerializer& s, const servmngt::cstyle::UserCommandResult  e)
        {
            int32_t value = int32_t(e);

            if ((value < 0) ||
                (value > 2))
            {
                ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "UserCommandResult");
                return true;
            }
            return s.putEnum(value, 32);
        }

        inline bool deserialize(IStructuredPullDeserializer& s, servmngt::cstyle::UserCommandResult & e)
        {
            int32_t value;
            bool error = s.getEnum(value, 32, false /*unsigned */);
            if (!error) {
                if ((value < 0) ||
                    (value > 2))
                {
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "UserCommandResult");
                    return true;
                }
                e = (servmngt::cstyle::UserCommandResult) value;
            }
            return error;
        }


        inline bool serialize(IStructuredSerializer& s, const servmngt::cstyle::SystemEvent  e)
        {
            int32_t value = int32_t(e);

            if ((value < 0) ||
                (value > 1))
            {
                ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "SystemEvent");
                return true;
            }
            return s.putEnum(value, 32);
        }

        inline bool deserialize(IStructuredPullDeserializer& s, servmngt::cstyle::SystemEvent & e)
        {
            int32_t value;
            bool error = s.getEnum(value, 32, false /*unsigned */);
            if (!error) {
                if ((value < 0) ||
                    (value > 1))
                {
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "SystemEvent");
                    return true;
                }
                e = (servmngt::cstyle::SystemEvent) value;
            }
            return error;
        }


        inline bool serialize(IStructuredSerializer& s, const servmngt::cstyle::SuspendRequest  e)
        {
            int32_t value = int32_t(e);

            if ((value < 0) ||
                (value > 2))
            {
                ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "SuspendRequest");
                return true;
            }
            return s.putEnum(value, 32);
        }

        inline bool deserialize(IStructuredPullDeserializer& s, servmngt::cstyle::SuspendRequest & e)
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
                e = (servmngt::cstyle::SuspendRequest) value;
            }
            return error;
        }


        inline bool serialize(IStructuredSerializer& s, const servmngt::cstyle::AppState  e)
        {
            int32_t value = int32_t(e);

            if ((value < 0) ||
                (value > 8))
            {
                ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "AppState");
                return true;
            }
            return s.putEnum(value, 32);
        }

        inline bool deserialize(IStructuredPullDeserializer& s, servmngt::cstyle::AppState & e)
        {
            int32_t value;
            bool error = s.getEnum(value, 32, false /*unsigned */);
            if (!error) {
                if ((value < 0) ||
                    (value > 8))
                {
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "AppState");
                    return true;
                }
                e = (servmngt::cstyle::AppState) value;
            }
            return error;
        }


        inline bool serialize(IStructuredSerializer& s, const servmngt::cstyle::LoaderResult  e)
        {
            int32_t value = int32_t(e);

            if ((value < 0) ||
                (value > 2))
            {
                ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "LoaderResult");
                return true;
            }
            return s.putEnum(value, 32);
        }

        inline bool deserialize(IStructuredPullDeserializer& s, servmngt::cstyle::LoaderResult & e)
        {
            int32_t value;
            bool error = s.getEnum(value, 32, false /*unsigned */);
            if (!error) {
                if ((value < 0) ||
                    (value > 2))
                {
                    ipl_raise( serializer::Error, SerializerErrors::ILLEGAL_ENUM_VALUE, value, "LoaderResult");
                    return true;
                }
                e = (servmngt::cstyle::LoaderResult) value;
            }
            return error;
        }


} } // namespace util::serializer

#endif  // SERVMNGT_DEFINITIONS_CSTYLE_HXX
