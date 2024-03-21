/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_TRANSPORT_LOCAL_HXX
#define UTIL_TRANSPORT_LOCAL_HXX

#include <ipl_config.h>
#include <util/util_dso.h>
#include <common/types/string.hxx>
#include <util/transport/factory/TransportConfig.hxx>

namespace util
{
namespace transport
{
namespace local
{

    struct UTIL_EXPORT Param {
        std::string                         path;
        bool                                abstract{true};
        TransportConfig::TransportProtocol  tp;

    };

    //! converts local transport config parameters to astra descriptor
    UTIL_EXPORT std::string toDescriptor(const std::string& path
                    , bool abstract
                    , bool server
                    , const util::transport::TransportConfig::CommonParameter& =
                                        util::transport::TransportConfig::CommonParameter()
                    ) IPL_NOEXCEPT;

    /*! 
        \brief Converts Descriptor to local transport config parameters

        Returns true on error and does not raise.

        Errors are:
        - \a config has a scheme other than "local"
        - path retrieved from \a config is empty
    */
    UTIL_EXPORT bool fromDescriptor(const std::string& config, Param& param) IPL_NOEXCEPT;

}
}
}

#endif /* UTIL_TRANSPORT_LOCAL_HXX */
