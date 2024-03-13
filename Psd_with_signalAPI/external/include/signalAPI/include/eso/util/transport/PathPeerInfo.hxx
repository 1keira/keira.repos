/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_TRANSPORT_PATH_PEERINFO_HXX
#define UTIL_TRANSPORT_PATH_PEERINFO_HXX

#include <ipl_config.h>

#include <util/transport/PeerInfo.hxx>

#include <string>
#include <iostream>

namespace util {
namespace transport {
    // Peer info for a process connedted via an endpoint represented as a path in the filesystem
    class UTIL_EXPORT PathPeerInfo : public PeerInfo {
        public:
            explicit PathPeerInfo(const std::string& path) IPL_NOEXCEPT;
            explicit PathPeerInfo(const char* path) IPL_NOEXCEPT;
            ~PathPeerInfo() IPL_NOEXCEPT override = default;

            static ipl::Tag TYPE;
            const ipl::Tag& tag() const IPL_NOEXCEPT override { return TYPE; }

            const std::string& path() const IPL_NOEXCEPT;

            std::string toString() const IPL_NOEXCEPT override;

        private:
            std::string m_path;
    };

    UTIL_EXPORT std::ostream& operator<<(std::ostream& out, const PathPeerInfo& peer_info) IPL_NOEXCEPT;
}
}
#endif // UTIL_TRANSPORT_PATH_PEERINFO_HXX


