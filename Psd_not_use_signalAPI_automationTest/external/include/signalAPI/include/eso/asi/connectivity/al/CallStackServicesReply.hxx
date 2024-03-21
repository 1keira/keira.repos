/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceReply_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_CALLSTACKSERVICESREPLY_HXX
#define ASI_CONNECTIVITY_AL_CALLSTACKSERVICESREPLY_HXX

#include <comm/commtypes.hxx>
#include <comm/commidltypes.hxx>
#include <comm/CallEvent.hxx>
#include <asi/connectivity/al/StructCallStackEntry.hxx>
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
    class CallStackServicesReply {

    public:
    // List of reply methods
            /**
            updCallStackSourceAvailable Method ID: 3
            **/
        virtual void updCallStackSourceAvailable(
            const int64_t btAddress,
            const bool available
        ) = 0;
            /**
            updNewCallStackEntries Method ID: 4
            **/
        virtual void updNewCallStackEntries(
            const int64_t btAddress,
            const asi::connectivity::al::CallStackType type,
            const CIPtr< CIPtrArray< asi::connectivity::al::CallStackEntry > >& entries,
            const int32_t undismissed_missed_calls,
            const CIPtr< CIString >& stored_version
        ) = 0;
            /**
            updCallStackDownloadStatus Method ID: 2
            **/
        virtual void updCallStackDownloadStatus(
            const int64_t btAddress,
            const asi::connectivity::al::CallStackType type,
            const asi::connectivity::al::CallStackDownloadStatus result
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
        updCallStackSourceAvailableCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<CallStackServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 3;
            ce.assign(inst, mid);
        }

        void
        updNewCallStackEntriesCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<CallStackServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 4;
            ce.assign(inst, mid);
        }

        void
        updCallStackDownloadStatusCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<CallStackServicesReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 2;
            ce.assign(inst, mid);
        }


        virtual ~CallStackServicesReply() {}
    };

}//namespace asi
}//namespace connectivity
}//namespace al

#endif// ASI_CONNECTIVITY_AL_CALLSTACKSERVICESREPLY_HXX
