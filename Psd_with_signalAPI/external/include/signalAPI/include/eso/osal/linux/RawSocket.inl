/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

namespace osal
{

inline void* RawSocket::getNextPacket(
    void *recv_data,
    size_t recv_data_len,
    void *packet_base,
    size_t &packet_offset,
    size_t &packet_len)
{
    /*
     * on Linux we always get exactly one packet without magic
     * headers attached. simple enough.
     */

    if( packet_base )
    {
        return NULL;
    }

    packet_offset = 0;
    packet_len = recv_data_len;
    return recv_data;
}

inline size_t RawSocket::getRequiredReadSize() const
{
    return 0;
}

} // end ns osal
