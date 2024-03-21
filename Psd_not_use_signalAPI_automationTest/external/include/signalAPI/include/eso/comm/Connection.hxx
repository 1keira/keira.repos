/*
    Copyright 2021 e.solutions GmbH
    All rights reserved
*/

#ifndef COMM_CONNECTION_HXX
#define COMM_CONNECTION_HXX

#include <ipl_config.h>
#include <comm/comm_dso.h>
#include <util/transport/Readable.hxx>
#include <comm/commtypes.hxx>
#include <util/transport/PeerInfo.hxx>
#include <comm/Call.hxx>

#include <memory>
#include <string>

namespace comm {
    namespace protocol {
        struct Message;
    }

    /**
        \brief Query about a connected peer.
    */
    class COMM_EXPORT PeerQuery {
        public:
            using PeerInfo = util::transport::PeerInfo;

            PeerQuery() IPL_NOEXCEPT = default;
            virtual ~PeerQuery() IPL_NOEXCEPT = default;

            virtual comm::AgentID getPeerAgentID() const IPL_NOEXCEPT = 0;

            virtual comm::AgentEpoch getPeerEpoch() const IPL_NOEXCEPT = 0;

            virtual const std::shared_ptr<const PeerInfo>& getPeerInfo() const IPL_NOEXCEPT = 0;
    };

    /**
        \brief Common interface for synchronous and asyncronous connections in comm.
    */
    class COMM_EXPORT Connection : public PeerQuery {
        public:
            using PeerInfo = util::transport::PeerInfo;

            Connection() IPL_NOEXCEPT;
            ~Connection() IPL_NOEXCEPT override = default;

            using Id = unsigned;
            Id id() const IPL_NOEXCEPT { return m_id; }

            // send a comm message
            virtual bool send_msg(const comm::protocol::Message& message) IPL_NOEXCEPT = 0;

            // send a comm call
            virtual bool send_call(comm::ICall& call) IPL_NOEXCEPT = 0;

            // check connection health
            virtual void check_health() IPL_NOEXCEPT = 0;

            class Peer {
                public:
                    virtual ~Peer() IPL_NOEXCEPT = default;
                    virtual comm::AgentID agent() const IPL_NOEXCEPT = 0;
                    virtual comm::AgentEpoch epoch() const IPL_NOEXCEPT = 0;
                    virtual const std::shared_ptr<const PeerInfo>& info() const IPL_NOEXCEPT = 0;
                    virtual bool has_feature(const char* feature_name) const IPL_NOEXCEPT = 0;
            };
            virtual const Peer& peer() const IPL_NOEXCEPT = 0;

            virtual bool is_incoming() const IPL_NOEXCEPT = 0;

            virtual std::string to_string() const IPL_NOEXCEPT = 0;

            virtual void close() IPL_NOEXCEPT = 0;

            // irrecoverable error
            virtual bool has_error() const IPL_NOEXCEPT = 0;

            comm::AgentID getPeerAgentID() const IPL_NOEXCEPT override {
                return peer().agent();
            }

            comm::AgentEpoch getPeerEpoch() const IPL_NOEXCEPT override {
                return peer().epoch();
            }

            const std::shared_ptr<const PeerInfo>& getPeerInfo() const IPL_NOEXCEPT override {
                return peer().info();
            }

        private:
            Id    m_id;
    };


    using ConnectionPtr = std::shared_ptr<Connection>;

    // push a received frame to be processed
    class PushReceiver {
        public:
            PushReceiver() IPL_NOEXCEPT = default;
            virtual ~PushReceiver() IPL_NOEXCEPT = default;

            virtual bool push_frame(const util::transport::Readable& msg) IPL_NOEXCEPT = 0;

    };

    // pull a received frame
    class PullReceiver {
        public:
            PullReceiver() IPL_NOEXCEPT = default;
            virtual ~PullReceiver() IPL_NOEXCEPT = default;

            // gets a frame from the transport
            virtual util::transport::Readable pull_frame( bool& error) IPL_NOEXCEPT = 0;
    };

    // Synchronous transports and connections have an explicit open
    class ExplicitOpen {
        public:
            ExplicitOpen() IPL_NOEXCEPT = default;
            virtual ~ExplicitOpen() IPL_NOEXCEPT = default;

            virtual bool open() IPL_NOEXCEPT = 0;
    };
}

#endif // COMM_CONNECTION_HXX
