/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_TRANSPORT_UDP_PEERINFO_HXX
#define UTIL_TRANSPORT_UDP_PEERINFO_HXX

#include <ipl_config.h>

#include <osal/UDPSocket.hxx>
#include <util/transport/PeerInfo.hxx>


#include <string>
#include <iostream>

namespace util {
namespace transport {
    // Peer info for a process connedted via an endpoint represented as a path in the filesystem
    class UTIL_EXPORT UdpPeerInfo : public PeerInfo {
        public:
            UdpPeerInfo(const osal::IPSocket::IPAddress& peer_address
                        ,osal::IPSocket::IPProtocolVersion version) IPL_NOEXCEPT;
            ~UdpPeerInfo() IPL_NOEXCEPT override = default;

            static ipl::Tag TYPE;
            const ipl::Tag& tag() const IPL_NOEXCEPT override { return TYPE; }

            const osal::IPSocket::IPAddress& address() const IPL_NOEXCEPT;
            osal::IPSocket::IPProtocolVersion family() const IPL_NOEXCEPT;

            std::string toString() const IPL_NOEXCEPT override;

        private:
            osal::IPSocket::IPAddress m_peer_address;
            osal::IPSocket::IPProtocolVersion m_family;
    };

    UTIL_EXPORT std::ostream& operator<<(std::ostream& out, const UdpPeerInfo& peer_info) IPL_NOEXCEPT;
}
}
#endif // UTIL_TRANSPORT_UDP_PEERINFO_HXX


