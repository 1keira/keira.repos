/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_TRANSPORT_TCP_PEERINFO_HXX
#define UTIL_TRANSPORT_TCP_PEERINFO_HXX

#include <ipl_config.h>

#include <osal/TCPSocket.hxx>
#include <util/transport/PeerInfo.hxx>

#include <iostream>
#include <string>

namespace util {
namespace transport {
    // Peer info for a process connected via TCP socket
    class UTIL_EXPORT TcpPeerInfo : public PeerInfo {
        public:
            explicit TcpPeerInfo(/*const*/ osal::TCPSocket& socket) IPL_NOEXCEPT;
            ~TcpPeerInfo() IPL_NOEXCEPT override = default;

            static ipl::Tag TYPE;
            const ipl::Tag& tag() const IPL_NOEXCEPT override { return TYPE; }

            const osal::IPSocket::IPAddress& address() const IPL_NOEXCEPT;
            osal::IPSocket::IPProtocolVersion family() const IPL_NOEXCEPT;

            // gets peer address and protocol version from a connected socket
            // if version is osal::IPSocket::IPVUNSPEC peer_address has not been touched
            // TODO: seems to only work on Posix
            static void peerAddress(const osal::Socket& socket
                                    ,osal::IPSocket::IPAddress& peer_address
                                    ,osal::IPSocket::IPProtocolVersion& version
                                    ) IPL_NOEXCEPT;

            std::string toString() const IPL_NOEXCEPT override;

        private:
            osal::IPSocket::IPAddress m_peer_address;
            osal::IPSocket::IPProtocolVersion m_family;
    };

    UTIL_EXPORT std::ostream& operator<<(std::ostream& out, const TcpPeerInfo& peer_info) IPL_NOEXCEPT;
}
}
#endif // UTIL_TRANSPORT_TCP_PEERINFO_HXX


