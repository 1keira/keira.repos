/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef TRACING_AGENTPROVIDER_HXX
#define TRACING_AGENTPROVIDER_HXX

#include <ipl_config.h>
#include <comm/AgentStarter.hxx>
#include <comm/SingleThreadedActiveObjectFactory.hxx>

#ifdef IPL_OS_WIN32
#    if defined(TracingAgentProvider_EXPORTS)
#        define TRACINGAGENTPROVIDER_EXPORT __declspec(dllexport)
#    elif TracingAgentProvider_STATIC
#        define TRACINGAGENTPROVIDER_EXPORT
#    else
#        define TRACINGAGENTPROVIDER_EXPORT __declspec(dllimport)
#    endif
#else
#    if __GNUC__ >= 4
#        define TRACINGAGENTPROVIDER_EXPORT __attribute__ ((visibility("default")))
#    else
#        define TRACINGAGENTPROVIDER_EXPORT
#    endif
#endif

namespace tracing
{
/*!
 *  \brief
 *      Initialization of Tracing Agent singleton.
 *
 *  \param
 *      agent_name The agent name.
 *  \param
 *      node_name The node name as found in the framework.json configuration file.
 */
TRACINGAGENTPROVIDER_EXPORT void initTracingAgent(
        const ipl::string & agent_name,
        const ipl::string & node_name = "local");
/*!
 *  \brief
 *      Shutdown of Tracing Agent singleton.
 */
TRACINGAGENTPROVIDER_EXPORT void shutdownTracingAgent();

/*!
 *  \brief
 *      Provides the Active Object Factory.
 */
TRACINGAGENTPROVIDER_EXPORT ::comm::ActiveObjectFactoryPtr getAOFactory();

} // end of namespace tracing

#endif
