/*
    Copyright 2021 e.solutions GmbH
    All rights reserved
*/

#ifndef COMM_CALL_HXX
#define COMM_CALL_HXX

#include <ipl_config.h>
#include <comm/comm_dso.h>
#include <comm/commtypes.hxx>
#include <common/buffers.hxx>
#include <util/transport/Writeable.hxx>

#include <cstddef>

namespace util {
    class ByteBufferWriter;
}

namespace comm {
    struct Session;

    /*! Internal Interface to comm call related data used form genereated code  */
    class COMM_EXPORT ICall {
        public:

            ICall() IPL_NOEXCEPT = default;
            virtual ~ICall() IPL_NOEXCEPT = default;
        
            virtual bool call() IPL_NOEXCEPT = 0;

            // size of the serialized call payload
            virtual size_t size() const IPL_NOEXCEPT = 0;

            // write yourself into a buffer
            virtual bool write(ipl::Buf&) const IPL_NOEXCEPT = 0;
            virtual bool write(const util::transport::Writeable&) const IPL_NOEXCEPT = 0;
            
            virtual Session& session() IPL_NOEXCEPT = 0;
            virtual MethodID mid() const IPL_NOEXCEPT = 0;
    };

    class COMM_EXPORT CallBase : public ICall {
        public:

            CallBase(comm::Session& session, MethodID mid) IPL_NOEXCEPT;

            ~CallBase() IPL_NOEXCEPT override = default;
        
            Session& session() IPL_NOEXCEPT final {
                return m_session;
            }

            MethodID mid() const IPL_NOEXCEPT final {
                return m_mid;
            }

        protected:
            Session&        m_session;
            comm::MethodID  m_mid;
    };

    class COMM_EXPORT RPCCall : public CallBase {
        public:
            RPCCall(comm::Session& session
                    ,size_t payload_size
                    ,util::ByteBufferWriter& payload_writer
                    ,comm::MethodID mid
                    ) IPL_NOEXCEPT;

            bool call() IPL_NOEXCEPT override;
        
            bool write(ipl::Buf&) const IPL_NOEXCEPT override;
            bool write(const util::transport::Writeable&) const IPL_NOEXCEPT override;
            
            size_t size() const IPL_NOEXCEPT override;
            
        private:
            util::ByteBufferWriter&    m_payload_writer;
            size_t                     m_payload_size;
    };

    class COMM_EXPORT LocalCall : public CallBase {
        public:
            LocalCall(comm::Session& session
                    ,void* data
                    ,comm::MethodID mid
                    ) IPL_NOEXCEPT;

            size_t size() const IPL_NOEXCEPT override;
        
            bool write(ipl::Buf&) const IPL_NOEXCEPT override;
            bool write(const util::transport::Writeable&) const IPL_NOEXCEPT override;

            bool call() IPL_NOEXCEPT override;
            
        private:
            void*             m_data{nullptr};
    };
}


#endif // COMM_CALL_HXX

