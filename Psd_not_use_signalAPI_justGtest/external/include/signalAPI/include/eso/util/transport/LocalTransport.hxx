/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_LOCALTRANSPORT_HXX
#define UTIL_LOCALTRANSPORT_HXX

#include <ipl_config.h>
#include <common/types/string.hxx>
#include <util/transport/ITransport.hxx>
#include <util/transport/PacketSizeLimit.hxx>
#include <util/transport/StreamFraming.hxx>
#include <util/transport/StreamIOHandler.hxx>
#include <util/transport/DefaultBufferAllocator.hxx>
#include <osal/UnixSocketBase.hxx>

#if defined (IPL_OS_QNX)
#include <sys/neutrino.h> // for qnx version
#endif
namespace osal {
    class UnixSocket;
}

namespace util
{
namespace transport
{

/**
 * \brief
 *     A transport for local connections via AF_UNIX sockets
**/
class OSAL_EXPORT LocalTransport :
    public IDisposableTransport
{
public:
    /**
     * \brief
     *     Constructor from a transport-url
     * \errorindicator
     *     via isValid()
     * \errors
     * CREATION_ERROR
     **/
    LocalTransport(const ipl::string& url) IPL_NOEXCEPT;

    /**
     * \brief
     *     Constructor from a socket descriptor

     *     Use for in a server context where accept returns socket descriptors
     *     when clients connect
     *
     * \param[in,out] socket
     *     The socket descriptor
     * \param[in] config
     * a configuration string for the server socket that produced the description
     * used in error messages
     * \errorindicator
     *     via isValid()
     **/
    LocalTransport(const osal::UnixSocket::Description& socket, const ipl::string& config) IPL_NOEXCEPT;

    /**
     * \brief
     *     Removes any ressources associated with the transport
     * \pre
     *     The transports needs to be closed before the destructor
     *     runs
     **/
    virtual ~LocalTransport() IPL_NOEXCEPT;
    
    LocalTransport(const LocalTransport &)=delete;
    LocalTransport &operator =(const LocalTransport &)=delete;

    bool isValid() const IPL_NOEXCEPT;

    virtual void open() IPL_NOEXCEPT override;

    /**
     * \see
     *     util::ITransport::close()
     * \errorindicator
     *     via return code
     * \return
     *     true on error, false otherwise
     **/
    virtual bool close() IPL_NOEXCEPT override;

    /**
     * \brief
     *     Call \c writer with a buffer suitable to hold \c p_size
     *     bytes
     * \param[in] p_size
     *    is the number of bytes to be send
     * \param[in] writer
     *     The Writer that will be provided with a suitable buffer
    */
    virtual bool send(const size_t p_size, IMsgWriter *writer) IPL_NOEXCEPT override;

    //! \brief
    //! variant of send(const size_t, IMsgWriter*) for asynchronous
    //! writes
    virtual bool send(const size_t p_size, MsgWriterPtr writer) IPL_NOEXCEPT override;

    virtual Readable receive() IPL_NOEXCEPT override;

    //! perform a flush on the transport channel
    virtual void flush() IPL_NOEXCEPT override;

    //! request the state of the transport. It's not thread safe
    virtual State getState() const IPL_NOEXCEPT override;

    //! SL detects peer reset (under certain restrictions)
    virtual bool detectsPeerReset() const IPL_NOEXCEPT override { return true; }
    //! is reliable
    virtual bool isReliable() const IPL_NOEXCEPT override { return true; }
    //! We've added record boundaries in the implementation
    virtual bool keepsRecordBoundaries() const IPL_NOEXCEPT override { return true; }
    //! \brief
    //! As we add record headers and tcp doesn't reorder we can send
    //! very long messages
    virtual size_t maxMsgSize() const IPL_NOEXCEPT override { return UINT32_MAX; }

    virtual void dispose() override;

    // get the peer info. A valid peer info can be retreived after open
    // returns successfully.
    virtual PeerInfoPtr getPeerInfo() const IPL_NOEXCEPT override;

    virtual void enablePacketSizeLimit(size_t limit) IPL_NOEXCEPT override;
    virtual void disablePacketSizeLimit() IPL_NOEXCEPT override;

    // if the implementation supports it and we're asked to use it, use the abstract namespace,
    // filesystem namespace otherwise
    static osal::UnixSocketBase::NameSpace defaultLocalSocketNamespace(bool use_abstract) IPL_NOEXCEPT {
#ifdef HAVE_AF_UNIX_ABSTRACT
        if (use_abstract)
            return osal::UnixSocketBase::ABSTRACT;
        else
            return osal::UnixSocketBase::FILESYSTEM;
#else
        return osal::UnixSocketBase::FILESYSTEM;
#endif
    }
    // ISelectable interface
    bool isSelectableBy (size_t index) const IPL_NOEXCEPT override {
        return index == util::transport::ISelectable::SOCKET_INDEX;
    }

    SelectableResource getResource() const IPL_NOEXCEPT override {
        if ( m_socket ) {
            return SelectableResource(SocketPair{m_socket->getHandle().rxfd, m_socket->getHandle().txfd});
        }
        // construct from invalid value in default-constructed handle
        return SelectableResource(SocketPair{osal::SocketHandle().rxfd, osal::SocketHandle().txfd});
    }

protected:
    virtual ReqWriteable getWriteable(const size_t p_size) IPL_NOEXCEPT override;
    virtual bool sendWriteable(ReqWriteable &w) IPL_NOEXCEPT override;

    osal::UnixSocket*       m_socket;

    StreamIOHandler*        m_io;
    StreamFramingPtr        m_framing;
    DefaultBufferAllocator  m_allocator;

    //! the current transport state
    State m_state;

    bool m_valid;

private:
    bool checkSocket(const ipl::string& config);

    PeerInfoPtr m_peer_info;

    PacketSizeLimit    m_limit;
};

}
}

#endif /* UTIL_LOCALTRANSPORT_HXX */
