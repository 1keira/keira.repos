/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/
/****************************************************************************/
#ifndef UTIL_ASTRA_TRANSPORT_TCP_HXX
#define UTIL_ASTRA_TRANSPORT_TCP_HXX
/****************************************************************************/

#include "TransportStreamSocket.hxx"
#include "Listener.hxx"
#include <util/Descriptor.hxx>

#include <osal/TCPSocket.hxx>
#include <osal/TCPServerSocket.hxx>
#include <osal/Thread.hxx>

#include <memory>

#include <util/util_dso.h>

/****************************************************************************/

namespace util {
    namespace astra {

/****************************************************************************/

        class UTIL_EXPORT TransportTcp:
            public TransportStreamSocket {
                
        protected:
            
            class ListenerBase;
        
        public:
            
            //! Socket (and other) configuration options for TCP based Transports
            struct UTIL_EXPORT Config: public TransportStreamSocket::Config {
                bool nodelay{true};            //!< \brief TCP_NODELAY
                unsigned int user_timeout{0};  //!< \brief TCP_USER_TIMEOUT
                bool keepalive{false};         //!< \brief SO_KEEPALIVE
                int keepalive_intvl{75};       //!< \brief TCP_KEEPINTVL
                int keepalive_probes{9};       //!< \brief TCP_KEEPCNT
                int keepalive_time{2700};      //!< \brief TCP_KEEPIDLE
                bool enable_linger{false};     //!< \brief SO_LINGER.l_onoff
                int linger_time{0};            //!< \brief SO_LINGER.l_linger
                
                explicit Config(Descriptor &descriptor /* patches descriptor */) IPL_NOEXCEPT;
                Config() IPL_NOEXCEPT=default;
                
                void apply(osal::TCPSocket &socket) const {
                    socket.setTCPNoDelay(nodelay);
                    socket.setKeepalive(keepalive, keepalive_intvl,
                                        keepalive_probes, keepalive_time);
                    socket.setUserTimeout(user_timeout);
                    if(enable_linger)
                        socket.setLinger(true, linger_time);
                }
            };
            
            class Listener;
            class Service;
            
            TransportTcp(const StreamProtocol::Create &create_protocol,
                         const std::string &ip, uint16_t port) IPL_NOEXCEPT:
                TransportTcp(create_protocol, ip, port, Config()) {}
            TransportTcp(const std::string &ip, uint16_t port,
                         const Config &config) IPL_NOEXCEPT:
                TransportTcp(DefaultProtocol::create, ip, port, config) {}
            TransportTcp(const std::string &ip, uint16_t port) IPL_NOEXCEPT:
                TransportTcp(DefaultProtocol::create, ip, port, Config()) {}
            TransportTcp(const StreamProtocol::Create &create_protocol,
                         const std::string &ip, uint16_t port,
                         const Config &config) IPL_NOEXCEPT;
                         
            static const char *const scheme;
            static bool is_listener(const Descriptor &descriptor) IPL_NOEXCEPT;
            static std::unique_ptr<TransportTcp>
                create_transport(const Descriptor &descriptor) IPL_NOEXCEPT;
            static std::unique_ptr<Listener>
                create_listener(const Descriptor &descriptor) IPL_NOEXCEPT;
            
            void io_connected(
                const osal::IoMultiplexer::Channel *channel
            ) IPL_NOEXCEPT override;
            
        protected:
            explicit TransportTcp(const StreamProtocol::Create &create_protocol) IPL_NOEXCEPT:
                TransportStreamSocket(create_protocol) {}
            
            void from_description(
                const osal::TCPSocket::Description &description,
                const Config &config
            ) IPL_NOEXCEPT;
            
            static const char *const kw_listen_1;
            static const char *const kw_listen_many;
            static const char *const kw_delay;
            static const char *const kw_user_timeout;
            static const char *const kw_keepalive;
            static const char *const kw_keepalive_intvl;
            static const char *const kw_keepalive_probes;
            static const char *const kw_keepalive_time;
            static const char *const kw_linger;
        };

/****************************************************************************/

        //! \internal
        //! \brief Common functionality for single and multi connection listeners
        //!
        //! Classes inheriting this must make sure to remove their socket
        //! from the multiplexer within \b their \b own destructor, else
        //! the multiplexer might call baseclass versions of the callbacks
        //! and crash.
        class TransportTcp::ListenerBase: public osal::IoMultiplexer::Client {
            
        public:
            ListenerBase(const std::string &ip, uint16_t port,
                         const Config &config, bool retry_accept) IPL_NOEXCEPT;
            
            bool isValid() const IPL_NOEXCEPT;
            bool io_read(
                const osal::IoMultiplexer::Channel *channel
            ) IPL_NOEXCEPT override;

        protected:
            virtual void got_socket(const osal::TCPSocket::Description &description) IPL_NOEXCEPT=0;
            virtual void error(const std::string &error) IPL_NOEXCEPT=0;
            
            // Workaround around Description sillyness
            osal::TCPSocket::Description accept_connection() IPL_NOEXCEPT {
                return listener_socket.acceptConnection();
            }
            
            void from_description(TransportTcp *transport,
                                  const osal::TCPSocket::Description &description,
                                  const Config &config) IPL_NOEXCEPT {
                transport->from_description(description, config);
            }
            
            ipl::Shared<osal::IoMultiplexer>::Ptr
                multiplexer{osal::IoMultiplexer::DEFAULT};
                
            osal::TCPServerSocket listener_socket;
                
            Config config;
            bool retry_accept;
        };

/****************************************************************************/

        class UTIL_EXPORT TransportTcp::Listener:
            public astra::Listener, public ListenerBase {
        
        public:
            Listener(const std::string &ip, uint16_t port) IPL_NOEXCEPT:
                Listener(DefaultProtocol::create, ip, port) {}
            Listener(const StreamProtocol::Create &create_protocol,
                     const std::string &ip, uint16_t port) IPL_NOEXCEPT:
                Listener(create_protocol, ip, port, Config()) {}
            Listener(const std::string &ip, uint16_t port,
                     const Config &config) IPL_NOEXCEPT:
                Listener(DefaultProtocol::create, ip, port, config) {}
            Listener(const StreamProtocol::Create &create_protocol,
                     const std::string &ip, uint16_t port,
                     const Config &config) IPL_NOEXCEPT;
            ~Listener() IPL_NOEXCEPT override;
            
            bool isValid() const IPL_NOEXCEPT override;
            void retry_accepted() IPL_NOEXCEPT override;
            
        protected:
            void enable() IPL_NOEXCEPT override;
            void disable() IPL_NOEXCEPT override;
            
            void got_socket(const osal::TCPSocket::Description &description) IPL_NOEXCEPT override;
            void error(const std::string &error) IPL_NOEXCEPT override;
            
            std::string error_description;
            std::unique_ptr<TransportTcp> transport;
            StreamProtocol::Create create_protocol;
        };

/****************************************************************************/

        class UTIL_EXPORT TransportTcp::Service:
            public TransportTcp {
        
        public:
            Service(const std::string &ip, uint16_t port) IPL_NOEXCEPT:
                Service(DefaultProtocol::create, ip, port, Config()) {}
            Service(const std::string &ip, uint16_t port,
                    const Config &config) IPL_NOEXCEPT:
                Service(DefaultProtocol::create, ip, port, config) {}
            Service(const StreamProtocol::Create &create_protocol,
                    const std::string &ip, uint16_t port) IPL_NOEXCEPT:
                Service(create_protocol, ip, port, Config()) {}
            Service(const StreamProtocol::Create &create_protocol,
                    const std::string &ip, uint16_t port,
                    const Config &config) IPL_NOEXCEPT;
            ~Service() IPL_NOEXCEPT override;
        
            bool isValid() const IPL_NOEXCEPT override;
            
        protected:
            class Listener: public ListenerBase {
                
            public:
                Listener(TransportTcp::Service *transport,
                         const std::string &ip, uint16_t port) IPL_NOEXCEPT:
                    ListenerBase(ip, port, Config(), false), transport(transport) {
                    // this needs to be done after ListenerBase or we get
                    // into a race with multiplexer
                    multiplexer->add(listener_socket, *this, true, false);
                }
                Listener(TransportTcp::Service *transport,
                         const std::string &ip, uint16_t port,
                         const Config &config) IPL_NOEXCEPT:
                    ListenerBase(ip, port, config, false), transport(transport) {
                    // this needs to be done after ListenerBase or we get
                    // into a race with multiplexer
                    multiplexer->add(listener_socket, *this, true, false);
                }
                ~Listener() IPL_NOEXCEPT override;
        
            protected:
                void got_socket(const osal::TCPSocket::Description &description) IPL_NOEXCEPT override;
                void error(const std::string &error) IPL_NOEXCEPT override;
                
                TransportTcp::Service *transport;
            };
            
            std::unique_ptr<Listener> listener;
        };

/****************************************************************************/

    }  // end of namespace astra
}  // end of namespace util

/****************************************************************************/
#endif
