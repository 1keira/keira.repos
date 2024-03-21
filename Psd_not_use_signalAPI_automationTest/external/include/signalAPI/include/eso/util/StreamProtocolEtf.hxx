/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/
/****************************************************************************/
#ifndef UTIL_STREAMPROTOCOLETF_HXX
#define UTIL_STREAMPROTOCOLETF_HXX
/****************************************************************************/

#include <util/util_dso.h>
#include <util/StreamProtocol.hxx>
#include <util/transport/ETFH.hxx>
#include <util/transport/ETFToken.hxx>
#include <util/transport/PeerInfo.hxx>

#include <memory>

/****************************************************************************/

namespace util {

/****************************************************************************/

    /*!
        \warning This contains state, so do not share between Transports!
    */
    // https://intra.esolutions.de/wiki/doku.php?id=knowledge:framework:mib:comm:transport_framing
    class StreamProtocolEtf: public StreamProtocol {
        
    public:
        static /* Factory */ Create factory(Descriptor &descriptor);

        StreamProtocolEtf(Client *client, ipl::Buf::Allocator &underlying,
                          bool send_peerinfo=true):
            StreamProtocol(client, 0x3fffffff /* < *tag */),
#ifdef IPL_TOKEN_IS_DUMMY
            state_tx{State::eoi},
#else
            state_tx{send_peerinfo? State::token : State::eoi},
#endif
            allocator(transport::ETFH::headerSize(), underlying)
        {
            (void)send_peerinfo;  // ifdef IPL_TOKEN_IS_DUMMY...
//                 std::cerr << "### StreamProtocolEtf" << this << "::Protocol: state_tx=" << (int)state_tx << "\n";
        }
        
        ipl::Buf initial_message() IPL_NOEXCEPT override;
        bool internal_payload(const Context &header,
                              const ipl::Buf &data) IPL_NOEXCEPT override;
        
        ipl::Buf malloc(size_t bytes) const IPL_NOEXCEPT override;

        ipl::Buf prepare(const ipl::Buf &data) override;
        
        ipl::Buf realloc_header(const ipl::Buf &data) override;
        Result parse_header(const ipl::Buf &data) override;
        
        transport::ETFH header_tx{0, 0};  // initializes tag
        
        static const char *const name;
    
    protected:
        enum class State { token, eoi, data };
        State state_tx{State::token};
        
        ipl::Buf::PreAllocator allocator;
        
        static const char *const kw_no_peerinfo;
    };

/****************************************************************************/

}  // end of namespace util

/****************************************************************************/
#endif
