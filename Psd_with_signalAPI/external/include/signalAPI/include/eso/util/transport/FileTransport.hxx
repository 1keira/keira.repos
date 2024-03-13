/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_TRANSPORT_FILETRANSPORT_HXX
#define UTIL_TRANSPORT_FILETRANSPORT_HXX

#include <ipl_config.h>

#include <util/util_dso.h>
#include <util/transport/ITransport.hxx>
#include <util/transport/PacketSizeLimit.hxx>
#include <osal/StreamBinFileRW.hxx>
#include <util/transport/PathPeerInfo.hxx>

namespace util
{

namespace transport
{

/**
 * \brief
 *     Transport implementation reading/writing a file

 *    This is of course not intended to be used on a normal file (the
 *    transport would receive its own sent messages and the storage
 *    would fill up) but on special filesystem objects representing
 *    some bi-directional communication channel like a Unix device
 *    file or a QNX resource manager.
 * \see
 *     QnxResourceManagerTransport
**/
class UTIL_EXPORT FileTransport :
    public IDisposableTransport
{
public:
    /**
     * \brief
     *     Creates a new FileTransport acting on the given path \c
     *     filename
     * \param[in] filename
     *     The path to open for communication
     * \param[in] poll_ms
     *     If opening \c filename should fail, because the path
     *     isn't existing then retry opening the filename after
     *     sleeping for \c poll_ms milliseconds.  If set to zero
     *     then no retries will be performed.
     **/
    FileTransport(const ipl::string &filename, unsigned poll_ms=0) IPL_NOEXCEPT;

    ~FileTransport() IPL_NOEXCEPT;

    virtual State getState() const IPL_NOEXCEPT;

    virtual bool send(const size_t bytes, IMsgWriter *writer) IPL_NOEXCEPT;
    virtual bool send(const size_t bytes, MsgWriterPtr writer) IPL_NOEXCEPT;
    virtual Readable receive() IPL_NOEXCEPT;
    virtual void flush() IPL_NOEXCEPT;
    virtual void open() IPL_NOEXCEPT;
    virtual bool close() IPL_NOEXCEPT;

    virtual bool detectsPeerReset() const IPL_NOEXCEPT;
    virtual bool isReliable() const IPL_NOEXCEPT;
    virtual size_t maxMsgSize() const IPL_NOEXCEPT;
    virtual bool keepsRecordBoundaries() const IPL_NOEXCEPT;

    virtual void dispose();

    virtual PeerInfoPtr getPeerInfo() const IPL_NOEXCEPT;

    void enablePacketSizeLimit(size_t limit) IPL_NOEXCEPT;
    void disablePacketSizeLimit() IPL_NOEXCEPT;

protected:
    virtual ReqWriteable getWriteable(const size_t bytes) IPL_NOEXCEPT;
    virtual bool sendWriteable(ReqWriteable &w) IPL_NOEXCEPT;

    osal::StreamBinFileRW m_file;
    ipl::string m_filename;
    unsigned m_poll_ms;

    PacketSizeLimit m_limit;

    PeerInfoPtr m_peer_info;
};

} // end of namespace transport
} // end of namespace util

#endif
