/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceReplyS_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_OOC_POWERMANAGEMENTSERVICE_REPLYS_HXX
#define ASI_CONNECTIVITY_OOC_POWERMANAGEMENTSERVICE_REPLYS_HXX
#include <ipl_config.h>
#include <comm/commidltypes.hxx>
#include <asi/connectivity/ooc/Definitions.hxx>
namespace asi
{
namespace connectivity
{
namespace ooc
{

    /**
    \brief  Interface declaration, which is implemented by the proxy, and used/called by any user of this interface
    **/
    class PowerManagementServiceReplyS
    {
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
        virtual bool responseClusterActiveBits (
            const uint64_t clusterActiveBits,
            const uint16_t activationCause,
            const uint64_t counter
        ) IPL_NOEXCEPT = 0;

            /**
            *
         *    Broadcast the current partition keep alive status
         *
         *    @param alive: current partition keep alive status
         *    @param activationCause: reason to stay alive
         *    @param counter: running counter to map request and response 
         
            responsePartitionKeepAlive Method ID: 4
            **/
        virtual bool responsePartitionKeepAlive (
            const bool alive,
            const uint16_t activationCause,
            const uint64_t counter
        ) IPL_NOEXCEPT = 0;

            /**
            *
         *    Broadcast the current process keep alive status
         *
         *    @param alive: current process keep alive status
         *    @param activationCause: reason to stay alive
         *    @param counter: running counter to map request and response
         
            responseProcessKeepAlive Method ID: 5
            **/
        virtual bool responseProcessKeepAlive (
            const bool alive,
            const uint16_t activationCause,
            const uint64_t counter
        ) IPL_NOEXCEPT = 0;

        virtual ~PowerManagementServiceReplyS() {}
    };

}// namespace asi
}// namespace connectivity
}// namespace ooc


#endif// ASI_CONNECTIVITY_OOC_POWERMANAGEMENTSERVICE_REPLYS_HXX
