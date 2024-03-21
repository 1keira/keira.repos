/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_PROTOCOLS_HXX
#define OSAL_PROTOCOLS_HXX

#include <osal/Socket.hxx>

namespace osal
{

/**
 * \brief
 *     Network protocol data types and constants

 *     This header defines data types, constants and structures for
 *     common protocols like TCP/IP, UDP/IP, Ethernet and similar.
 **/
struct Protocols
{
    // internet protocol numbers in host byte order found e.g. in
    // ethernet headers
    enum Protocol
    {
        // the IPv4 protocol
        IPv4 = 0x0800,
        // v6
        IPv6 = 0x86dd,
        // the address resolution protocl
        ARP = 0x0806,
        UNKNOWN_PROTOCOL = 0xFFFFFFFF
    };

    // IP protocol numbers found in IP headers
    enum IPProtocol
    {
        ICMP = 1,
        TCP = 6,
        UDP = 17,
        // common address redundancy protocol
        CARP = 112
    };

    /**
     * \brief
     *     Structure of an Ethernet frame header
     **/
    struct EthernetHeader
    {
        //! MAC address of the destination node
        uint8_t destination_address[6];
        //! MAC address of the sending node
        uint8_t source_address[6];
        //! Protocol number the rest of the frame's data is for
        uint16_t type;
    };

    /**
     * \brief
     *     Structure of an IP header
     **/
    struct IPHeader
    {
#ifdef IPL_FW_LITTLE_ENDIAN
        // length of the header in 32-bit words
        unsigned ihl:4;
        // version of the IP protocol that is in use
        unsigned version:4;
#else
        unsigned version:4;
        unsigned ihl:4;
#endif
        unsigned service:8;
        // length of the complete message in bytes, in network
        // order
        unsigned length:16;
        // identification of the datagram that this fragment
        // belongs to
        unsigned ident:16;
        unsigned unused:1;
#ifdef IPL_FW_LITTLE_ENDIAN
        // the number of this fragment
        unsigned fragment_nr:13;
        // set if more fragments for this datagram are coming
        // up, or the datagram is finished
        unsigned more_fragments:1;
        // request not to fragment this datagram
        unsigned dont_fragment:1;
#else
        unsigned dont_fragment:1;
        unsigned more_fragments:1;
        unsigned fragment_nr:13;
#endif
        // maximum number of hops left allowed
        unsigned ttl:8;
        // the specific IP protocol the datagram is destined for
        unsigned protocol:8;
        // IP checksum
        unsigned checksum:16;
        // source IP
        unsigned src_addr:32;
        // dest IP
        unsigned dst_addr:32;
    };

    /**
     * \brief
     *     Structure of the UDP/ip header
     **/
    struct UDPHeader
    {
        uint16_t src_port;
        uint16_t dst_port;
        // includes the 8 byte header
        uint16_t length;
        uint16_t checksum;
    };

    /**
     * \brief
     *     Structure of the TCP/ip header
     **/
    struct TCPHeader
    {
        uint16_t src_port;
        uint16_t dst_port;
        uint32_t seq_nr;
        uint32_t ack_nr;
#ifdef IPL_FW_LITTLE_ENDIAN
        unsigned reserved1:4;
        // length of the header in 32-bit words
        unsigned header_len:4;
#else
        unsigned header_len:4;
        unsigned reserved1:4;
#endif
        unsigned reserved2:2;
        // whether urgent_ptr is in use
        unsigned urgent:1;
        // whether ack_nr is in use
        unsigned ack_set:1;
        // request not to buffer but reply immediatly
        unsigned push:1;
        // connection reset/reject
        unsigned reset:1;
        // connection request init/reply (depending on ACK)
        unsigned syn:1;
        // connection is finished for the sender
        unsigned fin:1;
        uint16_t window;
        uint16_t checksum;
        uint16_t urgent_ptr;
    };
}; // end class

} // end namespace

#endif
