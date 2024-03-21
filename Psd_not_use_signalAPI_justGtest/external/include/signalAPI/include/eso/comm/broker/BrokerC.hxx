/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceC_hxx.tmpl
*/
#ifndef COMM_BROKER_BROKERC_HXX
#define COMM_BROKER_BROKERC_HXX

#include <ipl_config.h>
#include <comm/commidltypes.hxx>
#include <comm/broker/StructInstanceID.hxx>
#include <comm/broker/Definitions.hxx>

namespace comm
{
namespace broker
{

    /**
    \brief The broker::Broker interface on the client side.
    \details
            A proxy implements this interface.
    **/
    class BrokerC
    {
    public:
        // List of request methods
        /**
            
            \brief announces an agent to the broker
            \param agent_interface_id the InstanceID id of the calling agent's Agent Inteface.
                   The handle in the interface_id IS the agent_id.
        
            announce Method ID: 0
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool announce(
            const CIPtr< comm::broker::InstanceID >& agent_interface_id
        ) const IPL_NOEXCEPT = 0;

        /**
            
            \brief Registers a service
            \param svc_id the instance id of the service
            \param home_agent_id the agent id of the agent where the service is located
        
            registerService Method ID: 2
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool registerService(
            const CIPtr< comm::broker::InstanceID >& svc_id,
            const uint16_t home_agent_id
        ) const IPL_NOEXCEPT = 0;

        /**
            
            \brief Unregisters a service
            \param svc_id the instance id of the service
            \param home_agent_id the agent id of the agent where the service is located
        
            unregisterService Method ID: 3
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool unregisterService(
            const CIPtr< comm::broker::InstanceID >& svc_id,
            const uint16_t home_agent_id
        ) const IPL_NOEXCEPT = 0;

        /**
            
            \brief Looks up a service
            \param svc_id the instance id of the service
            \param caller_id the agent id of the calling agent
        
            lookupService Method ID: 1
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool lookupService(
            const CIPtr< comm::broker::InstanceID >& svc_id,
            const uint16_t caller_id
        ) const IPL_NOEXCEPT = 0;

        BrokerC()  {}
        virtual ~BrokerC() {}
    protected:
        friend class BrokerProxy;
    };

}//namespace comm
}//namespace broker
#endif// COMM_BROKER_BROKERC_HXX
