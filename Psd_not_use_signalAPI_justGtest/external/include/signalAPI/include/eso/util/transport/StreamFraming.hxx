/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_STREAM_FRAMING_HXX
#define UTIL_STREAM_FRAMING_HXX

#include <ipl_config.h>
#include <util/util_dso.h>
#include <util/transport/Readable.hxx>
#include <util/transport/Buffer.hxx>
#include <util/transport/IBufferAllocator.hxx>
#include <util/SharedPtr.hxx>
#include <util/transport/PeerInfoPtrForward.hxx>
#include <util/transport/factory/TransportConfig.hxx>
namespace util
{
    namespace transport
    {

        class StreamFraming;
        class StreamIOHandler;

        typedef util::SharedPtr<StreamFraming> StreamFramingPtr;

        /**
            \brief Transport framing layer interface for byte stream I/O.
        **/
        class UTIL_EXPORT StreamFraming {
            public:

                /**
                    \brief creates an adapter by name or returns an empty pointer.
                **/
                static StreamFramingPtr create(const TransportConfig::TransportProtocol& tp
                                                ,StreamIOHandler& io
                                                ,IBufferAllocator& buffer_allocator
                                            ) IPL_NOEXCEPT;

                StreamFraming() IPL_NOEXCEPT {}

                virtual ~StreamFraming() IPL_NOEXCEPT {}

                virtual size_t getHeaderSize() const IPL_NOEXCEPT = 0;

                /**
                    \brief Sends the passed Writable after adding its header.

                    size is the payload in the Writable at starting at offset getHeaderSize().
                **/
                virtual bool send ( size_t size, Writeable& w) IPL_NOEXCEPT = 0;

                /**
                    \brief Receives a Readable.

                    If the message to be received exceeds limit, an error is raised.
                    In case of errors an empty Readable is returned.
                **/
                virtual Readable receive( size_t limit ) IPL_NOEXCEPT = 0;

                struct Buffered {
                    Buffer::BufferPtr   data;
                    size_t              amount;

                    Buffered(): amount(0u) {}

                    void reset() {
                        amount = 0;
                        data = Buffer::BufferPtr();
                    }

                };

                /**
                    \brief opens the framing layer.

                    recv_first indicates that the framing layer should try to receive first.
                    instead of sending first during the protocol exchange for open() if there
                    is any.
                    This helps to handle a downgrade-to-classic case and should generally be false.

                    buffered is in/out: when passed it is the amount of data already received
                    from an earlier open attempt,
                    If open returns with error, the already read-in data is  returned in buffered.
                **/
                virtual bool open( Buffered& buffered, bool recv_first=false ) IPL_NOEXCEPT = 0;

                virtual bool close() IPL_NOEXCEPT = 0;

                virtual PeerInfoPtr getPeerInfo() const IPL_NOEXCEPT = 0;
        };

    }
}

#endif // UTIL_STREAM_FRAMING_HXX

