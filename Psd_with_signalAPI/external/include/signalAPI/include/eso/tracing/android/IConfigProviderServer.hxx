/*
    Copyright 2023 e.solutions GmbH
    All rights reserved
 */
#ifndef TRACING_ICONFIGROVIDERSERVERP_HXX_
#define TRACING_ICONFIGROVIDERSERVERP_HXX_

#include <string>

namespace tracing {

/**
 * \brief
 *    Interface which is used by Android AIDL Configprovider server for communication
 *    towards the tracecore server.
 *
 *    Tracecore server needs to implement this interface offering callbacks to the
 *    Android AIDL Configprovider server.
**/
class IConfigProviderServer
{
public:
    /**
     * \brief
     *     Enumeration of ConfigProvider capabilities.
     **/
    enum Capability : unsigned int
    {
        CHANNEL_LEVEL_SUPPORT = 1,
        THREAD_LEVEL_SUPPORT = 2,
        PRIVACY_FLAGS_SUPPORT = 4
    };

    virtual ~IConfigProviderServer() = default;

    /**
     * \brief
     *     Will be called by Android AIDL Configprovider server to request a
     *     the capabilities from the tracecore server.
     *
     * \return Bit mask reflecting the AIDL Configprovider capability of the server
     *         \sa enum ConfigProvider::Capability.
     **/
    virtual uint32_t getCapability() noexcept = 0;

    /**
     * \brief
     *     Will be called by Android AIDL Configprovider server to request a
     *     tracecore client's tracing configuration for a single type/capability
     *     from the tracecore server.
     *
     * \param[in]  cfg_type    The configuration type. Only a single bit of server's
     *                         reported capabilities must be set
     *                         \sa enum ConfigProvider::Capability.
     * \param[in]  client_name The client process name as configured in framework.json.
     * \param[in]  cfg_in      The client local configuration part of given type in JSON format.
     * \param[out] cfg_out     The resulting configuration part of given type to be used
     *                         by the client. In case of an empty string the client
     *                         shall use its own local configuration.
     * Note: Only minimal required content and size of the JSON configuration strings
     *       shall be transmitted via AIDL.
     *       E.g. for this sample channel configuration
     *           "levels":{
     *               "channel":{
     *                   "*":"debug",
     *                   "FW":"trace"
     *               }
     *           }
     *       the related JSON config string which shall be transmitted is
     *           {"*":"debug","FW":"trace"}
     **/
    virtual void updateConfig(uint32_t cfg_type, const std::string & client_name,
                              const std::string & cfg_in, std::string & cfg_out) noexcept = 0;
};

} /*  namespace tracing */

#endif /* TRACING_ICONFIGROVIDERSERVERP_HXX_ */
