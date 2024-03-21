/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_TRANSPORT_SSL_HXX
#define UTIL_TRANSPORT_SSL_HXX

#include <ipl_config.h>
#include <util/util_dso.h>
#include <common/types/string.hxx>
#include <util/transport/factory/TransportConfig.hxx>
#include <osal/IPSocket.hxx>

namespace util
{
namespace transport
{
namespace ssl
{

    struct UTIL_EXPORT Param {
        osal::IPSocket::IPAddress   address;
        std::string                 cert;
        std::string                 ca;
        std::string                 key;
        std::string                 ciphers;
        std::string                 ec_name;

        Param()
        {
        }

        Param(const std::string& host, unsigned port
            ,const util::transport::TransportConfig::SSLParameter& ssl_config) IPL_NOEXCEPT;
    };

    //! converts ssl config parameters to astra descriptor
    UTIL_EXPORT std::string toDescriptor(const Param& ssl_param
                            ,const util::transport::TransportConfig::CommonParameter& cp
                                    = util::transport::TransportConfig::CommonParameter()
                            ) IPL_NOEXCEPT;


    /*! 
        \brief Converts Descriptor to ssl transport config parameters

        Returns true on error and does not raise.

        Errors are:
        - \a config has a scheme other than "ssl"
        - address or port are not present in \a config
        - address is empty
    */
    UTIL_EXPORT bool fromDescriptor(const std::string& cfg
                            ,Param& param
                            ,util::transport::TransportConfig::TransportProtocol& tp
                            ) IPL_NOEXCEPT;
}
}
}

#endif /* UTIL_TRANSPORT_SSL_HXX */
