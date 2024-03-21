/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceReply_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_OOC_POWERMANAGEMENTSERVICEREPLY_HXX
#define ASI_CONNECTIVITY_OOC_POWERMANAGEMENTSERVICEREPLY_HXX

#include <comm/commtypes.hxx>
#include <comm/commidltypes.hxx>
#include <comm/CallEvent.hxx>
#include <asi/connectivity/ooc/Definitions.hxx>

namespace asi
{
namespace connectivity
{
namespace ooc
{

    /**
    \brief  Declaration of the reply interface, which must be implemented by any user of this interface
    **/
    class PowerManagementServiceReply {

    public:
    // List of reply methods
            /**
            *
         *    Broadcast the current set of cluster active bits with the corresponding activation cause
         *
         *    @param clusterActiveBits: set of ECU's that are currently kept alive
         *    @param activationCause: reason to stay alive
         *    @param counter: running counter to map request and response  
         
            responseClusterActiveBits Method ID: 3
            **/
        virtual void responseClusterActiveBits(
            const uint64_t clusterActiveBits,
            const uint16_t activationCause,
            const uint64_t counter
        ) = 0;
            /**
            *
         *    Broadcast the current partition keep alive status
         *
         *    @param alive: current partition keep alive status
         *    @param activationCause: reason to stay alive
         *    @param counter: running counter to map request and response 
         
            responsePartitionKeepAlive Method ID: 4
            **/
        virtual void responsePartitionKeepAlive(
            const bool alive,
            const uint16_t activationCause,
            const uint64_t counter
        ) = 0;
            /**
            *
         *    Broadcast the current process keep alive status
         *
         *    @param alive: current process keep alive status
         *    @param activationCause: reason to stay alive
         *    @param counter: running counter to map request and response
         
            responseProcessKeepAlive Method ID: 5
            **/
        virtual void responseProcessKeepAlive(
            const bool alive,
            const uint16_t activationCause,
            const uint64_t counter
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
        responseClusterActiveBitsCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<PowerManagementServiceReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 3;
            ce.assign(inst, mid);
        }

        void
        responsePartitionKeepAliveCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<PowerManagementServiceReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 4;
            ce.assign(inst, mid);
        }

        void
        responseProcessKeepAliveCallID( comm::CallEvent::CallID& ce )
        {
            void* inst=static_cast<PowerManagementServiceReply*>(this);
            // Don't ever rely on these values outside of a CallID
            comm::OpaqueMethodID mid= 5;
            ce.assign(inst, mid);
        }


        virtual ~PowerManagementServiceReply() {}
    };

}//namespace asi
}//namespace connectivity
}//namespace ooc

#endif// ASI_CONNECTIVITY_OOC_POWERMANAGEMENTSERVICEREPLY_HXX
