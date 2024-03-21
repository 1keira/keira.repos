/*
    Copyright 2021 e.solutions GmbH
    All rights reserved
*/

#ifndef COMM_ICALLPAYLOAD_HXX
#define COMM_ICALLPAYLOAD_HXX


#include <ipl_config.h>
#include <comm/comm_dso.h>
#include <util/transport/Readable.hxx>
#include <common/buffers.hxx>

#include <cstdint>
#include <cstddef>

namespace comm {
    /*
        This interface is used by the generated code.
    */

    /*! Provides access to data associated with comm calls */
    // This contains all Arguments of comm method calls
    class COMM_EXPORT ICallPayload {
        public:
            virtual ~ICallPayload() IPL_NOEXCEPT = default;  

            //! Access to the payload's data
            virtual const uint8_t* data() const IPL_NOEXCEPT = 0;

            /** Size of the payload.

                Always returns 0 if is_structured() is true.
            */
            virtual size_t size() const IPL_NOEXCEPT = 0;

            /** Is the value returned in data() a pointer to structured (objects in memory) or packed/serialized data.

                Returns true for structured.
            */
            virtual bool is_structured() const IPL_NOEXCEPT = 0;

            /**
                Returns a copy of the payload's data.

                Returns an empty Buf in case of failure.
                Fails always if is_structured() is true.
                An empty buf is not a failure if size() is 0;
                The returned buffer is owned by the caller.
                
            */
            virtual ipl::Buf copy_b() const IPL_NOEXCEPT = 0;
        
            /**
                Return a copy of the payload's data.

                Returns an empty redable in case of failure.
                Fails always if is_structured() is true.
                An empty Readable is not a failure if size() is 0;
            */
            virtual util::transport::Readable copy_r() const IPL_NOEXCEPT = 0;
    };
}


#endif // COMM_CALLPAYLOAD_HXX
