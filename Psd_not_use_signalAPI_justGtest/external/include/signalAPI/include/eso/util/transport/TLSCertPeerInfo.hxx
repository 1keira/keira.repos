/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_TRANSPORT_TLS_CERT_PEERINFO_HXX
#define UTIL_TRANSPORT_TLS_CERT_PEERINFO_HXX

#include <ipl_config.h>

#include <osal/TCPSocket.hxx>
#include <util/transport/PeerInfo.hxx>

#include <iostream>
#include <string>

namespace util {
namespace transport {
    class SSLTransport;

    class UTIL_EXPORT TLSCertPeerInfo : public PeerInfo {
        public:
            TLSCertPeerInfo() IPL_NOEXCEPT;
            // Constructor with parameter indicating the certificate validity
            explicit TLSCertPeerInfo(bool valid) IPL_NOEXCEPT;
            // Constructor with connected socket and validity parameter
            TLSCertPeerInfo(bool valid, osal::TCPSocket* s) IPL_NOEXCEPT;
            // Constructor with issuer and subject names and connected socket
            TLSCertPeerInfo(const char* issuer, const char* subject, osal::TCPSocket* s) IPL_NOEXCEPT;

            ~TLSCertPeerInfo() IPL_NOEXCEPT override = default;

            static ipl::Tag TYPE;
            const ipl::Tag& tag() const IPL_NOEXCEPT override { return TYPE; }

            bool isCertValid() const IPL_NOEXCEPT { return m_valid; }
            const std::string& issuer() const IPL_NOEXCEPT;
            const std::string& subject() const IPL_NOEXCEPT;
            const osal::IPSocket::IPAddress& address() const IPL_NOEXCEPT;
            osal::IPSocket::IPProtocolVersion family() const IPL_NOEXCEPT;

            std::string toString() const IPL_NOEXCEPT override;

        private:

            bool            m_valid{false};
            std::string     m_issuer;
            std::string     m_subject;
            osal::IPSocket::IPAddress m_peer_address;
            osal::IPSocket::IPProtocolVersion m_family{osal::IPSocket::IPVUNSPEC};
    };

    UTIL_EXPORT std::ostream& operator<<(std::ostream& out, const TLSCertPeerInfo& peer_info) IPL_NOEXCEPT;
}
}
#endif


