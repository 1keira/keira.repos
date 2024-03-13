/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_RAWSOCKET_HXX
#define OSAL_RAWSOCKET_HXX

#include <ipl_config.h>

#include <osal/Socket.hxx>

namespace osal
{

/**
 * \brief
 *    Specialization of a Socket that implements raw data-link layer
 *    communication on network device level

 *     A RawSocket will not operate on the Network Layer i.e. protocols
 *     like UDP or TCP aren't involved when receiving or sending data.
 *     Instead you will obtain packets directly from the networking
 *     hardware without any headers stripped.
 *
 *     This allows you to:
 *
 *     - analyze ongoing traffic on a network device
 *     - hook yourself into the operation of certain higher level
 *     protocols like TCP or UDP
 *     - implement your own, all new protocol without having to enter
 *     the kernel space or the TCP/IP-stack space
 *
 *     Note, however, that sending on a raw socket is not currently
 *     implemented in OSAL.
 *
 *     A call to read() on a RawSocket returns one or more packets as
 *     seen on the network device. No partial packets will be returned,
 *     expect they're not fitting into the provided receive buffer.
 *
 *     On Win32 there currently is no implementation of RawSocket
 *     due to operating system restrictions. On these OS the
 *     constructor will always return a SysError with reason
 *     NOT_IMPLEMENTED.
 * \note
 *     For being able to see packets not only destined for the own
 *     network node but also packets that are passing by destined for
 *     other nodes you might need to enable the so called promiscuous
 *     mode for the network device you want to operate on.
 *
 *     To do this please refer to the \c osal::NetDevice class.
 * \note
 *     QNX requires you to perform read() calls with a specific
 *     buffer size. To acquire that size please refer to function
 *     getRequiredReadSize(). That OS also merges multiple packets into
 *     a single read() call. To iterate over all packets present in a
 *     buffer please refer to the getNextPacket() function.
 *
 *     If you perform read calls on QNX with unsuitable buffer
 *     sizes then the read calls will fail with an "invalid argument"
 *     error.
 **/
class OSAL_EXPORT RawSocket :
    // inherit the basic Socket
    public Socket
{
public:
    /**
     * \brief
     *     Construct a new RawSocket

     *     Regarding the parameters please refer to \c osal::Socket
     * \errors
     *     SysError with reasons:
     *
     *     - NOT_IMPLEMENTED if the OS doesn't support raw sockets
     *     - PERMISSION_DENIED if you don't have the priveleges to
     *     open a raw socket
     *     - UNKNOWN_ERROR on other occasions
     **/
    RawSocket(
        const bool p_blocking = true,
        const size_t p_input_buffer = 0,
        const size_t p_output_buffer = 0);

    /**
     * \brief
     *     Cleans up all associated ressources
     **/
    ~RawSocket();

    /**
     * \brief
     *     Closes the raw socket
     * 
     * \param discard_pending not used, needed due to override
     **/
    bool close(const bool discard_pending = false) override;

    /**
     * \brief
     *     Open the socket for the given network device

     *     If \c device is provided then the RawSocket will attempt
     *     to bind a network device named \c device. If there is
     *     not such device then the object will become invalid.
     *
     *     If \c device is NULL then an attempt is made to receive
     *     data from *any* interface in the system. This might not
     *     be supported by the operating system in which case an
     *     according error will raised and the open will fail.
     *
     *     If \c p_cooked_mode is \c true then data link layer
     *     headers will be passed to received packets, too.
     * \errors
     *     SysError with reasons:
     *
     *     - PERMISSION_DENIED if you don't have enough priveleges
     *     to open a raw socket on the given device
     *     - INVALID_DEVICE if the given device is no existing
     *     - NOT_SUPPORTED if \c device is NULL an listening on all
     *     interfaces is not supported or if \c device is not NULL
     *     but does not support opening a raw socket on it
     *     - UNKNOWN_ERROR on other occasions
     **/
    bool open(const char *device);

    /**
     * \brief
     *     Iterate to the next packet found in data returned by a
     *     read() call on a RawSocket

     *     A call to read() on a RawSocket can return multiple data
     *     link layer packets at once. Also additional operating
     *     sytem specific headers can be prepended to the actual
     *     packets.
     *
     *     That is why this helper function allows you to iterate
     *     from packet to packet without needing to know those
     *     operating system specific formats.
     * \param[in] recv_data
     *     A pointer to the beginning of the data previously
     *     received from a call to read(). Must not be NULL. Must
     *     not be any other data than that returned from a
     *     RawSocket's read call.
     * \param[in] recv_data_len
     *     The amount of bytes that have been read into the buffer
     *     located at \c recv_data.
     * \param[in] packet_base
     *     A pointer to the packet base pointer previously returned
     *     from this function. If you're calling this function the
     *     first time then set this parameter to NULL. Otherwise
     *     set this pointer to the value last returned from a call
     *     to this function.
     * \param[out] packet_offset
     *     An offset into the returned pointer that tells you where
     *     actual packet data starts. The pointer returned from
     *     this function still might point to proprietary headers,
     *     which is necessary for this function to iterate through
     *     the available messages by means of the information found
     *     in those proprietary headers. Thus you need to use the
     *     offset to find the actual packet data.
     * \param[out] packet_len
     *     The amount of bytes the packet found at the returned
     *     address plus the \c packet_offset consists of.
     * \return
     *     A base pointer to the next packet. NULL if no more
     *     packets are available. The returned pointer must only be
     *     accessed at the offset returned in \c packet_offset!
     **/
    inline static void* getNextPacket(
        void *recv_data,
        size_t recv_data_len,
        void *packet_base,
        size_t &packet_offset,
        size_t &packet_len);

    /**
     * \brief
     *     Returns the size your buffer needs to have for
     *     successfull read() calls on a RawSocket

     *     On certain OSs you can't call read() with arbitrary
     *     buffer sizes. That's why you need to query this value
     *     and provide an appropriatly dimensioned buffer to
     *     read(). Otherwise you will get an INVALID_SOCKET error
     *     on those OSs.
     *
     *     If there is no restriction on read sizes on the current
     *     OS then this function returns zero and you can choose an
     *     suitable buffer size yourself. A typical buffer size for
     *     ethernet based devices is 1500 bytes for example, to fit
     *     the MTU.
     **/
    size_t getRequiredReadSize() const;

protected: // functions

#ifdef IPL_OS_QNX
    // on QNX we need to overwrite the Socket's default read/write
    virtual bool performRead(
        void* const p_read_buffer,
        const size_t p_max_bytes,
        size_t &p_bytes_read) IPL_NOEXCEPT;

    virtual bool performWrite(
        const void* const p_write_buffer,
        const size_t p_max_bytes,
        size_t &p_bytes_written) IPL_NOEXCEPT;
#endif
}; // end class

} // end namespace

#if defined IPL_OS_ANDROID || defined IPL_OS_LINUX
#    include "linux/RawSocket.inl"
#elif defined IPL_OS_QNX
#    include "qnx/RawSocket.inl"
#elif defined IPL_OS_WINPC
#    include "win32/RawSocket.inl"
#elif defined IPL_OS_INTEGRITY
#    include "integrity/RawSocket.inl"
#else
#    error "error undefined IPL_OS_ variant"
#endif

#endif // OSAL_RAWSOCKET_HXX
