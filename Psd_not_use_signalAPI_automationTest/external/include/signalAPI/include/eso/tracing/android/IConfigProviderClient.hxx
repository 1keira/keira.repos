/*
    Copyright 2023 e.solutions GmbH
    All rights reserved
 */
#ifndef TRACING_ICONFIGPROVIDERCLIENT_HXX
#define TRACING_ICONFIGPROVIDERCLIENT_HXX

#include <memory>
#include <string>

namespace tracing {

/**
 * \brief
 *    Interface which is used by tracecore client for communication towards the
 *    tracecore server via the Android AIDL Configprovider.
 *
 *    The Android AIDL Configprovider client needs to implement this interface offering
 *    callbacks to the tracecore client.
 *    Interface is defined and used but not built in scope of the esofw tracecore.
 *    It must be provided as shared AOSP lib.
**/
class IConfigProviderClientListener
{
public:
    virtual ~IConfigProviderClientListener() = default;

    /**
     * \brief
     *     Will be called by tracecore client to request the capabilities
     *     from the tracecore server.
     *
     * \return Bit mask reflecting the AIDL Configprovider capability of the server
     *         \sa enum ConfigProvider::Capability.
     **/
    virtual uint32_t getCapability() const noexcept = 0;

    /**
     * \brief
     *     Will be called by tracecore client to request its tracing configuration
     *     for a single config/capability type from tracecore server.
     *
     * \param[in]  cfg_type The configuration type. Only a single bit of server's
     *                      reported capabilities must be set
     *                      \sa enum ConfigProvider::Capability.
     * \param[in]  cfg_in   The client local configuration part of given type in JSON format.
     * \param[out] cfg_out  The resulting configuration part of given type to be used
     *                      by the client. In case of an empty string the client
     *                      shall use its own local configuration.
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
    virtual void updateConfig(uint32_t cfg_type, const std::string & cfg_in,
                              std::string & cfg_out) noexcept = 0;

    /**
     * \brief Will be called upon shutdown of client tracecore.
     **/
    virtual void shutdown() noexcept = 0;
};

/**
 * \brief
 *    Interface which is used by Android AIDL Configprovider client for communication
 *    towards the tracecore client.
 *
 *    Tracecore client needs to implement this interface offering callbacks to the
 *    Android AIDL Configprovider client.
 **/
class IConfigProviderClient
{
public:
    virtual ~IConfigProviderClient() = default;

    /**
     * \brief
     *     Will be called by Android AIDL Configprovider client to indicate its
     *     availability towards the tracecore client.
     **/
    virtual void init(std::shared_ptr<IConfigProviderClientListener> listener) noexcept = 0;

    /**
     * \brief
     *     Will be called by Android AIDL Configprovider client to indicate its
     *     termination towards the tracecore client.
     **/
    virtual void exit() noexcept = 0;

    /**
     * \brief
     *     Informs if the tracecore client is (still) running.
     **/
    virtual bool isRunning() const noexcept = 0;

};

} /*  namespace tracing */

#endif /* TRACING_ICONFIGPROVIDERCLIENT_HXX */

