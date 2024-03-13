/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceReplyS_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_NADDATASERVICES_REPLYS_HXX
#define ASI_CONNECTIVITY_AL_NADDATASERVICES_REPLYS_HXX
#include <ipl_config.h>
#include <comm/commidltypes.hxx>
#include <asi/connectivity/al/StructDataConnectionInfo.hxx>
#include <asi/connectivity/al/StructSimDataConfig.hxx>
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
    class NadDataServicesReplyS
    {
    public:
        // List of reply methods
            /**
            *
         * Response for a request of Data Connection establishment/release.
         * @param dataConnectionId the identifier of the data connection the action is performed for.
         * @param result : the outcome of the performed action (if it has succeeded or the nature of error, if it failed)
         * @param backoffTimer : in case the failure is caused by the network rejection that requires a break between
         * attempts, the result will be RESULT_TYPE_ERROR_BACKOFF and a backoff timer value will be provided (in seconds)
         *
         
            requestDataConnectionResponse Method ID: 3
            **/
        virtual bool requestDataConnectionResponse (
            const int32_t dataConnectionId,
            const asi::connectivity::al::ResultType result,
            const uint64_t backoffTimer
        ) IPL_NOEXCEPT = 0;

            /**
            updateDataConnectionState Method ID: 10
            **/
        virtual bool updateDataConnectionState (
            const int32_t dataConnectionId,
            const asi::connectivity::al::DataConnectionState state,
            const int32_t reject_cause
        ) IPL_NOEXCEPT = 0;

            /**
            updateDataConnectionInfo Method ID: 9
            **/
        virtual bool updateDataConnectionInfo (
            const int32_t dataConnectionId,
            const CIPtr< asi::connectivity::al::DataConnectionInfo >& info
        ) IPL_NOEXCEPT = 0;

            /**
            bipRouteRequest Method ID: 0
            **/
        virtual bool bipRouteRequest (
            const bool add,
            const CIPtr< CIString >& interface_name,
            const CIPtr< CIString >& source_address,
            const CIPtr< CIString >& destination_address,
            const int32_t port,
            const bool is_ipv6
        ) IPL_NOEXCEPT = 0;

            /**
            setConfigurationResponse Method ID: 7
            **/
        virtual bool setConfigurationResponse (
            const int32_t reqId,
            const int32_t result
        ) IPL_NOEXCEPT = 0;

            /**
            requestPSReattachResponse Method ID: 5
            **/
        virtual bool requestPSReattachResponse (
            const asi::connectivity::al::ResultType result
        ) IPL_NOEXCEPT = 0;

        virtual ~NadDataServicesReplyS() {}
    };

}// namespace asi
}// namespace connectivity
}// namespace al


#endif// ASI_CONNECTIVITY_AL_NADDATASERVICES_REPLYS_HXX
