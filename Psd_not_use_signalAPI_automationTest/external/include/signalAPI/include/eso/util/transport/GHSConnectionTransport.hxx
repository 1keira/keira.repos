/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_GHSCONNECTIONTRANSPORT_HXX
#define UTIL_GHSCONNECTIONTRANSPORT_HXX

#include <ipl_config.h>
#include <common/types/string.hxx>
#include <util/transport/ITransport.hxx>
#include <util/transport/PacketSizeLimit.hxx>
#include <osal/integrity/GHSConnection.hxx>

namespace osal {
    class GHSConnection;
}

namespace util
{
namespace transport
{

/**
 * \brief
 *     A transport for GHSConnection connections via GHS connection
**/
class GHSConnectionTransport :
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
    GHSConnectionTransport(const ipl::string& url) IPL_NOEXCEPT;

    /**
     * \brief
     *     Constructor from a GHSConnection descriptor

     *     Use for in a server context where accept returns connection descriptors
     *     when clients connect
     *
     * \param[in,out] conn
     *     The connection descriptor
     * \param[in] config
     * a configuration string for the server connection that produced the description
     * used in error messages
     * \errorindicator
     *     via isValid()
     **/
    GHSConnectionTransport(const osal::GHSConnection::Description& conn, const ipl::string& config) IPL_NOEXCEPT;

    /**
     * \brief
     *     Removes any ressources associated with the transport
     * \preconds
     *     The transports needs to be closed before the destructor
     *     runs
     **/
    virtual ~GHSConnectionTransport() IPL_NOEXCEPT;

    bool isValid() const IPL_NOEXCEPT;

    virtual void open() IPL_NOEXCEPT;

    /**
     * \see
     *     util::ITransport::close()
     * \errorindicator
     *     via return code
     * \return
     *     true on error, false otherwise
     **/
    virtual bool close() IPL_NOEXCEPT;

    /**
     * \brief
     *     Call \c writer with a buffer suitable to hold \c p_size
     *     bytes
     * \param[in] p_size
     *    is the number of bytes to be send
     * \param[in] writer
     *     The Writer that will be provided with a suitable buffer
    */
    virtual bool send(const size_t p_size, IMsgWriter *writer) IPL_NOEXCEPT;

    //! \brief
    //! variant of send(const size_t, IMsgWriter*) for asynchronous
    //! writes
    virtual bool send(const size_t p_size, MsgWriterPtr writer) IPL_NOEXCEPT;

    virtual Readable receive() IPL_NOEXCEPT;

    //! perform a flush on the transport channel
    virtual void flush() IPL_NOEXCEPT;

    //! request the state of the transport. It's not thread safe
    virtual State getState() const IPL_NOEXCEPT;

    //! SL detects peer reset (under certain restrictions)
    virtual bool detectsPeerReset() const IPL_NOEXCEPT { return true; }
    //! is reliable
    virtual bool isReliable() const IPL_NOEXCEPT { return true; }
    //! We've added record boundaries in the implementation
    virtual bool keepsRecordBoundaries() const IPL_NOEXCEPT { return true; }
    //! \brief
    //! As we add record headers and tcp doesn't reorder we can send
    //! very long messages
    virtual size_t maxMsgSize() const IPL_NOEXCEPT { return UINT32_MAX; }

    virtual void dispose();

    // get the peer info. A valid peer info can be retreived after open
    // returns successfully.
    virtual PeerInfoPtr getPeerInfo() const IPL_NOEXCEPT;

    void enablePacketSizeLimit(size_t limit) IPL_NOEXCEPT;

    void disablePacketSizeLimit() IPL_NOEXCEPT;

protected:
    virtual ReqWriteable getWriteable(const size_t p_size);

    virtual bool sendWriteable(ReqWriteable &w);

    osal::GHSConnection* m_conn;

    //! the current transport state
    State m_state;

    bool m_valid;

private:
    bool send(const Readable& readable);

    bool checkConnection(const ipl::string& config);

    PeerInfoPtr m_peer_info;

    PacketSizeLimit m_limit;
};

}
}

#endif /* UTIL_GHSCONNECTIONTRANSPORT_HXX */
