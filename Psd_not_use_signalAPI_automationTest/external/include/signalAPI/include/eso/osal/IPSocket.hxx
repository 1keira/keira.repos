/*
    Copyright e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_IPSOCKET_HXX
#define OSAL_IPSOCKET_HXX

#include <ipl_config.h>

#include <osal/Socket.hxx>
#include <osal/IPObject.hxx>

#include <common/streams/ostream.hxx>
#include <common/types/string.hxx>
#include <common/types/algorithm.hxx>
#include <common/CommonError.hxx>

namespace osal
{

/**
 * \brief
 *     Specialization of an abstract Socket that serves as a base class
 *     for connection oriented and IP-protocol based sockets

 *     IP-protocol based sockets use the IP-protocol as basis i.e.
 *     IP-addressing scheme and certain other semantics. Further
 *     typical specializations of this type of socket are a TCP and a
 *     UDP based socket. An IPSocket can thus not be instantiated. It's
 *     still an abstract class.
 **/
class OSAL_EXPORT IPSocket :
    // inherit the general socket interface
    public Socket,
    public IPObject
{


public: // functions

    /**
     * \brief
     *     If the socket is still in state INACTIVE then it will be
     *     closed by the destructor via a call to close()
     **/
    virtual ~IPSocket();

    /**
     * \brief
     *     Return a reference to the peer IP address used for
     *     communication.

     *     If you want to examine what the peer IP address used for
     *     communication is you can retrieve it via this function
     *     call.
     * \return
     *     The returned object is a reference to the interally
     *     stored IPAddress object.  This is to avoid copying of
     *     the involved address string.
     **/
    const IPAddress& getPeerAddress() const
    {
        return m_peer_address;
    }

    /**
     * \brief
     *     Update the addressing information returned by
     *     getPeerAddress()

     *     If you want to know the real peer address (for example
     *     for sockets created from
     *     TCPServerSocket::acceptConnection() then you can use
     *     this function. This operation may fail for UDPSocket or
     *     other connection-less sockets as there is no static
     *     binding to a peer. In that case an undefined address
     *     will be returned by getPeerAddress()
     *
     *     Calling this function is only valid in case of socket
     *     state being OPEN. Otherwise nothing is done.
     **/
    void updatePeerAddress();

    /**
     * \brief
     *     Update the addressing information returned by
     *     getLocalAddress()
     * \details
     *     If you want to know the local address the socket is buond to
     *     call this after the socket is bound.
     **/

    void updateLocalAddress();

    /**
     * \brief
     *     Common close function for all IPSocket types

     *     Closes the socket on all communication levels. Further
     *     communication will not be possible. Another connection
     *     will not be possible. This object will be DEAD.
     *
     *     Before closing the socket any buffered but not yet
     *     written data in the InputStream base class will be
     *     flushed.
     *
     *     Under certain conditions (e.g. the mentioned flush, the
     *     TCP linger option) this call might block for some time
     *     depending on socket settings and socket type.
     * \pre
     *     Socket must be in state OPEN
     * \post
     *     Socket will be in state DEAD and may not be used for any
     *     communication neither now nor in the future.
     * \param[in]
     *     discard_pending All data not yet send will be discarded
     * \errorindicator
     *     via return code. true is error, false otherwise. (note:
     *     needs to be via return code instead of hasError(), as
     *     multi-threaded use of close() together with read/write
     *     calls may occur in case one thread wants to get the
     *     other out of a blocking read/write call by closing the
     *     socket.
     * \errors
     *     ipl::CommonError with IDs:
     *
     *     - INVALID_USAGE if the socket is already DEAD
     *
     *     Failures in flush or shutdown operation are currently
     *     ignored such that a smooth close of an erroneous socket
     *     is possible.
     **/
    bool close(const bool discard_pending=false) override;

protected: // functions
    /**
     * \brief
     *     Constructs a new IPSocket using the given IP protocol
     *     version

     *     Setups up the m_ipsocket_handle in a defined manner.
     *     Sets up OS dependant address structures. Tries to
     *     resolve provided src and dst addresses into binary IP
     *     addresses.
     * \param[in]
     *     p_blocking Wheter the socket should be in blocking or
     *     non-blocking mode.  This parameter is passed on to the
     *     Socket base class.
     * \param[in]
     *     p_input_buffer The size of a userspace input/read
     *     buffer, if any (zero to disable buffering). This value
     *     is passed on to the Socket base class.
     * \param[in]
     *     p_output_buffer The size of a userspace output/write
     *     buffer, if any (zero to disable buffering). This value
     *     is passed on to the Socket base class.
     * \param[in]
     *     p_src Local IP address to use for communication
     * \param[in]
     *     p_dst Peer IP address to use for communication
     * \param[in]
     *     p_version IP version to use.
     * \note
     *     This abstraction assumes there is always an exact
     *     communication between two defined nodes via network.
     *     Implementations of this class can still provide extended
     *     functions that allow one-to-may communication and
     *     special aspects like "don't care" addresses and alike.
     * \errorindicator
     *     via isValid()
     * \errors
     *     ipl::CommonError with IDs:
     *
     *     the errors stated in IPAddress::resolve() and
     *     IPResolver::resolveName() can occur
     **/
    IPSocket(
        const bool p_blocking,
        const size_t p_input_buffer,
        const size_t p_output_buffer,
        const IPAddress &p_src,
        const IPAddress &p_dst,
        const IPProtocolVersion p_version = IPV4);

protected: // members
    //! the peer IP address to use
    IPAddress m_peer_address;

}; // end class

} // end namespace

#endif // OSAL_IPSOCKET_HXX
