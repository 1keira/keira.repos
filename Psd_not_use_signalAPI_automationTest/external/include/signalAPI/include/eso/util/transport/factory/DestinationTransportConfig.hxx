/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_TRANSPORT_DEST_TRANSPORTCONFIG_HXX
#define UTIL_TRANSPORT_DEST_TRANSPORTCONFIG_HXX

#include <ipl_config.h>

#include <util/util_dso.h>
#include <util/transport/factory/TransportConfig.hxx>

#include <string>

namespace util
{
namespace transport
{

/**
 * \brief
 *     Accesses the transport configuration for a single destination process.
 * \details
 *     Translates a set of parameters into a configuration string that can be passed
 *     to a SimpleFactory.
**/
class UTIL_EXPORT DestinationTransportConfig
{
    public:
        using ExtConfig = TransportConfig::ExtConfig;

        /*!
         * \brief
         * Constructor with own process name, peer process name and transport protocol name.
         * \param[in] process the name of this process used in the transport configuration.
         * \param[in] peer the name of the process we want to connect to.
         * \param[in] protocol the name of the transport protocol e.g. "comm", "tracing".
         * \errorindicator via size(): < 0 indicates that an error has been raised.
         */
        DestinationTransportConfig(const std::string& process
                                    ,const std::string& peer
                                    ,const std::string& protocol
                );

        /*!
         * \brief
         * Returns the config string.
         * \details The string is empty if size() returns <=0.
         */
        const std::string& getConfig() const {
            return m_config.first;
        }

        /*!
         * \brief
         * Returns the extended config: description string and astra flag.
         * \details The string is empty if size() returns <=0.
         */
        const ExtConfig& getExtConfig() const {
            return m_config;
        }

        /*!
         * \brief
         * Returns the number of configurations found.
         * \details
         * <br> returns -1 in case of an error.
         * <br> returns 0 in case of no error and no configuration found.
         * <br> retunrs 1 in case of success.
         */
        int size() {
            return m_size;
        }
    private:
        ExtConfig   m_config;
        int         m_size;
};

}
}

#endif /* UTIL_TRANSPORT_DEST_TRANSPORTCONFIG_HXX */
