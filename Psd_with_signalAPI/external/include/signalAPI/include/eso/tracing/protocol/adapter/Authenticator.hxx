/*
    Copyright 2022 e.solutions GmbH

    All rights reserved
*/
#ifndef TRACING_PROTOCOL_AUTHENTICATOR_HXX
#define TRACING_PROTOCOL_AUTHENTICATOR_HXX

#include <string>
#include <map>
#include <util/transport/PeerInfoPtrForward.hxx>
#include <tracing/util/TraceMe.hxx>
#include <tracing/protocol/protocol_dso.h>

// fwd declarations
namespace util
{
namespace config
{
class Value;
} // end of namespace config
} // end of namespace util

namespace tracing
{
namespace protocol
{

class ConnectionFrontendHandler;

class TRACING_PROTOCOL_EXPORT Authenticator final
{
public:
    explicit Authenticator(const std::string & config_file);
    bool isAuthentic(const ConnectionFrontendHandler * handler) const;

protected:
    bool m_enabled{false};
    bool m_enforce{false};
    bool m_accept_unknown_clients{true};
    std::multimap<std::string, util::transport::PeerInfoPtr> m_configured_clients;
    std::map<std::string, bool> m_configured_default;

    IPL_TRACEME_DECLARE_SCOPE(Authenticator);

    bool parseClientsDictionary(const util::config::Value & clients);
    util::transport::PeerInfoPtr parseLocalTransport(const std::string & client_name,
            const util::config::Value & transport_dict);
    util::transport::PeerInfoPtr parseTcpTransport(const std::string & client_name,
            const util::config::Value & transport_dict);
};

} // end of namespace protocol
} // end of namespace tracing

#endif /* TRACING_PROTOCOL_AUTHENTICATOR_HXX */
