/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_PEERINFOPTR_FORWARD_HXX
#define UTIL_PEERINFOPTR_FORWARD_HXX

#include <ipl_config.h>
#include <util/util_dso.h>
#include <util/SharedPtr.hxx>
#include <util/transport/PeerInfo.hxx>

#include <iostream>

namespace util {
    namespace transport {

        using PeerInfoPtr = util::SharedPtr<const PeerInfo>;

        UTIL_EXPORT std::ostream& operator<<(std::ostream& out, const PeerInfoPtr& peerInfo) IPL_NOEXCEPT;

    }
}
#endif /* UTIL_PEERINFOPTR_FORWARD_HXX */

