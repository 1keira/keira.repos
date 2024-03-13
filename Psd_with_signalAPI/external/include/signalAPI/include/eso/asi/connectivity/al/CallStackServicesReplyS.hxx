/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceReplyS_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_CALLSTACKSERVICES_REPLYS_HXX
#define ASI_CONNECTIVITY_AL_CALLSTACKSERVICES_REPLYS_HXX
#include <ipl_config.h>
#include <comm/commidltypes.hxx>
#include <asi/connectivity/al/StructCallStackEntry.hxx>
#include <asi/connectivity/al/Definitions.hxx>
namespace asi
{
namespace connectivity
{
namespace al
{

    /**
    \brief  Interface declaration, which is implemented by the proxy, and used/called by any user of this interface
    **/
    class CallStackServicesReplyS
    {
    public:
        // List of reply methods
            /**
            updCallStackSourceAvailable Method ID: 3
            **/
        virtual bool updCallStackSourceAvailable (
            const int64_t btAddress,
            const bool available
        ) IPL_NOEXCEPT = 0;

            /**
            updNewCallStackEntries Method ID: 4
            **/
        virtual bool updNewCallStackEntries (
            const int64_t btAddress,
            const asi::connectivity::al::CallStackType type,
            const CIPtr< CIPtrArray< asi::connectivity::al::CallStackEntry > >& entries,
            const int32_t undismissed_missed_calls,
            const CIPtr< CIString >& stored_version
        ) IPL_NOEXCEPT = 0;

            /**
            updCallStackDownloadStatus Method ID: 2
            **/
        virtual bool updCallStackDownloadStatus (
            const int64_t btAddress,
            const asi::connectivity::al::CallStackType type,
            const asi::connectivity::al::CallStackDownloadStatus result
        ) IPL_NOEXCEPT = 0;

        virtual ~CallStackServicesReplyS() {}
    };

}// namespace asi
}// namespace connectivity
}// namespace al


#endif// ASI_CONNECTIVITY_AL_CALLSTACKSERVICES_REPLYS_HXX
