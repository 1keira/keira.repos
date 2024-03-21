/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceReply_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_NADDATASERVICESREPLY_HXX
#define ASI_CONNECTIVITY_AL_NADDATASERVICESREPLY_HXX

#include <comm/commtypes.hxx>
#include <comm/commidltypes.hxx>
#include <comm/CallEvent.hxx>
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
    \brief  Declaration of the reply interface, which must be implemented by any user of this interface
    **/
    class NadDataServicesReply {

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
        virtual void requestDataConnectionResponse(
            const int32_t dataConnectionId,
            const asi::connectivity::al::ResultType result,
            const uint64_t backoffTimer
        ) = 0;
            /**
            updateDataConnectionState Method ID: 10
            **/
        virtual void updateDataConnectionState(
            const int32_t dataConnectionId,
            const asi::connectivity::al::DataConnectionState state,
            const int32_t reject_cause
        ) = 0;
            /**
            updateDataConnectionInfo Method ID: 9
            **/
        virtual void updateDataConnectionInfo(
            const int32_t dataConnectionId,
            const CIPtr< asi::connectivity::al::DataConnectionInfo >& info
        ) = 0;
            /**
            bipRouteRequest Method ID: 0
            **/
        virtual void bipRouteRequest(
            const bool add,
            const CIPtr< CIString >& interface_name,
            const CIPtr< CIString >& source_address,
            const CIPtr< CIString >& destination_address,
            const int32_t port,
            const bool is_ipv6
        ) = 0;
            /**
            setConfigurationResponse Method ID: 7
            **/
        virtual void setConfigurationResponse(
            const int32_t reqId,
            const int32_t result
        ) = 0;
            /**
            requestPSReattachResponse Method ID: 5
            **/
        virtual void requestPSReattachResponse(
            const asi::connectivity::al::ResultType result
        ) = 0;

        /*!
        \brief Informs the service about a connected client
        \param count The number of connected clients
        */
        virtual void clientConnected(uint32_t count) {}

        /*!
        \brief Informs the service that a client disconnected
        \param count the number of connected clients
        */
        virtual void clientDisconnected(uint32_t count) {}

        // call ids
        void
        requestDataConnectionResponseCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NadDataServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 3;
            ce.assign(inst, mid);
        }

        void
        updateDataConnectionStateCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NadDataServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 10;
            ce.assign(inst, mid);
        }

        void
        updateDataConnectionInfoCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NadDataServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 9;
            ce.assign(inst, mid);
        }

        void
        bipRouteRequestCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NadDataServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 0;
            ce.assign(inst, mid);
        }

        void
        setConfigurationResponseCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NadDataServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 7;
            ce.assign(inst, mid);
        }

        void
        requestPSReattachResponseCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<NadDataServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 5;
            ce.assign(inst, mid);
        }


        virtual ~NadDataServicesReply() {}
    };

}//namespace asi
}//namespace connectivity
}//namespace al

#endif// ASI_CONNECTIVITY_AL_NADDATASERVICESREPLY_HXX
