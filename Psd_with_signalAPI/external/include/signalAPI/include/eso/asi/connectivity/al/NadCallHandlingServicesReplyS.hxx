/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceReplyS_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_NADCALLHANDLINGSERVICES_REPLYS_HXX
#define ASI_CONNECTIVITY_AL_NADCALLHANDLINGSERVICES_REPLYS_HXX
#include <ipl_config.h>
#include <comm/commidltypes.hxx>
#include <asi/connectivity/al/StructCallStatus.hxx>
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
    class NadCallHandlingServicesReplyS
    {
    public:
        // List of reply methods
            /**
            acceptCallResponse Method ID: 1
            **/
        virtual bool acceptCallResponse (
            const asi::connectivity::al::ResultType result
        ) IPL_NOEXCEPT = 0;

            /**
            dialNumberResponse Method ID: 3
            **/
        virtual bool dialNumberResponse (
            const asi::connectivity::al::ResultType result
        ) IPL_NOEXCEPT = 0;

            /**
            hangupCallResponse Method ID: 5
            **/
        virtual bool hangupCallResponse (
            const asi::connectivity::al::ResultType result
        ) IPL_NOEXCEPT = 0;

            /**
            updCallStatus Method ID: 8
            **/
        virtual bool updCallStatus (
            const CIPtr< CIPtrArray< asi::connectivity::al::CallStatus > >& states
        ) IPL_NOEXCEPT = 0;

            /**
            *
        *@param callId The ID of the call, which got disconnected.
        *@param ccCause The cause value for call control according to ETSI TS 124 008.
        *@param endStatus The call end status as reported by the Huawei M2M SDK.
        
            updCallDisconnected Method ID: 7
            **/
        virtual bool updCallDisconnected (
            const int32_t callId,
            const int32_t ccCause,
            const int32_t endStatus
        ) IPL_NOEXCEPT = 0;

        virtual ~NadCallHandlingServicesReplyS() {}
    };

}// namespace asi
}// namespace connectivity
}// namespace al


#endif// ASI_CONNECTIVITY_AL_NADCALLHANDLINGSERVICES_REPLYS_HXX
