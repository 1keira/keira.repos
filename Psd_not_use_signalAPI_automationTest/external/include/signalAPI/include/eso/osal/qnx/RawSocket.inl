/*
    Copyright esolutions GmbH
    All rights reserved
    Authors:
        Matthias Gerstner
    $Id: $
*/

#include <net/bpf.h>

namespace osal {

    inline void* RawSocket::getNextPacket(
        void *recv_data,
        size_t recv_data_len,
        void *packet_base,
        size_t &packet_offset,
        size_t &packet_len)
    {
        /*
        * On QNX with the BPF device we need to deal with a packet
        * stream and bpf_hdr structs prepended to each packet
        */
        struct bpf_hdr *h;

        if( ! packet_base )
        {
            h = (bpf_hdr*)recv_data;
            packet_len = h->bh_caplen;
            packet_offset = h->bh_hdrlen;
            return recv_data;
        }
        else
        {
            h = (bpf_hdr*)packet_base;
            // advance to the next packet
            h = (bpf_hdr*)((char*)h + BPF_WORDALIGN(h->bh_caplen + h->bh_hdrlen));

            if( (char*)h >= (char*)recv_data + recv_data_len )
                return NULL;

            packet_offset = h->bh_hdrlen;
            packet_len = h->bh_caplen;

            return h;
        }
    }

} // end ns osal
