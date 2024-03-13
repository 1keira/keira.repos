/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_TRANSPORT_GHSCONN_HXX
#define UTIL_TRANSPORT_GHSCONN_HXX

#include <ipl_config.h>
#include <util/util_dso.h>

#include <string>

namespace util
{
namespace transport
{
namespace ghsconn
{
    //! converts ghsconn transport config parameters to Descriptor
    UTIL_EXPORT std::string toDescriptor(const std::string& path) IPL_NOEXCEPT;

    /*! 
        \brief Converts Descriptor to ghsconn transport config parameters

        Returns true on error and does not raise.

        Errors are:
        - \a config has a scheme other than "ghsconn"
        - \a path retrieved form \a config is empty
    */
    UTIL_EXPORT bool fromDescriptor(const std::string& config, std::string& path) IPL_NOEXCEPT;
}
}
}

#endif /* UTIL_TRANSPORT_GHSCONN_HXX */
