/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/
/****************************************************************************/
#ifndef UTIL_ASTRA_TRANSPORTSTREAMSOCKET_HXX
#define UTIL_ASTRA_TRANSPORTSTREAMSOCKET_HXX
/****************************************************************************/

#include "Transport.hxx"
#include <util/StreamProtocolClassic.hxx>
#include <threadsafe/Condition.hxx>

#include <util/util_dso.h>

#include <list>

/****************************************************************************/

namespace util {
    namespace astra {

/****************************************************************************/

        /*!
            \brief Transport over any stream based Socket
        */
        class UTIL_EXPORT TransportStreamSocket:
            public Transport, public osal::IoMultiplexer::Client,
            public StreamProtocol::Client {
                
        public:
            
            //! Common configuration options for stream based Transports
            struct UTIL_EXPORT Config {
                //! \brief Maximum message size
                //!
                //! This is \e inclusive, and the special value 0 means
                //! "use default".
                size_t max_bytes{0};
                
                explicit Config(Descriptor &descriptor /* patches descriptor */) IPL_NOEXCEPT;
                Config() IPL_NOEXCEPT=default;
            };

            /*!
                Any constructor must call start_with_initial_message(),
                but not before the object is fully constructed. This means
                when you use this class plain, it must call it, but when you
                derive from this class, \b you must call it at the end of
                \b your constructor. That's why there is a flag
                \p i_call_start_with_initial_message_myself -- if you just
                create a TransportStreamSocket object, leave it at its default
                and start_with_initial_message() will be called automatically,
                but when you inherit this class, set it to \c true and
                call the method yourself.
                \{
            */
            TransportStreamSocket(const StreamProtocol::Create &create_protocol,
                                  std::unique_ptr<osal::Socket> &&socket,
                                  bool i_call_start_with_initial_message_myself=false
                                 ) IPL_NOEXCEPT;
            TransportStreamSocket(const StreamProtocol::Create &create_protocol,
                                  std::unique_ptr<osal::Socket> &&socket,
                                  size_t max_bytes,
                                  bool i_call_start_with_initial_message_myself=false
                                 ) IPL_NOEXCEPT:
                TransportStreamSocket(create_protocol, std::move(socket), true) {
                    
                if(max_bytes) {
                    if(max_bytes>this->max_bytes) {
                        ipl_raise(final_error, 1, "configured max message size exceeds protocol's");
                        this->socket.reset();  // invalidates
                    } else
                        this->max_bytes=max_bytes;
                }
                if(!i_call_start_with_initial_message_myself)
                    start_with_initial_message();
            }
            TransportStreamSocket(std::unique_ptr<osal::Socket> &&socket,
                                  size_t max_bytes,
                                  bool i_call_start_with_initial_message_myself=false
                                 ) IPL_NOEXCEPT:
                TransportStreamSocket(DefaultProtocol::create,
                                      std::move(socket), max_bytes,
                                      i_call_start_with_initial_message_myself) {}
            explicit TransportStreamSocket(std::unique_ptr<osal::Socket> &&socket,
                bool i_call_start_with_initial_message_myself=false) IPL_NOEXCEPT:
                TransportStreamSocket(DefaultProtocol::create,
                                      std::move(socket),
                                      i_call_start_with_initial_message_myself) {}
            /*! \} */
            ~TransportStreamSocket() IPL_NOEXCEPT override;
            
            ipl::Buf malloc(size_t bytes) const IPL_NOEXCEPT override;
            bool isValid() const IPL_NOEXCEPT override;
            bool send(const ipl::Buf &data) IPL_NOEXCEPT override;
            void retry() IPL_NOEXCEPT override;
            
            bool io_read(
                const osal::IoMultiplexer::Channel *channel
            ) IPL_NOEXCEPT override;
            bool io_write(
                const osal::IoMultiplexer::Channel *channel
            ) IPL_NOEXCEPT override;
            
            void peerinfo(
                const std::shared_ptr<transport::PeerInfo> &peerinfo
            ) IPL_NOEXCEPT override;
            
        protected:
            explicit TransportStreamSocket(const StreamProtocol::Create &create_protocol) IPL_NOEXCEPT:
                protocol(create_protocol(this, ipl::Buf::DEFAULT_ALLOCATOR)) {
                max_bytes=protocol->max_bytes;
            }
            
            void enable() IPL_NOEXCEPT override;
            void disable() IPL_NOEXCEPT override;
            
            bool call_received() IPL_NOEXCEPT;  // hold mutex while calling!
            void error(const std::string &error) IPL_NOEXCEPT;
            void start_with_initial_message() {
                threadsafe::Mutex::Guard lock(mutex);
                IPL_ASSERT(!send_buf);
                send_buf=protocol->initial_message();
                IPL_ASSERT(socket);
                multiplexer->add(*socket, *this, false, send_buf);
                send_enabled=true;
            }

            ipl::Shared<osal::IoMultiplexer>::Ptr
                multiplexer{osal::IoMultiplexer::DEFAULT};
            std::unique_ptr<osal::Socket> socket;
            std::unique_ptr<StreamProtocol> protocol;
            size_t max_bytes=(size_t)-1;
            
            bool send_enabled{false};
            bool already_enabled{false};
            std::string error_description;
            ipl::Buf send_buf;
            bool internal_message{false};
            StreamProtocol::Context internal_header;
            bool receive_payload{false};
            ipl::Buf receive_buf;
            ipl::Buf receive_chunk;
            using PeerInfos=std::list<std::shared_ptr<transport::PeerInfo>>;
            PeerInfos peerinfos;

            using DefaultProtocol=StreamProtocolClassic;
            
            static const char *const kw_protocol;  // shared between children
            static const char *const kw_max_bytes;
        };

/****************************************************************************/

    }  // end of namespace astra
}  // end of namespace osal

/****************************************************************************/
#endif
