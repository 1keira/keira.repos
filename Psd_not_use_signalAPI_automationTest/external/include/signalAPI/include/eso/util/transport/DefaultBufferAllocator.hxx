/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_TRANSPORT_DEFAULTBUFFERALLOCATOR_HXX
#define UTIL_TRANSPORT_DEFAULTBUFFERALLOCATOR_HXX

#include <ipl_config.h>
#include <util/util_dso.h>
#include <util/transport/IBufferAllocator.hxx>

namespace util {
    namespace transport {

        /**
         * \brief
         *     Allocates buffer from the heap.
         *
         **/
        class UTIL_EXPORT DefaultBufferAllocator : public IBufferAllocator {
            public:
                DefaultBufferAllocator() IPL_NOEXCEPT;

                virtual ~DefaultBufferAllocator() IPL_NOEXCEPT;

                virtual Buffer::BufferPtr allocate( size_t size ) IPL_NOEXCEPT;

        };

    }
}

#endif // UTIL_TRANSPORT_DEFAULTBUFFERALLOCATOR_HXX
