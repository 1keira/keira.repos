/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_TRANSPORT_SRC_TRANSPORTCONFIG_HXX
#define UTIL_TRANSPORT_SRC_TRANSPORTCONFIG_HXX

#include <ipl_config.h>

#include <util/util_dso.h>
#include <util/transport/factory/TransportConfig.hxx>

#include <string>
#include <vector>

namespace util
{
namespace transport
{

/**
 * \brief
 *     Accesses the transport configuration for all endpoints a given process has.
 * \details
 *     Translates a transport protocol name into an array of configuration strings that can be passed
 *     to a SpawnFactory.
**/
class UTIL_EXPORT SourceTransportConfig
{
    public:

        using ExtConfig = TransportConfig::ExtConfig;

        /*!
         * \brief
         * Constructor with transport protocol name.
         * \param[in] protocol the name of the transport protocol e.g. "comm", "tracing".
         * \errorindicator via size(): < 0 indicates that an erroro has been raised.
         */
        explicit SourceTransportConfig(const std::string& protocol);

        /*!
         * \brief
         * Constructor with transport protocol name and process.
         * \param[in] protocol the name of the transport protocol e.g. "comm", "tracing".
         * \errorindicator via size(): < 0 indicates that an erroro has been raised.
         */
        SourceTransportConfig(const std::string& process, const std::string& protocol);

        /*!
         * \brief
         * Returns the array of config strings.
         * \details The vector is empty if this->size() returns <=0.
         */
        const std::vector < std::string >& getConfig() {
            if ( m_config.empty() ) {
                for(const auto& config: m_ext_config) {
                    m_config.push_back(config.first); // ExtConfig is a pair
                }
            }
            return m_config;
        }

        /*!
         * \brief
         * Returns the array of config strings.
         * \details The vector is empty if this->size() returns <=0.
         */
        const std::vector < ExtConfig >& getExtConfig() const {
            return m_ext_config;
        }

        /*!
         * \brief
         * Returns the number of configurations found.
         * \details
         * <br> returns -1 in case of an error.
         * <br> returns 0 in case of no error and no configuration found.
         * <br> returns >1 in case of success.
         */
        int size() {
            return m_size;
        }

    private:
        std::vector<std::string>    m_config;
        std::vector<ExtConfig>      m_ext_config;
        int                         m_size;
};

}
}

#endif /* UTIL_TRANSPORT_SRC_TRANSPORTCONFIG_HXX */
