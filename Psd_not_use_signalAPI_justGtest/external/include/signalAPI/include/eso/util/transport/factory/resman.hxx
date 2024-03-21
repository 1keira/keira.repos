/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_TRANSPORT_RESMAN_HXX
#define UTIL_TRANSPORT_RESMAN_HXX

#include <ipl_config.h>
#include <util/util_dso.h>
#include <util/transport/factory/TransportConfig.hxx>

#include <string>

namespace util
{
namespace transport
{
namespace resman
{

    //! converts resman config parameters to Descriptor
    UTIL_EXPORT std::string toDescriptor(const std::string& path
                    ,const TransportConfig::CommonParameter& cp
                    ) IPL_NOEXCEPT;

    /*! 
        \brief Converts Descriptor to resman transport config parameters

        Returns true on error and does not raise.

        Errors are:
        - \a config has a scheme other than "resman"
        - \a path retrieved from \a config is empty
    */
    UTIL_EXPORT bool fromDescriptor(const std::string& config
                ,std::string& path
                ,size_t& tx_buffer_size, size_t& rx_buffer_size
              ) IPL_NOEXCEPT;
}
}
}

#endif /* UTIL_TRANSPORT_RESMAN_HXX */
