/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_TRANSPORT_TRANSPORTCONFIGPARAMETER_HXX
#define UTIL_TRANSPORT_TRANSPORTCONFIGPARAMETER_HXX

#include <ipl_config.h>
#include <util/util_dso.h>

#include <util/config/Values.hxx>
#include <util/transport/factory/TransportConfig.hxx>
#include <common/types/optional.hxx>

#include <string>

// Conversion functions for transport configuration
namespace util {
    
    struct Descriptor;
    
namespace transport {
    
    class DescriptorBuilder;
    
namespace config_cvt {

    using TransportProtocol = TransportConfig::TransportProtocol;
    using CommonParameter = TransportConfig::CommonParameter;
    using KeepaliveParameter = TransportConfig::KeepaliveParameter;

    UTIL_EXPORT void fromDescriptor(const Descriptor& descriptor, TransportProtocol& tp) IPL_NOEXCEPT;

    UTIL_EXPORT void addToBuilder(DescriptorBuilder& builder, const CommonParameter& cp) IPL_NOEXCEPT;

    UTIL_EXPORT void addToBuilder(DescriptorBuilder& builder, const KeepaliveParameter& k) IPL_NOEXCEPT;


    //! convert config dictionary to Descriptor
    UTIL_EXPORT std::string configToDescriptor(const std::string& scheme
                        ,const CommonParameter& cp
                        ,const util::config::Value& config
                        ,const std::string& process
                        ,const std::string& protocol
                        ,bool is_incoming
                        ) IPL_NOEXCEPT;

}
}
}

#endif // UTIL_TRANSPORT_TRANSPORTCONFIGPARAMETER_HXX
