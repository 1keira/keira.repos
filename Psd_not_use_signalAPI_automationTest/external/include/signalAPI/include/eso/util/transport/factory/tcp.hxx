/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_TRANSPORT_TCP_HXX
#define UTIL_TRANSPORT_TCP_HXX

#include <ipl_config.h>
#include <util/util_dso.h>
#include <common/types/string.hxx>
#include <util/transport/factory/TransportConfig.hxx>
#include <osal/IPSocket.hxx>
#include <osal/TCPSocket.hxx>

namespace util
{
namespace transport
{
namespace tcp
{
    //! converts tcp config parameters to config-url
    // \link2req{satisfies,req~FW_UTIL_TCP_USER_TIMEOUT_DEFAULT_SETTING~1}
    UTIL_EXPORT ipl::string toDescriptor(const util::transport::TransportConfig::TcpParameter& tcp_parameter
                                    ,bool server
                                    ,const util::transport::TransportConfig::CommonParameter& cp
                                    = util::transport::TransportConfig::CommonParameter()
                                ) IPL_NOEXCEPT;


    //! all tcp parameters
    // \link2req{satisfies,req~FW_UTIL_TCP_USER_TIMEOUT_DEFAULT_SETTING~1}
    // \link2req{satisfies,req~FW_UTIL_SO_LINGER_DEFAULT_SETTING~1}
    struct UTIL_EXPORT Param {
        osal::IPSocket::IPAddress                           address;
        ipl::string                                         family;
        size_t                                              rx_buffer{0u};
        size_t                                              tx_buffer{0u};
        bool                                                no_delay{true};
        util::transport::TransportConfig::TransportProtocol tp;
        osal::TCPSocket::KeepaliveSettings                  keepalive{false};
        uint32_t                                            user_timeout{0};        // off by default as per req~FW_UTIL_TCP_USER_TIMEOUT_DEFAULT_SETTING~1
        bool                                                enable_linger{false};   // off by default as per req~FW_UTIL_SO_LINGER_DEFAULT_SETTING~1
        unsigned                                            linger_time{0};
    };

    // \link2req{satisfies,req~FW_UTIL_TCP_USER_TIMEOUT_DEFAULT_SETTING~1}
    // \link2req{satisfies,req~FW_UTIL_SO_LINGER_DEFAULT_SETTING~1}
    /*! 
        \brief Converts Descriptor to tcp transport config parameters

        Returns true on error and does not raise.

        Errors are:
        - \a config has a scheme other than "tcp"
        - address or port are not present in \a config
    */
    UTIL_EXPORT bool fromDescriptor(const ipl::string& cfg, Param& param ) IPL_NOEXCEPT;
}
}
}

#endif /* UTIL_TRANSPORT_TCP_HXX */
