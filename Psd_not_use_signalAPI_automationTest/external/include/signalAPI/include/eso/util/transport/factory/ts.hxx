/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_TRANSPORT_TS_HXX
#define UTIL_TRANSPORT_TS_HXX

#include <ipl_config.h>
#include <util/util_dso.h>
#include <common/types/string.hxx>
#include <util/transport/factory/TransportConfig.hxx>
#include <osal/IPSocket.hxx>

namespace util
{
namespace transport
{
namespace ts
{

    //! converts transportserver config parameters to Descriptor
    UTIL_EXPORT std::string toDescriptor(const std::string& path
                    , unsigned tx_buffer_size = 0, unsigned rx_buffer_size = 0
                    ) IPL_NOEXCEPT;

    /*! 
        \brief Converts Descriptor to transportserver transport config parameters

        Returns true on error and does not raise.

        Errors are:
        - \a config has a scheme other than "ts"
        - \a path retrieved form \a config is empty
    */
    UTIL_EXPORT bool fromDescriptor(const std::string& config, std::string& path
                ,size_t& tx_buffer_size, size_t& rx_buffer_size
                ) IPL_NOEXCEPT;
}
}
}

#endif /* UTIL_TRANSPORT_TS_HXX */
