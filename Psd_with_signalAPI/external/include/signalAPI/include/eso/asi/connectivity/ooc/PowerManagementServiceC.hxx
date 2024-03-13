/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceC_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_OOC_POWERMANAGEMENTSERVICEC_HXX
#define ASI_CONNECTIVITY_OOC_POWERMANAGEMENTSERVICEC_HXX

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
    \brief The ooc::PowerManagementService interface on the client side.
    \details
            A proxy implements this interface.
    **/
    class PowerManagementServiceC
    {
    public:
        // List of request methods
        /**
            *
         *    Request a set of cluster active bits with an activation cause
         *
         *    @param clusterActiveBits: set of ECU's to keep alive
         *    @param activationCause: reason to stay alive
         *    @param counter: running counter to map request and response
         
            requestClusterActiveBits Method ID: 0
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool requestClusterActiveBits(
            const uint64_t clusterActiveBits,
            const uint16_t activationCause,
            const uint64_t counter
        ) const IPL_NOEXCEPT = 0;

        /**
            *
         *    Request to keep the NAD partition alive or cancel the request
         *
         *    @param alive: submit a partition keep alive request or cancel the current request
         *    @param activationCause: reason to stay alive
         *    @param counter: running counter to map request and response 
         
            requestPartitionKeepAlive Method ID: 1
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool requestPartitionKeepAlive(
            const bool alive,
            const uint16_t activationCause,
            const uint64_t counter
        ) const IPL_NOEXCEPT = 0;

        /**
            *
         *    Request to keep the process alive or cancel the request
         *
         *    @param alive: submit a process keep alive request or cancel the current request
         *    @param activationCause: reason to stay alive
         *    @param counter: running counter to map request and response
         
            requestProcessKeepAlive Method ID: 2
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool requestProcessKeepAlive(
            const bool alive,
            const uint16_t activationCause,
            const uint64_t counter
        ) const IPL_NOEXCEPT = 0;

        PowerManagementServiceC()  {}
        virtual ~PowerManagementServiceC() {}
    protected:
        friend class PowerManagementServiceProxy;
    };

}//namespace asi
}//namespace connectivity
}//namespace ooc
#endif// ASI_CONNECTIVITY_OOC_POWERMANAGEMENTSERVICEC_HXX
