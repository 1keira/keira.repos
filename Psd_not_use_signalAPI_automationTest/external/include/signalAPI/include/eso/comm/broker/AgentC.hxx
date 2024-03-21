/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template InterfaceC_hxx.tmpl
*/
#ifndef COMM_BROKER_AGENTC_HXX
#define COMM_BROKER_AGENTC_HXX

#include <ipl_config.h>
#include <comm/commidltypes.hxx>
#include <comm/broker/StructAgentUpdateEvent.hxx>
#include <comm/broker/StructUpdateEvent.hxx>
#include <comm/broker/Definitions.hxx>

namespace comm
{
namespace broker
{

    /**
    \brief The broker::Agent interface on the client side.
    \details
            A proxy implements this interface.
    **/
    class AgentC
    {
    public:
        // List of request methods
        /**
            serviceUpdate Method ID: 1
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool serviceUpdate(
            const CIPtr< CIPtrArray< comm::broker::UpdateEvent > >& events
        ) const IPL_NOEXCEPT = 0;

        /**
            agentUpdate Method ID: 0
        \return false in case of success, true in case of an failed
                In case of failed
                    - the error has to be acknowledged (ipl_error.ack())
                    - details can be retrieved via ipl_error.id() and ipl_error.reason()
        **/
        virtual bool agentUpdate(
            const CIPtr< CIPtrArray< comm::broker::AgentUpdateEvent > >& events
        ) const IPL_NOEXCEPT = 0;

        AgentC()  {}
        virtual ~AgentC() {}
    protected:
        friend class AgentProxy;
    };

}//namespace comm
}//namespace broker
#endif// COMM_BROKER_AGENTC_HXX
