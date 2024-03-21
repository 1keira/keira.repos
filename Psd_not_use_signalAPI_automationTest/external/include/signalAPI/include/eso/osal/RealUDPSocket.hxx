/*
    Copyright e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_REALUDPSOCKET_HXX
#define OSAL_REALUDPSOCKET_HXX

#include <ipl_config.h>

#include <osal/SocketDatagram.hxx>
#include <osal/IPObject.hxx>
#include <common/buffers.hxx>

namespace osal
{

/*!
    \brief This class should be used for all UDP sockets, don't use the UDPSocket class
 **/
class OSAL_EXPORT RealUDPSocket :
    public SocketDatagram,
    public IPObject
{
public:
    class OSAL_EXPORT IpAddress
    {
    public:
        IpAddress() IPL_NOEXCEPT
            : m_binary_handle(), m_address(), m_ip_version(IPVUNSPEC), m_handle_valid(false)
        { /* NOP */ }
        IpAddress(const IPAddressHandleAny &handle) IPL_NOEXCEPT
            : m_binary_handle(handle), m_address(), m_ip_version(IPVUNSPEC), m_handle_valid(true)
        { /*NOP*/ }
        IpAddress(const IPAddress &address, IPProtocolVersion ip_version=IPVUNSPEC) IPL_NOEXCEPT
            : IpAddress(address.address, ip_version)
        { /* NOP */ }
        IpAddress(const std::string &address, IPProtocolVersion ip_version=IPVUNSPEC) IPL_NOEXCEPT;
        ~IpAddress() { /* NOP */ }

        const IPAddressHandleAny& binaryHandle() const IPL_NOEXCEPT { return m_binary_handle; }
        void getBinaryHandle(IPAddressHandleAny& handle, uint16_t port) const IPL_NOEXCEPT;
        const std::string& address() const IPL_NOEXCEPT { return m_address; }
        IPProtocolVersion ipVersion() const IPL_NOEXCEPT { return m_ip_version; }
        bool isValid() const IPL_NOEXCEPT { return m_handle_valid; }

        /**
            \brief Get address and ip_version from address handle

            \return false on success, true on error
            */
        bool resolveFromBinary() IPL_NOEXCEPT;
        bool isAddressValid() const IPL_NOEXCEPT { return m_ip_version != IPVUNSPEC; }
    private:
        IPAddressHandleAny m_binary_handle;
        std::string m_address;
        IPProtocolVersion m_ip_version;
        bool m_handle_valid;
    };

    struct OSAL_EXPORT IpMessage : public Message
    {
        IpAddress peer_address;
        uint16_t peer_port;

        static ipl::Tag type;
        const ipl::Tag& tag() const IPL_NOEXCEPT override { return type; }
    };

    /**
        \p local_address and/or \p port can be
        empty, a suitable address and/or port is chosen by the
        system.

        \p local_address can be in numbers and dots notation or a
        hostname alternatively. If it is a hostname, the constructor
        tries to resolve it.

        If other sockets should be able to use the same \p local_address,
        \p reuse_address has to be true

        \errorindicator
            via isValid()
        \errors
            see SocketBase()
     **/
    RealUDPSocket(
        bool blocking,
        uint16_t local_port=0,
        const std::string &local_address = ANY_IP,
        IPProtocolVersion ip_version = IPVUNSPEC,
        bool reuse_address = false) IPL_NOEXCEPT
        : RealUDPSocket(blocking, local_port, IpAddress(local_address, ip_version), reuse_address) { /* NOP */ }
    RealUDPSocket(
        bool blocking,
        uint16_t local_port,
        const IpAddress &local_address,
        bool reuse_address = false) IPL_NOEXCEPT;

    RealUDPSocket(const RealUDPSocket&) = delete;
    RealUDPSocket& operator=(const RealUDPSocket&) = delete;

    ~RealUDPSocket() IPL_NOEXCEPT override;

    /**
        \brief
            Only data from this address will be received

            If a filter has already been set, a multicast group
            has been joined or the state is not OPEN, this function will
            return an error.
        \return true on failure, false on success
     */
    bool setFilter(const IpAddress &peer_address, uint16_t port) IPL_NOEXCEPT;

    bool hasFilter() const IPL_NOEXCEPT { return m_has_filter; }

    /**
        Join the multicast group in \p mcast_address, if the group hasn't
        been joined before

        For IPV4 the address of the interface which should receive
        multicast messages is required. For IPV6 \p interface_address is
        ignored.

        \note
            The socket will also receive messages transmitted by itself,
            to change this behaviour use setMulticastLoop()

        \errorindicator
            via hasError()
        \errors
            see Socket::setSendBuffer()
     **/
    void joinMulticastGroup(const IpAddress& mcast_address, 
                    const IpAddress& interface_address = IpAddress()) IPL_NOEXCEPT;

    /**
        Undo joinMulticastGroup. Do nothing if the group hasn't been joined.
     **/
    void leaveMulticastGroup(const IpAddress& mcast_address,
                    const IpAddress& interface_address = IpAddress()) IPL_NOEXCEPT;

    bool inMulticastGroup() const IPL_NOEXCEPT {return !m_multicast_addresses.empty();} 

    bool inMulticastGroup(const IpAddress &mcast_address) const IPL_NOEXCEPT
    {
        return m_multicast_addresses.find(mcast_address.address()) != m_multicast_addresses.end();
    } 

    /**
        \brief
            Set specific interface for multicast transmission
        \errorindicator
            via hasError()
        \errors
            see Socket::setSendBuffer()
     **/
    bool setMulticastInterface(const IpAddress& interface_address);


    /**
        allows/disallows reception of multicast messages transmitted by ourself
        \errorindicator
            via hasError()
        \errors
            see Socket::setSendBuffer()
     **/
    bool setMulticastLoop(bool enable) IPL_NOEXCEPT;


    /**
        \brief
            Set ttl/hop limit for multicast transmission
        \errorindicator
            via hasError()
        \errors
            see Socket::setSendBuffer()
     **/
    bool setMulticastTtl(int ttl) IPL_NOEXCEPT;


    /**
        \brief
            enable or disable broadcast reception and transmission

            Default is a disabled broadcast, to prevent the socket
            from accidentally sending a datagram to many systems.
        \note
            If broadcast semantics are needed for application
            purposes then it is more efficient to use a multicast
            group.
        \errorindicator
            via hasError()
        \errors
            see SocketBase::setSendBuffer()
     **/
    void setBroadcast(const bool enable) IPL_NOEXCEPT;

    /**
        \brief
            Retrieves the current broadcast setting from the system.
        \errorindicator
            via hasError()
        \errors
            see SocketBase::getSendBuffer()
     **/
    bool isBroadcast() const IPL_NOEXCEPT;

    size_t maxTxSize() const IPL_NOEXCEPT override
    {
        // send buffer size limits maximum send (usually)
        const size_t bufsize = this->getSendBuffer();
        if( this->hasError() )
        {
            ipl_error.ack();
        }

        return bufsize > max_datagram_size ? max_datagram_size : bufsize;
    }

    /**
        \brief
            Read a message from the socket

            The returned message is of type IPMessage. To get 
            information about the peer, the peer has to be resolved
            with IpMessage::peer.resolveHandle().
        \return nullptr on Error or if no data is available, 
            valid IPMessage object on success
        \errorindicator
            return value is nullptr and hasError() is true
     */
    std::unique_ptr<Message> receive() IPL_NOEXCEPT override;
    /**
        \brief
            Write a message to the socket

            On success send will free \p data.
        \return
           true on error, false on success; also via hasError()
     */
    bool send(const ipl::Buf &data, const IpAddress &address, uint16_t port) IPL_NOEXCEPT;

protected:
    static const size_t max_datagram_size;

    IpAddress m_peer_address;
    uint16_t m_peer_port;
    bool m_has_filter;

    std::set<std::string> m_multicast_addresses;
}; // end class

} // end namespace osal

#endif
