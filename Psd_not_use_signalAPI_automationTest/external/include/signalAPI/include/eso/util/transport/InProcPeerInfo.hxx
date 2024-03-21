/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_TRANSPORT_INPROC_PEERINFO_HXX
#define UTIL_TRANSPORT_INPROC_PEERINFO_HXX

#include <ipl_config.h>

#include <util/transport/PeerInfo.hxx>

#include <iostream>

namespace util {
namespace transport {
    // Peer info for a peer in the same process (tag only, no further info)
    class UTIL_EXPORT InProcPeerInfo : public PeerInfo {
        public:
            ~InProcPeerInfo() IPL_NOEXCEPT override = default;

            static ipl::Tag TYPE;
            const ipl::Tag& tag() const IPL_NOEXCEPT override { return TYPE; }

            std::string toString() const IPL_NOEXCEPT override;

    };

    UTIL_EXPORT std::ostream& operator<<(std::ostream& out, const InProcPeerInfo& peer_info) IPL_NOEXCEPT;
}
}
#endif // UTIL_TRANSPORT_INPROC_PEERINFO_HXX


