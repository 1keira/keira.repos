/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_TRANSPORT_FACTORY_MSG_HXX
#define UTIL_TRANSPORT_FACTORY_MSG_HXX

#include <ipl_config.h>
#include <util/util_dso.h>
#include <util/transport/factory/TransportConfig.hxx>

#include <string>

namespace util
{
namespace transport
{
namespace msg
{

    //! converts msg transport config parameters to Descriptor
    UTIL_EXPORT std::string toDescriptor(const std::string& service, const std::string& process
                                ,const std::string& mapper_name=""
                                ) IPL_NOEXCEPT;

    /*! 
        \brief Converts Descriptor to msg transport config parameters

        Returns true on error and does not raise.

        Errors are:
        - \a config has a scheme other than "msg"
        - \a service retrieved from \a config is empty
        - \a process retrieved from \a config is empty
    */
    UTIL_EXPORT bool fromDescriptor(const std::string& cfg, std::string& service, std::string& process
                            ,std::string& mapper_name
                            ) IPL_NOEXCEPT;
}
}
}

#endif /* UTIL_TRANSPORT_FACTORY_MSG_HXX */
