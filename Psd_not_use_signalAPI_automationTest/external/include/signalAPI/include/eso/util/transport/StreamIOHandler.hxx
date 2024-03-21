/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_STREAM_IO_HANDLER_HXX
#define UTIL_STREAM_IO_HANDLER_HXX

#include <ipl_config.h>
#include <util/util_dso.h>
#include <util/transport/Readable.hxx>
#include <util/transport/Buffer.hxx>

namespace util
{
    namespace transport
    {

        /**
            \brief Adapter for reading and writing Readables and Buffers via I/O channels
            (e.g. sockets etc.)
        **/
        class UTIL_EXPORT StreamIOHandler {
            public:

                StreamIOHandler() {}
                virtual ~StreamIOHandler() {}

                struct Result {
                    size_t  nbytes; // number of bytes read/sent
                    bool    has_error;  // presence of an error

                    // default: Error, no data
                    Result(): nbytes(0u), has_error(true) {}

                    // amount and error/no error
                    explicit Result(size_t nbytes, bool error)
                    : nbytes(nbytes), has_error(error)
                    {
                    }

                    // OK: with data
                    explicit Result(size_t amount)
                    : nbytes(amount), has_error(false)
                    {
                    }

                    size_t amount() const { return nbytes; }
                    bool error() const { return has_error; }
                };

                // sends the Readable
                virtual Result send ( const Readable& w ) IPL_NOEXCEPT = 0;

                // a tag we may expect when receiving data
                struct Tag {
                    const uint8_t*  data;       // tag data to compare
                    size_t          length;     // tag length

                    Tag(): data(0), length(0u) {}

                    Tag(const uint8_t* data, size_t dlen)
                    : data(data)
                    , length(dlen)
                    {
                    }
                };

                // receives data.
                // Tries to fill the buffer.
                // buffer_cap contains the capacity of the buffer
                // buffer_amount contains the amount already in the buffer.
                // returns earlier if the data read-in doesn't match the tag
                // tag may be a nullptr, then no tag verification is done
                // returns the number of bytes read and an error marker in Result
                // End of stream is indicated by 0 bytes read, error
                // and error-id transport::TransportErrors::CONNECTION_LOST

                virtual Result receive( uint8_t* buffer
                                        ,size_t buffer_cap
                                        ,size_t buffer_amount=0
                                        ,const Tag* tag=0 ) IPL_NOEXCEPT = 0;
        };

    }
}

#endif // UTIL_STREAM_IO_HANDLER_HXX

