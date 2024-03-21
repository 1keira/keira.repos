/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_TRANSPORT_FILE_HXX
#define UTIL_TRANSPORT_FILE_HXX

#include <ipl_config.h>
#include <util/util_dso.h>

#include <string>

namespace util
{
namespace transport
{
namespace file
{

    //! converts file transport config parameters to an Descriptor
    UTIL_EXPORT std::string toDescriptor(const std::string& path, unsigned poll_ms = 0) IPL_NOEXCEPT;

    /*! 
        \brief Converts Descriptor to file transport config parameters

        Returns true on error and does not raise.

        Errors are:
        - \a config has a scheme other than "file"
        - \a path retrieved from \a config is empty
    */
    UTIL_EXPORT bool fromDescriptor(const std::string& config
                                    ,std::string& path, unsigned& poll_ms) IPL_NOEXCEPT;
}
}
}

#endif /* UTIL_TRANSPORT_FILE_HXX */
