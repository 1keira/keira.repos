/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/
/****************************************************************************/
#ifndef UTIL_STREAMPROTOCOLCLASSIC_HXX
#define UTIL_STREAMPROTOCOLCLASSIC_HXX
/****************************************************************************/

#include "StreamProtocol.hxx"
#include <util/transport/MessageSizeSerialization.hxx>  // Classic

/****************************************************************************/

namespace util {

/*****************************************************************************/

    /*!
        \brief Classic Framing Protocol using a plain, network byte order
        32 bit payload length
    */
    class UTIL_EXPORT StreamProtocolClassic: public StreamProtocol {
    
    public:
        static /* Create */ std::unique_ptr<StreamProtocol> create(
            Client *client, ipl::Buf::Allocator &underlying
        );
        static /* Factory */ Create factory(Descriptor &descriptor);
        
        StreamProtocolClassic(Client *client, ipl::Buf::Allocator &underlying,
                              size_t max_bytes=0xffffffffu):
            StreamProtocol(client, max_bytes),
            allocator(transport::MessageSizeSerialization::DATASIZE, underlying)
        {
            IPL_ASSERT(!(max_bytes>0xffffffffu));
        }
        
        ipl::Buf malloc(size_t bytes) const IPL_NOEXCEPT override;

        ipl::Buf prepare(const ipl::Buf &data) override;
        
        ipl::Buf realloc_header(const ipl::Buf &data) override;
        Result parse_header(const ipl::Buf &data) override;
        
        static const char *const name;
        
    protected:
        ipl::Buf::PreAllocator allocator;
    };

/****************************************************************************/

}  // end of namespace util

/****************************************************************************/
#endif
