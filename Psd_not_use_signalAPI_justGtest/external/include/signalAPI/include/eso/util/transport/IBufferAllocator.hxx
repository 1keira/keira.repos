/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_TRANSPORT_IBUFFERALLOCATOR_HXX
#define UTIL_TRANSPORT_IBUFFERALLOCATOR_HXX

#include <ipl_config.h>
#include <util/util_dso.h>
#include <util/transport/ITransport.hxx>
#include <util/transport/Buffer.hxx>

namespace util {
    namespace transport {

        /**
         * \brief
         *     The BufferAllocator is a class that allocates transport buffers.
         *
         *     Buffer management is the responsibility of the transport. Different transports may
         *     have different requirements to buffer management - e.g most buffers may be allocated on
         *     the heap, while some transport might want to allocate buffers from shared memory.
         *
         *     If a transport needs to delegate buffer allocation it can pass an IBufferAllocator
         *     so that it still maintains control over buffer allocation.
         **/
        class UTIL_EXPORT IBufferAllocator {
            public:
                IBufferAllocator() IPL_NOEXCEPT {}

                virtual ~IBufferAllocator() IPL_NOEXCEPT {}

                /* \brief allocates a buffer */
                virtual Buffer::BufferPtr allocate( size_t size ) IPL_NOEXCEPT = 0;
        };

    }
}

#endif // UTIL_TRANSPORT_IBUFFERALLOCATOR_HXX
