/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/
/****************************************************************************/
#ifndef UTIL_ASTRA_TRANSPORT_UNIX_HXX
#define UTIL_ASTRA_TRANSPORT_UNIX_HXX
/****************************************************************************/

#include "TransportStreamSocket.hxx"
#include "Listener.hxx"
#include <util/Descriptor.hxx>

#include <osal/UnixSocket.hxx>
#include <osal/UnixServerSocket.hxx>
#include <osal/Thread.hxx>

#include <memory>

#include <util/util_dso.h>

/****************************************************************************/

namespace util {
    namespace astra {

/****************************************************************************/

        /*!
            \brief Unix Domain Socket based Transport
        */
        class UTIL_EXPORT TransportUnix:
            public TransportStreamSocket {
                
        protected:
            
            class ListenerBase;
        
        public:
            
            class Listener;
            class Service;
            
            TransportUnix(const StreamProtocol::Create &create_protocol,
                          const std::string &path) IPL_NOEXCEPT:
                TransportUnix(create_protocol, path, Config()) {}
            TransportUnix(const std::string &path,
                          const Config &config) IPL_NOEXCEPT:
                TransportUnix(DefaultProtocol::create, path, config) {}
            TransportUnix(const std::string &path) IPL_NOEXCEPT:
                TransportUnix(DefaultProtocol::create, path, Config()) {}
            TransportUnix(const StreamProtocol::Create &create_protocol,
                          const std::string &path,
                          const Config &config) IPL_NOEXCEPT;
                         
            static const char *const scheme;
            static bool is_listener(const Descriptor &descriptor) IPL_NOEXCEPT;
            static std::unique_ptr<TransportUnix>
                create_transport(const Descriptor &descriptor) IPL_NOEXCEPT;
            static std::unique_ptr<Listener>
                create_listener(const Descriptor &descriptor) IPL_NOEXCEPT;
                
            void io_connected(
                const osal::IoMultiplexer::Channel *channel
            ) IPL_NOEXCEPT override;
            
        protected:
            explicit TransportUnix(const StreamProtocol::Create &create_protocol) IPL_NOEXCEPT:
                TransportStreamSocket(create_protocol) {}
            
            void from_description(
                const osal::UnixSocket::Description &description,
                const Config &config
            ) IPL_NOEXCEPT;
            
            static std::string crop_path(const std::string &path) {
                if(address_type(path)==osal::UnixSocketBase::ABSTRACT)
                    return path.substr(1);
                return path;
            }
            static osal::UnixSocketBase::NameSpace address_type(const std::string &path) {
                if(path.size() && (path[0]==0 || path[0]=='@'))
                    return osal::UnixSocketBase::ABSTRACT;
                return osal::UnixSocketBase::FILESYSTEM;
            }
    

            
            static const char *const kw_listen_1;
            static const char *const kw_listen_many;
        };

/****************************************************************************/

        //! \internal
        //! \brief Common functionality for single and multi connection listeners
        //!
        //! Classes inheriting this must make sure to remove their socket
        //! from the multiplexer within \b their \b own destructor, else
        //! the multiplexer might call baseclass versions of the callbacks
        //! and crash.
        class TransportUnix::ListenerBase: public osal::IoMultiplexer::Client {
            
        public:
            ListenerBase(const std::string &path,
                         const Config &config, bool retry_accept) IPL_NOEXCEPT;
            
            bool isValid() const IPL_NOEXCEPT;
            bool io_read(
                const osal::IoMultiplexer::Channel *channel
            ) IPL_NOEXCEPT override;

        protected:
            virtual void got_socket(const osal::UnixSocket::Description &description) IPL_NOEXCEPT=0;
            virtual void error(const std::string &error) IPL_NOEXCEPT=0;
            
            // Workaround around Description sillyness
            osal::UnixSocket::Description accept_connection() IPL_NOEXCEPT {
                return listener_socket.acceptConnection();
            }
            
            void from_description(TransportUnix *transport,
                                  const osal::UnixSocket::Description &description,
                                  const Config &config) IPL_NOEXCEPT {
                transport->from_description(description, config);
            }
            
            ipl::Shared<osal::IoMultiplexer>::Ptr
                multiplexer{osal::IoMultiplexer::DEFAULT};
                
            osal::UnixServerSocket listener_socket;
                
            Config config;
            bool retry_accept;
        };

/****************************************************************************/

        class UTIL_EXPORT TransportUnix::Listener:
            public astra::Listener, public ListenerBase {
        
        public:
            Listener(const std::string &path) IPL_NOEXCEPT:
                Listener(DefaultProtocol::create, path) {}
            Listener(const StreamProtocol::Create &create_protocol,
                     const std::string &path) IPL_NOEXCEPT:
                Listener(create_protocol, path, Config()) {}
            Listener(const std::string &path,
                     const Config &config) IPL_NOEXCEPT:
                Listener(DefaultProtocol::create, path, config) {}
            Listener(const StreamProtocol::Create &create_protocol,
                     const std::string &path,
                     const Config &config) IPL_NOEXCEPT;
            ~Listener() IPL_NOEXCEPT override;
            
            bool isValid() const IPL_NOEXCEPT override;
            void retry_accepted() IPL_NOEXCEPT override;
            
        protected:
            void enable() IPL_NOEXCEPT override;
            void disable() IPL_NOEXCEPT override;
            
            void got_socket(const osal::UnixSocket::Description &description) IPL_NOEXCEPT override;
            void error(const std::string &error) IPL_NOEXCEPT override;
            
            std::string error_description;
            std::unique_ptr<TransportUnix> transport;
            StreamProtocol::Create create_protocol;
        };

/****************************************************************************/

        class UTIL_EXPORT TransportUnix::Service:
            public TransportUnix {
        
        public:
            Service(const std::string &path) IPL_NOEXCEPT:
                Service(DefaultProtocol::create, path, Config()) {}
            Service(const std::string &path,
                    const Config &config) IPL_NOEXCEPT:
                Service(DefaultProtocol::create, path, config) {}
            Service(const StreamProtocol::Create &create_protocol,
                    const std::string &path) IPL_NOEXCEPT:
                Service(create_protocol, path, Config()) {}
            Service(const StreamProtocol::Create &create_protocol,
                    const std::string &path,
                    const Config &config) IPL_NOEXCEPT;
            ~Service() IPL_NOEXCEPT override;
        
            bool isValid() const IPL_NOEXCEPT override;
            
        protected:
            class Listener: public ListenerBase {
                
            public:
                Listener(TransportUnix::Service *transport,
                         const std::string &path) IPL_NOEXCEPT:
                    ListenerBase(path, Config(), false), transport(transport) {
                    // this needs to be done after ListenerBase or we get
                    // into a race with multiplexer
                    multiplexer->add(listener_socket, *this, true, false);
                }
                Listener(TransportUnix::Service *transport,
                         const std::string &path,
                         const Config &config) IPL_NOEXCEPT:
                    ListenerBase(path, config, false), transport(transport) {
                    // this needs to be done after ListenerBase or we get
                    // into a race with multiplexer
                    multiplexer->add(listener_socket, *this, true, false);
                }
                ~Listener() IPL_NOEXCEPT override;
        
            protected:
                void got_socket(const osal::UnixSocket::Description &description) IPL_NOEXCEPT override;
                void error(const std::string &error) IPL_NOEXCEPT override;
                
                TransportUnix::Service *transport;
            };
            
            std::unique_ptr<Listener> listener;
        };

/****************************************************************************/

    }  // end of namespace astra
}  // end of namespace util

/****************************************************************************/
#endif
